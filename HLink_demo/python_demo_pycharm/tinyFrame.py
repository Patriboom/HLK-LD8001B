"""
" @File   model_tf.py
" @Author Home
" @Date   2022-02-07
" @Brief
"
"                 Copyright (c) 2022, Andar Technologies Inc.
"                           www.andartechs.com
"
"""
import binascii


class TinyFrame:
    """
    # ----------------------------- FRAME FORMAT ---------------------------------
    #  The format can be adjusted to fit your particular application needs
    # ,-----+-----+-----+------+------------+- - - -+-------------,
    # | SOF | ID  | LEN | TYPE | HEAD_CKSUM | DATA  | DATA_CKSUM  |
    # | 1   | 2   | 2   | 2    |      1     | ...   |      1      | <- size (bytes)
    # '-----+-----+-----+------+------------+- - - -+-------------'
    #
    # SOF ......... start of frame, usually 0x01 (optional, configurable)
    # ID  ......... the frame ID (MSb is the peer bit)
    # LEN ......... number of data bytes in the frame
    # TYPE ........ message type (used to run Type Listeners, pick any values you like)
    # HEAD_CKSUM .. use XOR to calculate the checksum of the header
    #
    # DATA ........ LEN bytes of data (can be 0, in which case DATA_CKSUM is omitted as well)
    # DATA_CKSUM .. use XOR to calculate the checksum of datas

    #  !!! BOTH SIDES MUST USE THE SAME SETTINGS !!!
    # Settings can be adjusted by setting the properties after init
    """
    def __init__(self, peer: int = 1):

        super().__init__()
        self.write = None  # the writer function should be attached here

        self.id_listeners = {}
        self.type_listeners = {}
        self.fallback_listener = None
        self.peer = peer  # the peer bit

        self.fifo_data = bytes()

        #  Adjust sizes as desired (1,2,2,2)
        #  Value of the SOF byte (if TF_USE_SOF_BYTE == 1)
        self.SOF_BYTE = 0x01
        self.ID_BYTES = 0x02
        self.LEN_BYTES = 0x02
        self.TYPE_BYTES = 0x02

        #  Checksum type
        self.CKSUM_TYPE = 'xor'

        #  Use a SOF byte to mark the start of a frame
        self.USE_SOF_BYTE = True

        self.complete = False

        self.next_frame_id = 0

        self.reset_parser()

        self._CKSUM_BYTES = None  # will be updated on first compose / accept

    def reset_parser(self):
        # parser state: SOF, ID, LEN, TYPE, HCK, PLD, PCK
        self.ps = 'SOF'
        # buffer for receiving bytes
        self.rbuf = None
        # expected number of bytes to receive
        self.rlen = 0
        # buffer for payload or checksum
        self.rpayload = None

        self.complete = False

        # received frame
        self.rf = TFMsg()

    def tf_reflect(self, num, width):
        """
        Reverts bit order of the given number

        Args:
            num (int): Number that should be reflected
            width (int): Size of the number in bits
        """
        reflected = 0

        for i in range(width):
            if (num >> i) & 1 != 0:
                reflected |= 1 << (width - 1 - i)

        return reflected

    def tf_crc16(self, data: bytes):
        xor_in = 0x0000  # initial value
        xor_out = 0x0000  # final XOR value
        poly = 0x8005  # generator polinom (normal form)

        reg = xor_in
        for byte in data:
            cur_byte = self.tf_reflect(byte, 8)
            for i in range(8):
                topbit = reg & 0x8000
                if cur_byte & (0x80 >> i):
                    topbit ^= 0x8000
                reg <<= 1
                if topbit:
                    reg ^= poly
            reg &= 0xFFFF
        return self.tf_reflect(reg ^ xor_out, 16)

    def tf_calc_cksum_bytes(self):
        if self.CKSUM_TYPE == 'none' or self.CKSUM_TYPE is None:
            return 0
        elif self.CKSUM_TYPE == 'xor':
            return 1
        else:
            raise Exception("Bad cksum type!")

    def tf_cksum(self, buffer) -> int:
        if self.CKSUM_TYPE == 'none' or self.CKSUM_TYPE is None:
            return 0

        elif self.CKSUM_TYPE == 'xor':
            acc = 0
            for b in buffer:
                acc ^= b
            return (~acc) & ((1 << (self._CKSUM_BYTES * 8)) - 1)

        else:
            raise Exception("Bad cksum type!")

    def tf_gen_frame_id(self) -> int:
        """
        Get a new frame ID
        """

        frame_id = self.next_frame_id

        self.next_frame_id += 1
        if self.next_frame_id > ((1 << (8 * self.ID_BYTES - 1)) - 1):
            self.next_frame_id = 0

        if self.peer == 1:
            frame_id |= 1 << (8 * self.ID_BYTES - 1)

        return frame_id

    def tf_pack(self, num: int, bytes: int) -> bytes:
        """ Pack a number for a TF field """
        return num.to_bytes(bytes, byteorder='big', signed=False)

    def tf_unpack(self, buf) -> int:
        """ Unpack a number from a TF field """
        return int.from_bytes(buf, byteorder='big', signed=False)

    def tf_compose(self, type: int, pld=None, id: int = None) -> tuple:
        """
        Compose a frame.

        frame_id can be an ID of an existing session, None for a new session.
        """
        if self._CKSUM_BYTES is None:
            self._CKSUM_BYTES = self.tf_calc_cksum_bytes()

        if pld is None:
            pld = bytearray()

        if id is None:
            id = self.tf_gen_frame_id()

        buf = bytearray()
        if self.USE_SOF_BYTE:
            buf.extend(self.tf_pack(self.SOF_BYTE, 1))

        buf.extend(self.tf_pack(id, self.ID_BYTES))
        buf.extend(self.tf_pack(len(pld), self.LEN_BYTES))
        buf.extend(self.tf_pack(type, self.TYPE_BYTES))

        if self._CKSUM_BYTES > 0:
            buf.extend(self.tf_pack(self.tf_cksum(buf), self._CKSUM_BYTES))

        if len(pld) > 0:
            buf.extend(pld)
            buf.extend(self.tf_pack(self.tf_cksum(pld), self._CKSUM_BYTES))

        return id, buf

    def accept(self, bytes):
        """
        Parse bytes received on the serial port
        """
        for b in bytes:
            self.accept_byte(b)

    def accept_byte(self, b: int):
        """
        Parsing TF frame format data by byte
        """
        if self._CKSUM_BYTES is None:
            self._CKSUM_BYTES = self.tf_calc_cksum_bytes()

        if self.ps == 'SOF':
            if self.USE_SOF_BYTE:
                if b != self.SOF_BYTE:
                    return

                self.rpayload = bytearray()
                self.rpayload.append(b)

            self.ps = 'ID'
            self.rlen = self.ID_BYTES
            self.rbuf = bytearray()

            if self.USE_SOF_BYTE:
                return
        if self.ps == 'ID':
            self.rpayload.append(b)
            self.rbuf.append(b)

            if len(self.rbuf) == self.rlen:
                self.rf.id = self.tf_unpack(self.rbuf)

                self.ps = 'LEN'
                self.rlen = self.LEN_BYTES
                self.rbuf = bytearray()
            return
        if self.ps == 'LEN':
            self.rpayload.append(b)
            self.rbuf.append(b)

            if len(self.rbuf) == self.rlen:
                self.rf.len = self.tf_unpack(self.rbuf)

                self.ps = 'TYPE'
                self.rlen = self.TYPE_BYTES
                self.rbuf = bytearray()
            return
        if self.ps == 'TYPE':
            self.rpayload.append(b)
            self.rbuf.append(b)

            if len(self.rbuf) == self.rlen:
                self.rf.type = self.tf_unpack(self.rbuf)

                if self._CKSUM_BYTES > 0:
                    self.ps = 'HCK'
                    self.rlen = self._CKSUM_BYTES
                    self.rbuf = bytearray()
                else:
                    self.ps = 'PLD'
                    self.rlen = self.rf.len
                    self.rbuf = bytearray()
                    self.rpayload = bytearray()
            return

        if self.ps == 'HCK':
            self.rbuf.append(b)

            if len(self.rbuf) == self.rlen:
                hck = self.tf_unpack(self.rbuf)
                actual = self.tf_cksum(self.rpayload)

                if hck != actual:
                    self.reset_parser()
                else:
                    if self.rf.len == 0:
                        self.reset_parser()
                    else:
                        self.ps = 'PLD'
                        self.rlen = self.rf.len
                        self.rbuf = bytearray()
                        self.rpayload = bytearray()
            return
        if self.ps == 'PLD':
            self.rpayload.append(b)
            self.rbuf.append(b)

            if len(self.rbuf) == self.rlen:
                self.rf.data = self.rpayload

                if self._CKSUM_BYTES > 0:
                    self.ps = 'PCK'
                    self.rlen = self._CKSUM_BYTES
                    self.rbuf = bytearray()
                else:
                    self.complete = True
                    # self.reset_parser()
            return

        if self.ps == 'PCK':
            self.rbuf.append(b)

            if len(self.rbuf) == self.rlen:
                pck = self.tf_unpack(self.rbuf)
                actual = self.tf_cksum(self.rpayload)

                if pck != actual:
                    self.reset_parser()
                else:
                    self.complete = True
                    # self.reset_parser()
            return


