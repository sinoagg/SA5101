//==============================================================================
//
// Title:		i_tProtocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/18 at 10:51:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include "i_tPanel.h"
#include "i_tProtocol.h"
#include "Graph.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Extern Global variables
extern unsigned char comSelect;

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
/*------------------------------------------------------------------*/
/*  自定义函数;发送电压值命令                                       */
/*------------------------------------------------------------------*/
 char initialFrameHead[2] = {0xAA};
 char initialFrameFreq[3] = {0x03,0x04};
 char initialFrameData[3] = {0};
 char initialFrameCalibration[2] = {0};
 char initialSendBuf[6] = {0};
 char initialSendnBuf[12] = {0};
 char Analogboard_V_x1[] = {0xAA ,0X09, 0X01, 0X00, 0X01, 0X09};
 char Analogboard_V_x51[] = {0xAA ,0X9A, 0X01, 0X00, 0X84, 0X1F};
 char Analogboard_V_x5[] = {0xAA ,0X09, 0X01, 0X00, 0X02, 0X0A};

void send_cmd_vol(double vol)
{
	char  return_voltage = 0;
	if( abs(vol) < 2.5 )
	{
		return_voltage = (((vol/(-2.5)) + 1) / 2) * 65536;
		initialFrameData[0] = return_voltage >> 8;
		initialFrameData[1] = return_voltage & 0xFF;
		initialFrameCalibration[0] = initialFrameFreq[0] ^ initialFrameFreq[1] ^ initialFrameData[0] ^ initialFrameData[1];

		memcpy(initialSendBuf,initialFrameHead,1);
		memcpy(initialSendBuf + 1,initialFrameFreq,2);
		memcpy(initialSendBuf + 1 + 2,initialFrameData,2);
		memcpy(initialSendBuf + 1 + 2 + 2,initialFrameCalibration,1);
		FlushInQ (comSelect);  //清空输入队列缓冲区
		FlushOutQ (comSelect);
		ComWrt (comSelect,initialSendBuf,6);
		ComWrt (comSelect,Analogboard_V_x1,6);
	}
	else
	{
		return_voltage = ((((vol/5.1)/(-2.5)) + 1) / 2) * 65536;
		initialFrameData[0] = return_voltage >> 8;
		initialFrameData[1] = return_voltage & 0xFF;
		initialFrameCalibration[0] = initialFrameFreq[0] ^ initialFrameFreq[1] ^ initialFrameData[0] ^ initialFrameData[1];

		memcpy(initialSendBuf,initialFrameHead,1);
		memcpy(initialSendBuf + 1,initialFrameFreq,2);
		memcpy(initialSendBuf + 1 + 2,initialFrameData,2);
		memcpy(initialSendBuf + 1 + 2 + 2,initialFrameCalibration,1);
		FlushInQ (comSelect);  //清空输入队列缓冲区
		FlushOutQ (comSelect);
		ComWrt (comSelect,initialSendBuf,6);
		ComWrt (comSelect,Analogboard_V_x51,6);
		Delay(0.5);
		ComWrt (comSelect,Analogboard_V_x5,6);
	}
}

/*------------------------------------------------------------------*/
/*自定义函数;发送采样间隔命令                                       */
/*------------------------------------------------------------------*/
 char   SamIntFrameHead[3] = {0xAA,0x09};
 char   SamIntFrame_L_Data[4] = {0};
 char   SamIntFrame_H_Data[4] = {0};
 char   SamIntFrame_L_Calibration[2] = {0};
 char   SamIntFrame_H_Calibration[2] = {0};
 char   SamIntSend_L_Buf[6] = {0};
 char   SamIntSend_H_Buf[6] = {0};
