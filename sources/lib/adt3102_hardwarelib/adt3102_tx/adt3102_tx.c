//--------------------------------------------------------------------
//Copyright(c)2020,Andar Technologise Inc.
//All Rights Reserved
//Confidential Property of Andar Technologies Inc.
//
//Module Description:
//  .PLLI
//  .PLLN
//  .LDO(1.2v 1.8v )
//  .Buff20G
//  .Buff77G
//  .Tx PA
//  .Phase shift
//  .
//Created by :wuhao
//$Revision: 1.0
//$Data: 2020/11/9
//--------------------------------------------------------------------
//
//All include header files
#include "math.h"
#include "adt3102.h"
#include "adt3102_system.h"
#include "adt3102_type_define.h"
#include "adt3102_tx.h"
#include "pmu_ctype_map.h"
#include "rfc_ctype_map.h"
#include "stdio.h"
#include "arm_math.h"
//
//------Global variable declaration


/************************************************************************************************
                                                PLLI
*************************************************************************************************/
/****************************************************************************************
*Function name : plliLDOconfig
*Description   : plli vco Ldo setting, plli pll vco ldo is enable default, cloes through FSM
*register*RW*rf_plli_ldo_cfg_reg
[11:8]	4'h4	plli_bias_reg1:
<2:0>: plli_ibias_ztc_sel<2:0>: V-to-I output current selection, '0' *1.8, '1' *1.55, '2' *1.325, '3' *1.15, '4' *1(default), '5' *0.9, '6' *0.825, '7' *0.75.
<3>: ibias_insel: 0: Select V-to-I biasing from BG_1P8, 1: V-to-I biasing is generated internally.
[7:0]	8'h0	plli_ldo_reg1:
<1:0>: ldovco_out<1:0>: LDO_VCO output selection,00: 1.8V, 01: 2.0V, 10: 2.2V, 11: 2.5V.
<2>: en_ldovco_fbc: 1: Enable diode-connected MOS feedback.
<3>: : .
<5:4>: ldopll_out<1:0>: LDO_PLL output selection,00: 1.8V, 01: 1.5V, 10: 2.2V, 11: 2.5V.
<6>: en_ldopll_fbc: 1: Enable diode-connected MOS feedback.
<7>: : .
*Paramater	   :
*        @plliVcoLdoEnable : plli Vco Ldo Enable
*        @plliPllLdoEnable : plli Pll Ldo Enable
*Paramater	selection:
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void plliLDOEnable(int32 plliVcoLdoEnable, int32 plliPllLdoEnable)
{
    uint32 regVel = 0;
    //xo_core_bias=15 config. From Yuan. 2021.3.12.
    RFC->rfc_xo50m_cfg_reg = 0x000008F8;
	
#ifdef DISABLE_LOW_NOISE
    // Disable bit4:low noise function, especially for hare_switch project. 
    // Because this bit will spend about 30ms for avdd18_plli to become stable. From XX. 
    RFC->rfc_ldo_bg_reg_reg = 0x00000200 ;
#else
    RFC->rfc_ldo_bg_reg_reg = 0x00000210 ;	
#endif
	
	  // there is a manu_ctrl_en=1 at the end of this function. 
    //PMU->pmu_pmu_ctrl_reg |= pmu_pmu_ctrl_reg_manu_ctrl_en_bit;
    //delayUs(100,HIGH_CLOCK);
    //PMU->pmu_pmu_ctrl_reg &= ~pmu_pmu_ctrl_reg_manu_ctrl_en_bit;
	
    /*rw
    <6>: en_ldopll_fbc: 1: Enable diode-connected MOS feedback.
    */
    //plli default setting 1.8v

    //regVel |= RFC->rf_plli_ldo_cfg_reg;
    //RFC->rf_plli_ldo_cfg_reg = regVel;

    /*rw
    [12]	1'h0	plli_en_ldovco:1: Enable PLL-I VCO LDO
    [11]	1'h1	plli_en_ldopll:1: Enable PLL-I PLL LDO
    [10]	1'h1	plli_en_bias:1: Enable PLL-I Iztc bias
    [9]	1'h0	plli_en_pll:1: Enable PLL-I blocks
    [8]	1'h0	plli_en_ckdig_125m:1: Enable 125M clk output to digital
    [7]	1'h1	xo50m_en:1: Enable of 50MHz crystal oscillator block
    [6]	1'h0	xo50m_mode:0: Internal crystal oscillator mode, 1: External clock mode
    [5]	1'h1	xo50m_en_ckdig:1: Enable 50MHz clk output to digital
    [4]	1'h0	xo50m_en_ckpll:1: Enable 50M clk output to PLL-I
    [3]	1'h0	xo50m_en_refclk_out:1: Enable 50MHz ref clk output to slave chips in multi-chip cascading
    [2]	1'h0	xo50m_en_ckbist:1: Enable 50MHz clk output to BIST
    [1]	1'h0	plli_en_ckplln:1: Enable 250MHz output to PLLN
    [0]	1'h0	plli_en_ckadc:1: Enable clk output to ADC
    */    

		// Firstly, only open essential modules. 
		regVel = 	(rfc_plli_ctrl_reg_plli_en_ldopll_bit |
		           rfc_plli_ctrl_reg_plli_en_bias_bit | 
							 rfc_plli_ctrl_reg_xo50m_en_bit | 
							 rfc_plli_ctrl_reg_xo50m_en_ckdig_bit );
		// Then, if VCO enable, then open other modules. otherwise, do not open them. 
    if (plliVcoLdoEnable == 1)
    {
        regVel |= (rfc_plli_ctrl_reg_plli_en_ldovco_bit | 
			             rfc_plli_ctrl_reg_plli_en_pll_bit | 
			             rfc_plli_ctrl_reg_plli_en_ckdig_125m_bit | 
			             rfc_plli_ctrl_reg_xo50m_en_ckpll_bit | 
			             rfc_plli_ctrl_reg_plli_en_ckplln_bit |
			             rfc_plli_ctrl_reg_plli_en_ckadc_bit ) ;
    }
#if EN_1V8_EXTERNAL	==0
    RFC->rfc_plli_ctrl_reg = regVel;
#else
	regVel |= (rfc_plli_ctrl_reg_plli_en_ldovco_bit | 
			             rfc_plli_ctrl_reg_plli_en_pll_bit | 
			             rfc_plli_ctrl_reg_plli_en_ckdig_125m_bit | 
			             rfc_plli_ctrl_reg_xo50m_en_ckpll_bit | 
			             rfc_plli_ctrl_reg_plli_en_ckplln_bit |
			             rfc_plli_ctrl_reg_plli_en_ckadc_bit ) ;
	regVel &= ~rfc_plli_ctrl_reg_plli_en_ldopll_bit;
	regVel &= ~rfc_plli_ctrl_reg_plli_en_ldovco_bit;
	RFC->rfc_plli_ctrl_reg = regVel;
#endif
    //plli pll ldo open defualt, go to sleep close by FSM
    PMU->pmu_pmu_ctrl_reg |= pmu_pmu_ctrl_reg_manu_ctrl_en_bit;
    delayUs(100,HIGH_CLOCK);
    PMU->pmu_pmu_ctrl_reg &= ~pmu_pmu_ctrl_reg_manu_ctrl_en_bit;

}


void plliDacSetting(void)
{
    //uint32 regVel = 0;
    //regVel = RFC->rf_plli_daca_reg;
    //RFC->rf_plli_daca_reg = regVel;

    //regVel = 0;
    //regVel = RFC->rf_plli_dacb_reg;
    //RFC->rf_plli_dacb_reg = regVel;
}

