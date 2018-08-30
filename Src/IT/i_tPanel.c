#include "c_v Configuration.h"

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
#include <utility.h>
#include <userint.h>
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
	double temp;
	int temp1;

	if(GetCtrlVal(panelHandle,I_T_CFG_INITIAL,&temp) < 0)
	 return -1;
	if(temp > 12)
	{
	   MessagePopup("Warning","The max initial voltage is 12v");
	   temp = 12;
	   SetCtrlAttribute (panelHandle,I_T_CFG_INITIAL,ATTR_CTRL_VAL,temp);
	   I_tCfg.cfgI_t_initial = temp;
	}
	else
	{
	    I_tCfg.cfgI_t_initial = temp; 	
	}
	if(GetCtrlVal(panelHandle,I_T_CFG_SAMPLEINTERVAL,&temp) < 0)
	 return -1;
	if(temp <= 1200)
	{
	 I_tCfg.cfgI_t_sampleinterval = temp;
	}
	else
	{
	  MessagePopup("Warning","The max SampleInterval is 20 minute");
	  temp = 1200;
	  SetCtrlAttribute (panelHandle,I_T_CFG_SAMPLEINTERVAL,ATTR_CTRL_VAL,temp);
	  I_tCfg.cfgI_t_sampleinterval = temp;
	}
	if(GetCtrlVal(panelHandle,I_T_CFG_RUNTIME,&temp) < 0)
	 return -1;
	I_tCfg.cfgI_t_runtime = temp;
	if(GetCtrlVal(panelHandle,I_T_CFG_QUIETTIME,&temp1) < 0)
	 return -1;
	I_tCfg.cfgI_t_quiettime = temp1;
	if(GetCtrlVal(panelHandle,I_T_CFG_CURRENTRANGE,&temp1) < 0)
	 return -1;
	I_tCfg.cfgI_t_currentrange = temp1;

	return 0;
}

int CVICALLBACK ItAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(itAdvancePanel, 105, 1592);
			SetPanelSize(itAdvancePanel, 500, 308);
			DisplayPanel(itAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK ItBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(itBasicPanel, 105, 1592);
				SetPanelSize(itBasicPanel, 500, 308);
				DisplayPanel(itBasicPanel);
			break;
	}
	return 0;
}
