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
/// @file   drvAESDMA.h
/// @brief  AESDMA Driver Interface
/// @author MStar Semiconductor,Inc.
///
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DRVCIPHER_H__
#define __DRVCIPHER_H__

#include "MsTypes.h"
#include "MsDevice.h"
#include "MsCommon.h"

//--------------------------------------------------------------------------------------------------
//  Define
//--------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------
//  Driver Capability
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  Local variable
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  Type and Structure
//--------------------------------------------------------------------------------------------------
/// AESDMA DDI return value
typedef MS_U32                         DRV_CIPHER_RET;


typedef enum
{
    E_CIPHER_MAIN_UNDF = 0,
    E_CIPHER_MAIN_AES = 1,
    E_CIPHER_MAIN_DES = 2,
    E_CIPHER_MAIN_TDES = 3,
    E_CIPHER_MAIN_M6_S56_CCBC = 4 ,
    E_CIPHER_MAIN_M6_S56 =5 ,
    E_CIPHER_MAIN_M6_KE56 = 7 ,
    E_CIPHER_MAIN_RC4 = 8,
    E_CIPHER_MAIN_NUM
}CIPHER_MAIN_ALGO;

typedef enum
{
    E_CIPHER_SUB_NONE = 0,
    E_CIPHER_SUB_ECB = 0,
    E_CIPHER_SUB_CBC,
    E_CIPHER_SUB_CTR,
    E_CIPHER_SUB_CBC_MAC,
    E_CIPHER_SUB_CTR_64,
    E_CIPHER_SUB_CMAC_Key,
    E_CIPHER_SUB_CMAC_Algo,
    E_CIPHER_SUB_PCBC_ADD,
    E_CIPHER_SUB_PCBC_XOR,
    E_CIPHER_SUB_NUM,

}CIPHER_SUB_ALGO;

typedef enum
{
    E_CIPHER_RES_NONE   = 0 ,
    E_CIPHER_RES_CLR    = 0 ,
    E_CIPHER_RES_CTS    = 1 ,
    E_CIPHER_RES_SCTE52 = 2 ,
    E_CIPHER_RES_NUM ,
}CIPHER_RES_ALGO;

typedef enum
{
    E_CIPHER_SB_NONE   = 0 ,
    E_CIPHER_SB_CLR    = 0 ,
    E_CIPHER_SB_IV1   ,
    E_CIPHER_SB_IV2  ,
    E_CIPHER_SB_NUM  ,

}CIPHER_SB_ALGO;

typedef enum
{
    E_CIPHER_KSRC_CPU = 0 ,
    E_CIPHER_KSRC_KL ,
    E_CIPHER_KSRC_OTP ,

}CIPHER_KEY_SRC;


typedef struct
{
    CIPHER_MAIN_ALGO    eMainAlgo;
    CIPHER_SUB_ALGO     eSubAlgo;
    CIPHER_RES_ALGO     eResAlgo;
    CIPHER_SB_ALGO      eSBAlgo;
}DRV_CIPHER_ALGO;

typedef struct
{
    CIPHER_KEY_SRC  eKeySrc;
    MS_U8           u8KeyIdx;
    MS_U8           u8KeyLen;
    MS_U8           *pu8KeyData;
    MS_U8           u8IVLen;
    MS_U8           *pu8IVData;
    MS_BOOL         bClearSK;
}DRV_CIPHER_KEY;


typedef enum
{
	E_CIPHER_DRAM = 0,
	E_CIPHER_DQMEM,
	E_CIPHER_IQMEM,
	E_CIPHER_DIRECT,
	E_CIPHER_KL_SRAM,
}CIPHER_MEM_TYPE;


typedef struct
{
    MS_U32 u32Addr;
    MS_U32 u32Size;
	CIPHER_MEM_TYPE    eMemoryType;
}DRV_CIPHER_DATA;

typedef struct
{
    DRV_CIPHER_ALGO stAlgo;
    DRV_CIPHER_KEY  stKey;
    DRV_CIPHER_DATA stInput;
    DRV_CIPHER_DATA stOutput;
    MS_BOOL         bDecrypt;
}DRV_CIPHER_DMACFG;

