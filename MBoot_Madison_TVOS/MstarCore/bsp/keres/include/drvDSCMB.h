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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvDscmb.h
/// @brief  Descrambler (Dscmb) Driver Interface
/// @author MStar Semiconductor,Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_DSCMB_H__
#define __DRV_DSCMB_H__

#include "MsTypes.h"
#include "MsCommon.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define MSIF_DSMB_LIB_CODE              {'D','S','M','B'}    //Lib code
#define MSIF_DSMB_LIBVER                {'0','2'}            //LIB version
#define MSIF_DSMB_BUILDNUM              {'1','8'}            //Build Number
#define MSIF_DSMB_CHANGELIST            {'0','0','5','6','5','9','8','0'} //P4 ChangeList Number

#define DSCMB_DRV_VERSION               /* Character String for DRV/API version             */  \
    MSIF_TAG,                           /* 'MSIF'                                           */  \
    MSIF_CLASS,                         /* '00'                                             */  \
    MSIF_CUS,                           /* 0x0000                                           */  \
    MSIF_MOD,                           /* 0x0000                                           */  \
    MSIF_CHIP,                                                                                  \
    MSIF_CPU,                                                                                   \
    MSIF_DSMB_LIB_CODE,                 /* IP__                                             */  \
    MSIF_DSMB_LIBVER,                   /* 0.0 ~ Z.Z                                        */  \
    MSIF_DSMB_BUILDNUM,                 /* 00 ~ 99                                          */  \
    MSIF_DSMB_CHANGELIST,               /* CL#                                              */  \
    MSIF_OS


#define DSCMB_ASSERT_AND_RETURN(x)             if (!(x)){printf ("ASSERT FAIL: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__); return FALSE;}
#define DSCMB_ASSERT_NO_RETURN(x)             if (!(x)){printf ("ASSERT FAIL: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);}

#define DSCMB_LIB_TIME_MAX          16      ///< Maximum length of time
#define DSCMB_LIB_DATE_MAX          16      ///< Maximum length of date

#define DEFAULT_CAVID   (0x0F)
#define DRV_DSCMB_CAVID_NDS (0x1)
#define DRV_DSCMB_CAVID_NAG (0x2)
#define DRV_DSCMB_CAVID_IRD (0x4)

typedef struct
{
    MS_U8   Time[DSCMB_LIB_TIME_MAX];       ///< Library Built Time
    MS_U8   Date[DSCMB_LIB_DATE_MAX];       ///< Library Built Date
} DSCMB_Info;

typedef struct
{
    MS_U32 u32Status;
} DSCMB_Status;

/// Descrambler null filter ID
#define DRV_DSCMB_FLT_NULL          0xFFFFFFFF

typedef enum
{
    /// Descrambler Slot Type :
    E_SLOT_TYPE_NORMAL = 0,  // Normal
    E_SLOT_TYPE_SHARE,       // Share
} DSCMB_SLOT_Type;

typedef enum
{
    E_DSCMB_FLT_3_KEYS        = 0x00000000, // Odd, Even, and Clear Key
    E_DSCMB_FLT_2_KEYS        = 0x00000001, // Odd and Even Key
    E_DSCMB_FLT_2_KEYS_SHARE  = 0x00000002, // Odd and Even Key (share key)
} DSCMB_Flt_Type;

/// Descrambler algorithm type
typedef enum
{
    /// Descrambler algorithm : CSA
    E_DSCMB_TYPE_CSA = 0,    // CSA
    /// Descrambler algorithm : NSA as ESA
    E_DSCMB_TYPE_NSA_AS_ESA, // NSA as ESA
    /// Descrambler algorithm : CI+ DES
    E_DSCMB_TYPE_DES,        // CI+ DES
    /// Descrambler algorithm : CI+ AES
    E_DSCMB_TYPE_AES,        // CI+ AES
    // E_DSCMB_TYPE_ESA,       // ESA
    // E_DSCMB_TYPE_NSAS,      // NSAS
    E_DSCMB_TYPE_AES_ECB,
    E_DSCMB_TYPE_AES_SCTE52,  // Descrambler algorithm : DBook, AES+CBC, S8 new, not support for all chips
    E_DSCMB_TYPE_AES_CTR,     // AES Counter mode
    E_DSCMB_TYPE_TDES_ECB,
    E_DSCMB_TYPE_TDES_SCTE52,

    // Synamedia AES
    E_DSCMB_TYPE_SYN_AES,    // AES Leading CLR EBC

    E_DSCMB_TYPE_MULTI2,    // Multi2

    /// Descrambler algorithm : CSA3
    E_DSCMB_TYPE_CSA3,    // CSA3
} DSCMB_Type;

