//==============================================================================
//
// Title:		Protocol.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/9 at 9:58:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <ansi_c.h>
#include <userint.h>
#include "Protocol.h"
#include <rs232.h>
#include "LoadPanel.h"
#include "Graph.h"
#include "ItPanel.h"
#include <analysis.h>
//==============================================================================
// Constants
     
//==============================================================================
// Types
enum MsgType
{
	MSG_TYPE_SYSTEM_7RESET=0x10,	//系统复位
	MSG_TYPE_REPORT_ID=0x20,	  //查询设备
	MSG_TYPE_SITTING_REGISTER1=0x30,  //设置寄存器1
	MSG_TYPE_SITTING_REGISTER2=0x31,  //设置寄存器2
	MSG_TYPE_RUN=0x40,				  //开始采集
	MSG_TYPE_STOP=0x50,				  //停止采集
	MSG_TYPE_QUERY=0x60				  //轮询
};
//==============================================================================
// Static global variables
static float amplificationFactor = 1.0;   //放大系数 
float fsin, val = 0;                    //交流频率值
float leftVal, rightVal;
float minFreq = 0.0;
//==============================================================================
// Static functions

//==============================================================================
// Global variables
unsigned char pointInFlag = 0; //频点内之间的循环标志位
unsigned char impCloseFlag = 0;//imp实验关闭标志位
unsigned char pointInNumber = 1;//段内循环数量
unsigned char num = 0;
unsigned char totalNum = 0;
double channel1Real[POINTS];
double channel1Imaginary[POINTS] = {0};
double channel2Real[POINTS];
double channel2Imaginary[POINTS] = {0};

