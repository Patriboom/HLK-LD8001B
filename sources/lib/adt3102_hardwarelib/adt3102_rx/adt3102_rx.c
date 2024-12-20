//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  .Rx LNA
//  .TIA
//  .PGA(VGA)
//  .bias1 (enable bias1,dina,dinb,dinc)
//  .bias2 (enable bias2,dina,dinb,dinc)
//  .bist config
//  .atb
//  .spart
//  .AGC

//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/9
//--------------------------------------------------------------------
//
//All include header files
#include "adt3102_type_define.h"
#include "adt3102_rx.h"
#include "pmu_ctype_map.h"
#include "rfc_ctype_map.h"
#include "dsp_ctype_map.h"
//
//------Global variable declaration

/**********************************************************************************************************
									LNA	
***********************************************************************************************************/
/****************************************************************************************
*Function name : rxLnaEnable
*Description   : control rx lna enable
*register*RW*rfc_rx_lna_reg
[1]	 1'h0	lna1_en:LNA1 enable 
[0]	 1'h0	lna0_en:LNA0 enable 
*Paramater	   :
*        @lna0Enable : rx0 enable
*        @lna1Enable : rx0 enable
*
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rxLnaEnable(int32 lna0Enable, int32 lna1Enable)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_rx_lna_reg;
	if(lna0Enable == 1)
		regVel |= rfc_rx_lna_reg_lna0_en_bit;
	else
		regVel &= ~rfc_rx_lna_reg_lna0_en_bit;
	
	if(lna1Enable == 1)
		regVel |= rfc_rx_lna_reg_lna1_en_bit;
	else
		regVel &= ~rfc_rx_lna_reg_lna1_en_bit;	
    RFC->rfc_rx_lna_reg = regVel;
}
/****************************************************************************************
*Function name : mixerEnable
*Description   : control mixer enable
*register*RW*rfc_rx_lna_reg
[5:4]2'h0	mixer_reg:mixer enable, <0> for channel0 Mixer enable, <1> for channel1 Mixer enble 
*Paramater	   :
*        @ch0MixerEnable : channel0 Mixer enable
*        @ch1MixerEnable : channel1 Mixer enable
*
*Power consumption : No
*Return        : None
****************************************************************************************/
void mixerEnable(int32 ch0MixerEnable, int32 ch1MixerEnable)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_rx_lna_reg;
	if(ch0MixerEnable == 1)
		regVel |= 1<<4;
	else
		regVel &= ~(1<<4);

	if(ch1MixerEnable == 1)
		regVel |= 1<<5;
	else
		regVel &= ~(1<<5);		
    RFC->rfc_rx_lna_reg = regVel;
}
/****************************************************************************************
*Function name : lnaRegularBias
*Description   : control mixer enable
*register*RW*rfc_rx_lna_reg
[3:2]2'h0	lna_reg:regular bias mode, <0> for channel 0 LNA, <1> for channel 1 LNA 
*Paramater	   :
*        @ch0MixerEnable : channel0 Mixer enable
*        @ch1MixerEnable : channel1 Mixer enable
*
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void lnaRegularBias(int32 lna0bias, int32 lna1bias)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_rx_lna_reg;
	if(lna0bias == 1)
		regVel |= 1<<2;
	else
		regVel &= ~(1<<2);

	if(lna1bias == 1)
		regVel |= 1<<3;
	else
		regVel &= ~(1<<3);
    RFC->rfc_rx_lna_reg = regVel;
}
/****************************************************************************************
*Function name : lnaDacBias
*Description   : control dac lna bias
*
*register*RW*rfc_rx_lna_reg
[31:28]	4'h8	bias1_din7:DAC8 data, ch1, LNA bias3 
[27:24]	4'h8	bias1_din6:DAC7 data, ch1, LNA bias2 
[23:20]	4'h8	bias1_din5:DAC6 data, ch1, LNA bias1 
[19:16]	4'h8	bias1_din4:DAC5 data, ch0, LNA bias3 
[15:12]	4'h8	bias1_din3:DAC4 data, ch0, LNA bias2 
[11:8]	4'h8	bias1_din2:DAC3 data, ch0, LNA bias1 
*
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
void lnaDacBias(int32 ch0bias1, int32 ch0bias2, int32 ch0bias3, int32 ch1bias1, int32 ch1bias2, int32 ch1bias3)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_bias1_dina_reg;
	regVel &= ~(rfc_bias1_dina_reg_bias1_din2_mask<<rfc_bias1_dina_reg_bias1_din2_shift);
	regVel |= ch0bias1<<rfc_bias1_dina_reg_bias1_din2_shift;
	
	regVel &= ~(rfc_bias1_dina_reg_bias1_din3_mask<<rfc_bias1_dina_reg_bias1_din3_shift);
	regVel |= ch0bias2<<rfc_bias1_dina_reg_bias1_din3_shift;

	regVel &= ~(rfc_bias1_dina_reg_bias1_din4_mask<<rfc_bias1_dina_reg_bias1_din4_shift);
	regVel |= ch0bias3<<rfc_bias1_dina_reg_bias1_din4_shift;

	regVel &= ~(rfc_bias1_dina_reg_bias1_din5_mask<<rfc_bias1_dina_reg_bias1_din5_shift);
	regVel |= ch1bias1<<rfc_bias1_dina_reg_bias1_din5_shift;

	regVel &= ~(rfc_bias1_dina_reg_bias1_din6_mask<<rfc_bias1_dina_reg_bias1_din6_shift);
	regVel |= ch1bias2<<rfc_bias1_dina_reg_bias1_din6_shift;

	regVel &= ~((uint32)rfc_bias1_dina_reg_bias1_din7_mask<<rfc_bias1_dina_reg_bias1_din7_shift);
	regVel |= ch1bias3<<rfc_bias1_dina_reg_bias1_din7_shift;
    RFC->rfc_bias1_dina_reg = regVel;
}

/**********************************************************************************************************
									TIA
***********************************************************************************************************/
/****************************************************************************************
*Function name : rfTiaEnable
*Description   : control tia enable
*
*register*RW*rfc_tia0_cfg_reg
[12]	1'h0	tia0_en:1: enable TIA0 
*
*Paramater	   :
*        @tia0enable : enable TIA0
*        @tia1enable : enable TIA0
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfTiaEnable(int32 tia0Enable, int32 tia1Enable)
{
    if (tia0Enable == 1)
    {
       RFC->rfc_tia0_cfg_reg |= 1<<12; 
    }
    else
    {
       RFC->rfc_tia0_cfg_reg &= ~(0x1<<12);
    }

    if (tia1Enable == 1)
    {
       RFC->rfc_tia1_cfg_reg |= 1<<12;
    }
    else
    {
       RFC->rfc_tia1_cfg_reg &= ~(0x1<<12);
    } 
}
/****************************************************************************************
*Function name : rfTiaGainSetting
*Description   : control tia gain setting
*
*register*RW*rfc_tia0_cfg_reg
[11:10]	2'h2	tia0_q_gain:TIA diff gain setting, 0~18dB, 6dB/bit (AGC_VGA0[3:2]) 
[9:8]	2'h2	tia0_i_gain:TIA diff gain setting, 0~18dB, 6dB/bit (AGC_VGA0[1:0]) 
*
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
void rfTiaGainSetting(int32 tia0IGain, int32 tia0QGain, int32 tia1IGain, int32 tia1IQain)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_tia0_cfg_reg; 
    regVel &= ~(rfc_tia0_cfg_reg_tia0_i_gain_mask<<rfc_tia0_cfg_reg_tia0_i_gain_shift);
	regVel |= tia0IGain<<rfc_tia0_cfg_reg_tia0_i_gain_shift;
    
    regVel &= ~(rfc_tia0_cfg_reg_tia0_q_gain_mask<<rfc_tia0_cfg_reg_tia0_q_gain_shift);
	regVel |= tia0QGain<<rfc_tia0_cfg_reg_tia0_q_gain_shift;
    RFC->rfc_tia0_cfg_reg = regVel;
    
    regVel = 0;
    regVel = RFC->rfc_tia1_cfg_reg;
    regVel &= ~(rfc_tia1_cfg_reg_tia1_q_gain_mask<<rfc_tia1_cfg_reg_tia1_i_gain_shift);
	regVel |= tia1IGain<<rfc_tia1_cfg_reg_tia1_i_gain_shift;
                
    regVel &= ~(rfc_tia1_cfg_reg_tia1_q_gain_mask<<rfc_tia1_cfg_reg_tia1_q_gain_shift);
	regVel |= tia1IQain<<rfc_tia1_cfg_reg_tia1_q_gain_shift; 
    RFC->rfc_tia1_cfg_reg = regVel;
}
/****************************************************************************************
*Function name : rfTiaDacBias
*Description   : control tia bias setting
*
*register*RW*rf_bias2_dina_reg
[11:8]	4'h8	bias2_din2:DAC3 data, I channel, tia bias 
[3:0]	4'h8	bias2_din0:DAC1 data, Q channel, tia bias 
*
*Paramater	   :
*        @tia0bias : TIA0I tia bias 
*        @tia1bias : TIA0Q tia bias 
*Paramater	selection:0~15
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfTiaDacBias(int32 tiaBiasI, int32 tiaBiasQ)
{
    uint32 regVel = 0;
    regVel = RFC->rf_bias2_dina_reg;
    regVel &= ~(rf_bias2_dina_reg_bias2_din2_mask<<rf_bias2_dina_reg_bias2_din2_shift);
	regVel |= tiaBiasI<<rf_bias2_dina_reg_bias2_din2_shift;
    
    regVel &= ~rf_bias2_dina_reg_bias2_din0_mask;
	regVel |= tiaBiasQ;
    RFC->rf_bias2_dina_reg = regVel;
}

/**********************************************************************************************************
									PGA
***********************************************************************************************************/
/****************************************************************************************
*Function name : rfTiaEnable
*Description   : control pga enable
*
*register*RW*rfc_vga0_reg rfc_vga1_reg
[26]	1'h0	pga0_en:1: enable PGA0 
[26]	1'h0	pga1_en:1: enable PGA1 
*
*Paramater	   :
*        @pga0Enable : enable VGA0
*        @pga1Enable : enable VGA1
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfVgaEnable(int32 pga0Enable, int32 pga1Enable)
{
    if (pga0Enable == 1)
    {
        RFC->rfc_vga0_reg |= 1<<26;
    }
    else
    {
        RFC->rfc_vga0_reg &= ~(0x1<<26); 
    }

    if (pga1Enable == 1)
    {
        RFC->rfc_vga1_reg |= 1<<26;
    }
    else
    {
        RFC->rfc_vga1_reg &= ~(0x1<<26); 
    }    
}

/****************************************************************************************
*Function name : rfVgaGainSetting
*Description   : control tia gain setting
*
*register*RW*rfc_tia0_cfg_reg
[25:21]	5'h0	pga0_q_gain:PGA diff gain, 0~40dB, 2dB/bit (AGC_VGA0[13:9]) 
[20:16]	5'h0	pga0_i_gain:PGA diff gain, 0~40dB, 2dB/bit (AGC_VGA0[8:4])
*
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
void rfVgaGainSetting(int32 pga0IGain, int32 pga0QGain, int32 pga1IGain, int32 pga1QGain)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_vga0_reg;
    regVel &= ~(rfc_vga0_reg_pga0_i_gain_mask<<rfc_vga0_reg_pga0_i_gain_shift);
	regVel |= pga0IGain<<rfc_vga0_reg_pga0_i_gain_shift;
    
    regVel &= ~(rfc_vga0_reg_pga0_q_gain_mask<<rfc_vga0_reg_pga0_q_gain_shift);
	regVel |= pga0QGain<<rfc_vga0_reg_pga0_q_gain_shift; 
    RFC->rfc_vga0_reg = regVel;

    regVel = 0;
    regVel = RFC->rfc_vga1_reg;
    regVel &= ~(rfc_vga1_reg_pga1_i_gain_mask<<rfc_vga1_reg_pga1_i_gain_shift);
	regVel |= pga1IGain<<rfc_vga1_reg_pga1_i_gain_shift;
                
    regVel &= ~(rfc_vga1_reg_pga1_q_gain_mask<<rfc_vga1_reg_pga1_q_gain_shift);
	regVel |= pga1QGain<<rfc_vga1_reg_pga1_q_gain_shift; 
    RFC->rfc_vga1_reg = regVel;
}
/****************************************************************************************
*Function name : rfPgaGainCal
*Description   : 
*
*register*RW*rfc_tia0_cfg_reg 
[7:0]	8'h0	tia0_reg:
<0>: gain_cal_Q<1>: I/Q calibration gain range: -1~1dB, 0.5dB/bit. 
rfc_vga0_reg [15:8]<0>: gain_cal_Q<0>: work with TIA_REG<0>.
*
<1>: gain_cal_I<0>: . 
<2>: gain_cal_I<1>: I/Q calibration gain range: -1~1dB, 0.5dB/bit. 
*
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
void rfPgaGainCalEnable(int32 pga0ICalEnable, int32 pga0QCalEnable, 
                        int32 pga1ICalEnable, int32 pga1QCalEnable)
{
    /*RW
    <7:6>: PGA1_REG3<1:0>: . <5:4>: PGA0_REG3<1:0>:     //pga calibration gain enable 
    <3:2>: vblo_cal<3:2>: channel1, vbias for Mixer LO. //adjust TIA1 Gain uniformity(default)
    <1:0>: vblo_cal<1:0>: channel0, vbias for Mixer LO. //adjust TIA0 Gain uniformity(default)
    */
    uint32 regVel = 0;
    regVel = RFC->rf_bias1_en_reg;
    if (pga0ICalEnable == 1)
    {
        regVel |= 1<<4;
    }
    else
    {
        regVel &= ~(0x1<<4); 
    }  

    if (pga0QCalEnable == 1)
    {
        regVel |= 1<<5;
    }
    else
    {
        regVel &= ~(0x1<<5); 
    }  

    if (pga1ICalEnable == 1)
    {
        regVel |= 1<<6;
    }
    else
    {
        regVel &= ~(0x1<<6); 
    } 
    
    if (pga1QCalEnable == 1)
    {
        regVel |= 1<<7;
    }
    else
    {
        regVel &= ~(0x1<<7); 
    }  
    RFC->rf_bias1_en_reg = regVel;
}
void rfPgaGainCalSetting(int32 pga0ICal, int32 pga0QCal, int32 pga1ICal, int32 pga1QCal)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_tia0_cfg_reg;
    regVel &= ~(0x3<<1);
	regVel |= pga0ICal<<1;
    
    regVel &= ~(0x1<<0);
    regVel |= ((pga0QCal&0x02)>>1)<<0;
    RFC->rfc_tia0_cfg_reg = regVel;
    
    RFC->rfc_vga0_reg     &= ~(0x1<<8);
    RFC->rfc_vga0_reg     |= (pga0QCal&0x01)<<8;
    
    regVel = 0;
    regVel = RFC->rfc_tia1_cfg_reg;
	regVel &= ~(0x3<<1);
	regVel |= pga1ICal<<1;
                
    regVel &= ~(0x1<<0);
    regVel |= ((pga1QCal&0x02)>>1)<<0;
    RFC->rfc_tia1_cfg_reg = regVel;
    
    RFC->rfc_vga1_reg     &= ~(0x1<<8);
    RFC->rfc_vga1_reg     |= (pga1QCal&0x01)<<8;
}

