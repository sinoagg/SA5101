//==============================================================================
//
// Title:		i_t Curve.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/20 at 13:31:04 by .
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

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int curveInit(Curve_TypeDef* pCurve,int curveIndex,int numOfTotalDots,CurveAttrTypeDef* pCurveAttr)
{
	pCurve->pDotXHead = (double *)malloc((numOfTotalDots+1) * sizeof(double));
	 if(pCurve->pDotXHead == NULL) return -1;
	pCurve->pDotYHead = (double *)malloc ((numOfTotalDots+1) * sizeof(double));
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

int curveDeinit(Curve_TypeDef* pCurve)
{
	free(pCurve->pDotXHead);
	pCurve->pDotXHead = NULL;
	free(pCurve->pDotYHead);
	pCurve->pDotYHead = NULL;
	
	return 0;
}
