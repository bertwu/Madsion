//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#include "eMMC.h"

#ifdef IP_FCIE_VERSION_5

#include "hal_fcie5.h"
#ifdef STATIC_RELIABLE_TEST
#include "drvWDT.h"
#include "MsCommon.h"
#include "drvPM.h"
#endif
/*
U16 const crc16_table[256] = {
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
	0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};



static inline U16 crc16_byte(U16 crc, const U8 data)
{
	return (crc >> 8) ^ crc16_table[(crc ^ data) & 0xff];
}

U16 crc16(U16 crc, U8 const *buffer, unsigned int len)
{
	while (len--)
		crc = crc16_byte(crc, *buffer++);
	return crc;
}*/

#if defined(UNIFIED_eMMC_DRIVER) && UNIFIED_eMMC_DRIVER

//========================================================
// HAL pre-processors
//========================================================
#if IF_FCIE_SHARE_IP
    // re-config FCIE3 for NFIE mode
	#define eMMC_RECONFIG()       //eMMC_ReConfig();
#else
    // NULL to save CPU a JMP/RET time
    #define eMMC_RECONFIG()
#endif


#if defined(eMMC_RSP_FROM_RAM) && eMMC_RSP_FROM_RAM
    #define eMMC_KEEP_RSP(pu8_OneRspBuf, u8_CmdIdx)         \
		if(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_RSPFROMRAM_SAVE)\
			eMMC_KeepRsp(pu8_OneRspBuf, u8_CmdIdx)
#else
    #define eMMC_KEEP_RSP(pu8_OneRspBuf, u8_CmdIdx)  // NULL to save CPU a JMP/RET time
#endif


#define eMMC_FCIE_CLK_DIS()    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_CLK_EN)

#define eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT       20
#define eMMC_CMD_API_ERR_RETRY_CNT            20
#define eMMC_CMD_API_WAIT_FIFOCLK_RETRY_CNT   20

#define eMMC_CMD1_RETRY_CNT    0x8000
#define eMMC_CMD3_RETRY_CNT    0x5

U32 eMMC_CMD7(U16 u16_RCA);



//========================================================
// HAL APIs
//========================================================


static U32 gu32Fcie5DebugBus[4];
static char *gStrDebugMode[] = {"CMD state",
								"FIFO status",
								"ADMA Address",
								"ADMA blk cnt"};

//1: CMDstate
//2: {FIFOsts, WRstate, RDstate}l
//3: ADMA Address
//4: ADMA block cnt

void eMMC_FCIE_DumpDebugBus(void)
{
	U32 u32_reg;
	U16 u16_i;

	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n\n");
	eMMC_debug(eMMC_DEBUG_LEVEL, 1, "\n");

	REG_FCIE_CLRBIT(FCIE_EMMC_DEBUG_BUS1, BIT_DEBUG_MODE_MSK);
	REG_FCIE_SETBIT(FCIE_EMMC_DEBUG_BUS1, BIT_DEBUG_MODE_SET);

	for(u16_i=0; u16_i<4; u16_i++)
	{
		REG_FCIE_CLRBIT(FCIE_TEST_MODE, BIT_DEBUG_MODE_MASK);
		REG_FCIE_SETBIT(FCIE_TEST_MODE, (u16_i+1)<<BIT_DEBUG_MODE_SHIFT);

		eMMC_debug(1, 0, "0x15 = %Xh, ", REG_FCIE(FCIE_TEST_MODE));
		REG_FCIE_R(FCIE_EMMC_DEBUG_BUS0, u32_reg);
		eMMC_debug(1, 0, "0x38 = %Xh, ", u32_reg);
		gu32Fcie5DebugBus[u16_i] = u32_reg;

		REG_FCIE_R(FCIE_EMMC_DEBUG_BUS1, u32_reg);
		eMMC_debug(1, 0, "0x39 = %Xh\n", u32_reg);
		gu32Fcie5DebugBus[u16_i] |= (u32_reg&0x00FF)<<16;
	}

	for(u16_i=0; u16_i<4; u16_i++)
	{
		eMMC_debug(1, 0, "%s:\t %06Xh\n", gStrDebugMode[u16_i], gu32Fcie5DebugBus[u16_i]);
	}

	eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n");

}


//static U16 sgau16_eMMCDebugReg[100];


void eMMC_FCIE_DumpRegisterBank(U32 u32Bank, U16 u16WordCount)
{
	U16 u16_i;
	volatile U16 u16_reg;

	for(u16_i=0 ; u16_i<u16WordCount; u16_i++)
	{
		if(0 == u16_i%8)
			eMMC_debug(1, 0, "\n%02Xh:| ", u16_i);

		REG_FCIE_R(GET_REG_ADDR(u32Bank, u16_i), u16_reg);
		eMMC_debug(1, 0, "%04Xh ", u16_reg);
	}
    eMMC_debug(1, 0, "\n");
}

void eMMC_FCIE_DumpRegisters(void)
{
	//U16 u16_i;

	eMMC_debug(1, 0, "\n\nfcie reg:");
	eMMC_FCIE_DumpRegisterBank(FCIE_REG_BASE_ADDR, 0x40);

    eMMC_debug(1, 0, "\n\nchiptop reg:");
	eMMC_FCIE_DumpRegisterBank(PAD_CHIPTOP_BASE, 0x80);

    eMMC_debug(1, 0, "\n\nemmc_pll reg:");
	eMMC_FCIE_DumpRegisterBank(EMMC_PLL_BASE, 0x80);


}

void eMMC_FCIE_ErrHandler_Stop(void)
{
	if(0==eMMC_IF_TUNING_TTABLE())
	{
		//eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);
		eMMC_DumpDriverStatus();
		eMMC_DumpPadClk();
		eMMC_FCIE_DumpRegisters();
		eMMC_FCIE_DumpDebugBus();
		eMMC_die("\n");
	}
	else
		eMMC_FCIE_Init();
}

U32 eMMC_FCIE_ErrHandler_Retry(void)
{
	//static U8 u8_IfToggleDataSync=0;

    eMMC_debug(0,0,"%s\n", __FUNCTION__);

	eMMC_FCIE_Init();

    // -------------------------------------------------
	if(0 ==(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_INIT_DONE))
		return eMMC_ST_SUCCESS;

	// -------------------------------------------------
	if(0 == (g_eMMCDrv.u32_DrvFlag & DRV_FLAG_DDR_MODE))
	{
		if(gau8_FCIEClkSel[eMMC_FCIE_VALID_CLK_CNT-1] == g_eMMCDrv.u16_ClkRegVal)
			return eMMC_ST_ERR_NO_SLOWER_CLK;
	}
	else
	{
		//if(g_eMMCDrv.DDRTable.u8_SetCnt-1 == g_eMMCDrv.DDRTable.u8_CurSetIdx)
			return eMMC_ST_ERR_NO_SLOWER_CLK;
	}

	if(0 == (g_eMMCDrv.u32_DrvFlag & DRV_FLAG_DDR_MODE))
	{
		U8 u8_i;

		for(u8_i=0; u8_i<eMMC_FCIE_VALID_CLK_CNT; u8_i++)
			if(gau8_FCIEClkSel[u8_i] == g_eMMCDrv.u16_ClkRegVal)
				break;

		eMMC_clock_setting(gau8_FCIEClkSel[u8_i+1]);
		eMMC_debug(eMMC_DEBUG_LEVEL_WARNING,0,
			"eMMC Warn: slow SDR clk to %Xh\n", g_eMMCDrv.u16_ClkRegVal);
	}else
	{
	    //eMMC_FCIE_ApplyDDRTSet(g_eMMCDrv.DDRTable.u8_CurSetIdx+1);
		eMMC_debug(eMMC_DEBUG_LEVEL_WARNING,0,
			"eMMC Warn: slow DDR clk to %Xh\n", g_eMMCDrv.u16_ClkRegVal);
	}

	return eMMC_ST_SUCCESS;
}


void eMMC_FCIE_ErrHandler_RestoreClk(void)
{
	if(FCIE_DEFAULT_CLK == g_eMMCDrv.u16_ClkRegVal) // no slow clk
		return;

	if(0 == (g_eMMCDrv.u32_DrvFlag & DRV_FLAG_DDR_MODE))
		eMMC_clock_setting(gau8_FCIEClkSel[0]);
	//else
		//eMMC_FCIE_ApplyDDRTSet(eMMC_DDRT_SET_MAX);
}


void eMMC_FCIE_ErrHandler_ReInit(void)
{
	#if 1
	U32 u32_err;
	U16 u16_RestoreClk=g_eMMCDrv.u16_ClkRegVal;
	//U16 u16_Reg10 = g_eMMCDrv.u16_Reg10_Mode;
	U32 u32_DrvFlag = g_eMMCDrv.u32_DrvFlag;

    eMMC_debug(0,0,"%s\n", __FUNCTION__);

    //g_eMMCDrv.u8_make_sts_err = 0;

	u32_err = eMMC_FCIE_Init();
	if(u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: FCIE_Init fail, %Xh\n", u32_err);
		goto LABEL_REINIT_END;
	}

	g_eMMCDrv.u32_DrvFlag = 0;
	eMMC_PlatformInit();
	u32_err = eMMC_Identify();
	if(u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: Identify fail, %Xh\n", u32_err);
		goto LABEL_REINIT_END;
	}

	eMMC_clock_setting(FCIE_SLOW_CLK);

	u32_err = eMMC_CMD7(g_eMMCDrv.u16_RCA);
	if(u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: CMD7 fail, %Xh\n", u32_err);
		goto LABEL_REINIT_END;
	}

	u32_err = eMMC_SetBusWidth(8, 0);
	if(u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: SetBusWidth fail, %Xh\n", u32_err);
		goto LABEL_REINIT_END;
	}

	u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HIGH);
	if(u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: SetBusSpeed fail, %Xh\n", u32_err);
		goto LABEL_REINIT_END;
	}

	eMMC_clock_setting(u16_RestoreClk);
	g_eMMCDrv.u32_DrvFlag = u32_DrvFlag;

	eMMC_pads_switch(EMMC_HIGH_SPEED_MODE);

	LABEL_REINIT_END:
	if(u32_err)
		eMMC_die("\n");
	#endif
}

#if 0
#define FCIE_WAIT_RST_DONE_D1  0x5555
#define FCIE_WAIT_RST_DONE_D2  0xAAAA
#define FCIE_WAIT_RST_DONE_CNT 3

void eMMC_FCIE_CheckResetDone(void)
{
	volatile U16 au16_tmp[FCIE_WAIT_RST_DONE_CNT];
	volatile U32 u32_i, u32_j, u32_err;

	for(u32_i=0; u32_i<TIME_WAIT_FCIE_RESET; u32_i++)
	{
	    for(u32_j=0; u32_j<FCIE_WAIT_RST_DONE_CNT; u32_j++)
		    REG_FCIE_W(FCIE_CMDFIFO_ADDR(u32_j), FCIE_WAIT_RST_DONE_D1+u32_j);

		for(u32_j=0; u32_j<FCIE_WAIT_RST_DONE_CNT; u32_j++)
		    REG_FCIE_R(FCIE_CMDFIFO_ADDR(u32_j), au16_tmp[u32_j]);

		for(u32_j=0; u32_j<FCIE_WAIT_RST_DONE_CNT; u32_j++)
			if(FCIE_WAIT_RST_DONE_D1+u32_j != au16_tmp[u32_j])
		        break;

		if(FCIE_WAIT_RST_DONE_CNT == u32_j)
			break;
		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	}

	if(TIME_WAIT_FCIE_RESET == u32_i)
	{
		u32_err = eMMC_ST_ERR_FCIE_NO_RIU;
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: check CIFC fail: %Xh \n", u32_err);
	    eMMC_FCIE_ErrHandler_Stop();
	}
}

#endif

U32 eMMC_FCIE_Reset(void)
{
	U16 u16Reg, u16Cnt;
	U32 u32_err = eMMC_ST_SUCCESS;
	U16 u16_clk = g_eMMCDrv.u16_ClkRegVal;

	eMMC_clock_setting(gau8_FCIEClkSel[0]); // speed up FCIE reset done
	REG_FCIE_W(FCIE_MIE_FUNC_CTL, BIT_SD_EN);
	eMMC_FCIE_CLK_DIS(); // do not output clock

	// FCIE reset - set
	REG_FCIE_CLRBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n); /* active low */
	REG_FCIE_CLRBIT(reg_emmcpll_0x6f, BIT1|BIT0);		//macro reset

	// FCIE reset - wait

	u16Cnt=0;
	do
	{
		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	  	if(0x1000 == u16Cnt++)
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: FCIE Reset fail: %Xh \n", eMMC_ST_ERR_FCIE_NO_CLK);
			return eMMC_ST_ERR_FCIE_NO_CLK;
		}

		REG_FCIE_R(FCIE_RST, u16Reg);

	}while (BIT_RST_STS_MASK  != (u16Reg  & BIT_RST_STS_MASK));

	//[FIXME] is there any method to check that reseting FCIE is done?

	// FCIE reset - clear
	REG_FCIE_SETBIT(FCIE_RST, BIT_FCIE_SOFT_RST_n);
	REG_FCIE_SETBIT(reg_emmcpll_0x6f, BIT1|BIT0);
	// FCIE reset - check

	u16Cnt=0;
	do
	{
		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	  	if(0x1000 == u16Cnt++)
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: FCIE Reset fail2: %Xh \n", eMMC_ST_ERR_FCIE_NO_CLK);
			return eMMC_ST_ERR_FCIE_NO_CLK;
		}

		REG_FCIE_R(FCIE_RST, u16Reg);

	}while (0  != (u16Reg  & BIT_RST_STS_MASK));

	eMMC_clock_setting(u16_clk);
	return u32_err;
}


U32 eMMC_FCIE_Init(void)
{
	U32 u32_err;

	eMMC_PlatformResetPre();

	// ------------------------------------------
	#if 0 //eMMC_TEST_IN_DESIGN
	{
		volatile U16 u16_i, u16_reg;
		// check timer clock
		eMMC_debug(eMMC_DEBUG_LEVEL, 1, "Timer test, for 6 sec: ");
		for(u16_i = 6; u16_i > 0; u16_i--)
		{
			eMMC_debug(eMMC_DEBUG_LEVEL, 1, "%u ", u16_i);
			eMMC_hw_timer_delay(HW_TIMER_DELAY_1s);
		}
		eMMC_debug(eMMC_DEBUG_LEVEL, 0, "\n");

		// check FCIE reg.30h
		REG_FCIE_R(FCIE_TEST_MODE, u16_reg);
		if(0)//u16_reg & BIT_FCIE_BIST_FAIL) /* Andersen: "don't care." */
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Reg0x30h BIST fail: %04Xh \r\n", u16_reg);
			return eMMC_ST_ERR_BIST_FAIL;
		}
		if(u16_reg & BIT_FCIE_DEBUG_MODE_MASK)
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: Reg0x30h Debug Mode: %04Xh \r\n", u16_reg);
			return eMMC_ST_ERR_DEBUG_MODE;
		}

		u32_err = eMMC_FCIE_Reset();
		if(eMMC_ST_SUCCESS != u32_err){
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: reset fail\n");
			eMMC_FCIE_ErrHandler_Stop();
			return u32_err;
		}
	}
    #endif // eMMC_TEST_IN_DESIGN

	// ------------------------------------------
	u32_err = eMMC_FCIE_Reset();
	if(eMMC_ST_SUCCESS != u32_err){
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: reset fail: %Xh\n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		return u32_err;
	}

	REG_FCIE_W(FCIE_MIE_INT_EN, 0);
	REG_FCIE_W(FCIE_MIE_FUNC_CTL, BIT_SD_EN);
	// all cmd are 5 bytes (excluding CRC)
	//REG_FCIE_CLRBIT(FCIE_CMD_RSP_SIZE, BIT_CMD_SIZE_MASK);
	//REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, (eMMC_CMD_BYTE_CNT)<< BIT_CMD_SIZE_SHIFT);
	REG_FCIE_W(FCIE_SD_CTRL, 0);
	//REG_FCIE_W(FCIE_SD_MODE, g_eMMCDrv.u16_Reg10_Mode);
	// default sector size: 0x200
	//REG_FCIE_W(FCIE_BLK_SIZE,  eMMC_SECTOR_512BYTE);

    REG_FCIE_W(FCIE_RSP_SHIFT_CNT, 0);
    REG_FCIE_W(FCIE_RX_SHIFT_CNT, 0);
    //REG_FCIE_CLRBIT(FCIE_RX_SHIFT_CNT, BIT_RSTOP_SHIFT_SEL|BIT_RSTOP_SHIFT_TUNE_MASK);

    REG_FCIE_W(FCIE_WR_SBIT_TIMER, 0);
    REG_FCIE_W(FCIE_RD_SBIT_TIMER, 0);

	eMMC_FCIE_ClearEvents();
    eMMC_PlatformResetPost();

	return eMMC_ST_SUCCESS;	// ok
}


