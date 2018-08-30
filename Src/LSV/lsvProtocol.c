#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
//==============================================================================
//
// Title:		lsvProtocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/23 at 10:17:44 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "lsvProtocol.h"
#include "lsvPanel.h"

//==============================================================================
// Constants
const char lsv_Analogboard_V_x5[] = {0xAA ,0X9A, 0X01, 0X00, 0X84, 0X1F}; //电压放大5.1
const char AC_Set0[] = {0xAA,0X03,0X03,0X00,0X00,0X00};	  //交流置0命令
const char DC_Set0[] = {0xAA,0X03,0X04,0X80,0X00,0X87};	  //直流置0命令 

const char OwtputWaveTurn[] = {0xAA,0X02,0X04,0X00,0X01,0X07};	   //输出波形翻转
const char OwtputWaveNormal[] ={0xAA,0X02,0X04,0X00,0X00,0X06};     //输出正常波形
const char WaveSelectSawtooth[] ={0xAA,0X03,0X01,0X02,0X00,0X00};   //输出波形选择锯齿波
const char CloseOutputWave[] ={0xAA,0X03,0X01,0X00,0X00,0X02};      //关闭输出波形
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
extern unsigned char comSelect;
extern lsvCfg_TypeDef LsvCfg;  
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?

 char   lsvFrameHead[2] = {0xAA};

 char   lsvFrame_CmdType_AC[3] = {0x03,0x03};
 char   lsvFrame_CmdType_DC[3] = {0x03,0x04};
 char   lsvFrame_CmdType_ss[3] = {0x03,0x02};

 char   lsvFrame_Data[3] = {0}; 

 char   lsvFrame_L_Data[4] = {0};
 char   lsvFrame_H_Data[4] = {0};

 char lsvFrame_H_Calibration[2] = {0};
 char lsvFrame_L_Calibration[2] = {0};
 char lsvSend_L_Buf[6] = {0};
 char lsvSend_H_Buf[6] = {0}; 

 char   lsvFrame_Calibration[2] = {0};
 char   lsvSendBuf[6] = {0}; 

