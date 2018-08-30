//==============================================================================
//
// Title:		scvProtocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/26 at 15:44:52 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include "scvProtocol.h"
#include "scvPanel.h"

//==============================================================================
// Constants
const char scvWaveSelectStep[] ={0xAA,0X03,0X14,0X00,0X01,0X16};   //输出波形选择阶梯波
const char scvCloseOutputWave[] ={0xAA,0X03,0X14,0X00,0X04,0X13};      //关闭输出波形

const char scv_Analogboard_V_x5[] = {0xAA ,0X9A, 0X01, 0X00, 0X84, 0X1F}; //电压放大5.1  
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
extern unsigned char comSelect;
extern scvCfg_TypeDef ScvCfg;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?

 char   scvFrameHead[2] = {0xAA};

const char   scvFrame_CmdType_initial[3] = {0x0B,0X01};
const char   scvFrame_CmdType_final[3] = {0x0B,0X02};
const char   scvFrame_CmdType_incr[3] = {0x0B,0X03};
const char   scvFrame_CmdType_stepPeriods_L[3] = {0x0A,0x10};
const char   scvFrame_CmdType_stepPeriods_H[3] = {0x0A,0x11};  
const char   scvFrame_CmdType_samplingWidth_L[3] = {0x0A,0x20};
const char   scvFrame_CmdType_samplingWidth_H[3] = {0x0A,0x21};  

 char   scvFrame_Data[3] = {0}; 

 char   scvFrame_L_Data[3] = {0};
 char   scvFrame_H_Data[3] = {0};

 char scvFrame_H_Calibration[2] = {0};
 char scvFrame_L_Calibration[2] = {0};
 char scvSend_L_Buf[6] = {0};
 char scvSend_H_Buf[6] = {0}; 

 char  scvFrame_Calibration[2] = {0};
 char  scvSendBuf[6] = {0}; 

