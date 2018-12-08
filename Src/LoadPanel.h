//==============================================================================
//
// Title:		LoadPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 15:21:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __LoadPanel_H__
#define __LoadPanel_H__

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
#include "ResultMenuPanel.h"
#include "Table.h"
#include "Settings.h"
#include "ProjectPanel.h"
#include "system_ini.h"
#include "MainPanelCb.h"
#include "MainPanel.h"  
#include "Terminal.h"
#include "Sample Configuration.h"
#include "I-T.h"
#include "SV.h"
#include "DNPV.h"
#include "DPV.h"
#include "NPV.h"
#include "SWV.h"
		
#include "ItPanel.h"
#include "CvPanel.h"
#include "LsvPanel.h"
#include "TafelPanel.h"
#include "SvPanel.h"
#include "NpvPanel.h"
#include "DpvPanel.h"
#include "DnpvPanel.h"
#include "SwvPanel.h"
#include "ImpPanel.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// global variables
int hMainPanel;
int hExpListPanel;
int hResultMenuPanel;
int hSaveDataPanel; 
int hGraphDispPanel;
int hEnvironmentPanel;
int hResultDispPanel;
int hTablePanel;
int hGraphSelectPanel;
int hPrjPanel;
int hSettingsPanel;
int hPrjListPanel;
int hSettingsPrjPanel;
int hSettingsAboutPanel;
int hSettingsGraphPanel;
int hTwoTerminalPanel;
int hEnvCfgPanel;

int hBasicSamplePanel;
int hAdvanceSamplePanel;
int hIT_Panel;
int hCV_Panel;
int hLSV_Panel;
int hTAFEL_Panel;
int hSV_Panel;
int hNPV_Panel;
int hDPV_Panel;
int hDNPV_Panel;
int hSWV_Panel;
int hIMP_Panel;




//==============================================================================
// Global functions
int LoadInitPanel (void);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Load_Panel_H__ */
