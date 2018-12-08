//==============================================================================
//
// Title:		NpvPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/10/30 at 9:34:42 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "NpvPanel.h"
#include "NPV.h"
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
   ExpPanelTypeDef NpvPanel={
	 0,
	 NPVPANEL_NUM_INIT,
	 NPVPANEL_NUM_STOP,
	 NPVPANEL_NUM_IPFLOAT,   //次参数不可用
	 NPVPANEL_NUM_STEP,
	 NPVPANEL_NUM_IPINT,   //次参数不可用
	 NPVPANEL_NUM_IPINT,   //次参数不可用
	 NPVPANEL_NUM_IPINT,   //次参数不可用
	 NPVPANEL_NUM_SAMPLINGWIDTH,
	 NPVPANEL_NUM_PULSEWIDTH,
	 NPVPANEL_NUM_PULSEPERIOD,
	 NPVPANEL_NUM_IPFLOAT, //次参数不可用
	 NPVPANEL_NUM_IPFLOAT, //次参数不可用
	};
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int Define_Your_Functions_Here (int x)
{
	return x;
}