/// Descrambler key type
typedef enum
{
    /// Descrambler key type : clear
    E_DSCMB_KEY_CLEAR = 0,
    /// Descrambler key type : even
    E_DSCMB_KEY_EVEN,
    /// Descrambler key type : odd
    E_DSCMB_KEY_ODD,

    E_DSCMB_KEY_MAX
} DSCMB_Key_Type;


// Descrambler Engine Type //
typedef enum
{
    E_DSCMB_ENG_KEY_LSAD,
    E_DSCMB_ENG_KEY_ESA ,
	E_DSCMB_ENG_KEY_LSAS,
    E_DSCMB_ENG_KEY_IV  ,
} DSCMB_Eng_Type;

/// Descrambler key Length
typedef enum
{
    E_DSCMB_KEY_ETPY_64 = 0,
    E_DSCMB_KEY_ETPY_128,
    E_DSCMB_KEY_ETPY_192,
    E_DSCMB_KEY_ETPY_256
} DSCMB_Key_Entropy;

/// Descrambler key forbidden
typedef enum
{
    E_DSCMB_KEY_FORBID_NONE = 0,
    E_DSCMB_KEY_FORBID_CSA2 = 1,
    E_DSCMB_KEY_FORBID_CSA3 ,
    E_DSCMB_KEY_FORBID_MULTI2 ,
    E_DSCMB_KEY_FORBID_AES ,
    E_DSCMB_KEY_FORBID_TDES ,
    E_DSCMB_KEY_FORBID_DES

} DSCMB_Key_Forbid;


/// Scramble level
typedef enum
{
    /// Descrambler level : none
    E_DSCMB_NONE                    =   0x00000000,
    /// Descrambler level : TS level
    E_DSCMB_TS                      =   0x00000001,
    /// Descrambler level : PES level
    E_DSCMB_PES                     =   0x00000002,
    /// Descrambler level : TS and PES level
    E_DSCMB_TS_PES                  =   (E_DSCMB_TS | E_DSCMB_PES),
} SCMB_Level;

/// Key ladder input source
typedef enum
{
    /// Key ladder source from ACPU/SCPU
    E_DSCMB_KL_SRC_ACPU             =   0,
    /// Key ladder source from SECRET_1
    E_DSCMB_KL_SRC_SECRET_1         =   1,
    /// Key ladder source from SECRET_2
    E_DSCMB_KL_SRC_SECRET_2         =   2,
    /// Key ladder source from SECRET_3
    E_DSCMB_KL_SRC_SECRET_3         =   3,
    /// Key ladder source from SECRET_4
    E_DSCMB_KL_SRC_SECRET_4         =   4,
    /// Key ladder source from SECRET_1
    E_DSCMB_KL_SRC_SECRET_5         =   5,
    /// Key ladder source from SECRET_2
    E_DSCMB_KL_SRC_SECRET_6         =   6,
    /// Key ladder source from SECRET_3
    E_DSCMB_KL_SRC_SECRET_7         =   7,
    /// Key ladder source from SECRET_4
    E_DSCMB_KL_SRC_SECRET_8         =   8,
    E_DSCMB_KL_SRC_SECRET_9         =   9,
    E_DSCMB_KL_SRC_SECRET_10        =   10,
    E_DSCMB_KL_SRC_SECRET_11        =   11,
    E_DSCMB_KL_SRC_SECRET_12        =   12,
    E_DSCMB_KL_SRC_SECRET_13        =   13,
    E_DSCMB_KL_SRC_SECRET_14        =   14,
    E_DSCMB_KL_SRC_SECRET_15        =   15,
} DSCMB_KLSrc;

