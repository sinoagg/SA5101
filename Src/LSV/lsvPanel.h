//==============================================================================
//
// Title:		lsvPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/19 at 11:48:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __lsvPanel_H__
#define __lsvPanel_H__

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
	double cfgLsv_Initial;
	double cfgLsv_final;
	double cfgLsv_scanrate;
	double cfgLsv_sampleinterval;
	double cfgLsv_quiettime;
	int cfgLsv_currentrange;
}lsvCfg_TypeDef;
//==============================================================================
// External variables
lsvCfg_TypeDef LsvCfg; 
extern int lsvBasicPanel;
extern int lsvAdvancePanel;
//==============================================================================
// Global functions
int GetLsvCfg (int panelHandle);
int InitialLsvCfg(int panelHandle);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __lsvPanel_H__ */
