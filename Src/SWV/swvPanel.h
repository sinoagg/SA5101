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
	double cfgLsv_initial;              //��ʼ��ֱ����ѹ��ֵ
	double cfgLsv_final;
	double cfgLsv_incr;              //��λ����
	double cfgLsv_amplitude;
	double cfgLsv_samplingWidth;    //�������
	double cfgLsv_Frequency;        
	  int  cfgG_v_quiettime;        
	  int  cfgC_v_currentrange;     //�������̣��ֶ����λ����Ϊ0��ʾAUTOģʽ
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
