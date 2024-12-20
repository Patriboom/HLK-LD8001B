# README

## c_demo_keil

This project must be based on the radar chip models **ADT310x and ADT60xx** series produced by `ANDAR company `before it  can be compiled and run.

The function realized in the project is that after the radar receives TF frame data through **UART0 (Message Type: 0xFFFF)**, analyze the data, and then return the data.

### Upper Computer -> ADT310x

|   Format   | SOF  |  ID  | LEN  | TYPE | HEAD_CKSUM | DATA | DATA_CKSUM |
| :--------: | :--: | :--: | :--: | :--: | :--------: | :--: | :--------: |
| Value(HEX) |  01  | 8000 | 0000 | FFFF |     7E     | NULL |    NULL    |



### ADT310x -> Upper Computer

|   Format   | SOF  |  ID  | LEN  | TYPE | HEAD_CKSUM |    DATA     | DATA_CKSUM |
| :--------: | :--: | :--: | :--: | :--: | :--------: | :---------: | :--------: |
| Value(HEX) |  01  | 0015 | 0004 | FFFF |     EF     | 00 01 05 0A |     F1     |

