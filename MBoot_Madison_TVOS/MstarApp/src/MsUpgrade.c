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

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <MsUpgrade.h>
#include <MsUpgradeUtility.h>
#include <MsUtility.h>
#include <config.h>
#include <MsTypes.h>
#include <ShareType.h>
#include <MsVfs.h>
#include <MsString.h>
#include <MsDebug.h>
#include <MsRawIO.h>
#include <CusConfig.h>

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define SCRIPT_BUF_FOR_DO_MSTAR 4096
#define DEFAULT_BIN_PATH             "/MstarUpgrade.bin"
#define DEFAULT_SCRIPT_FILE_NAME    "auto_update.txt"   // script file name
#define DEFAULT_DEBUG_SCRIPT_PATH             "/MstarDebug.script"

#define ARG_NUM_SCRIPT_FILE         1
#define IS_ARG_AVAILABLE_SCRIPT_FILE(x) ((x) > ARG_NUM_SCRIPT_FILE)
#define ARG_SCRIPT_FILE(x)              (x)[ARG_NUM_SCRIPT_FILE]

#if defined(CONFIG_KENYA)
#include <configs/kenya.h>
#ifdef HB_CUS
#include "usb.h"
#include "fat.h"
#endif
#endif

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
#if ((ENABLE_MODULE_OAD == 1) || (ENABLE_MODULE_USB == 1) || (ENABLE_MODULE_NETUPDATE == 1) || (CONFIG_RESCUE_ENV))
static show_Error_cb            fpShow_Error = NULL;
static show_Finish_cb           fpShow_Finish = NULL;
static show_LoadData_cb         fpShow_LoadData = NULL;
static show_StartUpgrading_cb   fpShow_StartUpgrading = NULL;
static show_Upgrading_cb        fpShow_upgrading = NULL;
#endif

//-------------------------------------------------------------------------------------------------
//  Extern Functions
//-------------------------------------------------------------------------------------------------
extern int snprintf(char *str, size_t size, const char *fmt, ...);

//-------------------------------------------------------------------------------------------------
//  Private Functions
//-------------------------------------------------------------------------------------------------
#if (ENABLE_MODULE_USB == 1)
static int LoadScript2DramByUsb(char *upgradeFile, char *downloadBuf);
#endif

#if (ENABLE_MODULE_OAD == 1) || (ENABLE_MODULE_NETUPDATE == 1 || (CONFIG_RESCUE_ENV))
#if defined (CONFIG_OAD_IN_MBOOT)
static int LoadScript2DramByOAD(void);
#endif
static int LoadScript2DramByFS(char *upgradeFile, char *downloadBuf);
static int LoadScript2DramByFSFromVolume(char *upgradeFile, char *downloadBuf, char *volume);
#endif

#if (ENABLE_MODULE_OAD == 1) || (ENABLE_MODULE_NETUPDATE == 1)||(ENABLE_MODULE_USB == 1 || (CONFIG_RESCUE_ENV))
static int _show_Error(unsigned int var);
static int _show_Finish(unsigned int var);
static int _show_LoadData(unsigned int var);
static int _show_StartUpgrading(unsigned int var);
static int _show_Upgrading(unsigned int var1, unsigned int var2);
static unsigned int _check_upgrade_script_cmd_count(char *buffer);
#endif
//-------------------------------------------------------------------------------------------------
//  Public Functions
//-------------------------------------------------------------------------------------------------
#if (ENABLE_MODULE_NET == 1)
int do_mstar (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char* buffer = NULL;
    char *script_buf = NULL;
    char *next_line = NULL;
    char *ScriptFile = NULL;
    unsigned long iFilesize = 0;
    char *tmp = NULL;
    int BeAbort = 1;
    UBOOT_TRACE("IN\n");
    setUpgradeMode(EN_UPDATE_MODE_TFTP);

    ScriptFile= IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : DEFAULT_SCRIPT_FILE_NAME;
    UBOOT_DEBUG("ScriptFile=%s\n",ScriptFile);

    buffer=(char *)malloc(SCRIPT_BUF_FOR_DO_MSTAR);
    if(buffer==NULL)
    {
        UBOOT_ERROR("no memory for command string!!\n");
        return -1;
    }

    // Set mstar commmand abort or not when cmd error.
    tmp = getenv ("CmdAbort");
    if (tmp != NULL)
    {
        BeAbort = (int)simple_strtol(tmp, NULL, 10);
        UBOOT_DEBUG("BeAbort=%d\n",BeAbort);
    }

    //Enable emac
    if(-1 == run_command("estart", 0))
    {
        UBOOT_ERROR("estart Fail \n");
        free(buffer);
        return -1;
    }

    // Set DHCP
    if(getenv("ipaddr") == NULL)
    {
        if(-1 == run_command("dhcp",0))
        {
            UBOOT_ERROR("please use the legal mac address.\n");
            free(buffer);// Fix CID:147674
            return -1;
        }
    }
    else
    {
        UBOOT_DEBUG("ipaddr=%s\n",getenv("ipaddr") );
    }
    // Load script
    memset(buffer, 0 , CMD_BUF);
    snprintf(buffer, CMD_BUF, "tftp %X %s", buffer,ScriptFile);
    UBOOT_DEBUG("cmd=%s\n",buffer);
    if(-1 == run_command(buffer, 0))
    {
        UBOOT_ERROR("cmd: %s\n",buffer);
        free(buffer);
        return -1;
    }

    // because application member is lazy, so we must set "sync_mmap 1" after tftp burn code,
    // and check and prevent LX inconsistent problem between KL & SN.
    run_command("setenv sync_mmap 1;saveenv", 0);
    run_command("setenv force_upgrade;saveenv", 0);

    // Run script
    iFilesize = (unsigned long)simple_strtol(getenv("filesize"), NULL, 16);
    UBOOT_DEBUG("iFilesize=0x%x\n",(unsigned int)iFilesize);
    script_buf = buffer;
    script_buf[iFilesize]='\n'; script_buf[iFilesize+1]='%';
    while ((next_line = get_script_next_line(&script_buf)) != NULL)
    {
        next_line=ParaReplace(next_line,argc-2,&argv[1]);
#if CONFIG_MINIUBOOT
        printf("\n>> %s \n", next_line);
#else
        UBOOT_INFO ("\n>> %s \n", next_line);
#endif
        if(-1 == run_command(next_line, 0))
        {
            UBOOT_ERROR("command error!\n");
            if(BeAbort == 1)
            {
                free(buffer);
                return -1;
            }
        }
    }
    free(buffer);
    UBOOT_TRACE("OK\n");
    return 0;
}
#endif

