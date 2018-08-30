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
	double cfgI_t_initial;              //初始化直流电压数值
	double cfgI_t_sampleinterval;      //采样间隔数值
	double cfgI_t_runtime;            //运行时间数值  
	double cfgI_t_quiettime;  		 //静止时间数值
	  int  cfgI_t_currentrange;     //电流量程，分多个档位，当为0表示AUTO模式
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
