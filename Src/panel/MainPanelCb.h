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
//==============================================================================
// Include files
#include "AbnormalDataCache.h" 
#include <utility.h> 
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "MainPanel.h" 
#include "cvidef.h"
#include "ExpListPanel.h"
#include "Graph.h"
#include "LoadPanel.h"
#include "TablePanel.h"
#include "asynctmr.h"
#include "File.h"
#include "SettingsPanel.h"
#include "ResultDispPanel.h"
#include "Protocol.h"
#include "Timer.h"
#include "main.h"
#include "TablePanel.h" 
//==============================================================================
// Constants
unsigned char measureComPort;
unsigned char controlComPort;
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
extern unsigned char measUartTxBuf[SA51_UART_TX_LEN];  
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
