//
// hal_fcie.c
//

//#include "eMMC_config.h"

#include "eMMC.h"

#ifdef IP_FCIE_VERSION_5

#include "hal_fcie5.h"


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


// total 17 bytes 0~16
U8 HalFcie_CmdFifoGet(U8 u8addr)
{
    U16 u16Tmp;

	if(u8addr>16) eMMC_debug(1, 1, "eMMC Err: Cmd FIFO addr overflow in get %d\n", u8addr);

	//REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

	u16Tmp = REG_FCIE(FCIE_CMDFIFO_ADDR(u8addr>>1));

	//REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

    if(u8addr&0x1)
    {
        return (U8)(u16Tmp>>8);
    }
    else
    {
        return (U8)(u16Tmp&0xFF);
    }
}

// total 17 bytes 0~16
void HalFcie_CmdFifoSet(U8 u8addr, U8 u8value)
{
    U16 u16Tmp;

	if(u8addr>16) eMMC_debug(1, 1, "eMMC Err: Cmd FIFO addr overflow to set %d\n", u8addr);

	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

	u16Tmp = REG_FCIE(FCIE_CMDFIFO_ADDR(u8addr>>1));

    if(u8addr & 1)
    {
        u16Tmp = (u8value<<8) + (u16Tmp&0xFF);
    }
    else
    {
        u16Tmp = (u16Tmp&0xFF00)+u8value;
    }

	REG_FCIE_W(FCIE_CMDFIFO_ADDR(u8addr>>1), u16Tmp);

	REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_CHK_CMD);

}



U32 eMMC_WaitCIFD_Event(U16 u16_WaitEvent, U32  u32_MicroSec)
{
	volatile U32 u32_Count;
	volatile U16 u16_Reg;

	for (u32_Count=0; u32_Count < u32_MicroSec; u32_Count++)
	{
		REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
		if ((u16_Reg & u16_WaitEvent) == u16_WaitEvent)
			break;

		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
	}
	if (u32_Count >= u32_MicroSec)
	{
		REG_FCIE_R(NC_CIFD_EVENT, u16_Reg);
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "CIFD Event Timout %X\n", u16_Reg);
	}
	return u32_Count;
}

U32 eMMC_WaitSetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt)
{
	U16 u16_i, *pu16_Data = (U16*)pu32_DataBuf;

	if(u32_ByteCnt > FCIE_CIFD_BYTE_CNT)
	{
		return eMMC_ST_ERR_INVALID_PARAM;
	}

	for(u16_i=0; u16_i<(u32_ByteCnt>>1); u16_i++)
		REG_FCIE_W(NC_RBUF_CIFD_ADDR(u16_i), pu16_Data[u16_i]);

	REG_FCIE_SETBIT(NC_CIFD_EVENT, BIT_RBUF_FULL_TRI);

	if (eMMC_WaitCIFD_Event(BIT_RBUF_EMPTY, HW_TIMER_DELAY_500ms)== (HW_TIMER_DELAY_500ms ))
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1, "eMMC Err: set CIFD timeout 0, ErrCode:%Xh\r\n", eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT);
		return eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT; // timeout
	}

	REG_FCIE_SETBIT(NC_CIFD_EVENT, BIT_RBUF_EMPTY); // W1C

	return eMMC_ST_SUCCESS;
}


