//==============================================================================
//
// Title:		MainPanel.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MainPanel_H__
#define __MainPanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef INCLUDE_AFTER_WINDOWS_H

#include "AbnormalDataCache.h"

#define INCLUDE_AFTER_WINDOWS_H
#endif		
//==============================================================================
// Include files
#include <utility.h> 
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "MainPanel.h" 
#include "cvidef.h"
#include "ExpListPanel.h"
#include "Graph.h"
#include "Load_Panel.h"
#include "Timer.h"
#include "TablePanel.h"
#include "asynctmr.h"
#include "File.h"
#include "SettingsPanel.h"
		
#include "i_tPanel.h"
#include "i_tProtocol.h" 
#include "c_vPanel.h"
#include "c_vProtocol.h"
#include "lsvPanel.h"
#include "lsvProtocol.h"
#include "scvPanel.h"
#include "scvProtocol.h"
#include "npvPanel.h"
#include "npvProtocol.h"
//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int hSinglePrjPanel;				//加载后每个项目的panel句柄
	int index;							//自定义的目录，决定了位置和显示
}PrjHandleTypeDef;
//==============================================================================
// External variables
extern FileLableTypeDef *pFileLable[];
extern PrjHandleTypeDef SingleProject[];
//==============================================================================
// Global functions
static void InitSingleProject(PrjHandleTypeDef *pSingleProject);
static int SaveConfigToFile(char* pConfigSavePath);
static int SaveAllPanelState(char* pConfigSavePath);
static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char index);
static int LoadAllProject(char* pProjectSavePath);


#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MainPanel_H__ */
