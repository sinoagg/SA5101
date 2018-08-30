//==============================================================================
//
// Title:		scvPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/26 at 15:43:40 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __scvPanel_H__
#define __scvPanel_H__

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
	double cfgScv_Initial; //起始电压
	double cfgScv_Final;   //结束电压
	double cfgScv_Incr;   //电位增量
	double cfgScv_StepPeriods; //步进周期
	double cfgScv_SamplingWidth; //采样宽度
	int cfgScv_QuietTime;     //静止时间
	int cfgScv_currentrange;  //量程
}scvCfg_TypeDef;
//==============================================================================
// External variables
extern int scvBasicPanel;
extern int scvAdvancePanel;

scvCfg_TypeDef ScvCfg; 
//==============================================================================
// Global functions
int GetScvCfg (int panelHandle);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __scvPanel_H__ */
