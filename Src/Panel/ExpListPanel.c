//==============================================================================
//
// Title:		ExperimentList.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/11 at 9:55:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <userint.h>
#include "Experiment List.h"
#include "ExpListPanel.h"

#include "scvPanel.h"
#include "lsvPanel.h"
#include "c_vPanel.h"
#include "npvPanel.h"
#include "i_tPanel.h"
#include "swvPanel.h"

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
int CVICALLBACK ExpListCallBack (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	
	int ExpSelVal;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, control, &ExpSelVal);
			if(ExpSelVal == 1)
			{
				SetPanelPos(cvBasicPanel, 105, 1592);
				SetPanelSize(cvBasicPanel, 500, 308);
				DisplayPanel(cvBasicPanel);
			}
			else if(ExpSelVal == 2)
			{
				SetPanelPos(lsvBasicPanel, 105, 1592);
				SetPanelSize(lsvBasicPanel, 500, 308);
				DisplayPanel(lsvBasicPanel);
			}
			else if(ExpSelVal == 3)
			{
				SetPanelPos(scvBasicPanel, 105, 1592);
				SetPanelSize(scvBasicPanel, 500, 308);
				DisplayPanel(scvBasicPanel);
			}
			else if(ExpSelVal==7)
			{
			    SetPanelPos(cpBasicPanel, 105, 1592);
				SetPanelSize(cpBasicPanel, 500, 308);
				DisplayPanel(cpBasicPanel);
			}
			else if(ExpSelVal==9)
			{
			    SetPanelPos(npvBasicPanel, 105, 1592);
				SetPanelSize(npvBasicPanel, 500, 308);
				DisplayPanel(npvBasicPanel);
			}
			else if(ExpSelVal==11)
			{
				SetPanelPos(swvBasicPanel, 105, 1592);
				SetPanelSize(swvBasicPanel, 500, 308);
				DisplayPanel(swvBasicPanel);
			}
			else if(ExpSelVal==12)
			{
				SetPanelPos(itBasicPanel, 105, 1592);
				SetPanelSize(itBasicPanel, 500, 308);
				DisplayPanel(itBasicPanel);
			}
			else if(ExpSelVal==13)
			{
				SetPanelPos(ocptBasicPanel, 105, 1592);
				SetPanelSize(ocptBasicPanel, 500, 308);
				DisplayPanel(ocptBasicPanel);
			}
			break;
	}
	return 0;
}