U32 eMMC_WaitGetCIFD(U32 * pu32_DataBuf, U32 u32_ByteCnt)
{
	U16 u16_i, *pu16_Data = (U16*)pu32_DataBuf;

	//eMMC_debug(1, 1, "wait 64 bytes CIFD and copy to %08X\n", (U32)pu32_DataBuf);

	if(u32_ByteCnt > FCIE_CIFD_BYTE_CNT)
	{
		return eMMC_ST_ERR_INVALID_PARAM;
	}
	if (eMMC_WaitCIFD_Event(BIT_WBUF_FULL, HW_TIMER_DELAY_500ms)== (HW_TIMER_DELAY_500ms ))
	{
		eMMC_debug(1, 1, "eMMC Err: get CIFD timeout 0, ErrCode:%Xh\r\n", eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT);
		return eMMC_ST_ERR_TIMEOUT_WAITCIFDEVENT; // timeout
	}

	for(u16_i=0; u16_i<(u32_ByteCnt>>1); u16_i++)
		REG_FCIE_R(NC_WBUF_CIFD_ADDR(u16_i), pu16_Data[u16_i]);

	REG_FCIE_W(NC_CIFD_EVENT, BIT_WBUF_FULL); // W1C

	REG_FCIE_W(NC_CIFD_EVENT, BIT_WBUF_EMPTY_TRI);

	return eMMC_ST_SUCCESS;
}



#define HalFcie_ClearErrSts() do { \
    REG_FCIE_W(FCIE_SD_STATUS, BITS_ERROR); \
} while(0)


U32 eMMC_FCIE_WaitEvents(U32 u32_RegAddr, U16 u16_Events, U32 u32_MicroSec)
{
    //eMMC_debug(0, 0, "\033[32m%s\033[m\n", __FUNCTION__);
	#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
	return eMMC_WaitCompleteIntr(u32_RegAddr, u16_Events, u32_MicroSec);
	#else
	return eMMC_FCIE_PollingEvents(u32_RegAddr, u16_Events, u32_MicroSec);
	#endif
}


U32 eMMC_FCIE_PollingEvents(U32 u32_RegAddr, U16 u16_Events, U32 u32_MicroSec)
{
	volatile U32 u32_i;
	volatile U16 u16_val;

    //eMMC_debug(0, 0, "\033[32m%s\033[m\n", __FUNCTION__);

    //if( g_eMMCDrv.u8_make_sts_err )
    //{
    //    eMMC_debug(0, 0, "\033[7;36mg_eMMCDrv.u8_make_sts_err=%X\033[m\n", g_eMMCDrv.u8_make_sts_err);
    //    eMMC_debug(0, 0, "\033[7;36mDump FCIE register before waiting\033[m\n");
    //    eMMC_FCIE_DumpRegisters();
    //}

	for(u32_i=0; u32_i<u32_MicroSec; u32_i++)
	{
		eMMC_hw_timer_delay(HW_TIMER_DELAY_1us);
		REG_FCIE_R(u32_RegAddr, u16_val);

        #if 1
        if((u32_RegAddr==FCIE_MIE_EVENT) && (u16_val & BIT_ERR_STS))
        {
            eMMC_debug(0, 0, "eMMC Err: %u us, Reg %04Xh=%04X, but wanted %04Xh\n",
                u32_MicroSec,
                (u32_RegAddr-FCIE_MIE_EVENT)>>REG_OFFSET_SHIFT_BITS,
                u16_val, u16_Events);
            REG_FCIE_R(FCIE_SD_STATUS, u16_val);
            eMMC_debug(0, 0, "SD_STS=%04X\n", u16_val);

            if( u16_val & BIT_DAT_RD_CERR )
            {
                eMMC_debug(0, 0, "\033[7;35mData read CRC error\033[m\n");
                return eMMC_ST_ERR_DATA_MISMATCH;
            }
            else if( u16_val & BIT_DAT_WR_CERR )
            {
                eMMC_debug(0, 0, "\033[7;35mData write CRC error\033[m\n");
                return eMMC_ST_ERR_DATA_MISMATCH;
            }
            else if( u16_val & BIT_DAT_WR_TOUT )
            {
                eMMC_debug(0, 0, "\033[7;35mData write timeout error\033[m\n");
                return eMMC_ST_ERR_DATA_MISMATCH;
            }
            else if( u16_val & BIT_CMD_NO_RSP )
            {
                eMMC_debug(0, 0, "\033[7;35mCommand no response error\033[m\n");
                return eMMC_ST_ERR_DATA_MISMATCH;
            }
            else if( u16_val & BIT_CMD_RSP_CERR )
            {
                eMMC_debug(0, 0, "\033[7;35mCommand response CRC error\033[m\n");
                return eMMC_ST_ERR_DATA_MISMATCH;
            }
            else if( u16_val & BIT_DAT_RD_TOUT )
            {
                eMMC_debug(0, 0, "\033[7;35mData read wait start bit timeout error\033[m\n");
                return eMMC_ST_ERR_DATA_MISMATCH;
            }
            else if( u16_val & BIT_SD_CARD_BUSY )
            {
                eMMC_debug(0, 0, "\033[7;35meMMC busy error\033[m\n");
                return eMMC_ST_ERR_DATA_MISMATCH;
            }
            else
            {
                eMMC_debug(0, 0, "Unknown type error!!!\n");
                eMMC_debug(0, 0, "Ask Brian for debugging......!!!\n");
                eMMC_DumpPadClk();
                eMMC_FCIE_DumpRegisters();
                while(1);
            }
        }
        #endif

		if(u16_Events == (u16_val & u16_Events))
        {
            if( (REG_FCIE(FCIE_SD_CTRL) & BIT_ERR_DET_ON) == 0 ) // why check reg_err_det_on
            {
			    break;
            }
        }
	}

	if(u32_i == u32_MicroSec)
	{
		eMMC_debug(eMMC_DEBUG_LEVEL_ERROR, 1,
			"eMMC Err: %u us, Reg.%04Xh: %04Xh, but wanted: %04Xh\n",
			u32_MicroSec,
			(u32_RegAddr-FCIE_MIE_EVENT)>>REG_OFFSET_SHIFT_BITS,
			u16_val, u16_Events);

		return eMMC_ST_ERR_TIMEOUT_WAIT_REG0;
	}

	return eMMC_ST_SUCCESS;
}