#if (ENABLE_MODULE_USB == 1)
static int LoadScript2DramByUsb(char *upgradeFile, char *downloadBuf)
{
    char *buffer=NULL;
    int partition = 0;
    int device = 0;
    UBOOT_TRACE("IN\n");
    if(check_file_partition(upgradeFile,&device,&partition)!=0)
    {
        UBOOT_ERROR("fail : no file in usb\n");
        return -1;
    }
    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(buffer,0,CMD_BUF);

    //Load Script
    snprintf(buffer, CMD_BUF, "fatload usb %d:%d  %X %s %X",device, partition, downloadBuf, upgradeFile, getScritSizeOfUpgradeImage());
    UBOOT_DEBUG("cmd=%s\n",buffer);
    if(-1 == run_command(buffer, 0))
    {

        UBOOT_ERROR("Error: cmd: %s\n",buffer);
        free(buffer);//Coverity CID:149588
        return -1;
    }
    /*Check script file is ciphertext or not(start)*/
#if (CONFIG_SECURE_USB_UPGRADE==1)
     if(check_script_encrypt(downloadBuf) == TRUE)
     {
        setUpgradeMode(EN_UPDATE_MODE_USB_WITH_SEG_DECRYPTED);
        memset(buffer, 0 , CMD_BUF);
        snprintf(buffer, CMD_BUF, "fileSegRSA usb %d:%d %s",device, partition, upgradeFile);
        UBOOT_DEBUG("cmd=%s\n",buffer);
        if(-1 == run_command(buffer, 0))
        {
            free(buffer);
            UBOOT_ERROR("Error: cmd: %s\n",buffer);
            return -1;
        }

        memset(buffer, 0 , CMD_BUF);
        snprintf(buffer, CMD_BUF, "filepartload %x %s %x %x",downloadBuf, upgradeFile, 0, getScritSizeOfUpgradeImage());
        UBOOT_DEBUG("cmd=%s\n",buffer);
        if(-1 == run_command(buffer, 0))
        {
            free(buffer);
            UBOOT_ERROR("Error: cmd: %s\n",buffer);
            return -1;
        }
     }
     else
#endif
     {
        //check script crc
        if(check_script_crc(upgradeFile,downloadBuf)==-1)
        {
            free(buffer);
            UBOOT_ERROR("Error: check_script_crc Fail !!\n");
            return -1;
        }
     }
     free(buffer);
     UBOOT_TRACE("OK\n");
     return 0;
}

int do_ustar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char *script_buf = NULL;
    char *_script_buf = NULL;
    char *next_line = NULL;
    char *upgradeFile = NULL;
    unsigned int scriptFileSize=0;
    unsigned int progress_total_cnt = 0;
    unsigned int progress_cnt = 0;

    UBOOT_TRACE("IN\n");
    setUpgradeMode(EN_UPDATE_MODE_USB); // set the Upgrade mode
    /* Load Script */
    _show_LoadData(0);

    upgradeFile = IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : DEFAULT_BIN_PATH;

    scriptFileSize=getScritSizeOfUpgradeImage();
    if(scriptFileSize==0)
    {
        UBOOT_ERROR("The size of script file is zero \n");
        return -1;
    }

    _script_buf=malloc(scriptFileSize);
    if(_script_buf==NULL)
    {
        UBOOT_ERROR("malloc fail \n");
        return -1;
    }
    script_buf=_script_buf;
    memset(script_buf,0,scriptFileSize);


    if(setUpgradeFileName(upgradeFile)==-1)
    {
        setUpgradeMode(EN_UPDATE_MODE_NONE);
        free(_script_buf);
        UBOOT_ERROR("Error> set upgrade fail fail\n");
        _show_Error(0);
        return -1;
    }
    if(LoadScript2DramByUsb(upgradeFile,script_buf) == -1)
    {
        deleteUpgradeFileName();
        free(_script_buf);
        setUpgradeMode(EN_UPDATE_MODE_NONE);
        _show_Error(0);
        return -1;
    }
    #if(ENABLE_MODULE_DONT_OVERWRITE==1)
    set_dont_overwrite_byname(upgradeFile);
    #endif
    //Run Script

    //script_buf = (char *)UPGRADE_BUFFER_ADDR;

    progress_total_cnt=_check_upgrade_script_cmd_count(script_buf);
    if(progress_total_cnt==0)
    {
        deleteUpgradeFileName();
        setUpgradeMode(EN_UPDATE_MODE_NONE);
        free(_script_buf);
        UBOOT_ERROR("There are no any commands in the upgrade script file\n");
       _show_Error(0);
       return -1;
    }
    UBOOT_DEBUG("progress_total_cnt=%d\n",progress_total_cnt);

    _show_StartUpgrading(0);


    while ((next_line = get_script_next_line(&script_buf)) != NULL)
    {
#if CONFIG_MINIUBOOT
        printf("\n>> %s \n", next_line);
#else
        UBOOT_INFO("\n>> %s \n", next_line);
#endif

        progress_cnt++;
        UBOOT_DEBUG("progress_cnt=%d,progress_total_cnt=%d\n",progress_cnt,progress_total_cnt);
        _show_Upgrading(progress_cnt,progress_total_cnt);
        if(check_skip_cmd(next_line)== FALSE)//filterCmd
        {
            if(run_command(next_line, 0) < 0)
            {
                deleteUpgradeFileName();
                setUpgradeMode(EN_UPDATE_MODE_NONE);
                free(_script_buf);
                UBOOT_ERROR("Error> cmd: %s Fail !!\n", next_line);
                _show_Error(0);
                return -1;

            }
        }
    }

    if(deleteUpgradeFileName()==-1)
    {
        UBOOT_ERROR("delete upgrade name fail\n");
    }

    free(_script_buf);
    _show_Finish(0);
    UBOOT_TRACE("OK\n");
    return 0;


}

#ifdef HB_CUS
/*******************************************************************************************************************/
///[In]cmdtp: Monitor Command Table
///[In]flag:
///[In]argc:parm number
///[In]argv[]:input command
///This function to use usb update
/*******************************************************************************************************************/
#define ARG_NUM_BOOTDELAY           4
#define ENV_BOOTDELAY               "bootdelay"
#define DEFAULT_BOOTDELAY           "1" 
#define ARG_BOOTDELAY(x)                (x)[ARG_NUM_BOOTDELAY]
#define U8 MS_U8
#define U16 MS_U16
#define U32 MS_U32
#define USB_SCRIPT_FILE_NAME        "usb_auto_update.txt"  //usb update script file name

#define BUF_SIZE 4096
#define ENV_USB                     "usb_complete"
#define GWIN_WIDTH              720
#define GWIN_HEIGHT             576
#define GRAPHIC_WIDTH           600
#define GRAPHIC_HEIGHT          400
#define GRAPHIC_X               60
#define GRAPHIC_Y               88
#define LINE_HEIGHT             50
#define RECT_LEFT_INTERVAL      50