void plliConfig(int32 plliVcoEn)
{
    uint32 regVel ;//= 0;
	
	//From Yuan. 2021.3.12.
    //modified by xx for ADC_SAMPLE_RATE == ADC_16P6M. 
    regVel = 0x3F0104FF | (RFC->rf_plli_rega_reg & (1<<9));

    if(plliVcoEn == 1)
    {
        regVel |= 1<<rf_plli_rega_reg_plli_reg1_shift;
    } else {
        regVel &= ~(1<<rf_plli_rega_reg_plli_reg1_shift);
    }
    RFC->rf_plli_rega_reg = regVel;

    RFC->rf_plli_regb_reg = 0x9A61093F;

    //regVel |= RFC->rf_plli_regc_reg;
    //RFC->rf_plli_regc_reg = regVel;
}

/************************************************************************************************
                                                PLLN
*************************************************************************************************/
/****************************************************************************************
*Function name : pllnVcoConfig
*Description   :
[11:8]	4'h8	plln_bias_reg1:
<0>: ibias_sel_biasgen: 0: Select V-to-I biasing from BG_1P8, 1: V-to-I biasing is generated internally.
<3:1>: ibias_ztc_sel<2:0>: V-to-I output current selection,
'0' *1.8, '1' *1.55, '2' *1.325, '3' *1.15, '4' *1(default), '5' *0.9, '6' *0.825, '7' *0.75.
[7:0]	8'h0	plln_ldo_reg1:
<0>: NC: NC.
<2:1>: : adjust avdd_VCO, '00' 1.8v, '01' 2.0v, '10' 2.2v, '11' 2.5v.
<3>: : ldo_1p8_lown for VCO.
<5:4>: : adjust avdd_VCO, '00' 1.8v, '01' 2.0v, '10' 2.2v, '11' 2.5v.
<6>: : ldo_1p8_lown for PLL. <7>: : NC.
*Paramater	   :
*        @pllnVcoLdoEnable:  enable VCO LDO
*        @pllnVcoLdo      :  adjust avdd_VCO for PLL VCO
*Paramater	selection:		PLLN_VCO_LDO_1P8     PLLN_VCO_LDO_2P2
                            PLLN_VCO_LDO_2P0     PLLN_VCO_LDO_2P5
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void pllnVcoConfig(int32 pllnVcoLdoEnable, int32 pllnVcoLdo)
{
    if (pllnVcoLdoEnable == 1)
    {
        RFC->rf_plln_ctrl_reg |= rf_plln_ctrl_reg_plln_en_ldovco_bit;
    }
    else
    {
        RFC->rf_plln_ctrl_reg &= ~rf_plln_ctrl_reg_plln_en_ldovco_bit;
    }

    RFC->rf_plln_ldo_cfg_reg &= ~(3<<1);
    RFC->rf_plln_ldo_cfg_reg |= pllnVcoLdo<<1;
}
/****************************************************************************************
*Function name : pllnPllConfig
*Description   :
[11:8]	4'h8	plln_bias_reg1:
<0>: ibias_sel_biasgen: 0: Select V-to-I biasing from BG_1P8, 1: V-to-I biasing is generated internally.
<3:1>: ibias_ztc_sel<2:0>: V-to-I output current selection,
'0' *1.8, '1' *1.55, '2' *1.325, '3' *1.15, '4' *1(default), '5' *0.9, '6' *0.825, '7' *0.75.
[7:0]	8'h0	plln_ldo_reg1:
<0>: NC: NC.
<2:1>: : adjust avdd_VCO, '00' 1.8v, '01' 2.0v, '10' 2.2v, '11' 2.5v.
<3>: : ldo_1p8_lown for VCO.
<5:4>: : adjust avdd_VCO, '00' 1.8v, '01' 2.0v, '10' 2.2v, '11' 2.5v.
<6>: : ldo_1p8_lown for PLL. <7>: : NC.
*Paramater	   :
*        @pllnPllLdoEnable:  enable PLLN LDO
*        @pllnPllLdo      :  adjust avdd for PLLN
*Paramater	selection:		PLLN_VCO_LDO_1P8     PLLN_VCO_LDO_2P2
                            PLLN_VCO_LDO_2P0     PLLN_VCO_LDO_2P5
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void pllnPllConfig(int32 pllnPllLdoEnable, int32 pllnPllLdo, int32 pllnEnBias)
{
    uint32 regVel = 0;
    regVel = RFC->rf_plln_ctrl_reg;
    if (pllnPllLdoEnable == 1)
    {
        regVel |= rf_plln_ctrl_reg_plln_en_ldopll_bit;
    }
    else
    {
        regVel &= ~rf_plln_ctrl_reg_plln_en_ldopll_bit;
    }

    if (pllnEnBias == 1)
    {
        regVel |= rf_plln_ctrl_reg_plln_en_bias_bit;
    }
    else
    {
        regVel &= ~rf_plln_ctrl_reg_plln_en_bias_bit;
    }
    RFC->rf_plln_ctrl_reg = regVel;

    RFC->rf_plln_ldo_cfg_reg &= ~(3<<4);
    RFC->rf_plln_ldo_cfg_reg |= pllnPllLdo<<4;
}

void pllnDacSetting(void)
{
    uint32 regVel = 0;
    regVel = RFC->rf_plln_daca_reg;
    RFC->rf_plln_daca_reg = regVel;

    regVel = 0;
    regVel = RFC->rf_plln_dacb_reg;
    RFC->rf_plln_dacb_reg = regVel;
}

void pllnConfig(int32 vcoEn)
{
    // PLL-N configuration for PLL-N BW=1MHz. External loop filter value: R2=200 Ohm, C2=22nF, no external C1 required.
    // PLL-N configuration for PLL-N BW=300KHz. External loop filter value: R2=130 Ohm, C2=4.7nF, no external C1 required.
    /*
        ___________oVtunt
       |        |
       |        -
       |       | |R2
       |       | |
       |        -
       |        |
      -----    -----
    C1-----  c2-----
       |        |
       |        |
       |________|____Gnd
    */
    //config for haifeng plln reg1~4. cp_offip=cp_offin=3'b0, lpf3d_sel=2'b00
    RFC->rf_plln_rega_reg &= ~0x0f000000;//0x0220887f
#ifdef LOOP_FILTER_1M
    RFC->rf_plln_rega_reg |= 0xB420883F;//0x0220887f
#else
    RFC->rf_plln_rega_reg |= 0x0020883F;//0x0220887f
#endif
    pllnVcoEnable(vcoEn);
    //config for haifeng, ibc_10G=00
    //plln reg5~8. cp_swip=cp_swin=3'b111, ibc_10G=2'b00. vco_sw=4'b0111 is for 20G single-point testing only.
    //RFC->rf_plln_regb_reg = 0x200447BF;
    //becase of lowpower, close plln, so don't write vco switch 
    uint32 regVel = 0;
    regVel = (RFC->rf_plln_regb_reg)&0xf00;
    RFC->rf_plln_regb_reg = 0x200440BF|regVel;
    //config for haifeng
    //plln reg9~12. en_ld=1, ld_vh=ld_vl=3'b001
    RFC->rf_plln_regc_reg = 0x00000492;
    //add gpadc read vtune value from yuan
    //RFC->rf_plln_regc_reg = 0x72300492;
    //RFC->rf_plln_regc_reg = 0x72300480;
    //RFC->rf_plln_regc_reg = 0x000004A4;
    //plln reg13. lpfc1_sel=2'b11
    RFC->rf_plln_regd_reg = 0x00000003;
}

