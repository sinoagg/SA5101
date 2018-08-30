//==============================================================================
//
// Title:		npvPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/28 at 9:31:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "npvPanel.h"
#include "npv Configuration.h"

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
int GetNpvCfg (int panelHandle)
{
	double temp;
	int temp1;
		
	if(GetCtrlVal(panelHandle,NPV_CFG_INITIAL,&temp) < 0)
	      return -1;
	NpvCfg.cfgNpv_Initial = temp;
	
	if(GetCtrlVal(panelHandle,NPV_CFG_FINAL,&temp) < 0)
	      return -1;
	NpvCfg.cfgNpv_Final = temp;
	
	if(GetCtrlVal(panelHandle,NPV_CFG_INCR,&temp) < 0)
	      return -1;
	NpvCfg.cfgNpv_Incr = temp;
	
	if(GetCtrlVal(panelHandle,NPV_CFG_PLUSE,&temp) < 0)
	      return -1;
	NpvCfg.cfgNpv_Pluse= temp;
	
	if(GetCtrlVal(panelHandle,NPV_CFG_SAMPLEWIDTH,&temp) < 0)
	      return -1;
	 NpvCfg.cfgNpv_PluseWdith = temp;
	
	if(GetCtrlVal(panelHandle,NPV_CFG_PLUSEWIDTH,&temp) < 0)
	      return -1;
	 NpvCfg.cfgNpv_PluseWdith = temp;
	
	if(GetCtrlVal(panelHandle,NPV_CFG_PLUSEPERIOD,&temp) < 0)
	      return -1;
	 NpvCfg.cfgNpv_PlusePeriods = temp;
	
	if(GetCtrlVal(panelHandle,NPV_CFG_QUIETTIME,&temp1) < 0)
	      return -1;
	NpvCfg.cfgNpv_QuietTime = temp1;
	if(GetCtrlVal(panelHandle,NPV_CFG_CURRETNRANGE,&temp1) < 0)
	      return -1;
	NpvCfg.cfgNpv_currentrange = temp1;

	return 0;
}

int CVICALLBACK NpvAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(npvAdvancePanel, 105, 1592);
			SetPanelSize(npvAdvancePanel, 500, 308);
			DisplayPanel(npvAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK NpvBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(npvBasicPanel, 105, 1592);
				SetPanelSize(npvBasicPanel, 500, 308);
				DisplayPanel(npvBasicPanel);
			break;
	}
	return 0;
}