/// Key ladder output destination
typedef enum
{

    /// Compatible for old version
    E_DSCMB_KL_DST_ACPU             =   0x1,
    E_DSCMB_KL_DST_KT_NSA           =   0x3,
    E_DSCMB_KL_DST_DMA_AES          =   0x4,
    E_DSCMB_KL_DST_DMA_TDES         =   0x5,
    E_DSCMB_KL_DST_PRIVATE0         =   0x6,
    E_DSCMB_KL_DST_PRIVATE1         =   0x7,
    E_DSCMB_KL_DST_PRIVATE2         =   0x8,


    /// Key ladder destination to ACPU
    E_DSCMB_KL_DST_CPU_ACPU         =   0x00000080,
    /// Key ladder destination to Secure CPU
    E_DSCMB_KL_DST_CPU_SCPU         =   0x00000081,
    /// Key ladder destination to DSCMB (KeyTable)
    E_DSCMB_KL_DST_KT_LSAD          =   0x00008000,
    E_DSCMB_KL_DST_KT_ESA           =   0x00008100,
    E_DSCMB_KL_DST_KT_LSAS          =   0x00008200,
    /// Key ladder destination to DMA
    E_DSCMB_KL_DST_DMA_SK0         =    0x00800000,
    E_DSCMB_KL_DST_DMA_SK1         =    0x00810000,
    E_DSCMB_KL_DST_DMA_SK2         =    0x00820000,
	E_DSCMB_KL_DST_DMA_SK3         =    0x00830000,
    E_DSCMB_KL_DST_DMA_SPS0        =    0x00880000 ,
    E_DSCMB_KL_DST_DMA_SPS1        =    0x00890000 ,
    E_DSCMB_KL_DST_DMA_SPS2        =    0x008A0000 ,
    E_DSCMB_KL_DST_DMA_SPS3        =    0x008B0000 ,
    E_DSCMB_KL_DST_DMA_SPD0        =    0x008C0000 ,
    E_DSCMB_KL_DST_DMA_SPD1        =    0x008D0000 ,
    E_DSCMB_KL_DST_DMA_SPD2        =    0x008E0000 ,
    E_DSCMB_KL_DST_DMA_SPD3        =    0x008F0000 ,
    E_DSCMB_KL_DST_DMA_CSSK        =    0x00900000 ,
    /// Key ladder destination to PRIVATE KEY
    E_DSCMB_KL_DST_PRIVATE_0       =    0x81000000   ,
    E_DSCMB_KL_DST_PRIVATE_1       =    0x82000000   ,
    E_DSCMB_KL_DST_PRIVATE_2       =    0x83000000   ,
    E_DSCMB_KL_DST_PRIVATE_3       =    0x84000000   ,
} DSCMB_KLDst;

#define DSCMB_CWKL                (0)
#define DSCMB_PVRKL               (1)

#define DSCMB_KL_DST_CLASS_CPU     (0x80)
#define DSCMB_KL_DST_CLASS_KT      (0x8000)
#define DSCMB_KL_DST_CLASS_DMA     (0x800000)
#define DSCMB_KL_DST_CLASS_PVT     (0x80000000)

/// Key ladder DSCMB destination

typedef enum
{
    // descrambler engine
    E_DSCMB_CAP_ENGINE_NUM,
    // descrambler slot
    E_DSCMB_CAP_FLT_NUM,
    // descrambler type supported
    E_DSCMB_CAP_SUPPORT_ALGORITHM,
    // descrambler key type supported
    E_DSCMB_CAP_SUPPORT_KEY_TYPE,
    // descrambler mapping, start tsp pid filter
    E_DSCMB_CAP_PIDFILTER_MAP_START,
    // descrambler mapping, end tsp pid filter
    E_DSCMB_CAP_PIDFILTER_MAP_END,
    // share key slot max number
    E_DSCMB_CAP_SHARE_KEY_SLOT_MAX_NUM,
    // share key region number
    E_DSCMB_CAP_SHARE_KEY_REGION_NUM,
    // share key region start
    E_DSCMB_CAP_SHARE_KEY_REGION_START,
    // share key region end
    E_DSCMB_CAP_SHARE_KEY_REGION_END,
} DSCMB_Query_Type;

typedef enum
{
    E_DSCMB_KL_TDES                 =   0x00000000,
    E_DSCMB_KL_AES                  =   0x0000003F,
} DSCMB_KLEng;

/// Key ladder configurations
typedef enum
{
    E_DSCMB_KL_LVL_0 = 0,
    E_DSCMB_KL_LVL_1 ,
    E_DSCMB_KL_LVL_2 ,
    E_DSCMB_KL_LVL_3 ,
    E_DSCMB_KL_LVL_9 = 9,
    E_DSCMB_KL_LVL_D = 0xD,
} DSCMB_KLType;