void pllnVcoEnable(int32 vcoEn)
{
    if (vcoEn == 1)
    {
        RFC->rf_plln_rega_reg |= 1<<1;
    }
    else
    {
        RFC->rf_plln_rega_reg &= ~(1<<1);
    }
}
/************************************************************************************************
                                                LDO
*************************************************************************************************/
/****************************************************************************************
*Function name : baseband18LDO
*Description   :
*register*RW*rfc_rx_lna_reg
[5:3]	3'h0	ldo18bb_reg1:
<1:0>: ldo_out<1:0>: adjust LDO output, '00' 1.8v, '01' 2v, '10' 2.2v, '11' 2.5v.
<2>: en_fbc: 1: Enable diode-connected MOS feedback.
[2:0]	3'h0	ldo18bb_reg0:
<1:0>: ldo_out<1:0>: adjust LDO output, '00' 1.8v, '01' 2v, '10' 2.2v, '11' 2.5v.
<2>: en_fbc: 1: Enable diode-connected MOS feedback.
*Paramater	   :
*        @ :
*        @ :
*Paramater	selection:

*Power consumption : Yes
*Return        : None
****************************************************************************************/
void baseband18LDO(int32 bb1Enable, int32 bb1Adjust, int32 bb2Enable, int32 bb2Adjust)
{
    //--- option 1: this register only has bb1Adjust and bb2Adjust, and there is no other bit.
    RFC->rf_ldo18bb_regb_reg = (bb2Adjust << rf_ldo18bb_regb_reg_ldo18bb_reg1_shift) | (bb1Adjust << rf_ldo18bb_regb_reg_ldo18bb_reg0_shift);

    //--- option 2: this register has other bits except bb1Adjust and bb2Adjust.
    //uint32 regVel;
    //regVel = RFC->rf_ldo18bb_regb_reg;
    //regVel &= ~(rf_ldo18bb_regb_reg_ldo18bb_reg1_mask << rf_ldo18bb_regb_reg_ldo18bb_reg1_shift);
    //regVel &= ~(rf_ldo18bb_regb_reg_ldo18bb_reg0_mask << rf_ldo18bb_regb_reg_ldo18bb_reg0_shift);
    //regVel |= (bb1Adjust << rf_ldo18bb_regb_reg_ldo18bb_reg0_shift);
    //regVel |= (bb2Adjust << rf_ldo18bb_regb_reg_ldo18bb_reg1_shift);
    //RFC->rf_ldo18bb_regb_reg = regVel;
    
    if (bb1Enable == 1)
    {
        PMU->pmu_pmu_ctrl_reg |= pmu_pmu_ctrl_reg_ctrl_ldo18bb1_on_bit;
    }
    else
    {
        PMU->pmu_pmu_ctrl_reg &= ~pmu_pmu_ctrl_reg_ctrl_ldo18bb1_on_bit;
    }

    if (bb2Enable == 1)
    {
        PMU->pmu_pmu_ctrl_reg |= pmu_pmu_ctrl_reg_ctrl_ldo18bb2_on_bit;
    }
    else
    {
        PMU->pmu_pmu_ctrl_reg &= ~pmu_pmu_ctrl_reg_ctrl_ldo18bb2_on_bit;
    }

}

/****************************************************************************************
*Function name : dvdd12HpLDO
*Description   :
*register*RW*rfc_ldo12n_rega_reg
[9:8]	2'h0	ldo12_hp_vcfg:
Adjust the out of the LDO_1p2_HP, '00' 1.2v, '01' 1.1v, '10' 1.3v, '11' 1.4v
*Paramater	   :
*        @ powerOnDown:
*        @ dvdd12Adjust:
*Paramater	selection:	POWER_ON 		DVDD1P2_HP DVDD1P3_HP
                        POWER_OFF   	DVDD1P1_HP DVDD1P4_HP
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void dvdd12HpLDO(int32 powerOnDown, int32 dvdd12Adjust)
{
    if (powerOnDown == 1)
    {
        PMU->pmu_pmu_ctrl_reg |= pmu_pmu_ctrl_reg_ctrl_ldo12_pd_bit;
    }
    else
    {
        PMU->pmu_pmu_ctrl_reg &= ~pmu_pmu_ctrl_reg_ctrl_ldo12_pd_bit;
    }

    RFC->rfc_ldo12n_rega_reg &= ~(3<<8);
    RFC->rfc_ldo12n_rega_reg |= dvdd12Adjust<<8;

    PMU->pmu_pmu_ctrl_reg |= pmu_pmu_ctrl_reg_manu_ctrl_en_bit;
    delayUs(100,HIGH_CLOCK);
    PMU->pmu_pmu_ctrl_reg &= ~pmu_pmu_ctrl_reg_manu_ctrl_en_bit;
}
/****************************************************************************************
*Function name : dvdd12LpLDO
*Description   :
*register*RW*rfc_ldo12n_rega_reg
[12:10]	3'h0	ldo12_lp_vcfg:
Adjust the out of the LDO_1p2_LP,
'000' 1.2v,
'001' 0.7v,
'010' 0.75v,
'011' 0.8v,
'100' 0.85v,
'101' 1v,
'110' 1.1v ,
'111' 1.3v
*Paramater	   :
*        @ powerOnDown:
*        @ dvdd12Adjust:
*Paramater	selection:	POWER_ON 		DVDD1P2_LP DVDD0P7_LP DVDD0P75_LP DVDD0P8_LP
                        POWER_OFF   	DVDD0P85_LP DVDD1P0_LP DVDD1P1_LP DVDD1P3_LP
*Power consumption : Yes
*Return        : None
****************************************************************************************/
//void dvdd12LpLDO(int32 powerOnDown, int32 dvdd12Adjust)
//{
//	PMU->pmu_slp_power_ctrl_reg &= ~(1<<2);
//	PMU->pmu_slp_power_ctrl_reg |= powerOnDown<<2;
//
//	RFC->rfc_ldo12n_rega_reg &= ~(7<<10);
//	RFC->rfc_ldo12n_rega_reg |= dvdd12Adjust<<10;
//}

