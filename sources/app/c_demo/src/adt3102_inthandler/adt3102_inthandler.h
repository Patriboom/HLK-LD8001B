#ifndef __INTHANDER__H
#define __INTHANDER__H
#include "adt3102_type_define.h"

/****************************************************************************************
*
*Function name : uart0Handler uart1Handler uart2Handler
*Description   : uart's interrupt entry function
*Paramater	   : Nane
*
*Note          :1,you need to turn on the total interrupt, for example, you want to use
                the uart0Hander ,the code you need to initialize is :
                soc_NVIC[soc_SETENA] = 0x01;
                2,you need to change the interrupt entry name in the startip_CMSDK_CM3.s
                to uart0Handler
*Return        Nane
****************************************************************************************/
void uart0Handler(void);       
void uart1Handler(void);     
void uart2Handler(void);       
void timer0Handler(void);      
void timer1Handler(void);      
void dualtimer0Handler(void);  
void uartOverflowHandler(void);
void pmuHandler(void);         
void spi0Handler(void);        
void spi1Handler(void);        
void rtcHandler(void);         
void i2c0Handler(void);        
void i2c1Handler(void);        
void fftHandler(void);         
void gpioHandler(void);        
void dma0Handler(void);        
void dma1Handler(void);        
void trngHandler(void);     





#endif











