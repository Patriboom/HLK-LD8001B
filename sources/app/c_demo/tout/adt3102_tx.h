#ifndef __TX_H
#define __TX_H

#include "adt3102_type_define.h"
/***Macro Definition*********************************************************************
MODE_INTER    : 20G to internal doubler
MODE_EXTERN   : 20G from external source
MODE_CASCADED : 20G to internal doubler and output other chip
MODE_TEST     : 20G output test port
****************************************************************************************/
#define MODE_INTER      00
#define MODE_EXTERN     01
#define MODE_CASCADED   10
#define MODE_TEST       11
/***Macro Definition*********************************************************************
POWER_ON : power on 0 valid
POWER_DOWN : power down 1 valid
****************************************************************************************/
#define POWER_ON    0
#define POWER_DOWN  1
/***Macro Definition*********************************************************************
BB_LDO_xPy :set baseband ldo voltage x.yv
****************************************************************************************/
#define BB_LDO_1P8  0
#define BB_LDO_2P0  1
#define BB_LDO_2P2  2
#define BB_LDO_2P5  3
/***Macro Definition*********************************************************************
DVDDxPy_HP :set VDD ldo voltage x.yv
****************************************************************************************/
#define DVDD1P2_HP  0
#define DVDD1P1_HP  1
#define DVDD1P3_HP  2
#define DVDD1P4_HP  3
/***Macro Definition*********************************************************************
DVDD_LP :set VDD ldo voltage
****************************************************************************************/
#define DVDD1P2_LP  0
#define DVDD0P7_LP  1
#define DVDD0P75_LP 2
#define DVDD0P8_LP  3
#define DVDD0P85_LP 4
#define DVDD1P0_LP  5
#define DVDD1P1_LP  6
#define DVDD1P3_LP  7
/***Macro Definition*********************************************************************
PLLN_VCO_LDO_xPy : set PLLN VCO LDO voltage x.yv
****************************************************************************************/
#define PLLN_VCO_LDO_1P8    0
#define PLLN_VCO_LDO_2P0    1
#define PLLN_VCO_LDO_2P2    2
#define PLLN_VCO_LDO_2P5    3
/***Macro Definition*********************************************************************
PLLN_PLL_LDO_xPy : set PLLN PLL LDO voltage x.yv
****************************************************************************************/
#define PLLN_PLL_LDO_1P8    0
#define PLLN_PLL_LDO_2P0    1
#define PLLN_PLL_LDO_2P2    2
#define PLLN_PLL_LDO_2P5    3
/***Macro Definition*********************************************************************
DATA_SAMPLE_MODULE : fmcw_en select from data_sample module
REGISTER : fmcw_en select from register
****************************************************************************************/
#define DATA_SAMPLE_MODULE 1
#define REGISTER           0
/***Macro Definition*********************************************************************
SINGLE_MODE : chirp_single_mode is single mode
CONTINUE_MODE : chirp_single_mode is continue mode
****************************************************************************************/
#define SINGLE_MODE   1
#define CONTINUE_MODE 0
/***Macro Definition*********************************************************************
PAx_ENABLE :  pax enable
PAx_DISABLE : pax disable
****************************************************************************************/
#define PA0_ENABLE  1
#define PA0_DISABLE 0
#define PA1_ENABLE  1
#define PA1_DISABLE 0
/***Macro Definition*********************************************************************
TEMPxUA :kc_bottom<1:0>: Mini bias setting@temp<-20c,'00' 20uA, '01' 30uA,'10' 40u,'11' 50uA.
****************************************************************************************/
#define TEMP20UA    0
#define TEMP30UA    1
#define TEMP40UA    2
#define TEMP50UA    3
/***Macro Definition*********************************************************************
KC1_XxPT :kc1_reg: bias0~11 temp coefficient control, '000' 1x PT current rate, '111' 3x PT rate.
****************************************************************************************/
#define KC1_X1PT    0
#define KC1_X3PT    7
/***Macro Definition*********************************************************************
KC2_XxPT :kc2_reg: bias12~23 temp coefficient control, '000' 1x PT current rate, '111' 3x PT rate.
****************************************************************************************/
#define KC2_X1PT    0
#define KC2_X3PT    7
/****************************************************************************************
*Function name : plliLDOconfig
*Description   : plli vco Ldo setting, plli pll vco ldo is enable default, cloes through FSM
*Paramater	   :
*        @plliVcoLdoEnable : plli Vco Ldo Enable
*        @plliPllLdoEnable : plli Pll Ldo Enable
*Paramater	selection:
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void plliLDOEnable(int32 plliVcoLdoEnable, int32 plliPllLdoEnable);
void plliDacSetting(void);
void plliConfig(int32 plliVcoEn);
/****************************************************************************************
*Function name : pllnVcoConfig
*Description   : plln vco config
*Paramater	   :
*        @pllnVcoLdoEnable:  enable VCO LDO
*        @pllnVcoLdo      :  adjust avdd_VCO for PLL VCO
*Paramater	selection:		PLLN_VCO_LDO_1P8     PLLN_VCO_LDO_2P2
                            PLLN_VCO_LDO_2P0     PLLN_VCO_LDO_2P5
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void pllnVcoConfig(int32 pllnVcoLdoEnable, int32 pllnVcoLdo);
/****************************************************************************************
*Function name : pllnPllConfig
*Description   : plln pll config
*Paramater	   :
*        @pllnPllLdoEnable:  enable PLLN LDO
*        @pllnPllLdo      :  adjust avdd for PLLN
*Paramater	selection:		PLLN_VCO_LDO_1P8     PLLN_VCO_LDO_2P2
                            PLLN_VCO_LDO_2P0     PLLN_VCO_LDO_2P5
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void pllnPllConfig(int32 pllnPllLdoEnable, int32 pllnPllLdo, int32 pllnEnBias);
void pllnDacSetting(void);
void pllnConfig(int32 vcoEn);
void pllnVcoEnable(int32 vcoEn);
/****************************************************************************************
*Function name : baseband18LDO
*Description   : adjust LDO output, '00' 1.8v, '01' 2v, '10' 2.2v, '11' 2.5v.
*Paramater	   :
*        @bb1Enable :baseband1 ldo enable, 
*        @bb1Adjust :adjust baseband1 LDO output
*        @bb2Enable :baseband2 ldo enable, 
*        @bb2Adjust :adjust baseband2 LDO output
*Paramater	selection:
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void baseband18LDO(int32 bb1Enable, int32 bb1Adjust, int32 bb2Enable, int32 bb2Adjust);
/****************************************************************************************
*Function name : dvdd12HpLDO
*Description   :Adjust the out of the LDO_1p2_HP, '00' 1.2v, '01' 1.1v, '10' 1.3v, '11' 1.4v
*Paramater	   :
*        @ powerOnDown: usually we do not turn off vdd
*        @ dvdd12Adjust:Adjust the out of the LDO_1p2_HP
*Paramater	selection:	POWER_ON 		DVDD1P2_HP DVDD1P3_HP
                        POWER_OFF   	DVDD1P1_HP DVDD1P4_HP
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void dvdd12HpLDO(int32 powerOnDown, int32 dvdd12Adjust);
void dvdd12LpLDO(int32 powerOnDown, int32 dvdd12Adjust);
/****************************************************************************************
*Function name : fmcwModeSel
*Description   : o_reg:FMCW buffer mode
*register*RW*rf_buf20g_db_reg
*Paramater	   :
*        @fmcwMode :  00': int32 mode, '01' external mode, '10' cascaded mode, '11' test mode
*        @ :
*Paramater	selection:	MODE_INTER    : 20G to internal doubler
						MODE_EXTERN   : 20G from external source
						MODE_CASCADED : 20G to internal doubler and output other chip
						MODE_TEST     : 20G output test port
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void fmcwModeSel(int32 fmcwMode);
/****************************************************************************************
*Function name : rfbuff20G
*Description   : 20G buffer and doubler enable
*Paramater	   :
*        @buffer20gEn :20G buffer enable
*        @doublerEn   :doubler enable
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfbuff20G(int32 buffer20gEn, int32 doublerEn);
/****************************************************************************************
*Function name : rfbuff20G
*Description   : about 80G buffer dac enable
*Paramater	   :
*        @biasdb77G    : ib_db77
*        @biasBuff38   : ib_buf38
*        @biasDb38     : ib_db38
*        @bias2Buff20G : 20G buf bias2
*        @biasbuff20G  : 20G buf
*        @txBuff1To4   : buf_1to4, tx loop
*        @loBuff1To4   : buf_1to4, lo loop
*        @rxBuff1To4   : buf_1to4, rx loop
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void bias20GTo80G(int32 biasdb77G, int32 biasBuff38, int32 biasDb38, int32 bias2Buff20G, 
				  int32 biasbuff20G, int32 txBuff1To4, int32 loBuff1To4, int32 rxBuff1To4);
/****************************************************************************************
*Function name : dacEnBias1Pd
*Description   : enable for dac<9:24> and bias1 power down, '0' enable, '1' disable.
*Paramater	   :
*        @dacEnable :  enable for dac<9:24>
*        @Bias1PowerDown :  bias1 power down, '0' enable, '1' disable.
*Paramater	selection:		

*Power consumption : 
*Return        :
****************************************************************************************/
void dacEnBias1Pd(int32 dacEnable, int32 Bias1PowerDown);
void biasPowerdector(int32 biasPowerDector);
/****************************************************************************************
*Function name :biasBist 
*Description   :bist bias setting
*Paramater	   :
*        @biasBistIptat0 : bias1_din18:DAC18, bist IPTAT<1> 
*        @biasBistIptat1 : bias1_din17:DAC17, bist IPTAT<0>  
*        @biasBist0 :  bias2_din18:DAC15 data, Bist bias<1>
*        @biasBist1 :  bias2_din17:DAC14 data, Bist bias<0>
*Paramater	selection:		

*Power consumption : 
*Return        :
****************************************************************************************/
void biasBist(int32 biasBistIptat0, int32 biasBistIptat1, int32 biasBist0, int32 biasBist1);
void biasGpadc(int32 gpadcBias1test, int32 gpadcBias2test, int32 gpadcBias);
/****************************************************************************************
*Function name : rfBuff77GEnable
*Description   :77G buffer enable
*Paramater	   :
*        @stage1Buff77G  : 77G buffer 1st stage enable
*        @tx0BufferEn77G : tx0 buffer enable
*        @tx1BufferEn77G : tx1 buffer enable
*        @rx0BufferEn77G : rx0 buffer enable
*        @rx1BufferEn77G : rx1 buffer enable
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfBuff77GEnable(int32 stage1Buff77G, int32 tx0BufferEn77G, int32 tx1BufferEn77G,
					 int32 rx0BufferEn77G, int32 rx1BufferEn77G);
/****************************************************************************************
*Function name : txPaEnable
*Description   : control pa enable
*Paramater	   :
*        @pa0Enable : channel0 DAC bias1
*        @pa1Enable : channel0 DAC bias2
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void txPaEnable(int32 pa0Enable, int32 pa1Enable);
/****************************************************************************************
*Function name : txPaBias
*Description   : control dac pa bias
*Paramater	   :
*        @pa0Bias : channel0 PA bias1
*        @pa1Bias : channel0 PA bias2
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void txPaBias(int32 pa0Bias, int32 pa1Bias);
/****************************************************************************************
*Function name : rfPhaseShift
*Description   : phase shifter data setting
*Paramater	   :
*        @ps_ip :  phase shifter i posedge
*        @ps_in :  phase shifter i negedge 
*        @ps_qp :  phase shifter q posedge 
*        @ps_qn :  phase shifter q negedge  
*Paramater	selection:		
*Power consumption : 
*Return        :
****************************************************************************************/
void rfPhaseShift(int32 ps_ip, int32 ps_in, int32 ps_qp, int32 ps_qn);
void rfPhaseShiftLUT(int32 ch0_idx, int32 ch1_idx);
/****************************************************************************************
*Function name : plliLock
*Description   : adjust plli vco switch, lock plli at 1G.
*Paramater	   : None
*Power consumption : No
*Return        : None
****************************************************************************************/
void plliLock(void);
/****************************************************************************************
*
*Function name : fmcwChirpSetting
*Description   :
*Paramater	   : The following is the parameter configuaration of vco output(sweep wave)
																												_
     ��                /|\                    /|\        |            /|\
     |               / | \                  / | \       |           / | \
     |              /  |  \                /  |  \      |          /  |  \
     |     	       /   |   \      		  /   |   \    FM         /   |   \
     |     	      /    |    \     	     /    |    \    |        /    |    \
     |     	     /     |     \     		/     |     \   |       /     |     \
     |          /      |      \        /      |      \  |      /      |      \
     |[fstart] /       |       \      /       |       \ |     /       |       \
_____|________/________|________\____/________|________\|____/________|________\
     |        [  t0    ][  t1   ][t2][  t0    ][   t1   ][t2]
     |		  [    Chirp1 cycle     ][    Chirp2 cycle  ]
     |
*					@fstart       : GHz  start frequence
*					@fm			  : MHz  bandwidth
*					@num_step     :
*					@t0           : us   chir p0 rise time
*					@t1           : us   chirp1 rise time
*					@t2           : us   chirp1 rise time
*					@chirpNumber  : FMCW chirp number TX (Chirp1 cycle,Chirp2 cycle......)
Note : 1,t1+t2+T3 = n*(120ns)
       2,single frequency mode setting: FM=0;
	   3,t1<500us,t2>10us
*Return        : None
****************************************************************************************/
void fmcwConfig(float fstart,uint32 fm,uint32 t0,uint32 t1,uint32 t2,uint32 chirpNumber);
/****************************************************************************************
*
*Function name : fmcwChirpSetting for dual saw.
*Description   :
*Paramater	   : The following is the parameter configuaration of vco output(sweep wave)
                             fmSaw0                                              fmSaw0                                                                               _
     ?                        /|\                                                 /|\                                
     |                      /  | \            fmSaw1             |              /  | \            fmSaw1             
     |                    /    |  \            /|\               |            /    |  \            /|\               
     |                  /      |   \          / | \              |          /      |   \          / | \              
     |                /        |    \        /  |  \             |        /        |    \        /  |  \             
     |              /          |     \      /   |   \            |      /          |     \      /   |   \            
     |            /            |      \    /    |    \           |    /            |      \    /    |    \           
     |[fstart]  /              |       \  /     |     \          |  /              |       \  /     |     \          
_____|________/________________|________\/______|______\_________|/________________|________\/______|______\_________
     |        [    t0Saw0      ][t1Saw0 ][t0Saw1][t1Saw1][  t2  ]|
     |        [    Chirp1 cycle                                 ][    Chirp1 cycle                                 ]
     |                                                           |
*    @fstart       : GHz  start frequence
*    @fm           : MHz  bandwidth
*    @num_step     :
*    @t0Saw0       : us   saw0 rise time
*    @t1Saw0       : us   saw0 fall time  
*    @t0Saw1       : us   saw1 rise time
*    @t1Saw1       : us   saw1 fall time
*    @t2           : us   reset time
*    @chirpNumber  : FMCW chirp number TX (Chirp1 cycle,Chirp2 cycle......)
Note :        
      1. (t0Saw0, t1Saw0, t0Saw1, t1Saw1, t2)*1000  MUST be c8's integer multiple. 
      2. chirp's slope more than 1mhz/1us. 
      3. t0Saw0, t1Saw0, t0Saw0, t1Saw0, t2, each of them should < 1ms.  so we can assume all channel's dt=1, that means 8ns. 
         why there is "1ms"?  Because our maximum step number is 2^17-1, and every step is assumed as 8ns, so (2^17-1)*8ns = 1ms approximately. 
      4. Assume t0Saw0 > 0. 
      5. if t0Saw1=0, then t1Saw1 will be ignored.   
      6. t0Saw0+t1Saw0+t0Saw1+t1Saw1+t2 = n*(120ns), to align adc sampling. 
      7. single frequency mode setting: FM=0;     
*Return        : None
****************************************************************************************/
void fmcwConfig_dualSaw(float fstart,uint32 fmSaw0,uint32 t0Saw0,uint32 t1Saw0,uint32 fmSaw1,uint32 t0Saw1,uint32 t1Saw1,uint32 t2,uint32 chirpNumber);
/****************************************************************************************
*Function name : fmcwEnmode
*Description   : fmcw enable mode
*Paramater	   :
*        @startMode :fmcw_en select. 1'h1: from data_sample module. 1'h0: from register.
*        @chirpMode :Chirp mode. 1 : single mode. 0 : continue mode
*Paramater	selection:		

*Power consumption : 
*Return        :
****************************************************************************************/
void fmcwEnmode(int32 startMode, int32 chirpMode);
void waitFmcwcycEnd(void);
/****************************************************************************************
*Function name : temperatureCompensation
*Description   : temperature compensation
*Paramater	   :
*        @miniBais :  
*        @kc1Reg :   
*        @kc2Reg :  
*Paramater	selection:		

*Power consumption : 
*Return        :
****************************************************************************************/
void temperatureCompensation(uint32 miniBais, uint32 kc1Reg, uint32 kc2Reg);
void tdMimo(uint32 t0,uint32 t1,uint32 t2);
#endif















