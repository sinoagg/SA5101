//==============================================================================
//
// Title:		TafelPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/10/24 at 17:41:57 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "TafelPanel.h"
#include "TAFEL.h"

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
   ExpPanelTypeDef TafelPanel={
	 0,
	 TAFELPANEL_NUM_INIT,
	 TAFELPANEL_NUM_STOP,
	 TAFELPANEL_NUM_IPFLOAT,                   //此参数不使用
	 TAFELPANEL_NUM_STEP,
	 TAFELPANEL_NUM_SWEEPSEGMENTS,
	 TAFELPANEL_NUM_IPINT,                //此参数不使用
	 TAFELPANEL_NUM_HOLDTIME,
	};
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