#define IS_ARG_AVAILABLE_BOOTDELAY(x)   ((x) > ARG_NUM_BOOTDELAY)
extern MS_U8 s_usbUpgrade;
int do_ustar_hb(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    char* buffer=NULL;
    buffer=(char *)malloc(BUF_SIZE);
    int ret=10;
    char * cUsb= getenv(ENV_USB);
    ulong  usb_complete = 0;

    if(buffer==NULL)
    {
        printf("no memory for command string!!\n");
        return -1;
    }

    //printf("%s@%d, USB envParam[%s]. \n", __FUNCTION__, __LINE__, cUsb);
    if(cUsb==NULL)
    {
        memset(buffer, 0 , BUF_SIZE);
        sprintf(buffer, "setenv %s 0", ENV_USB);
        run_command(buffer, 0); // run_command("setenv usb_complete 0");

        memset(buffer, 0 , BUF_SIZE);
        sprintf(buffer, "saveenv");
        run_command(buffer, 0); // run_command("saveenv");
    }
    else
    {
        usb_complete = simple_strtoul (cUsb, NULL, 10);
        if(usb_complete==1)
        {
            memset(buffer, 0 , BUF_SIZE);
            sprintf(buffer, "setenv %s 0", ENV_USB);
            run_command(buffer, 0);  // run_command("setenv usb_complete 0");

            memset(buffer, 0 , BUF_SIZE);
            sprintf(buffer, "saveenv");
            run_command(buffer, 0); // run_command("saveenv");
            free(buffer);
            printf("last USB upgrade complete\n");
            return 0;
        }
    }

    // setenv (prelude)
    if (IS_ARG_AVAILABLE_BOOTDELAY(argc) || getenv(ENV_BOOTDELAY) == NULL)
    {
        memset(buffer, 0 , BUF_SIZE);
        sprintf(buffer, "setenv %s %s", ENV_BOOTDELAY, IS_ARG_AVAILABLE_BOOTDELAY(argc) ? ARG_BOOTDELAY(argv) : DEFAULT_BOOTDELAY);
        run_command(buffer, 0); // run_command("setenv "ENV_BOOTDELAY" "DEFAULT_BOOTDELAY, 0);
    }

    // load & run script
    {
        char *script_buf;
        char *next_line;


        {
            // Check if file exist by load 1 byte of the file
            if (s_usbUpgrade)
            {
                sprintf(buffer, "fatload usb 0  %X %s 1", UPGRADE_BUFFER_ADDR, IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : USB_SCRIPT_FILE_NAME);
            }
            else
            {
                //For backward compatible, we must check "USB_SCRIPT_FILE_NAME" in USB disk first
                sprintf(buffer, "fatload usb 0  %lX /Target/script/%s 1", (U32)buffer, IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : USB_SCRIPT_FILE_NAME);
            }

            ret = run_command(buffer, 0);
            if(ret!=0)
            {
                printf("cmd %s failed\n", buffer);
                goto exit;
            }
        }

#if   CONFIG_DISPLAY_OSD
        U8 progress_cnt = 0;

        if (s_usbUpgrade)
        {
			//run_command("dbtable_init", 0); //TODO: refine it
            sprintf(buffer, "osd_create %d %d", GWIN_WIDTH, GWIN_HEIGHT);
            run_command(buffer, 0);
            sprintf(buffer, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
            run_command(buffer, 0);
            sprintf(buffer, "draw_string %d %d 0x3fffffff 1 LOADING DATA...", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 2);
            run_command(buffer, 0);
            progress_cnt = 1;
            sprintf(buffer, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL, GRAPHIC_Y + LINE_HEIGHT * 5, progress_cnt);
            run_command(buffer, 0);
        }
#endif

        if (s_usbUpgrade)
        {
            sprintf(buffer, "fatload usb 0  %X %s", UPGRADE_BUFFER_ADDR, IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : USB_SCRIPT_FILE_NAME);
        }
        else
        {
            //For backward compatible, we must check "USB_SCRIPT_FILE_NAME" in USB disk first
            sprintf(buffer, "fatload usb 0  %lX /Target/script/%s", (U32)buffer, IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : USB_SCRIPT_FILE_NAME);
        }

        ret = run_command(buffer, 0);

        if(s_usbUpgrade)
        {
            // Check CRC
            U32 CRC_result=0;
            U32 CRC_value=0;
            U32 addr=0;
            U32 file_size=0;

            file_size = simple_strtol(getenv("filesize"), NULL, 16);
            if((file_size <= 4) || (file_size%4 != 0))
            {
                //wrong file size
                printf("wrong file size: 0x%lx\n", file_size);
                goto exit;
            }
            addr = UPGRADE_BUFFER_ADDR+(file_size-4);
            CRC_value = CRC_result+1;
            if(addr > UPGRADE_BUFFER_ADDR)
            {
                CRC_value=*((U32*)(addr));
            }
            CRC_result=crc32( 0x00, (U8*)UPGRADE_BUFFER_ADDR, file_size-4 );
            if(CRC_result!= CRC_value)
            {
                //CRC error
                printf("wrong file size: 0x%lx\n", file_size);
#if CONFIG_DISPLAY_OSD
            {
                memset(buffer, 0 , 256);
                sprintf(buffer, "draw_rect %d %d %d %d 000000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
                ret=run_command(buffer, 0);

                memset(buffer, 0 , 256);
                sprintf(buffer, "draw_string %d %d ffffffff 1 '%s'", GRAPHIC_X, GRAPHIC_Y+200, "Software Update(USB)");
                ret=run_command(buffer, 0);

                memset(buffer, 0 , 256);
                sprintf(buffer, "draw_string %d %d ffffffff 1 '%s'", GRAPHIC_X, GRAPHIC_Y+300, "Wrong CRC");
                ret=run_command(buffer, 0);
                udelay(1000000);
            }
#endif //(CONFIG_COMMANDS & CONFIG_DISPLAY_OSD)
                goto exit;
            }
        }

#if CONFIG_DISPLAY_OSD
        if (s_usbUpgrade)
        {
            sprintf(buffer, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
            run_command(buffer, 0);
            sprintf(buffer, "draw_string %d %d 0x3fffffff 1 UPGRADING SOFTWARE", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 2);
            run_command(buffer, 0);
            sprintf(buffer, "draw_string %d %d 0x3fffffff 1 PLEASE DO NOT TURN OFF", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 3);
            run_command(buffer, 0);
            progress_cnt = 40;
            sprintf(buffer, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL, GRAPHIC_Y + LINE_HEIGHT * 5, progress_cnt);
            run_command(buffer, 0);
        }
#endif


        script_buf = s_usbUpgrade ? (char *)UPGRADE_BUFFER_ADDR : buffer;

        while ((next_line = get_script_next_line(&script_buf)) != NULL)
        {
            printf ("\n>> %s \n", next_line);
#if CONFIG_DISPLAY_OSD
            if (s_usbUpgrade)
            {
                if (strncmp("reset", next_line, 5) != 0)
                {
                    if (progress_cnt < 100)
                    {
                        progress_cnt += 4;
                        sprintf(buffer, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 5, GRAPHIC_WIDTH, LINE_HEIGHT);
                        run_command(buffer, 0);
                        sprintf(buffer, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL, GRAPHIC_Y + LINE_HEIGHT * 5, progress_cnt);
                        run_command(buffer, 0);
                    }
                }
                else
                {
                    progress_cnt = 100;
                    sprintf(buffer, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
                    run_command(buffer, 0);
                    sprintf(buffer, "draw_string %d %d 0x3fffffff 1 SOFTWARE UPGRADE COMPLETE", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 2);
                    run_command(buffer, 0);
                    sprintf(buffer, "draw_progress %d %d 0x3fffffff %d", GRAPHIC_X + RECT_LEFT_INTERVAL, GRAPHIC_Y + LINE_HEIGHT * 5, progress_cnt);
                    run_command(buffer, 0);
                    udelay(1000000);
                    sprintf(buffer, "osd_destroy"); //clear screen
                    run_command(buffer, 0);
                }
            }
#endif

//added for twice init
if (strncmp("reset", next_line, 5) == 0)
{
    memset(buffer, 0 , BUF_SIZE);
    sprintf(buffer, "setenv %s 0", ENV_USB);
    run_command(buffer, 0); // run_command("setenv usb_complete 0");
    
    memset(buffer, 0 , BUF_SIZE);
    sprintf(buffer, "saveenv");
    run_command(buffer, 0); // run_command("saveenv");
}

//added end


#if(ENABLE_MODULE_WDT_ENABLE)
#define WDT_ENABLE_HB 1
#else
#define WDT_ENABLE_HB 0
#endif

#if WDT_ENABLE_HB
    MDrv_WDT_Stop(E_WDT_DBGLV_INFO);
#endif

            ret = run_command(next_line, 0);
            if (ret < 0)
            {
                printf("Error> cmd: %s FAIL !!\n", next_line);
#if CONFIG_DISPLAY_OSD
                if (s_usbUpgrade)
                {
                    sprintf(buffer, "draw_rect %d %d %d %d 0x800000ff", GRAPHIC_X, GRAPHIC_Y, GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
                    run_command(buffer, 0);
                    sprintf(buffer, "draw_string %d %d 0x3fffffff 1 SOFTWARE UPGRADE ERROR", GRAPHIC_X, GRAPHIC_Y + LINE_HEIGHT * 2);
                    run_command(buffer, 0);
                    //udelay(5000000);
                    //sprintf(buffer, "reset");
                    //run_command(buffer, 0);
                }
#endif
                break;
            }
        }
    }

exit:
    free(buffer);
    return ret;
}

#endif

#ifdef HB_CUS
//Upgrade define
#define USB_SCRIPT_FILE_NAME        "usb_auto_update.txt"  //usb update script file name
#define OAD_ENV_FILE_NAME           "oad.txt"  //usb update script file name
#define OAD_FILE_NAME               "oad.bin"
#define ENV_OAD                     "oad_complete"
#define ENV_USB                     "usb_complete"
#define INFO_EXCHANGE_CFG           "info_exchange"
#define INFO_EXCHANGE_UBIFILE       "ubifile"
#define INFO_EXCHANGE_SPI           "spi"
#define USB_ENV_FILE_NAME           "usb.txt"
#define MAX_USB_PATH_LEN            256
#define USB_UPGRADE                 "usb_upgrade"
#define USB_UPGRADE_PORT            "usb_upgrade_port"
#define USB_UPGRADE_PATH            "usb_upgrade_path"
MS_U8 s_usbUpgrade = 0;
#include "usb.h"
int do_check_usb_upgrade(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    ulong port = 0;
    char* pPath = NULL;
    char buffer[100] = {0};

#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
    char* cUsbUpgrade = getenv(USB_UPGRADE);
    if (!cUsbUpgrade)
    {
        return 1;
    }

    if (simple_strtoul (cUsbUpgrade, NULL, 10) != 1)
    {
        return 1;
    }

    char* cUsbPort = getenv(USB_UPGRADE_PORT);
    if (cUsbPort)
    {
        port = simple_strtoul(cUsbPort, NULL, 10);
    }

    pPath = getenv(USB_UPGRADE_PATH);
#else
    #error
#endif

   //scan usable usb port
   
    for(port = 0; port < 3; port++)
    {
        if (usb_init(port) >= 0)
        {
            break;
        }
    }

    if (!pPath)
    {
        return 1;
    }

    if (port > 2)
    {
        return 1;
    }

    if (usb_stor_scan(1) != 0)
    {

        return 1;
    }


    sprintf(buffer, "ustar_hb %s", pPath);
    s_usbUpgrade = 1;
    run_command(buffer, 0);
    s_usbUpgrade = 0;

    memset(buffer, 0, sizeof(buffer));
#if   CONFIG_DISPLAY_OSD
    sprintf(buffer, "osd_destroy");
#endif
    run_command(buffer, 0);
    return 1;
}



#endif//hbcus end


int do_udstar (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char *cmdBuf=NULL;
    char *script_buf=NULL;
    char *pBuf=NULL;
    char *next_line=NULL;
    char *upgradeFile=NULL;
    char *env=NULL;
    int ret=0;
    unsigned int u32FileSize=0;
    int partition = 0;
    int device = 0;
    UBOOT_TRACE("IN\n");

    upgradeFile = IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : DEFAULT_DEBUG_SCRIPT_PATH;

    if(check_file_partition(upgradeFile,&device,&partition)!=0)
    {
        UBOOT_ERROR("no file in usb\n");
        return -1;
    }

    UBOOT_DEBUG("upgradeFile=%s\n",upgradeFile);

    cmdBuf=malloc(CMD_BUF);
    if(cmdBuf==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    memset(cmdBuf, 0 , CMD_BUF);
    snprintf(cmdBuf, CMD_BUF, "fatload usb %d:%d %X %s 1", device,partition,cmdBuf, upgradeFile);
    UBOOT_DEBUG("cmd=%s\n",cmdBuf);
    ret=run_command(cmdBuf, 0);
    if(ret!=0)
    {
        free(cmdBuf);
        UBOOT_ERROR("No script file exist\n");
        return -1;
    }

    memset(cmdBuf, 0, CMD_BUF);
    snprintf(cmdBuf, CMD_BUF, "fatfilesize usb %d:%d %s", device,partition, upgradeFile);
    UBOOT_DEBUG("cmd=%s\n",cmdBuf);
    ret = run_command(cmdBuf, 0);
    if(ret!=0)
    {
        free(cmdBuf);
        UBOOT_ERROR("get script file's size fail\n");
        return -1;
    }
    // Get file size. If larger then DRAM, don't load the whole. Just load its script.
    env=getenv("filesize");
    if(env==NULL)
    {
       free(cmdBuf);
       UBOOT_ERROR("get env 'filesize' fail\n");
       return -1;
    }
    u32FileSize = simple_strtol(env, NULL, 16);
    pBuf=malloc(u32FileSize);
    if(pBuf==NULL)
    {
        free(cmdBuf);
        UBOOT_ERROR("malloc for script file fail\n");
        return -1;
    }
    script_buf=pBuf;
    memset(script_buf,0,u32FileSize);

    memset(cmdBuf, 0, CMD_BUF);
    snprintf(cmdBuf, CMD_BUF, "fatload usb %d:%d %X %s %X",device,partition,script_buf,upgradeFile,u32FileSize);
    UBOOT_DEBUG("cmd=%s\n",cmdBuf);
    ret = run_command(cmdBuf, 0);
    if(ret!=0)
    {
        free(pBuf);
        free(cmdBuf);
        return -1;
    }

    while ((next_line = get_script_next_line(&script_buf)) != NULL)
    {
        UBOOT_INFO ("\n>>1 %s \n", next_line);

        if(strstr((char *)next_line,(char *)"go")!=NULL)
        {
            UBOOT_INFO ("skip cmd 'go' \n");
            continue;
        }

        if(strstr((char *)next_line,(char *)"run")!=NULL)
        {
            UBOOT_INFO ("skip cmd 'run' \n");
            continue;
        }

        ret=run_command(next_line, 0);
        if(ret!=0)
        {
            free(pBuf);
            free(cmdBuf);
            UBOOT_ERROR("run cmd '%s' fail\n",next_line);
            return -1;
        }
    }

    free(cmdBuf);
    free(pBuf);
    UBOOT_TRACE("OK\n");
    return 0;
}

#endif

#if (ENABLE_MODULE_OAD == 1) || (ENABLE_MODULE_NETUPDATE == 1 || (CONFIG_RESCUE_ENV))
#if defined (CONFIG_OAD_IN_MBOOT)
static int LoadScript2DramByOAD(void)
{
    char buffer[CMD_BUF]="\0";
    char* p_str = NULL;
    unsigned int  u32Freq = 0;
    unsigned int  u32Pid  = 0;
    unsigned char u8Band = 0;
    unsigned char u8DVBC = 0;
    unsigned int  u32QAM = 0;
    unsigned int  u16SYMBOLRATE = 0;
#if(CONFIG_SDTT_OAD)
    unsigned char u8SDTT_OAD  = 0;
#endif
    UBOOT_TRACE("IN\n");
    p_str = getenv("oad_upgrade_freq");
    if(p_str == NULL)
    {
        return -1;
    }
    u32Freq = simple_strtoul (p_str, NULL, 10);
    p_str = getenv("oad_upgrade_pid");
    if(p_str == NULL)
    {
        return -1;
    }
    u32Pid = simple_strtoul (p_str, NULL, 10);
    p_str = getenv("oad_upgrade_dvbc");
    if(p_str != NULL)
    {
        u8DVBC = simple_strtoul (p_str, NULL, 10);
    }
    if(u8DVBC != 0)
    {
        p_str = getenv("oad_upgrade_qam");
        u32QAM = simple_strtoul (p_str, NULL, 10);
        if(p_str == NULL)
        {
            return -1;
        }
        p_str = getenv("oad_upgrade_symbol_rate");
        u16SYMBOLRATE = simple_strtoul (p_str, NULL, 10);
        if(p_str == NULL)
        {
            return -1;
        }
#if(CONFIG_SDTT_OAD)
        u8SDTT_OAD = 1;
        snprintf(buffer, CMD_BUF, "oaddvbc %d %d %d 0x%x %d", u32Freq, u32QAM, u16SYMBOLRATE, u32Pid, u8SDTT_OAD);
#else
        snprintf(buffer, CMD_BUF, "oaddvbc %d %d %d 0x%x", u32Freq, u32QAM, u16SYMBOLRATE, u32Pid);
#endif
    }
    else
    {
        p_str = getenv("oad_upgrade_band");
        if(p_str == NULL)
        {
            return -1;
        }

        u8Band = simple_strtoul (p_str, NULL, 10);
        if((u8Band<1) || (u8Band>3))
        {
            UBOOT_ERROR("wrong band: %d \n",u8Band);
            return FALSE;
        }
#if(CONFIG_SDTT_OAD)
        u8SDTT_OAD = 1;
        snprintf(buffer, CMD_BUF, "oad %d %d 0x%x %d", u32Freq, u8Band, u32Pid, u8SDTT_OAD);
#else
        snprintf(buffer, CMD_BUF, "oad %d %d 0x%x", u32Freq, u8Band, u32Pid);
#endif
    }
     //do OAD: download from ts to mamory
    if(run_command(buffer,0)!=0)
    {
        UBOOT_ERROR("do %s fail\n",buffer);
        return -1;
    }
    UBOOT_TRACE("OK\n");
    return 0;

}
#endif

static int LoadScript2DramByFS(char *upgradeFile, char *downloadBuf)
{
    char *buffer=NULL;
    UBOOT_TRACE("IN\n");
    
    buffer=malloc(CMD_BUF);
    if(buffer==NULL)
    {
        UBOOT_ERROR("malloc fail\n");
        return -1;
    }
    //load script
    if(0 != LoadScript2DramByFSFromVolume(upgradeFile, downloadBuf, OAD))
    {
        UBOOT_ERROR("Error: LoadScript2DramByFSFromVolume Fail !!\n");
        return -1;
    }
#if (CONFIG_SECURE_USB_UPGRADE==1)
    if(check_script_encrypt(downloadBuf) == TRUE)
    {
        setUpgradeMode(EN_UPDATE_MODE_NET_WITH_SEG_DECRYPTED);
        memset(buffer, 0 , CMD_BUF);
        snprintf(buffer, CMD_BUF, "fileSegRSA FS NULL %s",upgradeFile);
        UBOOT_DEBUG("cmd=%s\n",buffer);
        if(-1 == run_command(buffer, 0))
        {
            free(buffer);
            UBOOT_ERROR("Error: cmd: %s\n",buffer);
            return -1;
        }

        memset(buffer, 0 , CMD_BUF);
        snprintf(buffer, CMD_BUF, "filepartload %x %s %x %x",downloadBuf, upgradeFile, 0, getScritSizeOfUpgradeImage());
        UBOOT_DEBUG("cmd=%s\n",buffer);
        if(-1 == run_command(buffer, 0))
        {
            free(buffer);
            UBOOT_ERROR("Error: cmd: %s\n",buffer);
            return -1;
        }
    }
    else
#endif
    {
        //check script crc
        if(check_script_crc(upgradeFile,downloadBuf)==-1)
        {
            free(buffer);
            UBOOT_ERROR("Error: check_script_crc Fail !!\n");
            return -1;
        }    
    }
    UBOOT_TRACE("OK\n");
    return 0;
}

static int LoadScript2DramByFSFromVolume(char *upgradeFile, char *downloadBuf, char *volume)
{
    UBOOT_TRACE("IN\n");

    if(upgradeFile==NULL || downloadBuf==NULL)
    {
        UBOOT_ERROR("Input NULL\n");
        return -1;
    }

    if(NULL == volume)
    {
        UBOOT_ERROR("volume is NULL\n");
        return -1;
    }
    if(vfs_mount(volume) == -1)
    {
        UBOOT_ERROR("Error: vfs_mount Fail !!\n");
        return -1;
    }
    setUpgradeFsMountName(volume);   
    if(vfs_read((void *)downloadBuf,upgradeFile,0,getScritSizeOfUpgradeImage()) == -1)
    {
        UBOOT_ERROR("Error: vfs_read Fail !!\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

int do_nstar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char *script_buf  = NULL;
    char *_script_buf = NULL;
    char *next_line   = NULL;
    char *upgradeFile = NULL;
    unsigned int scriptFileSize=0;
    unsigned int progress_total_cnt = 0;
    unsigned int progress_cnt = 0;

    UBOOT_TRACE("IN\n");
    setUpgradeMode(EN_UPDATE_MODE_OAD); // set the Upgrade mode

    upgradeFile = IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : DEFAULT_BIN_PATH;
    UBOOT_DEBUG("upgradeFile=%s\n",upgradeFile);
    if(setUpgradeFileName(upgradeFile)==-1)
    {
        UBOOT_ERROR("Error> set upgrade fail fail\n");
        _show_Error(0);
        setUpgradeMode(EN_UPDATE_MODE_NONE);
        return -1;
    }

     scriptFileSize=getScritSizeOfUpgradeImage();
     if(scriptFileSize==0)
     {
         UBOOT_ERROR("The size of script file is zero \n");
         return -1;
     }

     _script_buf=malloc(scriptFileSize+512);
     if(_script_buf==NULL)
     {
         UBOOT_ERROR("malloc fail \n");
         return -1;
     }
     script_buf=_script_buf;
     memset(script_buf,0,scriptFileSize);
    _show_LoadData(0);
    // load script
    if(LoadScript2DramByFS(upgradeFile,script_buf) != 0)
    {
        goto OAD_FAIL;
    }

    //set dont overwrite
    #if(ENABLE_MODULE_DONT_OVERWRITE==1)
    dont_overwrite_enable();
    do_force_overwrite_enable();
    #endif
    _show_StartUpgrading(0);

    //run script
    progress_total_cnt=_check_upgrade_script_cmd_count(script_buf);
    if(progress_total_cnt==0)
    {
       UBOOT_ERROR("There are no any commands in the upgrade script file\n");
       goto OAD_FAIL;
    }
    UBOOT_DEBUG("progress_total_cnt=%d\n",progress_total_cnt);

    while ((next_line = get_script_next_line(&script_buf)) != NULL)
    {
        UBOOT_INFO ("\n>> %s \n", next_line);

        progress_cnt++;
        UBOOT_DEBUG("progress_cnt=%d,progress_total_cnt=%d\n",progress_cnt,progress_total_cnt);
        _show_Upgrading(progress_cnt,progress_total_cnt);
        #if(ENABLE_MODULE_DONT_OVERWRITE==1)
        if(check_skip_cmd(next_line)== FALSE)
        {
            if(run_command(next_line, 0) < 0)
            {
                UBOOT_ERROR("Error> cmd: %s Fail !!\n", next_line);
                goto OAD_FAIL;
            }
        }
        #endif

    }

    if(deleteUpgradeFileName()==-1)
    {
        UBOOT_ERROR("delete upgrade name fail\n");
    }

    if(_script_buf!=NULL)
    {
        free(_script_buf);
    }

    _show_Finish(0);
    UBOOT_TRACE("OK\n");
    return 0;

OAD_FAIL:
   _show_Error(0);
    deleteUpgradeFileName();
    setUpgradeMode(EN_UPDATE_MODE_NONE);
    if(_script_buf!=NULL)
    {
        free(_script_buf);
    }
    return -1;
}

#define BRICK_BACKUP_VOLUME "brickbackup"
int do_bstar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char *script_buf  = NULL;
    char *_script_buf = NULL;
    char *next_line   = NULL;
    char *upgradeFile = NULL;
    unsigned int scriptFileSize=0;
    unsigned int progress_total_cnt = 0;
    unsigned int progress_cnt = 0;

    UBOOT_TRACE("IN\n");
    setUpgradeMode(EN_UPDATE_MODE_OAD); // set the Upgrade mode

    upgradeFile = IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : DEFAULT_BIN_PATH;
    UBOOT_DEBUG("upgradeFile=%s\n",upgradeFile);
    if(setUpgradeFileName(upgradeFile)==-1)
    {
        UBOOT_ERROR("Error> set upgrade fail fail\n");
        _show_Error(0);
        setUpgradeMode(EN_UPDATE_MODE_NONE);
        return -1;
    }

     scriptFileSize=getScritSizeOfUpgradeImage();
     if(scriptFileSize==0)
     {
         UBOOT_ERROR("The size of script file is zero \n");
         return -1;
     }

     _script_buf=malloc(scriptFileSize+512);
     if(_script_buf==NULL)
     {
         UBOOT_ERROR("malloc fail \n");
         return -1;
     }
     script_buf=_script_buf;
     memset(script_buf,0,scriptFileSize);
    _show_LoadData(0);

    // load script
    if(LoadScript2DramByFSFromVolume(upgradeFile,script_buf, BRICK_BACKUP_VOLUME) != 0)
    {
        goto OAD_FAIL;
    }

    //set dont overwrite
#if(ENABLE_MODULE_DONT_OVERWRITE==1)
    dont_overwrite_enable();
    do_force_overwrite_enable();
#endif
    _show_StartUpgrading(0);

    //run script
    progress_total_cnt=_check_upgrade_script_cmd_count(script_buf);
    if(progress_total_cnt==0)
    {
       UBOOT_ERROR("There are no any commands in the upgrade script file\n");
       goto OAD_FAIL;
    }
    UBOOT_DEBUG("progress_total_cnt=%d\n",progress_total_cnt);

    while ((next_line = get_script_next_line(&script_buf)) != NULL)
    {
        UBOOT_INFO ("\n>> %s \n", next_line);

        progress_cnt++;
        UBOOT_DEBUG("progress_cnt=%d,progress_total_cnt=%d\n",progress_cnt,progress_total_cnt);
        _show_Upgrading(progress_cnt,progress_total_cnt);
        #if(ENABLE_MODULE_DONT_OVERWRITE==1)
        if(check_skip_cmd(next_line)== FALSE)
        {
            if(run_command(next_line, 0) < 0)
            {
                UBOOT_ERROR("Error> cmd: %s Fail !!\n", next_line);
                goto OAD_FAIL;
            }
        }
        #endif
    }

    if(deleteUpgradeFileName()==-1)
    {
        UBOOT_ERROR("delete upgrade name fail\n");
    }

    if(_script_buf!=NULL)
    {
        free(_script_buf);
    }

    _show_Finish(0);
    UBOOT_TRACE("OK\n");
    return 0;

OAD_FAIL:
   _show_Error(0);
    deleteUpgradeFileName();
    setUpgradeMode(EN_UPDATE_MODE_NONE);
    if(_script_buf!=NULL)
    {
        free(_script_buf);
    }
    return -1;
}

int do_ostar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    char *script_buf  = NULL;
    char *_script_buf = NULL;
    char *next_line   = NULL;
    char *upgradeFile = NULL;
    unsigned int scriptFileSize=0;
    unsigned int progress_total_cnt = 0;
    unsigned int progress_cnt = 0;

    UBOOT_TRACE("IN\n");
    setUpgradeMode(EN_UPDATE_MODE_OAD); // set the Upgrade mode

#if defined (CONFIG_OAD_IN_MBOOT)
    scriptFileSize = 0;
    _script_buf = NULL;
    upgradeFile = NULL;
    script_buf=(char *)UPGRADE_BUFFER_ADDR;
    if(LoadScript2DramByOAD()!= 0)
    {
         UBOOT_ERROR("OAD Download in Mboot Fail!!\n");
         return -1;
    }
#else
    upgradeFile = IS_ARG_AVAILABLE_SCRIPT_FILE(argc) ? ARG_SCRIPT_FILE(argv) : DEFAULT_BIN_PATH;
    UBOOT_DEBUG("upgradeFile=%s\n",upgradeFile);
    if(setUpgradeFileName(upgradeFile)==-1)
    {
        UBOOT_ERROR("Error> set upgrade fail fail\n");
        _show_Error(0);
        setUpgradeMode(EN_UPDATE_MODE_NONE);
        return -1;
    }

     scriptFileSize=getScritSizeOfUpgradeImage();
     if(scriptFileSize==0)
     {
         UBOOT_ERROR("The size of script file is zero \n");
         return -1;
     }

     _script_buf=malloc(scriptFileSize+512);
     if(_script_buf==NULL)
     {
         UBOOT_ERROR("malloc fail \n");
         return -1;
     }
     script_buf=_script_buf;
     memset(script_buf,0,scriptFileSize);
    _show_LoadData(0);
    // load script
    if(LoadScript2DramByFS(upgradeFile,script_buf) != 0)
    {
        goto OAD_FAIL;
    }
#endif

    //set dont overwrite
    #if(ENABLE_MODULE_DONT_OVERWRITE==1)
    dont_overwrite_enable();
    do_force_overwrite_enable();
    #endif
    _show_StartUpgrading(0);

    //run script
    progress_total_cnt=_check_upgrade_script_cmd_count(script_buf);
    if(progress_total_cnt==0)
    {
       UBOOT_ERROR("There are no any commands in the upgrade script file\n");
       goto OAD_FAIL;
    }
    UBOOT_DEBUG("progress_total_cnt=%d\n",progress_total_cnt);

    while ((next_line = get_script_next_line(&script_buf)) != NULL)
    {
        UBOOT_INFO ("\n>> %s \n", next_line);

        progress_cnt++;
        UBOOT_DEBUG("progress_cnt=%d,progress_total_cnt=%d\n",progress_cnt,progress_total_cnt);
        _show_Upgrading(progress_cnt,progress_total_cnt);
        #if(ENABLE_MODULE_DONT_OVERWRITE==1)
        if(check_skip_cmd(next_line)== FALSE)
        {
            if(run_command(next_line, 0) < 0)
            {
                UBOOT_ERROR("Error> cmd: %s Fail !!\n", next_line);
                goto OAD_FAIL;
            }
        }
        #endif

    }

    if(deleteUpgradeFileName()==-1)
    {
        UBOOT_ERROR("delete upgrade name fail\n");
    }

    if(_script_buf!=NULL)
    {
        free(_script_buf);
    }

    _show_Finish(0);
    UBOOT_TRACE("OK\n");
    return 0;

OAD_FAIL:
   _show_Error(0);
    deleteUpgradeFileName();
    setUpgradeMode(EN_UPDATE_MODE_NONE);
    if(_script_buf!=NULL)
    {
        free(_script_buf);
    }
    return -1;
}

#endif

#if (ENABLE_MODULE_ENV_UPGRADE_FROM_BANK == 1)
int do_rstar(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
//=========================================================
    #define ENV_RECOVERY "env_recovery"
    #define SCRIPT_SIZE 0x1000

    char *cEnvRecoveryOffset = getenv(ENV_RECOVERY);
    char *script_buf = NULL;
    char *_script_buf = NULL;
    char *next_line = NULL;

    unsigned int progress_total_cnt = 0;
    unsigned int progress_cnt = 0;
    unsigned int u32RecoveryOffset = 0;

    UBOOT_TRACE("IN\n");

    if (cEnvRecoveryOffset == NULL)
    {
        UBOOT_ERROR("Recovery offset not found\n");
       //_show_Error(0);
       return -1;
    }

    u32RecoveryOffset = (unsigned int)strtol(cEnvRecoveryOffset, NULL, 16);

    _script_buf=malloc(SCRIPT_SIZE);

    if(_script_buf==NULL){
        return -1;
    }

    script_buf = _script_buf;
    memset(script_buf ,0 ,SCRIPT_SIZE);
    raw_read((unsigned int)script_buf, u32RecoveryOffset, SCRIPT_SIZE);

    //Run Script

    progress_total_cnt=_check_upgrade_script_cmd_count(script_buf);
    if(progress_total_cnt==0)
    {
        setUpgradeMode(EN_UPDATE_MODE_NONE);
        free(_script_buf);
        UBOOT_ERROR("There are no any commands in the upgrade script file\n");
       //_show_Error(0);
       return -1;
    }
    UBOOT_DEBUG("progress_total_cnt=%d\n",progress_total_cnt);


    while ((next_line = get_script_next_line(&script_buf)) != NULL)
    {
        UBOOT_INFO("\n>> %s \n", next_line);

        progress_cnt++;
        UBOOT_DEBUG("progress_cnt=%d,progress_total_cnt=%d\n",progress_cnt,progress_total_cnt);
        //_show_Upgrading(progress_cnt,progress_total_cnt);
        if(check_skip_cmd(next_line)== FALSE)//filterCmd
        {
            if(run_command(next_line, 0) < 0)
            {
                free(_script_buf);
                UBOOT_ERROR("Error> cmd: %s Fail !!\n", next_line);
                //_show_Error(0);
                return -1;

            }
        }
    }
#if 0
    if(deleteUpgradeFileName()==-1)
    {
        UBOOT_ERROR("delete upgrade name fail\n");
    }
#endif
    free(_script_buf);
    UBOOT_TRACE("OK\n");
    return 0;

}
#endif

#if ((ENABLE_MODULE_OAD == 1) || (ENABLE_MODULE_USB == 1) || (ENABLE_MODULE_NETUPDATE == 1))
int do_mboot_upgrade(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    #define MBOOT_BUF_ADDR argv[1]
    #define MBOOT_SIZE argv[2]
    char ciscmd[CMD_BUF]="\0";
    UBOOT_TRACE("IN\n");
    unsigned int u32DramBuf = simple_strtoul(MBOOT_BUF_ADDR, NULL, 16);
    unsigned int u32MbootSize = simple_strtoul(MBOOT_SIZE, NULL, 16);

    UBOOT_DEBUG("u32DramBuf   : 0x%x\n",u32DramBuf);
    UBOOT_DEBUG("u32MbootSize : 0x%x\n",u32MbootSize);

    if(mboot_raw_io_Config()!= 0)
    {
        UBOOT_ERROR("raw_io_config setting fail!\n");
        return -1;
    }

    if(get_raw_status()==E_RAW_DATA_IN_SPI)
    {
        UBOOT_INFO("Upgrading Mboot.bin into SPI....\n");
        if(raw_write(u32DramBuf,0,u32MbootSize)!= 0)
        {
            UBOOT_ERROR("raw_write fail!\n");
            return -1;
        }
    }
    else if(get_raw_status()==E_RAW_DATA_IN_NAND)
    {
        UBOOT_INFO("Upgrading RomBoot.bin(MBOOT) into NAND....\n");
        
    	#if (ENABLE_EAGLE) || (ENABLE_EMERALD) || (ENABLE_NIKON) || (ENABLE_KENYA)
    	sprintf(ciscmd,"ncisbl 0x%X 0x%X 0x%X 0x%X 0x%X", \
    	        u32DramBuf,u32DramBuf+0x10000,u32DramBuf+0x20000,u32DramBuf+0x30000,u32MbootSize);
    	#elif (ENABLE_NUGGET)
    	sprintf(ciscmd,"ncishash 0x%X 0x%X 0x%X 0x%X 0x3800 0x%X 0x%X 0x3200", \
                u32DramBuf,u32DramBuf+0x10000,u32DramBuf+0x20000,u32DramBuf+0x30000,u32DramBuf+0x33800,u32MbootSize-0x3800);
    	#else //(ENABLE_EIFFEL) || (ENABLE_NIKE) || (ENABLE_MADISON) || (ENABLE_CLIPPERS) || (ENABLE_MIAMI) || (ENABLE_NADAL) || (ENABLE_EINSTEIN)
    	sprintf(ciscmd,"ncishash 0x%X 0x%X 0x%X 0x%X 0x2800 0x%X 0x%X", \
    	        u32DramBuf,u32DramBuf+0x10000,u32DramBuf+0x20000,u32DramBuf+0x30000,u32DramBuf+0x32800,u32MbootSize-0x2800);	
    	#endif        
        if(run_command(ciscmd,0)!=0)
        {
            UBOOT_ERROR("CMD: ncisbl/ncishash  fail!\n");
            return -1;
        }
        setenv("CISRefresh",NULL);
        saveenv();
    }
    else if(get_raw_status()==E_RAW_DATA_IN_MMC)
    {
        UBOOT_INFO("Upgrading Mboot.bin into EMMC....\n");
        //todo
    }
    else
    {
        UBOOT_ERROR("wrong raw_io_setting !!\n");
        return -1;
    }

    UBOOT_TRACE("OK\n");
    return 0;
}

void RegisterCBShowError(show_Error_cb cb)
{
    UBOOT_TRACE("IN\n");
    fpShow_Error=cb;
    UBOOT_TRACE("OK\n");
}

void RegisterCBShowFinish(show_Finish_cb cb)
{
    UBOOT_TRACE("IN\n");
    fpShow_Finish=cb;
    UBOOT_TRACE("OK\n");
}

void RegisterCBShowLoadData(show_LoadData_cb cb)
{
    UBOOT_TRACE("IN\n");
    fpShow_LoadData=cb;
    UBOOT_TRACE("OK\n");
}

void RegisterCBShowStartUpgrading(show_StartUpgrading_cb cb)
{
    UBOOT_TRACE("IN\n");
    fpShow_StartUpgrading=cb;
    UBOOT_TRACE("OK\n");
}
void RegisterCBShowUpgrading(show_Upgrading_cb cb)
{
    UBOOT_TRACE("IN\n");
    fpShow_upgrading=cb;
    UBOOT_TRACE("OK\n");
}

void UnRegisterShowCb(void)
{
    UBOOT_TRACE("IN\n");
    fpShow_Error=NULL;
    fpShow_Finish=NULL;
    fpShow_LoadData=NULL;
    fpShow_StartUpgrading=NULL;
    fpShow_upgrading=NULL;
    UBOOT_TRACE("OK\n");
}


static int _show_Error(unsigned int var)
{
#if (ENABLE_MODULE_DISPLAY_OSD==1)
    UBOOT_TRACE("IN\n");
    if(fpShow_Error!=NULL)
    {
        UBOOT_TRACE("OK\n");
        return fpShow_Error(var);
    }
    else
    {
        UBOOT_DEBUG("No call back function for 'error' phase\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
#else
    return 0;
#endif
}

static int _show_Finish(unsigned int var)
{
#if (ENABLE_MODULE_DISPLAY_OSD==1)
    UBOOT_TRACE("IN\n");
    if(fpShow_Finish!=NULL)
    {
        UBOOT_TRACE("OK\n");
        return fpShow_Finish(var);
    }
    else
    {
        UBOOT_DEBUG("No call back function for 'finish' phase\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
#else
    return 0;
#endif
}

static int _show_LoadData(unsigned int var)
{
#if (ENABLE_MODULE_DISPLAY_OSD==1)
    UBOOT_TRACE("IN\n");
    if(fpShow_LoadData!=NULL)
    {
        UBOOT_TRACE("OK\n");
        return fpShow_LoadData(var);
    }
    else
    {
        UBOOT_DEBUG("No call back function for 'LoadData' phase\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
#else
    return 0;
#endif
}
static int _show_StartUpgrading(unsigned int var)
{
#if (ENABLE_MODULE_DISPLAY_OSD==1)
    UBOOT_TRACE("IN\n");
    if(fpShow_StartUpgrading!=NULL)
    {
        UBOOT_TRACE("OK\n");
        return fpShow_StartUpgrading(var);
    }
    else
    {
        UBOOT_DEBUG("No call back function for 'StartUpgrading' phase\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
#else
    return 0;
#endif
}

static int _show_Upgrading(unsigned int var1, unsigned int var2)
{
#if (ENABLE_MODULE_DISPLAY_OSD==1)
    UBOOT_TRACE("IN\n");
    if(fpShow_upgrading!=NULL)
    {
        UBOOT_TRACE("OK\n");
        return fpShow_upgrading(var1, var2);
    }
    else
    {
        UBOOT_DEBUG("No call back function for 'Upgrading' phase\n");
        UBOOT_TRACE("OK\n");
        return 0;
    }
#else
    return 0;
#endif
}

static unsigned int _check_upgrade_script_cmd_count(char *buffer)
{
    unsigned int scriptFileSize=0;
    unsigned int amount=0;
    char *tempBuf=NULL;

    UBOOT_TRACE("IN\n");
    scriptFileSize=getScritSizeOfUpgradeImage();
    if(scriptFileSize==0)
    {
        UBOOT_ERROR("The size of script file is zero \n");
        return 0;
    }

    tempBuf=malloc(scriptFileSize);
    if(tempBuf==NULL)
    {
        UBOOT_ERROR("malloc fail \n");
        return 0;
    }
    memcpy(tempBuf,buffer,scriptFileSize);
    amount=check_script_cmd_count(tempBuf);
    free(tempBuf);

    UBOOT_TRACE("OK\n");
    return amount;
}

#endif

