//==============================================================================
//
// Title:		swvPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/8/2 at 14:28:36 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __swvPanel_H__
#define __swvPanel_H__

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
	double cfgLsv_initial;              //初始化直流电压数值
	double cfgLsv_final;
	double cfgLsv_incr;              //电位增量
	double cfgLsv_amplitude;
	double cfgLsv_samplingWidth;    //采样宽度
	double cfgLsv_Frequency;        
	  int  cfgG_v_quiettime;        
	  int  cfgC_v_currentrange;     //电流量程，分多个档位，当为0表示AUTO模式
}lsv_Cfg_TypeDef;

//==============================================================================
// External variables
extern int swvBasicPanel;
extern int swvAdvancePanel;
lsv_Cfg_TypeDef SwvCfg; 
//==============================================================================
// Global functions
int GetSwvCfg (int panelHandle);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __swvPanel_H__ */