#if 0// defined(IF_DETECT_eMMC_DDR_TIMING) && IF_DETECT_eMMC_DDR_TIMING
void eMMC_DumpDDRTTable(void)
{
	U16 u16_i;

	eMMC_debug(eMMC_DEBUG_LEVEL,0,"\n  eMMC DDR Timing Table: Cnt:%u CurIdx:%u \n",
		g_eMMCDrv.TimingTable_t.u8_SetCnt, g_eMMCDrv.TimingTable_t.u8_CurSetIdx);

	for(u16_i=0; u16_i<g_eMMCDrv.TimingTable_t.u8_SetCnt; u16_i++)
	    eMMC_debug(eMMC_DEBUG_LEVEL,0,"    Set:%u: clk:%Xh, DQS:%Xh, Cell:%Xh \n",
			u16_i, g_eMMCDrv.TimingTable_t.Set[u16_i].u8_Clk,
			g_eMMCDrv.TimingTable_t.Set[u16_i].Param.u8_DQS,
			g_eMMCDrv.TimingTable_t.Set[u16_i].Param.u8_Cell);
}

U32 eMMC_LoadDDRTTable(void)
{
	U32 u32_err;
	U32 u32_ChkSum;

	u32_err = eMMC_CMD18(eMMC_DDRTABLE_BLK_0, gau8_eMMC_SectorBuf, 1);
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC WARN: load 1 DDRT Table fail, %Xh\n", u32_err);

		u32_err = eMMC_CMD18(eMMC_DDRTABLE_BLK_1, gau8_eMMC_SectorBuf, 1);
		if(eMMC_ST_SUCCESS != u32_err)
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: load 2 DDRT Tables fail, %Xh\n", u32_err);
			goto LABEL_END_OF_NO_TABLE;
		}
	}

	memcpy((U8*)(&g_eMMCDrv.TimingTable_t), gau8_eMMC_SectorBuf, sizeof(g_eMMCDrv.TimingTable_t));

	u32_ChkSum = eMMC_ChkSum((U8*)(&g_eMMCDrv.TimingTable_t), sizeof(g_eMMCDrv.TimingTable_t)-4);
	if(u32_ChkSum != g_eMMCDrv.TimingTable_t.u32_ChkSum)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: ChkSum error, no DDRT Table \n");
		u32_err = eMMC_ST_ERR_DDRT_CHKSUM;
		goto LABEL_END_OF_NO_TABLE;
	}

	if(0 == u32_ChkSum &&
		g_eMMCDrv.TimingTable_t.Set[0].u8_Clk == g_eMMCDrv.TimingTable_t.Set[1].u8_Clk)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC WARN: no DDRT Table \n");
		u32_err = eMMC_ST_ERR_DDRT_NONA;
		goto LABEL_END_OF_NO_TABLE;
	}

	#if 0
	for(u16_i=0; u16_i<eMMC_FCIE_DDRT_SET_CNT; u16_i++)
	    eMMC_debug(eMMC_DEBUG_LEVEL_HIGH,0,"\n Set:%u: clk:%Xh, DQS:%Xh, Cell:%Xh \n",
				u16_i, g_eMMCDrv.DDRTable.Set[u16_i].u8_Clk,
				g_eMMCDrv.DDRTable.Set[u16_i].Param.u8_DQS,
				g_eMMCDrv.DDRTable.Set[u16_i].Param.u8_Cell);
    #endif
	return eMMC_ST_SUCCESS;

	LABEL_END_OF_NO_TABLE:
	g_eMMCDrv.TimingTable_t.u8_SetCnt = 0;
	return u32_err;

}


U32 eMMC_FCIE_EnableDDRMode_Ex(void)
{
	U32 u32_err;
	g_eMMCDrv.u8_PadType = EMMC_DDR52_MODE;

	u32_err = eMMC_SetBusWidth(g_eMMCDrv.u8_DefaultBusMode, 1);
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
			"eMMC Err: set device 8b DDR fail: %Xh\n", u32_err);
		return u32_err;
	}

	eMMC_pads_switch(EMMC_DDR52_MODE);
	//g_eMMCDrv.u16_Reg10_Mode |= BIT_DATA_SYNC;
	g_eMMCDrv.u16_Reg10_Mode &= ~BIT_DATA_SYNC;
	g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_DDR_MODE;

	return u32_err;
}

U32 eMMC_FCIE_EnableDDRMode(void)
{
	U32 u32_err;

	if(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_DDR_MODE)
		return eMMC_ST_SUCCESS;

	u32_err = eMMC_LoadDDRTTable();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Warn: no DDR Timing Table, %Xh\n", u32_err);
		return u32_err;
	}

	u32_err = eMMC_FCIE_EnableDDRMode_Ex();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: EnableDDRMode_Ex fail, %Xh\n", u32_err);
		eMMC_die("");
		return u32_err;
	}

	eMMC_FCIE_ApplyDDRTSet(eMMC_TIMING_SET_MAX);

	return eMMC_ST_SUCCESS;
}


void eMMC_FCIE_SetDDRTimingReg(U8 u8_DQS, U8 u8_DelaySel)
{
/*	if(g_eMMCDrv.u8_MacroType ==FCIE_eMMC_MACRO_8BIT)
	{
		REG_FCIE_CLRBIT(reg_emmcpll_0x6c, BIT_DQS_MODE_MASK);
		REG_FCIE_SETBIT(reg_emmcpll_0x6c, u8_DQS << BIT_DQS_MODE_SHIFT);
	}
	else if(g_eMMCDrv.u8_MacroType ==FCIE_eMMC_MACRO_32BIT)
	{
		if((u8_DQS & 1))
			REG_FCIE_SETBIT(reg_emmcpll_0x6c, BIT5);  //clock or data inverse ???
		else
			REG_FCIE_CLRBIT(reg_emmcpll_0x6c, BIT5);
		//tune pshof offset

		//REG_FCIE_W(reg_emmcpll_0x69, (u8_DQS << BIT_TUNE_SHOT_OFFSET_SHIFT) & BIT_TUNE_SHOT_OFFSET_MASK) ;
	}

	if(u8_DelaySel) eMMC_debug(1, 1, "\n"); // remove warning
	*/
}


void eMMC_FCIE_ApplyDDRTSet(U8 u8_DDRTIdx)
{
	eMMC_clock_setting(g_eMMCDrv.TimingTable_t.Set[u8_DDRTIdx].u8_Clk);
	eMMC_FCIE_SetDDRTimingReg(
		g_eMMCDrv.TimingTable_t.Set[u8_DDRTIdx].Param.u8_DQS,
		g_eMMCDrv.TimingTable_t.Set[u8_DDRTIdx].Param.u8_Cell);

	g_eMMCDrv.TimingTable_t.u8_CurSetIdx = u8_DDRTIdx;
}
#endif

U32 eMMC_FCIE_EnableSDRMode(void)
{
	U32 u32_err;

	u32_err = eMMC_SetBusWidth(8, 0);
	if(eMMC_ST_SUCCESS != u32_err){
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: set device 8b SDR fail: %Xh\n", u32_err);
        return u32_err;
	}

	eMMC_pads_switch(EMMC_HIGH_SPEED_MODE);

	g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_DDR_MODE;

	return eMMC_ST_SUCCESS;
}

void eMMC_FCIE_ClearEvents(void)
{
	volatile U16 u16_reg;
	while(1){
		REG_FCIE_W(FCIE_MIE_EVENT, BIT_ALL_CARD_INT_EVENTS);
		REG_FCIE_R(FCIE_MIE_EVENT, u16_reg);
		if(0==(u16_reg&BIT_ALL_CARD_INT_EVENTS))
			break;
		REG_FCIE_W(FCIE_MIE_EVENT, 0);
		REG_FCIE_W(FCIE_MIE_EVENT, 0);
	}
	REG_FCIE_W1C(FCIE_SD_STATUS, BIT_SD_FCIE_ERR_FLAGS); // W1C
}


void eMMC_FCIE_ClearEvents_Reg0(void)
{
	volatile U16 u16_reg;

	while(1){
		REG_FCIE_W(FCIE_MIE_EVENT, BIT_ALL_CARD_INT_EVENTS);
		REG_FCIE_R(FCIE_MIE_EVENT, u16_reg);
		if(0==(u16_reg&BIT_ALL_CARD_INT_EVENTS))
			break;
		REG_FCIE_W(FCIE_MIE_EVENT, 0);
		REG_FCIE_W(FCIE_MIE_EVENT, 0);
	}
}

#if 0
U32 eMMC_FCIE_WaitD0High_Ex(U32 u32_us)
{
   volatile U32 u32_cnt;
   volatile U16 u16_read0=0, u16_read1=0;

   for(u32_cnt=0; u32_cnt < u32_us; u32_cnt++)
   {
   	   REG_FCIE_R(FCIE_SD_STATUS, u16_read0);
	   eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	   REG_FCIE_R(FCIE_SD_STATUS, u16_read1);

	   if((u16_read0&BIT_SD_CARD_BUSY) ==0 && (u16_read1&BIT_SD_CARD_BUSY) ==0)
	       break;

	   if(u32_cnt > 500 && u32_us-u32_cnt > 1000)
	   {
	   	   eMMC_hw_timer_sleep(1);
		   u32_cnt += 1000-2;
	   }
   }

   return u32_cnt;
}

U32 eMMC_FCIE_WaitD0High(U32 u32_us)
{
    volatile U32 u32_cnt;

	REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_CLK_EN);
	u32_cnt = eMMC_FCIE_WaitD0High_Ex(u32_us);

	if(u32_us == u32_cnt)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: wait D0 H timeout %u us\n", u32_cnt);
		return eMMC_ST_ERR_TIMEOUT_WAITD0HIGH;
	}
//	eMMC_hw_timer_delay(HW_TIMER_DELAY_1s  * 2);

    return eMMC_ST_SUCCESS;
}

U32 eMMC_FCIE_SendCmd
(
	U16 u16_Mode, U16 u16_Ctrl, U32 u32_Arg, U8 u8_CmdIdx, U8 u8_RspByteCnt
)
{
	U32 u32_err, u32_Timeout = TIME_WAIT_DAT0_HIGH;
	U16 au16_tmp[3];

    if(38 == u8_CmdIdx)
        u32_Timeout = TIME_WAIT_ERASE_DAT0_HIGH;

    #if (defined(DELAY_FOR_DEBUGGING_BUS) && DELAY_FOR_DEBUGGING_BUS) || \
        (defined(DELAY_FOR_BRIAN) && DELAY_FOR_BRIAN)
    printf("\33[1;31mCMD%02d_%08Xh\33[m\n", u8_CmdIdx, u32_Arg); // red color
    #endif

	#if 0
	eMMC_debug(0,1,"\n");
	eMMC_debug(0,1,"cmd:%u, arg:%Xh, rspb:%Xh, mode:%Xh, ctrl:%Xh \n",
		u8_CmdIdx, u32_Arg, u8_RspByteCnt, u16_Mode, u16_Ctrl);
	#endif

	REG_FCIE_CLRBIT(FCIE_CMD_RSP_SIZE, BIT_RSP_SIZE_MASK);

    if( g_eMMCDrv.u8_make_sts_err == FCIE_MAKE_CMD_RSP_ERR )
    {
        REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, (u8_RspByteCnt+1) & BIT_RSP_SIZE_MASK);
    }
    else
    {
	    REG_FCIE_SETBIT(FCIE_CMD_RSP_SIZE, u8_RspByteCnt & BIT_RSP_SIZE_MASK);
    }

	REG_FCIE_W(FCIE_SD_MODE, u16_Mode);
	//   set cmd
	//   CMDFIFO(0) = 39:32 | 47:40
	//   CMDFIFO(1) = 23:16 | 31:24
	//   CMDFIFO(2) = (CIFC(2) & 0xFF00) | 15:8, ignore (CRC7 | end_bit).

	//check command FIFO for filled command value
	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_CHK_CMD);
	while(1)
	{
//		eMMC_debug(0, 1, "FIFO 0 =  0x%4X\n",  ((u32_Arg>>24)<<8) | (0x40|u8_CmdIdx));
//		eMMC_debug(0, 1, "FIFO 1 =  0x%4X\n",  (u32_Arg&0xFF00) | ((u32_Arg>>16)&0xFF));
//		eMMC_debug(0, 1, "FIFO 2 =  0x%4X\n", u32_Arg&0xFF);
		REG_FCIE_W(FCIE_CMDFIFO_ADDR(0),((u32_Arg>>24)<<8) | (0x40|u8_CmdIdx));
		REG_FCIE_W(FCIE_CMDFIFO_ADDR(1), (u32_Arg&0xFF00) | ((u32_Arg>>16)&0xFF));
		REG_FCIE_W(FCIE_CMDFIFO_ADDR(2),  u32_Arg&0xFF);

		REG_FCIE_R(FCIE_CMDFIFO_ADDR(0),au16_tmp[0]);
		REG_FCIE_R(FCIE_CMDFIFO_ADDR(1),au16_tmp[1]);
		REG_FCIE_R(FCIE_CMDFIFO_ADDR(2),au16_tmp[2]);

		if(au16_tmp[0] == (((u32_Arg>>24)<<8) | (0x40|u8_CmdIdx))&&
			au16_tmp[1] == ((u32_Arg&0xFF00) | ((u32_Arg>>16)&0xFF))&&
			au16_tmp[2] == (u32_Arg&0xFF))
			break;
	}

	//clear command check for reading response value
	REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

	if(12 != u8_CmdIdx)
	{
		u32_err = eMMC_FCIE_WaitD0High(u32_Timeout);
		if(eMMC_ST_SUCCESS != u32_err)
			goto LABEL_SEND_CMD_ERROR;
	}

	REG_FCIE_W(FCIE_SD_CTRL, u16_Ctrl |BIT_JOB_START);

	#if defined(ENABLE_eMMC_INTERRUPT_MODE) && ENABLE_eMMC_INTERRUPT_MODE
	REG_FCIE_W(FCIE_MIE_INT_EN, BIT_CMD_END);
	#endif
	if(g_eMMCDrv.u32_DrvFlag & DRV_FLAG_RSP_WAIT_D0H){
		u32_err = eMMC_FCIE_WaitD0High(u32_Timeout);
        if(eMMC_ST_SUCCESS != u32_err)
	        goto LABEL_SEND_CMD_ERROR;
	}

	// wait event
	if( g_eMMCDrv.u8_make_sts_err == FCIE_MAKE_RD_TOUT_ERR )
        u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_CMD_END, TIME_WAIT_CMDRSP_END*100);
    else
	u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_CMD_END, TIME_WAIT_CMDRSP_END);

	LABEL_SEND_CMD_ERROR:
	return u32_err;

}
#endif

