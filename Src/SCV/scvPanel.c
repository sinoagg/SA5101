//==============================================================================
//
// Title:		scvPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/26 at 15:43:40 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <utility.h>
#include "scvPanel.h"
#include "scv Configuration.h"

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

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetScvCfg (int panelHandle)
{
	double temp;
	int temp1;
		
	if(GetCtrlVal(panelHandle,SCV_CFG_INITIAL,&temp) < 0)
	      return -1;
	ScvCfg.cfgScv_Initial = temp;

	if(GetCtrlVal(panelHandle,SCV_CFG_FINAL,&temp) < 0)
	      return -1;
	ScvCfg.cfgScv_Final = temp;

	if(GetCtrlVal(panelHandle,SCV_CFG_INCR,&temp) < 0)
	      return -1;
	ScvCfg.cfgScv_Incr = temp;

	if(GetCtrlVal(panelHandle,SCV_CFG_STEPPERIODS,&temp) < 0)
	      return -1;
	ScvCfg.cfgScv_StepPeriods = temp;

	if(GetCtrlVal(panelHandle,SCV_CFG_SAMPLEWIDTH,&temp) < 0)
	      return -1;
	ScvCfg.cfgScv_SamplingWidth = temp;

	if(GetCtrlVal(panelHandle,SCV_CFG_QUIETTIME,&temp1) < 0)
	      return -1;
	ScvCfg.cfgScv_QuietTime = temp1;
	if(GetCtrlVal(panelHandle,SCV_CFG_CURRETNRANGE,&temp1) < 0)
	      return -1;
	ScvCfg.cfgScv_currentrange = temp1;
	return 0;
}

int CVICALLBACK ScvAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(scvAdvancePanel, 105, 1592);
			SetPanelSize(scvAdvancePanel, 500, 308);
			DisplayPanel(scvAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK ScvBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(scvBasicPanel, 105, 1592);
				SetPanelSize(scvBasicPanel, 500, 308);
				DisplayPanel(scvBasicPanel);
			break;
	}
	return 0;
}
