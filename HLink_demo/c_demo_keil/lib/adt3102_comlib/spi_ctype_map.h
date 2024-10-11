#ifndef __SPI_MAP_H
#define __SPI_MAP_H
#include "adt3102_type_define.h"

//SSPCR0
#define Fhigh_clock               50000000
#define SPI_datasize_select_4bit  3 
#define SPI_datasize_select_5bit	4
#define SPI_datasize_select_6bit	5
#define SPI_datasize_select_7bit	6
#define SPI_datasize_select_8bit	7
#define SPI_datasize_select_9bit	8
#define SPI_datasize_select_10bit	9
#define SPI_datasize_select_11bit	10
#define SPI_datasize_select_12bit 11
#define SPI_datasize_select_13bit	12
#define SPI_datasize_select_14bit	13
#define SPI_datasize_select_15bit	14
#define SPI_datasize_select_16bit	15
#define SPI_CPOL_High_CPHA_1Edge  ((1<<6)|(0<<7)) //CPOL_High:The idle state of clock is high leve                     
#define SPI_CPOL_High_CPHA_2Edge  ((1<<6)|(1<<7))	//CPOL_Low: The idle state of clock is loew leve 
#define SPI_CPOL_Low_CPHA_1Edge	  ((0<<6)|(0<<7)) //CPHA_1Edge:The first jump edge is sampled
#define SPI_CPOL_Low_CPHA_2Edge	  ((0<<6)|(1<<7)) //CPHA_1Edge:The second jump edge is sampled
#define SPI_SCR	                  1<<8            //Serial clock rate(Fhigh_clock/(2))
//SSPCR1
#define SPI_LBM	     1<<0//Output of transmit serial shifter is connected to input of receive shifter internally
#define SPI_SSE	     1<<1//SPI enable 
#define SPI_Master	 0<<2//SPI is Master mode 
#define SPI_slave    1<<2//SPI is slave mode 	           
#define SPI_SOD	     1<<3//SPI must not drive the SSPTXD output in slave mode 
//SSPSR
#define SPI_TFE 	   1<<0//SPI transmit FIFO is empty
#define SPI_TFNE 	   0<<0//SPI transmit FIFO is not empty
#define SPI_TNF	     0<<1//SPI transmit FIFO is full 
#define SPI_TNNF	   1<<1//SPI transmit FIFO is not full 	
#define SPI_RNE 	   1<<2//SPI receive FIFO is not empty
#define SPI_RE 	     0<<2//SPI receive FIFO is empty
#define SPI_RFF	     1<<3//SPI receive FIFO is full 
#define SPI_RFNF	   0<<3//SPI receive FIFO is not full 		
#define SPI_Busy	   1<<4//SSP is busy 
#define SPI_Nobusy	 1<<4//SSP is idle	
//SSPIMSC
#define SPI_RORIM    0<<0//SPI receive FIFO written to while full condition interrupt is masked  
#define SPI_RORINM   1<<0//SPI receive FIFO written to while full condition interrupt is not masked  
#define SPI_RTIM     0<<1//SPI receive FIFO not empty and no read prior to timeout period interrupt is masked
#define SPI_RTINM    1<<1//SPI receive FIFO not empty and no read prior to timeout period interrupt is not masked
#define SPI_RXIM     0<<2//SPI receive FIFO half full or less condition interrrupt is masked
#define SPI_RXINM    0<<2//SPI receive FIFO half full or less condition interrrupt is not masked
#define SPI_TXIM     0<<3//SPI transmit FIFO half empty or less condition interrruptis masked
#define SPI_TXINM    1<<3//SPI transmit FIFO half empty or less condition interrruptis not masked
//SSPRIS
#define SPI_RORRIS   1<<0//Gives the raw interrupt state ,prior to masking ,of the SSPTXINTR interrupt
#define SPI_RTRIS    1<<1//Gives the raw interrupt state ,prior to masking ,of the SSPRXINTR interrupt  
#define SPI_RXRIS    1<<2//Gives the raw interrupt state ,prior to masking ,of the SSPRTINTR interrupt
#define SPI_TXRIS    1<<3//Gives the raw interrupt state ,prior to masking ,of the SSPRORINTR interrupt  
//SSPMIS
#define SPI_RORMIS   1<<0//Gives the receive over run masked interrupt status ,after masking,of the SSPRORINTR interrupt
#define SPI_RTMIS    1<<1//Gives the receive timeout masked interrupt status ,after masking,of the SSPRORINTR interrupt
#define SPI_RXMIS    1<<2//Gives the receive FIFO masked interrupt status ,after masking,of the SSPRORINTR interrupt
#define SPI_TXMIS    1<<3//Gives the transmit FIFO masked interrupt status ,after masking,of the SSPRORINTR interrupt
//SSPICR
#define SPI_RORIC    1<<0//Clears the SSPRORINTER interrupt 
#define SPI_RTIC     1<<1//Clears the SSPRTINTER interrupt 
//SSPDMACR
#define SPT_RXDMAE   1<<0//Receive DMA Enable.if this bit is set to 1,DMA for the receive FIFO is enable
#define SPT_TXDMAE   1<<1//Transmit DMA Enable.if this bit is set to 1,DMA for the transmit FIFO is enable	

typedef struct
  {
		__IO uint32	SSPCR0;   
		__IO uint32	SSPCR1;  
		__IO uint32	SSPDR;   
		__IO uint32 SSPSR;   
		__IO uint32	SSPCPSR;
		__IO uint32	SSPIMSC;
		__IO uint32	SSPRIS;  
		__IO uint32	SSPMIS;   
		__IO uint32	SSPICR;   
		__IO uint32	SSPDMACR; 
  }SPI_TypeDef;

  
#endif






