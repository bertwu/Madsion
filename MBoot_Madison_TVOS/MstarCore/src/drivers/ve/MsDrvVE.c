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

//--------------------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------------------
#include <common.h>
#include <MsCommon.h>
#include <drvTVEncoder.h>
#include <uboot_mmap.h>
#include <MsMmap.h>
#include <MsDebug.h>
#include <apiPNL.h>
#include <apilth.h>
#include <apiXC.h>
#include <apiXC_Adc.h>

#include <apiGOP.h>
#include <ve/MsDrvVE.h>
#include <panel/MsDrvPanel.h>


//-------------------------------------------------------------------------------------------------
//  Local Compiler Options
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// Local Defines
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Local Variables
//--------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
static MS_VE_VIDEOSYS getVEVideoSys(HDMITX_VIDEO_TIMING outPutType)
{
    switch (outPutType)
    {
        case HDMITX_RES_640x480p:
        case HDMITX_RES_720x480i:
        case HDMITX_RES_720x480p:
        case HDMITX_RES_1280x720p_60Hz:
        case HDMITX_RES_1920x1080i_60Hz:
        case HDMITX_RES_1920x1080p_24Hz:
        case HDMITX_RES_1920x1080p_30Hz:
        case HDMITX_RES_1920x1080p_60Hz:
        case HDMITX_RES_4K2Kp_30Hz:
        case HDMITX_RES_1280x1470p_60Hz:
        case HDMITX_RES_1280x1470p_24Hz:
        case HDMITX_RES_1280x1470p_30Hz:
        case HDMITX_RES_1920x2205p_24Hz:
        case HDMITX_RES_1920x2205p_30Hz:
        case HDMITX_RES_4K2Kp_25Hz:
        case HDMITX_RES_MAX:
            
            return MS_VE_NTSC;
            
        case HDMITX_RES_720x576i:
        case HDMITX_RES_720x576p:
        case HDMITX_RES_1280x720p_50Hz:
        case HDMITX_RES_1920x1080i_50Hz:
        case HDMITX_RES_1920x1080p_25Hz:
        case HDMITX_RES_1920x1080p_50Hz:
        case HDMITX_RES_1280x1470p_50Hz:
            
            return MS_VE_PAL;
        default:
            UBOOT_ERROR("ERROR: Not support current panel resolution!\n");
            break;
    }

    return MS_VE_VIDEOSYS_NUM;
}

static MS_U16 getFrameRates(HDMITX_VIDEO_TIMING outPutType)
{
    switch (outPutType)
    {
        case HDMITX_RES_640x480p:
        case HDMITX_RES_720x480i:
        case HDMITX_RES_720x480p:
        case HDMITX_RES_1280x720p_60Hz:
        case HDMITX_RES_1920x1080i_60Hz:
        case HDMITX_RES_1920x1080p_24Hz:
        case HDMITX_RES_1920x1080p_30Hz:
        case HDMITX_RES_1920x1080p_60Hz:
        case HDMITX_RES_4K2Kp_30Hz:
        case HDMITX_RES_1280x1470p_60Hz:
        case HDMITX_RES_1280x1470p_24Hz:
        case HDMITX_RES_1280x1470p_30Hz:
        case HDMITX_RES_1920x2205p_24Hz:
        case HDMITX_RES_1920x2205p_30Hz:
        case HDMITX_RES_MAX:
            return 6000 / 2;
        case HDMITX_RES_720x576i:
        case HDMITX_RES_720x576p:
        case HDMITX_RES_1280x720p_50Hz:
        case HDMITX_RES_1920x1080i_50Hz:
        case HDMITX_RES_1920x1080p_25Hz:
        case HDMITX_RES_1920x1080p_50Hz:
        case HDMITX_RES_1280x1470p_50Hz:
        default:
            break;
    }

    return 5000 / 2;
}

