//==============================================================================
//
// Title:		Protocol.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/9 at 9:58:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================
#ifndef __Protocol_H__
#define __Protocol_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files
#include "cvidef.h"
#include "ExpListPanel.h"  

//==============================================================================
// Constants
		
//==============================================================================
// Types
enum TestCmd
{	
	CMD_REPORT_ID=0x20,
	CMD_SETTING_REGISTER1=0x30,   //���üĴ���1
	CMD_SETTING_REGISTER2=0x31,   //���üĴ���2
	CMD_SETTING_REGISTER3=0x32,   //���üĴ���3
	CMD_SETTING_REGISTER4=0x33,   //���üĴ���4
	CMD_SETTING_REGISTER5=0x34,   //���üĴ���5
	CMD_SETTING_REGISTER6=0x35,   //���üĴ���6
	CMD_START=0x40,
	CMD_STOP=0x50,
	CMD_QUERY=0x60
};		

typedef union										//float union
{
	unsigned char num_uchar[4]; 
	float num_float;
}Float_Union_Data;

enum TestMode
{
	IT=1,
	LSV=2,
	CV=3,
	TAFEL=4, 
	SV=5,
	NPV=6,
	DPV=7,
	DNPV=8,
	SWV=9,
	IMP=10,
};

enum OutputModeType
{
	VOL_BIAS=0,
	VOL_SWEEP=1,
	VOL_STEP=2
};

typedef struct
{
	unsigned char devAddr;					//�豸��ַ
	enum TestCmd testCmd;					//��������
	enum TestMode testMode;					//����ģʽ
	float init;                               //��ʼ��ѹ
	float start;								//��ʼ��ѹ����͵�ѹ��
	float stop;								//������ѹ����ߵ�ѹ��
	int sweepSegments;                       //ɨ�����
    float voltageStep;  
	int posOrNeg;							 //ɨ�跽��
    int holdTime;                            //��TAFEL
	float sampleRate;                             //ɨ������        
	float timeStep;								   //�������			IT \ LSV \ CV \ 

	float samplingWidth;                               //�������
	float pluseWidth;                                  //������
	float plusePeriod;                                 //��������
	float pluseWidth2;                                 //������
	float amplitude;                                   //������
	float frequency;                                   //Ƶ��
	float highFreq;                                    //��Ƶ��
	float lowFreq;                                     //��Ƶ��
	unsigned char points_100k_1Mhz;
	unsigned char points_10k_100Khz;
	unsigned char points_1k_10Khz;
	unsigned char points_100_1Khz;
	unsigned char points_10_100hz;
	unsigned char points_1_10hz;
	unsigned char points_01_1hz;
	unsigned char points_001_01hz;
	unsigned char points_0001_001hz;
	unsigned char points_00001_0001hz;
	unsigned char points_000001_00001hz;
	unsigned char cycle_100k_1Mhz;
	unsigned char cycle_10k_100Khz;
	unsigned char cycle_1k_10Khz;
	unsigned char cycle_100_1Khz;
	unsigned char cycle_10_100hz;
	unsigned char cycle_1_10hz;
	unsigned char cycle_01_1hz;
	unsigned char cycle_001_01hz;
	unsigned char cycle_0001_001hz;
	unsigned char cycle_00001_0001hz;
	unsigned char cycle_000001_00001hz;
	unsigned char impDrawingType; 

	unsigned int quietTime;								   //��Ĭʱ��		   IT \ LSV \ CV \ TAFEL
	unsigned char rangeMode;							  //��λ�任				   IT \ LSV \ CV \ TAFEL
	unsigned int sampleNumber;							 //������				  IT \ LSV \ CV \ TAFEL          
	unsigned char maxRange;
	unsigned char minRange;
	unsigned long runTime;		
}TestParaTypeDef;  //��ȡ��ֵ

typedef struct
{
	unsigned char rxDevAddr;						//received Device Address
	int rxVdtest;									//voltage drain undertest
	int rxResistance;
	float rxVoltage;
	int rxResistance1;
    float rxVoltage1;
	unsigned char dataFlag;                        //���ؽ����迹���ݱ�־λ
	int channel2Data;                  //ͨ��2����
	int channel1Data;				  //ͨ��1���� 
}RxDataTypeDef;

typedef struct {
	double real;
	double imaginary;
} ComplexNums;

//==============================================================================
// External variables
extern TestParaTypeDef TestPara;
extern unsigned char pointInFlag; //Ƶ����֮���ѭ����־λ
extern float leftVal;
extern float rightVal;
extern float fsin;
//==============================================================================
// Global functions
void ProtocolCfg(unsigned char comSelect, unsigned char devAddr, enum TestMode expType, unsigned char* pmeasUartTxBuf);
void ProtocolRun(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf); 
void ProtocolStop(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf);
void ProtocolQuery(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf);
void ProtocolCalibrate(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf, unsigned char caliType, unsigned char caliRange);
void ProtocolGetData(unsigned char* pmeasUartRxBuf, RxDataTypeDef* pRxData);
void ProtocolCfgTxData(unsigned char comSelect, unsigned char devAddr, unsigned char* pmeasUartTxBuf, enum TestMode expType);  
void ProtocolGetImpData(unsigned char* pmeasUartRxBuf, RxDataTypeDef* pRxData);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Protocol_H__ */