void eMMC_FCIE_GetCMDFIFO(U16 u16_WordPos, U16 u16_WordCnt, U16 *pu16_Buf)
{
	U16 u16_i;

	if(u16_WordPos==0x55) eMMC_debug(1, 1, "\n"); // remove warning

	for(u16_i=0; u16_i<u16_WordCnt; u16_i++)
		REG_FCIE_R(FCIE_CMDFIFO_ADDR(u16_i), pu16_Buf[u16_i]);
}

U8 eMMC_FCIE_CmdRspBufGet(U8 u8addr)
{
    U16 u16Tmp;

    u16Tmp = REG_FCIE(FCIE_CMDFIFO_ADDR(u8addr>>1));

    if(u8addr&0x1)
    {
        return ((u16Tmp>>8)&0xFF);
    }
    else
    {
        return (u16Tmp&0xFF);
    }
}

U8 eMMC_FCIE_DataFifoGet(U8 u8addr)
{
    U16 u16Tmp;

    u16Tmp = REG_FCIE(FCIE_CMDFIFO_ADDR(u8addr>>1));

    if(u8addr&0x1)
    {
        return ((u16Tmp>>8)&0xFF);
    }
    else
    {
        return (u16Tmp&0xFF);
    }
}

//===================================================
#if defined(eMMC_RSP_FROM_RAM) && eMMC_RSP_FROM_RAM
void eMMC_KeepRsp(U8 *pu8_OneRspBuf, U8 u8_CmdIdx)
{
	U16 u16_idx;
	U8  u8_ByteCnt;

	u16_idx = u8_CmdIdx * eMMC_CMD_BYTE_CNT;
	u8_ByteCnt = eMMC_CMD_BYTE_CNT;

	if(u8_CmdIdx > 10)
		u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*3;
	else if(u8_CmdIdx > 9)
		u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*2;
	else if(u8_CmdIdx > 2)
		u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*1;

	if(10==u8_CmdIdx || 9==u8_CmdIdx || 2==u8_CmdIdx)
		u8_ByteCnt = eMMC_R2_BYTE_CNT;

	if(u16_idx+u8_ByteCnt > eMMC_SECTOR_512BYTE-4) // last 4 bytes are CRC
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: KeepRsp over 512B, %Xh, %Xh, %Xh\n",
			u8_CmdIdx, u16_idx, u8_ByteCnt);
		eMMC_die("\n"); // should be system fatal error, not eMMC driver
	}

	memcpy(g_eMMCDrv.au8_AllRsp + u16_idx, pu8_OneRspBuf, u8_ByteCnt);

}


U32 eMMC_ReturnRsp(U8 *pu8_OneRspBuf, U8 u8_CmdIdx)
{
	U16 u16_idx;
	U8  u8_ByteCnt;

	u16_idx = u8_CmdIdx * eMMC_CMD_BYTE_CNT;
	u8_ByteCnt = eMMC_CMD_BYTE_CNT;

	if(u8_CmdIdx > 10)
		u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*3;
	else if(u8_CmdIdx > 9)
		u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*2;
	else if(u8_CmdIdx > 2)
		u16_idx += (eMMC_R2_BYTE_CNT-eMMC_CMD_BYTE_CNT)*1;

	if(10==u8_CmdIdx || 9==u8_CmdIdx || 2==u8_CmdIdx)
		u8_ByteCnt = eMMC_R2_BYTE_CNT;

	if(u16_idx+u8_ByteCnt > eMMC_SECTOR_512BYTE-4) // last 4 bytes are CRC
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: KeepRsp over 512B, %Xh, %Xh, %Xh\n",
			u8_CmdIdx, u16_idx, u8_ByteCnt);
		return eMMC_ST_ERR_NO_RSP_IN_RAM;
	}

	if(0 == g_eMMCDrv.au8_AllRsp[u16_idx])
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_LOW,1,"eMMC Info: no rsp, %u %u \n", u8_CmdIdx, u16_idx);
		return eMMC_ST_ERR_NO_RSP_IN_RAM;
	}

	memcpy(pu8_OneRspBuf, g_eMMCDrv.au8_AllRsp + u16_idx, u8_ByteCnt);

	return eMMC_ST_SUCCESS;
}


// -------------------------------
U32 eMMC_SaveRsp(void)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_SaveDriverContext(void)
{

	return eMMC_ST_SUCCESS;
}


U32 eMMC_LoadRsp(U8 *pu8_AllRspBuf)
{

	return eMMC_ST_SUCCESS;
}

U32 eMMC_LoadDriverContext(U8 *pu8_Buf)
{

    return eMMC_ST_SUCCESS;
}

#endif
//========================================================
// Send CMD HAL APIs
//========================================================
U32 eMMC_Identify(void)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	U16 u16_i, u16_retry=0;

	g_eMMCDrv.u16_RCA=1;
	g_eMMCDrv.u8_BUS_WIDTH = BUS_WIDTH_1;
	g_eMMCDrv.u32_SEC_COUNT = 0;

LABEL_IDENTIFY_CMD0:

	if(eMMC_ST_SUCCESS != eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH))
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: WaitD0High TO\n");
	    eMMC_FCIE_ErrHandler_Stop();
	}
	eMMC_RST_L();  eMMC_hw_timer_sleep(1);
	eMMC_RST_H();  eMMC_hw_timer_sleep(1);

	if(u16_retry > 10)
	{
		eMMC_FCIE_ErrHandler_Stop();
		return u32_err;
	}
	if(u16_retry)
		eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC Warn: retry: %u\n", u16_retry);

	// CMD0
	u32_err = eMMC_CMD0(0); // reset to idle state
	if(eMMC_ST_SUCCESS != u32_err)
	{u16_retry++;  goto LABEL_IDENTIFY_CMD0;}

	// CMD1
	for(u16_i=0; u16_i<eMMC_CMD1_RETRY_CNT; u16_i++)
	{
		//eMMC_debug(eMMC_DEBUG_LEVEL, 1, "CMD1 try: %02Xh \n", u16_i);
		u32_err = eMMC_CMD1();
		if(eMMC_ST_SUCCESS == u32_err)
			break;

		eMMC_hw_timer_sleep(2);

		if(eMMC_ST_ERR_CMD1_DEV_NOT_RDY != u32_err)
		{u16_retry++;  goto LABEL_IDENTIFY_CMD0;}
	}
	//eMMC_debug(eMMC_DEBUG_LEVEL, 1, "CMD1 try: %02Xh \n", u16_i);
	if(eMMC_ST_SUCCESS != u32_err)
	{u16_retry++;  goto LABEL_IDENTIFY_CMD0;}

	// CMD2
	u32_err = eMMC_CMD2();
	if(eMMC_ST_SUCCESS != u32_err)
	{u16_retry++;  goto LABEL_IDENTIFY_CMD0;}

	// CMD3
	u32_err = eMMC_CMD3(g_eMMCDrv.u16_RCA);
	if(eMMC_ST_SUCCESS != u32_err)
	{
		u16_retry++;
		g_eMMCDrv.u16_RCA++;
		goto LABEL_IDENTIFY_CMD0;
	}

	return eMMC_ST_SUCCESS;
}


U32 eMMC_CMD0(U32 u32_Arg) //
{
	U32 u32_err = eMMC_ST_SUCCESS;
    CMD_RSP_INFO CmdRspInfo;// = {0};

    //CmdRspInfo.CardClock = gDisk[u8Disk].CardClock;

	CmdRspInfo.Command.Cmd.Index = eMMC_GO_IDLE_STATE;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_Arg);

    CmdRspInfo.CmdType = CMD_TYPE_BC;
    CmdRspInfo.RspType = RSP_TYPE_NO;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD0 %Xh \n", u32_err);

	return u32_err;
}

// send OCR
U32 eMMC_CMD1(void)
{
	U32 u32_err = eMMC_ST_SUCCESS, u32_arg;
	//U16 u16_ctrl, u16_reg;
	#if 0
	U8  u8_retry_fcie=0, u8_retry_cmd=0;
	#endif
    CMD_RSP_INFO CmdRspInfo;// = {0};

	// (sector mode | byte mode) | (3.0|3.1|3.2|3.3|3.4 V)
	u32_arg = BIT30 | (BIT23|BIT22|BIT21|BIT20|BIT19|BIT18|BIT17|BIT16|BIT15);

	CmdRspInfo.Command.Cmd.Index = eMMC_SEND_OP_COND;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);
	/*CmdRspInfo.CmdRsp.Command[1] = 0x40;
    CmdRspInfo.CmdRsp.Command[2] = 0xFF;
    CmdRspInfo.CmdRsp.Command[3] = 0x80;
    CmdRspInfo.CmdRsp.Command[4] = 0x00;*/

    CmdRspInfo.CmdType = CMD_TYPE_BCR;
    CmdRspInfo.RspType = RSP_TYPE_R3;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
	else
	{
		// CMD1 ok, do things here
    	if( CmdRspInfo.Response.Array[1] & 0x80 ) // vlotage accepted
    	{
			eMMC_FCIE_GetCMDFIFO(0, 3, (U16*)g_eMMCDrv.au8_Rsp);
			g_eMMCDrv.u8_IfSectorMode = (g_eMMCDrv.au8_Rsp[1]&BIT6)>>6;
			//eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 1);
			return eMMC_ST_SUCCESS;
    	}
		else
		{
			// eMMC not pwoer up ready
			//printf("not ready...\n");
			return eMMC_ST_ERR_CMD1_DEV_NOT_RDY;
		}
	}

    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD1 %Xh \n", u32_err);

	return u32_err;
}


// send CID
U32 eMMC_CMD2(void)
{
	U32 u32_err = eMMC_ST_SUCCESS;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	CmdRspInfo.Command.Cmd.Index = eMMC_ALL_SEND_CID;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(STUFF_BITS);

    CmdRspInfo.CmdType = CMD_TYPE_BCR;
    CmdRspInfo.RspType = RSP_TYPE_R2;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
	else
	{
		// CMD2 ok, do things here (get CID)
		eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CID);
		eMMC_dump_mem(g_eMMCDrv.au8_CID, eMMC_R2_BYTE_CNT);
		//eMMC_KEEP_RSP(g_eMMCDrv.au8_CID, 2);
	}
    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD2 %Xh \n", u32_err);

	return u32_err;

}


// CMD3: assign RCA. CMD7: select device
U32 eMMC_CMD3(U16 u16_RCA)
{
	U32 u32_err = eMMC_ST_SUCCESS;//, u32_arg;
	//U16 u16_ctrl, u16_reg;
	//U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	CmdRspInfo.Command.Cmd.Index = eMMC_SET_RLT_ADDR;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u16_RCA<<16);

    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
	else
	{
		// CMD2 ok, do things here (get CID)
		//eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CID);
		//eMMC_dump_mem(g_eMMCDrv.au8_CID, eMMC_R2_BYTE_CNT);
		//eMMC_KEEP_RSP(g_eMMCDrv.au8_CID, 2);
	}
    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD3 %Xh \n", u32_err);

	return u32_err;
}

U32 eMMC_CMD7(U16 u16_RCA)
{
	U32 u32_err = eMMC_ST_SUCCESS;//, u32_arg;
	//U16 u16_ctrl, u16_reg;
	//U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

    CMD_RSP_INFO CmdRspInfo;// = {0};

	CmdRspInfo.Command.Cmd.Index = eMMC_SEL_DESEL_CARD;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u16_RCA<<16);

    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1b;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
	else
	{
		// CMD2 ok, do things here (get CID)
		//eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CID);
		//eMMC_dump_mem(g_eMMCDrv.au8_CID, eMMC_R2_BYTE_CNT);
		//eMMC_KEEP_RSP(g_eMMCDrv.au8_CID, 2);
	}
    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD7 %Xh \n", u32_err);

	return u32_err;
}

U32 eMMC_CMD3_CMD7(U16 u16_RCA, U8 u8_CmdIdx)
{
	if(u8_CmdIdx==3) {
		return eMMC_CMD3(u16_RCA);
	}
	else if(u8_CmdIdx==7){
		return eMMC_CMD7(u16_RCA);
	}
	else {
		eMMC_debug(1, 1, "wrong cmd idx for eMMC_CMD3_CMD7()\n");
		return eMMC_ST_ERR_PARAMETER;
	}
}

//------------------------------------------------
U32 eMMC_CSD_Config(void)
{
	U32 u32_err = eMMC_ST_SUCCESS;

	u32_err = eMMC_CMD9(g_eMMCDrv.u16_RCA);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	// ------------------------------
	g_eMMCDrv.u8_SPEC_VERS = (g_eMMCDrv.au8_CSD[1]&0x3C)>>2;
	g_eMMCDrv.u8_R_BL_LEN = g_eMMCDrv.au8_CSD[6] & 0xF;
	g_eMMCDrv.u8_W_BL_LEN = ((g_eMMCDrv.au8_CSD[13]&0x3)<<2)+
		((g_eMMCDrv.au8_CSD[14]&0xC0)>>6);

	// ------------------------------
	g_eMMCDrv.u16_C_SIZE = (g_eMMCDrv.au8_CSD[7] & 3)<<10;
	g_eMMCDrv.u16_C_SIZE += g_eMMCDrv.au8_CSD[8] << 2;
	g_eMMCDrv.u16_C_SIZE +=(g_eMMCDrv.au8_CSD[9] & 0xC0) >> 6;
	if(0xFFF == g_eMMCDrv.u16_C_SIZE)
	{
		g_eMMCDrv.u32_SEC_COUNT = 0;
	}
	else
	{
		g_eMMCDrv.u8_C_SIZE_MULT = ((g_eMMCDrv.au8_CSD[10]&3)<<1)+
			((g_eMMCDrv.au8_CSD[11]&0x80)>>7);

		g_eMMCDrv.u32_SEC_COUNT =
			(g_eMMCDrv.u16_C_SIZE+1)*
			(1<<(g_eMMCDrv.u8_C_SIZE_MULT+2))*
			((1<<g_eMMCDrv.u8_R_BL_LEN)>>9) - 8; // -8: //Toshiba CMD18 access the last block report out of range error
	}

	//printf("g_eMMCDrv.u32_SEC_COUNT = %X\n", g_eMMCDrv.u32_SEC_COUNT);

	// ------------------------------
	g_eMMCDrv.u8_ERASE_GRP_SIZE = (g_eMMCDrv.au8_CSD[10]&0x7C)>>2;
	g_eMMCDrv.u8_ERASE_GRP_MULT = ((g_eMMCDrv.au8_CSD[10]&0x03)<<3)+
		((g_eMMCDrv.au8_CSD[11]&0xE0)>>5);
	g_eMMCDrv.u32_EraseUnitSize = (g_eMMCDrv.u8_ERASE_GRP_SIZE+1)*
		(g_eMMCDrv.u8_ERASE_GRP_MULT+1);
    // ------------------------------
	// others
	g_eMMCDrv.u8_TAAC = g_eMMCDrv.au8_CSD[2];
	g_eMMCDrv.u8_NSAC = g_eMMCDrv.au8_CSD[3];
	g_eMMCDrv.u8_Tran_Speed = g_eMMCDrv.au8_CSD[4];
	g_eMMCDrv.u8_R2W_FACTOR = (g_eMMCDrv.au8_CSD[13]&0x1C)>>2;

	return eMMC_ST_SUCCESS;
}


