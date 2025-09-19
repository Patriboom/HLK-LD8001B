//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  .timer initial
//  .dualtimer initial
//
//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/24
//$Revision: 1.1, 2021/10/04, Jack, add app timer

//--------------------------------------------------------------------
#include "adt3102_timer.h"
#include "adt3102_type_define.h"
#include "timer_ctype_map.h"
#include "stdio.h"
//
//------Global variable declaration

volatile uint32 g_app_timerout = 0;

static ADT_APP_Timer_Typedef s_adt_app_timer[MAX_APP_TIMER_NUM];



/****************************************************************************************
*
*Function name : Timer0_Init, Timer1_Init
*Description   : Timer init,
                 50:50M high clock,if switch 125M high clock, we have to change  50 to 125
                 excute callback function when timming is up
*Paramater	   :
*        @time    set the time of the timer,the unit is us


*callback function :void Irq3_Handler()
*Return        : None
****************************************************************************************/

#ifdef TIMER_CALLBACK

timerCallback timeRoutine;
void timerCallbackTest(int32 *a )
{
    printf("aaa%d\r\n",*a);
}

static void *arg;

void timer0Handler(void)//Timer0
{
    Timer0->INTSTATUS=1;// clear timer interrupt
    if(timeRoutine)
    {
        timeRoutine(arg);
    }
}

timerCallback timer0Start(float time, timerCallback timerFunc,void *data,int32 highClock50M)
{
    uint32 reload;
    //50M   reload (us)
    reload = highClock50M ? (time*50) : (time*125);
    Timer0->RELOAD=reload;
    Timer0->CTRL=0x09;
    timeRoutine = timerFunc;
    arg = data;
    return timeRoutine;
}
#endif


/****************************************************************************************
*
*Function name : Timer0_Init, Timer1_Init
*Description   : Timer initialization, 50:50M high clock,if switch 125M high clock, we have to change
                 50 to 125
*Paramater		 :
*        @time   : set the time of the timer,the unit is us
*        @Timerx : include Timer0,Timer1

*Return        : None
*Notes        : There is a fixed 1us for timer's function call and interruption call. for example,
              : when time=1   (us), the actual period is about 2us.
              : when time=10  (us), the actual period is about 11us.
              : when time=100 (us), the actual period is about 101us.
              : when time=1000(us), the actual period is about 1001us.
****************************************************************************************/
void timerInit(TimerTypeDef *Timerx, float time, int32 highClock50M)
{
    uint32 reload;
    //50M   reload (us)
    reload = highClock50M ? (time*50) : (time*125);
    Timerx->RELOAD=reload;
    Timerx->CTRL=0x09;
}

/****************************************************************************************
*
*Function name : timer0Off
*Description   : cloes timer,clear current value
*Paramater		 : None


*Return        : None
****************************************************************************************/
void timerOff(TimerTypeDef *Timerx)
{
    Timerx->RELOAD=0;
    Timerx->CTRL=0x00;
    Timerx->VALUE=0;
}
/****************************************************************************************
*
*Function name : timerInclock
*Description   : Timer external clock input for GPIO
*Paramater		 :
*        @Timerx : include Timer0,Timer1

*Return        : None
****************************************************************************************/
void timerInclock(TimerTypeDef *Timerx ,float time, int32 highClock50M)
{
    uint32 reload;
    //Timer0 External clock input GPIO is GPIO2
    //50M   reload (us)
    reload = highClock50M ? (time*50) : (time*125);
    Timerx->CTRL=0x0D;//select external input as high clock
    Timerx->RELOAD = reload;
}
/****************************************************************************************
*
*Function name : timerInclock
*Description   : Timer external clock enable for GPIO
*Paramater		 :
*        @Timerx : include Timer0,Timer1

*Return        : None
****************************************************************************************/
void timerInenable(TimerTypeDef *Timerx ,float time,int32 highClock50M)
{
    uint32 reload;
    //select external GPIO as Timer enable,high level active
    //50M   reload (us)
    reload = highClock50M ? (time*50) : (time*125);
    Timerx->CTRL=0x0b;
    Timerx->RELOAD=reload;
}
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
void dualtimerInit(uint32 reloadValue, int32 clkDiv)
{
    /*RW
    [7]:timer enable
    [6]:timer mode
        0:timer is in free_runing mode
        1:timer is in periodic mode
    [5]:intterrupt enable 1:enable
    [3:2]:timerper 00: 0 stages of perscale,clock is divided by 1
                   01: 4 stages of perscale,clock is divided by 16
                   10: 8 stages of perscale,clock is divided by 256
                   11: not used
    [1]:tiemr size ,0:16-bit counter
                    1:32-bit counter
    [0]:0 wrapping mode
        1 One-shot mode
    */
    Dualtimer->TIMER2CONTROL=1<<7|1<<6|1<<5|(clkDiv<<2)|1<<1|1<<0;
    Dualtimer->TIMER2LOAD=reloadValue;

}

