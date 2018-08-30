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
#include "c_vPanel.h"
#include "c_v Configuration.h"
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
c_v_Cfg_TypeDef CvCfg; 
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GetC_vBasicCfg (int panelHandle)
{
	double temp;
	int temp1;

	if(GetCtrlVal(panelHandle,C_V_CFG_INITIAL,&temp) < 0)
	 return -1;
	CvCfg.cfgC_v_initial = temp;
	if(GetCtrlVal(panelHandle,C_V_CFG_HIGH,&temp) < 0)
	 return -1;
	CvCfg.cfgC_v_high = temp;
	if(GetCtrlVal(panelHandle,C_V_CFG_LOW,&temp) < 0)
	 return -1;
	CvCfg.cfgC_v_low = temp;
	if(GetCtrlVal(panelHandle,C_V_CFG_FINAL,&temp) < 0)
	 return -1;
	CvCfg.cfgC_v_final = temp;
	if(GetCtrlVal(panelHandle,C_V_CFG_SCANRATE,&temp) < 0)
	 return -1;
	CvCfg.cfgC_v_scanrate = temp;
	if(GetCtrlVal(panelHandle,C_V_CFG_SAMPLEINTERVAL,&temp) < 0)
	 return -1;
	CvCfg.cfgC_v_sampleinterval = temp;
	if(GetCtrlVal(panelHandle,C_V_CFG_CURRETNRANGE,&temp1) < 0)
	 return -1;
	CvCfg.cfgC_v_currentrange = temp1;
	if(GetCtrlVal(panelHandle,C_V_CFG_QUIETTIME,&temp) < 0)
	 return -1;
	CvCfg.cfgG_v_quiettime = temp;
	if(GetCtrlVal(panelHandle,C_V_CFG_SWEEPSEGMENTS,&temp1) < 0)
	 return -1;
	CvCfg.cfgC_v_sweepsegments = temp1;
	return 0;
}

int GetC_vAdvanceCfg (int panelHandle) 
{
	int temp1;
	if(GetCtrlVal(panelHandle,C_V_ADV_INTIALSCANPOLARITY,&temp1) < 0)
	   return -1;
	CvCfg.cvgC_v_intialscanpolarity = temp1;
	return 0;
}

int CVICALLBACK CvAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(cvAdvancePanel, 105, 1592);
			SetPanelSize(cvAdvancePanel, 500, 308);
			DisplayPanel(cvAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK CvBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(cvBasicPanel, 105, 1592);
				SetPanelSize(cvBasicPanel, 500, 308);
				DisplayPanel(cvBasicPanel);
			break;
	}
	return 0;
}