// send CSD (in R2)
U32 eMMC_CMD9(U16 u16_RCA)
{
	U32 u32_err = eMMC_ST_SUCCESS;//, u32_arg;
	//U16 u16_ctrl, u16_reg;
	//U8  u8_retry_fcie=0, u8_retry_cmd=0;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	CmdRspInfo.Command.Cmd.Index = eMMC_SEND_CSD;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u16_RCA<<16);

    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R2;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
		u32_err = 0x1234;
        goto ErrorHandle;
    }
	else
	{
		eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CSD);
		//eMMC_dump_mem(g_eMMCDrv.au8_CSD, eMMC_R2_BYTE_CNT);
		//eMMC_KEEP_RSP(g_eMMCDrv.au8_CSD, 9);
	}
    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD9 %Xh \n", u32_err);

	return u32_err;
}

//------------------------------------------------
U32 eMMC_ExtCSD_Config(void)
{
	U32 u32_err = eMMC_ST_SUCCESS;

	u32_err = eMMC_CMD8(gau8_eMMC_SectorBuf);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	//eMMC_dump_mem(gau8_eMMC_SectorBuf, 0x200);

	g_eMMCDrv.u32_SEC_COUNT = 0;

	//--------------------------------
	if(0 == g_eMMCDrv.u32_SEC_COUNT)
		 g_eMMCDrv.u32_SEC_COUNT = ((gau8_eMMC_SectorBuf[215]<<24)|
		                           (gau8_eMMC_SectorBuf[214]<<16)|
		                           (gau8_eMMC_SectorBuf[213]<< 8)|
		                           (gau8_eMMC_SectorBuf[212])) - 8; //-8: Toshiba CMD18 access the last block report out of range error
	eMMC_debug(eMMC_DEBUG_LEVEL_LOW, 0, "g_eMMCDrv.u32_SEC_COUNT = %X\n", g_eMMCDrv.u32_SEC_COUNT);
    //-------------------------------
	if(0 == g_eMMCDrv.u32_BOOT_SEC_COUNT)
		 g_eMMCDrv.u32_BOOT_SEC_COUNT = gau8_eMMC_SectorBuf[226] * 128 * 2;

	//--------------------------------
	if(!g_eMMCDrv.u8_BUS_WIDTH) {
		g_eMMCDrv.u8_BUS_WIDTH = gau8_eMMC_SectorBuf[183];
		switch(g_eMMCDrv.u8_BUS_WIDTH)
		{
			case 0:  g_eMMCDrv.u8_BUS_WIDTH = BUS_WIDTH_1;  break;
			case 1:  g_eMMCDrv.u8_BUS_WIDTH = BUS_WIDTH_4;  break;
			case 2:  g_eMMCDrv.u8_BUS_WIDTH = BUS_WIDTH_8;  break;
			default: eMMC_debug(0,1,"eMMC Err: eMMC BUS_WIDTH not support \n");
			    while(1);
		}
	}
	//--------------------------------
	if(gau8_eMMC_SectorBuf[231]&BIT4) // TRIM
		g_eMMCDrv.u32_eMMCFlag |= eMMC_FLAG_TRIM;
	else
		g_eMMCDrv.u32_eMMCFlag &= ~eMMC_FLAG_TRIM;

	//--------------------------------
	if(gau8_eMMC_SectorBuf[503]&BIT0) // HPI
	{
		if(gau8_eMMC_SectorBuf[503]&BIT1)
			g_eMMCDrv.u32_eMMCFlag |= eMMC_FLAG_HPI_CMD12;
		else
			g_eMMCDrv.u32_eMMCFlag |= eMMC_FLAG_HPI_CMD13;
	}else
		g_eMMCDrv.u32_eMMCFlag &= ~(eMMC_FLAG_HPI_CMD12|eMMC_FLAG_HPI_CMD13);

	//--------------------------------
	if(gau8_eMMC_SectorBuf[166]&BIT2) // Reliable Write
	    g_eMMCDrv.u16_ReliableWBlkCnt = BIT_SD_JOB_BLK_CNT_MASK;
	else
	{
		#if 0
		g_eMMCDrv.u16_ReliableWBlkCnt = gau8_eMMC_SectorBuf[222];
		#else
		if((gau8_eMMC_SectorBuf[503]&BIT0) && 1==gau8_eMMC_SectorBuf[222])
		    g_eMMCDrv.u16_ReliableWBlkCnt = 1;
		else if(0==(gau8_eMMC_SectorBuf[503]&BIT0))
			g_eMMCDrv.u16_ReliableWBlkCnt = gau8_eMMC_SectorBuf[222];
		else
		{
			//eMMC_debug(0,1,"eMMC Warn: not support dynamic  Reliable-W\n");
			g_eMMCDrv.u16_ReliableWBlkCnt = 0; // can not support Reliable Write
		}
		#endif
	}

	//--------------------------------
	g_eMMCDrv.u8_ErasedMemContent = gau8_eMMC_SectorBuf[181];

	//--------------------------------
	g_eMMCDrv.u8_ECSD185_HsTiming = gau8_eMMC_SectorBuf[185];
	g_eMMCDrv.u8_ECSD192_Ver = gau8_eMMC_SectorBuf[192];
	g_eMMCDrv.u8_ECSD196_DevType = gau8_eMMC_SectorBuf[196];
	g_eMMCDrv.u8_ECSD197_DriverStrength = gau8_eMMC_SectorBuf[197];
	g_eMMCDrv.u8_ECSD248_CMD6TO = gau8_eMMC_SectorBuf[248];
	g_eMMCDrv.u8_ECSD247_PwrOffLongTO = gau8_eMMC_SectorBuf[247];
	g_eMMCDrv.u8_ECSD34_PwrOffCtrl = gau8_eMMC_SectorBuf[34];

	//for GP Partition
	g_eMMCDrv.u8_ECSD160_PartSupField = gau8_eMMC_SectorBuf[160];
	g_eMMCDrv.u8_ECSD224_HCEraseGRPSize= gau8_eMMC_SectorBuf[224];
	g_eMMCDrv.u8_ECSD221_HCWpGRPSize= gau8_eMMC_SectorBuf[221];

	//for Max Enhance Size
	g_eMMCDrv.u8_ECSD157_MaxEnhSize_0= gau8_eMMC_SectorBuf[157];
	g_eMMCDrv.u8_ECSD158_MaxEnhSize_1= gau8_eMMC_SectorBuf[158];
	g_eMMCDrv.u8_ECSD159_MaxEnhSize_2= gau8_eMMC_SectorBuf[159];

	g_eMMCDrv.u8_u8_ECSD155_PartSetComplete = gau8_eMMC_SectorBuf[155];
	g_eMMCDrv.u8_ECSD166_WrRelParam = gau8_eMMC_SectorBuf[166];
	/*printf("[196] DEVICE TYPE = %02Xh\n", g_eMMCDrv.u8_ECSD196_DevType);
	printf("[197] DRIVER STRENGTH = %02Xh\n", g_eMMCDrv.u8_ECSD197_DriverStrength);
	printf("[185] HS_TIMING = %02Xh\n", g_eMMCDrv.u8_ECSD185_HsTiming);*/

	//--------------------------------
	// set HW RST
	if(0 == gau8_eMMC_SectorBuf[162])
	{
		u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 162, BIT0); // RST_FUNC
		if(eMMC_ST_SUCCESS != u32_err)
		{
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh, eMMC, set Ext_CSD[162]: %Xh fail\n",
			u32_err, BIT0);
			return u32_err;
		}
	}

	return eMMC_ST_SUCCESS;
}


U32 eMMC_CMD8(U8 *pu8_DataBuf)
{
	#if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
    	return eMMC_CMD8_CIFD(pu8_DataBuf);
	#else
    	return eMMC_CMD8_MIU(pu8_DataBuf);
	#endif
}

// CMD8: send EXT_CSD
U32 eMMC_CMD8_CIFD(U8 *pu8_DataBuf)
{
	U32 u32_err= eMMC_ST_SUCCESS;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	CmdRspInfo.Command.Cmd.Index = eMMC_SEND_EXT_CSD;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(STUFF_BITS);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.DataPath = PATH_R2N;
	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}
	CmdRspInfo.MiuAddr = 0; // R2N don't need this field
	CmdRspInfo.pBufferAddr = (U32*)pu8_DataBuf;
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    //u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
	else
	{
		//eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CSD);
		//eMMC_dump_mem(g_eMMCDrv.au8_CSD, eMMC_R2_BYTE_CNT);
		//eMMC_KEEP_RSP(g_eMMCDrv.au8_CSD, 9);
	}

	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		u32_err = eMMC_ST_ERR_CMD8_MIU;
		eMMC_debug(1, 1, "eMMC Err: CMD8 check R1 error: %Xh\n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
	}

	//eMMC_dump_mem(ExtCSD, 512);

    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD8 %Xh \n", u32_err);

	return u32_err;
}

// CMD8: send EXT_CSD
U32 eMMC_CMD8_MIU(U8 *pu8_DataBuf)
{
	U32 u32_err = eMMC_ST_SUCCESS;
    CMD_RSP_INFO CmdRspInfo;// = {0};
	U32 u32_dma_addr;

	//eMMC_dump_mem(pu8_DataBuf, 512);

//printf("before --> %08Xh\n", (U32)pu8_DataBuf );

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);

//printf("after --> %08Xh\n", u32_dma_addr );



	CmdRspInfo.Command.Cmd.Index = eMMC_SEND_EXT_CSD;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(STUFF_BITS);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.DataPath = PATH_DMA;
	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}
	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
	else
	{
		//eMMC_dump_mem(pu8_DataBuf, 512);
		//eMMC_FCIE_GetCMDFIFO(0, eMMC_R2_BYTE_CNT>>1, (U16*)g_eMMCDrv.au8_CSD);
		//eMMC_dump_mem(g_eMMCDrv.au8_CSD, eMMC_R2_BYTE_CNT);
		//eMMC_KEEP_RSP(g_eMMCDrv.au8_CSD, 9);
	}

	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
		u32_err = eMMC_ST_ERR_CMD8_MIU;
		eMMC_debug(1, 1, "eMMC Err: CMD8 check R1 error: %Xh\n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
	}

	//eMMC_dump_mem(pu8_DataBuf, 512);

    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD8 %Xh \n", u32_err);

	return u32_err;
}


U32 eMMC_SetPwrOffNotification(U8 u8_SetECSD34)
{
	U32 u32_err;
	static U8 u8_OldECSD34=0;

	if(eMMC_PwrOffNotif_SHORT==u8_OldECSD34 || eMMC_PwrOffNotif_LONG==u8_OldECSD34)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: PwrOffNotif already set: %u, now: %u\n",
			u8_OldECSD34, u8_SetECSD34);
		return eMMC_ST_SUCCESS;
	}

	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 34, u8_SetECSD34); // PWR_OFF_NOTIFICATION
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_PwrOffNotif_MASK;
	switch(u8_SetECSD34)
	{
		case eMMC_PwrOffNotif_OFF:
			g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_OFF;  break;
		case eMMC_PwrOffNotif_ON:
			g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_ON;  break;
		case eMMC_PwrOffNotif_SHORT:
			g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_SHORT;  break;
		case eMMC_PwrOffNotif_LONG:
			g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_PwrOffNotif_LONG;  break;
	}

	return u32_err;
}

U32 eMMC_Sanitize(U8 u8_ECSD165)
{
	U32 u32_err;

	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 165, u8_ECSD165);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	u32_err = eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH<<2);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	return eMMC_ST_SUCCESS;
}

#define BITS_MSK_DRIVER_STRENGTH	0xF0
#define BITS_MSK_TIMING			0x0F

U32 eMMC_SetBusSpeed(U8 u8_BusSpeed)
{
	U32 u32_err;

	g_eMMCDrv.u8_ECSD185_HsTiming &= ~BITS_MSK_TIMING;
	g_eMMCDrv.u8_ECSD185_HsTiming |= u8_BusSpeed;

	eMMC_debug(1, 1, "%s(%02Xh)\n", __FUNCTION__, g_eMMCDrv.u8_ECSD185_HsTiming);

	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 185, g_eMMCDrv.u8_ECSD185_HsTiming); // HS_TIMING, HS200
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	g_eMMCDrv.u32_DrvFlag &= ~DRV_FLAG_SPEED_MASK;
	switch(u8_BusSpeed)
	{
		case eMMC_SPEED_HIGH:
			g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_SPEED_HIGH;
			//eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC set bus HIGH speed\n");
			break;
		case eMMC_SPEED_HS200:
			g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_SPEED_HS200;
			//eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC set bus HS200 speed\n");
			break;
        case eMMC_SPEED_HS400:
			g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_SPEED_HS400;
			//eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC set bus HS400 speed\n");
			break;
		default:
			//eMMC_debug(eMMC_DEBUG_LEVEL,1,"eMMC set bus LOW speed\n");
			break;
	}

	return u32_err;
}

U32 eMMC_SetDrivingStrength(U8 u8Driving)
{
	U32 u32_err;

	g_eMMCDrv.u8_ECSD185_HsTiming &= ~BITS_MSK_DRIVER_STRENGTH;
	g_eMMCDrv.u8_ECSD185_HsTiming |= u8Driving;

	//printf("\n\n%s(%02Xh)\n", __FUNCTION__, g_eMMCDrv.u8_ECSD185_HsTiming);
	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 185, g_eMMCDrv.u8_ECSD185_HsTiming); // HS_TIMING, HS200
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(1, 1, "eMMC Err: %s() fail %Xh\n", __FUNCTION__, u32_err);
		return eMMC_ST_ERR_SET_DRV_STRENGTH;
	}

	return eMMC_ST_SUCCESS;
}