typedef enum
{
    E_DSCMB_KL_128_BITS   ,
    E_DSCMB_KL_64_BITS  ,
} DSCMB_KL_OutputSize;

typedef enum
{
    E_DSCMB_KL_SEL_DEFAULT = 0, //Backward compatible, actual default value is chosen in HAL driver
    E_DSCMB_KL_SEL_CW      , //CWKL
    E_DSCMB_KL_SEL_PVR     , //PVRKL
} DSCMB_KL_SelEng;


/// Key ladder configurations
typedef struct
{
    MS_BOOL         bDecrypt;
    MS_BOOL         bInverse;
    MS_BOOL         bKeepRound;
    MS_U32          u32Round;
    MS_U32          u32EngMode;
    DSCMB_KLType         eKLType;
    DSCMB_KL_OutputSize  eOutsize;

} DSCMB_KLCfg;


///New  Key ladder configurations for Keyladder run all.
typedef struct
{
    DSCMB_KLEng          eAlgo;
    DSCMB_KLSrc          eSrc;   // Select KL root key source //
    DSCMB_KLDst          eDst;   // Select KL output Key destination //
    DSCMB_KL_OutputSize  eOutsize;  // Select ouput Key size. ex: Key size of CSA and DES are E_DSCMB_KL_64_BITS//
    DSCMB_Key_Type       eKeyType;
    // Key ladder running level, support level 0 ~ 3 // [NOTE] Level 0 is only supported when destination is CryptoDMA
    MS_U32               u32Level;
    MS_U32               u32EngID;  // Select ESA/NSA as KL destination, Dscmb engine ID //
    MS_U32               u32DscID;  // Select ESA/NSA as KL destination, Dscmb ID //
    MS_U8                *u8KeyACPU;  // Select ACPU as KL root Key, KL root key //
    // KL inputs, pointer of bytes array for each level input, every input contains 16 bytes //
    // ex: MS_U8 input[48]: input[0-15] Level1 , input[16-31] Level2, input[32-47] Level3
    MS_U8                *pu8KeyKLIn;
    MS_BOOL     bDecrypt;
    MS_BOOL     bInverse;

    // New data member
    DSCMB_KL_SelEng      eKLSel;   //Select KeyLadder
	MS_U32               u32CAVid; //Set CAVid
    MS_U8                *pu8TAEncCW;  //Transformed Algorithm CEKpT
    MS_U8                u8LUT3Addr;  //Transformed Algorithm LUT3 address
    //TODO: Add Key property
} DSCMB_KLCfg_All;


typedef enum
{
    E_DSCMB_ALGOTYPE_AES       ,
    E_DSCMB_ALGOTYPE_CSA2      ,
    E_DSCMB_ALGOTYPE_DES       ,
    E_DSCMB_ALGOTYPE_TDES      ,
    E_DSCMB_ALGOTYPE_MULTI2    ,
    E_DSCMB_ALGOTYPE_CSA2_CONF ,
    E_DSCMB_ALGOTYPE_CSA3      ,
    E_DSCMB_ALGOTYPE_DEFAULT = 0xF,
    E_DSCMB_ALGOTYPE_NUM,
} DSCMB_AlgoType;


typedef enum
{
	E_DSCMB_SUBALGO_NONE = 0,
    E_DSCMB_SUBALGO_MDI_CBC = 0   ,
    E_DSCMB_SUBALGO_MDI_RCBC  ,
    E_DSCMB_SUBALGO_MDD_CBC   ,
    E_DSCMB_SUBALGO_MDD_RCBC  ,
    E_DSCMB_SUBALGO_LEADING_CLEAR ,
    E_DSCMB_SUBALGO_ECB ,
    E_DSCMB_SUBALGO_CBC ,
    E_DSCMB_SUBALGO_CTR ,
    E_DSCMB_SUBALGO_OFB ,
    E_DSCMB_SUBALGO_DEFAULT = 0xF,
    E_DSCMB_SUBALGO_NUM,
} DSCMB_SubAlgoType;


