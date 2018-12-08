//==============================================================================
//
// Title:		ImpPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/11/15 at 9:57:39 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "ImpPanel.h"
#include "IMP.h"
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
 ExpPanelTypeDef ImpPanel={
	0,
	IMPPANEL_NUM_INIT,
	IMPPANEL_NUM_IPFLOAT,//此数据不用
	IMPPANEL_NUM_IPFLOAT,//此数据不用
	IMPPANEL_NUM_IPFLOAT,//此数据不用
	IMPPANEL_NUM_IPINT, //此数据不用
	IMPPANEL_NUM_IPINT,//此数据不用
	IMPPANEL_NUM_IPINT,//此数据不用
	IMPPANEL_NUM_IPFLOAT,//此数据不用 
	IMPPANEL_NUM_IPFLOAT,//此数据不用
	IMPPANEL_NUM_IPFLOAT,//此数据不用 
	IMPPANEL_NUM_IPFLOAT,//此数据不用
	IMPPANEL_NUM_AMPLITUDE,
	IMPPANEL_NUM_IPFLOAT,//此数据不用
	IMPPANEL_NUM_HIGHFREQ,
	IMPPANEL_NUM_LOWFREQ,
	IMPPANEL_100K_1MHZ_POINT,
	IMPPANEL_10K_100KHZ_POINT,
	IMPPANEL_1K_10KHZ_POINT, 
	IMPPANEL_100_1KHZ_POINT,   
	IMPPANEL_10_100HZ_POINT, 
	IMPPANEL_1_10HZ_POINT,
	IMPPANEL_01_1HZ_POINT, 
	IMPPANEL_001_01HZ_POINT, 
	IMPPANEL_0001_001HZ_POINT, 
	IMPPANEL_00001_0001HZ_POINT, 	
	IMPPANEL_000001_00001HZ_POINT,   
    IMPPANEL_100K_1MHZ_CYCLE,
    IMPPANEL_10K_100KHZ_CYCLE,
	IMPPANEL_1K_10kHZ_CYCLE, 
	IMPPANEL_100_1KHZ_CYCLE, 
	IMPPANEL_10_100HZ_CYCLE,  
	IMPPANEL_1_10HZ_CYCLE, 
	IMPPANEL_01_1HZ_CYCLE, 
	IMPPANEL_001_01HZ_CYCLE,
	IMPPANEL_0001_001HZ_CYCLE,
	IMPPANEL_00001_0001HZ_CYCLE,	
	IMPPANEL_000001_00001HZ_CYCLE,
	IMPPANEL_NUM_DRAWINGTYPE,
 };
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?