// Use CMD6 to set ExtCSD[183] BUS_WIDTH
U32 eMMC_SetBusWidth(U8 u8_BusWidth, U8 u8_IfDDR)
{
	U8  u8_value;
	U32 u32_err;

	// -------------------------------
	switch(u8_BusWidth)
	{
		case 1:  u8_value=0; break;
		case 4:  u8_value=1; break;
		case 8:  u8_value=2; break;
		default: return eMMC_ST_ERR_PARAMETER;
	}

	if(u8_IfDDR)
		u8_value |= BIT2;
	if(BIT2 == u8_value)
		return eMMC_ST_ERR_PARAMETER;

	// -------------------------------
	u32_err = eMMC_ModifyExtCSD(eMMC_ExtCSD_WByte, 183, u8_value); // BUS_WIDTH
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	// -------------------------------
	//g_eMMCDrv.u16_Reg10_Mode &= ~BIT_SD_DATA_WIDTH_MASK;
	switch(u8_BusWidth)
	{
		case 1:
			g_eMMCDrv.u8_BUS_WIDTH = BUS_WIDTH_1;
			//g_eMMCDrv.u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_1;
			if( (g_eMMCDrv.u8_PadType != EMMC_DEFO_SPEED_MODE) &&
                (g_eMMCDrv.u8_PadType != EMMC_HIGH_SPEED_MODE) )
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "Can't enable 1bit mode for SDR/DDR Mode\n");
                eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "g_eMMCDrv.u8_PadType=%d\n", g_eMMCDrv.u8_PadType);
				eMMC_die("\n");
			}
			break;
		case 4:
			g_eMMCDrv.u8_BUS_WIDTH = BUS_WIDTH_4;
			//g_eMMCDrv.u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_4;
			break;
		case 8:
			g_eMMCDrv.u8_BUS_WIDTH = BUS_WIDTH_8;
			//g_eMMCDrv.u16_Reg10_Mode |= BIT_SD_DATA_WIDTH_8;
			break;
	}

    //REG_FCIE_W(FCIE_SD_MODE, g_eMMCDrv.u16_Reg10_Mode); // add by hdwang


	//eMMC_debug(eMMC_DEBUG_LEVEL,1,"set %u bus width\n", u8_BusWidth);
	return u32_err;
}

U32 eMMC_ModifyExtCSD(U8 u8_AccessMode, U8 u8_ByteIdx, U8 u8_Value)
{
	U32 u32_arg, u32_err;

    //eMMC_debug(0, 1, "ByteIdx: %d(%03X), value %02X\n", u8_ByteIdx, u8_ByteIdx, u8_Value);

	u32_arg = ((u8_AccessMode&3)<<24) | (u8_ByteIdx<<16) |
		      (u8_Value<<8);

	u32_err = eMMC_CMD6(u32_arg);
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: eMMC: %Xh \n", u32_err);
		return u32_err;
	}

	u32_err = eMMC_CMD13(g_eMMCDrv.u16_RCA);
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: eMMC: %Xh \n", u32_err);
		return u32_err;
	}

    return u32_err;
}

// SWITCH cmd
U32 eMMC_CMD6(U32 u32_Arg)
{
	U32 u32_err;
    CMD_RSP_INFO CmdRspInfo = {0};
	//U16 u16_ctrl, u16_reg;
	//U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

	//u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;
	g_eMMCDrv.u32_DrvFlag |= DRV_FLAG_RSP_WAIT_D0H;


	CmdRspInfo.Command.Cmd.Index = eMMC_SWITCH;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_Arg);

    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1b;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);
    if(u32_err)
    {
        goto ErrorHandle;
    }
	else
	{
	}

    return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD6 %Xh \n", u32_err);

	return u32_err;
}


U32 eMMC_EraseCMDSeq(U32 u32_eMMCBlkAddr_start, U32 u32_eMMCBlkAddr_end)
{
	U32 u32_err;

	u32_err = eMMC_CMD35_CMD36(u32_eMMCBlkAddr_start, 35);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	u32_err = eMMC_CMD35_CMD36(u32_eMMCBlkAddr_end, 36);
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	u32_err = eMMC_CMD38();
	if(eMMC_ST_SUCCESS != u32_err)
		return u32_err;

	return u32_err;
}

U32 eMMC_CMD35_CMD36(U32 u32_eMMCBlkAddr, U8 u8_CmdIdx)
{
	U32 u32_err, u32_arg;
	U8  u8_retry = 0;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	if(u8_CmdIdx==35)
		CmdRspInfo.Command.Cmd.Index = eMMC_ERASE_GROUP_S;
	else
		CmdRspInfo.Command.Cmd.Index = eMMC_ERASE_GROUP_E;

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);

    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

LABEL_SEND_CMD:

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

    if(u32_err)
    {
		if(u8_retry < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry++;
			eMMC_debug(1, 1, "eMMC WARN: CMD%u retry:%u, %Xh \n", u8_CmdIdx, u8_retry, u32_err);
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}

		eMMC_debug(1, 1, "eMMC Err: CMD%u retry:%u, %Xh \n", u8_CmdIdx, u8_retry, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
    }
	else
	{
		u32_err = eMMC_CheckR1Error();
		if(eMMC_ST_SUCCESS != u32_err)
		{
			if(u8_retry < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE()){
				u8_retry++;
				eMMC_debug(1, 1, "eMMC WARN: CMD%u check R1 error: %Xh, retry: %u\n", u8_CmdIdx, u32_err, u8_retry);
				eMMC_FCIE_ErrHandler_Retry();
				goto LABEL_SEND_CMD;
			}
			eMMC_debug(1, 1, "eMMC Err: CMD%u check R1 error: %Xh, retry: %u\n", u8_CmdIdx, u32_err, u8_retry);
			eMMC_FCIE_ErrHandler_Stop();
		}
	}

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD35 CMD36 %Xh \n", u32_err);

	return u32_err;
}

U32 eMMC_CMD38(void)
{
	U32 u32_err, u32_arg;
 	U8  u8_retry_r1=0, u8_retry_cmd=0;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	if(g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_TRIM)
		u32_arg =  0x1;
	else
		u32_arg =  0x0;

	CmdRspInfo.Command.Cmd.Index = eMMC_ERASE;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);
    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1b;

LABEL_SEND_CMD:

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

    if(u32_err)
    {
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD38 retry:%u, %Xh \n",
				u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}

		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD38 retry:%u, %Xh \n",
			u8_retry_cmd, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
    }
	else
	{
			// CMD38 ok, do things here
			u32_err = eMMC_CheckR1Error();
			if(eMMC_ST_SUCCESS != u32_err)
			{
				if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE()){
					u8_retry_r1++;
					eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					    "eMMC WARN: CMD38 check R1 error: %Xh, retry: %u\n",
					    u32_err, u8_retry_r1);
					eMMC_FCIE_ErrHandler_Retry();
					goto LABEL_SEND_CMD;
				}
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
				    "eMMC Err: CMD38 check R1 error: %Xh, retry: %u\n",
				    u32_err, u8_retry_r1);
				eMMC_FCIE_ErrHandler_Stop();
			}
			eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 38);
	}

	return u32_err;
}


// CMD13: send Status
U32 eMMC_CMD13(U16 u16_RCA)
{
	U32 u32_err, u32_arg;
	//U16 u16_ctrl, u16_reg;
	U8  u8_retry = 0;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	u32_arg = (u16_RCA<<16);// | ((g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_HPI_CMD13)?1:0);

	/*if(g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_TRIM)
		u32_arg =  0x1;
	else
		u32_arg =  0x0;*/

	CmdRspInfo.Command.Cmd.Index = eMMC_SEND_STATUS;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);
    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

LABEL_SEND_CMD:

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

    if(u32_err)
    {
		if(u8_retry < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD13 retry:%u, %Xh \n", u8_retry, u32_err);
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD13 retry:%u, %Xh \n", u8_retry, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
    }
	else
	{
			// CMD13 ok, do things here
			u32_err = eMMC_CheckR1Error();
			if(eMMC_ST_SUCCESS != u32_err)
			{
				if(u8_retry < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE()){
					u8_retry++;
					eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					    "eMMC WARN: CMD13 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry);
					eMMC_FCIE_ErrHandler_Retry();
					goto LABEL_SEND_CMD;
				}
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
				    "eMMC Err: CMD13 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry);
				eMMC_FCIE_ErrHandler_Stop();
			}
			eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 13);
	}

	eMMC_FCIE_CLK_DIS();
	return u32_err;
}

#if 0
U32 eMMC_CMD16(U32 u32_BlkLength)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;
	U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

	u32_arg = u32_BlkLength;
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

	LABEL_SEND_CMD:
	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 16, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD16 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD16 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
    }
	else
	{	// check status
		REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

		if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
		{
			if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
			{
				u8_retry_fcie++;
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					"eMMC WARN: CMD16 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
				eMMC_FCIE_ErrHandler_Retry();
				goto LABEL_SEND_CMD;
			}

			u32_err = eMMC_ST_ERR_CMD16;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					"eMMC Err: CMD16 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
			eMMC_FCIE_ErrHandler_Stop();
		}
		else
		{	// CMD16 ok, do things here
			u32_err = eMMC_CheckR1Error();
			if(eMMC_ST_SUCCESS != u32_err)
			{
				if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE()){
					u8_retry_r1++;
					eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					    "eMMC WARN: CMD16 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
					eMMC_FCIE_ErrHandler_Retry();
					goto LABEL_SEND_CMD;
				}
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
				    "eMMC Err: CMD16 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
				eMMC_FCIE_ErrHandler_Stop();
			}
			eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 16);
		}
	}

	eMMC_FCIE_CLK_DIS();
	return u32_err;
}
#endif

//------------------------------------------------

U32 eMMC_CMD17(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	//#if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
    //return eMMC_CMD17_CIFD(u32_eMMCBlkAddr, pu8_DataBuf);
	//#else
    return eMMC_CMD17_MIU(u32_eMMCBlkAddr, pu8_DataBuf);
	//#endif
}

U32 eMMC_CMD17_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	U32 u32_arg;
	U8  u8_retry = 0;

    CMD_RSP_INFO CmdRspInfo;// = {0};
	U32 u32_dma_addr;

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);

	CmdRspInfo.Command.Cmd.Index = eMMC_R_SINGLE_BLOCK;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.DataPath = PATH_DMA;

	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}

	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
	    /*if(u8_retry < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
	    {
		    u8_retry++;
		    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD17 retry:%u, %Xh, Arg: %Xh \n", u8_retry, u32_err, u32_arg);
		    eMMC_FCIE_ErrHandler_Retry();
		    //goto ErrorHandle;
	    }*/
	    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD17 retry:%u, %Xh, Arg: %Xh \n", u8_retry, u32_err, u32_arg);
	    eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	u32_err = eMMC_CheckR1Error();

	if(u32_err)
	{
	    eMMC_FCIE_ErrHandler_ReInit();
	}

    /*if( g_eMMCDrv.u8_check_last_blk_crc )
    {
        eMMC_dump_mem(FCIE_CRC_BASE, 0x40);
        //crc16(0, pu8_DataBuf, 512)
    }*/

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(1, 1, "eMMC Err: CMD17 MIU fail, err = %X\n", u32_err);

	return u32_err;
}


U32 eMMC_CMD17_CIFD(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	U32 u32_arg;
	U8  u8_retry = 0;

    CMD_RSP_INFO CmdRspInfo;// = {0};

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

LABEL_SEND_CMD:

	CmdRspInfo.Command.Cmd.Index = eMMC_R_SINGLE_BLOCK;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.DataPath = PATH_R2N;

	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}

	CmdRspInfo.MiuAddr = 0; // R2N don't need this field
	CmdRspInfo.pBufferAddr = (U32*)pu8_DataBuf;
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
	    if(u8_retry < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
	    {
		    u8_retry++;
		    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD17 retry:%u, %Xh, Arg: %Xh \n", u8_retry, u32_err, u32_arg);
		    eMMC_FCIE_ErrHandler_Retry();
		    goto LABEL_SEND_CMD;
	    }
	    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD17 retry:%u, %Xh, Arg: %Xh \n", u8_retry, u32_err, u32_arg);
	    eMMC_FCIE_ErrHandler_Stop();
	    goto ErrorHandle;

	}

	u32_err = eMMC_CheckR1Error();

	if(u32_err)
	{
	    eMMC_FCIE_ErrHandler_ReInit();
	}

    /*if( g_eMMCDrv.u8_check_last_blk_crc )
    {
        eMMC_dump_mem(FCIE_CRC_BASE, 0x40);
        //crc16(0, pu8_DataBuf, 512)
    }*/

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(1, 1, "eMMC Err: CMD17 MIU fail, err = %X\n", u32_err);

	return u32_err;
}


U32 eMMC_CMD12(U16 u16_RCA)
{
	U8  u8_retry_r1=0, u8_retry_cmd=0;
	U32 u32_err = eMMC_ST_SUCCESS;//, u32_arg;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	//u32_arg = (u16_RCA<<16);
	//u32_arg |= ((g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_HPI_CMD12)?1:0); // for HPI

	CmdRspInfo.Command.Cmd.Index = eMMC_STOP_TRANSMIT;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u16_RCA<<16);

    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1b;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD12 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_ReInit();
			//eMMC_FCIE_ErrHandler_Retry();
			//goto LABEL_SEND_CMD;
			return u32_err;
		}
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD12 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
	}
	else
	{
		u32_err = eMMC_CheckR1Error();
		if(eMMC_ST_SUCCESS != u32_err)
		{
			if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
	        {
		        u8_retry_r1++;
    			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
	                "eMMC WARN: CMD12 check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
    			//eMMC_FCIE_ErrHandler_Retry();
	        	//goto LABEL_SEND_CMD;
	        	return u32_err;
	        }
	    	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
	            "eMMC Err: CMD12 check R1 error: %Xh, Retry: %u\n", u32_err, u8_retry_r1);
	        eMMC_FCIE_ErrHandler_Stop();
			goto ErrorHandle;
	    }
		eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 12);
	}

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD12 %Xh \n", u32_err);

	return u32_err;

}


U32 eMMC_CMD12_NoCheck(U16 u16_RCA)
{
	U32 u32_err = eMMC_ST_SUCCESS;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	//u32_arg = (u16_RCA<<16);
	//u32_arg |= ((g_eMMCDrv.u32_eMMCFlag & eMMC_FLAG_HPI_CMD12)?1:0); // for HPI

	CmdRspInfo.Command.Cmd.Index = eMMC_STOP_TRANSMIT;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u16_RCA<<16);

    CmdRspInfo.CmdType = CMD_TYPE_AC;
    CmdRspInfo.RspType = RSP_TYPE_R1b;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	//eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD12 %Xh \n", u32_err);

	return u32_err;
}


U32 eMMC_CMD18(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
	#if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
	U16 u16_cnt;
	U32 u32_err;

	for(u16_cnt=0; u16_cnt<u16_BlkCnt; u16_cnt++)
	{
		u32_err = eMMC_CMD17_CIFD(u32_eMMCBlkAddr+u16_cnt, pu8_DataBuf+(u16_cnt<<9));
		if(eMMC_ST_SUCCESS != u32_err)
			return u32_err;
	}
	#else
    return eMMC_CMD18_MIU(u32_eMMCBlkAddr, pu8_DataBuf, u16_BlkCnt);
	#endif
}

U32 eMMC_CMD18_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	U32 u32_arg;
	U8  u8_retry = 0;
	U8  u8_cmd12_snet = 0;

    CMD_RSP_INFO CmdRspInfo;// = {0};
	U32 u32_dma_addr;

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE*u16_BlkCnt);

	CmdRspInfo.Command.Cmd.Index = eMMC_R_MULTIP_BLOCK;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.DataPath = PATH_DMA;

	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}

	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = u16_BlkCnt;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
	    #if 0
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD18 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_ReInit();
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD18 retry:%u, %Xh \n", u8_retry, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
	    #if 0
		if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_r1++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
		        "eMMC WARN: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);

			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		u32_err = eMMC_ST_ERR_CMD18;
		eMMC_debug(1, 1, "eMMC Err: CMD18 check R1 error: %Xh, Arg: %Xh\n", u32_err, u32_arg);
	    eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	u32_err = eMMC_CMD12(g_eMMCDrv.u16_RCA);
	u8_cmd12_snet = 1;
	if(u32_err) {
		eMMC_debug(1, 1, "eMMC Err: CMD12 fail after CMD18, error: %Xh, Arg: %Xh\n", u32_err, u32_arg);
		goto ErrorHandle;
	}

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(1, 1, "eMMC Err: CMD18 MIU fail, err = %X\n", u32_err);

	// sned CMD12 without check when CMD18 fail for eMMC back to tran-state
	if(u8_cmd12_snet==0) eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);

	return u32_err;
}