typedef enum
{
	E_DSCMB_RESSB_NONE = 0,
    E_DSCMB_RESSB_CLR  = 0,
    E_DSCMB_RESSB_CTS    ,
    E_DSCMB_RESSB_SCTE52 ,
    E_DSCMB_RESSB_XORIV1 ,
    E_DSCMB_RESSB_OC_M   ,
    E_DSCMB_RESSB_XORIV2 ,
    E_DSCMB_RESSB_DEFAULT = 0x7,
    E_DSCMB_RESSB_NUM,
} DSCMB_ResSB_AlgoType;


typedef struct
{
    DSCMB_AlgoType        eAlgo;
    DSCMB_SubAlgoType     eSubAlgo;
    DSCMB_ResSB_AlgoType  eRes;
    DSCMB_ResSB_AlgoType  eSB;
    MS_BOOL               bDecrypt;
} DSCMB_AlgCfg_All;


typedef struct
{
    MS_U32                  pPvrBuf0;       ///< DMX PVR buffer 0 starting address
    MS_U32                  pPvrBuf1;       ///< DMX PVR buffer 1 starting address
    MS_U32                  u32PvrBufSize0;    ///< DMX PVR buffer 0 size
    MS_U32                  u32PvrBufSize1;    ///< DMX PVR buffer 1 size
    MS_U16                  u16Pid;
} DSCMB_SPSPVR_Info;


// Error Status for KL //s
#define DSCMB_KL_Status MS_U32

#define    KL_STATUS_KEY_OK                            0x0000
#define    KL_STATUS_ACPU_KEY_NULL                     0x0001
#define    KL_STATUS_ACPU_OUTKEY_NULL                  0x0002
#define    KL_STATUS_INVALID_KEYROUND_PARAMETER        0x0004
#define    KL_STATUS_INVALID_INPUT_LEVEL               0x0008
#define    KL_STATUS_IVALID_DSCMB_ID                   0x0010
#define    KL_STATUS_WAIT_CW_READY_TIMEOUT             0x0020
#define    KL_STATUS_WAIT_KL_READY_TIMEOUT             0x0040
#define    KL_STATUS_KL_INPUT_NULL                     0x0080

#define    KL_STATUS_BAD_KEY                           0x0100
#define    KL_STATUS_INVALID_FUNCTION                  0x0200
#define    KL_STATUS_MULTI_FUNCTION                    0x0400
#define    KL_STATUS_ZERO_ORDER                        0x0800
#define    KL_STATUS_INTERNAL_BAD_KEY                  0x1000
#define    KL_STATUS_INVALID_KL_SEL                    0x2000



// Backward compatible
typedef DSCMB_KLSrc          DSCMB_KLadderSrc;
#define E_DSCMB_KLAD_SRC_ACPU               E_DSCMB_KL_SRC_ACPU
#define E_DSCMB_KLAD_SRC_SECRET_KEY1        E_DSCMB_KL_SRC_SECRET_1
#define E_DSCMB_KLAD_SRC_SECRET_KEY2        E_DSCMB_KL_SRC_SECRET_2
#define E_DSCMB_KLAD_SRC_SECRET_KEY3        E_DSCMB_KL_SRC_SECRET_3
#define E_DSCMB_KLAD_SRC_SECRET_KEY4        E_DSCMB_KL_SRC_SECRET_4
#define E_DSCMB_KLAD_SRC_VGK                E_DSCMB_KL_SRC_VGK

typedef DSCMB_KLDst          DSCMB_KLadderDst;
#define E_DSCMB_KLAD_DST_KTAB_ESA           E_DSCMB_KL_DST_KT_ESA
#define E_DSCMB_KLAD_DST_KTAB_NSA =         E_DSCMB_KL_DST_KT_NSA
#define E_DSCMB_KLAD_DST_AESDMA_AES =       E_DSCMB_KL_DST_DMA_AES
#define E_DSCMB_KLAD_DST_AESDMA_TDES =      E_DSCMB_KL_DST_DMA_TDES
#define E_DSCMB_KLAD_DST_ACPU =             E_DSCMB_KL_DST_ACPU

typedef DSCMB_KLCfg          DSCMB_KLadderConfig;
// Backward compatible

#if 1

typedef enum
{
    //temp for outline
    DSCMB_LV1_MAIN_AES = E_DSCMB_ALGOTYPE_AES,
    DSCMB_LV1_MAIN_TDES = E_DSCMB_ALGOTYPE_TDES,
}DSCMB_LV1_MAIN_ALGO_e;

