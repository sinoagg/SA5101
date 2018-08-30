//==============================================================================
//
// Title:		i_tPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/16 at 16:44:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __i_tPanel_H__
#define __i_tPanel_H__

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
	double cfgI_t_initial;              //��ʼ��ֱ����ѹ��ֵ
	double cfgI_t_sampleinterval;      //���������ֵ
	double cfgI_t_runtime;            //����ʱ����ֵ  
	double cfgI_t_quiettime;  		 //��ֹʱ����ֵ
	  int  cfgI_t_currentrange;     //�������̣��ֶ����λ����Ϊ0��ʾAUTOģʽ
  }i_tCfg_TypeDef;
//==============================================================================
// External variables
extern int itBasicPanel;
extern int itAdvancePanel; 
//==============================================================================
// Global functions
int GetI_tCfg (int panelHandle);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __i_tPanel_H__ */
