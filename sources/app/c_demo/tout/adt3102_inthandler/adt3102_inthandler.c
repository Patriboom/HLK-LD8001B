//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  .interrupt hander function
//  .
//  .
//  .
//  .

//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/9
//--------------------------------------------------------------------
//
//All include header files
#include "adt3102_type_define.h"
#include "stdio.h"
#include "adt3102.h"
#include "adt3102_tx.h"
#include "adt3102_rx.h"
#include "uart_ctype_map.h"
#include "dma_ctype_map.h"
#include "gpio_ctype_map.h"
#include "dsp_ctype_map.h"
#include "timer_ctype_map.h"
#include "pmu_ctype_map.h"
#include "rfc_ctype_map.h"
#include "rtc_ctype_map.h"
#include "trng_ctype_map.h"
#include "adt3102_inthandler.h"
#include "adt3102_timer.h"
#include "adt3102_gpio.h"
#include "TinyFrame.h"
//
//------Global variable declaration
extern uint8 g_uartRecvFlag;
extern int v_g_fftFlag;
extern int g_delayUsFlag;
extern int v_g_trngFlag;
extern uint32 g_frameStart;
extern volatile uint32 g_app_timerout;
extern volatile uint8 g_TfRxBuff[TF_RX_BUF_SIZE];
extern volatile uint32 g_TfWriteCount;
extern volatile uint8 g_powerThdFlag;
/****************************************************************************************
*
*Function name : uart0Handler uart1Handler uart2Handler
*Description   : uart's interrupt entry function
*Paramater	   : Nane
*
*Note          :1,you need to turn on the total interrupt, for example, you want to use
                the uart0Hander ,the code you need to initialize is :
                soc_NVIC[soc_SETENA] = 0x01;
                2,you need to change the interrupt entry name in the startip_CMSDK_CM3.s
                to uart0Handler
*Return        Nane
****************************************************************************************/
//watchdog interrupt
void NMI_Handler(void)
{ 

}
void uart0Handler(void)
{
    uint8 resTemp;
    UART0->INTSTATUS=0x02;
    if(UART0->STATE&(1<<1))
    {
        g_powerThdFlag = 1;
        resTemp = UART0->DATA;

        g_TfRxBuff[g_TfWriteCount] = resTemp;
        g_TfWriteCount++;
        g_TfWriteCount %= TF_RX_BUF_SIZE;
    }
}

void dualtimer0Handler(void)  
{
    if((Dualtimer->TMEER2MIS&0x01) == 1)
    {
        Dualtimer->TIMER2INTCLR = 1;
        g_delayUsFlag = 1;
    }
}












