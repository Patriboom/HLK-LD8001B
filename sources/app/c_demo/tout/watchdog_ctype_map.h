#ifndef __WATCHDOG_MAP_H
#define __WATCHDOG_MAP_H
#include "adt3102_type_define.h"
typedef struct
{
	__IO uint32 WDOGLOAD;       /* 0x000 */
	__IO uint32 WDOGVALUE;
	__IO uint32 WDOGCONTROL;
	__IO uint32 WDOGINTCLR;
	__IO uint32 WDOGRIS;
	__IO uint32 WDOGMIS;
       uint32 RESERVED0[0x2fa];
	__IO uint32 WDOGLOCK;       /* 0xc00 */
       uint32 RESERVED1[0xbf];
	__IO uint32 WDOGITCR;       /* 0xf00 */
	__IO uint32 WDOGITOP;
}WATCHDOG_TypeDef;


#endif




