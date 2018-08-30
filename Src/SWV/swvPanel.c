//==============================================================================
//
// Title:		swvPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/2 at 14:28:36 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <utility.h>
#include "swvPanel.h"
#include "swv Configuration.h"
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
int GetSwvCfg (int panelHandle)
{
	double temp;
	int temp1;
		
	if(GetCtrlVal(panelHandle,SWV_CFG_INITIAL,&temp) < 0)
	      return -1;
	SwvCfg.cfgLsv_initial = temp;
	if(GetCtrlVal(panelHandle,SWV_CFG_FINAL,&temp) < 0)
	      return -1;
	SwvCfg.cfgLsv_final = temp;
	if(GetCtrlVal(panelHandle,SWV_CFG_INCR,&temp) < 0)
	      return -1;
	SwvCfg.cfgLsv_incr = temp;
	if(GetCtrlVal(panelHandle,SWV_CFG_AMPLITUDE,&temp) < 0)
	      return -1;
	SwvCfg.cfgLsv_amplitude = temp;
	if(GetCtrlVal(panelHandle,SWV_CFG_SAMPLEWIDTH,&temp) < 0)
	      return -1;
	SwvCfg.cfgLsv_samplingWidth = temp;
	if(GetCtrlVal(panelHandle,SWV_CFG_FREQUENCY,&temp) < 0)
	      return -1;
	SwvCfg.cfgLsv_Frequency = temp;
	if(GetCtrlVal(panelHandle,SWV_CFG_QUIETTIME,&temp1) < 0)
	      return -1;
    SwvCfg.cfgG_v_quiettime = temp1;
	if(GetCtrlVal(panelHandle,SWV_CFG_CURRETNRANGE,&temp1) < 0)
	      return -1;
	SwvCfg.cfgC_v_currentrange = temp1;
	return 0;
}

int CVICALLBACK SwvAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(swvAdvancePanel, 105, 1592);
			SetPanelSize(swvAdvancePanel, 500, 308);
			DisplayPanel(swvAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK SwvBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(swvBasicPanel, 105, 1592);
				SetPanelSize(swvBasicPanel, 500, 308);
				DisplayPanel(swvBasicPanel);
			break;
	}
	return 0;
}
