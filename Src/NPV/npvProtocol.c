//==============================================================================
//
// Title:		npvProtocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/28 at 9:31:51 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <utility.h> 
#include <ansi_c.h>
#include <rs232.h>
#include "npvProtocol.h"
#include "npvPanel.h"

//==============================================================================
// Constants
const  char npvWaveSelectStep[] ={0xAA,0X03,0X14,0X00,0X02,0X15};   //输出波形选择阶梯波
const  char npvCloseOutputWave[] ={0xAA,0X03,0X14,0X00,0X00,0X17};  //关闭输出波形
const  char npv_Analogboard_V_x5[] = {0xAA ,0X9A, 0X01, 0X00, 0X84, 0X1F}; //电压放大5.1  
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Extern variables 
extern unsigned char comSelect;
extern npvCfg_TypeDef NpvCfg;

//==============================================================================
// Global functions

// HIFN  What does your function do?              npv实验将用户输入参数转化成要发送的命令
// HIPAR x/What inputs does your function expect? 输入参数有起始电压、结束电压、脉冲电压、电位增量、采样宽度、脉冲宽度、脉冲周期
// HIRET What does your function return?		  正确返回 0； 错误返回 -1；
const char   npvFrameHead[2] = {0xAA};						      //Frame head
const char   npvFrame_CmdType_initial[3] = {0x0B,0X01};			  //cmd type of frame
const char   npvFrame_CmdType_final[3] = {0x0B,0X04};
const char   npvFrame_CmdType_pluse[3] = {0x0B,0X02};
const char   npvFrame_CmdType_incr[3] = {0x0B,0X03};
const char   npvFrame_CmdType_pluseWidth_L[3] = {0x0A,0x10};
const char   npvFrame_CmdType_pluseWidth_H[3] = {0x0A,0x11};
const char   npvFrame_CmdType_plusePeriod_L[3] = {0x0A,0x20};
const char   npvFrame_CmdType_plusePeriod_H[3] = {0x0A,0x21};
const char   npvFrame_CmdType_samplingWidth_L[3] = {0x0A,0x30};
const char   npvFrame_CmdType_samplingWidth_H[3] = {0x0A,0x31};  
 char   npvFrame_Data[3] = {0}; 							    //data of frame
 char   npvFrame_L_Data[3] = {0};
 char   npvFrame_H_Data[3] = {0};							   
 char   npvFrame_H_Calibration[2] = {0};						// calibration of frame
 char   npvFrame_L_Calibration[2] = {0};
 char   npvFrame_Calibration[2] = {0};  
 char   npvSend_L_Buf[6] = {0};								    //send a frame
 char   npvSend_H_Buf[6] = {0}; 
 char   npvSendBuf[6] = {0}; 

