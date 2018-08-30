//==============================================================================
//
// Title:		c_vPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/17 at 16:42:32 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __c_vPanel_H__
#define __c_vPanel_H__

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
	double cfgC_v_initial;              //��ʼ��ֱ����ѹ��ֵ
	double cfgC_v_high; 
	double cfgC_v_final;              
	double cfgC_v_low;   
	double cfgC_v_sampleinterval;      //���������ֵ
	double cfgC_v_scanrate;   
	double cfgC_v_sweepsegments;    //�ָΧ
	double cfgG_v_quiettime;        
	  int  cvgC_v_intialscanpolarity; //��ʼɨ�輫��
	  int  cfgC_v_currentrange;     //�������̣��ֶ����λ����Ϊ0��ʾAUTOģʽ
  }c_v_Cfg_TypeDef;
//==============================================================================
// External variables
extern int cvBasicPanel;
extern int cvAdvancePanel;
//==============================================================================
// Global functions
int GetC_vBasicCfg (int panelHandle);
int GetC_vAdvanceCfg (int panelHandle);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __c_vPanel_H__ */