//#define PRINT_CMD_RSP

U32 HalFcie_SendCommand(CMD_RSP_INFO * pCmdRspInfo)
{
    //E_IO_STS IoSts = IO_SUCCESS;
    U8 i;
	U16 u16_reg;
	U16 u16Index = 0;
	U32 u32_err = eMMC_ST_SUCCESS;
	const U8 u8CmdSize = 5; // command always 6 bytes, exclude CRC is fix to 5
	U8 u8RspSize = 0;

	// setup response size from response type
	switch(pCmdRspInfo->RspType) {
		case RSP_TYPE_NO:
			u8RspSize = 0;
			break;
		case RSP_TYPE_R2:
			u8RspSize = 16; // not include CRC byte
			break;
		default:
			u8RspSize = 5; // not include CRC byte
			break;
	}

#ifdef PRINT_CMD_RSP
	//eMMC_debug(1, 0, "\r\n");
	//eMMC_debug(1, 0, "\33[1;31mCMD%d_\33[m", 0xBF&pCmdRspInfo->Command.Cmd.Index);
	eMMC_debug(1, 0, "CMD%d_", 0xBF&pCmdRspInfo->Command.Cmd.Index);
	eMMC_debug(1, 0, "[%d] ", u8CmdSize);
    for(i=0; i<u8CmdSize; i++)
    {
        eMMC_debug(1, 0, "%02X ", pCmdRspInfo->Command.Array[i]);
    }
	if(pCmdRspInfo->Command.Cmd.Index==0x46) {
		switch(pCmdRspInfo->Command.Array[2]) {
			case 0xAF: eMMC_debug(1, 0, "[ERASE GROUP]");	break;
			case 0xB7: eMMC_debug(1, 0, "[BUS WIDTH]");	break;
			case 0xB9: eMMC_debug(1, 0, "[HS TIMING]");	break;
			case 0xA1: eMMC_debug(1, 0, "[HPI]");			break;
			case 0x21: eMMC_debug(1, 0, "[CACHE CTRL]");	break;
			case 0xBB: eMMC_debug(1, 0, "[POWER CLASS]");	break;
			case 0xB3: eMMC_debug(1, 0, "[PART CONFIG]");	break;
			default:
				eMMC_debug(1, 0, "ExtCSD index: %d %02Xh", pCmdRspInfo->Command.Array[2], pCmdRspInfo->Command.Array[2]);
				break;
		}
	}
#endif

	eMMC_FCIE_ClearEvents();

	//eMMC_debug(1, 1, "FCIE_MIE_EVENT = %04X\r\n", REG_FCIE(FCIE_MIE_EVENT));
    //HalFcie_EnableCardInf(R_SD_EN);
    //HalFcie_SetClock(pCmdRspInfo->CardClock);

    REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_CLK_EN);
    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_DATA_SYNC);

	// setup command & response size
	// hardware generate the last CRC byte automatically
	// hardware check the last CRC byte automatically
	REG_FCIE_W(FCIE_CMD_RSP_SIZE, (u8CmdSize<<BIT_CMD_SIZE_SHIFT) + u8RspSize );

	// prepare command FIFO
    for(i=0; i<u8CmdSize; i++)
    {
        HalFcie_CmdFifoSet(i, pCmdRspInfo->Command.Array[i]);
    }

	REG_FCIE_W(FCIE_SD_CTRL, 0); // clear first

	if(pCmdRspInfo->CmdType!=CMD_TYPE_ADTC) // simple command
	{
		switch(pCmdRspInfo->RspType) {
			case RSP_TYPE_NO:
				//eMMC_debug(1, 1, "command only");
		        REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN);
				break;
			case RSP_TYPE_R2:
				//eMMC_debug(1, 1, "cmd + r2\r\n");
    	        REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN + BIT_SD_RSP_EN + BIT_SD_RSPR2_EN);
				break;
			case RSP_TYPE_R1:
			case RSP_TYPE_R1b:
			case RSP_TYPE_R3:
			//case RSP_TYPE_R4:
			//case RSP_TYPE_R5:
			default:
				//eMMC_debug(1, 1, "cmd + rsp\r\n");
    	        REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN + BIT_SD_RSP_EN);
				break;
		}

		#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
			REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_CMD_END);
		#endif

	}
	else // data transfer command
	{
		// we can enable cmd + data at the same time in read
		if(pCmdRspInfo->ReadWriteDir==DIR_R)
		{
           	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN+BIT_SD_RSP_EN+BIT_SD_DTRX_EN);

			if(pCmdRspInfo->DataPath==PATH_ADMA) {

				REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_ADMA_EN); // ADMA read
			}
			#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
				REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_DMA_END);
			#endif
		}
		else // write can not send data with cmd at the same time
		{
           	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_CMD_EN+BIT_SD_RSP_EN);
			#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
				REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_CMD_END);
			#endif
		}


		//if(pCmdRspInfo->ReadWriteDir==DIR_W) {
		//	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_SD_DAT_DIR_W);
		//}

	    /*if( g_eMMCDrv.u8_make_sts_err == FCIE_MAKE_WR_TOUT_ERR )
	    {
	        REG_FCIE_W(FCIE_WR_SBIT_TIMER, BIT_WR_SBIT_TIMER_EN|0x02);
	        REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN|BIT_SD_DAT_DIR_W|BIT_JOB_START|BIT_ERR_DET_ON);
	    }*/

		switch(pCmdRspInfo->DataPath)
		{
			case PATH_DMA:
			case PATH_ADMA:
				REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_DATA_DEST);
				break;
			case PATH_R2N:
				REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_DATA_DEST);
				break;
			default:
				eMMC_debug(1, 1, "eMMC Err: wrong data destination\r\n");
				break;
		}

		//eMMC_debug(1, 1, "FCIE_SD_MODE = %04X\r\n", REG_FCIE(FCIE_SD_MODE));

		// data bus width setup
		REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_MASK);
		if(pCmdRspInfo->BusWidth==BUS_4_BITS) {
			//eMMC_debug(1, 0, "4 bits\n");
			REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_4);
		}
		else if(pCmdRspInfo->BusWidth==BUS_8_BITS) {
			//eMMC_debug(1, 0, "8 bits\n");
			REG_FCIE_SETBIT(FCIE_SD_MODE, BIT_SD_DATA_WIDTH_8);
		}
		else {
			//eMMC_debug(1, 0, "1 bit\n");
		}

		REG_FCIE_W(FCIE_BLK_SIZE, pCmdRspInfo->BlockSize);

		REG_FCIE_W(FCIE_MIU_DMA_ADDR_15_0,  pCmdRspInfo->MiuAddr & 0xFFFF);
		REG_FCIE_W(FCIE_MIU_DMA_ADDR_31_16, pCmdRspInfo->MiuAddr >> 16);

		if(pCmdRspInfo->DataPath!=PATH_ADMA) // normal DMA or R2N
		{
			REG_FCIE_W(FCIE_JOB_BL_CNT, pCmdRspInfo->BlockCount);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0,  (pCmdRspInfo->BlockCount*pCmdRspInfo->BlockSize) & 0xFFFF);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, (pCmdRspInfo->BlockCount*pCmdRspInfo->BlockSize) >> 16);
		}
		else // ADMA
		{
			REG_FCIE_W(FCIE_JOB_BL_CNT, 1);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_15_0,  0x0010);
			REG_FCIE_W(FCIE_MIU_DMA_LEN_31_16, 0x0000);
		}
	}


	#if 0 // debug use only ------------------------------------------------------------------------
	if((0xBF&pCmdRspInfo->CmdRsp.Command[0])==1)
	{
		eMMC_debug(1, 1, "while(1) on purpose\n"); while(1);
	}
	#endif // debug use only -----------------------------------------------------------------------


	REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_JOB_START); // start action


	if(pCmdRspInfo->CmdType!=CMD_TYPE_ADTC) // simple command
	{
		u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_CMD_END, TIME_WAIT_CMDRSP_END);
		if(u32_err==eMMC_ST_ERR_ERR_DET)
		{
			eMMC_debug(1, 1, "eMMC Err: fcie detect error while wait simple cmd end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
			goto ErrorHandle;
		}
		else if(u32_err==eMMC_ST_ERR_TIMEOUT_WAIT_REG0)
		{
			eMMC_debug(1, 1, "eMMC Err: wait simple cmd end timeout\r\n");
			goto ErrorHandle;
		}
    }
    else // data transfer command
    {
		if(pCmdRspInfo->ReadWriteDir==DIR_R) // read adtc
		{
			// R2N need wait for more events
			if(pCmdRspInfo->DataPath==PATH_R2N)
			{
				// read out 64 bytes per time, read 8 times in 512 bytes case
				for(u16Index=0; u16Index<8; u16Index++)
				{
					u32_err = eMMC_WaitGetCIFD( pCmdRspInfo->pBufferAddr + (u16Index<<4), 64);
					if(u32_err)
					{
						eMMC_debug(1, 1, "eMMC Err: wait get CIFD fail\r\n");
						eMMC_FCIE_ErrHandler_Stop();
						goto ErrorHandle;
					}
				}
			}

	        u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_DMA_END, SD_DMA_TIMEOUT_VALUE);
			if(u32_err==eMMC_ST_ERR_ERR_DET)
			{
				eMMC_debug(1, 1, "eMMC Err: fcie detect error while wait read end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
				goto ErrorHandle;
			}
			else if(u32_err==eMMC_ST_ERR_TIMEOUT_WAIT_REG0)
			{
				eMMC_debug(1, 1, "eMMC Err: wait read end timeout\r\n");
				goto ErrorHandle;
			}
		}
		else // write adtc
		{
			// need to wait cmd finish then start the data transfer in write
			u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_CMD_END, SD_CMD_TIMEOUT_VALUE);
			if(u32_err==eMMC_ST_ERR_ERR_DET)
			{
				eMMC_debug(1, 1, "eMMC Err: fcie detect error while wait write cmd end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
				goto ErrorHandle;
			}
			else if(u32_err==eMMC_ST_ERR_TIMEOUT_WAIT_REG0)
			{
				eMMC_debug(1, 1, "eMMC Err: wait write cmd end timeout\r\n");
				goto ErrorHandle;
			}

			//REG_FCIE_CLRBIT(FCIE_SD_CTRL, BIT_SD_RSPR2_EN+BIT_SD_RSP_EN+BIT_SD_CMD_EN+BIT_SD_DTRX_EN+BIT_SD_DAT_DIR_W);
			REG_FCIE_W(FCIE_SD_CTRL, BIT_SD_DTRX_EN+BIT_SD_DAT_DIR_W);

			if(pCmdRspInfo->DataPath==PATH_ADMA) {

				REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_ADMA_EN); // ADMA write
			}

			#if defined(ENABLE_eMMC_INTERRUPT_MODE)&&ENABLE_eMMC_INTERRUPT_MODE
				REG_FCIE_SETBIT(FCIE_MIE_INT_EN, BIT_DMA_END);
			#endif


			REG_FCIE_SETBIT(FCIE_SD_CTRL, BIT_JOB_START); // start action


			// R2N
			if(pCmdRspInfo->DataPath==PATH_R2N)
			{
				// write in 64 bytes per time, read 8 times in 512 bytes case
				for(u16Index=0; u16Index<8; u16Index++)
				{
					u32_err = eMMC_WaitSetCIFD( pCmdRspInfo->pBufferAddr + (u16Index<<4), 64);
					if(u32_err)
					{
						eMMC_debug(1, 1, "eMMC Err: wait set CIFD fail\r\n");
						eMMC_FCIE_ErrHandler_Stop();
						goto ErrorHandle;
					}
				}
			}

	        u32_err = eMMC_FCIE_WaitEvents(FCIE_MIE_EVENT, BIT_DMA_END, SD_DMA_TIMEOUT_VALUE);
			if(u32_err==eMMC_ST_ERR_ERR_DET)
			{
				eMMC_debug(1, 1, "eMMC Err: fcie detect error while wait dma end, FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
				goto ErrorHandle;
			}
			else if(u32_err==eMMC_ST_ERR_TIMEOUT_WAIT_REG0)
			{
				eMMC_debug(1, 1, "eMMC Err: wait dma end timeout\r\n");
				goto ErrorHandle;
			}
		}

    }

	u16_reg = REG_FCIE(FCIE_SD_STATUS);

	//eMMC_debug(1, 0, "FCIE_SD_STATUS = %04X", u16_reg);

	if( ((pCmdRspInfo->RspType==RSP_TYPE_R2)||(pCmdRspInfo->RspType==RSP_TYPE_R3)) && ((u16_reg&BITS_ERROR)==BIT_CMD_RSP_CERR) ) {
		// patch hardware false alarm of R2 response CRC error
		//printf("patch hardware false alarm of R2 response CRC error\r\n");
	    REG_FCIE_W(FCIE_SD_STATUS, BIT_CMD_RSP_CERR);
	}
	else if(u16_reg&BITS_ERROR) {
		eMMC_debug(1, 0, "eMMC Err: FCIE_SD_STATUS = %04X\n", REG_FCIE(FCIE_SD_STATUS));
		if(u16_reg&BIT_SD_R_CRC_ERR)	eMMC_debug(1, 0, "eMMC Err: read CRC error\n");
		if(u16_reg&BIT_DAT_WR_CERR)		eMMC_debug(1, 0, "eMMC Err: write CRC status error\n");
		if(u16_reg&BIT_DAT_WR_TOUT)		eMMC_debug(1, 0, "eMMC Err: transmitted data phase to error\n");
		if(u16_reg&BIT_CMD_NO_RSP)		eMMC_debug(1, 0, "eMMC Err: command no response\n");
		if(u16_reg&BIT_CMD_RSP_CERR)	eMMC_debug(1, 0, "eMMC Err: response CRC error\n");
		if(u16_reg&BIT_DAT_RD_TOUT)		eMMC_debug(1, 0, "eMMC Err: received data phase to error\n");
		HalFcie_ClearErrSts();
		u32_err = eMMC_ST_ERR_FCIE_STS_ERR;
		goto ErrorHandle;
	}

	// After CMD18, data might be possible all low in D0 to cause timeout here.
    //if(pCmdRspInfo->SkipWaitData0==0)
    if(pCmdRspInfo->RspType==RSP_TYPE_R1b)
    {
		u32_err = eMMC_FCIE_WaitD0High(TIME_WAIT_DAT0_HIGH);
        if(u32_err)
        {
			eMMC_debug(1, 0, "eMMC Err: wait D0 high timeout in sned cmd\n");
			while(1);
            goto ErrorHandle;
        }
    }

    if(u8RspSize)
    {
		#ifdef PRINT_CMD_RSP
		eMMC_debug(1, 0, ", RSP(%d): ", u8RspSize);
		#endif
        for(i=0; i<u8RspSize; i++) // last CRC didn't copy to CIFC
        {
            pCmdRspInfo->Response.Array[i] = HalFcie_CmdFifoGet(i);
			#ifdef PRINT_CMD_RSP
			eMMC_debug(1, 0, "%02X ", pCmdRspInfo->Response.Array[i]);
			#endif
        }
		#ifdef PRINT_CMD_RSP
        eMMC_debug(1, 0, "\n");
		#endif
        /*if(HalFcie_CheckResponse())
        {
            LOG_FCIE(L_FCIE_ERROR, "Error!!! Response Error!\r\n");
            goto ErrorHandle;
        }*/
    }
    else
    {
		#ifdef PRINT_CMD_RSP
        eMMC_debug(1, 0, "\n");
		#endif
    }

    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_CLK_EN); // turn off clock after command finish

    return eMMC_ST_SUCCESS;

