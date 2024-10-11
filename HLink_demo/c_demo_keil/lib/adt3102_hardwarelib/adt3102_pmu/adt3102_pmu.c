//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  .PLLI
//  .PLLN
//  .LDO(1.2v 1.8v )
//  .Buff20G
//  .Buff77G
//  .Tx PA
//  .Phase shift
//  .

//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/9
//--------------------------------------------------------------------
//
//All include header files
#include "adt3102_type_define.h"
#include "adt3102.h"
#include "adt3102_pmu.h"
#include "adt3102_gpio.h"
#include "adt3102_tx.h"
#include "adt3102_rx.h"
#include "adt3102_system.h"
#include "pmu_ctype_map.h"
#include "rfc_ctype_map.h"
#include "gpio_ctype_map.h"
extern uint32 g_phaseShftLut0;
extern uint32 g_phaseShftLut1;

//------Global variable declaration
/****************************************************************************************
*Function name : adt3102 power setting
*Description   : 
****************************************************************************************/
void adt3102PowerSw(int onOroff)
{   
    if(onOroff == 1)
    { 
		
	#if (EN_1V8_EXTERNAL == 1)
		baseband18LDO(DISABLE, BB_LDO_1P8, DISABLE, BB_LDO_1P8);
	#else 
		baseband18LDO(ENABLE, BB_LDO_1P8, DISABLE, BB_LDO_1P8);	
	    delayUs(50,HIGH_CLOCK);	 
        baseband18LDO(ENABLE, BB_LDO_1P8, ENABLE, BB_LDO_1P8);
	#endif
	    delayUs(50,HIGH_CLOCK);	
		
	#if (EN_1V8_EXTERNAL == 1)
		plliLDOEnable(DISABLE, DISABLE);
	#else
		plliLDOEnable(ENABLE, ENABLE);
	#endif	
	    delayUs(50,HIGH_CLOCK);
		
       
	#if (EN_1V8_EXTERNAL == 1)
		 pllnVcoConfig(DISABLE, PLLN_VCO_LDO_1P8);
	#else
		 pllnVcoConfig(ENABLE, PLLN_VCO_LDO_1P8);
	#endif		
	    delayUs(50,HIGH_CLOCK);	  
        pllnPllConfig(ENABLE, PLLN_PLL_LDO_2P5, ENABLE);
	    delayUs(50,HIGH_CLOCK);	  
        dacEnBias1Pd(ENABLE, POWER_ON);
	    delayUs(50,HIGH_CLOCK);
        //As a GPIO, P29 is conflict with debugMode, which would enable analog IF on P29.  
        //Add this to being compatible with some old version of PCB. 
        #if DEBUGMODE
        #else
            gpioOutput(29,1);  //must output 1, ant then set as output. so there is no glitch of P29's high level output.
            gpioDirection(29,0);
        #endif 
        gpioOutput(22,1);  //must output 1, ant then set as output. so there is no glitch of P29's high level output.
        gpioDirection(22,0);        
    }else{
		
	#if (EN_1V8_EXTERNAL == 1)
		plliLDOEnable(DISABLE, DISABLE);
	#else
		plliLDOEnable(DISABLE, ENABLE);
	#endif	

        pllnVcoConfig(DISABLE, PLLN_VCO_LDO_1P8);
        pllnPllConfig(DISABLE, PLLN_PLL_LDO_2P5, DISABLE);
        baseband18LDO(DISABLE, BB_LDO_1P8, DISABLE, BB_LDO_1P8);
        dacEnBias1Pd(DISABLE, POWER_DOWN);
    }
}

void switch_to_50m(void)
{
    int32 regVal=0;
    int32 i;

    //-----------------------------------------------
    //--- switch to DCXO.
    //-----------------------------------------------
    regVal = PMU->pmu_clk_high_reg;
    regVal &= ~pmu_clk_high_reg_ctrl_high_clk_sel_mask << pmu_clk_high_reg_ctrl_high_clk_sel_shift;
    regVal |= 0x0 << pmu_clk_high_reg_ctrl_high_clk_sel_shift;
    PMU->pmu_clk_high_reg = regVal;
    delayUs(100, HIGH_CLOCK);
    for(i=0; i<10; i=i+1);
}

void switch_to_plli(void)
{
    int32 regVal=0;
    int32 i;

    // for adt301. turn on PLLI.
    //RFC->rfc_plli_ctrl_reg = 0xffffffff;

    //-----------------------------------------------
    //--- switch to plli.
    //-----------------------------------------------
    regVal = PMU->pmu_clk_high_reg;
    regVal &= ~pmu_clk_high_reg_ctrl_high_clk_sel_mask << pmu_clk_high_reg_ctrl_high_clk_sel_shift;
    regVal |= 0x1 << pmu_clk_high_reg_ctrl_high_clk_sel_shift;
    PMU->pmu_clk_high_reg = regVal;
    for(i=0; i<10; i=i+1);
}

