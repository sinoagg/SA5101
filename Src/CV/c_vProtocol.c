//==============================================================================
//
// Title:		c_vProtocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/23 at 9:57:16 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "c_vProtocol.h"

//==============================================================================
// Constants
const char cvOwtputWaveTurn[] = {0xAA,0X02,0X04,0X00,0X01,0X07};	   //输出波形翻转
const char cvOwtputWaveNormal[] ={0xAA,0X02,0X04,0X00,0X00,0X06};     //输出正常波形
const char cvWaveSelectSawtooth[] ={0xAA,0X03,0X01,0X03,0X00,0X01};   //输出波形选择锯齿波
const char cvCloseOutputWave[] ={0xAA,0X03,0X01,0X00,0X00,0X02};      //关闭输出波形
const char cv_Analogboard_V_x5[] = {0xAA ,0X9A, 0X01, 0X00, 0X84, 0X1F}; //电压放大5.1
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
 char   cvFrameHead[2] = {0xAA};

 char   cvFrame_CmdType_AC[3] = {0x03,0x03};
 char   cvFrame_CmdType_DC[3] = {0x03,0x04};
 char   cvFrame_CmdType_ss[3] = {0x03,0x02};
 char   cvFrame_CmdType_Start[3] = {0x02,0x01};
 char   cvFrame_CmdType_Final[3] = {0x02,0x02};
 char   cvFrame_CmdType_Seg[3] = {0x02,0x03};

 char   cvFrame_Data[3] = {0}; 

 char   cvFrame_L_Data[4] = {0};
 char   cvFrame_H_Data[4] = {0};

 char cvFrame_H_Calibration[2] = {0};
 char cvFrame_L_Calibration[2] = {0};
 char cvSend_L_Buf[6] = {0};
 char cvSend_H_Buf[6] = {0}; 

 char   cvFrame_Calibration[2] = {0};
 char   cvSendBuf[6] = {0};

