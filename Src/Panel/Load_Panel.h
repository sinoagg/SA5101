//==============================================================================
//
// Title:		LoadPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 15:21:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Load_Panel_H__
#define __Load_Panel_H__

#ifdef __cplusplus
    extern "C" {
#endif
//==============================================================================
// Include files
#include <userint.h>
#include "cvidef.h"
#include "AbnormalDataCache.h"
#include "MainPanel.h"
#include "Experiment List.h"
#include "GraphDisp.h"
#include "Environment.h"
#include "Result Menu.h"
#include "Table.h"
#include "User Manage.h"
#include "Settings.h"
#include "ProjectPanel.h"
#include "system_ini.h"
#include "MainPanelCb.h"
#include "MainPanel.h"  
		
#include "i_t Configuration.h"
#include "c_v Configuration.h"
#include "lsv Configuration.h"
#include "cp Configuration.h"
#include "ocpt Configuration.h"
#include "scv Configuration.h"
#include "npv Configuration.h"
#include "swv Configuration.h"
	
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// global variables
int mainPanel;
int expListPanel;
int samplePanel;
int graphDispPanel;
int environmentPanel;
int userManagePanel;
int resultPanel;
int tablePanel;
int saveDataPanel;
int graphSelectPanel;
int prjPanel;
int settingsPanel;
int prjListPanel;
int settingsPrjPanel;
int settingsPrjPanel;
int settingsAboutPanel;
int settingsGraphPanel;


int itBasicPanel;
int itAdvancePanel;
int cvBasicPanel;
int cvAdvancePanel;
int lsvBasicPanel;
int lsvAdvancePanel;
int cpBasicPanel;
int cpAdvancePanel;
int ocptBasicPanel;
int ocptAdvancePanel;
int scvBasicPanel;
int scvAdvancePanel;
int npvBasicPanel;
int npvAdvancePanel;
int swvBasicPanel;
int swvAdvancePanel;



//==============================================================================
// Global functions

int LoadInitPanel (void);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Load_Panel_H__ */
