//==============================================================================
//
// Title:		ocptPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/3 at 16:32:37 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <userint.h>
#include "ocptPanel.h"

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
int CVICALLBACK OcptAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(ocptAdvancePanel, 105, 1592);
			SetPanelSize(ocptAdvancePanel, 500, 308);
			DisplayPanel(ocptAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK OcptBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(ocptBasicPanel, 105, 1592);
				SetPanelSize(ocptBasicPanel, 500, 308);
				DisplayPanel(ocptBasicPanel);
			break;
	}
	return 0;
}
