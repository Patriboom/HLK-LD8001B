#ifndef __RX_H
#define __RX_H
#include "adt3102_type_define.h"

/***Macro Definition*********************************************************************
TIA_GAIN_xDB :TIA diff gain setting, 0~18dB, 6dB/bit
****************************************************************************************/
#define TIA_GAIN_0DB  0
#define TIA_GAIN_6DB  1
#define TIA_GAIN_12DB 2
#define TIA_GAIN_18DB 3
/***Macro Definition*********************************************************************
PGA_GAIN_xDB :PGA diff gain, 0~40dB,2dB/bit
****************************************************************************************/
#define PGA_GAIN_0DB    0  
#define PGA_GAIN_2DB    1    
#define PGA_GAIN_4DB    2
#define PGA_GAIN_6DB    3
#define PGA_GAIN_8DB    4
#define PGA_GAIN_10DB   5
#define PGA_GAIN_12DB   6
#define PGA_GAIN_14DB   7
#define PGA_GAIN_16DB   8
#define PGA_GAIN_18DB   9
#define PGA_GAIN_20DB   10
#define PGA_GAIN_22DB   11
#define PGA_GAIN_24DB   12
#define PGA_GAIN_26DB   13
#define PGA_GAIN_28DB   14
#define PGA_GAIN_30DB   15
#define PGA_GAIN_32DB   16
#define PGA_GAIN_34DB   17
#define PGA_GAIN_36DB   18
#define PGA_GAIN_38DB   19
#define PGA_GAIN_40DB   20
#define PGA_GAIN_42DB   21
#define PGA_GAIN_44DB   22
#define PGA_GAIN_46DB   23
#define PGA_GAIN_48DB   24
/***Macro Definition*********************************************************************
PGA_CAL_Nx :I/Q calibration gain range: -1~1dB, 0.5dB/bit
****************************************************************************************/
#define PGA_CAL_N1 0  //-1DB
#define PGA_CAL_N5 1  //-0.5DB
#define PGA_CAL_P1 2  //0.5DB
#define PGA_CAL_P5 3  //1DB
/***Macro Definition*********************************************************************
RC_HPF_xKHZ :rc hpf select
****************************************************************************************/
#define RC_HPF_150KHZ  150
#define RC_HPF_400KHZ  400
/***Macro Definition*********************************************************************
TIA_HPF_xKHZ :tia hpf parameter select
****************************************************************************************/
#define TIA_HPF_25KHZ   0
#define TIA_HPF_50KHZ   1
#define TIA_HPF_100KHZ  2
#define TIA_HPF_300KHZ  3
/***Macro Definition*********************************************************************
PGA_LPF_xM :pga lpf parameter select
****************************************************************************************/
#define PGA_LPF_2M 0
#define PGA_LPF_4M 1
#define PGA_LPF_6M 2
#define PGA_LPF_8M 3
/***Macro Definition*********************************************************************
PGA_HPF_xKHZ :pga hpf parameter select
****************************************************************************************/
#define PGA_HPF_25KHZ  0
#define PGA_HPF_50KHZ  1
#define PGA_HPF_100KHZ 2
#define PGA_HPF_500KHZ 3
/****************************************************************************************
*Function name : rxLnaEnable
*Description   : control rx lna enable
*Paramater	   :
*        @lna0Enable : rx0 enable
*        @lna1Enable : rx1 enable
*
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rxLnaEnable(int32 lna0Enable, int32 lna1Enable);
/****************************************************************************************
*Function name : mixerEnable
*Description   : control mixer enable
*Paramater	   :
*        @ch0MixerEnable : channel0 Mixer enable
*        @ch1MixerEnable : channel1 Mixer enable
*
*Power consumption : No
*Return        : None
****************************************************************************************/
void mixerEnable(int32 ch0MixerEnable, int32 ch1MixerEnable);
/****************************************************************************************
*Function name : lnaRegularBias
*Description   : control mixer enable
*Paramater	   :
*        @ch0MixerEnable : channel0 Mixer enable
*        @ch1MixerEnable : channel1 Mixer enable
*
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void lnaRegularBias(int32 lna0bias, int32 lna1bias);
/****************************************************************************************
*Function name : lnaDacBias
*Description   : control dac lna bias
*Paramater	   :
*        @ch0bias1 : channel0 DAC bias1
*        @ch0bias2 : channel0 DAC bias2
*        @ch0bias3 : channel0 DAC bias3
*        @ch1bias1 : channel1 DAC bias1
*        @ch1bias2 : channel1 DAC bias2
*        @ch1bias3 : channel1 DAC bias3
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void lnaDacBias(int32 ch0bias1, int32 ch0bias2, int32 ch0bias3, int32 ch1bias1, int32 ch1bias2, int32 ch1bias3);
/****************************************************************************************
*Function name : rfTiaEnable
*Description   : control tia enable
*Paramater	   :
*        @tia0enable : enable TIA0
*        @tia1enable : enable TIA0
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfTiaEnable(int32 tia0Enable, int32 tia1Enable);
/****************************************************************************************
*Function name : rfTiaGainSetting
*Description   : control tia gain setting
*Paramater	   :
*        @tia0IGain : TIA0I diff gain setting
*        @tia0QGain : TIA0Q diff gain setting
*        @tia1IGain : TIA1I diff gain setting
*        @tia1QGain : TIA1Q diff gain setting
*Paramater	selection:TIA_GAIN_0DB 
                      TIA_GAIN_6DB 
                      TIA_GAIN_12DB
                      TIA_GAIN_18DB
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfTiaGainSetting(int32 tia0IGain, int32 tia0QGain, int32 tia1IGain, int32 tia1IQain);
/****************************************************************************************
*Function name : rfTiaDacBias
*Description   : control tia bias setting
*Paramater	   :
*        @tia0bias : TIA0I tia bias 
*        @tia1bias : TIA0Q tia bias 
*Paramater	selection:0~15
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfTiaDacBias(int32 tiaBiasI, int32 tiaBiasQ);
/****************************************************************************************
*Function name : rfPgaGainCal
*Description   : 
*Paramater	   :
*        @pga0ICal : PGA0I calibration gain 
*        @pga0QCal : PGA0Q calibration gain 
*        @pga1ICal : PGA1I calibration gain 
*        @pga1QCal : PGA1Q calibration gain 
*Paramater	selection:PGA_CAL_N1 0  //-1DB
                      PGA_CAL_N5 1  //-0.5DB
                      PGA_CAL_P1 2  //0.5DB
                      PGA_CAL_P5 3  //1DB
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfPgaGainCalEnable(int32 pga0ICalEnable, int32 pga0QCalEnable, int32 pga1ICalEnable, int32 pga1QCalEnable);
void rfPgaGainCalSetting(int32 pga0ICal, int32 pga0QCal, int32 pga1ICal, int32 pga1QCal);
/****************************************************************************************
*Function name : rfTiaEnable
*Description   : control pga enable
*Paramater	   :
*        @pga0Enable : enable VGA0
*        @pga1Enable : enable VGA1
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfVgaEnable(int32 vga0Enable, int32 vga1Enable);
/****************************************************************************************
*Function name : rfVgaGainSetting
*Description   : control tia gain setting
*Paramater	   :
*        @pga0IGain : TIA0I diff gain setting
*        @pga0QGain : TIA0Q diff gain setting
*        @pga1IGain : TIA1I diff gain setting
*        @pga1QGain : TIA1Q diff gain setting
*Paramater	selection: PGA_GAIN_0DB  PGA_GAIN_2DB  PGA_GAIN_4DB     PGA_GAIN_6DB 
                       PGA_GAIN_8DB  PGA_GAIN_10DB PGA_GAIN_12DB    PGA_GAIN_14DB
                       PGA_GAIN_16DB PGA_GAIN_18DB PGA_GAIN_19DB    PGA_GAIN_20DB
                       PGA_GAIN_22DB PGA_GAIN_24DB PGA_GAIN_26DB    PGA_GAIN_28DB
                       PGA_GAIN_30DB PGA_GAIN_32DB PGA_GAIN_34DB    PGA_GAIN_36DB PGA_GAIN_38DB
                       PGA_GAIN_40DB
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfVgaGainSetting(int32 vga0IGain, int32 vga0QGain, int32 vga1IGain, int32 vga1QGain);
/****************************************************************************************
*Function name : rfVgaDacBias
*Description   : control tia pga setting
*Paramater	   :
*        @pga0bias : TIA0I pga bias
*        @pga0bias : TIA0Q pga bias
*Paramater	selection:0~15
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfVgaDacBias(int32 pgaBiasI, int32 pgaBiasQ);
/**********************************************************************************************************
									HPF(Tia) LPF&HPF(Pga)
   TIA HP bypass        ->         HP RC           ->      PGA HP RC  
  25k, 50k, 100k, 300kHz       150k 400kHz            25k, 50k, 100k, 500kHz       

***********************************************************************************************************/
/****************************************************************************************
*Function name : tiaHpfConfig
*Description   : control hpf parameter
*Paramater	   :
*        @tia0HpfParameter : tia0 hpf
*        @tia1HpfParameter : tia1 hpf
*Paramater	selection:RC_HPF_150KHZ
                      RC_HPF_400KHZ
*Power consumption : No
*Return        : None
****************************************************************************************/
void tiaHpfConfig(int32 tia0HpfEnable, int32 tia1HpfEnable, int32 tia0HpfParameter, int32 tia1HpfParameter);
void rcHpfConfig(int32 rcHpf0Enable, int32 rcHpf1Enable, int32 rc0HpfParameter, int32 rc1HpfParameter);
/****************************************************************************************
*Function name : rfLpfConfig
*Description   : control lpf parameter
*Paramater	   :
*        @pga0LpfParameter : pga0 lpf
*        @pga1LpfParameter : pga1 lpf
*Paramater	selection:PGA_LPF_2M    PGA_LPF_4M
                      PGA_LPF_6M    PGA_LPF_8M
*Power consumption : No
*Return        : None
****************************************************************************************/
void pgaLpfConfig(int32 pga0LpfParameter, int32 pga1LpfParameter);
void pgaLpfCal(int32 lpf0CalEn, int32 lpf1CalEn, int32 lpf0CalConf, int32 lpf1CalConf);
/****************************************************************************************
*Function name : pgaHpfConfig
*Description   : control hpf parameter 
*Paramater	   :
*        @pga0LpfParameter : pga0 hpf
*        @pga1LpfParameter : pga1 hpf
*Paramater	selection:PGA_HPF_25KHZ    PGA_HPF_50KHZ
                      PGA_HPF_100KHZ   PGA_HPF_500KHZ
*Power consumption : No
*Return        : None
****************************************************************************************/
void pgaHpfConfig(int32 vga0HpfEnable, int32 vga1HpfEnable,int32 pga0HpfParameter, int32 pga1HpfParameter);
#endif