/****************************************************************************************
*
*Function name : app_timer_init
*Description   : APP Timer initialization, 50:50M high clock,if switch 125M high clock, we have to change
                 50 to 125, the counter is always one second
*Paramater		 :
*        @Timerx : include Timer0,Timer1
*        @highClock50M   : set Timer clock

*Return        : None
****************************************************************************************/
void app_timer_init(TimerTypeDef *Timerx, int32 highClock50M)
{
    timerInit(Timerx,(float)1000000, highClock50M);

    app_timer_clean();
}

/****************************************************************************************
*
*Function name : app_timer_new
*Description   : Allocate a new APP Timer
*Paramater		 :
*                None

*Return        : Int8  timer id
****************************************************************************************/
int8 app_timer_new(void)
{
    int id = -1;
    for(int i=0; i<MAX_APP_TIMER_NUM; i++){

        if(s_adt_app_timer[i].active == 0){

            s_adt_app_timer[i].active = 1;

            s_adt_app_timer[i].counter = 0;

            id = s_adt_app_timer[i].id;

            break;

        }

    }

    return id;

}

/****************************************************************************************
*
*Function name : app_timer_start
*Description   : Allocate a new APP Timer
*Paramater		 :
*                int8 id :      APP Timer id
*                int32 counter: APP Timer counter, unit is second

*Return        : None
****************************************************************************************/
void app_timer_start(int8 id, int32 counter)
{
    if((id < 0) || (id > MAX_APP_TIMER_NUM - 1)){
        return;
    }

    s_adt_app_timer[id].counter = counter;

}

/****************************************************************************************
*
*Function name : app_timer_clean
*Description   : clean all APP Timer
*Paramater		 :
*                None

*Return        : None
****************************************************************************************/
void app_timer_clean(void)
{
    for(int i=0; i<MAX_APP_TIMER_NUM; i++){
        s_adt_app_timer[i].id 			= i;
        s_adt_app_timer[i].active 	= 0;
        s_adt_app_timer[i].counter 	= 0;
    }
}


/****************************************************************************************
*
*Function name : app_timer_update
*Description   : update all active APP Timer
*Paramater		 :
*                None

*Return        : None
****************************************************************************************/
void app_timer_update(void)
{
    if(g_app_timerout == 1){
        g_app_timerout = 0;

        for(int i=0; i<MAX_APP_TIMER_NUM; i++){

            if(s_adt_app_timer[i].active == 1){

                if(s_adt_app_timer[i].counter > 0){

                    s_adt_app_timer[i].counter--;

                }
            }
        }
    }
}


/****************************************************************************************
*
*Function name : app_timer_check_timeout
*Description   : check if timeout happened with one certain APP Timer
*Paramater		 :
*                int8 id : APP Timer id

*Return        : int8 : timeout status
****************************************************************************************/
int8 app_timer_check_timeout(int8 id)
{
    if((id < 0) || (id > MAX_APP_TIMER_NUM - 1)){
        return -1;
    }

    return s_adt_app_timer[id].counter;

}




