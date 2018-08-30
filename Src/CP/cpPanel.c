//==============================================================================
//
// Title:		cpPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/3 at 16:22:11 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <userint.h>
#include "cpPanel.h"

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

int CVICALLBACK CpAdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(cpAdvancePanel, 105, 1592);
			SetPanelSize(cpAdvancePanel, 500, 308);
			DisplayPanel(cpAdvancePanel);
			break;
	}
	return 0;
}

int CVICALLBACK CpBasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(cpBasicPanel, 105, 1592);
				SetPanelSize(cpBasicPanel, 500, 308);
				DisplayPanel(cpBasicPanel);
			break;
	}
	return 0;
}