/************************************************************************************************
                                                Mixer
*************************************************************************************************/
/****************************************************************************************
*Function name : fmcwModeSel
*Description   :
*register*RW*rf_buf20g_db_reg
[3:2]2'h0	lo_reg:FMCW buffer mode, 00': int32 mode, '01' external mode, '10' cascaded mode, '11' test mode
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
void fmcwModeSel(int32 fmcwMode)
{
    RFC->rf_buf20g_db_reg &= ~(rf_buf20g_db_reg_lo_reg_mask<<rf_buf20g_db_reg_lo_reg_shift);
    RFC->rf_buf20g_db_reg |= fmcwMode<<rf_buf20g_db_reg_lo_reg_shift;
}
/****************************************************************************************
*Function name : rfbuff20G
*Description   :
*register*RW*rf_buf20g_db_reg
[3:2]2'h0	lo_reg:FMCW buffer mode, 00': int32 mode, '01' external mode, '10' cascaded mode, '11' test mode
[1]	1'h0	buf20g_en:20G buffer enable
[0]	1'h0	dbl_en:doubler enable
*Paramater	   :
*        @ :
*        @ :
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void rfbuff20G(int32 buffer20gEn, int32 doublerEn)
{
    uint32 regVel = 0;
    regVel = RFC->rf_buf20g_db_reg;
    if (doublerEn == 1)
    {
        regVel |= rf_buf20g_db_reg_dbl_en_bit;
    }
    else
    {
        regVel &= ~rf_buf20g_db_reg_dbl_en_bit;
    }

    if (buffer20gEn == 1)
    {
        regVel |= rf_buf20g_db_reg_buf20g_en_bit;
    }
    else
    {
        regVel &= ~rf_buf20g_db_reg_buf20g_en_bit;
    }
    RFC->rf_buf20g_db_reg = regVel;
}
/****************************************************************************************
*Function name : rfbuff20G
*Description   :
*register*RW*rf_buf20g_db_reg
[31:28]	4'h8	bias1_din15:DAC16 data,ib_db77
[27:24]	4'h8	bias1_din14:DAC15 data,ib_buf38
[23:20]	4'h8	bias1_din13:DAC14 data, ib_db38
[19:16]	4'h8	bias1_din12:DAC13 data, 20G buf bias2
[15:12]	4'h8	bias1_din11:DAC12 data, 20G buf
[11:8]	4'h8	bias1_din10:DAC11 data, buf_1to4, tx loop
[7:4]	4'h8	bias1_din9: DAC10 data, buf_1to4, lo loop
[3:0]	4'h8	bias1_din8: DAC9 data, buf_1to4, rx loop
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
void dacEnBias1Pd(int32 dacEnable, int32 Bias1PowerDown)
{
    /*RW
    <3>: dac_en<9:24>: enable for dac<9:24>.
    <0>: pd: bias power down, '0' enable, '1' disable.
    */
    //dac9~24 enable
    //RFC->rf_bias1_regs_reg |= 1<<3;
    uint32 regVel = 0;
    regVel = RFC->rf_bias1_regs_reg;

    if( dacEnable == 1)
    {
        regVel |= 1<<3;
    } else
    {
        regVel &= ~(1<<3);
    }
    if( Bias1PowerDown == 1)
    {
        regVel |= 1<<0;
    } else
    {
        regVel &= ~(1<<0);
    }
    RFC->rf_bias1_regs_reg = regVel;
}

void bias20GTo80G(int32 biasdb77G, int32 biasBuff38, int32 biasDb38, int32 bias2Buff20G,
                  int32 biasbuff20G, int32 txBuff1To4, int32 loBuff1To4, int32 rxBuff1To4)
{
    uint32 regVel = 0;
    //RFC->rf_bias1_dinb_reg   = 0;
    regVel |= biasdb77G   << rf_bias1_dinb_reg_bias1_din15_shift ;
    regVel |= biasBuff38  << rf_bias1_dinb_reg_bias1_din14_shift;
    regVel |= biasDb38    << rf_bias1_dinb_reg_bias1_din13_shift;
    regVel |= bias2Buff20G<< rf_bias1_dinb_reg_bias1_din12_shift;
    regVel |= biasbuff20G << rf_bias1_dinb_reg_bias1_din11_shift;
    regVel |= txBuff1To4  << rf_bias1_dinb_reg_bias1_din10_shift;
    regVel |= loBuff1To4  << rf_bias1_dinb_reg_bias1_din9_shift;
    regVel |= rxBuff1To4  << rf_bias1_dinb_reg_bias1_din8_shift;
    RFC->rf_bias1_dinb_reg   = regVel;
}

void biasPowerdector(int32 biasPowerDector)
{
    /*RW
    [15:12]	4'h8	bias1_din19:DAC20 data,ib power dector
    */
    RFC->rf_bias1_dinc_reg &= ~(rf_bias1_dinc_reg_bias1_din19_mask<<rf_bias1_dinc_reg_bias1_din19_shift);
    RFC->rf_bias1_dinc_reg |= biasPowerDector<<12;
}