/****************************************************************************************
*Function name : rfVgaDacBias
*Description   : control tia pga setting
*
*register*RW*rf_bias2_dina_reg
[15:12]	4'h8	bias2_din3:DAC4 data, I channel, pga bias  
[7:4]	4'h8	bias2_din1:DAC2 data, Q channel, pga bias
*
*Paramater	   :
*        @pga0bias : TIA0I pga bias
*        @pga0bias : TIA0Q pga bias
*Paramater	selection:0~15
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfVgaDacBias(int32 pgaBiasI, int32 pgaBiasQ)
{
    uint32 regVel = 0;
    regVel = RFC->rf_bias2_dina_reg;
    regVel &= ~(rf_bias2_dina_reg_bias2_din1_mask<<rf_bias2_dina_reg_bias2_din1_shift);
	regVel |= pgaBiasQ<<rf_bias2_dina_reg_bias2_din1_shift;
    
    regVel &= ~(rf_bias2_dina_reg_bias2_din3_mask<<rf_bias2_dina_reg_bias2_din3_shift);
	regVel |= pgaBiasI<<rf_bias2_dina_reg_bias2_din3_shift; 
    RFC->rf_bias2_dina_reg = regVel;
}

/**********************************************************************************************************
									HPF(Tia) LPF&HPF(Pga)
   TIA HP bypass        ->         HP RC           ->      PGA HP RC  
  25k, 50k, 100k, 300kHz       150k 400kHz            25k, 50k, 100k, 500kHz       

***********************************************************************************************************/
/****************************************************************************************
*Function name : tiaHpfConfig
*Description   : control hpf parameter
*
*register*RW*rfc_tia0_cfg_reg rfc_tia1_cfg_reg
<3>: hpf_fsel: 0: 150k, 1: 400kHz.(RC) 
<4>: hpf_bypass_mode: 0: HPF(RC), 1: bypass mode(from TIA to VGA). 
<5>: tia_dcos_fsel<0>: 00: 25k, 01: 50k, 10: 100k, 11: 300kHz. 
<6>: tia_dcos_fsel<1>: . 
<7>: tia_dcos_en: tia dc offset calibration enable, '0' disable. 
*
*Paramater	   :
*        @tia0HpfParameter : tia0 hpf
*        @tia1HpfParameter : tia1 hpf
*Paramater	selection:RC_HPF_150KHZ
                      RC_HPF_400KHZ
*Power consumption : No
*Return        : None
****************************************************************************************/
void rcHpfConfig(int32 rcHpf0Enable, int32 rcHpf1Enable, int32 rc0HpfParameter, int32 rc1HpfParameter)
{
    //select bypass mode
    uint32 regVel = 0;
    regVel = RFC->rfc_tia0_cfg_reg;
    if (rcHpf0Enable == 1)
    {
        regVel &= ~(1<<4); 
    }
    else
    {
        regVel |= 1<<4;
    } 
    regVel &= ~(0x1<<3);
    if(rc0HpfParameter==150)
        regVel |= 0<<3;
    else
        regVel |= 1<<3;
    RFC->rfc_tia0_cfg_reg = regVel;
    
    //select bypass mode
    regVel = 0;
    regVel = RFC->rfc_tia1_cfg_reg;
    if (rcHpf1Enable == 1)
    {
        regVel &= ~(1<<4); 
    }
    else
    {
        regVel |= 1<<4;
    } 
 
    regVel &= ~(0x1<<3);
    if(rc1HpfParameter==150)
        regVel |= 0<<3;
    else
        regVel |= 1<<3;
    RFC->rfc_tia1_cfg_reg = regVel;

}
void tiaHpfConfig(int32 tia0HpfEnable, int32 tia1HpfEnable, int32 tia0HpfParameter, int32 tia1HpfParameter)
{
    //select rc mode
    uint32 regVel = 0;
    regVel = RFC->rfc_tia0_cfg_reg;
    if (tia0HpfEnable == 1)
    {
        regVel |= 1<<7;
    }
    else
    {
        regVel &= ~(1<<7); 
    } 
    regVel &= ~(0x3<<5);
    regVel |= tia0HpfParameter<<5;
    RFC->rfc_tia0_cfg_reg = regVel;
    
    //select rc mode
    regVel = 0;
    regVel = RFC->rfc_tia1_cfg_reg;
    if (tia1HpfEnable == 1)
    {
        regVel |= 1<<7;
    }
    else
    {
        regVel &= ~(1<<7); 
    } 
    regVel &= ~(0x3<<5);
    regVel |= tia1HpfParameter<<5;
    RFC->rfc_tia1_cfg_reg = regVel;
}
/****************************************************************************************
*Function name : rfLpfConfig
*Description   : control lpf parameter
*
*register*RW*rfc_tia0_cfg_reg rfc_tia0_cfg_reg 
<3>: lpf_fsel<0>: 00: 2M, 01: 4M, 10: 6M,, 11: 8MHz. 
<4>: lpf_fsel<1>: . 
<7>: pga_dcos_en: pga dc offset calibration enable, '0' disable.  
*
*Paramater	   :
*        @pga0LpfParameter : pga0 lpf
*        @pga1LpfParameter : pga1 lpf
*Paramater	selection:PGA_LPF_2M    PGA_LPF_4M
                      PGA_LPF_6M    PGA_LPF_8M
*Power consumption : No
*Return        : None
****************************************************************************************/
void pgaLpfConfig(int32 pga0LpfParameter, int32 pga1LpfParameter)
{
    RFC->rfc_vga0_reg &= ~(0x3<<3);  
    RFC->rfc_vga0_reg |= pga0LpfParameter<<3;
    
    RFC->rfc_vga1_reg &= ~(0x3<<3);  
    RFC->rfc_vga1_reg |= pga1LpfParameter<<3;
}
void pgaLpfCal(int32 lpf0CalEn, int32 lpf1CalEn, int32 lpf0CalConf, int32 lpf1CalConf)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_vga0_reg;
    if (lpf0CalEn==1)
    {
        regVel |= 1<<2;
    }else {
        regVel &= ~(1<<2);
    }
    regVel &= ~(0x3<<14);
    regVel |= lpf0CalConf<<14;
    RFC->rfc_vga0_reg = regVel;
    
    regVel = 0;
    regVel = RFC->rfc_vga1_reg;
    if (lpf1CalEn==1)
    {
        regVel |= 1<<2;
    }else {
        regVel &= ~(1<<2);
    }
    regVel &= ~(0x3<<14);
    regVel |= lpf1CalConf<<14;
    RFC->rfc_vga1_reg = regVel;
}
/****************************************************************************************
*Function name : pgaHpfConfig
*Description   : control hpf parameter 
*
*register*RW*rfc_tia0_cfg_reg rfc_tia0_cfg_reg 
<5>: pga_dcos_fsel<0>: 00: 25k, 01: 50k, 10: 100k, 11: 500kHz. 
<6>: pga_dcos_fsel<1>: .
<7>: pga_dcos_en: pga dc offset calibration enable, '0' disable.  
*
*Paramater	   :
*        @pga0LpfParameter : pga0 hpf
*        @pga1LpfParameter : pga1 hpf
*Paramater	selection:PGA_HPF_25KHZ    PGA_HPF_50KHZ
                      PGA_HPF_100KHZ   PGA_HPF_500KHZ
*Power consumption : No
*Return        : None
****************************************************************************************/
void pgaHpfConfig(int32 pga0HpfEnable, int32 pga1HpfEnable,int32 pga0HpfParameter, int32 pga1HpfParameter)
{
    
    //dc offset
    RFC->rfc_vga0_reg &= ~(1<<7);
    RFC->rfc_vga0_reg |= pga0HpfEnable<<7;
    
    RFC->rfc_vga1_reg &= ~(1<<7);
    RFC->rfc_vga1_reg |= pga1HpfEnable<<7;
    
    
    RFC->rfc_vga0_reg &= ~(0x3<<5);  
    RFC->rfc_vga0_reg |= pga0HpfParameter<<5;
    
    RFC->rfc_vga1_reg &= ~(0x3<<5);  
    RFC->rfc_vga1_reg |= pga1HpfParameter<<5;
}