void SetLsvArguments(double Vmax,double Vmin,double ss)
{
  char ac;
  char dc;
  
  double f_dds;
  char freq;
  long long cnt;
 //设置交流和直流最大电压 
  if((((Vmax - Vmin) > 0) && ((Vmax - Vmin) < 1.92)) ||
	(((Vmax - Vmin) < 0) && ((Vmax - Vmin) > -1.92)))
  {
	ac = (Vmax - Vmin) * 34133;
	dc = (2.5-((Vmax - Vmin)/2)) / 5 * 65536;
	
	lsvFrame_Data[0] = ac >> 8;
	lsvFrame_Data[1] = ac & 0xff;
	lsvFrame_Calibration[0] = lsvFrame_CmdType_AC[0] ^ lsvFrame_CmdType_AC[1] ^ 
								 lsvFrame_Data[0] ^ lsvFrame_Data[1]; 
	
	memcpy (lsvSendBuf,lsvFrameHead,1);
	memcpy (lsvSendBuf+1,lsvFrame_CmdType_AC,2);
	memcpy (lsvSendBuf+1+2,lsvFrame_Data,2);
	memcpy (lsvSendBuf+1+2+2,lsvFrame_Calibration,1);
	ComWrt(comSelect,lsvSendBuf,6);
	
	lsvFrame_Data[0] = dc >> 8;
	lsvFrame_Data[1] = dc & 0xff;
	lsvFrame_Calibration[0] = lsvFrame_CmdType_DC[0] ^ lsvFrame_CmdType_DC[1] ^ 
								 lsvFrame_Data[0] ^ lsvFrame_Data[1]; 
	
	memcpy (lsvSendBuf,lsvFrameHead,1);
	memcpy (lsvSendBuf+1,lsvFrame_CmdType_DC,2);
	memcpy (lsvSendBuf+1+2,lsvFrame_Data,2);
	memcpy (lsvSendBuf+1+2+2,lsvFrame_Calibration,1);
	ComWrt(comSelect,lsvSendBuf,6);
  }else
  {
	ac = ((Vmax - Vmin) / 5.1) * 34133;
	dc = (2.5-((Vmax - Vmin)/(2*5.1))) / 5 * 65536;
	
	lsvFrame_Data[0] = ac >> 8;
	lsvFrame_Data[1] = ac & 0xff;
	lsvFrame_Calibration[0] = lsvFrame_CmdType_AC[0] ^ lsvFrame_CmdType_AC[1] ^ 
								 lsvFrame_Data[0] ^ lsvFrame_Data[1]; 
	
	memcpy (lsvSendBuf,lsvFrameHead,1);
	memcpy (lsvSendBuf+1,lsvFrame_CmdType_AC,2);
	memcpy (lsvSendBuf+1+2,lsvFrame_Data,2);
	memcpy (lsvSendBuf+1+2+2,lsvFrame_Calibration,1);
	ComWrt (comSelect,lsv_Analogboard_V_x5,6); //确定电压放大5.1倍，发送Analogboard_V_x5
	ComWrt(comSelect,lsvSendBuf,6);
	
	lsvFrame_Data[0] = dc >> 8;
	lsvFrame_Data[1] = dc & 0xff;
	lsvFrame_Calibration[0] = lsvFrame_CmdType_DC[0] ^ lsvFrame_CmdType_DC[1] ^ 
								 lsvFrame_Data[0] ^ lsvFrame_Data[1]; 
	
	memcpy (lsvSendBuf,lsvFrameHead,1);
	memcpy (lsvSendBuf+1,lsvFrame_CmdType_DC,2);
	memcpy (lsvSendBuf+1+2,lsvFrame_Data,2);
	memcpy (lsvSendBuf+1+2+2,lsvFrame_Calibration,1);
	
	ComWrt (comSelect,lsv_Analogboard_V_x5,6); //确定电压放大5.1倍，发送Analogboard_V_x5
	ComWrt(comSelect,lsvSendBuf,6);
	
  }
   //设置扫描速度
   f_dds = (Vmax - Vmin) / ss;
   if(f_dds > 3051)
   {
	 freq = (f_dds * 32768) / 100000000;
	 lsvFrame_Data[0] = freq >> 8;
	 lsvFrame_Data[1] = freq & 0xff;
	 lsvFrame_Calibration[0] = lsvFrame_CmdType_ss[0] ^ lsvFrame_CmdType_ss[1] ^ 
								 lsvFrame_Data[0] ^ lsvFrame_Data[1];
	 memcpy (lsvSendBuf,lsvFrameHead,1);
	 memcpy (lsvSendBuf+1,lsvFrame_CmdType_ss,2);
	 memcpy (lsvSendBuf+1+2,lsvFrame_Data,2);
	 memcpy (lsvSendBuf+1+2+2,lsvFrame_Calibration,1);
	 ComWrt(comSelect,lsvSendBuf,6);
   }else
   {
		cnt = (100000000 / ((f_dds * 32768) / 1000000)) - 1;

		lsvFrame_L_Data[0] = ((cnt >> 16) & 0x000000000F) | 0x00000000B0; 
		lsvFrame_L_Data[1] = (cnt >> 8) & 0x00000000ff;
		lsvFrame_L_Data[2] = cnt & 0x00000000ff;
		lsvFrame_L_Calibration[0] = lsvFrameHead[1] ^ 
									   lsvFrame_L_Data[0] ^ 
									   lsvFrame_L_Data[1] ^ 
									   lsvFrame_L_Data[2];

		lsvFrame_H_Data[0] = ((cnt >> 36) & 0x000000000F) | 0x00000000A0; 
		lsvFrame_H_Data[1] = (cnt >> 28) & 0x00000000ff;
		lsvFrame_H_Data[2] = (cnt >> 20) & 0x00000000ff;
		lsvFrame_H_Calibration[0] = lsvFrameHead[1] ^ lsvFrame_H_Data[0] ^
									   lsvFrame_H_Data[1] ^ lsvFrame_H_Data[2];

		memcpy (lsvSend_L_Buf,lsvFrameHead,1);
		memcpy (lsvSend_L_Buf+1,"0x03",1);
		memcpy (lsvSend_L_Buf+1+1,lsvFrame_L_Data,3);
		memcpy (lsvSend_L_Buf+1+1+3,lsvFrame_L_Calibration,1);

		memcpy (lsvSend_H_Buf,lsvFrameHead,1);
		memcpy (lsvSend_H_Buf+1,"0x03",1);
		memcpy (lsvSend_H_Buf+1+1,lsvFrame_H_Data,3);
		memcpy (lsvSend_H_Buf+1+1+3,lsvFrame_H_Calibration,1);

		ComWrt (comSelect,lsvSend_L_Buf,6); 
		ComWrt (comSelect,lsvSend_H_Buf,6);
   }
}

void Send_lsvcmd(double final,double initial,double scanrate)
{
	switch(LsvCfg.cfgLsv_currentrange)
	{
	   case 0:
			SetLsvArguments(LsvCfg.cfgLsv_final,LsvCfg.cfgLsv_Initial,LsvCfg.cfgLsv_scanrate);
			ComWrt(comSelect,WaveSelectSawtooth,6);
			ComWrt(comSelect,CloseOutputWave,6); 
		   break;
	   case 1:
		   break;
	}
}