TestParaTypeDef TestPara;
GraphTypeDef* pGraph;
//==============================================================================
//Global functions
static void GetTestPara(ExpPanelTypeDef* pExpPanel,TestParaTypeDef* pTestPara)
{
    GetCtrlVal(pExpPanel->panelHandle, pExpPanel->InitID, &(pTestPara->init));                //获取起始点压控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->StopID, &(pTestPara->stop));	              //获取结束电压控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->StartID, &(pTestPara->start));              //获取初始电压控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VoltageStepID, &(pTestPara->voltageStep));   //获取电压增量控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PosOrNegID, &(pTestPara->posOrNeg)); 		    //获取正反扫描控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->SweepSegmentsID, &(pTestPara->sweepSegments));  //获取扫描段数控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->HoldTimeID, &(pTestPara->holdTime)); 			   //获取保持高电压控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->SamplingWidthID, &(pTestPara->samplingWidth));    //获取采样宽度控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PulseWidthID, &(pTestPara->pluseWidth));          //获取脉冲宽度控件的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PulsePeriodID, &(pTestPara->plusePeriod));        //获取脉冲周期控件的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PulseWidth2ID, &(pTestPara->pluseWidth2));        //获取脉冲宽度控件2的值    
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->AmplitudeID, &(pTestPara->amplitude));            //获取振幅控件的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->FrequencyID, &(pTestPara->frequency));      //获取脉冲宽度控件4的值
	
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->HighFreqID, &(pTestPara->highFreq));  //获取最高频率的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->LowFreqID, &(pTestPara->lowFreq)); 	//获取最低频率的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_100k_1Mhz, &(pTestPara->points_100k_1Mhz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_10k_100Khz, &(pTestPara->points_10k_100Khz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_1k_10Khz, &(pTestPara->points_1k_10Khz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_100_1Khz, &(pTestPara->points_100_1Khz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_10_100hz, &(pTestPara->points_10_100hz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_1_10hz, &(pTestPara->points_1_10hz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_01_1hz, &(pTestPara->points_01_1hz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_001_01hz, &(pTestPara->points_001_01hz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_0001_001hz, &(pTestPara->points_0001_001hz));  //获取频点的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_00001_0001hz, &(pTestPara->points_00001_0001hz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_000001_00001hz, &(pTestPara->points_000001_00001hz));  //获取频点的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_100k_1Mhz, &(pTestPara->cycle_100k_1Mhz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_10k_100Khz, &(pTestPara->cycle_10k_100Khz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_1k_10Khz, &(pTestPara->cycle_1k_10Khz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_100_1Khz, &(pTestPara->cycle_100_1Khz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_10_100hz, &(pTestPara->cycle_10_100hz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_1_10hz, &(pTestPara->cycle_1_10hz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_01_1hz, &(pTestPara->cycle_01_1hz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_001_01hz, &(pTestPara->cycle_001_01hz));  //获取频圈的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_0001_001hz, &(pTestPara->cycle_0001_001hz));  //获取频圈的值
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_00001_0001hz, &(pTestPara->cycle_00001_0001hz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_000001_00001hz, &(pTestPara->cycle_000001_00001hz));  //获取频圈的值 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->DrawingTypeID, &(pTestPara->impDrawingType));  //获取频圈的值
	
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_QUIETTIME, &(pTestPara->quietTime));                 //采样静止时间
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, &(pTestPara->timeStep));			           //采样时间间隔
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, &(pTestPara->runTime));				       //运行时间
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLENUMBER, &(pTestPara->sampleNumber));		        //采样数 
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_CURRENTRANGE, &(pTestPara->rangeMode));			    //电阻档位选着
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, &(pTestPara->sampleRate));					//扫描速率
}
//==================================================================================================================================   
static unsigned char GetXorCheckVal(unsigned char* pUartBuf, unsigned char lenth)   //获取异或值
{
	unsigned char i, xorCheck=0;
	for(i=1;i<lenth;i++)
		xorCheck ^= *(pUartBuf+i);	
	return xorCheck;	
}
//==================================================================================================================================   
static float GetDoblePointVal(float leftVal, float rightVal, TestParaTypeDef* pTestPara)  //输入：左值，右值，point；输出：得到的是频点之间的差值
{
	float doublePointVal, temp;
	temp = rightVal - leftVal;
	if(temp > 100000)																			  
	{
	 	doublePointVal = temp/pTestPara->points_100k_1Mhz;	
	}
	else if(temp > 10000)
	{
		doublePointVal = temp/pTestPara->points_10k_100Khz;   	
	}
	else if(temp > 1000)
	{
		doublePointVal = temp/pTestPara->points_1k_10Khz;   	
	}
	else if(temp > 100)
	{
		doublePointVal = temp/pTestPara->points_100_1Khz;   	
	}
	else if(temp > 10)
	{
		doublePointVal = temp/pTestPara->points_10_100hz;   	
	}
	else if(temp > 1)
	{
		doublePointVal = temp/pTestPara->points_1_10hz;   	
	}
	else if(temp > 0.1)
	{
		doublePointVal = temp/pTestPara->points_01_1hz;   	
	}
	else if(temp > 0.01)
	{
		doublePointVal = temp/pTestPara->points_001_01hz;   	
	}
	else if(temp > 0.001)
	{
		doublePointVal = temp/pTestPara->points_0001_001hz;   									
	}
	else if(temp > 0.0001)
	{
		doublePointVal = temp/pTestPara->points_00001_0001hz;   	
	}
	else
	{
		doublePointVal = temp/pTestPara->points_000001_00001hz;   	
	}
	return doublePointVal;
}
//==========================================================================================================  
static void GetHighFreqRange(TestParaTypeDef* pTestPara, float *leftVal, float *rightVal)
{
	if(pTestPara->highFreq>100000 && pTestPara->highFreq<=1000000)
	{
		*leftVal = 100000.0;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 1000000.0;											  
	}
	else if(pTestPara->highFreq>10000 && pTestPara->highFreq<=100000)
	{
		*leftVal = 10000.0;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 100000.0;
	}
	else if(pTestPara->highFreq>1000 && pTestPara->highFreq<=10000)
	{
		*leftVal = 1000.0;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 10000.0;
	}
	else if(pTestPara->highFreq>100 && pTestPara->highFreq<=1000)
	{
		*leftVal = 100.0;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 1000.0;
	}
	else if(pTestPara->highFreq>10 && pTestPara->highFreq<=100)
	{
		*leftVal = 10.0;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 100.0;
	}
	else if(pTestPara->highFreq>1 && pTestPara->highFreq<=10)
	{
		*leftVal = 1.0;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 10.0;
	}
	else if(pTestPara->highFreq>0.1 && pTestPara->highFreq<=1)
	{
		*leftVal = 0.1;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 1.0;
	}
	else if(pTestPara->highFreq>0.01 && pTestPara->highFreq<=0.1) 			
	{
		*leftVal = 0.01;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 0.1;
	}
	else if(pTestPara->highFreq>0.001 && pTestPara->highFreq<=0.01) 			
	{
		*leftVal = 0.001;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 0.01;
	}
	else if(pTestPara->highFreq>0.0001 && pTestPara->highFreq<=0.001) 			
	{
		*leftVal = 0.0001;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 0.001;
	}
	else			
	{
		*leftVal = 0.00001;								 	//确定最大频率所在的范围以此来确定leftVal和R一个RightVal;   
		*rightVal = 0.0001;
	}	
}
//==================================================================================================================================   
static void PrepareCfgTxData(TestParaTypeDef* pTestPara, unsigned char devAddr, unsigned char* pmeasUartTxBuf, enum TestMode expType)	  // IT实验协议
{
	int sampleNumber = 1;
	unsigned int cnt = 0;
	int temp  = 0;
	int freq = 1; //频率字；范围是1-255
	*pmeasUartTxBuf=0xAA;													  //协议帧头
	*(pmeasUartTxBuf+1)=devAddr;     				                          //设备地址默认为OX00
	*(pmeasUartTxBuf+2)=MSG_TYPE_SITTING_REGISTER1;				              //命令种类为设置寄存器1
	switch(expType)
	{
		case IT:
			*(pmeasUartTxBuf+3)=0x01;				  //实验类型  		
			break;
		case LSV:
		case CV:
		case TAFEL:
			*(pmeasUartTxBuf+3)=0x02;
			break;
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV:
			*(pmeasUartTxBuf+3)=0x03;
			break;  
		case IMP:
			*(pmeasUartTxBuf+3)=0x04;
			break;
	 }
	*(pmeasUartTxBuf+4)=0x00;	   //保留位
	switch(pTestPara->rangeMode)   //档位选择 
	{
		case 0:
			*(pmeasUartTxBuf+5) = 0XB;	
		break;
		case 1:
			*(pmeasUartTxBuf+5) = 0X01;
		break;
		case 2:
			*(pmeasUartTxBuf+5) = 0X10;
		break;
		case 3:
			*(pmeasUartTxBuf+5) = 0X11;
		break;
		case 4:
			*(pmeasUartTxBuf+5) = 0X4;
		break;
		case 5:
			*(pmeasUartTxBuf+5) = 0X5;
		break;
		case 6:
			*(pmeasUartTxBuf+5) = 0X6;
		break;
		case 7:
			*(pmeasUartTxBuf+5) = 0X7;
		break;
		case 8:
			*(pmeasUartTxBuf+5) = 0X8;
		break;
		case 9:
			*(pmeasUartTxBuf+5) = 0X9;
		break;
		case 10:
			*(pmeasUartTxBuf+5) = 0XA;
		break;
	}
	if((pTestPara->posOrNeg) == 1)										//扫描方向是反扫
	{
	 	 *(pmeasUartTxBuf+5)= *(pmeasUartTxBuf+5) | 0x00000040;			//置第6个字节第六位为1		
	}
	else if((pTestPara->posOrNeg) == 0)								   //扫描方向是正向
	{
		 *(pmeasUartTxBuf+5) = *(pmeasUartTxBuf+5) & 0xFFFFFFBF;		//置第6个字节第六位为0
	}
	
	if( (abs(pTestPara->init)<2.5) && (abs(pTestPara->start)<2.5) &&(abs(pTestPara->stop)<2.5))
	{
		*(pmeasUartTxBuf+5)=*(pmeasUartTxBuf+5) & 0xFFFFFFEF;			 //置第四个字节第四位为0 
		amplificationFactor=1.0;									     //放大1倍
	}else
	{
		*(pmeasUartTxBuf+5)=*(pmeasUartTxBuf+5) | 0x00000010;			 //置第四个字节第四位为1    
		amplificationFactor=5.1;								         //放大5.1倍
	}
	*(pmeasUartTxBuf+8)=(unsigned char)((pTestPara->quietTime) & 0X0000FF);
	*(pmeasUartTxBuf+7)=(unsigned char)(((pTestPara->quietTime)>>8) & 0X0000FF); 
	*(pmeasUartTxBuf+6)=(unsigned char)(((pTestPara->quietTime)>>16) & 0X0000FF);  //静止时间
	if(pTestPara->sampleNumber == 1)
		temp = 0;
	else
	{
		while(pTestPara->sampleNumber != sampleNumber)
		{
		 sampleNumber = sampleNumber * 2;
		 temp += 1;
		}
	}
	*(pmeasUartTxBuf+9)=(unsigned char)(temp&0XFF);         //采样点数  			             

	switch(expType)
	{
		case IT:
				cnt = (pTestPara->timeStep)*1*10000000-1;    //采样间隔 
				*(pmeasUartTxBuf+13)=(unsigned char)(cnt & 0X000000FF);
				*(pmeasUartTxBuf+12)=(unsigned char)((cnt>>8) & 0X000000FF);
				*(pmeasUartTxBuf+11)=(unsigned char)((cnt>>16) & 0X000000FF); 
				*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);
				temp = ((pTestPara->init) / amplificationFactor + 2.5) * 13107.0;  //初始电位  
				*(pmeasUartTxBuf+15)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+14)=(unsigned char)((temp>>8) & 0X00FF);			                 
				*(pmeasUartTxBuf+18)=(unsigned char)((pTestPara->runTime)& 0X0000FF);
				*(pmeasUartTxBuf+17)=(unsigned char)(((pTestPara->runTime)>>8)& 0X0000FF);		
				*(pmeasUartTxBuf+16)=(unsigned char)(((pTestPara->runTime)>>16)& 0X0000FF);					
			break;
		case LSV:
		case CV:
		case TAFEL:
				cnt = ((pTestPara->voltageStep)/(pTestPara->sampleRate))*1*10000000-1;	    //采样时间间隔=采样电压间隔/扫描速率 单位是S
				*(pmeasUartTxBuf+13)=(unsigned char)(cnt & 0X000000FF);
				*(pmeasUartTxBuf+12)=(unsigned char)((cnt>>8) & 0X000000FF);
				*(pmeasUartTxBuf+11)=(unsigned char)((cnt>>16) & 0X000000FF); 
				*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);			                //采样时间间隔
				
				int n1 = 0,n2 = 0;
				while(n2 < 1)
				{
					n1 ++; 
					n2 = ((n1 * 76 * amplificationFactor) / (pTestPara->sampleRate));
				}
				*(pmeasUartTxBuf+17)=(unsigned char)(n2&0X000000FF);
				*(pmeasUartTxBuf+16)=(unsigned char)((n2>>8)&0X000000FF);			//电压增量       
				*(pmeasUartTxBuf+15)=(unsigned char)((n2>>16)&0X000000FF); 
				*(pmeasUartTxBuf+14)=(unsigned char)(n1&0XFF);		                                              

				temp = ((pTestPara->start) / amplificationFactor + 2.5) * 13107.0;
				*(pmeasUartTxBuf+19)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+18)=(unsigned char)((temp>>8) & 0X00FF);			                 //初始电压	

				temp = ((pTestPara->stop) / amplificationFactor + 2.5) * 13107.0;
				*(pmeasUartTxBuf+21)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+20)=(unsigned char)((temp>>8) & 0X00FF);			                 //结束电位	

				temp = ((pTestPara->init) / amplificationFactor + 2.5) * 13107.0;
				*(pmeasUartTxBuf+23)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+22)=(unsigned char)((temp>>8) & 0X00FF);			                 //起始电位 

				*(pmeasUartTxBuf+26)=(unsigned char)((pTestPara->sweepSegments) & 0X0000FF);
				*(pmeasUartTxBuf+25)=(unsigned char)(((pTestPara->sweepSegments)>>8) & 0X0000FF);	         //LSV运行段数为1，高电压维持时间为0；CV运行段数为N，高电压维持时间为0；TAFEL运行段数为1或2，高电压维持时间为n；
				*(pmeasUartTxBuf+24)=(unsigned char)(((pTestPara->sweepSegments)>>16) & 0X0000FF); 
				
				temp = (pTestPara->holdTime) * 10000; 						 //高电压保持时间；单位是0.1ms
				*(pmeasUartTxBuf+29)=(unsigned char)(temp&0X0000FF);					
				*(pmeasUartTxBuf+28)=(unsigned char)((temp>>8)&0X0000FF);	
				*(pmeasUartTxBuf+27)=(unsigned char)((temp>>16)&0X0000FF);	
			break;
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV: 
			cnt = (pTestPara->timeStep)*1*10000000-1;
			*(pmeasUartTxBuf+13)=(unsigned char)(cnt & 0X000000FF);
			*(pmeasUartTxBuf+12)=(unsigned char)((cnt>>8) & 0X000000FF);
			*(pmeasUartTxBuf+11)=(unsigned char)((cnt>>16) & 0X000000FF); 
			*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);			                //采样间隔
			
			temp = ((pTestPara->init) / amplificationFactor + 2.5) * 13107.0;
			*(pmeasUartTxBuf+15)=(unsigned char)(temp & 0X00FF);
			*(pmeasUartTxBuf+14)=(unsigned char)((temp>>8) & 0X00FF);			                 //起始电位 
			
			temp = ((pTestPara->stop) / amplificationFactor + 2.5) * 13107.0;
			*(pmeasUartTxBuf+17)=(unsigned char)(temp & 0X00FF);
			*(pmeasUartTxBuf+16)=(unsigned char)((temp>>8) & 0X00FF);			                 //结束电位
			
			 cnt = ((pTestPara->voltageStep)/amplificationFactor)*13107.0;
			*(pmeasUartTxBuf+19)=(unsigned char)(cnt & 0X000000FF);
			*(pmeasUartTxBuf+18)=(unsigned char)((cnt>>8) & 0X000000FF);                          //电压差值字节
			
			 cnt = ((pTestPara->amplitude)/amplificationFactor)*13107.0;
			*(pmeasUartTxBuf+21)=(unsigned char)(cnt & 0X000000FF);
			*(pmeasUartTxBuf+20)=(unsigned char)((cnt>>8) & 0X000000FF);                          //振幅值字节
			
			*(pmeasUartTxBuf+23)=(unsigned char)((pTestPara->sweepSegments) & 0X0000FF);
			*(pmeasUartTxBuf+22)=(unsigned char)(((pTestPara->sweepSegments)>>8) & 0X0000FF);	    //运行段数
			break;
		case IMP:
			if(impCloseFlag == 1)
			{
				GetHighFreqRange(&TestPara, &leftVal, &rightVal);
				minFreq = pTestPara->lowFreq;
				impCloseFlag = 0;
			}
			temp = (pTestPara->init/amplificationFactor + 2.5)*13107.0;				//初始电压						 
			*(pmeasUartTxBuf+15)=(unsigned char)(temp & 0X00FF);
			*(pmeasUartTxBuf+14)=(unsigned char)((temp>>8) & 0X00FF);
			temp = (pTestPara->amplitude)*34133.0;											  //交流幅值
			*(pmeasUartTxBuf+17)=(unsigned char)(temp & 0X00FF);						
			*(pmeasUartTxBuf+16)=(unsigned char)((temp>>8) & 0X00FF);
			if(pointInFlag == 0)
			{
				val = GetDoblePointVal(leftVal, rightVal, pTestPara);								  //频段/频点 
				fsin = rightVal;			 //fsin 为交流信号频率初始化值 
				if(rightVal == 1000000)
					pointInNumber = (pTestPara->points_100k_1Mhz);
				else if(rightVal == 100000)
					pointInNumber = (pTestPara->points_10k_100Khz);
				else if(rightVal == 10000)
					pointInNumber = (pTestPara->points_1k_10Khz);
				else if(rightVal == 1000)
					pointInNumber = (pTestPara->points_100_1Khz);
				else if(rightVal == 100)
					pointInNumber = (pTestPara->points_10_100hz);
				else if(rightVal == 10)
					pointInNumber = (pTestPara->points_1_10hz);
				else if(rightVal == 1)
					pointInNumber = (pTestPara->points_01_1hz);
				else if(rightVal == 0.1) 			
					pointInNumber = (pTestPara->points_001_01hz);		//段内循环次数；频点首和频点尾不参于
				else if(rightVal == 0.01) 			
					pointInNumber = (pTestPara->points_0001_001hz);		//段内循环次数；频点首和频点尾不参于
				else if(rightVal == 0.001) 			
					pointInNumber = (pTestPara->points_00001_0001hz);		//段内循环次数；频点首和频点尾不参于
				else			
					pointInNumber = (pTestPara->points_000001_00001hz);		//段内循环次数；频点首和频点尾不参于
				pointInFlag = 1;
			}
			 fsin = fsin - val;
			 if(fsin - val <= 0)
			 {
				 leftVal/=10;
				 rightVal/=10;
				 pointInFlag = 0;
			 }
			 float timeStep;
			 if(fsin > 100)          //交流信号频率大于100HZ
			 {
				 timeStep  = 1/(fsin*10);								//采样时间间隔
			 }else
			 {
				 timeStep  = 1/(fsin*10);
			 }
			 cnt = timeStep*1*10000000-1;
			*(pmeasUartTxBuf+13)=(unsigned char)(cnt & 0X000000FF);
			*(pmeasUartTxBuf+12)=(unsigned char)((cnt>>8) & 0X000000FF);
			*(pmeasUartTxBuf+11)=(unsigned char)((cnt>>16) & 0X000000FF); 
			*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);			                //采样时间间隔
			 freq  = fsin/4578;
			 if(freq*4578/fsin < 1)
			 {
				 freq+=1;
			 }
			 cnt = freq*4578/fsin - 1;
			
			*(pmeasUartTxBuf+19)=(unsigned char)(freq & 0X0000FF);		 //频率字freq ;范围是1-255
			*(pmeasUartTxBuf+18)=(unsigned char)((freq>>8) & 0X0000FF);	    
 
			*(pmeasUartTxBuf+24)=(unsigned char)(cnt       & 0X0000FF);
			*(pmeasUartTxBuf+23)=(unsigned char)((cnt>>8)  & 0X0000FF);	    
			*(pmeasUartTxBuf+22)=(unsigned char)((cnt>>16) & 0X0000FF);
			*(pmeasUartTxBuf+21)=(unsigned char)((cnt>>24) & 0X0000FF);	    
		
			*(pmeasUartTxBuf+26)=(unsigned char)((pTestPara->cycle_10_100hz) & 0X0000FF);
			*(pmeasUartTxBuf+25)=(unsigned char)(((pTestPara->cycle_10_100hz)>>8) & 0X0000FF);	      //运行周期数
			break;
	 }	
	*(pmeasUartTxBuf+SA51_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA51_UART_TX_LEN-1);   //校验位
}
//==================================================================================================================================   
static void PrepareCfgTxData2(TestParaTypeDef* pTestPara, unsigned char devAddr, unsigned char* pmeasUartTxBuf, enum TestMode expType)	  // 协议帧2
{
	*pmeasUartTxBuf=0xAA;
	*(pmeasUartTxBuf+1)=devAddr;     				                          //设备地址
	*(pmeasUartTxBuf+2)=MSG_TYPE_SITTING_REGISTER2;				              //命令种类
	*(pmeasUartTxBuf+3)=0x03;                                                 //实验类型
	*(pmeasUartTxBuf+4)=0x00;	                                              //保留位
	switch(expType)
	{
		case SV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X00;
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //脉冲1宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //脉冲2宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //采样宽度取值范围从0.1ms到10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	       //脉冲3宽度取值范围从1ms到50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
			break;
		case DPV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X01;
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //脉冲1宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+6)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	  
			*(pmeasUartTxBuf+5)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //采样宽度取值范围从0.1ms到10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			break;
		case NPV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X02;  
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //脉冲1宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //脉冲2宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //采样宽度取值范围从0.1ms到10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	       //脉冲3宽度取值范围从1ms到50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
		case DNPV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X02;
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //脉冲1宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //脉冲2宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //采样宽度取值范围从0.1ms到10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth) - (pTestPara->pluseWidth2)) * 1000) & 0X0000FF));	       //脉冲3宽度取值范围从1ms到50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth) - (pTestPara->pluseWidth2)) * 1000)>>8) & 0X0000FF));
			break;
		case SWV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X03;
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //脉冲1宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //脉冲2宽度取值范围从1ms到10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //采样宽度取值范围从0.1ms到10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	       //脉冲3宽度取值范围从1ms到50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
			*(pmeasUartTxBuf+17)=(unsigned char)((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000)) & 0X000000FF));	  //脉冲4宽度取值范围大于10us; 
			*(pmeasUartTxBuf+16)=(unsigned char)(((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000))>>8) & 0X000000FF));
			*(pmeasUartTxBuf+15)=(unsigned char)(((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000))>>16) & 0X000000FF)); 
			*(pmeasUartTxBuf+14)=(unsigned char)(((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000))>>24) & 0X000000FF));		
			break;
	}
	*(pmeasUartTxBuf+SA51_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA51_UART_TX_LEN-1);   //校验位  
}
//==================================================================================================================================   
void ProtocolCfgTxData(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf, enum TestMode expType)
{
	switch(expType)
	{
	 	case IT:
		case CV:
		case LSV:
		case TAFEL:
		case IMP:   
			PrepareCfgTxData(&TestPara, devAddr, pmeasUartTxBuf, expType); 
			ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN); //向指定串行口(comSelect)的输出队列写(SA51_UART_TX_LEN=33)入若干字节的信息;//即将读取到的参数发送出去	
			break;
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV:				 //这5个实验都是连续发两个33位个字节来设置寄存器
			PrepareCfgTxData(&TestPara, devAddr, pmeasUartTxBuf, expType); 
			ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN); //向指定串行口(comSelect)的输出队列写(SA51_UART_TX_LEN=33)入若干字节的信息;//即将读取到的参数发送出去	
			Delay(0.2);
			PrepareCfgTxData2(&TestPara, devAddr, pmeasUartTxBuf, expType); 
			ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN); //向指定串行口(comSelect)的输出队列写(SA51_UART_TX_LEN=33)入若干字节的信息;//即将读取到的参数发送出去	
			break;
	}
}
//==================================================================================================================================   
void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, enum TestMode expType, unsigned char* pmeasUartTxBuf)
{
	switch(expType)
	{
		case IT:
			GetTestPara(&ItPanel, &TestPara);
			break;
		case CV:
		    GetTestPara(&CvPanel, &TestPara);
			break;
		case LSV:
			GetTestPara(&LsvPanel, &TestPara);
			break;
		case TAFEL:
			GetTestPara(&TafelPanel, &TestPara);
			break;
		case SV:
			GetTestPara(&SvPanel,&TestPara);
			break;
		case NPV:
			GetTestPara(&NpvPanel,&TestPara);
			break;
		case DPV:
			GetTestPara(&DpvPanel, &TestPara);
			break;
		case DNPV:
			GetTestPara(&DnpvPanel,&TestPara);
			break;
		case SWV:
			GetTestPara(&SwvPanel,&TestPara);
			break;
		case IMP:
			GetTestPara(&ImpPanel,&TestPara);
			break;
	}
	ProtocolCfgTxData(comSelect, devAddr, pmeasUartTxBuf, expType);
}
//==================================================================================================================================   
void ProtocolRun(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)  //开始采集
{
	*pmeasUartTxBuf=0xAA;
	*(pmeasUartTxBuf+1)=devAddr;
	*(pmeasUartTxBuf+2)=MSG_TYPE_RUN;
	for(int i = 3;i<SA51_UART_TX_LEN-1;i++)
	{
		*(pmeasUartTxBuf+i)=0x00;	
	}
	*(pmeasUartTxBuf+SA51_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA51_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN);
}
//==================================================================================================================================   
void ProtocolStop(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)  //停止采集
{
	*pmeasUartTxBuf=0xAA;
	*(pmeasUartTxBuf+1)=devAddr;
	*(pmeasUartTxBuf+2)=MSG_TYPE_STOP;
	for(int i = 3;i<SA51_UART_TX_LEN-1;i++)
	{
		*(pmeasUartTxBuf+i)=0x00;	
	}
	*(pmeasUartTxBuf+SA51_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA51_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN);
}
//==================================================================================================================================   
void ProtocolQuery(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)  //循环查询
{
	*pmeasUartTxBuf=0xAA;
	*(pmeasUartTxBuf+1)=devAddr;
	*(pmeasUartTxBuf+2)=MSG_TYPE_QUERY;
	for(int i = 3;i<SA51_UART_TX_LEN-1;i++)
	{
		*(pmeasUartTxBuf+i)=0x00;	
	}
	*(pmeasUartTxBuf+SA51_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA51_UART_TX_LEN-1);
	ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN);
}
//==================================================================================================================================
void ProtocolGetData(unsigned char* pmeasUartRxBuf, RxDataTypeDef* pRxData)	//Get data from UART Rx Buffer
{
	pRxData->rxDevAddr=*(pmeasUartRxBuf+1);
	pRxData->rxResistance=*(pmeasUartRxBuf+2);
	switch(*(pmeasUartRxBuf+3))
	{
	  case 1:
		pRxData->rxResistance1 = 1;  //电阻为1欧
	    break;
		case 2:
		pRxData->rxResistance1 = 10;  //电阻为10欧
	    break;
		case 3:
		pRxData->rxResistance1 = 100;  //电阻为100欧
	    break;
		case 4:
		pRxData->rxResistance1 = 1000;  //电阻为1K欧
	    break;
		case 5:
		pRxData->rxResistance1 = 10000;  //电阻为10K欧
	    break;
		case 6:
		pRxData->rxResistance1 = 100000;  //电阻为100K欧
	    break;
		case 7:
		pRxData->rxResistance1 = 1000000;  //电阻为1M欧
	    break;
		case 8:
		pRxData->rxResistance1 = 10000000;  //电阻为10M欧
	    break;
		case 9:
		pRxData->rxResistance1 = 100000000;  //电阻为100M欧
	    break;
		case 10:
		pRxData->rxResistance1 = 1000000000;  //电阻为1G欧
	    break;
	}
	if(((*(pmeasUartRxBuf+4) >> 5) & 1) == 1)
	{
		pRxData->rxVoltage1=((float)((((*(pmeasUartRxBuf+4) << 8) | *(pmeasUartRxBuf+5)) & 0x1FFF) / 8192.00) - 1);
	}else
	{
		pRxData->rxVoltage1=((float)(((*(pmeasUartRxBuf+4) << 8) | *(pmeasUartRxBuf+5)) & 0x1FFF) / 8192.00);
	}
}
//================================================================================================================================== 
//imp实验单独一个解析接收回来数据的函数
void ProtocolGetImpData(unsigned char* pmeasUartRxBuf, RxDataTypeDef* pRxData)
{
	pRxData->dataFlag=*(pmeasUartRxBuf+1);
	pRxData->channel2Data=(*(pmeasUartRxBuf+2)<< 8) | *(pmeasUartRxBuf+3);
	if(pRxData->channel2Data > 8192)
		pRxData->channel2Data -= 65536;
	pRxData->channel1Data=(*(pmeasUartRxBuf+4)<< 8) | *(pmeasUartRxBuf+5);
	if(pRxData->channel1Data > 8192)
		pRxData->channel1Data -= 65536;
	channel1Real[num] = pRxData->channel2Data;
	channel2Real[num] = pRxData->channel1Data;
	num++;
}

