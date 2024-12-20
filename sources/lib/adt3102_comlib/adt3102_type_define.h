//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description: main function
//**************************************************
//This is a header file that defines data types and
//memory mapping
//
//
//***************************************************
//
//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/24
//--------------------------------------------------------------------
//
//------All include header files
#ifndef __TYPE_DEFINE_H
#define __TYPE_DEFINE_H
/* exact-width signed integer types */
typedef   signed            char int8;
typedef   signed short      int int16;
typedef   signed            int int32;
/* exact-width unsigned integer types */
typedef unsigned            char uint8;
typedef unsigned short      int uint16;
typedef unsigned            int uint32;
typedef unsigned long long  int uint64;   

//define NVIC        
#define soc_NVIC          ((volatile uint32 *)0xE000E100)
#define soc_SETENA        0x00
#define soc_CLRENA        0x20
#define soc_SETPEND       0x80
#define soc_CLRPEND       0xa0
//define System control block.
#define soc_SCB           ((volatile uint32 *)0xE000E010)
#define soc_VTOR          ((volatile uint32 *)0xE000ED08)
#define soc_SCR           ((volatile uint32 *)0xE000ED10)
#define soc_AIRCR         ((volatile uint32 *)0xE000ED0C)

#define     __IO    volatile  
//------------------------------------
//- Memory Mapping.
//------------------------------------
//define memory.        
#define AHB_ROM           ((volatile uint32 *)0x00000000) //ROM     32KB  0x00000000~0x00007fff
#define AHB_RAMI          ((volatile uint32 *)0x00008000) //RAMI    32KB  0x00008000~0x0000ffff
#define AHB_RAMD          ((volatile uint32 *)0x20000000) //RAMD    32KB  0x20000000~0x20007fff
//define AHB slave         
#define TIMER0_REGS       ((volatile uint32 *)0x40000000)	//Timer0's base address.  
#define TIMER1_REGS       ((volatile uint32 *)0x40001000)	//Timer1's base address.  
#define DUALTIMER0_REGS   ((volatile uint32 *)0x40002000)	//DualTimer0's base address.  

#define RFC_REG	          ((volatile uint32 *)0x40003000)


#define UART0_REGS        ((volatile uint32 *)0x40004000)	//UART0's base address.  
#define UART1_REGS        ((volatile uint32 *)0x40005000)	//UART1's base address.  
#define UART2_REGS        ((volatile uint32 *)0x40006000)	//UART2's base address.  
#define TRNG_REGS         ((volatile uint32 *)0x40007000)	//Trng's base address.  
#define WATCHDOG_REGS     ((volatile uint32 *)0x40008000)	//Watchdog's base address.  
#define I2C0_REGS         ((volatile uint32 *)0x40009000)	// I2C0 
#define I2C1_REGS         ((volatile uint32 *)0x4000a000)	// I2C1 
#define TEST_SLAVE_REGS   ((volatile uint32 *)0x4000b000)	//test slave's base address, for validation purpose.  
#define PMU_REGS          ((volatile uint32 *)0x4000c000)
#define RTC_REGS          ((volatile uint32 *)0x4000d000)
#define SPI0_REGS         ((volatile uint32 *)0x4000e000)
#define SPI1_REGS         ((volatile uint32 *)0x4000f000)
#define GPIO_REGS         ((volatile uint32 *)0x40020000)
#define DMA_REGS          ((volatile uint32 *)0x40021000)
#define DSP_REGS          ((volatile uint32 *)0x40022000)

#define RTC                ((RTC_TypeDef       *) RTC_REGS)
#define PMU                ((PMU_TypeDef       *) PMU_REGS)
#define WATCHDOG           ((WATCHDOG_TypeDef  *) WATCHDOG_REGS)
#define DMA                ((DMA_TypeDef       *) DMA_REGS)
#define SPI0               ((SPI_TypeDef       *) SPI0_REGS)
#define SPI1               ((SPI_TypeDef       *) SPI1_REGS)
#define GPIO               ((GPIO_TypeDef      *) (GPIO_REGS))
#define I2C0               ((I2C_TypeDef       *) I2C0_REGS)
#define I2C1               ((I2C_TypeDef       *) I2C1_REGS)
#define UART0              ((UartTypeDef       *) UART0_REGS)
#define UART1              ((UartTypeDef       *) UART1_REGS)
#define UART2              ((UartTypeDef       *) UART2_REGS)
#define TRNG               ((TrngTypeDef       *) TRNG_REGS)
#define Timer0             ((TimerTypeDef      *) TIMER0_REGS)
#define Timer1             ((TimerTypeDef      *) TIMER1_REGS)
#define Dualtimer          ((Dualtimer_TypeDef *) DUALTIMER0_REGS)
#define DSP                ((DSP_TypeDef       *) DSP_REGS)
#define FMCW               ((FMCW_TypeDef      *) FMCW_REG)
#define ATN_PSR            ((ATN_PSR_TypeDef   *) ATN_PSR_REG)
#define PDADC_RF           ((PDADC_RF_TypeDef  *) PDADC_RF_REG)
#define PLLI_PLLN          ((PLLI_PLLN_TypeDef *) PLLI_PLLN_REG)
#define LDO                ((LDO_TypeDef       *) LDO_REG)
#define RFC                ((RFC_TypeDef       *) RFC_REG)
#define VGA                ((VGA_TypeDef       *) VGA_REG)

#endif



















