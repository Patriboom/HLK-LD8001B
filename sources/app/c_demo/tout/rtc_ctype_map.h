#ifndef __RTC_MAP_H
#define __RTC_MAP_H
#include "adt3102_type_define.h"
typedef struct
{
	__IO uint32 RTCDR;
	__IO uint32 RTCMR;
	__IO uint32 RTCLR;
	__IO uint32 RTCCR;
	__IO uint32 RTCIMSC;
	__IO uint32 RTCRIS;
	__IO uint32 RTCMIS;
	__IO uint32 RTCICR;
}RTC_TypeDef;


#endif