#if 0
// enable Reliable Write
U32 eMMC_CMD23(U16 u16_BlkCnt)
{
	U32 u32_err, u32_arg;
	U16 u16_ctrl, u16_reg;
	U8  u8_retry_r1=0, u8_retry_fcie=0, u8_retry_cmd=0;

	u32_arg = u16_BlkCnt&0xFFFF; // don't set BIT24
	#if eMMC_FEATURE_RELIABLE_WRITE
    u32_arg |= BIT31; // don't set BIT24
	#endif
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

	LABEL_SEND_CMD:
	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 23, eMMC_R1_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD23 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD23 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
    }
	else
	{	// check status
		REG_FCIE_R(FCIE_SD_STATUS, u16_reg);

		if(u16_reg & (BIT_SD_RSP_TIMEOUT|BIT_SD_RSP_CRC_ERR))
		{
			if(u8_retry_fcie < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
			{
				u8_retry_fcie++;
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					"eMMC WARN: CMD23 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
				eMMC_FCIE_ErrHandler_Retry();
				goto LABEL_SEND_CMD;
			}

			u32_err = eMMC_ST_ERR_CMD13;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					"eMMC Err: CMD23 SD_STS: %04Xh, Retry: %u\n", u16_reg, u8_retry_fcie);
			eMMC_FCIE_ErrHandler_Stop();
		}
		else
		{	// CMD13 ok, do things here
			u32_err = eMMC_CheckR1Error();
			if(eMMC_ST_SUCCESS != u32_err)
			{
				if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE()){
					u8_retry_r1++;
					eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
					    "eMMC WARN: CMD23 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
					eMMC_FCIE_ErrHandler_Retry();
					goto LABEL_SEND_CMD;
				}
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
				    "eMMC Err: CMD23 check R1 error: %Xh, retry: %u\n", u32_err, u8_retry_r1);
				eMMC_FCIE_ErrHandler_Stop();
			}
			eMMC_KEEP_RSP(g_eMMCDrv.au8_Rsp, 23);

		}
	}

	eMMC_FCIE_CLK_DIS();
	return u32_err;
}
#endif

U32 eMMC_CMD25(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
	U32 u32_err=eMMC_ST_SUCCESS;
    //U16 u16_cnt;

	#if eMMC_BURST_LEN_AUTOCFG || ENABLE_eMMC_RIU_MODE
	U16 u16_RetryCnt=0;
	LABEL_CMD25:
	#endif
    // ------------------------------RIU mode
	#if defined(ENABLE_eMMC_RIU_MODE) && ENABLE_eMMC_RIU_MODE
	for(u16_cnt=0; u16_cnt<u16_BlkCnt; u16_cnt++)
	{
		u32_err = eMMC_CMD24_CIFD(u32_eMMCBlkAddr+u16_cnt, pu8_DataBuf+(u16_cnt<<eMMC_SECTOR_BYTECNT_BITS));
		if(eMMC_ST_SUCCESS != u32_err)
			goto LABEL_CMD25_END;
	}
	#else
    // ------------------------------MIU mode
	    #if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
	{
	    U16 u16_blk_cnt, u16_blk_pos;

        u16_blk_pos = 0;

	    if(g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen)
	        while(u16_blk_pos < u16_BlkCnt)
            {
	    		u16_blk_cnt = u16_BlkCnt-u16_blk_pos > g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen ?
		    		g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen : u16_BlkCnt-u16_blk_pos;
			    u16_blk_cnt = u16_blk_cnt == g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen ?
				    u16_blk_cnt/2 : u16_blk_cnt;

    			u32_err = eMMC_CMD25_MIU(u32_eMMCBlkAddr+u16_blk_pos,
	    			pu8_DataBuf+(u16_blk_pos<<eMMC_SECTOR_BYTECNT_BITS),
		    		u16_blk_cnt);
		        if(eMMC_ST_SUCCESS != u32_err)
			        goto LABEL_CMD25_END;

    			u16_blk_pos += u16_blk_cnt;
	    	}
        else
		    u32_err = eMMC_CMD25_MIU(u32_eMMCBlkAddr, pu8_DataBuf, u16_BlkCnt);
	}
		#else
	u32_err = eMMC_CMD25_MIU(u32_eMMCBlkAddr, pu8_DataBuf, u16_BlkCnt);
		#endif
	#endif

	#if eMMC_BURST_LEN_AUTOCFG || ENABLE_eMMC_RIU_MODE
	LABEL_CMD25_END:
	if(eMMC_ST_SUCCESS!=u32_err && u16_RetryCnt<eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT)
	{
		u16_RetryCnt++;
		goto LABEL_CMD25;
	}
	#endif

	return u32_err;
}


U32 eMMC_CMD25_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf, U16 u16_BlkCnt)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	U32 u32_arg;
	U8  u8_retry = 0;
	U8  u8_cmd12_sent = 0;

    CMD_RSP_INFO CmdRspInfo;// = {0};
	U32 u32_dma_addr;

	// -------------------------------
	// restore clock to max
	#if 0==IF_IP_VERIFY
	/*if(g_eMMCDrv.u32_DrvFlag&DRV_FLAG_DDR_MODE){
		if(0 == eMMC_IF_TUNING_TTABLE())
		{
			if(eMMC_DDRT_SET_MAX != g_eMMCDrv.DDRTable.u8_CurSetIdx)
				eMMC_FCIE_ApplyDDRTSet(eMMC_DDRT_SET_MAX);
		}
	}
	else{ // SDR Mode
		if(FCIE_DEFAULT_CLK != g_eMMCDrv.u16_ClkRegVal)
			eMMC_clock_setting(FCIE_DEFAULT_CLK);
	}*/
	#endif

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE*u16_BlkCnt);

	CmdRspInfo.Command.Cmd.Index = eMMC_W_MULTIP_BLOCK;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_W;
	CmdRspInfo.DataPath = PATH_DMA;

	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}

	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = u16_BlkCnt;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
	    #if 0
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD25 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_ReInit();
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD25 retry:%u, %Xh \n", u8_retry, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
	    #if 0
		if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_r1++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
		        "eMMC WARN: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);

			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		u32_err = eMMC_ST_ERR_CMD18;
		eMMC_debug(1, 1, "eMMC Err: CMD25 check R1 error: %Xh, Arg: %Xh\n", u32_err, u32_arg);
	    eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	u32_err = eMMC_CMD12(g_eMMCDrv.u16_RCA);
	u8_cmd12_sent = 1;
	if(u32_err) {
		eMMC_debug(1, 1, "eMMC Err: CMD12 fail after CMD25, error: %Xh, Arg: %Xh\n", u32_err, u32_arg);
		goto ErrorHandle;
	}

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(1, 1, "eMMC Err: CMD25 MIU fail, err = %X\n", u32_err);

	// sned CMD12 without check when CMD25 fail for eMMC back to tran-state
	if(u8_cmd12_sent==0) eMMC_CMD12_NoCheck(g_eMMCDrv.u16_RCA);

	return u32_err;

}


U32 eMMC_CMD24(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	//#if defined(ENABLE_eMMC_RIU_MODE)&&ENABLE_eMMC_RIU_MODE
    //return eMMC_CMD24_CIFD(u32_eMMCBlkAddr, pu8_DataBuf);
	//#else
    return eMMC_CMD24_MIU(u32_eMMCBlkAddr, pu8_DataBuf);
	//#endif
}

U32 eMMC_CMD24_MIU(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	U32 u32_arg;
	U8  u8_retry = 0;

    CMD_RSP_INFO CmdRspInfo;// = {0};
	U32 u32_dma_addr;

	// -------------------------------
	// restore clock to max
	#if 0==IF_IP_VERIFY
	/*if(g_eMMCDrv.u32_DrvFlag&DRV_FLAG_DDR_MODE){
		if(0 == eMMC_IF_TUNING_TTABLE())
		{
			if(eMMC_DDRT_SET_MAX != g_eMMCDrv.DDRTable.u8_CurSetIdx)
				eMMC_FCIE_ApplyDDRTSet(eMMC_DDRT_SET_MAX);
		}
	}
	else{ // SDR Mode
		if(FCIE_DEFAULT_CLK != g_eMMCDrv.u16_ClkRegVal)
			eMMC_clock_setting(FCIE_DEFAULT_CLK);
	}*/
	#endif

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);

	CmdRspInfo.Command.Cmd.Index = eMMC_W_SINGLE_BLOCK;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_W;
	CmdRspInfo.DataPath = PATH_DMA;

	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}

	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
	    #if 0
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD25 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_ReInit();
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD24 retry:%u, %Xh \n", u8_retry, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
	    #if 0
		if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_r1++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
		        "eMMC WARN: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);

			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		u32_err = eMMC_ST_ERR_CMD18;
		eMMC_debug(1, 1, "eMMC Err: CMD24 check R1 error: %Xh, Arg: %Xh\n", u32_err, u32_arg);
	    eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(1, 1, "eMMC Err: CMD24 MIU fail, err = %X\n", u32_err);

	return u32_err;

}

U32 eMMC_CMD24_CIFD(U32 u32_eMMCBlkAddr, U8 *pu8_DataBuf)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	U32 u32_arg;
	U8  u8_retry = 0;

    CMD_RSP_INFO CmdRspInfo;// = {0};
	U32 u32_dma_addr;

	// -------------------------------
	// restore clock to max
	#if 0==IF_IP_VERIFY
	/*if(g_eMMCDrv.u32_DrvFlag&DRV_FLAG_DDR_MODE){
		if(0 == eMMC_IF_TUNING_TTABLE())
		{
			if(eMMC_DDRT_SET_MAX != g_eMMCDrv.DDRTable.u8_CurSetIdx)
				eMMC_FCIE_ApplyDDRTSet(eMMC_DDRT_SET_MAX);
		}
	}
	else{ // SDR Mode
		if(FCIE_DEFAULT_CLK != g_eMMCDrv.u16_ClkRegVal)
			eMMC_clock_setting(FCIE_DEFAULT_CLK);
	}*/
	#endif

	u32_arg =  u32_eMMCBlkAddr << (g_eMMCDrv.u8_IfSectorMode?0:eMMC_SECTOR_512BYTE_BITS);

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)pu8_DataBuf, eMMC_SECTOR_512BYTE);

	CmdRspInfo.Command.Cmd.Index = eMMC_W_SINGLE_BLOCK;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(u32_arg);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_W;
	CmdRspInfo.DataPath = PATH_R2N;

	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_1:
			CmdRspInfo.BusWidth = BUS_1_BIT;
			break;
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			break;
	}

	CmdRspInfo.MiuAddr = 0; // R2N don't need this field
	CmdRspInfo.pBufferAddr = (U32*)u32_dma_addr;
	CmdRspInfo.BlockSize = 512;
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err)
	{
	    #if 0
		if(u8_retry_cmd < eMMC_FCIE_CMD_RSP_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_cmd++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC WARN: CMD25 retry:%u, %Xh \n", u8_retry_cmd, u32_err);
			eMMC_FCIE_ErrHandler_ReInit();
			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD24 retry:%u, %Xh \n", u8_retry, u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	u32_err = eMMC_CheckR1Error();
	if(eMMC_ST_SUCCESS != u32_err)
	{
	    #if 0
		if(u8_retry_r1 < eMMC_CMD_API_ERR_RETRY_CNT && 0==eMMC_IF_TUNING_TTABLE())
		{
			u8_retry_r1++;
			eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
		        "eMMC WARN: CMD18 check R1 error: %Xh, Retry: %u, Arg: %Xh\n", u32_err, u8_retry_r1, u32_arg);

			eMMC_FCIE_ErrHandler_Retry();
			goto LABEL_SEND_CMD;
		}
        #endif
		u32_err = eMMC_ST_ERR_CMD18;
		eMMC_debug(1, 1, "eMMC Err: CMD24 check R1 error: %Xh, Arg: %Xh\n", u32_err, u32_arg);
	    eMMC_FCIE_ErrHandler_Stop();
		goto ErrorHandle;
	}

	return eMMC_ST_SUCCESS;

ErrorHandle:

	eMMC_debug(1, 1, "eMMC Err: CMD24 MIU fail, err = %X\n", u32_err);

	return u32_err;

}



#if 1 //defined ENABLE_eMMC_HS200 && ENABLE_eMMC_HS200

static const U8 hs200_tunning_pattern_128[128] = {
    0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xCC, 0xCC, 0xCC, 0x33, 0xCC, 0xCC,
    0xCC, 0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xFF, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xFF, 0xEE, 0xEE, 0xFF,
    0xFF, 0xFF, 0xDD, 0xFF, 0xFF, 0xFF, 0xDD, 0xDD, 0xFF, 0xFF, 0xFF, 0xBB, 0xFF, 0xFF, 0xFF, 0xBB,
    0xBB, 0xFF, 0xFF, 0xFF, 0x77, 0xFF, 0xFF, 0xFF, 0x77, 0x77, 0xFF, 0x77, 0xBB, 0xDD, 0xEE, 0xFF,
    0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xCC, 0xCC, 0xCC, 0x33, 0xCC,
    0xCC, 0xCC, 0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xFF, 0xFF, 0xFF, 0xEE, 0xFF, 0xFF, 0xFF, 0xEE, 0xEE,
    0xFF, 0xFF, 0xFF, 0xDD, 0xFF, 0xFF, 0xFF, 0xDD, 0xDD, 0xFF, 0xFF, 0xFF, 0xBB, 0xFF, 0xFF, 0xFF,
    0xBB, 0xBB, 0xFF, 0xFF, 0xFF, 0x77, 0xFF, 0xFF, 0xFF, 0x77, 0x77, 0xFF, 0x77, 0xBB, 0xDD, 0xEE
};

static const U8 hs200_tunning_pattern_64[64] = {
	0xFF, 0x0F, 0xFF, 0x00, 0xFF, 0xCC, 0xC3, 0xCC, 0xC3, 0x3C, 0xCC, 0xFF, 0xFE, 0xFF, 0xFE, 0xEF,
    0xFF, 0xDF, 0xFF, 0xDD, 0xFF, 0xFB, 0xFF, 0xFB, 0xBF, 0xFF, 0x7F, 0xFF, 0x77, 0xF7, 0xBD, 0xEF,
    0xFF, 0xF0, 0xFF, 0xF0, 0x0F, 0xFC, 0xCC, 0x3C, 0xCC, 0x33, 0xCC, 0xCF, 0xFF, 0xEF, 0xFF, 0xEE,
    0xFF, 0xFD, 0xFF, 0xFD, 0xDF, 0xFF, 0xBF, 0xFF, 0xBB, 0xFF, 0xF7, 0xFF, 0xF7, 0x7F, 0x7B, 0xDE
};


// read out from RIU then compare pattern is slow
U32 eMMC_CMD21_CIFD(void)
{
	return eMMC_ST_SUCCESS;
}