void SetcvArguments(double Vmax,double Vmin,double sr,double Vstart,double Vfinal,char Seg)
{
  //设置交流最大电压和最小电压
  char ac;
  char dc;
  if((((Vmax - Vmin) > 0) && ((Vmax - Vmin) < 1.92)) ||
	(((Vmax - Vmin) < 0) && ((Vmax - Vmin) > -1.92)))
  {
	ac = (Vmax - Vmin) * 34133;
	dc = (2.5-((Vmax - Vmin)/2)) / 5 * 65536;
	
	cvFrame_Data[0] = ac >> 8;
	cvFrame_Data[1] = ac & 0xff;
    cvFrame_Calibration[0] = cvFrame_CmdType_AC[0] ^ cvFrame_CmdType_AC[1] ^ 
								 cvFrame_Data[0] ^ cvFrame_Data[1]; 
	
	memcpy (cvSendBuf,cvFrameHead,1);
	memcpy (cvSendBuf+1,cvFrame_CmdType_AC,2);
	memcpy (cvSendBuf+1+2,cvFrame_Data,2);
	memcpy (cvSendBuf+1+2+2,cvFrame_Calibration,1);
	ComWrt(comSelect,cvSendBuf,6);
	
	cvFrame_Data[0] = dc >> 8;
	cvFrame_Data[1] = dc & 0xff;
	cvFrame_Calibration[0] = cvFrame_CmdType_DC[0] ^ cvFrame_CmdType_DC[1] ^ 
								 cvFrame_Data[0] ^ cvFrame_Data[1]; 
	
	memcpy (cvSendBuf,cvFrameHead,1);
	memcpy (cvSendBuf+1,cvFrame_CmdType_DC,2);
	memcpy (cvSendBuf+1+2,cvFrame_Data,2);
	memcpy (cvSendBuf+1+2+2,cvFrame_Calibration,1);
	ComWrt(comSelect,cvSendBuf,6);
  }else
  {
	ac = ((Vmax - Vmin) / 5.1) * 34133;
	dc = (2.5-((Vmax - Vmin)/(2*5.1))) / 5 * 65536;
	
	cvFrame_Data[0] = ac >> 8;
	cvFrame_Data[1] = ac & 0xff;
	cvFrame_Calibration[0] = cvFrame_CmdType_AC[0] ^ cvFrame_CmdType_AC[1] ^ 
								 cvFrame_Data[0] ^ cvFrame_Data[1]; 
	
	memcpy (cvSendBuf,cvFrameHead,1);
	memcpy (cvSendBuf+1,cvFrame_CmdType_AC,2);
	memcpy (cvSendBuf+1+2,cvFrame_Data,2);
	memcpy (cvSendBuf+1+2+2,cvFrame_Calibration,1);
	ComWrt (comSelect,cv_Analogboard_V_x5,6); //确定电压放大5.1倍，发送Analogboard_V_x5
	ComWrt(comSelect,cvSendBuf,6);
	
	cvFrame_Data[0] = dc >> 8;
	cvFrame_Data[1] = dc & 0xff;
	cvFrame_Calibration[0] = cvFrame_CmdType_DC[0] ^ cvFrame_CmdType_DC[1] ^ 
								 cvFrame_Data[0] ^ cvFrame_Data[1]; 
	
	memcpy (cvSendBuf,cvFrameHead,1);
	memcpy (cvSendBuf+1,cvFrame_CmdType_DC,2);
	memcpy (cvSendBuf+1+2,cvFrame_Data,2);
	memcpy (cvSendBuf+1+2+2,cvFrame_Calibration,1);
	
	ComWrt (comSelect,cv_Analogboard_V_x5,6); //确定电压放大5.1倍，发送Analogboard_V_x5
	ComWrt(comSelect,cvSendBuf,6);	
  }
  
   //设置扫描频率
  
  
	//设置开始电压
    char addr_start;
	addr_start = (Vstart-Vmin)/(Vmax - Vmin)*8191;
   
	cvFrame_Data[0] = addr_start >> 8;
	cvFrame_Data[1] = addr_start & 0xff;
	cvFrame_Calibration[0] = cvFrame_CmdType_Start[0] ^ cvFrame_CmdType_Start[1] ^ 
							 cvFrame_Data[0] ^ cvFrame_Data[1]; 

	memcpy (cvSendBuf,cvFrameHead,1);
	memcpy (cvSendBuf+1,cvFrame_CmdType_Start,2);
	memcpy (cvSendBuf+1+2,cvFrame_Data,2);
	memcpy (cvSendBuf+1+2+2,cvFrame_Calibration,1);
	ComWrt(comSelect,cvSendBuf,6);
	//设置结束电压
	char addr_final;
	addr_final = 16383 - ((Vstart-Vmin)/(Vmax - Vmin)*8191);
   
	cvFrame_Data[0] = addr_final >> 8;
	cvFrame_Data[1] = addr_final & 0xff;
	cvFrame_Calibration[0] = cvFrame_CmdType_Final[0] ^ cvFrame_CmdType_Final[1] ^ 
							 cvFrame_Data[0] ^ cvFrame_Data[1]; 

	memcpy (cvSendBuf,cvFrameHead,1);
	memcpy (cvSendBuf+1,cvFrame_CmdType_Final,2);
	memcpy (cvSendBuf+1+2,cvFrame_Data,2);
	memcpy (cvSendBuf+1+2+2,cvFrame_Calibration,1);
	ComWrt(comSelect,cvSendBuf,6);
	//设置扫描短数
	cvFrame_Data[0] = Seg >> 8;
	cvFrame_Data[1] = Seg & 0xff;
	cvFrame_Calibration[0] = cvFrame_CmdType_Seg[0] ^ cvFrame_CmdType_Seg[1] ^ 
							 cvFrame_Data[0] ^ cvFrame_Data[1]; 

	memcpy (cvSendBuf,cvFrameHead,1);
	memcpy (cvSendBuf+1,cvFrame_CmdType_Seg,2);
	memcpy (cvSendBuf+1+2,cvFrame_Data,2);
	memcpy (cvSendBuf+1+2+2,cvFrame_Calibration,1);
	ComWrt(comSelect,cvSendBuf,6);
}

void Send_cvcmd(double Vmax,double Vmin,double ss,int seg)
{
	switch(CvCfg.cfgC_v_currentrange)
	{
	   case 0:
			SetcvArguments(CvCfg.cfgC_v_high,CvCfg.cfgC_v_low,CvCfg.cfgC_v_scanrate,CvCfg.cfgC_v_initial,CvCfg.cfgC_v_final,CvCfg.cfgC_v_sweepsegments);
			ComWrt(comSelect,cvWaveSelectSawtooth,6);
			Delay((2 * (Vmax - Vmin) * seg) / ss);
			ComWrt(comSelect,cvCloseOutputWave,6); 
		   break;
	   case 1:
		   break;
	}
}
