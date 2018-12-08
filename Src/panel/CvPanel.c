//==============================================================================
//
// Title:		CvPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/10/24 at 17:40:29 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "CvPanel.h"
#include "C-V.h"

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
   ExpPanelTypeDef CvPanel={
	 0,
	 CVPANEL_NUM_INIT,
	 CVPANEL_NUM_STOP,
	 CVPANEL_NUM_START,
	 CVPANEL_NUM_STEP, 
	 CVPANEL_NUM_SWEEPSEGMENTS,
	 CVPANEL_NUM_SCANPOLARITY,
	 CVPANEL_NUM_IPINT,        //此参数不使用 
	};
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