// use memcmp to confirm tuning pattern
U32 eMMC_CMD21_MIU(void)
{
	U8 i;
	U32 u32_dma_addr;
	U32 u32_err = eMMC_ST_SUCCESS;
    CMD_RSP_INFO CmdRspInfo;// = {0};

	if(!(g_eMMCDrv.u8_ECSD196_DevType & BIT4)) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Warn: eMMC not support HS200 1.8V\n");
		u32_err = eMMC_ST_ERR_CMD21_NO_HS200_1_8V;
		goto ErrorHandle;
	}

	u32_dma_addr = eMMC_translate_DMA_address_Ex((U32)gau8_eMMC_SectorBuf, eMMC_SECTOR_512BYTE);

	CmdRspInfo.Command.Cmd.Index = eMMC_SEND_TUNING_BLK;
	CmdRspInfo.Command.Cmd.Arg = U32BEND2LEND(STUFF_BITS);

    CmdRspInfo.CmdType = CMD_TYPE_ADTC;
    CmdRspInfo.RspType = RSP_TYPE_R1;

	CmdRspInfo.ReadWriteDir = DIR_R;
	CmdRspInfo.DataPath = PATH_DMA;

	switch(g_eMMCDrv.u8_BUS_WIDTH)
	{
		case BUS_WIDTH_4:
			CmdRspInfo.BusWidth = BUS_4_BITS;
			CmdRspInfo.BlockSize = 64;
			break;
		case BUS_WIDTH_8:
			CmdRspInfo.BusWidth = BUS_8_BITS;
			CmdRspInfo.BlockSize = 128;
			break;
		case BIT_SD_DATA_WIDTH_1:
		default:
			eMMC_debug(1, 1, "eMMC Err: CMD21 only run at 4 bits or 8 bits data bus\n");
			goto ErrorHandle;
			break;
	}

	CmdRspInfo.MiuAddr = u32_dma_addr;
	CmdRspInfo.pBufferAddr = NULL; // DMA don't need this field
	CmdRspInfo.BlockCount = 1;

    u32_err = HalFcie_SendCommand(&CmdRspInfo);

	if(u32_err) {
		//goto ErrorHandle;
		eMMC_DumpPadClk();
        eMMC_FCIE_DumpRegisters();
        while(1);
	}
	else
	{
		if(g_eMMCDrv.u8_BUS_WIDTH == BUS_WIDTH_4)
        {
            if(memcmp((void*)hs200_tunning_pattern_64, (void*)gau8_eMMC_SectorBuf, 64)) {
			    eMMC_debug(1, 1, "tuning pattern 4bit width:");
			    for(i=0; i<64; i++) {
				    if(i%16==0) eMMC_debug(1, 1, "\n\t");
				    eMMC_debug(1, 1, "%02X ", gau8_eMMC_SectorBuf[i]);
			    }
			    eMMC_debug(1, 1, "\n");
			    u32_err = eMMC_ST_ERR_CMD21_DATA_CMP;
			    goto ErrorHandle;
		    }
        }
        else if(g_eMMCDrv.u8_BUS_WIDTH == BUS_WIDTH_8)
        {
		    if(memcmp((void*)hs200_tunning_pattern_128, (void*)gau8_eMMC_SectorBuf, 128)) {
			    eMMC_debug(1, 1, "tuning pattern 8bit width:");
			    for(i=0; i<128; i++) {
				    if(i%16==0) eMMC_debug(1, 1, "\n\t");
				    eMMC_debug(1, 1, "%02X ", gau8_eMMC_SectorBuf[i]);
			    }
			    eMMC_debug(1, 1, "\n");
			    u32_err = eMMC_ST_ERR_CMD21_DATA_CMP;
			    goto ErrorHandle;
		    }
        }
	}

	u32_err = eMMC_CheckR1Error();

	if(u32_err)
	{
	    eMMC_FCIE_ErrHandler_ReInit();
	}

    /*if( g_eMMCDrv.u8_check_last_blk_crc )
    {
        eMMC_dump_mem(FCIE_CRC_BASE, 0x40);
        //crc16(0, pu8_DataBuf, 512)
    }*/

	return eMMC_ST_SUCCESS;

ErrorHandle:

	//REG_FCIE_W(FCIE_SDIO_CTRL, BIT_SDIO_BLK_MODE | eMMC_SECTOR_512BYTE); // restore anyway...
	REG_FCIE_W(FCIE_BLK_SIZE,  eMMC_SECTOR_512BYTE);

	if(u32_err)
		eMMC_debug(1, 1, "[%s] L: %d --> %s() error %08Xh\n", __FILE__, __LINE__, __FUNCTION__, u32_err);

	return u32_err;

}

// eMMC CMD21 adtc, R1, fix 128 clock, for HS200 only
//  64 bytes in 4 bits mode
// 128 bytes in 8 bits mode

U32 eMMC_CMD21(void) // send tuning block
{
#if 1
	return eMMC_CMD21_MIU(); // fast
#else
	return eMMC_CMD21_CIFD(); // slow
#endif
}

#define BIT0_DRIVING_1_00X	BIT0 // 1.00 X
#define BIT1_DRIVING_1_50X	BIT1 // 1.50 X
#define BIT2_DRIVING_0_75X	BIT2 // 0.75 X
#define BIT3_DRIVING_0_50X	BIT3 // 0.50 X

#define BITS_DRIVING_TUNING	(BIT3|BIT2|BIT1)

U32 eMMC_TuningHS200_DriverStrength(void)
{
	U32 u32_err = 0;
	U8 u8DrivingTuningResult = 0;
	//U8 u8DrivingCapability = g_eMMCDrv.u8_ECSD197_DriverStrength;

	if(!(g_eMMCDrv.u8_ECSD197_DriverStrength & 0x0E)) { // if support driver strength adjust
		return eMMC_ST_ERR_CMD21_NO_DRVING;
	}

	if(eMMC_SetDrivingStrength(eMMC_DRIVING_TYPE0)) {
		goto ErrorHandle;
	}
	//eMMC_ExtCSD_Config();
	if(eMMC_CMD21()==eMMC_ST_SUCCESS) {
		u8DrivingTuningResult |= BIT0_DRIVING_1_00X;
	}

	if(g_eMMCDrv.u8_ECSD197_DriverStrength & BIT1_DRIVING_1_50X) {
		if(eMMC_SetDrivingStrength(eMMC_DRIVING_TYPE1)) {
			goto ErrorHandle;
		}
		//eMMC_ExtCSD_Config();
		if(eMMC_CMD21()==eMMC_ST_SUCCESS) {
			u8DrivingTuningResult |= BIT1_DRIVING_1_50X;
		}
	}
	if(g_eMMCDrv.u8_ECSD197_DriverStrength & BIT2_DRIVING_0_75X) {
		if(eMMC_SetDrivingStrength(eMMC_DRIVING_TYPE2)) {
			goto ErrorHandle;
		}
		//eMMC_ExtCSD_Config();
		if(eMMC_CMD21()==eMMC_ST_SUCCESS) {
			u8DrivingTuningResult |= BIT2_DRIVING_0_75X;
		}
	}
	if(g_eMMCDrv.u8_ECSD197_DriverStrength & BIT3_DRIVING_0_50X) {
		if(eMMC_SetDrivingStrength(eMMC_DRIVING_TYPE3)) {
			goto ErrorHandle;
		}
		//eMMC_ExtCSD_Config();
		if(eMMC_CMD21()==eMMC_ST_SUCCESS) {
			u8DrivingTuningResult |= BIT3_DRIVING_0_50X;
		}
	}

	// switch back default driving
	if(eMMC_SetDrivingStrength(eMMC_DRIVING_TYPE0)) {
		goto ErrorHandle;
	}

	eMMC_debug(1, 1, "eMMC support %s%s%s%s\n", (u8DrivingTuningResult&BIT0_DRIVING_1_00X)?"1.00X ":""
					, (u8DrivingTuningResult&BIT1_DRIVING_1_50X)?"1.50X ":""
					, (u8DrivingTuningResult&BIT2_DRIVING_0_75X)?"0.75X ":""
					, (u8DrivingTuningResult&BIT3_DRIVING_0_50X)?"0.50X ":"");

	if(u8DrivingTuningResult) return eMMC_ST_SUCCESS; // at least 1 type success

ErrorHandle:

	eMMC_debug(1, 1, "eMMC Err: %s() fail %Xh\n", __FUNCTION__, u32_err);
	eMMC_die("\n");

	return u32_err;
}

#if defined ENABLE_eMMC_ATOP && ENABLE_eMMC_ATOP

U32 eMMC_SlectBestSkew4(U32 u32_Candidate)
{
	U32 u32_i;
	U8 u8_edge = 0;
	U32 u32LatchOKStart = 0xBEEF, u32LatchOKEnd = 0xBEEF, u32_LatchBestSelect = 0;

	if(!u32_Candidate) {
		eMMC_debug(1, 1, "ATOP fail: no workable skew4\n");
		eMMC_die("\n");
	}

	u32_Candidate<<=1; // bit 0~15 --> bit 1~16, add 0 former and later

	for(u32_i=0; u32_i<18; u32_i++) {
		if( (u32_Candidate&(1<<u32_i)) ^ ((u32_Candidate>>1)&(1<<u32_i)) ) { // use XOR to find 0b01/0b10 edge
			u8_edge++;
			//printf("%d[%04Xh ^ %04Xh] = %04Xh ", u32_i, (u32_Candidate&(1<<u32_i)), ((u32_Candidate>>1)&(1<<u32_i)), ( (u32_Candidate&(1<<u32_i)) ^ ((u32_Candidate>>1)&(1<<u32_i)) ) );
			if(u32LatchOKStart==0xBEEF) {
				u32LatchOKStart = u32_i;
			} else if(u32LatchOKEnd==0xBEEF) {
				u32LatchOKEnd = u32_i;
			}
		}
	}

	u32_Candidate>>=1; // bit 1~16 --> bit 0~15
	u32LatchOKEnd--;

	if(u8_edge==2) { // only 1 continuous workable skew4 group
		if( (u32LatchOKStart==0 && u32LatchOKEnd==0) || (u32LatchOKStart==15 && u32LatchOKEnd==15) ) {
			eMMC_debug(1, 1, "ATOP warn: %04Xh (%d ~ %d)\n", u32_Candidate, u32LatchOKStart, u32LatchOKEnd);

		} else {
			eMMC_debug(1, 1, "ATOP success: %04Xh (%d ~ %d)\n", u32_Candidate, u32LatchOKStart, u32LatchOKEnd);
		}
	} else {
		eMMC_debug(1, 1, "ATOP fail: not continuous: %04Xh, u8_edge: %d (%d ~ %d)\n", u32_Candidate, u8_edge, u32LatchOKStart, u32LatchOKEnd);
		eMMC_die("\n");
	}

	// select best skew4
	if((u32LatchOKStart + u32LatchOKEnd)%2) { // odd

		u32_LatchBestSelect = (u32LatchOKStart + u32LatchOKEnd) >> 1;
		//u32_LatchBestSelect++; // select later

	} else { // even

		u32_LatchBestSelect = (u32LatchOKStart + u32LatchOKEnd) >> 1;
	}
	eMMC_debug(1, 1, "Best skew4: %d\n", u32_LatchBestSelect);

	return u32_LatchBestSelect;
}

U32 eMMC_TuningDDR52_Skew(void) // change skew 4 and do write read compare
{
	// not implement yet...
	eMMC_die("\n");
	return 0;
}

U32 eMMC_TuningHS200_Skew(void) // change skew 4 and read tuning pattern
{
    #if 0
	RIU_EMMCPLL * const pRegEmmcPll = (RIU_EMMCPLL *)EMMC_PLL_BASE;
	U32 u32_i;
	U32 u32_err = 0;
	U32 u32_Skew4Result = 0;

	printf("%s(%04Xh) --> ", __FUNCTION__, u32_Skew4Result);
	for(u32_i=0; u32_i<16; u32_i++) {
		pRegEmmcPll->reg_emmc_pll_clkph_skew4 = u32_i;

		u32_err = eMMC_CMD21();
		printf("skew %d: %s\n", u32_i, (u32_err)?"NG":"OK");
		if(!u32_err) u32_Skew4Result |= (1<<u32_i);
	}

	pRegEmmcPll->reg_emmc_pll_clkph_skew4 = eMMC_SlectBestSkew4(u32_Skew4Result);
    #endif
	if(eMMC_CMD21())
    {
        eMMC_DumpPadClk();
        eMMC_FCIE_DumpRegisters();
        eMMC_die("\n"); // confirm 1 more time
    }

	return 0;

}

// can not use CMD21 for timing tuning, do normal write read compare
/*U32 eMMC_ATOP_EnableDDR52(void)
{
	U32 u32_err;

	u32_err = eMMC_SetBusWidth(8, 1); // config ExtCSD[183] BUS_WIDTH
	if(eMMC_ST_SUCCESS != u32_err) {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
			"eMMC Err: set device 8b DDR fail: %Xh\n", u32_err);
		return u32_err;
	}

	eMMC_pads_switch(EMMC_DDR52_MODE);
	eMMC_clock_setting(BIT_FCIE_CLK_52M);

	if(eMMC_TuningDDR52_Skew()==eMMC_ST_SUCCESS) return eMMC_ST_SUCCESS;

	return 0;
}

U32 eMMC_ATOP_EnableHS200(void)
{
	U32 u32_err;

	u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HS200); // config ExtCSD[185] HS_TIMING
	if(u32_err) {
		eMMC_debug(1, 1, "switch 2 HS200 fail\n");
	}
    else
        eMMC_debug(1, 1, "\033[7;33mSwitch to HS200 ok\033[m\n");

	eMMC_pads_switch(EMMC_HS200_MODE);

	eMMC_clock_setting(FCIE_HS200_CLK);

	if(eMMC_TuningHS200_Skew()==eMMC_ST_SUCCESS) return eMMC_ST_SUCCESS;

	if(eMMC_TuningHS200_DriverStrength()==eMMC_ST_SUCCESS) return eMMC_ST_SUCCESS; // test?

	return eMMC_ST_ERR_CMD21_HS200_FAIL;
}
*/
#endif // ENABLE_eMMC_ATOP
#endif // ENABLE_eMMC_HS200

#if defined(eMMC_BURST_LEN_AUTOCFG) && eMMC_BURST_LEN_AUTOCFG
void eMMC_DumpBurstLenTable(void)
{
	eMMC_debug(eMMC_DEBUG_LEVEL,0,"eMMC Burst Len: \n");
	eMMC_debug(eMMC_DEBUG_LEVEL,0,"  best:  %4u blks, %4u.%u MB/s \n",
		g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen,
		g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSec, g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSecPoint);
    eMMC_debug(eMMC_DEBUG_LEVEL,0,"  worst: %4u blks, %4u.%u MB/s \n",
		g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen,
		g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSec, g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSecPoint);
}