typedef enum
{
    E_CIPHER_HASH_ALGO_SHA1 = 0 ,
    E_CIPHER_HASH_ALGO_SHA256 ,
    E_CIPHER_HASH_ALGO_MD5 ,
}CIPHER_HASH_ALGO;

typedef enum
{
    E_CIPHER_HASH_IV_FIPS = 0 ,
    E_CIPHER_HASH_IV_CMD ,
    E_CIPHER_HASH_IV_PRV ,
}CIPHER_HASH_IV;

typedef enum
{
    E_CIPHER_HASH_STAGE_FIRST ,
    E_CIPHER_HASH_STAGE_UPDATE ,
    E_CIPHER_HASH_STAGE_LAST ,
}CIPHER_HASH_STAGE;

typedef enum
{
	E_CIPHER_IKPAD = 0,
	E_CIPHER_OKPAD,
}CIPHER_HMAC_KPAD;

typedef enum
{
    E_CIPHER_KSEL_HK = 0,
    E_CIPHER_KSEL_STRN,
    E_CIPHER_KSEL_MK0,
	E_CIPHER_KSEL_MK1,
	E_CIPHER_KSEL_CCCK,
	E_CIPHER_KSEL_SK0,
	E_CIPHER_KSEL_SK1,
	E_CIPHER_KSEL_SK2,
	E_CIPHER_KSEL_SK3,

}CIPHER_HMAC_KEY_SEL;

typedef struct
{
    CIPHER_HASH_ALGO    eAlgo;
    DRV_CIPHER_DATA     stInput;
    DRV_CIPHER_DATA     stOutput;
}DRV_CIPHER_HASHCFG;

typedef struct
{
    CIPHER_HASH_ALGO    eAlgo;
    DRV_CIPHER_DATA     stInput;
    DRV_CIPHER_DATA     stOutput;
    CIPHER_HMAC_KEY_SEL eHMACKeySel;
    MS_U8               *pu8HMAC_HK_KeyData;
    MS_BOOL             bClearKey;
}DRV_CIPHER_HMACCFG;


#define DRV_CIPHER_OK                   (0x00000000)
#define DRV_CIPHER_FAIL                 (0x00000001)
#define DRV_CIPHER_BAD_PARAM            (0x00000002)
#define DRV_CIPHER_HASH_OK              (0x80000000)
#define DRV_CIPHER_HMAC_ERR_MASK        (0xFFF8FFFF)



//--------------------------------------------------------------------------------------------------
//  Function Prototype
//--------------------------------------------------------------------------------------------------
DRV_CIPHER_RET MDrv_Cipher_Init(MS_U32 u32CAVid);
DRV_CIPHER_RET MDrv_Cipher_DMACalc(DRV_CIPHER_DMACFG stCfg, MS_U32 *u32CmdId);

DRV_CIPHER_RET MDrv_Cipher_HASHAuto(DRV_CIPHER_HASHCFG stCfg);
DRV_CIPHER_RET MDrv_Cipher_HASHManual(DRV_CIPHER_HASHCFG stCfg, CIPHER_HASH_STAGE eStage, MS_U32 u32DoneBytes, MS_U8 *pu8SetIV);
DRV_CIPHER_RET MDrv_Cipher_HMAC(DRV_CIPHER_HMACCFG stCfg);

DRV_CIPHER_RET MDrv_Cipher_Start(MS_U32 u32CmdId);
DRV_CIPHER_RET MDrv_Cipher_IsDMADone(MS_U32 u32CmdId, MS_BOOL *bDone);
DRV_CIPHER_RET MDrv_Cipher_IsHASHDone(MS_U32 u32CmdId, MS_BOOL *bDone);

#ifdef ENABLE_BGC
DRV_CIPHER_RET MDrv_Cipher_BGC_Enable(MS_U32 u32EngId,MS_U32 u32Algo, MS_U8 *pu8Golden, MS_U32 u32SAddr, MS_U32 u32Size);
DRV_CIPHER_RET MDrv_Cipher_BGC_Check(MS_U32 u32EngId, MS_BOOL *bOK);
#endif



//////// Old Interface /////////////////
//--------------------------------------------------------------------------------------------------
//  Function Prototype
//--------------------------------------------------------------------------------------------------
#include "drvAESDMA.h"

#endif
