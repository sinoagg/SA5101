//==============================================================================
//
// Title:		SwvPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/10/30 at 9:41:49 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "SwvPanel.h"
#include "SWV.h"

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
   ExpPanelTypeDef SwvPanel={
	 0,
	 SWVPANEL_NUM_INIT,
	 SWVPANEL_NUM_STOP,
	 SWVPANEL_NUM_IPFLOAT,      //此参数没有使用
	 SWVPANEL_NUM_STEP, 
	 SWVPANEL_NUM_IPINT,      //此参数没有使用
	 SWVPANEL_NUM_IPINT,      //此参数没有使用
	 SWVPANEL_NUM_IPINT,      //此参数没有使用
	 SWVPANEL_NUM_SAMPLINGWIDTH,
	 SWVPANEL_NUM_IPFLOAT,  //此参数没有使用
	 SWVPANEL_NUM_IPFLOAT,  //此参数没有使用
	 SWVPANEL_NUM_IPFLOAT,  //此参数没有使用
	 SWVPANEL_NUM_AMPLITUDE,
	 SWVPANEL_NUM_FREQUENCY,
	};
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//int Define_Your_Functions_Here (int x)
//{
//	return x;
//}
