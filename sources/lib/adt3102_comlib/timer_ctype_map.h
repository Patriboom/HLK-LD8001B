#ifndef __TIMER_MAP_H
#define __TIMER_MAP_H
#include "adt3102_type_define.h"
#define TIMERITCR          0x3C0
#define TIMERITOP          0x3C1
typedef struct
{
    __IO uint32 CTRL;
    __IO uint32 VALUE;
    __IO uint32 RELOAD;
	__IO uint32 INTSTATUS;
    
}TimerTypeDef;
//CTRL
#define Timer_enable        1<<0
#define Sel_exinput_enable  1<<1
#define Sel_exinput_clock   1<<2
#define Timer_int_enable    1<<3

/*********************************------Dualtimer------******************************************/ 
typedef struct
{
  __IO uint32 TIMER1LOAD;
  __IO uint32 TIMER1VALUE;   
  __IO uint32 TIMER1CONTROL;
  __IO uint32 TIMER1INTCLR;
  __IO uint32 TIMER1RIS;
  __IO uint32 TMEER1MIS;
  __IO uint32 TIMER1BGLOAD;
       uint32 RESERVED1;
  __IO uint32 TIMER2LOAD;
  __IO uint32 TIMER2VALUE;
  __IO uint32 TIMER2CONTROL;
  __IO uint32 TIMER2INTCLR;
  __IO uint32 TIMER2RIS;
  __IO uint32 TMEER2MIS;
  __IO uint32 TIMER2BGLOAD;
}Dualtimer_TypeDef; 
//CTRL
#define  Oneshot          1<<0
#define  Wrapping         0<<0
#define  Timer_size_32bit 1<<1
#define  Timer_size_16bit 0<<1
#define  Timer_prescale_1   ((1<<2)-1)
#define  Timer_prescale_16  ((1<<2))
#define  Timer_prescale_256	(1<<3)
#define  Timer_prescale_NO  ((1<<3)+1)
#define  int_Enable       1<<5
#define  freerunning      0<<6
#define  periodic         1<<6
#define  Dultimer_enable  1<<7



#endif

