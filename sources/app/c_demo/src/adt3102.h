#ifndef __ADT3102__H
#define __ADT3102__H
//<<< Use Configuration Wizard in Context Menu >>> 


#define ADT3102_1_PATCH  (1)
#define ADT3102_4_PATCH  (2)

#define ADT_HW_ANTENNA_TYPE  ADT3102_1_PATCH

#ifndef ADT_HW_ANTENNA_TYPE
#define ADT_HW_ANTENNA_TYPE  ADT3102_4_PATCH
#endif

#define PWM_OUTPUT_ENABLE   1

//Enable this for LGA board, or disable for Adt3102 Dev board
#define BOARD_LGA_3102      1

//Enable this for IR receiving
#define IR_RECEIVER         1

//This is TF ID used for result report
#define ADT_TF_TYPE         0x0A10

#define BAUDRATE            115200  //115200, 1382400

// Enable this Macro if a quicker response is needed.
// It will enable one quick scan between regular 6.25ms period.
// If disabled, the scan is performed per 6.25ms
#define VARIABLE_SCAN_PERIOD  1

#if VARIABLE_SCAN_PERIOD
#define SCAN_PATTERN_SIZE  2
#endif

/*  
    LGA_BOARD_PIN   LGA_BOARD_NAME   ADT3102_PIN_GPIO  ADT3102_NANE
          5            L_ON/OFF           20            TX2
          6            AIO_CDS                          AIO
          15           IR_IO              17            SCL1
          14           LED_ON/OFF         18            SDA1
          19           DEALY_SET2         16            MOSI1
          20           DEALY_SET1         15            MISO1
          21           CDS_IO2            11            RX1
          22           CDS_IO1            10            TX1
          23           H_SET2             14            CS1
          24           H_SET1             13            SCLK1
*/


/* v1.4.0 */
#define COMPATIBLE


#if BOARD_LGA_3102

#define PIN_IR_INPUT                (17)
#define PIN_DELAY_SET1_INPUT        (15)
#define PIN_DELAY_SET2_INPUT        (16)
#define PIN_DISTANCE_SET1_INPUT     (13)
#define PIN_DISTANCE_SET2_INPUT     (14)
#define PIN_CDS1_INPUT              (10)
#define PIN_CDS2_INPUT              (11)

#define PIN_PMW_OUTPUT              (20)
#define PIN_LED_OUTPUT              (18)

#else

#define PIN_PMW_OUTPUT              (20)

#endif

#if IR_RECEIVER

#ifndef PIN_IR_INPUT
#define PIN_IR_INPUT                (17)
#endif

#endif


//--Debug define e.g.,printf, output result, analog IF sign enbuffer
//<q.0> Enable debug mode 
#define DEBUGMODE 0

//--High clock
#define HIGH_CLOCK_50M  1
#define HIGH_CLOCK_125M 0

#define UART0_PRINTF
//#define UART1_PRINTF

#define HIGH_CLOCK HIGH_CLOCK_125M

//---Tx
//<e>FMCW config
// <o>FSTART
//   <i>Default: 76G(Uint:GHz)
//   <76-80>
#define FSTART    76
// <o>FM
//   <i>Default: 2000(Uint:MHz)
//   <0-4000>
#define FM        4000
// <o>CHIRP_NUM
//   <i>Default: 32
//   <0-256>
#define CHIRP_NUM         64
#define CHIRP_NUM_LOG2    6
              
#define CHIRP_T0          96
#define CHIRP_T1          0
#define CHIRP_T2          0

#define ADC_SAMPLE_RATE   ADC_8P3M       //ADC_16P6M: 16.667mhz.   ADC_8P3M: 8.333mhz
#define REMOVE_FIRST_CHIRP 0 
#define DOWN_SAMPLE       0  //actual down sample rate = 1/(DOWN_SAMPLE+1).
#define SAMPLE_POINT      512
#define RANGE_MIN         3
#define RANGE_MAX         128  
#define RANGE_STEP        5.86 //cm
#define SPEED_STEP        0.49 // cm/s
#define WN_BYPASS         1
#define CHIRP_PERIOD      6250  //us refreshing rate=1e6/32/6250=5Hz
#define FRAME_PERIOD      20000 //us
#define SAGC_EN           1
#define TF_ENABLE         0
#define PRINTF_TF         0

