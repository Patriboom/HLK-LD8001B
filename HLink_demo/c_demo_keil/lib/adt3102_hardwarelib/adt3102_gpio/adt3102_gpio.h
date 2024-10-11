#ifndef __GPIO_H
#define __GPIO_H

#include "adt3102_type_define.h"
/***Macro Definition*********************************************************************
GPIOx :gpio ID select
****************************************************************************************/
#define GPIO0 0
#define GPIO1 1
#define GPIO2 2
#define GPIO3 3
#define GPIO4 4
#define GPIO5 5
#define GPIO6 6
#define GPIO7 7
#define GPIO8 8
#define GPIO9 9
#define GPIO10 10
#define GPIO11 11
#define GPIO12 12
#define GPIO13 13
#define GPIO14 14
#define GPIO15 15
#define GPIO16 16
#define GPIO17 17
#define GPIO18 18
#define GPIO19 19
#define GPIO20 20
#define GPIO21 21
#define GPIO22 22
#define GPIO23 23
#define GPIO24 24
#define GPIO25 25
#define GPIO26 26
#define GPIO27 27
#define GPIO28 28
#define GPIO29 29
#define GPIO30 30
/***Macro Definition*********************************************************************
HIGH_LEVEL : gpio output high level
LOW_LEVEL : gpio output low level
****************************************************************************************/
#define HIGH_LEVEL 1
#define LOW_LEVEL 0
/***Macro Definition*********************************************************************
edge_triggered : gpio interrput edge triggered
level_triggered :gpio interrput level triggered
****************************************************************************************/
#define edge_triggered  1
#define level_triggered 0
/****************************************************************************************
*
*Function name : gpioPullUpDown
*Description   : GPIO set as high-z with pull up or pull down 

*Paramater	   : 
*        @pinNumber :gpio number
*        @pinUpDown :GPIO set as high-z with pull up or pull down, 1:pullUp, 0:pullDown. 
*Return        : None
****************************************************************************************/
void gpioPullUpDown(uint32 pinNumber,uint8 pinUpDown);
/****************************************************************************************
*
*Function name : gpioOutput
*Description   : GPIO set output high or low level 

*Paramater	   : 
*        @pinNumber :gpio number
*        @pinLeve   :GPIO set output high or low level
*Return        : None
****************************************************************************************/
void gpioOutput(uint32 pinNumber,uint8 pinLeve);
/****************************************************************************************
*
*Function name : getGpioStatus
*Description   : get gpio status 1:high level  0:low level

*Paramater	   : 
*           @pinNumber:gpio number
*Return        1:high level 
               0:low level
****************************************************************************************/
int32 getGpioStatus(uint32 pinNumber);
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
int32 getGpioDirection(uint32 pinNumber);
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
*Return        : None
****************************************************************************************/
void gpioDirection(uint32 pinNumber,uint32 pinDirection);
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
typedef void (*gpioCallback)(void *gpioArg);
extern gpioCallback gpioSetEnintC(uint32 pinNumber,uint32 triggerMode,uint32 triggerPol, gpioCallback gpioFunc,void *data);
void gpioSetEnint(uint32 pinNumber,uint32 triggerMode,uint32 triggerPol);
void gpioDisableint(uint32 pinNumber);

#endif


