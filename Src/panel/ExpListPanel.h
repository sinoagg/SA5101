//==============================================================================
//
// Title:		ExperimentList.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/11 at 9:55:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __ExperimentList_H__
#define __ExperimentList_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int panelHandle;								 //面板ID
	int InitID;									     //起始电压ID 
	int StopID;									     //结束电压ID 
	int StartID;									 //初始电压ID     
	int VoltageStepID;   							 //电压增量ID 
	int SweepSegmentsID;							 //扫描段数 ID   
	int PosOrNegID;									 //扫描方向ID 
	int HoldTimeID;                                  //只有TAFEL使用ID 
	int SamplingWidthID;							 //采样宽度ID 
	int PulseWidthID;								 //脉冲1宽度 ID 
	int PulsePeriodID;                               //脉冲周期ID   
	int PulseWidth2ID;								 //脉冲2宽度ID 
	int AmplitudeID;                                   //幅值ID 
	int FrequencyID;                                   //频率ID 
	int HighFreqID;                                    //高频率范围
	int LowFreqID;                                      //低频率范围
	int PointsID_100k_1Mhz;
	int PointsID_10k_100Khz; 
	int PointsID_1k_10Khz; 
	int PointsID_100_1Khz; 
	int PointsID_10_100hz; 
	int PointsID_1_10hz; 
	int PointsID_01_1hz; 
	int PointsID_001_01hz; 
	int PointsID_0001_001hz; 
	int PointsID_00001_0001hz; 
	int PointsID_000001_00001hz; 
	int CycleID_100k_1Mhz;
	int CycleID_10k_100Khz; 
	int CycleID_1k_10Khz; 
	int CycleID_100_1Khz; 
	int CycleID_10_100hz; 
	int CycleID_1_10hz; 
	int CycleID_01_1hz; 
	int CycleID_001_01hz; 
	int CycleID_0001_001hz; 
	int CycleID_00001_0001hz; 
	int CycleID_000001_00001hz;
	int DrawingTypeID;
}ExpPanelTypeDef;
//==============================================================================
// External variables
extern int hMainPanel;
extern int hExpListPanel;
extern int hEnvironmentPanel;
extern int hBasicSamplePanel;
extern int hIT_Panel;
extern int hCV_Panel;
extern int hLSV_Panel;
extern int hTAFEL_Panel;
extern int hResultDispPanel;
extern int hSV_Panel;
extern int hNPV_Panel;
extern int hDPV_Panel;
extern int hDNPV_Panel;
extern int hSWV_Panel;
extern int hIMP_Panel;
extern int hTwoTerminalPanel;
//==============================================================================
// Global functions
int Declare_Your_Functions_Here (int x);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __ExperimentList_H__ */