static void MsDrv_OSDC_init(void)
{
    UBOOT_TRACE("IN\n");

    MS_XC_OSDC_CTRL_INFO pstOC_Ctrl;
    
    pstOC_Ctrl.bOC_ClK_En = TRUE;
    pstOC_Ctrl.bOC_Mixer_Bypass_En = DISABLE;
    pstOC_Ctrl.bOC_Mixer_InvAlpha_En = ENABLE;
    pstOC_Ctrl.bOC_Mixer_Hsync_Vfde_Out = DISABLE;
    pstOC_Ctrl.bOC_Mixer_Hfde_Vfde_Out = ENABLE;
    pstOC_Ctrl.u16OC_Lpll_type=getLinkExtType();
#if defined (CONFIG_URSA7_VB1) && (CONFIG_URSA7_VB1 == 1)
    pstOC_Ctrl.u8OC_OutputFormat = 1;
#else
    pstOC_Ctrl.u8OC_OutputFormat = 0;
#endif

    if( LINK_HS_LVDS == pstOC_Ctrl.u16OC_Lpll_type)
    {
        UBOOT_DEBUG("\n OC Set to LINK_HS_LVDS (1920x1080)\n");
        MApi_XC_OSDC_InitSetting(E_XC_OSDC_TGEN_1920x1080, NULL, &pstOC_Ctrl);
    }
    else if(LINK_VBY1_10BIT_2LANE == pstOC_Ctrl.u16OC_Lpll_type)
    {
        UBOOT_DEBUG("\n OC Set to 2LANE (1920x1080)\n");
        MApi_XC_OSDC_InitSetting(E_XC_OSDC_TGEN_1920x1080, NULL, &pstOC_Ctrl);
        UBOOT_DEBUG("setup OSDC Vfreqx10 %u\n",600);
        MApi_XC_OSDC_SetOutVfreqx10(600);
    }
    else if(LINK_VBY1_10BIT_4LANE == pstOC_Ctrl.u16OC_Lpll_type)
    {
        UBOOT_DEBUG("\n OC Set to 4LANE (3840x2160)\n");
        MApi_XC_OSDC_InitSetting(E_XC_OSDC_TGEN_3840x2160, NULL, &pstOC_Ctrl);
        UBOOT_DEBUG("setup OSDC Vfreqx10 %u\n",300);
        MApi_XC_OSDC_SetOutVfreqx10(300);
    }
    MApi_XC_OSDC_Control(E_XC_OSDC_INIT);
    UBOOT_TRACE("OUT\n");

}