void biasBist(int32 biasBistIptat0, int32 biasBistIptat1, int32 biasBist0, int32 biasBist1)
{
    uint32 regVel = 0;
    regVel = RFC->rf_bias1_dinc_reg;
    /*RW
    [11:8]	4'h8	bias1_din18:DAC18, bist IPTAT<1>
    [7:4]	4'h8	bias1_din17:DAC17, bist IPTAT<0>
    */
    regVel &= ~(rf_bias1_dinc_reg_bias1_din17_mask<<rf_bias1_dinc_reg_bias1_din17_shift);
    regVel |= biasBistIptat0<<rf_bias1_dinc_reg_bias1_din17_shift;

    regVel &= ~(rf_bias1_dinc_reg_bias1_din18_mask<<rf_bias1_dinc_reg_bias1_din18_shift);
    regVel |= biasBistIptat1<<rf_bias1_dinc_reg_bias1_din18_shift;
    RFC->rf_bias1_dinc_reg = regVel;

    /*RW
    [11:8]	4'h0	bias2_din18:DAC15 data, Bist bias<1>
    [7:4]	4'h0	bias2_din17:DAC14 data, Bist bias<0>
    */
    regVel = 0;
    regVel = RFC->rf_bias2_dinc_reg;
    regVel &= ~(rf_bias2_dinc_reg_bias2_din17_mask<<rf_bias2_dinc_reg_bias2_din17_shift);
    //Updated 26/04/2021 by Diep. 
    //regVel = biasBistIptat0<<rf_bias2_dinc_reg_bias2_din17_shift;
    regVel = biasBist0<<rf_bias2_dinc_reg_bias2_din17_shift;

    regVel &= ~(rf_bias2_dinc_reg_bias2_din18_mask<<rf_bias2_dinc_reg_bias2_din18_shift);
    //Updated 26/04/2021 by Diep.     
    //regVel |= biasBistIptat1<<rf_bias2_dinc_reg_bias2_din18_shift;
    regVel |= biasBist1<<rf_bias2_dinc_reg_bias2_din18_shift;
    RFC->rf_bias2_dinc_reg = regVel;
}
void biasGpadc(int32 gpadcBias1test, int32 gpadcBias2test, int32 gpadcBias)
{
    /*RW
    [31:28]	4'h0	bias1_din23:
    RF bias iout24 for GPADC test 
    */
    RFC->rf_bias1_dinc_reg &= ~((uint32)rf_bias1_dinc_reg_bias1_din23_mask<<rf_bias1_dinc_reg_bias1_din23_shift);
    RFC->rf_bias1_dinc_reg |= gpadcBias1test<<rf_bias1_dinc_reg_bias1_din23_shift;
    
    /*RW
    [15:12]	4'h0	bias2_din19:BB bias iout20 for GPADC test
    [3:0]	4'h8	bias2_din16:DAC13 data, GPADC bias
    */
    RFC->rf_bias2_dinc_reg &= ~rf_bias2_dinc_reg_bias2_din16_mask;
    RFC->rf_bias2_dinc_reg |= gpadcBias;

    RFC->rf_bias2_dinc_reg &= ~(rf_bias2_dinc_reg_bias2_din19_mask<<rf_bias2_dinc_reg_bias2_din19_shift);
    RFC->rf_bias2_dinc_reg |= gpadcBias2test<<rf_bias2_dinc_reg_bias2_din19_shift;
}
/****************************************************************************************
*Function name : rfBuff77GEnable
*Description   :
*register*RW*rf_buf77g_ctrl_reg
[4]	1'h0	buff77g_en:77G buffer 1st stage enable
[3]	1'h0	buff77g_en_tx0:tx0 buffer enable
[2]	1'h0	buff77g_en_tx1:tx1 buffer enable
[1]	1'h0	buff77g_en_rx0:rx0 buffer enable
[0]	1'h0	buff77g_en_rx1:rx1 buffer enable
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
                     int32 rx0BufferEn77G, int32 rx1BufferEn77G)
{
    uint32 regVel = 0;
    if (rx1BufferEn77G == 1)
    {
        regVel |= rf_buf77g_ctrl_reg_buff77g_en_rx1_bit;
    } else {
        regVel &= ~rf_buf77g_ctrl_reg_buff77g_en_rx1_bit;
    }

    if (rx0BufferEn77G == 1)
    {
        regVel |= rf_buf77g_ctrl_reg_buff77g_en_rx0_bit;
    } else {
        regVel &= ~rf_buf77g_ctrl_reg_buff77g_en_rx0_bit;
    }

    if (tx1BufferEn77G == 1)
    {
        regVel |= rf_buf77g_ctrl_reg_buff77g_en_tx1_bit;
    } else {
        regVel &= ~rf_buf77g_ctrl_reg_buff77g_en_tx1_bit;
    }

    if (tx0BufferEn77G == 1)
    {
        regVel |= rf_buf77g_ctrl_reg_buff77g_en_tx0_bit;
    } else {
        regVel &= ~rf_buf77g_ctrl_reg_buff77g_en_tx0_bit;
    }

    if (stage1Buff77G == 1)
    {
        regVel |= rf_buf77g_ctrl_reg_buff77g_en_bit;
    } else {
        regVel &= ~rf_buf77g_ctrl_reg_buff77g_en_bit;
    }
    RFC->rf_buf77g_ctrl_reg = regVel;
}

/**********************************************************************************************************
									PA
***********************************************************************************************************/
/****************************************************************************************
*Function name : txPaEnable
*Description   : control pa enable
*register*RW*rfc_tx_pa_reg
[31:11]	21'h0	Reserved
[10:8]	3'h0	rf_atb_sel:atb select
[7:2]	6'h0	rf_atb_en:atb enable:<1:0> TX pwr en;<2> RX pwr en; <3> 77G buf atb enable;<4> 20G atb en;<5> db atb enable
[1]		1'h0	pa1_en:pa1 enable
[0]		1'h0	pa0_en:pa0 enable
*Paramater	   :
*        @pa0Enable : channel0 DAC bias1
*        @pa1Enable : channel0 DAC bias2

*Power consumption : Yes
*Return        : None
****************************************************************************************/
void txPaEnable(int32 pa0Enable, int32 pa1Enable)
{
    uint32 regVel = 0;
    regVel = RFC->rfc_tx_pa_reg;
    if (pa0Enable == 1)
    {
        regVel |= rfc_tx_pa_reg_pa0_en_bit;
    }
    else
    {
        regVel &= ~rfc_tx_pa_reg_pa0_en_bit;
    }

    if (pa1Enable == 1)
    {
        regVel |= rfc_tx_pa_reg_pa1_en_bit;
    }
    else
    {
        regVel &= ~rfc_tx_pa_reg_pa1_en_bit;
    }
    RFC->rfc_tx_pa_reg = regVel;
}
/****************************************************************************************
*Function name : txPaBias
*Description   : control dac pa bias
*register*RW*rfc_bias1_dina_reg
[7:4]	4'h8	bias1_din1:DAC2 data, ch1 PA
[3:0]	4'h8	bias1_din0:DAC1 data, ch0 PA
*Paramater	   :
*        @pa0Bias : channel0 PA bias1
*        @pa1Bias : channel0 PA bias2
*Power consumption : Yes
*Return        : None
****************************************************************************************/
void txPaBias(int32 pa0Bias, int32 pa1Bias)
{
    RFC->rfc_bias1_dina_reg &= ~(rfc_bias1_dina_reg_bias1_din1_mask<<rfc_bias1_dina_reg_bias1_din1_shift);
    RFC->rfc_bias1_dina_reg |= pa1Bias<<rfc_bias1_dina_reg_bias1_din1_shift;

    RFC->rfc_bias1_dina_reg &= ~(rfc_bias1_dina_reg_bias1_din0_mask);
    RFC->rfc_bias1_dina_reg |= pa0Bias;
}

// PhaseShift_1:  Direct mode. 
void rfPhaseShift(int32 ps_ip, int32 ps_in, int32 ps_qp, int32 ps_qn)
{
    /*RW
    [20] ps_auto_en:Configure phase shift value and en automatically, instead of from LUT table.
         When this bit is set to 1'h0, then set ps_ip, ps_in, ps_qp, ps_qn directly to analog.
         And then write ps0_en or ps1_en by software.
         When this bit is set to 1'h1, then ps_ip, ps_in, ps_qp, ps_qn are from LUT table and ps0_en/ps1_en from LUT's state machine.
    [19:15] ps_ip:phase shifter data
    [14:10] ps_in:phase shifter data
    [9:5]   ps_qp:phase shifter data
    [4:0]   ps_qn:phase shifter data
    */
    //ps_ip:1f  ps_in:00  ps_qp:1f  ps_qn: 00
    //RFC->rfc_phase_shift_reg = 0x000f83e0;
    //ps_ip:1f  ps_in:00  ps_qp:1f  ps_qn: 00
    //RFC->rfc_phase_shift_reg = 0x000fffff;
    //ps_ip:00  ps_in:00  ps_qp:00  ps_qn: 00
    RFC->rfc_phase_shift_reg = ps_qn| ps_qp<<rfc_phase_shift_reg_ps_qp_shift|ps_in<<rfc_phase_shift_reg_ps_in_shift| ps_ip<<rfc_phase_shift_reg_ps_ip_shift;
    delayUs(1, HIGH_CLOCK);
    RFC->rfc_nload_reg =  (rfc_nload_reg_ps0_en_inv_bit | rfc_nload_reg_ps1_en_inv_bit);  // [2]:ps1_en, [1]:ps0_en
    delayUs(1, HIGH_CLOCK); //Must have delay before loading. 
    RFC->rfc_nload_reg =  rfc_nload_reg_nload_inv_bit;  // [0]: nload.
    
    //--- Notice, RF's PhaseShift register is powered by VDD_RF. So when VDD_RF is powered off, the value will lose. 
    //--- And when VDD_RF is turned on, PhaseShift will be configured again. 
}

// PhaseShift_2:  LUT mode. 
void rfPhaseShiftLUT(int32 ch0_idx, int32 ch1_idx)
{
    // ch0_idx and ch1_idx belongs 0~63. they are indexs of phase shift LUT table. 
    RFC->rfc_phase_shift_reg |= rfc_phase_shift_reg_ps_auto_en_bit;  //enable LUT mode. 
    delayUs(1, HIGH_CLOCK); //Must have delay after writing rfc_phase_shift_reg_ps_auto_en_bit.

    RFC->rf_psr0_reg = ch0_idx;
    RFC->rf_psr1_reg = ch1_idx;
    delayUs(1, HIGH_CLOCK);  //Must have delay before loding. 
    RFC->rfc_nload_reg =  rfc_nload_reg_nload_inv_bit;  // [0]: nload.        
}

