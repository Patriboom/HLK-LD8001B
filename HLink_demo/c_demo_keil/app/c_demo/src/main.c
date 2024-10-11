/**
 * *****************************************************************************
 * @file    main.c
 * @author  Home(zhhuang@andartechs.com.cn)
 * @version 1.4.0
 * @brief
 *
 *                 Copyright (c) 2021, Andar Technologies Inc.
 *                           www.andartechs.com
 *
 * *****************************************************************************
 */

#include "CM3DS_MPS2.h"
#include "adt3102.h"
#include "adt3102_type_define.h"
#include "adt3102_system.h"
#include "TinyFrame.h"
#include "common.h"

#include <stdio.h>
#include <math.h>


/*------------------------------ variable ------------------------------------*/
volatile uint8  g_powerThdFlag      = 0;
volatile uint32 g_frameStart        = 0;

static uint8                        s_version_major;
static uint8                        s_version_minor;
static uint8                        s_version_patch;
static verStatusTypedef             s_verStatus;
static TinyFrameRx                  s_revTestStr;

/*------------------------------ function ------------------------------------*/

static void rxAndParseData(void);


/**
 * @brief   The entry point of the program.
 * @param   None.
 * @return  int:
 * @note
 */
int main(void)
{
    MY_NVIC_SetVectorTable(0x00000000, 0x8000);

    /*------------ Local variable declaration ------------*/
    s_version_major = 1;
    s_version_minor = 5;
    s_version_patch = 10;

    /*----- Initialize some basic functions --------------*/
    adt3102SystemInit();
    adt3102ModuleInit();

    /*------------- Function realization -----------------*/
    while(1)
    {
        rxAndParseData();
    }
}


/**
 * @brief   ADT3102 analog initialization.
 * @param   None.
 * @return  None.
 * @note
 */
static void rxAndParseData(void)
{
    if(g_powerThdFlag == 1)
    {
        s_revTestStr = tinyFramefRx();

        if (s_revTestStr.receiveType == 0xFFFF)
        {
            s_verStatus.project = PRJ_HUMAN_DETECTION_ID;
            s_verStatus.version_major = s_version_major;
            s_verStatus.version_minor = s_version_minor;
            s_verStatus.version_patch = s_version_patch;

            tinyFramefTx(0xFFFF, (uint8 *)(&s_verStatus), sizeof(s_verStatus));
        }
        g_powerThdFlag = 0;
     }

}
