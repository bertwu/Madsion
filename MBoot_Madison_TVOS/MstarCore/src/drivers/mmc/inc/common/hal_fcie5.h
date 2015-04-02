//
// hal_flash_ctrl.h
//

#ifndef HAL_FLASH_CTRL_H
#define HAL_FLASH_CTRL_H




#define USE_BYTE_MODE       1
#define MIU_WIDTH           4

#define R_SDIO_DET_N            WBIT07

#define SD_CMD_TIMEOUT_VALUE HW_TIMER_DELAY_1s*2
#if defined(CONFIG_MSTAR_ARM_BD_FPGA)
#define SD_DMA_TIMEOUT_VALUE 5000000
#else
#define SD_DMA_TIMEOUT_VALUE HW_TIMER_DELAY_1s*10
#endif

/*typedef enum
{
    IO_SUCCESS              = 0x00,
    IO_TIME_OUT             = 0x01,
    IO_D0_HIGH_TIME_OUT     = 0x02,
    IO_CMD_TIME_OUT         = 0x03,
    IO_DMA_TIME_OUT         = 0x04,
    IO_CARD_REMOVED         = 0x05,
    IO_ERROR                = 0x06,

    IO_VOLTAGE_NOT_ACCEPT   = 0x07,
    IO_MISS_CHECK_PATTERN   = 0x08,
    IO_WRONG_CSD_STRUCT     = 0x09,

    IO_CMD_NO_RSP           = 0x16,
    IO_RSP_CRC_ERROR        = 0x17,
    IO_RSP_ERROR            = 0x18,

    IO_R_DATA_CRC_ERROR     = 0x20,
    IO_W_DATA_STS_ERROR     = 0x21,
    IO_W_DATA_STS_NEGATIVE  = 0x22,

    IO_STILL_POWERING_UP    = 0x30,

    IO_CARD_CHANGED         = 0x40,

    IO_FIFO_CLK_NOT_READY   = 0xE0,
    IO_NO_LAST_DONE_Z       = 0xE1,
    IO_JOB_DIR_SETUP_FAIL   = 0xE2,

    IO_NO_IP_2_USE          = 0xFF,

} E_IO_STS;*/


typedef union _CMD
{
    U8 Array[17];

	eMMC_PACK0 struct
	{
		U8 Index;
		U32 Arg;
		U8 Reserve[12];

	} eMMC_PACK1 Cmd;

} CMD;

typedef union _RSP
{
    U8 Array[17];

	eMMC_PACK0 struct
	{
		U8 Index;
		U32 DeviceStatus;
		U8 Reserve[12];

	} eMMC_PACK1 Rsp;

} RSP;

typedef enum
{
    CMD_TYPE_BC     = 0, // broadcast command
    CMD_TYPE_BCR    = 1, // broadcast command with response
    CMD_TYPE_AC     = 2, // addressed command
    CMD_TYPE_ADTC   = 3, // addressed data transfer command

} E_CMD_TYPE;

typedef enum
{
    RSP_TYPE_NO  = 0,
    RSP_TYPE_R1  = 1,
    RSP_TYPE_R1b = 2,
    RSP_TYPE_R2  = 3,
    RSP_TYPE_R3  = 4,
    RSP_TYPE_R4  = 5,
    RSP_TYPE_R5  = 6,
    RSP_TYPE_R6  = 7,
    RSP_TYPE_R7  = 8, // SD CMD08 send if cond

} E_RSP_TYPE;

typedef enum
{
    SYNC_TIMING_DEFAULT     = 0,
    SYNC_TIMING_HIGH_SPEED  = 1,

} E_SYNC_TIMING;

typedef enum
{
    DIR_R = 0,
    DIR_W = 1,

} E_RWDIR;

typedef enum
{
    PATH_R2N	= 0, // only GPIO_PAD & 8 bits macro can use R2N
    PATH_DMA	= 1,
    PATH_ADMA	= 2,

} E_PATH;

typedef enum
{
    BUS_1_BIT   = 0,
    BUS_4_BITS  = 1,
    BUS_8_BITS  = 2,

} E_DATA_BUS;

typedef struct _CMD_RSP_INFO
{
	U32				CardClock;
	CMD				Command;
	RSP				Response;

	E_CMD_TYPE		CmdType;
	E_RSP_TYPE		RspType;

	// add for data transfer
	E_RWDIR			ReadWriteDir;
	E_PATH			DataPath; // R2N or DMA
	E_DATA_BUS		BusWidth;

	U32				MiuAddr;	// DMA & ADMA use only, this is a MIU address
	U32 *			pBufferAddr; // R2N use only, this is a data buffer pointer
	U16				BlockSize;
	U16				BlockCount; // ADMA don't care

} CMD_RSP_INFO;


U8		HalFcie_CmdFifoGet(U8 u8addr);
void	HalFcie_CmdFifoSet(U8 u8addr, U8 u8value);
U32		HalFcie_SendCommand(CMD_RSP_INFO * pCmdRspInfo);
void	HalFcie_SetFlag4Kernel2RuneMMC(void);
U8	HalFcie_CheckIfeMMCRun4Kernel(void);
U32 	eMMC_WaitCIFD_Event(U16 u16_WaitEvent, U32  u32_MicroSec);
U32 	eMMC_WaitSetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt);
U32 	eMMC_WaitGetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt);

#endif