void send_cmd_SamInt (int t)
{
	long long cnt = 0;
	cnt = (t * 1000000000) / 20;
	SamIntFrame_L_Data[0] = ((cnt >> 16) & 0x000000003) | 0x000000094;
	SamIntFrame_L_Data[1] = (cnt >> 8) & 0x0000000ff;
	SamIntFrame_L_Data[2] = cnt & 0x0000000ff;
	SamIntFrame_L_Calibration[0] = SamIntFrameHead[1] ^ SamIntFrame_L_Data[0] ^ SamIntFrame_L_Data[1] ^ SamIntFrame_L_Data[2];

	SamIntFrame_H_Data[0] = ((cnt >> 34) & 0x000000003) | 0x000000098;
	SamIntFrame_H_Data[1] = (cnt >> 26) & 0x0000000FF;
	SamIntFrame_H_Data[2] = (cnt >> 18) & 0X0000000FF;
	SamIntFrame_H_Calibration[0] = SamIntFrameHead[1] ^ SamIntFrame_H_Data[0] ^ SamIntFrame_H_Data[1] ^ SamIntFrame_H_Data[2];

	memcpy(SamIntSend_L_Buf,SamIntFrameHead,2);
	memcpy(SamIntSend_L_Buf + 2,SamIntFrame_L_Data,3);
	memcpy(SamIntSend_L_Buf + 2 + 3,SamIntFrame_L_Calibration,1);

	memcpy(SamIntSend_H_Buf,SamIntFrameHead,2);
	memcpy(SamIntSend_H_Buf + 2,SamIntFrame_H_Data,3);
	memcpy(SamIntSend_H_Buf + 2 + 3,SamIntFrame_H_Calibration,1);

	FlushInQ (comSelect);  //清空输入队列缓冲区
	FlushOutQ (comSelect);
	ComWrt (comSelect,SamIntSend_L_Buf,6);
	ComWrt (comSelect,SamIntSend_H_Buf,6);
}
void send_itcmd(void)
{
	switch(I_tCfg.cfgI_t_currentrange)
	{
		case 0:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay (I_tCfg.cfgI_t_sampleinterval);
			ComWrt(comSelect,Closesend,6);  //将CmdBufLen个长度的命令发送到指定的端口
			break;
		case 1:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_1,6);//
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_1,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 2:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_10,6);//
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_10,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 3:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_100,6);//
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_100,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 4:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_1K,6);//
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_1K,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 5:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_10k,6);//
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_10k,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 6:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_100K,6);//
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_100K,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 7:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_1M,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_1M,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 8:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_10M,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_10M,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 9:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_100M,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_100M,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
		case 10:
			send_cmd_vol(I_tCfg.cfgI_t_initial);
			Delay(0.5);
			if(abs(I_tCfg.cfgI_t_initial) < 2.5)
			{
				ComWrt(comSelect,O_1G,6);//
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			else
			{
				ComWrt(comSelect,O1_1G,6);
				Delay(0.5);
				ComWrt(comSelect,Closesend_3,6);
			}
			Delay(0.5);
			send_cmd_SamInt(I_tCfg.cfgI_t_sampleinterval);
			break;
	}
}

void send_itClosecmd()
{
	ComWrt(comSelect,Closesend_1,6);
	ComWrt(comSelect,Closesend_2,6);
}


//自定义函数，Protocol get data.
int ProtocolGetData (unsigned char *pUartRxBuf,RxDataTypeDef *pRxData)
{
	int vol;
	if(*(pUartRxBuf+2) == 0x02)
	{
		MessagePopup ("Error", "The resistance measured is too small");
		return -1;
	}
	else if(*(pUartRxBuf+2) == 0x03)
	{
		MessagePopup ("Error", "The resistance measured is too high");
		return -1;
	}
	if(*(pUartRxBuf+3) == 0x00 && *(pUartRxBuf + 4) == 0x84)
	{
		pRxData->rxResistance = 1;
	}
	else if(*(pUartRxBuf+3) == 0x00 && *(pUartRxBuf+4) == 0x44)
	{
		pRxData->rxResistance = 10;
	}
	else if(*(pUartRxBuf+3) == 0x02 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 100;
	}
	else if(*(pUartRxBuf+3) == 0x01 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 1000;
	}
	else if(*(pUartRxBuf+3) == 0x08 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 10000;
	}
	else if(*(pUartRxBuf+3) == 0x04 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 100000;
	}
	else if(*(pUartRxBuf+3) == 0x20 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 1000000;
	}
	else if(*(pUartRxBuf+3) == 0x10 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 10000000;
	}
	else if(*(pUartRxBuf+3) == 0x80 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 100000000;
	}
	else if(*(pUartRxBuf+3) == 0x40 && *(pUartRxBuf+4) == 0x04)
	{
		pRxData->rxResistance = 1000000000;
	}

	if(((*(pUartRxBuf+9) >> 5) & 1) == 0)
	{
		vol =  ((*(pUartRxBuf+9) << 8) | *(pUartRxBuf+10));
		pRxData->rxvoltage = (double) (vol/ 8192.00) ;
	}
	else
	{
		vol =  (((*(pUartRxBuf+9) & 0x1f) << 8) | *(pUartRxBuf+10));
		pRxData->rxvoltage = (double) (vol/ 8192.00) - 1;
	}

	return 0;
}

void ProtocolGetData1 (unsigned char *pUartRxBuf,RxDataTypeDef *pRxData)
{
	int vol;
	if(((*(pUartRxBuf+3) >> 5) & 1) == 0)
	{
		vol =  ((*(pUartRxBuf+3) << 8) | *(pUartRxBuf+4));
		pRxData->rxvoltage = (double) (vol/ 8192.00) ;
	}
	else
	{
		vol =  (((*(pUartRxBuf+3) & 0x1f) << 8) | *(pUartRxBuf+4));
		pRxData->rxvoltage = (double) (vol/ 8192.00) - 1;
	}
}