//void rxAgcconfig()
//{
//    DSP->agc_gain_tb_ch0_0 = ;
//    DSP->agc_gain_tb_ch0_1 = ;    
//    DSP->agc_gain_tb_ch0_2 = ;
//    DSP->agc_gain_tb_ch0_3 = ;
//    DSP->agc_gain_tb_ch0_4 = ;
//    DSP->agc_gain_tb_ch0_5 = ;
//    DSP->agc_gain_tb_ch0_6 = ;
//    DSP->agc_gain_tb_ch0_7 = ;
//    DSP->agc_gain_tb_ch0_8 = ;
//    DSP->agc_gain_tb_ch0_9 = ;
//    DSP->agc_gain_tb_ch0_10 = ;
//    DSP->agc_gain_tb_ch0_11 = ;
//    DSP->agc_gain_tb_ch0_12 = ;
//    DSP->agc_gain_tb_ch0_13 = ;
//    DSP->agc_gain_tb_ch0_14 = ;
//    DSP->agc_gain_tb_ch0_15 = ;
//    DSP->agc_gain_tb_ch0_16 = ;
//    DSP->agc_gain_tb_ch0_17 = ;
//    DSP->agc_gain_tb_ch0_18 = ;
//    DSP->agc_gain_tb_ch0_19 = ;
//    DSP->agc_gain_tb_ch0_20 = ;
//    DSP->agc_gain_tb_ch0_21 = ;
//    DSP->agc_gain_tb_ch0_22 = ;
//    DSP->agc_gain_tb_ch0_23 = ;
//    DSP->agc_gain_tb_ch0_24 = ;
//    DSP->agc_gain_tb_ch0_25 = ;
//    DSP->agc_gain_tb_ch0_26 = ;
//    DSP->agc_gain_tb_ch0_27 = ;
//    DSP->agc_gain_tb_ch0_28 = ;
//    DSP->agc_gain_tb_ch0_29 = ;
//    DSP->agc_gain_tb_ch0_30 = ;
//    DSP->agc_gain_tb_ch0_31 = ;
//    DSP->agc_gain_tb_ch0_32 = ;
//    DSP->agc_gain_tb_ch0_33 = ;
//    DSP->agc_gain_tb_ch0_34 = ;
//    DSP->agc_gain_tb_ch0_35 = ;
//    DSP->agc_gain_tb_ch0_36 = ;
//    DSP->agc_gain_tb_ch0_37 = ;
//    DSP->agc_gain_tb_ch0_38 = ;
//    DSP->agc_gain_tb_ch0_39 = ;
//    DSP->agc_gain_tb_ch0_40 = ;
//    DSP->agc_gain_tb_ch0_41 = ;
//    DSP->agc_gain_tb_ch0_42 = ;
//    DSP->agc_gain_tb_ch0_43 = ;
//    DSP->agc_gain_tb_ch0_44 = ;
//    DSP->agc_gain_tb_ch0_45 = ;
//    DSP->agc_gain_tb_ch0_46 = ;
//    DSP->agc_gain_tb_ch0_47 = ;
//    DSP->agc_lna_gain_tb_ch0_0 = ;
//    DSP->agc_lna_gain_tb_ch0_1 = ;
//    DSP->agc_lna_gain_tb_ch0_2 = ;
//    DSP->agc_lna_gain_tb_ch0_3 = ;
//    DSP->agc_lna_gain_tb_ch0_4 = ;
//    DSP->agc_lna_gain_tb_ch0_5 = ;
//    DSP->agc_lna_gain_tb_ch0_6 = ;
//    DSP->agc_lna_gain_tb_ch0_7 = ;
//    DSP->agc_gain_tb_ch1_0 = ;
//    DSP->agc_gain_tb_ch1_1 = ;
//    DSP->agc_gain_tb_ch1_2 = ;
//    DSP->agc_gain_tb_ch1_3 = ;
//    DSP->agc_gain_tb_ch1_4 = ;
//    DSP->agc_gain_tb_ch1_5 = ;
//    DSP->agc_gain_tb_ch1_6 = ;
//    DSP->agc_gain_tb_ch1_7 = ;
//    DSP->agc_gain_tb_ch1_8 = ;
//    DSP->agc_gain_tb_ch1_9 = ;
//    DSP->agc_gain_tb_ch1_10 = ;
//    DSP->agc_gain_tb_ch1_11 = ;
//    DSP->agc_gain_tb_ch1_12 = ;
//    DSP->agc_gain_tb_ch1_13 = ;
//    DSP->agc_gain_tb_ch1_14 = ;
//    DSP->agc_gain_tb_ch1_15 = ;
//    DSP->agc_gain_tb_ch1_16 = ;
//    DSP->agc_gain_tb_ch1_17 = ;
//    DSP->agc_gain_tb_ch1_18 = ;
//    DSP->agc_gain_tb_ch1_19 = ;
//    DSP->agc_gain_tb_ch1_20 = ;
//    DSP->agc_gain_tb_ch1_21 = ;
//    DSP->agc_gain_tb_ch1_22 = ;
//    DSP->agc_gain_tb_ch1_23 = ;
//    DSP->agc_gain_tb_ch1_24 = ;
//    DSP->agc_gain_tb_ch1_25 = ;
//    DSP->agc_gain_tb_ch1_26 = ;
//    DSP->agc_gain_tb_ch1_27 = ;
//    DSP->agc_gain_tb_ch1_28 = ;
//    DSP->agc_gain_tb_ch1_29 = ;
//    DSP->agc_gain_tb_ch1_30 = ;
//    DSP->agc_gain_tb_ch1_31 = ;
//    DSP->agc_gain_tb_ch1_32 = ;
//    DSP->agc_gain_tb_ch1_33 = ;
//    DSP->agc_gain_tb_ch1_34 = ;
//    DSP->agc_gain_tb_ch1_35 = ;
//    DSP->agc_gain_tb_ch1_36 = ;
//    DSP->agc_gain_tb_ch1_37 = ;
//    DSP->agc_gain_tb_ch1_38 = ;
//    DSP->agc_gain_tb_ch1_39 = ;
//    DSP->agc_gain_tb_ch1_40 = ;
//    DSP->agc_gain_tb_ch1_41 = ;
//    DSP->agc_gain_tb_ch1_42 = ;
//    DSP->agc_gain_tb_ch1_43 = ;
//    DSP->agc_gain_tb_ch1_44 = ;
//    DSP->agc_gain_tb_ch1_45 = ;
//    DSP->agc_gain_tb_ch1_46 = ;
//    DSP->agc_gain_tb_ch1_47 = ;
//    DSP->agc_lna_gain_tb_ch1_0 = ;
//    DSP->agc_lna_gain_tb_ch1_1 = ;
//    DSP->agc_lna_gain_tb_ch1_2 = ;
//    DSP->agc_lna_gain_tb_ch1_3 = ;
//    DSP->agc_lna_gain_tb_ch1_4 = ;
//    DSP->agc_lna_gain_tb_ch1_5 = ;
//    DSP->agc_lna_gain_tb_ch1_6 = ;
//    DSP->agc_lna_gain_tb_ch1_7 = ;

//}




