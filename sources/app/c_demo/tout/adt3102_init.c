/**
 * *****************************************************************************
 * @file    adt3102_init.c
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
#include "common.h"

#include "adt3102_system.h"
#include "gpio_ctype_map.h"
#include "adt3102.h"
#include "adt3102_gpio.h"
#include "adt3102_uart.h"
#include "adt3102_pmu.h"

/**
 * @brief   ADT3102 system initialization.
 * @param   None.
 * @return  None.
 * @note
 */
void adt3102SystemInit(void)
{
    setInterrupt(INT_UART0,     ENABLEINT);

    setInterrupt(INT_DUALTIMER, ENABLEINT);

}


/**
 * @brief   ADT3102 module initialization.
 * @return  None.
 * @note
 */
void adt3102ModuleInit(void)
{
    uartInit(UART0, BAUDRATE, HIGH_CLOCK_50M);

    // power on
    adt3102PowerSw(ON);
}


