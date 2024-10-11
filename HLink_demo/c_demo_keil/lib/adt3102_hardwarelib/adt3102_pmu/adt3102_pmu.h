#ifndef __PMU__H
#define __PMU__H
#include "adt3102_type_define.h"
/****************************************************************************************
*Function name : adt3102PowerSw
*Description   : adt3102 power setting
*Paramater	   :
*        @ onOroff: power on plli pll, plli vco, plln pll, plln vco, bb1 and bb2, bias1 and so on
*        @ :   
*Paramater	selection:		

*Power consumption : None
*Return        :
****************************************************************************************/
void adt3102PowerSw(int onOroff);
/****************************************************************************************
*Function name : switch_to_50m
*Description   : select high_clk as 50MHz
*Paramater	   : None
*        @ :  
*        @ :   
*Paramater	selection:		None

*Power consumption : None
*Return        :
****************************************************************************************/
void switch_to_50m(void);
/****************************************************************************************
*Function name : switch_to_plli
*Description   : select high_clk as 125MHz
*Paramater	   : None
*        @ :  
*        @ :   
*Paramater	selection:		None

*Power consumption : None
*Return        :
****************************************************************************************/
void switch_to_plli(void);

#endif