class TFMsg:
    """ A TF message object """

    def __init__(self):
        self.data = bytearray()
        self.len = 0
        self.type = 0
        self.id = 0

    def __str__(self):
        return f"ID {self.id:X}h, type {self.type:X}h, len {self.len:d}, body: {self.data}"


if __name__ == '__main__':
    tinyFrame = TinyFrame()

    """
    Automatically generate TF frame according to configuration.
    ,--------+----------+---------+-----------+------------+-------------------+------------,
    # | SOF  |    ID    |   LEN   |   TYPE    | HEAD_CKSUM |        DATA       | DATA_CKSUM |
    # | 0x01 | 0x0 0x01 | 0x0 0x4 | 0xFF 0xFF |    0xB0    | 0x01 0x02 0x0 0x0 |    0xFC    | <- data (bytes)
    '--------+----------+---------+-----------+------------+-------------------+------------'
    """
    id, rx_b_data = tinyFrame.tf_compose(0xFFFF, (0x1, 0x2, 0x0, 0x0), 1)
    print('Print: received complete data in TF frame format(hex):  ' + str(binascii.hexlify(rx_b_data)))

    for b in rx_b_data:
        tinyFrame.accept_byte(b)
        if tinyFrame.complete:
            if tinyFrame.rf.type == 0xFFFF:
                print("Print: TF frame received and parsed successfully.")

    """
    Automatically generate TF frame according to configuration.
    ,--------+----------+---------+----------+------------+-----------+------------,
    # | SOF  |    ID    |   LEN   |   TYPE   | HEAD_CKSUM |   DATA    | DATA_CKSUM |
    # | 0x01 | 0x0 0x01 | 0x0 0x02| 0x03 0x0 |    0xFE    | 0xA0 0x0A |    0x55    | <- data (bytes)
    '--------+----------+---------+----------+------------+-----------+------------'
    """
    id, rx_b_data = tinyFrame.tf_compose(0x0300, (0xA0, 0x0A), 1)
    print('Print: send complete data in TF frame format(hex):  ' + str(binascii.hexlify(rx_b_data)))
