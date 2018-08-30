//==============================================================================
//
// Title:		npvPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/28 at 9:31:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __npvPanel_H__
#define __npvPanel_H__

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
	double cfgNpv_Initial; //起始电压
	double cfgNpv_Final;   //结束电压
	double cfgNpv_Incr;   //电位增量
	double cfgNpv_Pluse;  //脉冲电压
	double cfgNpv_SamplingWidth; //采样宽度
	double cfgNpv_PluseWdith;//脉冲宽度
	double cfgNpv_PlusePeriods;//脉冲周期
	int cfgNpv_QuietTime;     //静止时间
	int cfgNpv_currentrange;  //量程
}npvCfg_TypeDef;
//==============================================================================
// External variables
 npvCfg_TypeDef NpvCfg;
 extern int npvBasicPanel;
 extern int npvAdvancePanel;
//==============================================================================
// Global functions
int GetNpvCfg (int panelHandle);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __npvPanel_H__ */
