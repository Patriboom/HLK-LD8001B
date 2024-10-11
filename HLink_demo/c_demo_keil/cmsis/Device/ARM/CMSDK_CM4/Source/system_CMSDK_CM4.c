/**************************************************************************//**
 * @file     system_CMSDK_CM4.c
 * @brief    CMSIS Cortex-M4 Device Peripheral Access Layer Source File for
 *           Device CMSDK
 * @version  V3.01
 * @date     06. March 2012
 *
 * @note
 * Copyright (C) 2010-2012 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#include <stdint.h>
#include "CMSDK_CM4.h"


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/

#define XTAL    (50000000UL)            /* Oscillator frequency               */


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemFrequency = XTAL;    /*!< System Clock Frequency (Core Clock)  */
uint32_t SystemCoreClock = XTAL;    /*!< Processor Clock Frequency            */


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
  #if __FPU_PRESENT == 1
    SCB->CPACR |= (0xF << 20);               /* cp10 and cp11 set in CPACR    */
  #endif

  SystemCoreClock = XTAL;

  return;
}
/**
 * Update the SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Update the SystemCoreClock variable after clock setting changed.
 */
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
 SystemCoreClock = XTAL;
}

/* The below code snipet is required as a workaround.
 * False OVL_ERROR happens when using the Cortex-M4F core with the ARMCC compiler.
 * The C library initialization code uses the VMSR instruction to set FZ and DN bits
 * in the FPSCR register and this access triggers the false OVL_ERROR.
 * The below code overrides the original _fp_init procedure and uses standard
 * load/store instructions instead the VMSR to set the same bist in the FPDSCR.
 */
#if __FPU_PRESENT == 1

#if defined ( __CC_ARM   )

__asm void _fp_init(void) {
  LDR     R1,[pc,#8]            /* address of the FPDSCR register (0xE000EF3C)  */
  LDR     R0,[R1,#0]            /* load                                         */
  ORR     R0,R0,#0x03000000     /* modify, set FZ and DN (bits 24 and 25)       */
  STR     R0,[R1,#0]            /* write                                        */
  BX      LR                    /* return                                       */
  DCD     3758157628            /* constant address of FPDSCR (0xE000EF3C)      */
}

#endif

#endif

