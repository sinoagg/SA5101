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
	double cfgNpv_Initial; //��ʼ��ѹ
	double cfgNpv_Final;   //������ѹ
	double cfgNpv_Incr;   //��λ����
	double cfgNpv_Pluse;  //�����ѹ
	double cfgNpv_SamplingWidth; //�������
	double cfgNpv_PluseWdith;//������
	double cfgNpv_PlusePeriods;//��������
	int cfgNpv_QuietTime;     //��ֹʱ��
	int cfgNpv_currentrange;  //����
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