ErrorHandle:

    eMMC_debug(1, 0, "eMMC Err: send cmd fail 0x%02X!\r\n", u32_err);

	eMMC_FCIE_ErrHandler_Stop();

    REG_FCIE_CLRBIT(FCIE_SD_MODE, BIT_SD_CLK_EN); // turn off clock after command finish even fail

    return u32_err;
}


void HalFcie_SetFlag4Kernel2RuneMMC(void)
{
    REG_FCIE_CLRBIT(FCIE_MIE_FUNC_CTL, BIT_KERN_CHK_NAND_EMMC_MSK);
    REG_FCIE_SETBIT(FCIE_MIE_FUNC_CTL, BIT_KERN_EMMC);
}

U8 HalFcie_CheckIfeMMCRun4Kernel(void)
{
	#if defined(CONFIG_MSTAR_ARM_BD_FPGA)

		return 1;

	#else

	    u16 u16_regval = 0;

	    u16_regval = REG_FCIE(FCIE_MIE_FUNC_CTL);

	    if( (u16_regval & BIT_KERN_CHK_NAND_EMMC) == BIT_KERN_CHK_NAND_EMMC )
	    {
	        return ( (u16_regval & BIT_KERN_EMMC) != BIT_KERN_EMMC ) ? 0 : 1;
	    }
		return 0;

	#endif
}

void eMMC_DumpTimingTable(void)
{
	eMMC_debug(1, 1, "complete me\n");
}

#endif // IP_FCIE_VERSION_5


