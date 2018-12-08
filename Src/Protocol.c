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
	MSG_TYPE_SYSTEM_7RESET=0x10,	//ϵͳ��λ
	MSG_TYPE_REPORT_ID=0x20,	  //��ѯ�豸
	MSG_TYPE_SITTING_REGISTER1=0x30,  //���üĴ���1
	MSG_TYPE_SITTING_REGISTER2=0x31,  //���üĴ���2
	MSG_TYPE_RUN=0x40,				  //��ʼ�ɼ�
	MSG_TYPE_STOP=0x50,				  //ֹͣ�ɼ�
	MSG_TYPE_QUERY=0x60				  //��ѯ
};
//==============================================================================
// Static global variables
static float amplificationFactor = 1.0;   //�Ŵ�ϵ�� 
float fsin, val = 0;                    //����Ƶ��ֵ
float leftVal, rightVal;
float minFreq = 0.0;
//==============================================================================
// Static functions

//==============================================================================
// Global variables
unsigned char pointInFlag = 0; //Ƶ����֮���ѭ����־λ
unsigned char impCloseFlag = 0;//impʵ��رձ�־λ
unsigned char pointInNumber = 1;//����ѭ������
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
    GetCtrlVal(pExpPanel->panelHandle, pExpPanel->InitID, &(pTestPara->init));                //��ȡ��ʼ��ѹ�ؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->StopID, &(pTestPara->stop));	              //��ȡ������ѹ�ؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->StartID, &(pTestPara->start));              //��ȡ��ʼ��ѹ�ؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->VoltageStepID, &(pTestPara->voltageStep));   //��ȡ��ѹ�����ؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PosOrNegID, &(pTestPara->posOrNeg)); 		    //��ȡ����ɨ��ؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->SweepSegmentsID, &(pTestPara->sweepSegments));  //��ȡɨ������ؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->HoldTimeID, &(pTestPara->holdTime)); 			   //��ȡ���ָߵ�ѹ�ؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->SamplingWidthID, &(pTestPara->samplingWidth));    //��ȡ������ȿؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PulseWidthID, &(pTestPara->pluseWidth));          //��ȡ�����ȿؼ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PulsePeriodID, &(pTestPara->plusePeriod));        //��ȡ�������ڿؼ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PulseWidth2ID, &(pTestPara->pluseWidth2));        //��ȡ�����ȿؼ�2��ֵ    
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->AmplitudeID, &(pTestPara->amplitude));            //��ȡ����ؼ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->FrequencyID, &(pTestPara->frequency));      //��ȡ�����ȿؼ�4��ֵ
	
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->HighFreqID, &(pTestPara->highFreq));  //��ȡ���Ƶ�ʵ�ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->LowFreqID, &(pTestPara->lowFreq)); 	//��ȡ���Ƶ�ʵ�ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_100k_1Mhz, &(pTestPara->points_100k_1Mhz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_10k_100Khz, &(pTestPara->points_10k_100Khz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_1k_10Khz, &(pTestPara->points_1k_10Khz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_100_1Khz, &(pTestPara->points_100_1Khz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_10_100hz, &(pTestPara->points_10_100hz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_1_10hz, &(pTestPara->points_1_10hz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_01_1hz, &(pTestPara->points_01_1hz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_001_01hz, &(pTestPara->points_001_01hz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_0001_001hz, &(pTestPara->points_0001_001hz));  //��ȡƵ���ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_00001_0001hz, &(pTestPara->points_00001_0001hz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->PointsID_000001_00001hz, &(pTestPara->points_000001_00001hz));  //��ȡƵ���ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_100k_1Mhz, &(pTestPara->cycle_100k_1Mhz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_10k_100Khz, &(pTestPara->cycle_10k_100Khz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_1k_10Khz, &(pTestPara->cycle_1k_10Khz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_100_1Khz, &(pTestPara->cycle_100_1Khz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_10_100hz, &(pTestPara->cycle_10_100hz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_1_10hz, &(pTestPara->cycle_1_10hz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_01_1hz, &(pTestPara->cycle_01_1hz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_001_01hz, &(pTestPara->cycle_001_01hz));  //��ȡƵȦ��ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_0001_001hz, &(pTestPara->cycle_0001_001hz));  //��ȡƵȦ��ֵ
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_00001_0001hz, &(pTestPara->cycle_00001_0001hz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->CycleID_000001_00001hz, &(pTestPara->cycle_000001_00001hz));  //��ȡƵȦ��ֵ 
	GetCtrlVal(pExpPanel->panelHandle, pExpPanel->DrawingTypeID, &(pTestPara->impDrawingType));  //��ȡƵȦ��ֵ
	
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_QUIETTIME, &(pTestPara->quietTime));                 //������ֹʱ��
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, &(pTestPara->timeStep));			           //����ʱ����
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, &(pTestPara->runTime));				       //����ʱ��
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLENUMBER, &(pTestPara->sampleNumber));		        //������ 
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_CURRENTRANGE, &(pTestPara->rangeMode));			    //���赵λѡ��
	GetCtrlVal(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, &(pTestPara->sampleRate));					//ɨ������
}
//==================================================================================================================================   
static unsigned char GetXorCheckVal(unsigned char* pUartBuf, unsigned char lenth)   //��ȡ���ֵ
{
	unsigned char i, xorCheck=0;
	for(i=1;i<lenth;i++)
		xorCheck ^= *(pUartBuf+i);	
	return xorCheck;	
}
//==================================================================================================================================   
static float GetDoblePointVal(float leftVal, float rightVal, TestParaTypeDef* pTestPara)  //���룺��ֵ����ֵ��point��������õ�����Ƶ��֮��Ĳ�ֵ
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
		*leftVal = 100000.0;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 1000000.0;											  
	}
	else if(pTestPara->highFreq>10000 && pTestPara->highFreq<=100000)
	{
		*leftVal = 10000.0;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 100000.0;
	}
	else if(pTestPara->highFreq>1000 && pTestPara->highFreq<=10000)
	{
		*leftVal = 1000.0;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 10000.0;
	}
	else if(pTestPara->highFreq>100 && pTestPara->highFreq<=1000)
	{
		*leftVal = 100.0;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 1000.0;
	}
	else if(pTestPara->highFreq>10 && pTestPara->highFreq<=100)
	{
		*leftVal = 10.0;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 100.0;
	}
	else if(pTestPara->highFreq>1 && pTestPara->highFreq<=10)
	{
		*leftVal = 1.0;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 10.0;
	}
	else if(pTestPara->highFreq>0.1 && pTestPara->highFreq<=1)
	{
		*leftVal = 0.1;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 1.0;
	}
	else if(pTestPara->highFreq>0.01 && pTestPara->highFreq<=0.1) 			
	{
		*leftVal = 0.01;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 0.1;
	}
	else if(pTestPara->highFreq>0.001 && pTestPara->highFreq<=0.01) 			
	{
		*leftVal = 0.001;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 0.01;
	}
	else if(pTestPara->highFreq>0.0001 && pTestPara->highFreq<=0.001) 			
	{
		*leftVal = 0.0001;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 0.001;
	}
	else			
	{
		*leftVal = 0.00001;								 	//ȷ�����Ƶ�����ڵķ�Χ�Դ���ȷ��leftVal��Rһ��RightVal;   
		*rightVal = 0.0001;
	}	
}
//==================================================================================================================================   
static void PrepareCfgTxData(TestParaTypeDef* pTestPara, unsigned char devAddr, unsigned char* pmeasUartTxBuf, enum TestMode expType)	  // ITʵ��Э��
{
	int sampleNumber = 1;
	unsigned int cnt = 0;
	int temp  = 0;
	int freq = 1; //Ƶ���֣���Χ��1-255
	*pmeasUartTxBuf=0xAA;													  //Э��֡ͷ
	*(pmeasUartTxBuf+1)=devAddr;     				                          //�豸��ַĬ��ΪOX00
	*(pmeasUartTxBuf+2)=MSG_TYPE_SITTING_REGISTER1;				              //��������Ϊ���üĴ���1
	switch(expType)
	{
		case IT:
			*(pmeasUartTxBuf+3)=0x01;				  //ʵ������  		
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
	*(pmeasUartTxBuf+4)=0x00;	   //����λ
	switch(pTestPara->rangeMode)   //��λѡ�� 
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
	if((pTestPara->posOrNeg) == 1)										//ɨ�跽���Ƿ�ɨ
	{
	 	 *(pmeasUartTxBuf+5)= *(pmeasUartTxBuf+5) | 0x00000040;			//�õ�6���ֽڵ���λΪ1		
	}
	else if((pTestPara->posOrNeg) == 0)								   //ɨ�跽��������
	{
		 *(pmeasUartTxBuf+5) = *(pmeasUartTxBuf+5) & 0xFFFFFFBF;		//�õ�6���ֽڵ���λΪ0
	}
	
	if( (abs(pTestPara->init)<2.5) && (abs(pTestPara->start)<2.5) &&(abs(pTestPara->stop)<2.5))
	{
		*(pmeasUartTxBuf+5)=*(pmeasUartTxBuf+5) & 0xFFFFFFEF;			 //�õ��ĸ��ֽڵ���λΪ0 
		amplificationFactor=1.0;									     //�Ŵ�1��
	}else
	{
		*(pmeasUartTxBuf+5)=*(pmeasUartTxBuf+5) | 0x00000010;			 //�õ��ĸ��ֽڵ���λΪ1    
		amplificationFactor=5.1;								         //�Ŵ�5.1��
	}
	*(pmeasUartTxBuf+8)=(unsigned char)((pTestPara->quietTime) & 0X0000FF);
	*(pmeasUartTxBuf+7)=(unsigned char)(((pTestPara->quietTime)>>8) & 0X0000FF); 
	*(pmeasUartTxBuf+6)=(unsigned char)(((pTestPara->quietTime)>>16) & 0X0000FF);  //��ֹʱ��
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
	*(pmeasUartTxBuf+9)=(unsigned char)(temp&0XFF);         //��������  			             

	switch(expType)
	{
		case IT:
				cnt = (pTestPara->timeStep)*1*10000000-1;    //������� 
				*(pmeasUartTxBuf+13)=(unsigned char)(cnt & 0X000000FF);
				*(pmeasUartTxBuf+12)=(unsigned char)((cnt>>8) & 0X000000FF);
				*(pmeasUartTxBuf+11)=(unsigned char)((cnt>>16) & 0X000000FF); 
				*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);
				temp = ((pTestPara->init) / amplificationFactor + 2.5) * 13107.0;  //��ʼ��λ  
				*(pmeasUartTxBuf+15)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+14)=(unsigned char)((temp>>8) & 0X00FF);			                 
				*(pmeasUartTxBuf+18)=(unsigned char)((pTestPara->runTime)& 0X0000FF);
				*(pmeasUartTxBuf+17)=(unsigned char)(((pTestPara->runTime)>>8)& 0X0000FF);		
				*(pmeasUartTxBuf+16)=(unsigned char)(((pTestPara->runTime)>>16)& 0X0000FF);					
			break;
		case LSV:
		case CV:
		case TAFEL:
				cnt = ((pTestPara->voltageStep)/(pTestPara->sampleRate))*1*10000000-1;	    //����ʱ����=������ѹ���/ɨ������ ��λ��S
				*(pmeasUartTxBuf+13)=(unsigned char)(cnt & 0X000000FF);
				*(pmeasUartTxBuf+12)=(unsigned char)((cnt>>8) & 0X000000FF);
				*(pmeasUartTxBuf+11)=(unsigned char)((cnt>>16) & 0X000000FF); 
				*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);			                //����ʱ����
				
				int n1 = 0,n2 = 0;
				while(n2 < 1)
				{
					n1 ++; 
					n2 = ((n1 * 76 * amplificationFactor) / (pTestPara->sampleRate));
				}
				*(pmeasUartTxBuf+17)=(unsigned char)(n2&0X000000FF);
				*(pmeasUartTxBuf+16)=(unsigned char)((n2>>8)&0X000000FF);			//��ѹ����       
				*(pmeasUartTxBuf+15)=(unsigned char)((n2>>16)&0X000000FF); 
				*(pmeasUartTxBuf+14)=(unsigned char)(n1&0XFF);		                                              

				temp = ((pTestPara->start) / amplificationFactor + 2.5) * 13107.0;
				*(pmeasUartTxBuf+19)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+18)=(unsigned char)((temp>>8) & 0X00FF);			                 //��ʼ��ѹ	

				temp = ((pTestPara->stop) / amplificationFactor + 2.5) * 13107.0;
				*(pmeasUartTxBuf+21)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+20)=(unsigned char)((temp>>8) & 0X00FF);			                 //������λ	

				temp = ((pTestPara->init) / amplificationFactor + 2.5) * 13107.0;
				*(pmeasUartTxBuf+23)=(unsigned char)(temp & 0X00FF);
				*(pmeasUartTxBuf+22)=(unsigned char)((temp>>8) & 0X00FF);			                 //��ʼ��λ 

				*(pmeasUartTxBuf+26)=(unsigned char)((pTestPara->sweepSegments) & 0X0000FF);
				*(pmeasUartTxBuf+25)=(unsigned char)(((pTestPara->sweepSegments)>>8) & 0X0000FF);	         //LSV���ж���Ϊ1���ߵ�ѹά��ʱ��Ϊ0��CV���ж���ΪN���ߵ�ѹά��ʱ��Ϊ0��TAFEL���ж���Ϊ1��2���ߵ�ѹά��ʱ��Ϊn��
				*(pmeasUartTxBuf+24)=(unsigned char)(((pTestPara->sweepSegments)>>16) & 0X0000FF); 
				
				temp = (pTestPara->holdTime) * 10000; 						 //�ߵ�ѹ����ʱ�䣻��λ��0.1ms
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
			*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);			                //�������
			
			temp = ((pTestPara->init) / amplificationFactor + 2.5) * 13107.0;
			*(pmeasUartTxBuf+15)=(unsigned char)(temp & 0X00FF);
			*(pmeasUartTxBuf+14)=(unsigned char)((temp>>8) & 0X00FF);			                 //��ʼ��λ 
			
			temp = ((pTestPara->stop) / amplificationFactor + 2.5) * 13107.0;
			*(pmeasUartTxBuf+17)=(unsigned char)(temp & 0X00FF);
			*(pmeasUartTxBuf+16)=(unsigned char)((temp>>8) & 0X00FF);			                 //������λ
			
			 cnt = ((pTestPara->voltageStep)/amplificationFactor)*13107.0;
			*(pmeasUartTxBuf+19)=(unsigned char)(cnt & 0X000000FF);
			*(pmeasUartTxBuf+18)=(unsigned char)((cnt>>8) & 0X000000FF);                          //��ѹ��ֵ�ֽ�
			
			 cnt = ((pTestPara->amplitude)/amplificationFactor)*13107.0;
			*(pmeasUartTxBuf+21)=(unsigned char)(cnt & 0X000000FF);
			*(pmeasUartTxBuf+20)=(unsigned char)((cnt>>8) & 0X000000FF);                          //���ֵ�ֽ�
			
			*(pmeasUartTxBuf+23)=(unsigned char)((pTestPara->sweepSegments) & 0X0000FF);
			*(pmeasUartTxBuf+22)=(unsigned char)(((pTestPara->sweepSegments)>>8) & 0X0000FF);	    //���ж���
			break;
		case IMP:
			if(impCloseFlag == 1)
			{
				GetHighFreqRange(&TestPara, &leftVal, &rightVal);
				minFreq = pTestPara->lowFreq;
				impCloseFlag = 0;
			}
			temp = (pTestPara->init/amplificationFactor + 2.5)*13107.0;				//��ʼ��ѹ						 
			*(pmeasUartTxBuf+15)=(unsigned char)(temp & 0X00FF);
			*(pmeasUartTxBuf+14)=(unsigned char)((temp>>8) & 0X00FF);
			temp = (pTestPara->amplitude)*34133.0;											  //������ֵ
			*(pmeasUartTxBuf+17)=(unsigned char)(temp & 0X00FF);						
			*(pmeasUartTxBuf+16)=(unsigned char)((temp>>8) & 0X00FF);
			if(pointInFlag == 0)
			{
				val = GetDoblePointVal(leftVal, rightVal, pTestPara);								  //Ƶ��/Ƶ�� 
				fsin = rightVal;			 //fsin Ϊ�����ź�Ƶ�ʳ�ʼ��ֵ 
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
					pointInNumber = (pTestPara->points_001_01hz);		//����ѭ��������Ƶ���׺�Ƶ��β������
				else if(rightVal == 0.01) 			
					pointInNumber = (pTestPara->points_0001_001hz);		//����ѭ��������Ƶ���׺�Ƶ��β������
				else if(rightVal == 0.001) 			
					pointInNumber = (pTestPara->points_00001_0001hz);		//����ѭ��������Ƶ���׺�Ƶ��β������
				else			
					pointInNumber = (pTestPara->points_000001_00001hz);		//����ѭ��������Ƶ���׺�Ƶ��β������
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
			 if(fsin > 100)          //�����ź�Ƶ�ʴ���100HZ
			 {
				 timeStep  = 1/(fsin*10);								//����ʱ����
			 }else
			 {
				 timeStep  = 1/(fsin*10);
			 }
			 cnt = timeStep*1*10000000-1;
			*(pmeasUartTxBuf+13)=(unsigned char)(cnt & 0X000000FF);
			*(pmeasUartTxBuf+12)=(unsigned char)((cnt>>8) & 0X000000FF);
			*(pmeasUartTxBuf+11)=(unsigned char)((cnt>>16) & 0X000000FF); 
			*(pmeasUartTxBuf+10)=(unsigned char)((cnt>>24) & 0X000000FF);			                //����ʱ����
			 freq  = fsin/4578;
			 if(freq*4578/fsin < 1)
			 {
				 freq+=1;
			 }
			 cnt = freq*4578/fsin - 1;
			
			*(pmeasUartTxBuf+19)=(unsigned char)(freq & 0X0000FF);		 //Ƶ����freq ;��Χ��1-255
			*(pmeasUartTxBuf+18)=(unsigned char)((freq>>8) & 0X0000FF);	    
 
			*(pmeasUartTxBuf+24)=(unsigned char)(cnt       & 0X0000FF);
			*(pmeasUartTxBuf+23)=(unsigned char)((cnt>>8)  & 0X0000FF);	    
			*(pmeasUartTxBuf+22)=(unsigned char)((cnt>>16) & 0X0000FF);
			*(pmeasUartTxBuf+21)=(unsigned char)((cnt>>24) & 0X0000FF);	    
		
			*(pmeasUartTxBuf+26)=(unsigned char)((pTestPara->cycle_10_100hz) & 0X0000FF);
			*(pmeasUartTxBuf+25)=(unsigned char)(((pTestPara->cycle_10_100hz)>>8) & 0X0000FF);	      //����������
			break;
	 }	
	*(pmeasUartTxBuf+SA51_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA51_UART_TX_LEN-1);   //У��λ
}
//==================================================================================================================================   
static void PrepareCfgTxData2(TestParaTypeDef* pTestPara, unsigned char devAddr, unsigned char* pmeasUartTxBuf, enum TestMode expType)	  // Э��֡2
{
	*pmeasUartTxBuf=0xAA;
	*(pmeasUartTxBuf+1)=devAddr;     				                          //�豸��ַ
	*(pmeasUartTxBuf+2)=MSG_TYPE_SITTING_REGISTER2;				              //��������
	*(pmeasUartTxBuf+3)=0x03;                                                 //ʵ������
	*(pmeasUartTxBuf+4)=0x00;	                                              //����λ
	switch(expType)
	{
		case SV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X00;
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //����1���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //����2���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //�������ȡֵ��Χ��0.1ms��10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	       //����3���ȡֵ��Χ��1ms��50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
			break;
		case DPV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X01;
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //����1���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+6)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	  
			*(pmeasUartTxBuf+5)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //�������ȡֵ��Χ��0.1ms��10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			break;
		case NPV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X02;  
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //����1���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //����2���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //�������ȡֵ��Χ��0.1ms��10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	       //����3���ȡֵ��Χ��1ms��50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
		case DNPV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X02;
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //����1���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //����2���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //�������ȡֵ��Χ��0.1ms��10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth) - (pTestPara->pluseWidth2)) * 1000) & 0X0000FF));	       //����3���ȡֵ��Χ��1ms��50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth) - (pTestPara->pluseWidth2)) * 1000)>>8) & 0X0000FF));
			break;
		case SWV:
			*(pmeasUartTxBuf+18)=(unsigned char)0X03;
			*(pmeasUartTxBuf+6)=((int)((pTestPara->pluseWidth) * 1000) & 0X0000FF);	       //����1���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+5)=(((int)((pTestPara->pluseWidth) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+8)=((int)((pTestPara->pluseWidth2) * 1000) & 0X0000FF);	       //����2���ȡֵ��Χ��1ms��10s;
			*(pmeasUartTxBuf+7)=(((int)((pTestPara->pluseWidth2) * 1000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+11)=((int)((pTestPara->samplingWidth) * 10000) & 0X0000FF);	       //�������ȡֵ��Χ��0.1ms��10s;
			*(pmeasUartTxBuf+10)=(((int)((pTestPara->samplingWidth) * 10000)>>8) & 0X0000FF);
			*(pmeasUartTxBuf+9)=(((int)((pTestPara->samplingWidth) * 10000)>>16) & 0X0000FF); 
			*(pmeasUartTxBuf+13)=((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000) & 0X0000FF));	       //����3���ȡֵ��Χ��1ms��50s;
			*(pmeasUartTxBuf+12)=(((((int)((pTestPara->plusePeriod) - (pTestPara->pluseWidth)) * 1000)>>8) & 0X0000FF));
			*(pmeasUartTxBuf+17)=(unsigned char)((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000)) & 0X000000FF));	  //����4���ȡֵ��Χ����10us; 
			*(pmeasUartTxBuf+16)=(unsigned char)(((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000))>>8) & 0X000000FF));
			*(pmeasUartTxBuf+15)=(unsigned char)(((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000))>>16) & 0X000000FF)); 
			*(pmeasUartTxBuf+14)=(unsigned char)(((((int)(((1.0/(pTestPara->frequency))/2.0) * 1000000))>>24) & 0X000000FF));		
			break;
	}
	*(pmeasUartTxBuf+SA51_UART_TX_LEN-1)=GetXorCheckVal(pmeasUartTxBuf, SA51_UART_TX_LEN-1);   //У��λ  
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
			ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN); //��ָ�����п�(comSelect)���������д(SA51_UART_TX_LEN=33)�������ֽڵ���Ϣ;//������ȡ���Ĳ������ͳ�ȥ	
			break;
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV:				 //��5��ʵ�鶼������������33λ���ֽ������üĴ���
			PrepareCfgTxData(&TestPara, devAddr, pmeasUartTxBuf, expType); 
			ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN); //��ָ�����п�(comSelect)���������д(SA51_UART_TX_LEN=33)�������ֽڵ���Ϣ;//������ȡ���Ĳ������ͳ�ȥ	
			Delay(0.2);
			PrepareCfgTxData2(&TestPara, devAddr, pmeasUartTxBuf, expType); 
			ComWrt(comSelect, (const char*)pmeasUartTxBuf, SA51_UART_TX_LEN); //��ָ�����п�(comSelect)���������д(SA51_UART_TX_LEN=33)�������ֽڵ���Ϣ;//������ȡ���Ĳ������ͳ�ȥ	
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
void ProtocolRun(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)  //��ʼ�ɼ�
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
void ProtocolStop(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)  //ֹͣ�ɼ�
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
void ProtocolQuery(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf)  //ѭ����ѯ
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
		pRxData->rxResistance1 = 1;  //����Ϊ1ŷ
	    break;
		case 2:
		pRxData->rxResistance1 = 10;  //����Ϊ10ŷ
	    break;
		case 3:
		pRxData->rxResistance1 = 100;  //����Ϊ100ŷ
	    break;
		case 4:
		pRxData->rxResistance1 = 1000;  //����Ϊ1Kŷ
	    break;
		case 5:
		pRxData->rxResistance1 = 10000;  //����Ϊ10Kŷ
	    break;
		case 6:
		pRxData->rxResistance1 = 100000;  //����Ϊ100Kŷ
	    break;
		case 7:
		pRxData->rxResistance1 = 1000000;  //����Ϊ1Mŷ
	    break;
		case 8:
		pRxData->rxResistance1 = 10000000;  //����Ϊ10Mŷ
	    break;
		case 9:
		pRxData->rxResistance1 = 100000000;  //����Ϊ100Mŷ
	    break;
		case 10:
		pRxData->rxResistance1 = 1000000000;  //����Ϊ1Gŷ
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
//impʵ�鵥��һ���������ջ������ݵĺ���
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

