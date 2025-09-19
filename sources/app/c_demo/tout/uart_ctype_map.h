#ifndef __UART_MAP_H
#define __UART_MAP_H
#include "adt3102_type_define.h"
#include "stdio.h"

//State
#define TX_buff_full         1<<0  
#define RX_buff_full         1<<1
#define TX_buff_overrun      1<<2//write 1 to clear
#define RX_buff_overrun      1<<2//write 1 to clear
//CTRL
#define TX_enable            1<<0  
#define RX_enable            1<<1  
#define TX_int_en            1<<2//TX interrupt enable
#define RX_int_en            1<<3//RX interrupt enable
#define TX_OR_in_en          1<<4//TX overrun interrupt enable
#define RX_OR_in_en          1<<5//RX overrun interrupt enable
#define High_speed           1<<6//high speed test mode for TX only
//intstatus 
#define Clear_TX_int         1<<0
#define Clear_RX_int         1<<1
#define Clear_TXoverrun_int  1<<2
#define Clear_RXoverrun_int  1<<3

#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == UART0) || \
                                    ((PERIPH) == UART1) || \
                                    ((PERIPH) == UART2))

#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8 *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8* file, uint32 line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

typedef struct
{
    __IO uint32	DATA;
    __IO uint32	STATE;
    __IO uint32	CTRL;
    __IO uint32 INTSTATUS;
    __IO uint32	BAUDDIV;

} UartTypeDef;


#endif