/************************************************************************************************
                                                FMCW
*************************************************************************************************/
/****************************************************************************************
*Function name : plliLock
*Description   : adjust VCO cap bank, lock plli at 1G.
*
*register*RW*rf_plli_regd_reg
[2]	1'h0	plli_lock_status:plli locked status register, '1' locked
*register*RW*rf_plli_regb_reg
[31:24]	8'h9a	plli_reg8:
<2:0>: vco_sw<2:0>: VCO cap bank setting.
<5:3>: vco_bias<2:0>: VCO bias current selection. 4~32mA, 4mA/bit.
<7:6>: vco_bias_rsel<1:0>: resistor selection in VCO const-gm bias , 1.13k~1.98k , 283/bit.
*
*Paramater	   : None

*Power consumption : No
*Return        : None
****************************************************************************************/
void plliLock(void)
{
    int32 plliLockStatus;
    int32 vcoCap = 0;
    delayUs(2000, HIGH_CLOCK);
    plliLockStatus = (RFC->rf_plli_regd_reg)&(1<<2);
    while(plliLockStatus != 4)
    {
        RFC->rf_plli_regb_reg &= ~(0x7<<24);
        RFC->rf_plli_regb_reg |= vcoCap<<24;
        vcoCap++;
        if(vcoCap > 7) vcoCap=0;
        delayUs(2000, HIGH_CLOCK);
        plliLockStatus = (RFC->rf_plli_regd_reg)&(1<<2);
        delayUs(2000, HIGH_CLOCK);
    }
}

