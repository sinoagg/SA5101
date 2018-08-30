#include <userint.h>
//==============================================================================
//
// Title:		i_tPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:01:00 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "i_tPanel.h"
#include "i_t Configuration.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
i_tCfg_TypeDef I_tCfg; 
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetI_tCfg (int panelHandle)
{
 int temp;
 if(GetCtrlVal(panelHandle,i_t_CFG_INITIAL,&temp) < 0)
	 return -1;
 I_tCfg.cfgI_t_initial = temp;
 if(GetCtrlVal(panelHandle,i_t_CFG_SAMPLEINTERVAL,&temp) < 0)
	 return -1;
 I_tCfg.cfgI_t_sampleinterval = temp;
 if(GetCtrlVal(panelHandle,i_t_CFG_RUNTIME,&temp) < 0)
	 return -1;
 I_tCfg.cfgI_t_runtime = temp;
 if(GetCtrlVal(panelHandle,i_t_CFG_QUIETTIME,&temp) < 0)
	 return -1;
 I_tCfg.cfgI_t_quiettime = temp;
 if(GetCtrlVal(panelHandle,i_t_CFG_CURRENTRANGE,&temp) < 0)
	 return -1;
 I_tCfg.cfgI_t_currentrange = temp;
 
 return 0;
}