int SetNpvArguments(double initial,double final,double incr,double pluse,double samplingWidth,double pluseWidth,double plusePeriod)
{
	char temp;
	long long Ncnt1;
	long long Ncnt2;
	long long Ncnt3;
  
	temp = ((initial / 5.1) + 2.5) / 5 * 65536;   //设置起始电压
	npvFrame_Data[0] = temp >> 8;
	npvFrame_Data[1] = temp & 0xff;
	npvFrame_Calibration[0] = npvFrame_CmdType_initial[0] ^ npvFrame_CmdType_initial[1] ^ 
						      npvFrame_Data[0] ^ npvFrame_Data[1]; 
	memcpy (npvSendBuf,npvFrameHead,1);
	memcpy (npvSendBuf+1,npvFrame_CmdType_initial,2);
	memcpy (npvSendBuf+1+2,npvFrame_Data,2);
	memcpy (npvSendBuf+1+2+2,npvFrame_Calibration,1);
	ComWrt(comSelect,npvSendBuf,6);

  	temp = (pluse / 5.1) / 5 * 65536; //设置脉冲电压  
	npvFrame_Data[0] = temp >> 8;
	npvFrame_Data[1] = temp & 0xff;
	npvFrame_Calibration[0] = npvFrame_CmdType_pluse[0] ^ npvFrame_CmdType_pluse[1] ^ 
						      npvFrame_Data[0] ^ npvFrame_Data[1]; 
	memcpy (npvSendBuf,npvFrameHead,1);
	memcpy (npvSendBuf+1,npvFrame_CmdType_pluse,2);
	memcpy (npvSendBuf+1+2,npvFrame_Data,2);
	memcpy (npvSendBuf+1+2+2,npvFrame_Calibration,1);
	ComWrt(comSelect,npvSendBuf,6);
 
    temp = ((incr / 5.1) / 5) * 65536; //设置电位增量  
	npvFrame_Data[0] = temp >> 8;
	npvFrame_Data[1] = temp & 0xff;
	npvFrame_Calibration[0] = npvFrame_CmdType_incr[0] ^ npvFrame_CmdType_incr[1] ^ 
						      npvFrame_Data[0] ^ npvFrame_Data[1]; 
	memcpy (npvSendBuf,npvFrameHead,1);
	memcpy (npvSendBuf+1,npvFrame_CmdType_incr,2);
	memcpy (npvSendBuf+1+2,npvFrame_Data,2);
	memcpy (npvSendBuf+1+2+2,npvFrame_Calibration,1);
	ComWrt(comSelect,npvSendBuf,6);	
 
   	temp = ((final / 5.1) + 2.5) / 5 * 65536;  //设置结束电压  
	npvFrame_Data[0] = temp >> 8;
	npvFrame_Data[1] = temp & 0xff;
	npvFrame_Calibration[0] = npvFrame_CmdType_final[0] ^ npvFrame_CmdType_final[1] ^ 
						      npvFrame_Data[0] ^ npvFrame_Data[1]; 
	memcpy (npvSendBuf,npvFrameHead,1);
	memcpy (npvSendBuf+1,npvFrame_CmdType_final,2);
	memcpy (npvSendBuf+1+2,npvFrame_Data,2);
	memcpy (npvSendBuf+1+2+2,npvFrame_Calibration,1);
	ComWrt(comSelect,npvSendBuf,6);
  
    Ncnt1 = (plusePeriod / 20) * 1000000000 - ((pluseWidth / 20) * 1000000000) ; //设置脉冲周期 
	if(Ncnt1 < 30000)
      return -1;
	npvFrame_L_Data[1] = Ncnt1 & 0x000000FF; 
	npvFrame_L_Data[0] = (Ncnt1 >> 8) & 0x000000FF;
	npvFrame_L_Calibration[0] = npvFrame_CmdType_plusePeriod_L[0] ^
								npvFrame_CmdType_plusePeriod_L[1] ^ 
								   npvFrame_L_Data[0] ^ 
								   npvFrame_L_Data[1]; 
	npvFrame_H_Data[1] = (Ncnt1 >> 16) & 0x000000FF; 
	npvFrame_H_Data[0] = (Ncnt1 >> 24) & 0x000000FF;
	npvFrame_H_Calibration[0] = npvFrame_CmdType_plusePeriod_H[0] ^
								npvFrame_CmdType_plusePeriod_H[1] ^ 
								npvFrame_H_Data[0] ^
								npvFrame_H_Data[1];
	memcpy (npvSend_L_Buf,npvFrameHead,1);
	memcpy (npvSend_L_Buf+1,npvFrame_CmdType_plusePeriod_L,2);
	memcpy (npvSend_L_Buf+1+2,npvFrame_L_Data,2);
	memcpy (npvSend_L_Buf+1+2+2,npvFrame_L_Calibration,1);
	memcpy (npvSend_H_Buf,npvFrameHead,1);
	memcpy (npvSend_H_Buf+1,npvFrame_CmdType_plusePeriod_H,2);
	memcpy (npvSend_H_Buf+1+2,npvFrame_H_Data,2);
	memcpy (npvSend_H_Buf+1+2+2,npvFrame_H_Calibration,1);
	ComWrt (comSelect,npvSend_L_Buf,6); 
	ComWrt (comSelect,npvSend_H_Buf,6);

    Ncnt2 = (pluseWidth / 20) * 1000000000;  //设置脉冲宽度  
	if(Ncnt1 < 30000)
      return -1;
	npvFrame_L_Data[1] = Ncnt1 & 0x000000FF; 
	npvFrame_L_Data[0] = (Ncnt1 >> 8) & 0x000000FF;
	npvFrame_L_Calibration[0] = npvFrame_CmdType_pluseWidth_L[0] ^
								npvFrame_CmdType_pluseWidth_L[1] ^ 
								   npvFrame_L_Data[0] ^ 
								   npvFrame_L_Data[1]; 
	npvFrame_H_Data[1] = (Ncnt1 >> 16) & 0x000000FF; 
	npvFrame_H_Data[0] = (Ncnt1 >> 24) & 0x000000FF;
	npvFrame_H_Calibration[0] = npvFrame_CmdType_pluseWidth_H[0] ^
								npvFrame_CmdType_pluseWidth_H[1] ^ 
								npvFrame_H_Data[0] ^
								npvFrame_H_Data[1];
	memcpy (npvSend_L_Buf,npvFrameHead,1);
	memcpy (npvSend_L_Buf+1,npvFrame_CmdType_pluseWidth_L,2);
	memcpy (npvSend_L_Buf+1+2,npvFrame_L_Data,2);
	memcpy (npvSend_L_Buf+1+2+2,npvFrame_L_Calibration,1);
	memcpy (npvSend_H_Buf,npvFrameHead,1);
	memcpy (npvSend_H_Buf+1,npvFrame_CmdType_pluseWidth_H,2);
	memcpy (npvSend_H_Buf+1+2,npvFrame_H_Data,2);
	memcpy (npvSend_H_Buf+1+2+2,npvFrame_H_Calibration,1);
	ComWrt (comSelect,npvSend_L_Buf,6); 
	ComWrt (comSelect,npvSend_H_Buf,6);

    Ncnt3 = (samplingWidth / 20) * 1000000000;   //设置采样宽度
	if((Ncnt3 < 1) && (Ncnt3 > Ncnt2))
		return -1;
    npvFrame_L_Data[1] = Ncnt2 & 0x000000FF; 
	npvFrame_L_Data[0] = (Ncnt2 >> 8) & 0x000000FF;
	npvFrame_L_Calibration[0] = npvFrame_CmdType_samplingWidth_L[0] ^
								npvFrame_CmdType_samplingWidth_L[1] ^ 
								   npvFrame_L_Data[0] ^ 
								   npvFrame_L_Data[1]; 
	npvFrame_H_Data[1] = (Ncnt2 >> 16) & 0x000000FF; 
	npvFrame_H_Data[0] = (Ncnt2 >> 24) & 0x000000FF;
	npvFrame_H_Calibration[0] = npvFrame_CmdType_samplingWidth_H[0] ^
								npvFrame_CmdType_samplingWidth_H[1] ^ 
								npvFrame_H_Data[0] ^
								npvFrame_H_Data[1];
	memcpy (npvSend_L_Buf,npvFrameHead,1);
	memcpy (npvSend_L_Buf+1,npvFrame_CmdType_samplingWidth_L,2);
	memcpy (npvSend_L_Buf+1+2,npvFrame_L_Data,2);
	memcpy (npvSend_L_Buf+1+2+2,npvFrame_L_Calibration,1);
	memcpy (npvSend_H_Buf,npvFrameHead,1);
	memcpy (npvSend_H_Buf+1,npvFrame_CmdType_samplingWidth_H,2);
	memcpy (npvSend_H_Buf+1+2,npvFrame_H_Data,2);
	memcpy (npvSend_H_Buf+1+2+2,npvFrame_H_Calibration,1);
	ComWrt (comSelect,npvSend_L_Buf,6); 
	ComWrt (comSelect,npvSend_H_Buf,6);
	
	return 0;
}
// HIFN  What does your function do?              npv实验参数命令的发送
// HIPAR x/What inputs does your function expect? 输入参数有起始电压、结束电压、脉冲电压、电位增量、采样宽度、脉冲宽度、脉冲周期 
// HIRET What does your function return?		  无返回值
void Send_npvCmd(double initial,double final,double pluse,double incr,double samplingWidth,double PluseWidth,double PlusePeriod)
{
	switch(NpvCfg.cfgNpv_currentrange)
	{
	   case 0:
		    ComWrt(comSelect,npv_Analogboard_V_x5,6); 
			SetNpvArguments(NpvCfg.cfgNpv_Initial,NpvCfg.cfgNpv_Final,NpvCfg.cfgNpv_Incr,NpvCfg.cfgNpv_Pluse,
							NpvCfg.cfgNpv_SamplingWidth,NpvCfg.cfgNpv_PluseWdith,NpvCfg.cfgNpv_PlusePeriods);
			ComWrt(comSelect,npvWaveSelectStep,6);
			Delay(((final - initial - pluse) / incr ) *(PluseWidth + PlusePeriod));
			ComWrt(comSelect,npvCloseOutputWave,6); 
		   break;
	   case 1:
		   break;
	}
}