#if BOARD_LGA_3102
#define FRAME_LOWPOWER    0
#else
//#define FRAME_LOWPOWER    0  //temporarily disable this defintion
#endif

#define PRINT_DEBUG_EN    0

//memory address
#define RANGE_ADDR_MAX    128 //no less than RANGE_MAX
#define RNG_FFT_CH1_ADDR  0x20008000 //size 512x32x4=0x10000 
#define DOP_FFT_CH1_ADDR  (RNG_FFT_CH1_ADDR + SAMPLE_POINT*CHIRP_NUM*4) //start 0x20028000,size RANGE_ADDR_MAX*CHIRP_NUM*4=0x4000
#define ABS_CH1_ADDR      RNG_FFT_CH1_ADDR                              //start 0x20008000,size RANGE_ADDR_MAX*CHIRP_NUM*4=0x4000       
#define ABS_MERGE_ADDR    (ABS_CH1_ADDR+RANGE_ADDR_MAX*CHIRP_NUM*4)   //start 0x20010000,size RANGE_ADDR_MAX*CHIRP_NUM*4=0x4000 

//</e>
//---Rx

//---Adc
#define FFT_BUF_HF1 0x20030000         //FFT buffer start address input for 1st half
#define FFT_BUF_HF2 0x20030000 + 256*4 //FFT buffer start address input for 2nd half
#if (ADC_SAMPLE_RATE == ADC_16P6M)
  #define SAMPLE_END_NUM  ceil((CHIRP_T1+CHIRP_T2)*16.666)
  #define INTERVALNUM     (CHIRP_T0+CHIRP_T1+CHIRP_T2)*1000/60	
#else
  #define SAMPLE_END_NUM  ceil((CHIRP_T1+CHIRP_T2)*8.333)
  #define INTERVALNUM     (CHIRP_T0+CHIRP_T1+CHIRP_T2)*1000/120	
#endif
//512 1
//#define FIRREG0  ((0<<13)     +0x1fff)
//#define FIRREG1  ((1<<13)     +0x1) 
//#define FIRREG2  ((0x1ffd<<13)+0x1fff)
//#define FIRREG3  ((5<<13)     +0x0)
//#define FIRREG4  ((0x1ffa<<13)+0x3)
//#define FIRREG5  ((0x4<<13)   +0x1ff7)
//#define FIRREG6  ((0x3<<13)   +0x10)
//#define FIRREG7  ((0x1fef<<13)+0x1fea)
//#define FIRREG8  ((0x25<<13)  +0x16)
//#define FIRREG9  ((0x1fc6<<13)+0x1ff6)
//#define FIRREG10 ((0x46<<13)  +0x1fee)
//#define FIRREG11 ((0x1fc2<<13)+0x40)
//#define FIRREG12 ((0x11<<13)  +0x1f83)
//#define FIRREG13 ((0x58<<13)  +0xc0)
//#define FIRREG14 ((0x1ec2<<13)+0x1f03)
//#define FIRREG15 ((0x4ef<<13) +0x129)
//#define FC       (0x6c8)

#define FIRREG0   0x0
#define FIRREG1   0x0
#define FIRREG2   0x0
#define FIRREG3   0x0
#define FIRREG4   0x0
#define FIRREG5   0x0
#define FIRREG6   0x0
#define FIRREG7   0x0
#define FIRREG8   0x0
#define FIRREG9   0x0
#define FIRREG10  0x0
#define FIRREG11  0x0
#define FIRREG12  0x0
#define FIRREG13  0x0
#define FIRREG14  0x0
#define FIRREG15  0x0
#define FIRREG16  0xfff

#define FC        (FIRREG16 | (DOWN_SAMPLE << fir_cof_sample_rate_down_sample_rate_shift))

typedef enum
{
    ADT_IDLE,
    ADT_SCAN,
    ADT_SLEEP
}ADTStateTypedef;


//---FFT

//---Cfar
#define CFAR_ADDR 0x40024000
#endif