typedef enum
{
    DSCMB_LV1_SUB_MDI_CBC = E_DSCMB_SUBALGO_MDI_CBC,
    DSCMB_LV1_SUB_MDI_RCBC = E_DSCMB_SUBALGO_MDI_RCBC,
    DSCMB_LV1_SUB_MDD_CBC = E_DSCMB_SUBALGO_MDD_CBC,
    DSCMB_LV1_SUB_MDD_RCBC = E_DSCMB_SUBALGO_MDD_RCBC,
    DSCMB_LV1_SUB_ECB = E_DSCMB_SUBALGO_ECB ,
    DSCMB_LV1_SUB_CBC = E_DSCMB_SUBALGO_CBC ,
}DSCMB_LV1_SUB_ALGO_e;


typedef enum
{
    //temp for outline
    DSCMB_LV3_MAIN_AES = E_DSCMB_ALGOTYPE_AES,
    DSCMB_LV3_MAIN_TDES = E_DSCMB_ALGOTYPE_TDES,
}DSCMB_LV3_MAIN_ALGO_e;

typedef enum
{
    DSCMB_LV3_SUB_MDI_CBC = E_DSCMB_SUBALGO_MDI_CBC,
    DSCMB_LV3_SUB_MDI_RCBC = E_DSCMB_SUBALGO_MDI_RCBC,
    DSCMB_LV3_SUB_MDD_CBC = E_DSCMB_SUBALGO_MDD_CBC,
    DSCMB_LV3_SUB_MDD_RCBC = E_DSCMB_SUBALGO_MDD_RCBC,
    DSCMB_LV3_SUB_ECB = E_DSCMB_SUBALGO_ECB ,
    DSCMB_LV3_SUB_CBC = E_DSCMB_SUBALGO_CBC ,
}DSCMB_LV3_SUB_ALGO_e;

typedef enum
{
    DSCMB_FSCB_UNCHG = 0,
    DSCMB_FSCB_B00,
    DSCMB_FSCB_B10,
    DSCMB_FSCB_B11,
} DSCMB_FSCB;


#define DSCMB_OUT_CLEAR      0x01
#define DSCMB_OUT_SCRAMBLE   0x02
typedef enum
{
    DSCMB_CIPHER_ESA = 0,
    DSCMB_CIPHER_LSAD,
    DSCMB_CIPHER_LSAS,
    DSCMB_CIPHER_NUM,
}DSCMB_CipherEngType;


typedef struct
{
    MS_BOOL               bPvrEnable;
    MS_BOOL               bLiveEnable;

    DSCMB_AlgCfg_All      stAlgCfg;
    MS_U8                 pu8Key[16];

    MS_U8                 u8CSA_Var;        //ESA only
    MS_U8                 u8Permutation;    //ESA only
}DSCMB_EngConfig;

typedef struct
{
    MS_BOOL             bEnable;
    DSCMB_EngConfig     stLSADCfg;
    DSCMB_EngConfig     stESACfg;
    DSCMB_EngConfig     stLSASCfg;

    //IV is shared by all cipher Eng
    MS_U8               pu8IV[16];

} DSCMB_KeyConfig;

typedef struct
{
    MS_U16             u16CAVid;
    MS_U32             u32OutputType;
    DSCMB_FSCB         eForceSCB;
//    MS_U8              pu8KeyEnable[3];
    DSCMB_KeyConfig    pstKeyCfg[3]; // Three  KEYs: odd, even, clear

} DSCMB_MainConfig;

#endif



typedef enum
{
    E_DSCMB_SCBFIX_UNCHG  =             0,
    E_DSCMB_SCBFIX_USESCB =             1,
    E_DSCMB_SCBFIX_CLEAR  =             2,

    E_DSCMB_SCBFIX_ODD2EVEN =           4,
    E_DSCMB_SCBFIX_EVEN2ODD =           5,

    E_DSCMB_SCBFIX_ODD2CLEAR  =         6,
    E_DSCMB_SCBFIX_EVEN2CLEAR =         7,

} DSCMB_SCBFix;