MS_BOOL mvideo_sc_is_interlace(void)
{
    return 0;
}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
///Entry function
//--------------------------------------------------------------------------------------------------
int MsDrv_VE_init(HDMITX_VIDEO_TIMING outPutType)
{

    U32 u32Addr=0,u32Size=0;
	XC_INITDATA sXC_InitData;
    XC_INITDATA *pstXC_InitData= &sXC_InitData;
    UBOOT_TRACE("IN\n");
    
    // reset to zero

    memset(&sXC_InitData, 0, sizeof(sXC_InitData));

    // Init XC
		// (OBA2!=1) // remove when XC driver update
    // Check library version. Do not modify this statement please.
    pstXC_InitData->u32XC_version = XC_INITDATA_VERSION;

    pstXC_InitData->u32XTAL_Clock = MST_XTAL_CLOCK_HZ;
    if(get_addr_from_mmap("E_MMAP_ID_XC_MAIN_FB", &u32Addr)!=0)
    {
        UBOOT_ERROR("get E_MMAP_ID_XC_MAIN_FB mmap fail\n");
    }
    if(u32Addr==0xFFFF)
    {
        UBOOT_ERROR("get E_MMAP_ID_XC_MAIN_FB mmap fail\n");
        return -1;
    }
    get_length_from_mmap("E_MMAP_ID_XC_MAIN_FB", (U32 *)&u32Size);
    UBOOT_DEBUG("E_MMAP_ID_XC_MAIN_FB 0x%x \n",u32Addr);

    pstXC_InitData->u32Main_FB_Size = u32Size; //SCALER_DNR_BUF_LEN;
    pstXC_InitData->u32Main_FB_Start_Addr = u32Addr;//((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR));

    // Init DNR Address in Main & Sub channel. Keep the same. If project support FB PIP mode, set Sub DNR Address in AP layer (eg. mapp_init).
    pstXC_InitData->u32Sub_FB_Size = pstXC_InitData->u32Main_FB_Size;
    pstXC_InitData->u32Sub_FB_Start_Addr = pstXC_InitData->u32Main_FB_Start_Addr;

    // Chip related.
    pstXC_InitData->bIsShareGround = ENABLE;
    // (OBA2!=1) // remove when XC driver update
    // Board related
    pstXC_InitData->eScartIDPort_Sel = SCART_ID_SEL;//SCART_ID_SEL | SCART2_ID_SEL ;

    pstXC_InitData->bCEC_Use_Interrupt = FALSE;

    pstXC_InitData->bEnableIPAutoCoast = 0;

    pstXC_InitData->bMirror = FALSE;
  

    // panel info 
    pstXC_InitData->stPanelInfo.u16HStart = g_IPanel.HStart();      // DE H start
    pstXC_InitData->stPanelInfo.u16VStart = g_IPanel.VStart();
    pstXC_InitData->stPanelInfo.u16Width  = g_IPanel.Width();
    pstXC_InitData->stPanelInfo.u16Height = g_IPanel.Height();
    pstXC_InitData->stPanelInfo.u16HTotal = g_IPanel.HTotal();
    pstXC_InitData->stPanelInfo.u16VTotal = g_IPanel.VTotal();

    pstXC_InitData->stPanelInfo.u16DefaultVFreq = g_IPanel.DefaultVFreq();

    pstXC_InitData->stPanelInfo.u8LPLL_Mode = g_IPanel.LPLL_Mode();
    pstXC_InitData->stPanelInfo.enPnl_Out_Timing_Mode = (E_XC_PNL_OUT_TIMING_MODE)(g_IPanel.OutTimingMode());

    pstXC_InitData->stPanelInfo.u16DefaultHTotal = g_IPanel.HTotal();
    pstXC_InitData->stPanelInfo.u16DefaultVTotal = g_IPanel.VTotal();
    pstXC_InitData->stPanelInfo.u32MinSET = g_IPanel.MinSET();
    pstXC_InitData->stPanelInfo.u32MaxSET = g_IPanel.MaxSET();
    pstXC_InitData->stPanelInfo.eLPLL_Type = (E_XC_PNL_LPLL_TYPE) g_IPanel.LPLL_Type();
    pstXC_InitData->bDLC_Histogram_From_VBlank = FALSE;

    if(MApi_XC_Init(pstXC_InitData, sizeof(XC_INITDATA)) == FALSE)
    {
        UBOOT_ERROR("L:%d, XC_Init failed because of InitData wrong, please update header file and compile again\n", __LINE__);
        return -1;
    }
#if (CONFIG_HDMITX_MSTAR_ROCKET==1)
    //set display window 
    MApi_XC_SetDispWindowColor(0x82,MAIN_WINDOW);
    
    MApi_XC_SetFrameColor(0x00801080); 
#endif
    //0. VE initialization
    if(get_addr_from_mmap("E_MMAP_ID_VE", &u32Addr)!=0)
    {
        UBOOT_ERROR("get E_MMAP_ID_VE fail\n");
        return -1;
    }
   
   
    MApi_XC_SetOutputCapture(ENABLE,E_XC_OP2);      // Enable op2 to ve path
    MDrv_VE_Init(u32Addr); //MDrv_VE_Init(VE_BUFFER_ADDR);
    UBOOT_DEBUG("E_MMAP_ID_VE 0x%x \n",u32Addr);
    MDrv_VE_SetOSD(FALSE);
    
    MDrv_VE_SetOutputVideoStd(getVEVideoSys(outPutType));
    //setHDMITxAnalogTuning(outPutType);    //set bank21_0x2e(16bit mode)
    //1. VE configuration
    MS_Switch_VE_Src_Info SwitchInputSrc;
    SwitchInputSrc.InputSrcType = MS_VE_SRC_SCALER;
    
    MDrv_VE_SwitchInputSource(&SwitchInputSrc);

    MS_Switch_VE_Dest_Info SwitchOutputDest;
	SwitchOutputDest.OutputDstType = MS_VE_DEST_SCART;
    
    MDrv_VE_SwitchOuputDest(&SwitchOutputDest);

    MS_VE_Set_Mode_Type SetModeType;
    SetModeType.u16H_CapSize     = g_IPanel.Width();
    
#if (CONFIG_HDMITX_MSTAR_ROCKET==1 && ENABLE_MSTAR_NAPOLI==1) 
    extern MS_BOOL is_Interlace(HDMITX_VIDEO_TIMING outputTiming);

    if(is_Interlace(outPutType))
    {
        SetModeType.u16V_CapSize     = g_IPanel.Height()*2;
        SetModeType.bSrcInterlace = TRUE;
        UBOOT_DEBUG("interlaced u16V_CapSize X2 !!!\n"); 
    }
    else
#endif

    {
        SetModeType.bSrcInterlace = FALSE;
        SetModeType.u16V_CapSize     = g_IPanel.Height();
    }
    SetModeType.u16H_CapStart    = g_IPanel.HStart();
    SetModeType.u16V_CapStart    = g_IPanel.VStart();
    SetModeType.u16H_SC_CapSize  = g_IPanel.Width();
    SetModeType.u16V_SC_CapSize  = g_IPanel.Height();
    SetModeType.u16H_SC_CapStart = g_IPanel.HStart();
    SetModeType.u16V_SC_CapStart = g_IPanel.VStart();
    SetModeType.u16InputVFreq = getFrameRates(outPutType)*2/10;
    
    SetModeType.bHDuplicate   = FALSE;
    
    MDrv_VE_SetMode(&SetModeType);

    MS_VE_Output_Ctrl OutputCtrl;
    OutputCtrl.bEnable = TRUE;
    
    OutputCtrl.OutputType = MS_VE_OUT_TVENCODER;
    
    MDrv_VE_SetOutputCtrl(&OutputCtrl);
    MDrv_VE_SetRGBIn(FALSE);
    MApi_XC_ADC_SetCVBSOut(ENABLE, OUTPUT_CVBS1, INPUT_SOURCE_DTV, TRUE);
    MsDrv_OSDC_init();
    UBOOT_TRACE("OUT\n");
    return 1;

}



