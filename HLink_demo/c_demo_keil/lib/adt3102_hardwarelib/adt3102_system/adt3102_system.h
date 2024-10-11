#ifndef __SYSTEM__H
#define __SYSTEM__H
#include "adt3102_type_define.h"
/***Macro Definition*********************************************************************
INT_xxx :xxx interrupt number
****************************************************************************************/
#define INT_UART0        0
#define INT_UART1        1
#define INT_UART2        2
#define INT_TIMER0       3
#define INT_TIMER1       4
#define INT_DUALTIMER    5
#define INT_UARTOVERFLOW 6
#define INT_PMU          7
#define INT_SPI0         8
#define INT_SPI1         9
#define INT_RTC          10
#define INT_I2C0         11
#define INT_I2C1         12
#define INT_FFT          13
#define INT_GPIO         15
#define INT_DMA0         16
#define INT_DMA1         17
#define INT_TRNG         18
/***Macro Definition*********************************************************************
ENABLEINT  :enable interrupt
DISABLEINT :disable interrupt
****************************************************************************************/
#define ENABLEINT     1
#define DISABLEINT    0

#define ENABLE     1  
#define DISABLE    0   

#define ON     1  
#define OFF    0  

#define		PIN2	(0X0001<<2)
#define		PIN3 	(0X0001<<3)
#define		PIN4	(0X0001<<4)
#define		PIN5 	(0X0001<<5)
#define		PIN6 	(0X0001<<6)
#define		PIN7	(0X0001<<7)
#define		PIN8 	(0X0001<<8)
#define		PIN9 	(0X0001<<9)
#define		PIN10 	(0X0001<<10)
#define		PIN11 	(0X0001<<11)
#define		PIN12 	(0X0001<<12)
#define		PIN13 	(0X0001<<13)
#define		PIN14 	(0X0001<<14)
#define		PIN15 	(0X0001<<15)
#define		PIN16 	(0X0001<<16)
#define		PIN17 	(0X0001<<17)

#define	  GLEDS    	0x3fffc
#define   LEDUP		(PIN5|PIN6|PIN7|PIN8|PIN9|PIN10|PIN11|PIN12|PIN13|PIN15)
#define   LEDDOWN	(PIN2|PIN6|PIN7|PIN8|PIN9|PIN10|PIN11|PIN12|PIN13|PIN17)
#define   LEDLEFT	(PIN3|PIN4|PIN6|PIN8|PIN10|PIN12|PIN14|PIN15|PIN16|PIN17)
#define   LEDRIGHT	(PIN2|PIN3|PIN4|PIN5|PIN6|PIN8|PIN10|PIN12|PIN14|PIN16)
#define   LEDIN		(PIN6|PIN8|PIN10|PIN12)
#define   LEDOUT	(PIN3|PIN4|PIN7|PIN9|PIN11|PIN13|PIN14|PIN16)

#define   LEDUPIN			(PIN3|PIN6|PIN7|PIN10|PIN11|PIN16)
#define   LEDDOWNIN			(PIN4|PIN8|PIN9|PIN12|PIN13|PIN14)
#define   LEDRIGHTIN		(PIN10|PIN11|PIN12|PIN13|PIN14|PIN16)
#define   LEDLEFTIN			(PIN3|PIN4|PIN6|PIN7|PIN8|PIN9)

#define   LEDUPOUT			(PIN5|PIN8|PIN9|PIN12|PIN13|PIN15)
#define   LEDDOWNOUT		(PIN2|PIN6|PIN7|PIN10|PIN11|PIN17)
#define   LEDRIGHTOUT		(PIN2|PIN3|PIN4|PIN5|PIN6|PIN8)
#define   LEDLEFTOUT		(PIN10|PIN12|PIN14|PIN15|PIN16|PIN17)
/****************************************************************************************
*
*Function name : setInterrupt
*Description   : switching interrupt 
*Paramater	   :
*        @interrutNum : interrupt number
*        @enableOrDisenable : on or off total interrupt 1:on 0:off
*        @
NMI: Watchdog
0  : Uart0 tx/rx                9  : spi1
1  : Uart1 tx/rx                10 : RTC
2  : Uart3 tx/rx                11 : IIC0
3  : Timer0                     12 : IIC1
4  : Timer1                     13 : FFT
5  : Dualtimer2                 14 : reserve
6  : Uart0/1/2 overflow         15 : gpio
7  : pmu interrupt              16 : dma_int0
8  : spi0                       17 : dma_int1       18 : TRNG
*        @
*Return        : None
****************************************************************************************/
void setInterrupt(int32 interruptNum, int32 enableOrDisenable);
void turnOnPlli(void);
/****************************************************************************************
*
*Function name : MY_NVIC_SetVectorTable
*Description   : Used to indicate that the vector table is in the code area or in the RAM area
*Paramater	   :
*        @NVIC_VectTab :The defalut of ADT3102 is 0x00000000;
*        @Offset   : vector table offset ,The defalut of ADT3102 is 0x8000
*        @:
*Return        : None
****************************************************************************************/
void MY_NVIC_SetVectorTable(uint32 NVIC_VectTab, uint32 Offset);
/****************************************************************************************
*Function name : switch125MHclk
*Description   : switch 125M highclock
*Paramater	   :
*        @ :  
*        @ :   
*Paramater	selection:		

*Power consumption : 
*Return        :
****************************************************************************************/
void switch125MHclk(void);
/****************************************************************************************
*
*Function name : delayUs
*Description   : The delay realized by dualtimer, the accuracy is in "US"
*Paramater	   :
*        @delayUs : the time you want to delay,in us
*        @highClock50M : high clock setting,50M or 125M
*        @:
*
*function call example:  delayUs(1000,HIGH_CLOCK);
*Return        : None
****************************************************************************************/
void delayUs(uint32 delayUs,int32 highClock50M);
float getRangeRes(uint32 fm, uint32 t0, uint16 downSample, uint16 fftPoint);
/****************************************************************************************
*Function name : ledInit
*Description   : initalization p2~p17  
*Paramater	   : 
*Return        : None
****************************************************************************************/
void ledInit(void);
/****************************************************************************************
*Function name : ledAllon
*Description   : turn on all p2~p17
*Paramater	   : 
*        @ : 
*Return        : None
****************************************************************************************/
void ledAllon(void);
/****************************************************************************************
*Function name : ledAlloff
*Description   : turn off all p2~17
*Paramater	   : 
*Return        : None
****************************************************************************************/
void ledAlloff(void);
/****************************************************************************************
*Function name : ledOn
*Description   : turn on  led 
*Paramater	   : 
*        @Pin_number :gpio number
*Return        : None
****************************************************************************************/
void ledOn(unsigned int Pin_number);
/****************************************************************************************
*Function name : ledOff
*Description   : turn off led  
*Paramater	   : 
*        @Pin_number :gpio number
*Return        : None
****************************************************************************************/
void ledOff(unsigned int Pin_number);
/****************************************************************************************
*Function name : ledDisplay
*Description   : led gesture indication
*Paramater	   : 
*        @actionType :gesture indication  1:IN 2:OUT 3:LEFT 4:RIGHT 5:UP 6:DOWN
*Return        : None
****************************************************************************************/
void ledDisplay(uint32 actionType);

#endif












