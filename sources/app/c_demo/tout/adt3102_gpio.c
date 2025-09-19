//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  adc config
//  adc sampling data with dma
//  
//  
//
//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/4
//--------------------------------------------------------------------
//
//All include header files
#include "adt3102_gpio.h"
#include "adt3102_type_define.h"
#include "string.h"
#include "gpio_ctype_map.h"
//
//------Global variable declaration


/****************************************************************************************
*
*Function name : gpioPullUpDown
*Description   : GPIO set as high-z with pull up or pull down 

*Paramater	   : 
*        @pinNumber :gpio number
*        @pinUpDown :GPIO set as high-z with pull up or pull down, 1:pullUp, 0:pullDown. 
*Return        : None
****************************************************************************************/
void gpioPullUpDown(uint32 pinNumber,uint8 pinUpDown)
{
    //*((uint32*)(GPIO_REGS + pinNumber + 12)) = 1<<4|1<<5|1<<(pinUpDown+6);
    *((uint32*)(GPIO_REGS + pinNumber + 12)) = 1<<4|1<<(pinUpDown+6);    
}
/****************************************************************************************
*
*Function name : gpioOutput
*Description   : GPIO set output high or low level 
*Paramater	   : 
*        @pinNumber :gpio number
*        @pinLeve   :GPIO set output high or low level
*Return        : None
****************************************************************************************/
void gpioOutput(uint32 pinNumber,uint8 pinLeve)
{
    //*((uint32*)(GPIO_REGS + pinNumber + 12)) = 0;
    if(pinLeve == 1)
    {
        GPIO->gpio_out_set |= 1<<pinNumber;
    }
    else{
        GPIO->gpio_out_clear |= 1<<pinNumber;
    }
}
/****************************************************************************************
*
*Function name : getGpioStatus
*Description   : get gpio status 1:high level  0:low level
*Paramater	   : 
*           @pinNumber:gpio number
*Return        1:high level 
               0:low level
****************************************************************************************/
int32 getGpioStatus(uint32 pinNumber)
{
    //*((uint32*)(GPIO_REGS + pinNumber + 12)) = 0x30;
    //return (GPIO->gpio_in)&(1<<pinNumber);
    return ((GPIO->gpio_in)>>pinNumber) & 0x01;
}
/****************************************************************************************
*
*Function name : gpioDirection
*Description   : GPIO set output high or low level 

*Paramater	   : 
*        @pinNumber    :gpio number
*        @pinDirection :GPIO set output or input or high inpendence
                       0:output
                       1:input
                       2:high inpendence
                       3:output & input
*Return        : None
****************************************************************************************/
void gpioDirection(uint32 pinNumber,uint32 pinDirection)
{
    switch (pinDirection)
    {
        case 0:
            *((uint32*)(GPIO_REGS + pinNumber + 12)) = 0;
            break;
        case 1:
            *((uint32*)(GPIO_REGS + pinNumber + 12)) = 0x30;   
            break;
        case 2:
            *((uint32*)(GPIO_REGS + pinNumber + 12)) = 0x10; 
            break;        
        case 3:
            *((uint32*)(GPIO_REGS + pinNumber + 12)) = 0x20; 
            break;        
        default:
            break;
    }
}
/****************************************************************************************
*
*Function name : getGpioDirection
*Description   : get gpio status 1:high level  0:low level
*Paramater	   : None
*        @pinNumber    :gpio number
*Return        : 0:output
                 1:input
                 2:high inpendence
****************************************************************************************/
int32 getGpioDirection(uint32 pinNumber)
{
    uint32 gpioDirect;
    int32 gpioDir;
    gpioDirect = (*((uint32*)(GPIO_REGS + pinNumber + 12)))&(1<<4|1<<5);
    switch (gpioDirect)
    {
        case 0:
            gpioDir = 0;
            break;
        case 0x20:
            gpioDir = 1; 
            break;
        case 0x10:
            gpioDir = 2;
            break;        
        default:
            gpioDir = 3;
            break;
    }
    return gpioDir;
}
/****************************************************************************************
*
*Function name : gpioSetEnint
*Description   : set Gpio iunterrupt

@ param Pin_number   :enable GPIO number
@ param trigger_mode :GPIO trigger mode 1:edge  triggered
										0:level triggered
@ parma trigger_pol  :GPIO trigger pol  1:posedge or high level*        
										0:negedge or low  level*
Return        : None
****************************************************************************************/
#ifdef GPIOCALLBACK
gpioCallback gpioRoutine;
static void *gpioArg;
gpioCallback gpioSetEnintC(uint32 pinNumber,uint32 triggerMode,uint32 triggerPol, gpioCallback gpioFunc,void *data)
{
    *((uint32*)(GPIO_REGS + pinNumber + 12)) = 0x30;
    GPIO->gpio_int_en=1<<pinNumber;//GPIOX interrupt enable
    GPIO->gpio_int_edge_nlevel=triggerMode<<pinNumber;
    GPIO->gpio_int_pol=triggerMode<<pinNumber;
    gpioRoutine = gpioFunc;
    gpioArg = data;
    return gpioRoutine;
}
#else
/*
    pinNumber:      gpio number, include GPIO0-GPIO30.
    triggerMode:    GPIO trigger mode 1:edge triggered 0:level triggered
    triggerPol:     GPIO trigger pol  1:posedge or high level  0:negedge or low level
*/

void gpioSetEnint(uint32 pinNumber,uint32 triggerMode,uint32 triggerPol)
{
    *((uint32*)(GPIO_REGS + pinNumber + 12)) = 0x30;
    GPIO->gpio_int_edge_nlevel=triggerMode<<pinNumber;
    GPIO->gpio_int_pol=triggerMode<<pinNumber;
    GPIO->gpio_int_en=1<<pinNumber;//GPIOX interrupt enable    
}

void gpioDisableint(uint32 pinNumber)
{
    *((uint32*)(GPIO_REGS + pinNumber + 12)) = 0x30;

    GPIO->gpio_int_en=0<<pinNumber;//GPIOX interrupt enable    
}
#endif