typedef enum
{
    E_DSCMB_SCBFIX_LSAD =          0,
    E_DSCMB_SCBFIX_ESA  =          1,
    E_DSCMB_SCBFIX_LSAS =          2,
    E_DSCMB_SCBFIX_DMXU =          3,
    E_DSCMB_SCBFIX_DMXL =          4,
} DSCMB_SCBFix_EngSel;



typedef enum
{
    E_DSCMB_CIPHER_OUTPUT_SPS0 = 0 ,
    E_DSCMB_CIPHER_OUTPUT_SPS1 = 1 ,
    E_DSCMB_CIPHER_OUTPUT_SPS2 = 2 ,
    E_DSCMB_CIPHER_OUTPUT_SPS3 = 3 ,
    E_DSCMB_CIPHER_OUTPUT_CLR0 = 4 ,
    E_DSCMB_CIPHER_OUTPUT_CLR1 = 5 ,
    E_DSCMB_CIPHER_OUTPUT_CLR2 = 6 ,
    E_DSCMB_CIPHER_OUTPUT_CLR3 = 7 ,
    E_DSCMB_CIPHER_OUTPUT_CLR4 = 8 ,
    E_DSCMB_CIPHER_OUTPUT_CLR5 = 9 ,
    E_DSCMB_CIPHER_OUTPUT_TSO0 = 10 ,
    E_DSCMB_CIPHER_OUTPUT_TSO1 = 11 ,
} DSCMB_OutPut_Eng_Sel;


// wrapper function

#define MDrv_DSCMB_FltAlloc(void)   \
    MDrv_DSCMB2_FltAlloc(0)
#define MDrv_DSCMB_FltFree(u32DscmbId)   \
    MDrv_DSCMB2_FltFree(0, u32DscmbId)
#define MDrv_DSCMB_FltConnectFltId(u32DscmbId, u32FltId)    \
    MDrv_DSCMB2_FltConnectFltId(0, u32DscmbId, u32FltId)
#define MDrv_DSCMB_FltDisconnectFltId(u32DscmbId, u32FltId)    \
    MDrv_DSCMB2_FltDisconnectFltId(0, u32DscmbId, u32FltId)
#define MDrv_DSCMB_PidFlt_ScmbStatus(u32PidFltId, pScmbLevel)    \
    MDrv_DSCMB2_PidFlt_ScmbStatus(0, u32PidFltId, pScmbLevel)
#define MDrv_DSCMB_Multi2_SetRound(u32Round)    \
    MDrv_DSCMB2_Multi2_SetRound(0, u32Round)
#define MDrv_DSCMB_Multi2_SetSystemKey(u32Syskey)    \
    MDrv_DSCMB2_Multi2_SetSystemKey(0, u32Syskey)
//+++++++ Compatible API ++++++++//
#define MDrv_DSCMB_FltKeySet(u32DscmbId, eKeyType, pu8Key)  \
    MDrv_DSCMB2_FltKeySet(0, u32DscmbId, eKeyType, pu8Key)
#define MDrv_DSCMB_FltKeyReset(u32DscmbId, eKeyType)    \
    MDrv_DSCMB2_FltKeyReset(0, u32DscmbId, eKeyType)
#define MDrv_DSCMB_FltIVSet(u32DscmbId, eKeyType, pu8IV)    \
    MDrv_DSCMB2_FltIVSet(0, u32DscmbId, eKeyType, pu8IV)
#define MDrv_DSCMB_FltDscmb(u32DscmbId, bDscmb) \
    MDrv_DSCMB2_FltDscmb(0, u32DscmbId, bDscmb)
#define MDrv_DSCMB_FltTypeSet(u32DscmbId, eType)    \
    MDrv_DSCMB2_FltTypeSet(0, u32DscmbId, eType)
#define MDrv_DSCMB_FltConnectPid(u32DscmbId, u32Pid)  \
    MDrv_DSCMB2_FltConnectPid(0, u32DscmbId, u32Pid)
#define MDrv_DSCMB_FltDisconnectPid(u32DscmbId, u32Pid) \
    MDrv_DSCMB2_FltDisconnectPid(0, u32DscmbId, u32Pid)
//--------- Compatible API --------------//

// descmbler read pitslotmap
void MDrv_DSCMB_ReadPidSlotMap(MS_U32 PidFltNo);