/****************************************************************************************
*Function name : 
*Description   : 
*Paramater	   :
*        @ :  
*        @ :   
*Paramater	selection:		

*Power consumption : 
*Return        :
****************************************************************************************/
void temperatureCompensation(uint32 miniBais, uint32 kc1Reg, uint32 kc2Reg)
{
    uint32 regVel = 0;
    regVel = RFC->rf_bias1_regs_reg;
    regVel |= miniBais<<14|kc1Reg<<8|kc2Reg<<11;
    RFC->rf_bias1_regs_reg = regVel;
}
/****************************************************************************************
*
*Function name : fmcwChirpSetting
*Description   :
*Paramater	   : The following is the parameter configuaration of vco output(sweep wave)
																												_
                      /|\                    /|\        |            /|\
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
Note : t0+t1+t2 = n*(120ns), "n" is an integer number. 
       2,single frequency mode setting: FM=0;
       3,t0<1.04ms, t1<1.04ms, t0+t1+t2<7.86ms.  
         The "1.04ms" means 2^17*8ns, and the "7.86ms" means 2^16*120ns from data_sample's view. 
       5,Assumed the chirp's slope rate > 950Khz/1us.    
         The "950Khz/1us" means 2Ghz/2^18 per 8ns, and equals to 2Ghz/2^18*125 per 1us. 
*Return        : None
****************************************************************************************/
void fmcwConfig(float fstart,uint32 fm,uint32 t0,uint32 t1,uint32 t2,uint32 chirpNumber)
{
    uint32 c7 = 120;
    float c8 = 8;
    //float c9 = c8;
    float c10 = 8;
    uint32 regVal = 0;
    float b23 = fm*131.072;//pow(2,18)/2000;
    float b24 = t0*1000/c8;
    float b25 = round(fmin(b23,b24));
    float c23 = b25*round(b23/b25);
    float c24 = b25*round(b24/b25);
    float c26 = b25;
    float c29 = round(c26/t0*t1);
    float c31 = round(t2*1000/c10);
    float d24 = c24-fmodf(c24+c29+c31,(c7/c8));
    float c28 = round(c24/t0*t1);
    float d26 = d24;
    float Fstart_actual = fstart;
    float FM_actual = c23/131.072;//*2000000000/pow(2,18)/1000000;
    float T0_actual = d24*c8/1000;
    float T1_actual = c28*c8/1000;
    float T2_actual = c31*c8/1000;
    float c27 = c23;
    uint32 t_temp;
    t_temp = t0 + t1 + t2;
    while((t_temp%3) != 0)
    {
       if((t_temp%3) == 1)
       {
            t0--;
       }else if ((t_temp%3) == 2)
       {
            t0++;
       }
       t_temp = t0 + t1 + t2;
    }

    uint32 freq_start;
    uint32 num_step;
    uint32 dt_step;
    uint32 clear;
    uint32 df_step;
    uint32 df_step_1;
    uint32 num_step_1;
    uint32 dt_step_1;
    uint32 num_step_2;
    uint32 dt_step_2;

    //chirp number
    regVal = 0;
    regVal = chirpNumber&0xff;
    RFC->fmcw_reg4_reg = regVal;

    regVal = 0;
    regVal = (chirpNumber&0xff00)>>8;
    RFC->fmcw_reg5_reg = regVal;

    freq_start = (uint32)(round(131072*(Fstart_actual-64)));//(uint32)(round(pow(2,18)*((Fstart_actual-64)/2)));
    RFC->fmcw_reg12_reg = freq_start&0xff;//FMCW f_start
    RFC->fmcw_reg13_reg = (freq_start&0xff00)>>8;//FMCW f_start
    RFC->fmcw_reg14_reg = (freq_start&0x7F0000)>>16;//FMCW f_start

    num_step = (uint32)(round(d26-1));
    RFC->fmcw_reg16_reg = num_step&0xff;       //ch0 num_step
    RFC->fmcw_reg17_reg = (num_step&0xff00)>>8;//ch0 num_step
    /******************************************* FMCW frequency*******/
    //if t1 ==0, reg6=0. else if t2 ==0, reg6=1.  else  reg6=2.
    if(t1 == 0)
    {
        RFC->fmcw_reg6_reg = 0x00000000;//[3:0]:n: n+1 channels
    } else if (t2 == 0)
    {
        RFC->fmcw_reg6_reg = 0x00000001;//[3:0]:n: n+1 channels
    } else
    {
        RFC->fmcw_reg6_reg = 0x00000002;//[3:0]:n: n+1 channels
    }

    if (fmod(fstart,2)!=0)
    {
        clear = 0;
    } else {
        clear = 1;
    }
    dt_step = (uint32)(round(c24/c26*c8/4-1));
    RFC->fmcw_reg18_reg = ((dt_step&0xf)<<4)|(clear<<1)| ((num_step>>16)&0x1) ;// ch0 dt_step

    df_step = (uint32)(round(c23/c26));
    RFC->fmcw_reg19_reg = ((df_step &0xF)<<4)|((dt_step&0xF0)>>4);// ch0 df_step
    RFC->fmcw_reg20_reg = (df_step &0xFF0)>>4; // ch0 df_step

    if(fm == 0) {
        RFC->fmcw_reg18_reg |= 0<<1 ;   // single
    }


    if(c29) {
        num_step_1 = round(c29-1);
    }
    else {
        num_step_1 = 0;
    }
    //FMCW->fmcw_reg21_reg = num_step_ch1&0xff;       //ch1 num_step
    //FMCW->fmcw_reg22_reg = (num_step_ch1&0xff00)>>8;//ch1 num_step
    *(uint32*)0x40003854 = num_step_1&0xff;         //ch1 num_step
    *(uint32*)0x40003858 = (num_step_1&0xff00)>>8;  //ch1 num_step


    if(c29) {
        dt_step_1 = (uint32)(c28/c29*c8/4-1);
    }
    else {
        dt_step_1 = 0;
    }
    RFC->fmcw_reg23_reg = ((dt_step_1&0xf)<<4)|(1<<2)|((num_step_1&0x100)+4);// ch1 dt_step

    if(c29) {
        df_step_1 = (uint32)(round(c27/c29));
    }
    else {
        df_step_1 = 0;
    }
    RFC->fmcw_reg24_reg = (df_step_1&0xf)<<4|((dt_step_1&0xF0)>>4);  // ch1 df_step
    RFC->fmcw_reg25_reg = (df_step_1&0xff0)>>4;// ch1 df_step


    if(c31) {
        num_step_2 = round(c31-1);
    }
    else {
        num_step_2 = 0;
    }
    RFC->fmcw_reg26_reg = num_step_2&0xff;       //ch1 num_step
    RFC->fmcw_reg27_reg = (num_step_2&0xff00)>>8;//ch1 num_step

    //mode[3:2] , clear [1]
    if(fmod(c10,4)==0)
    {
        if(c10>4)
        {
            dt_step_2 = c10/4-1;
        }
        else {
            printf("dt must be 8ns at least\r\n");
        }
        //ch2_dt_step = roundf(ch1_T1_Tref/ch1_num_step);
    } else {
        printf("dt must be N*4ns\r\n");
    }
    RFC->fmcw_reg28_reg = ((dt_step_2&0xf)<<4)|(1<<2)|(1<<3)|(clear<<1)|(num_step_2>>16)| (num_step_2&0x100);// ch1 dt_step
    
    if (fm !=0 )
    {
        fmcwEnmode(DATA_SAMPLE_MODULE, SINGLE_MODE);
    }
    //// Start fmcw chirp with single_mode.
    //RFC->fmcw_reg0_reg |= (fmcw_reg0_reg_chirp_single_mode_bit | fmcw_reg0_reg_rst_fmcw_n_bit);
    //// configure FMCW trigger signal as ADC start signal.
    //RFC->fmcw_reg7_reg |= fmcw_reg7_reg_fmcw_en_from_ds_bit;

#ifdef TD_MIMO 
    // Please make sure g_tx0En=g_tx1En=1.  g_PaGain0 and g_PaGain0 not be zero. 
    // TD_MIMO could be confirmed by letting tinyFrame send out 2 chirp's data to GUI.  
    // such as tinyFramefTx(0x0B04, (uint8*)(RNG_FFT_CH0_ADDR+SAMPLE_POINT*4), SAMPLE_POINT*4*2); 
    // Please add more delayUs between frames, because tinyFrame need more time to send 2 chirp's data.
    uint32 chirp_channel_num;
    uint32 chirp_channel_bits;
    chirp_channel_num = RFC->fmcw_reg6_reg + 1;        // chirp_channel_num  
    chirp_channel_bits = (1 << chirp_channel_num) - 1; //for example,  2 channels: 0b11.  3 channels:0b111. 
    RFC->fmcw_mimo_tx0_on = chirp_channel_bits;
    RFC->fmcw_mimo_tx1_on = chirp_channel_bits << chirp_channel_num;
    RFC->fmcw_mimo_ctrl   = (chirp_channel_num << 1) | fmcw_mimo_ctrl_auto_tx_on_en_bit;   //chirp_channel_num*2.
#else
  #ifdef BP_MIMO
    // Please make sure g_tx0En=g_tx1En=1.  g_PaGain0 and g_PaGain0 not be zero. 
    // to be tested. 
    uint32 chirp_channel_num;
    uint32 chirp_channel_bits;
    chirp_channel_num = RFC->fmcw_reg6_reg + 1;        // chirp_channel_num  
    chirp_channel_bits = (1 << chirp_channel_num) - 1; //for example,  2 channels: 0b11.  3 channels:0b111. 
    RFC->fmcw_mimo_tx0_psr = 0x0;
    RFC->fmcw_mimo_tx1_psr = chirp_channel_bits << chirp_channel_num;
    RFC->fmcw_mimo_ctrl   = (chirp_channel_num << (fmcw_mimo_ctrl_tx_psr_period_shift+1)) | fmcw_mimo_ctrl_auto_tx_psr_en_bit;   //chirp_channel_num*2.
  #else    
    RFC->fmcw_mimo_ctrl   = 0;
  #endif
#endif
  
    
  

}

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
void fmcwConfig_dualSaw(float fstart,uint32 fmSaw0,uint32 t0Saw0,uint32 t1Saw0,uint32 fmSaw1,uint32 t0Saw1,uint32 t1Saw1,uint32 t2,uint32 chirpNumber)
{

    uint32 c7 = 120;  // ADC sample period. 
    float c8 = 8;     // fmcw reference clock. 
    //float c10 = 8;
    
    float chTemp = fmodf((t0Saw0+t1Saw0+t0Saw1+t1Saw1+t2)*1000,c7);
 
    float ch0StepNum = (t0Saw0*1000 - chTemp)/c8;  //ch0 step number, aligned to adc.
    float ch0Df = round(fmSaw0*131.072/ch0StepNum); // //pow(2,18)/2000;        //ch0 delta frequency  
    float ch1StepNum = round(t1Saw0*1000/c8); 
    float ch1Df = round(ch0Df * ch0StepNum / ch1StepNum) ; 
    float ch2StepNum = round(t0Saw1*1000/c8);   
    float ch2Df = round(fmSaw1*131.072/ch2StepNum); // //pow(2,18)/2000;            
    float ch3StepNum = round(t1Saw1*1000/c8);   
    float ch3Df = round(ch2Df * ch2StepNum / ch3StepNum) ;     
    float ch4StepNum = round(t2*1000/c8);       
        
    float Fstart_actual = fstart;
    //float FM_actual = ch0Df * ch0StepNum * 2000 / pow(2,18);   // unit: Mhz. 
    //float t0Saw0_actual = ch0StepNum * c8 / 1000;              // unit: us.
    //float t1Saw0_actual = ch1StepNum * c8 / 1000;              // unit: us.
    //float T2_actual     = ch4StepNum * c8 / 1000;              // unit: us.

    uint32 freq_start;
    uint32 num_step;
    uint32 dt_step;
    uint32 clear;
    uint32 df_step;
    uint8 channelNumber;   
    uint8 chAdd ;
    uint8 chMode, chClear;
    
    // Chirp number
    RFC->fmcw_reg4_reg = chirpNumber&0xff;
    RFC->fmcw_reg5_reg = (chirpNumber>>8)&0xff;
    
    // Chirp start frequency. 
    freq_start = (uint32)(round(131072*(Fstart_actual-64)));//(uint32)(round(pow(2,18)*((Fstart_actual-64)/2)));
    RFC->fmcw_reg12_reg = freq_start&0xff;//FMCW f_start
    RFC->fmcw_reg13_reg = (freq_start>>8)&0xff;//FMCW f_start
    RFC->fmcw_reg14_reg = (freq_start>>16)&0x7F;//FMCW f_start

    /******************************************* FMCW channel setting *******/
    // only for "UP mode" channel and fstart is 2Ghz's interger multiple, clear is 1.  For all other cases, clear is 0. 
    if (fmod(fstart,2)!=0) {
        clear = 0;
    } else {
        clear = 1;
    }
    // configure channel_0 to channle_5.        
    for(int i=0;i<=5;i++)
    {
        chAdd = 0;
        dt_step = 1;        //assume all channel's dt=1, that means 8ns. 
        switch(i) 
        {
            case 0:
                chAdd = 1;
                channelNumber = 0;
                num_step = (uint32)(ch0StepNum-1);  
                df_step = ch0Df; 
                chClear = clear; 
                chMode = 0x0 ; //0 : UP Mode. 1 : DOWN Mode. 2 : HOLD Mode. 3 : RESET Mode.                    
                break;
            case 1:
                if(t1Saw0 != 0) {
                    chAdd = 1;
                    channelNumber++;
                    num_step = (uint32)(ch1StepNum-1);  
                    df_step = ch1Df; 
                    chClear = 0;      
                    chMode = 0x1 ; //0 : UP Mode. 1 : DOWN Mode. 2 : HOLD Mode. 3 : RESET Mode.               
                }
                break;  
            case 2:  
                if(t0Saw1 != 0) {
                    chAdd = 1;
                    channelNumber++;
                    num_step = (uint32)(ch2StepNum-1);  
                    df_step = ch2Df; 
                    chClear = clear;      
                    chMode = 0x0 ; //0 : UP Mode. 1 : DOWN Mode. 2 : HOLD Mode. 3 : RESET Mode.               
                }                            
                break;
            case 3:    //if t0Saw1=0, then t1Saw1 will be ignored. 
                if((t0Saw1 != 0) && (t1Saw1 != 0)) {
                    chAdd = 1;
                    channelNumber++;
                    num_step = (uint32)(ch3StepNum-1);  
                    df_step = ch3Df; 
                    chClear = 0;      
                    chMode = 0x1 ; //0 : UP Mode. 1 : DOWN Mode. 2 : HOLD Mode. 3 : RESET Mode.               
                }                            
                break;  
            case 4:  
                if(t2 != 0) {
                    chAdd = 1;
                    channelNumber++;
                    num_step = (uint32)(ch4StepNum-1);  
                    df_step = 0; 
                    chClear = clear;      
                    chMode = 0x3 ; //0 : UP Mode. 1 : DOWN Mode. 2 : HOLD Mode. 3 : RESET Mode.               
                }                            
                break;                              
            default : 
                break;
        }
        if(chAdd)
        {
            *((uint32*)(RFC_REG + channelNumber*5 + 0x210)) = num_step&0xff;         // num_step's lsb.  fmcw_reg16_reg is 0x210
            *((uint32*)(RFC_REG + channelNumber*5 + 0x211)) = (num_step>>8)&0xff;    // num_step's mid. 
            *((uint32*)(RFC_REG + channelNumber*5 + 0x212)) = ((dt_step&0xf)<<4) | (chMode << 2) | (chClear<<1) | ((num_step>>16)&0x1) ;  // num_step's msb.
            *((uint32*)(RFC_REG + channelNumber*5 + 0x213)) = ((df_step &0xF)<<4)|((dt_step&0xF0)>>4);
            *((uint32*)(RFC_REG + channelNumber*5 + 0x214)) = (df_step &0xFF0)>>4;                                   
        }                   
    }
    
    RFC->fmcw_reg6_reg = channelNumber;
   
    if (fmSaw0 !=0 )
    {
        fmcwEnmode(DATA_SAMPLE_MODULE, SINGLE_MODE);
    }

#ifdef TD_MIMO 
    // Please make sure g_tx0En=g_tx1En=1.  g_PaGain0 and g_PaGain0 not be zero. 
    // TD_MIMO could be confirmed by letting tinyFrame send out 2 chirp's data to GUI.  
    // such as tinyFramefTx(0x0B04, (uint8*)(RNG_FFT_CH0_ADDR+SAMPLE_POINT*4), SAMPLE_POINT*4*2); 
    // Please add more delayUs between frames, because tinyFrame need more time to send 2 chirp's data.
    uint32 chirp_channel_num;
    uint32 chirp_channel_bits;
    chirp_channel_num = RFC->fmcw_reg6_reg + 1;        // chirp_channel_num  
    chirp_channel_bits = (1 << chirp_channel_num) - 1; //for example,  2 channels: 0b11.  3 channels:0b111. 
    RFC->fmcw_mimo_tx0_on = chirp_channel_bits;
    RFC->fmcw_mimo_tx1_on = chirp_channel_bits << chirp_channel_num;
    RFC->fmcw_mimo_ctrl   = (chirp_channel_num << 1) | fmcw_mimo_ctrl_auto_tx_on_en_bit;   //chirp_channel_num*2.
#else
  #ifdef BP_MIMO
    // Please make sure g_tx0En=g_tx1En=1.  g_PaGain0 and g_PaGain0 not be zero. 
    // to be tested. 
    uint32 chirp_channel_num;
    uint32 chirp_channel_bits;
    chirp_channel_num = RFC->fmcw_reg6_reg + 1;        // chirp_channel_num  
    chirp_channel_bits = (1 << chirp_channel_num) - 1; //for example,  2 channels: 0b11.  3 channels:0b111. 
    RFC->fmcw_mimo_tx0_psr = 0x0;
    RFC->fmcw_mimo_tx1_psr = chirp_channel_bits << chirp_channel_num;
    RFC->fmcw_mimo_ctrl   = (chirp_channel_num << (fmcw_mimo_ctrl_tx_psr_period_shift+1)) | fmcw_mimo_ctrl_auto_tx_psr_en_bit;   //chirp_channel_num*2.
  #else    
    RFC->fmcw_mimo_ctrl   = 0;
  #endif
#endif
}


