//==============================================================================
//
// Title:		i_t Curve.c
// Purpose:		曲线初始化和内存释放
//
// Created on:	2018/7/20 at 13:31:04 by.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <ansi_c.h>
#include "Curve.h"

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

//==============================================================================
/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int curveInit(CurveTypeDef* pCurve,int curveIndex,int numOfTotalDots,CurveAttrTypeDef* pCurveAttr) //曲线的初始化
{
	pCurve->pDotXHead = (float *)malloc(numOfTotalDots * sizeof(float));		  
	if(pCurve->pDotXHead == NULL) return -1;
	pCurve->pDotYHead = (float *)malloc (numOfTotalDots * sizeof(float));
	if(pCurve->pDotYHead == NULL) return -1;
	pCurve->curveIndex =curveIndex;
	pCurve->numOfTotalDots = numOfTotalDots;
	pCurve->numOfPlotDots = 0;
	pCurve->numOfDotsToPlot =0;
	pCurve->time = 0;
	pCurve->pDotX = pCurve->pDotXHead;
	pCurve->pDotY = pCurve->pDotYHead;
	pCurve->pDotXPlot = pCurve->pDotX;
	pCurve->pDotYPlot = pCurve->pDotY;
	/* pCurve->pCurveAttr = pCurveAttr;*/
	return 0;
}

//=============================================================================
int curveDeinit(CurveTypeDef* pCurve)   //内存释放
{
	free(pCurve->pDotXHead);
	pCurve->pDotXHead = NULL;
	free(pCurve->pDotYHead);
	pCurve->pDotYHead = NULL;
	return 0;
}

//============================================================================= 
