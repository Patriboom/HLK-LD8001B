//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  .adt3102 uart config 
//  .adt3102 include uart0(gpio0,gpio1),uart1(gpio10,gpio11),uart2(gpio20,gpio21)
//  .baud rate depends on hclk(Generally there are 50M,125M,determined by HIGH_CLOCK)
//  .supports 8bit communication without parity
//  .and is fixed at one stop bit per configuartion
//
//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/24
//--------------------------------------------------------------------
//
//All include header files
#include "adt3102_type_define.h"
#include "adt3102_uart.h"
#include "uart_ctype_map.h"
#include "gpio_ctype_map.h"
#include "stdio.h"
#include "stdarg.h"
#include "adt3102.h"
#include "string.h"
#include "stdarg.h"
//
//------Global variable declaration
uint8 g_uartRecvFlag;

#ifdef  USE_FULL_ASSERT
  /*
    this is aoutput function when a parameter check
    fines an error
  */
  void assert_failed(uint8* file, uint32 line)
  {
      printf("Wrong parameters value: file%s oneline%d \r\n",file,line);
  }
#endif

#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int32 handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int32 x)
{
    x = x;
}
//redefinition fputc function(UART0)
int32 fputc(int32 ch, FILE *f)
{
    #ifdef UART0_PRINTF
        while((UART0->STATE&0X01)== 0x01);
        UART0->DATA = (uint8) ch;
    #endif
    
    #ifdef UART1_PRINTF
        while((UART1->STATE&0X01)== 0x01);
        UART1->DATA = (uint8) ch;
    #endif
    return ch;
}
#endif
/****************************************************************************************
*
*Function name : uartInit
*Description   : uart0 and uart1 and uart2 setting
*Paramater	   :
*        @baudRate : Uart baud rate,
*        @*UartX   : Uart number:UART0,UART1,UART2
*Return        : None
****************************************************************************************/
void uartInit(UartTypeDef *UartX, uint32 baudRate, int32 highClock50M)
{
    assert_param(IS_UART_ALL_PERIPH(UartX));
    uint32 hclkDivision;
    if (UartX == UART0)
    {
        GPIO->gpio_p00_config=0x01;       //uart0 txd
        GPIO->gpio_p01_config=0x01;       //uart0 rxd
    }
    else if( UartX == UART1)
    {
        GPIO->gpio_p10_config=0x01;       //uart1 txd
        GPIO->gpio_p11_config=0x01;       //uart1 rxd 
    }
    else
    {
        GPIO->gpio_p20_config=0x01;       //uart2 txd
        GPIO->gpio_p21_config=0x01;       //uart2 rxd
    }

    hclkDivision = highClock50M ? (50000000/baudRate) : (125000000/baudRate);

    UartX->BAUDDIV = hclkDivision;
    //CTRL[0]:tx enable  CTRL[1]:rx enable 
    //CTRL[2]:tx interrupt enable  CTRL[3]:rx interrupt enable 
    //CTRL[4]:tx overrun interrupt enable  CTRL[5]:rx overrun interrupt enable 
    //CTRL[6]:High-speed test mode for TX only
    UartX->CTRL = 0x0b;
   
}
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
int32 uartWrite(UartTypeDef *UartX,const uint8 *sendBuff, int32 sendLen)
{
    int32 sendNum;
    for(sendNum=0; sendNum<sendLen; sendNum++)
    {
        while((UartX->STATE&0X01)== 0x01){};
        UartX->DATA = sendBuff[sendNum];
    }
    return sendNum;
}
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
int32 uartRead(UartTypeDef *UartX,uint8 *recvBuff, int32 recvLen)
{
    int32 recvNum;
    for(recvNum=0; recvNum<recvLen; recvNum++)
    {
        g_uartRecvFlag = 0;
        while(g_uartRecvFlag == 0){};
        recvBuff[recvNum] = UartX->DATA;
    }
    return recvNum;
}
//function comment examople
/****************************************************************************************
*
*Function name : printfDebug
*Description   : uart0 and uart1 and uart2 setting
*Paramater	   :
*        @baudRate : Uart baud rate,
*        @*UartX   : Uart number:UART0,UART1,UART2
*Return        : None
****************************************************************************************/
int16 printfDebug(const char *format, ...)
{
#if PRINT_DEBUG_EN
    va_list vl;
    va_start(vl, format);
    int16 ret = vprintf(format, vl);
    va_end(vl);
    return ret;
#else
    return 0;
#endif
}

/****************************************************************************************
*
*Function name : printfUart
*Description   : uart0 and uart1 and uart2 printf
*Paramater	   :
*        @UartX : Uart number:UART0,UART1,UART2
*Return        : None
****************************************************************************************/
#define USART_SENDBUFFLEN 256
void printfUart(UartTypeDef *UartX,const char *format, ...)
{
    static char uartSendBuff[USART_SENDBUFFLEN];
    uint16 sendNum = 0;
    
    memset(uartSendBuff,0,USART_SENDBUFFLEN);
    va_list vl;
    va_start(vl, format);
    vsprintf(uartSendBuff,format, vl);
    va_end(vl);
    while(uartSendBuff[sendNum])
    {
        while((UartX->STATE&0X01)== 0x01);
        UartX->DATA = uartSendBuff[sendNum++];
    }
}






