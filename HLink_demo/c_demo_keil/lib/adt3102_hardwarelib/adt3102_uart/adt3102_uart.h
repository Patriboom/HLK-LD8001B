#ifndef __UART_H
#define __UART_H
#include "adt3102_type_define.h"
#include "uart_ctype_map.h"

/****************************************************************************************
*
*Function name : uartInit
*Description   : uart0 and uart1 and uart2 setting
*Paramater	   :
*        @baudRate : Uart baud rate,
*        @*UartX   : Uart number:UART0,UART1,UART2
*Return        : None
****************************************************************************************/
void uartInit(UartTypeDef *UartX, uint32 baudRate, int32 highClock50M);
void assert_failed(uint8* file, uint32 line);

/****************************************************************************************
*
*Function name : uartWrite
*Description   : uart send specified byte data
*Paramater		 :
*        @sendBuff : uart buffered data ready to send
*        @sendLen  : The length of the buffer data uart is ready to send
*        @  : 

*Return    @ len : len uart has sent the length of the data 
****************************************************************************************/
int32 uartWrite(UartTypeDef *UartX,const uint8 *sendBuff, int32 sendLen);
/****************************************************************************************
*
*Function name : uartRead
*Description   : uart receive specified byte data
*Paramater		 :
*        @recvBuff : uart buffered data ready to receive
*        @recvLen  : The length of the buffer data uart is ready to receive
*        @  : 

*Return        @ len : len uart has receive the length of the data 
****************************************************************************************/
int32 uartRead(UartTypeDef *UartX,uint8 *recvBuff, int32 recvLen);
/****************************************************************************************
*
*Function name : printfDebug
*Description   : uart0 and uart1 and uart2 setting
*Paramater	   :
*        @baudRate : Uart baud rate,
*        @*UartX   : Uart number:UART0,UART1,UART2
*Return        : None
****************************************************************************************/
int16 printfDebug(const char *format, ...);
/****************************************************************************************
*
*Function name : printfUart
*Description   : uart0 and uart1 and uart2 printf
*Paramater	   :
*        @UartX : Uart number:UART0,UART1,UART2
*Return        : None
****************************************************************************************/
void printfUart(UartTypeDef *UartX,const char *format, ...);

#endif


