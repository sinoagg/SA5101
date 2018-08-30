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
	double cfgC_v_initial;              //初始化直流电压数值
	double cfgC_v_high; 
	double cfgC_v_final;              
	double cfgC_v_low;   
	double cfgC_v_sampleinterval;      //采样间隔数值
	double cfgC_v_scanrate;   
	double cfgC_v_sweepsegments;    //分割范围
	double cfgG_v_quiettime;        
	  int  cvgC_v_intialscanpolarity; //开始扫描极性
	  int  cfgC_v_currentrange;     //电流量程，分多个档位，当为0表示AUTO模式
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
