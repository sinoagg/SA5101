//==============================================================================
//
// Title:		lsvPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/19 at 11:48:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <utility.h>
#include "lsvPanel.h"
#include "lsv Configuration.h"

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
int GetLsvCfg (int panelHandle)
{
	double temp;
	int temp1;
	if(GetCtrlVal(panelHandle,LSV_CFG_INITIAL,&temp) < 0)
	 return -1;
	LsvCfg.cfgLsv_Initial = temp;
	if(GetCtrlVal(panelHandle,LSV_CFG_FINAL,&temp) < 0)
	 return -1;
	LsvCfg.cfgLsv_final = temp;
	if(GetCtrlVal(panelHandle,LSV_CFG_SCANRATE,&temp) < 0)
	 return -1;
	LsvCfg.cfgLsv_scanrate = temp;
	if(GetCtrlVal(panelHandle,LSV_CFG_SAMPLEINTERVAL,&temp) < 0)
	 return -1;
	LsvCfg.cfgLsv_sampleinterval = temp;
	if(GetCtrlVal(panelHandle,LSV_CFG_QUIETTIME,&temp) < 0)
	 return -1;
	LsvCfg.cfgLsv_quiettime = temp;
	if(GetCtrlVal(panelHandle,LSV_CFG_CURRETNRANGE,&temp1) < 0)
	 return -1;
	LsvCfg.cfgLsv_currentrange = temp1;

	return 0;
}

int CVICALLBACK LsvAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(lsvAdvancePanel, 105, 1592);
			SetPanelSize(lsvAdvancePanel, 500, 308);
			DisplayPanel(lsvAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK LsvBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(lsvBasicPanel, 105, 1592);
				SetPanelSize(lsvBasicPanel, 500, 308);
				DisplayPanel(lsvBasicPanel);
			break;
	}
	return 0;
}
