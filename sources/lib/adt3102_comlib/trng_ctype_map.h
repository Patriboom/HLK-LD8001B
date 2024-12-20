#ifndef __TRNG_MAP_H
#define __TRNG_MAP_H
#include "adt3102_type_define.h"

typedef struct
{
    uint32 reserve0[0x40];
    __IO uint32 RNG_IMR;
    __IO uint32 RNG_ISR;
    __IO uint32 RNG_ICR;
    __IO uint32 TRNG_CONFIG;
    __IO uint32 TRNG_VALUE;
    __IO uint32 EHRDATA0;
    __IO uint32 EHRDATA1; 
    __IO uint32 EHRDATA2; 
    __IO uint32 EHRDATA3; 
    __IO uint32 EHRDATA4; 
    __IO uint32 EHRDATA5; 
    __IO uint32 RND_SOURCE_ENABLE;
    __IO uint32 SAMPLE_CNT1;
    __IO uint32 AUTOCORR_STATISTIC;
    __IO uint32 TRNG_DEBUG_CONTROL;
    uint32 reserve1[0x01];
    __IO uint32 TRNG_SW_RESET;
    uint32 reserve2[0x1d]; 
    __IO uint32 TRNG_BUSY;
    __IO uint32 RST_BIST_COUNTER;
    uint32 reserve3[0x08]; 
    __IO uint32 RNG_BIST_CNTR0;
    __IO uint32 RNG_BIST_CNTR1;
    __IO uint32 RNG_BIST_CNTR2;

} TrngTypeDef;









#endif





