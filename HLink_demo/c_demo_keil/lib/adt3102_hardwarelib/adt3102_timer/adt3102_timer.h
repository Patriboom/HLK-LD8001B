#ifndef __Timer_H
#define __Timer_H
#include "adt3102_type_define.h"
#include "timer_ctype_map.h"

#define clkDIV1   00
#define clkDIV16  01
#define clkDIV256 10

#define MAX_APP_TIMER_NUM 5

typedef struct {
	int8  id;
	int8  active;
	
	int32 counter;
}ADT_APP_Timer_Typedef;


/****************************************************************************************
*
*Function name : Timer0_Init, Timer1_Init
*Description   : Timer initialization, 50:50M high clock,if switch 125M high clock, we have to change
                 50 to 125
*Paramater		 :
*        @time   : set the time of the timer,the unit is us
*        @Timerx : include Timer0,Timer1
*        @highClock50M : select high clock, include 50M and 125M

*Return        : None
****************************************************************************************/
typedef void (*timerCallback)(void *arg);
extern timerCallback timer0Start(float time, timerCallback timerFunc,void *data,int32 highClock50M);
void timerInit(TimerTypeDef *Timerx, float time,int32 highClock50M);
/****************************************************************************************
*
*Function name : timer0Off
*Description   : cloes timer,clear current value
*Paramater		 : None


*Return        : None
****************************************************************************************/
void timerOff(TimerTypeDef *Timerx);
/****************************************************************************************
*
*Function name : timerInclock
*Description   : Timer external clock input for GPIO
*Paramater		 :
*        @time   : set the time of the timer,the unit is us
*        @Timerx : include Timer0,Timer1
*        @highClock50M : select high clock, include 50M and 125M
*Return        : None
****************************************************************************************/
void timerInclock(TimerTypeDef *Timerx ,float time, int32 highClock50M);
/****************************************************************************************
*
*Function name : timerInclock
*Description   : Timer external clock enable for GPIO
*Paramater		 :
*        @time   : set the time of the timer,the unit is us
*        @Timerx : include Timer0,Timer1
*        @highClock50M : select high clock, include 50M and 125M
*Return        : None
****************************************************************************************/
void timerInenable(TimerTypeDef *Timerx ,float time,int32 highClock50M);
void timerCallbackTest(int32 *a);
/****************************************************************************************
*
*Function name : dualtimerInit
*Description   : 
                

*Paramater		 :
*        @reloadValue: timer reload 
*        @clkDiv :clock is divided by clkDiv
                 clkDIV1   :divided by 1
                 clkDIV16  :divided by 16 
                 clkDIV256 :divided by 256
*Return        : None
****************************************************************************************/
void dualtimerInit(uint32 reloadValue, int32 clkDiv);


/****************************************************************************************
*
*Function name : app_timer_init
*Description   : APP Timer initialization, 50:50M high clock,if switch 125M high clock, we have to change
                 50 to 125
*Paramater		 :
*        @Timerx : include Timer0,Timer1
*        @highClock50M   : set Timer clock

*Return        : None
****************************************************************************************/
void app_timer_init(TimerTypeDef *Timerx, int32 highClock50M);

/****************************************************************************************
*
*Function name : app_timer_new
*Description   : Allocate a new APP Timer
*Paramater		 :
*                None

*Return        : Int8  timer id
****************************************************************************************/
int8 app_timer_new(void);


/****************************************************************************************
*
*Function name : app_timer_new
*Description   : Allocate a new APP Timer
*Paramater		 :
*                int8 id :      APP Timer id
*                int32 counter: APP Timer counter

*Return        : None
****************************************************************************************/
void app_timer_start(int8 id, int32 counter);

/****************************************************************************************
*
*Function name : app_timer_clean
*Description   : clean all APP Timer
*Paramater		 :
*                None

*Return        : None
****************************************************************************************/
void app_timer_clean(void);

/****************************************************************************************
*
*Function name : app_timer_update
*Description   : update all active APP Timer
*Paramater		 :
*                None

*Return        : None
****************************************************************************************/
void app_timer_update(void);

/****************************************************************************************
*
*Function name : app_timer_check_timeout
*Description   : check if timeout happened with one certain APP Timer
*Paramater		 :
*                int8 id : APP Timer id

*Return        : int8 : timeout status
****************************************************************************************/
int8 app_timer_check_timeout(int8 id);


#endif




