/**
 * *****************************************************************************
 * @file    common.h
 * @author  Home(zhhuang@andartechs.com.cn)
 * @version 1.4.0
 * @date    2021-11-01
 * @brief   
 * 
 *                 Copyright (c) 2021, Andar Technologies Inc.
 *                           www.andartechs.com
 * 
 * *****************************************************************************
 */
#ifndef __DAT3102_INIT_H
#define __DAT3102_INIT_H
#include "adt3102_type_define.h"


/*--------------------------------- define -----------------------------------*/
#define PRJ_HUMAN_DETECTION_ID     (0)
#define PRJ_BREATH_DETECTION_ID    (1)
#define PRJ_GESTURE_DETECTION_ID   (2)
#define PRJ_RANGE_DETECTION_ID     (3)
#define PRJ_PEOPLE_COUNTING_ID     (4)


#define DOP_MIN                    ((int32)0)
#define FIRST_PEAK_ONLY            ((uint32)0)
#define DIST_COMP                  ((uint32)0)

/*--------------------------------- typedef ----------------------------------*/
typedef struct {
    uint32 curTiaGain;
    uint32 curVgaGain;
}curGainStrTypedef;

typedef struct {
    float powerDbDisp;
    float distanceDisp;
} DispStrTypedef;


/*--------------------------------- typedef ----------------------------------*/
typedef enum
{
    POWER_SWITCH_ON     = 0,
    POWER_SWITCH_DOWN
} PowerSWitchTypedef;


typedef struct
{
    int8   timer1_id;
    int8   timer2_id;
    int8   timer3_id;
} timerContextTypedef;


/*------------------------------ variable ------------------------------------*/
/*------------------------------ function ------------------------------------*/
/**
 * @brief   ADT3102 system initialization.
 * @param   None.
 * @return  None.
 * @note
 */
void adt3102SystemInit(void);

/**
 * @brief   ADT3102 module initialization.
 * @return  None.
 * @note
 */
void adt3102ModuleInit(void);


#endif
