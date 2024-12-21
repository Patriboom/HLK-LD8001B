//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  .include some commonly used function modules
//  .
//
//
//
//
//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/24
//--------------------------------------------------------------------
//
//All include header files
#include "CMSDK_CM3.h"
#include "adt3102_type_define.h"
#include "adt3102_uart.h"
#include "adt3102_pmu.h"
#include "adt3102_timer.h"
#include "adt3102_system.h"
#include "uart_ctype_map.h"
#include "gpio_ctype_map.h"
#include "pmu_ctype_map.h"
#include "rfc_ctype_map.h"
#include "stdio.h"
#include "adt3102.h"
#include "adt3102_gpio.h"
#include "adt3102_tx.h"
#include "adt3102_rx.h"
#include "adt3102_system.h"
//
//------Global variable declaration
volatile int32 g_delayUsFlag;
#ifndef  __NO_SYSTEM_INIT
void SystemInit()
{
    //Init.
    for(uint32 i=0;i<10000;i++){}
}
#endif
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
void setInterrupt(int32 interruptNum, int32 enableOrDisenable)
{
    if (enableOrDisenable == 0)
        soc_NVIC[soc_CLRENA] = 1<<interruptNum;  //clear interrupt.
    else
        soc_NVIC[soc_SETENA] = 1<<interruptNum;  //enable interrupt.
}

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
void MY_NVIC_SetVectorTable(uint32 NVIC_VectTab, uint32 Offset)
{
    //set NVIC's vector table offset register
    SCB->VTOR = NVIC_VectTab|(Offset & (uint32)0x1FFFFF80);
    __enable_irq();

}

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
void delayUs(uint32 delayus, int32 highClock50M)
{
    g_delayUsFlag = 0;
    if (highClock50M == 1)
    {
        dualtimerInit(delayus*50-1,clkDIV1);
    }else
    {
        dualtimerInit(delayus*125-1,clkDIV1);
    }
    while(g_delayUsFlag != 1);
}

/****************************************************************************************
*
*Function name : system_reset
*Description   : system reset
*Paramater	   :
*        @:
*
*Return        : None
****************************************************************************************/
void system_reset(void)
{
    int32 regVal=0;
    // read 0xE000ED0C, and then change key to 0x05fa, and write bit [2] = 1.
    regVal = soc_AIRCR[0x0];
    regVal = (0x0000ffff & regVal) | 0x05fa0004;
    soc_AIRCR[0x0] = regVal;
}


/****************************************************************************************
*Function name :
*Description   :
*Paramater	   :
*        @ :
*        @ :
*Paramater	selection:

*Power consumption :
*Return        :
****************************************************************************************/
void switch125MHclk(void)
{
    //delayUs(1000, HIGH_CLOCK);
    switch_to_plli();
    //delayUs(1000, HIGH_CLOCK_125M);
}

/****************************************************************************************
*Function name :
*Description   :
*Paramater	   :
*        @ :
*        @ :
*Paramater	selection:

*Power consumption :
*Return        :
****************************************************************************************/
float getRangeRes(uint32 fm, uint32 t0, uint16 downSample, uint16 fftPoint)
{
    float rangeResolution;
    rangeResolution = 300000000.0*(t0/1000000.0)*(125.0/15.0/(downSample+1)*1000000.0)/2.0/(fm*1000000.0)/fftPoint;
    return rangeResolution;
}


/****************************************************************************************
*Function name : ledAlloff
*Description   : turn off all p2~17
*Paramater	   :
*        @ch0 :
*        @ch1 :
*Return        : None
****************************************************************************************/
void ledAlloff(void)
{
    GPIO->gpio_out_clear=0x03FFFC;
}
/****************************************************************************************
*Function name : ledAllon
*Description   : turn on all p2~p17
*Paramater	   :
*        @ :
*Return        : None
****************************************************************************************/
void ledAllon(void)
{
    GPIO->gpio_out_set	=0x03FFFC;
}
/****************************************************************************************
*Function name : ledInit
*Description   : initalization p2~p17
*Paramater	   :
*Return        : None
****************************************************************************************/
void ledInit(void)
{
    gpioDirection(2,0);
    gpioDirection(3,0);
    gpioDirection(4,0);
    gpioDirection(5,0);
    gpioDirection(6,0);
    gpioDirection(7,0);
    gpioDirection(8,0);
    gpioDirection(9,0);
    gpioDirection(10,0);
    gpioDirection(11,0);
    gpioDirection(12,0);
    gpioDirection(13,0);
    gpioDirection(14,0);
    gpioDirection(15,0);
    gpioDirection(16,0);
    gpioDirection(17,0);
}
/****************************************************************************************
*Function name : ledOn
*Description   : turn on  led
*Paramater	   :
*        @Pin_number :gpio number
*Return        : None
****************************************************************************************/
void ledOn(uint32 actionType)
{
    GPIO->gpio_out_set=actionType&0x03FFFC;
}
/****************************************************************************************
*Function name : ledOff
*Description   : turn off led
*Paramater	   :
*        @Pin_number :gpio number
*Return        : None
****************************************************************************************/
void ledOff(unsigned int Pin_number)
{
    GPIO->gpio_out_clear=Pin_number&0x3fffff;
}
/****************************************************************************************
*Function name : ledDisplay
*Description   : led gesture indication
*Paramater	   :
*        @actionType :gesture indication  1:IN 2:OUT 3:LEFT 4:RIGHT 5:UP 6:DOWN
*Return        : None
****************************************************************************************/
void ledDisplay(uint32 actionType)
{
    switch(actionType)
    {
        case 0:
            break;
        case 1:
            ledOn(LEDIN);
            break;
        case 2:
            ledOn(LEDOUT);
            break;
        case 3:
            ledOn(LEDLEFT);
            break;
        case 4:
            ledOn(LEDRIGHT);
            break;
        case 5:
            ledOn(LEDUP);
            break;
        case 6:
            ledOn(LEDDOWN);
            break;
        default:
            break;
    }
}




