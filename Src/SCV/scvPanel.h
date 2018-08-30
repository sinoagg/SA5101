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
	double cfgScv_Initial; //��ʼ��ѹ
	double cfgScv_Final;   //������ѹ
	double cfgScv_Incr;   //��λ����
	double cfgScv_StepPeriods; //��������
	double cfgScv_SamplingWidth; //�������
	int cfgScv_QuietTime;     //��ֹʱ��
	int cfgScv_currentrange;  //����
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
