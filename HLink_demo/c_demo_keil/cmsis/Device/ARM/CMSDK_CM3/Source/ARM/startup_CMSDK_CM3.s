;/**************************************************************************//**
; * @file     startup_CMSDK_CM3.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           Device CMSDK_CM3
; * @version  V3.01
; * @date     06. March 2012
; *
; * @note
; * Copyright (C) 2012 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00004000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00001000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler
                DCD     uart0Handler              ; UART 0 RX TX Handler
                DCD     uart1Handler              ; UART 1 RX TX Handler
                DCD     uart2Handler              ; UART 2 RX TX Handler
                DCD     timer0Handler             ; TIMER 0 handler
                DCD     timer1Handler             ; TIMER 1 handler
                DCD     dualtimer0Handler         ; Dual timer handler
                DCD     uartOverflowHandler       ; UART 0 1 2 Overflow Handler
                DCD     pmuHandler                ; PMU Handler
                DCD     spi0Handler               ; SPI 0 handler
                DCD     spi1Handler               ; SPI 1 handler
                DCD     rtcHandler                ; RTC handler
                DCD     i2c0Handler               ; IIC 0 handler
                DCD     i2c1Handler               ; IIC 1 handler
                DCD     fftHandler                ; FFT Handler
                DCD     0                         ; Reserved
                DCD     gpioHandler               ; GPIO0~30 handler
                DCD     dma0Handler               ; DMA0 Handler
                DCD     dma1Handler               ; DMA1 Handler
                DCD     trngHandler               ; TRNG Handler
                DCD     PORT0_6_Handler           ; GPIO Port 0 pin 6 Handler
                DCD     PORT0_7_Handler           ; GPIO Port 0 pin 7 Handler
                DCD     PORT0_8_Handler           ; GPIO Port 0 pin 8 Handler
                DCD     PORT0_9_Handler           ; GPIO Port 0 pin 9 Handler
                DCD     PORT0_10_Handler          ; GPIO Port 0 pin 10 Handler
                DCD     PORT0_11_Handler          ; GPIO Port 0 pin 11 Handler
                DCD     PORT0_12_Handler          ; GPIO Port 0 pin 12 Handler
                DCD     PORT0_13_Handler          ; GPIO Port 0 pin 13 Handler
                DCD     PORT0_14_Handler          ; GPIO Port 0 pin 14 Handler
                DCD     PORT0_15_Handler          ; GPIO Port 0 pin 15 Handler
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]  
                IMPORT  SystemInit
                IMPORT  __main
                 LDR     R0, =SystemInit
                BLX     R0 
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                 B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT uart0Handler             [WEAK]
                EXPORT uart1Handler             [WEAK]
                EXPORT uart2Handler             [WEAK]
                EXPORT timer0Handler            [WEAK]
                EXPORT timer1Handler            [WEAK]
                EXPORT dualtimer0Handler        [WEAK]
                EXPORT uartOverflowHandler      [WEAK]
                EXPORT pmuHandler               [WEAK]
                EXPORT spi0Handler              [WEAK]
                EXPORT spi1Handler              [WEAK]
                EXPORT rtcHandler               [WEAK]
                EXPORT i2c0Handler              [WEAK]
                EXPORT i2c1Handler              [WEAK]
                EXPORT fftHandler               [WEAK]
                EXPORT gpioHandler              [WEAK]
				EXPORT dma0Handler              [WEAK]
                EXPORT dma1Handler              [WEAK]
                EXPORT trngHandler              [WEAK]
                EXPORT PORT0_6_Handler          [WEAK]
                EXPORT PORT0_7_Handler          [WEAK]
                EXPORT PORT0_8_Handler          [WEAK]
                EXPORT PORT0_9_Handler          [WEAK]
                EXPORT PORT0_10_Handler         [WEAK]
                EXPORT PORT0_11_Handler         [WEAK]
                EXPORT PORT0_12_Handler         [WEAK]
                EXPORT PORT0_13_Handler         [WEAK]
                EXPORT PORT0_14_Handler         [WEAK]
                EXPORT PORT0_15_Handler         [WEAK]
uart0Handler       
uart1Handler       
uart2Handler       
timer0Handler      
timer1Handler      
dualtimer0Handler  
uartOverflowHandler
pmuHandler         
spi0Handler        
spi1Handler        
rtcHandler         
i2c0Handler        
i2c1Handler        
fftHandler         
gpioHandler        
dma0Handler        
dma1Handler        
trngHandler        
PORT0_6_Handler    
PORT0_7_Handler    
PORT0_8_Handler    
PORT0_9_Handler    
PORT0_10_Handler   
PORT0_11_Handler   
PORT0_12_Handler   
PORT0_13_Handler   
PORT0_14_Handler   
PORT0_15_Handler   

                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