// descrambler initial function
DLL_PUBLIC MS_BOOL MDrv_DSCMB_Init(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_Init(MS_U32 u32CAVid);

// descrambler query function
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_GetCap(MS_U32 u32EngId, DSCMB_Query_Type eQueryType, void* pInput, void* pOutput);

DLL_PUBLIC const DSCMB_Info*  MDrv_DSCMB_GetInfo(void);//
DLL_PUBLIC MS_BOOL MDrv_DSCMB_GetLibVer(const MSIF_Version **ppVersion);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_SetDBGLevel(MS_U32 u32Level);//

// descrambler filter management
DLL_PUBLIC MS_U32  MDrv_DSCMB2_FltAlloc(MS_U32 u32EngId);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltFree(MS_U32 u32EngId, MS_U32 u32DscmbId);


// descrambler filter maps to TSP filter id
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltConnectFltId(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32FltId);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltDisconnectFltId(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32FltId);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_SetSwitch(MS_U32 u32EngId, MS_U32 u32DscmbId , MS_U32 u32UpSwitch ,MS_U32 u32LowSwitch,DSCMB_FSCB eForceSCB );
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_SetEngKey(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Eng_Type eEng, DSCMB_Key_Type eKeyType, MS_U8* pu8Key);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_SetEngAlgo(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Eng_Type eEng, DSCMB_AlgCfg_All stConfig);


DLL_PUBLIC MS_U32  MDrv_DSCMB_SetConfig(MS_U32 u32DscmbId, DSCMB_MainConfig *pConfig);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_StartAll(MS_U32 u32DscmbId);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_StopAll(MS_U32 u32DscmbId);

DLL_PUBLIC MS_BOOL MDrv_DSCMB2_PVR_RecCtrl(MS_U32 u32EngId, MS_BOOL Enable);


// Set descrambler filter as scrambling/decrambling mode
// Default filter mode is descrambling if this function is not specified
// This function should be invoked before MDrv_DSCMB_FltTypeSet
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltDscmb(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_BOOL bDscmb);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltTypeSet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Type);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltKeySet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U8* pu8Key);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltKeyReset(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltIVSet(MS_U32 u32EngId, MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType, MS_U8* pu8IV);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltConnectPid(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32Pid);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_FltDisconnectPid(MS_U32 u32EngId, MS_U32 u32DscmbId, MS_U32 u32Pid);
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_PidFlt_ScmbStatus(MS_U32 u32EngId, MS_U32 u32PidFltId, SCMB_Level* pScmbLevel);


// descrambler altorithm related
#if defined(DSCMB_MULTI2_ENABLE)
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_Multi2_SetRound(MS_U32 u32EngId, MS_U32 u32Round);//
DLL_PUBLIC MS_BOOL MDrv_DSCMB2_Multi2_SetSystemKey(MS_U32 u32EngId, MS_U32* u32Syskey);//
#endif

#if 1
// Key ladder
// New Key Ladder API. Group all old key ladder APIs into one.
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_ETSI(DSCMB_KLCfg_All* KLCfg , MS_U8 *ACPU_Out, MS_U8 *pu8Nonce, MS_U8 *pu8Response, DSCMB_KL_Status* u32Status );
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_TCSA3(DSCMB_KLCfg_All* KLCfg , MS_U8 *pu8ActCode, MS_U32 u32CHSel, DSCMB_KL_Status* u32Status);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_AtomicExec(DSCMB_KLCfg_All* KLCfg , MS_U8 *ACPU_Out, DSCMB_KL_Status* u32Status );
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Reset(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_SetInput(MS_U32 u32Level, MS_U8* pu8In, MS_U32 u32InLen);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_SetKey(DSCMB_KLSrc KLSrc, MS_U8* pu8Key, MS_U32 u32KeyLen);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_SetDst(DSCMB_KLDst KLDst);
DLL_PUBLIC void    MDrv_DSCMB_KLadder_SetConfig(DSCMB_KLCfg *KLCfg);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Start(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_IsComplete(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Output_Start(MS_U32 u32DscmbId, DSCMB_Key_Type eKeyType);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Output_IsComplete(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Output_Stop(void);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_ResetAcpuAck(void);//
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_ReadDataFromAcpu(MS_U8* pu8Out);
DLL_PUBLIC MS_BOOL MDrv_DSCMB_KLadder_Stop(void); // write KTE
#endif


#ifdef __cplusplus
}
#endif

#endif