int setScvArguments(double initial,double final,double incr,double stepPeriods,double samplingWidth)
{
  char temp;
  long long Ncnt1;
  long long Ncnt2;
  
  //设置起始电压
	temp = ((initial / 5.1) + 2.5) / 5 * 65536;

	scvFrame_Data[0] = temp >> 8;
	scvFrame_Data[1] = temp & 0xff;
	scvFrame_Calibration[0] = scvFrame_CmdType_initial[0] ^ scvFrame_CmdType_initial[1] ^ 
						      scvFrame_Data[0] ^ scvFrame_Data[1]; 
	memcpy (scvSendBuf,scvFrameHead,1);
	memcpy (scvSendBuf+1,scvFrame_CmdType_initial,2);
	memcpy (scvSendBuf+1+2,scvFrame_Data,2);
	memcpy (scvSendBuf+1+2+2,scvFrame_Calibration,1);
	ComWrt(comSelect,scvSendBuf,6);
  //设置结束电压
   	temp = ((final / 5.1) + 2.5) / 5 * 65536;  

	scvFrame_Data[0] = temp >> 8;
	scvFrame_Data[1] = temp & 0xff;
	scvFrame_Calibration[0] = scvFrame_CmdType_final[0] ^ scvFrame_CmdType_final[1] ^ 
						      scvFrame_Data[0] ^ scvFrame_Data[1]; 
	memcpy (scvSendBuf,scvFrameHead,1);
	memcpy (scvSendBuf+1,scvFrame_CmdType_final,2);
	memcpy (scvSendBuf+1+2,scvFrame_Data,2);
	memcpy (scvSendBuf+1+2+2,scvFrame_Calibration,1);
	ComWrt(comSelect,scvSendBuf,6);
  //设置电位增量
    temp = ((incr / 5.1) / 5) * 65536;

	scvFrame_Data[0] = temp >> 8;
	scvFrame_Data[1] = temp & 0xff;
	scvFrame_Calibration[0] = scvFrame_CmdType_incr[0] ^ scvFrame_CmdType_incr[1] ^ 
						      scvFrame_Data[0] ^ scvFrame_Data[1]; 
	memcpy (scvSendBuf,scvFrameHead,1);
	memcpy (scvSendBuf+1,scvFrame_CmdType_incr,2);
	memcpy (scvSendBuf+1+2,scvFrame_Data,2);
	memcpy (scvSendBuf+1+2+2,scvFrame_Calibration,1);
	ComWrt(comSelect,scvSendBuf,6);
  //设置步进周期
    Ncnt1 = (stepPeriods / 20) * 1000000000;
	if(Ncnt1 < 30000)
      return -1;
	scvFrame_L_Data[1] = Ncnt1 & 0x000000FF; 
	scvFrame_L_Data[0] = (Ncnt1 >> 8) & 0x000000FF;
	scvFrame_L_Calibration[0] = scvFrame_CmdType_stepPeriods_L[0] ^
								scvFrame_CmdType_stepPeriods_L[1] ^ 
								   scvFrame_L_Data[0] ^ 
								   scvFrame_L_Data[1]; 
							

	scvFrame_H_Data[1] = (Ncnt1 >> 16) & 0x000000FF; 
	scvFrame_H_Data[0] = (Ncnt1 >> 24) & 0x000000FF;
	scvFrame_H_Calibration[0] = scvFrame_CmdType_stepPeriods_H[0] ^
								scvFrame_CmdType_stepPeriods_H[1] ^ 
								scvFrame_H_Data[0] ^
								scvFrame_H_Data[1];

	memcpy (scvSend_L_Buf,scvFrameHead,1);
	memcpy (scvSend_L_Buf+1,scvFrame_CmdType_stepPeriods_L,2);
	memcpy (scvSend_L_Buf+1+2,scvFrame_L_Data,2);
	memcpy (scvSend_L_Buf+1+2+2,scvFrame_L_Calibration,1);

	memcpy (scvSend_H_Buf,scvFrameHead,1);
	memcpy (scvSend_H_Buf+1,scvFrame_CmdType_stepPeriods_H,2);
	memcpy (scvSend_H_Buf+1+2,scvFrame_H_Data,2);
	memcpy (scvSend_H_Buf+1+2+2,scvFrame_H_Calibration,1);

	ComWrt (comSelect,scvSend_L_Buf,6); 
	ComWrt (comSelect,scvSend_H_Buf,6);

  //设置采样宽度
    Ncnt2 = (samplingWidth / 20) * 1000000000; 
	if((Ncnt2 < 1) && (Ncnt2 > Ncnt1))
		return -1;
    scvFrame_L_Data[1] = Ncnt2 & 0x000000FF; 
	scvFrame_L_Data[0] = (Ncnt2 >> 8) & 0x000000FF;
	scvFrame_L_Calibration[0] = scvFrame_CmdType_samplingWidth_L[0] ^
								scvFrame_CmdType_samplingWidth_L[1] ^ 
								   scvFrame_L_Data[0] ^ 
								   scvFrame_L_Data[1]; 
							

	scvFrame_H_Data[1] = (Ncnt2 >> 16) & 0x000000FF; 
	scvFrame_H_Data[0] = (Ncnt2 >> 24) & 0x000000FF;
	scvFrame_H_Calibration[0] = scvFrame_CmdType_samplingWidth_H[0] ^
								scvFrame_CmdType_samplingWidth_H[1] ^ 
								scvFrame_H_Data[0] ^
								scvFrame_H_Data[1];

	memcpy (scvSend_L_Buf,scvFrameHead,1);
	memcpy (scvSend_L_Buf+1,scvFrame_CmdType_samplingWidth_L,2);
	memcpy (scvSend_L_Buf+1+2,scvFrame_L_Data,2);
	memcpy (scvSend_L_Buf+1+2+2,scvFrame_L_Calibration,1);

	memcpy (scvSend_H_Buf,scvFrameHead,1);
	memcpy (scvSend_H_Buf+1,scvFrame_CmdType_samplingWidth_H,2);
	memcpy (scvSend_H_Buf+1+2,scvFrame_H_Data,2);
	memcpy (scvSend_H_Buf+1+2+2,scvFrame_H_Calibration,1);

	ComWrt (comSelect,scvSend_L_Buf,6); 
	ComWrt (comSelect,scvSend_H_Buf,6);
	
	return 0;
}
void send_scvcmd(double initial,double final,double incr,double stepPeriods)
{
	switch(ScvCfg.cfgScv_currentrange)
	{
	   case 0:
		    ComWrt(comSelect,scv_Analogboard_V_x5,6); 
			setScvArguments(ScvCfg.cfgScv_Initial,ScvCfg.cfgScv_Final,ScvCfg.cfgScv_Incr,ScvCfg.cfgScv_StepPeriods,ScvCfg.cfgScv_SamplingWidth);
			ComWrt(comSelect,scvWaveSelectStep,6);
			Delay(((final - initial) / incr ) * stepPeriods * 2 + 3);
			ComWrt(comSelect,scvCloseOutputWave,6); 
		   break;
	   case 1:
		   break;
	}
}