void fmcwEnmode(int32 startMode, int32 chirpMode)
{
    if (startMode == 1)
    {
        RFC->fmcw_reg0_reg &= ~(0x83);
        // Start fmcw chirp with single_mode.
        // dsm_divn_negedge:select DIVN's clock edge. 1 : neg edge. 0 : posedge.
        RFC->fmcw_reg0_reg |= ((chirpMode<<1) | fmcw_reg0_reg_rst_fmcw_n_bit  | fmcw_reg0_reg_dsm_divn_negedge_bit |fmcw_reg0_reg_dsm_dither_en_bit);
        // configure FMCW trigger signal as ADC start signal.
        RFC->fmcw_reg7_reg |= fmcw_reg7_reg_fmcw_en_from_ds_bit;
    } else
    {
        RFC->fmcw_reg0_reg &= ~(0x83);
        // Start fmcw chirp with single_mode.
        RFC->fmcw_reg0_reg |= ((chirpMode<<1) | fmcw_reg0_reg_rst_fmcw_n_bit | fmcw_reg0_reg_fmcw_en_bit | fmcw_reg0_reg_dsm_divn_negedge_bit|fmcw_reg0_reg_dsm_dither_en_bit);
        // configure FMCW trigger signal as ADC start signal.
        RFC->fmcw_reg7_reg &= ~fmcw_reg7_reg_fmcw_en_from_ds_bit;
    }
}

void waitFmcwcycEnd(void)
{
    while((*(uint32 *)0x40003930) == 0);
}
/****************************************************************************************
*Function name : tdMimo
*Description   : 
*Paramater	   :
*        @channelNum : 
            t0,t1       != 0  channelNum=2
            t0,t1,t2    != 0  channelNum=3
            t0,t1,t2,t3 != 0  channelNum=4
*        @ :   
*Paramater	selection:		

*Power consumption : 
*Return        :
****************************************************************************************/
void tdMimo(uint32 t0,uint32 t1,uint32 t2)
{
    uint8 channelNum;
    txPaEnable(0, 0);
    if(t1 == 0)
    {
        channelNum = 1;
    } else if (t2 == 0)
    {
        channelNum = 2;
    } else
    {
        channelNum = 3;
    }
    RFC->fmcw_mimo_tx0_on = (int32)pow(2, channelNum)-1;
    RFC->fmcw_mimo_tx1_on = ((int32)pow(2, channelNum)-1)<<channelNum;
    
    RFC->fmcw_mimo_ctrl &= ~0xff;
    RFC->fmcw_mimo_ctrl |= 1<<16|channelNum*2;
}