U32 eMMC_LoadBurstLenTable(void)
{
	U32 u32_err, u32_ErrRetry=0;
	U32 u32_ChkSum;

	LABEL_RETRY:
	u32_err = eMMC_CMD18(eMMC_BURST_LEN_BLK_0, gau8_eMMC_SectorBuf, 1);
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC WARN: load Burst Len Table fail, %Xh\n", u32_err);
		goto LABEL_END_OF_NO_TABLE;
	}

	memcpy((U8*)&g_eMMCDrv.BurstWriteLen_t, gau8_eMMC_SectorBuf, sizeof(g_eMMCDrv.BurstWriteLen_t));
	u32_ChkSum = eMMC_ChkSum((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t)-4);
	if(u32_ChkSum != g_eMMCDrv.BurstWriteLen_t.u32_ChkSum ||
		0 == g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: no Burst Len Table. ChkSum: %Xh, BestLen: %Xh\n",
			g_eMMCDrv.BurstWriteLen_t.u32_ChkSum, g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen);
		u32_err = eMMC_ST_ERR_BLEN_CHKSUM;
		goto LABEL_END_OF_NO_TABLE;
	}

	if(u32_ErrRetry)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL,0,"eMMC: retry ok\n");
		//eMMC_dump_mem((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t));
	}
	return u32_err;

	// ---------------------------------
	LABEL_END_OF_NO_TABLE:

	if(0==u32_ErrRetry)
	{
		//eMMC_dump_mem((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t));
		u32_ErrRetry++;
		goto LABEL_RETRY;
	}
	return u32_err;
}

#define MAX_DETECT_BLK_CNT   2048 // 0.5MB
U32 eMMC_SaveBurstLenTable(void)
{
	U32 u32_Err;
	U32 u32_t0, u32_t1, u32_tMax=0, u32_tMin=(U32)(0-1), u32_tmp;
	U16 u16_BurstBlkCnt, u16_BestBlkCnt=0, u16_WorstBlkCnt=0;
	U16 u16_i;

	//eMMC_debug(eMMC_DEBUG_LEVEL,0,"\neMMC: burst len...\n");
	// --------------------------
	g_eMMCDrv.BurstWriteLen_t.u32_ChkSum = ~g_eMMCDrv.BurstWriteLen_t.u32_ChkSum;
	g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen = 0;
	g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen = 0;

	//eMMC_CMD25(eMMC_TEST_BLK_0, gau8_eMMC_SectorBuf, eMMC_TEST_BLK_CNT);

	// --------------------------
	u16_BurstBlkCnt = 0;
	LABEL_DETECT:
	switch(u16_BurstBlkCnt)
	{
		//case 0:   u16_BurstBlkCnt = 8;  break; // 4KB
		case 0:   u16_BurstBlkCnt = 16;  break;// 8KB
		case 16:  u16_BurstBlkCnt = 32;  break;//16KB
		case 32:  u16_BurstBlkCnt = 64;  break;//32KB
		case 64:  u16_BurstBlkCnt = 128;  break;//64KB
		case 128: u16_BurstBlkCnt = 256;  break;//128KB
		case 256: u16_BurstBlkCnt = MAX_DETECT_BLK_CNT;
	}
	eMMC_hw_timer_start();
	u32_t0 = eMMC_hw_timer_tick();
	for(u16_i=0; u16_i<MAX_DETECT_BLK_CNT/u16_BurstBlkCnt; u16_i++)
	{
	    u32_Err= eMMC_CMD25(eMMC_TEST_BLK_0, gau8_eMMC_SectorBuf, u16_BurstBlkCnt);
	    if(eMMC_ST_SUCCESS != u32_Err)
	    {
		    eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: w fail: %Xh\n", u32_Err);
		    goto LABEL_END;
	    }
	}
	eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH);
	u32_t1 = eMMC_hw_timer_tick();
	//eMMC_debug(0,0,"\n%u-%u=%8u, %3u ", u32_t1, u32_t0, u32_t1-u32_t0, u16_BurstBlkCnt);

	if(u32_tMin > u32_t1-u32_t0)
	{
		u32_tMin = u32_t1-u32_t0;
		u16_BestBlkCnt = u16_BurstBlkCnt;
	}
	if(u32_tMax < u32_t1-u32_t0)
	{
		u32_tMax = u32_t1-u32_t0;
		u16_WorstBlkCnt = u16_BurstBlkCnt;
	}

	if(MAX_DETECT_BLK_CNT != u16_BurstBlkCnt)
		goto LABEL_DETECT;

	// --------------------------
	g_eMMCDrv.BurstWriteLen_t.u16_BestBrustLen = u16_BestBlkCnt;
	g_eMMCDrv.BurstWriteLen_t.u16_WorstBrustLen = u16_WorstBlkCnt;

	u32_tmp = (U32)(MAX_DETECT_BLK_CNT<<eMMC_SECTOR_512BYTE_BITS)*4000 /
		(u32_tMin/(eMMC_HW_TIMER_HZ/4000));
	u32_tmp /= 0x100000/10;
	g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSec = u32_tmp/10;
	g_eMMCDrv.BurstWriteLen_t.u16_BestMBPerSecPoint = u32_tmp%10;

	u32_tmp = (U32)(MAX_DETECT_BLK_CNT<<eMMC_SECTOR_512BYTE_BITS)*4000 /
		(u32_tMax/(eMMC_HW_TIMER_HZ/4000));
	u32_tmp /= 0x100000/10;
	g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSec = u32_tmp/10;
	g_eMMCDrv.BurstWriteLen_t.u16_WorstMBPerSecPoint = u32_tmp%10;

	g_eMMCDrv.BurstWriteLen_t.u32_ChkSum =
		eMMC_ChkSum((U8*)&g_eMMCDrv.BurstWriteLen_t, sizeof(g_eMMCDrv.BurstWriteLen_t)-4);

	u32_Err= eMMC_CMD25(eMMC_BURST_LEN_BLK_0, (U8*)&g_eMMCDrv.BurstWriteLen_t, 1);
	if(eMMC_ST_SUCCESS != u32_Err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: save fail: %Xh\n", u32_Err);
		goto LABEL_END;
	}

	// --------------------------
	LABEL_END:
	return u32_Err;

}
#endif

#ifdef STATIC_RELIABLE_TEST
extern int reliable_test_sleep; //ms
extern int enable_pm_sleep_flag;
#endif


U32 eMMC_CheckR1Error(void)
{
	U32 u32_err = eMMC_ST_SUCCESS;
	//U8 u8_cs = 0;

	eMMC_FCIE_GetCMDFIFO(0, 3, (U16*)g_eMMCDrv.au8_Rsp);

	if(g_eMMCDrv.au8_Rsp[1] & (eMMC_ERR_R1_31_24>>24))
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_31_24 \n ");
		u32_err = eMMC_ST_ERR_R1_31_24;
		goto LABEL_CHECK_R1_END;
	}

	if(g_eMMCDrv.au8_Rsp[2] & (eMMC_ERR_R1_23_16>>16))
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_23_16 \n ");
		u32_err = eMMC_ST_ERR_R1_23_16;
		goto LABEL_CHECK_R1_END;
	}

	if(g_eMMCDrv.au8_Rsp[3] & (eMMC_ERR_R1_15_8>>8))
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_15_8 \n ");
		u32_err = eMMC_ST_ERR_R1_15_8;
		goto LABEL_CHECK_R1_END;
	}

	if(g_eMMCDrv.au8_Rsp[4] & (eMMC_ERR_R1_7_0>>0))
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: eMMC_ST_ERR_R1_7_0 \n ");
		u32_err = eMMC_ST_ERR_R1_7_0;
		goto LABEL_CHECK_R1_END;
	}

LABEL_CHECK_R1_END:

	/*u8_cs = (eMMC_FCIE_CmdRspBufGet(3) & (eMMC_R1_CURRENT_STATE>>8))>>1;
	printf("card state: %d ", u8_cs);
	switch(u8_cs) {
		case 0:		printf("(idle)\n");	break;
		case 1:		printf("(ready)\n");	break;
		case 2:		printf("(ident)\n");	break;
		case 3:		printf("(stby)\n");	break;
		case 4:		printf("(tran)\n");	break;
		case 5:		printf("(data)\n");	break;
		case 6:		printf("(rcv)\n");	break;
		case 7:		printf("(prg)\n");	break;
		case 8:		printf("(dis)\n");	break;
		default:	printf("(?)\n");	break;
	}*/

	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_dump_mem(g_eMMCDrv.au8_Rsp, eMMC_R1_BYTE_CNT);

		if(24==g_eMMCDrv.au8_Rsp[0] || 25==g_eMMCDrv.au8_Rsp[0] ||
		   18==g_eMMCDrv.au8_Rsp[0] || 12==g_eMMCDrv.au8_Rsp[0])
			eMMC_FCIE_ErrHandler_ReInit();
	}
	return u32_err;
}


// set eMMC device & pad registers (no macro timing registers, since also involved in tuning procedure)
#if 0
U32 eMMC_FCIE_EnableFastMode_Ex(U8 u8_PadType)
{
	U32 u32_err=eMMC_ST_SUCCESS;

	switch(u8_PadType)
	{
		case FCIE_eMMC_DDR:
			u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HIGH);
			if(eMMC_ST_SUCCESS!=u32_err)
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: enable HighSpeed fail: %Xh\n", u32_err);
				return u32_err;
			}
			u32_err = eMMC_SetBusWidth(8, 1);
			if(eMMC_ST_SUCCESS!=u32_err)
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: enable DDR fail: %Xh\n", u32_err);
				return u32_err;
			}

			if(0==g_eMMCDrv.TimingTable_t.u8_SetCnt)
				#if defined(ENABLE_eMMC_ATOP)&&ENABLE_eMMC_ATOP
				eMMC_clock_setting(gau8_eMMCPLLSel_52[0]);
				#else
                eMMC_clock_setting(gau8_FCIEClkSel[0]);
				#endif

			break;

		#if 1 //defined(ENABLE_eMMC_HS200)&&ENABLE_eMMC_HS200
		case FCIE_eMMC_HS200:
			u32_err = eMMC_SetBusWidth(8, 0); // disable DDR
			if(eMMC_ST_SUCCESS!=u32_err)
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: HS200 disable DDR fail: %Xh\n", u32_err);
				return u32_err;
			}
			u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HS200);
			if(eMMC_ST_SUCCESS!=u32_err)
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: enable HS200 fail: %Xh\n", u32_err);
				return u32_err;
			}
			//if(0==g_eMMCDrv.TimingTable_t.u8_SetCnt)
				eMMC_clock_setting(gau8_eMMCPLLSel_200[0]);

			break;
		#endif

		#if 1 //defined(ENABLE_eMMC_HS400)&&ENABLE_eMMC_HS400
		case FCIE_eMMC_HS400:
        case FCIE_eMMC_HS400_DS:
			u32_err = eMMC_SetBusWidth(8, 1); // enable DDR
			if(eMMC_ST_SUCCESS!=u32_err)
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: HS200 disable DDR fail: %Xh\n", u32_err);
				return u32_err;
			}
            u32_err = eMMC_SetBusSpeed(eMMC_SPEED_HS400);
			if(eMMC_ST_SUCCESS!=u32_err)
			{
				eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: enable HS200 fail: %Xh\n", u32_err);
				return u32_err;
			}
			//if(0==g_eMMCDrv.TimingTable_t.u8_SetCnt)
				eMMC_clock_setting(gau8_eMMCPLLSel_200[0]);
			break;
		#endif
	}

	// --------------------------------------
	if(eMMC_ST_SUCCESS != u32_err)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,
			"eMMC Err: set ECSD fail: %Xh\n", u32_err);
		return u32_err;
	}

	g_eMMCDrv.u16_Reg10_Mode &= ~BIT_DATA_SYNC;

	//if(g_eMMCDrv.TimingTable_t.u8_SetCnt)
	//	eMMC_FCIE_ApplyTimingSet(eMMC_TIMING_SET_MAX);
	//if(FCIE_eMMC_HS400 != u8_PadType)
	    eMMC_pads_switch(u8_PadType);

	return u32_err;
}
#endif

// ====================================================
#if defined(eMMC_UPDATE_FIRMWARE) && (eMMC_UPDATE_FIRMWARE)
#define  UPFW_SEC_WIAT_CNT   0x1000000
#define  UPFW_SEC_BYTE_CNT   (128*1024)
static U32 eMMC_UpFW_Samsung_Wait(void)
{
	U32 u32_err, u32_cnt, u32_st;

	for(u32_cnt=0; u32_cnt<UPFW_SEC_WIAT_CNT; u32_cnt++)
	{
		eMMC_CMD13(g_eMMCDrv.u16_RCA);
		//eMMC_dump_mem(g_eMMCDrv.au8_Rsp, 6);
		u32_st = (g_eMMCDrv.au8_Rsp[1]<<24) | (g_eMMCDrv.au8_Rsp[2]<<16) |
			(g_eMMCDrv.au8_Rsp[3]<<8) | (g_eMMCDrv.au8_Rsp[4]<<0);
		if(0x900 == u32_st)
			break;
		else
			eMMC_debug(eMMC_DEBUG_LEVEL,0,"st: %Xh\n", u32_st);
		eMMC_hw_timer_delay(HW_TIMER_DELAY_1ms);
	}

	if(UPFW_SEC_WIAT_CNT == u32_cnt)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR,1,"eMMC Err: %Xh\n", eMMC_ST_ERR_SEC_UPFW_TO);
		return eMMC_ST_ERR_SEC_UPFW_TO;
	}
	return eMMC_ST_SUCCESS;
}

U32 eMMC_UpFW_Samsung(U8 *pu8_FWBin)
{
	U16 u16_ctrl;
	U32 u32_err, u32_arg=0xEFAC60FC;

	// ---------------------------
	LABEL_CMD60:
	eMMC_debug(eMMC_DEBUG_LEVEL,0,"CMD60: %Xh\n", u32_arg);
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, u32_arg, 60, eMMC_R1b_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD60 fail, %Xh \n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }
	u32_err = eMMC_UpFW_Samsung_Wait();
	if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 1, Arg:%Xh \n", u32_arg);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }
	if(0xEFAC60FC == u32_arg)
	{
		u32_arg=0xCBAD1160;
		goto LABEL_CMD60;
	}

	#if 1
	// ---------------------------
	eMMC_debug(eMMC_DEBUG_LEVEL,0,"erase ... \n");
	g_eMMCDrv.u32_eMMCFlag &= ~eMMC_FLAG_TRIM;
    u32_err = eMMC_EraseCMDSeq(0, 0);
	if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: erase fail, %Xh \n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }
	u32_err = eMMC_UpFW_Samsung_Wait();
	if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 2, %Xh \n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }
	#endif

	// ---------------------------
	eMMC_debug(eMMC_DEBUG_LEVEL,0,"write ... \n");
	u32_err = eMMC_CMD25_MIU(0, pu8_FWBin, UPFW_SEC_BYTE_CNT>>eMMC_SECTOR_512BYTE_BITS);
    if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: write fail, %Xh \n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }
	u32_err = eMMC_UpFW_Samsung_Wait();
	if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 3, %Xh \n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }

	// ---------------------------
	eMMC_debug(eMMC_DEBUG_LEVEL,0,"close ... \n");
	u16_ctrl = BIT_SD_CMD_EN | BIT_SD_RSP_EN;

	eMMC_FCIE_ClearEvents();
	u32_err = eMMC_FCIE_SendCmd(
		g_eMMCDrv.u16_Reg10_Mode, u16_ctrl, 0, 28, eMMC_R1b_BYTE_CNT);
    if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: CMD28 fail, %Xh \n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }
	u32_err = eMMC_UpFW_Samsung_Wait();
	if(eMMC_ST_SUCCESS != u32_err)
    {
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: timeout 4, %Xh \n", u32_err);
		eMMC_FCIE_ErrHandler_Stop();
		goto LABEL_END_OF_UPFW;
    }

	LABEL_END_OF_UPFW:
	return u32_err;

}
#endif // eMMC_UPDATE_FIRMWARE

#endif // UNIFIED_eMMC_DRIVER

#endif // IP_FCIE_VERSION_5

