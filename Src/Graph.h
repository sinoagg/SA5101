//==============================================================================
//
// Title:		Graph.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/12 at 13:50:53 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Graph_H__
#define __Graph_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "Curve.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int xAxisHead;
	int xAxisTail;
	int yAxisHead;
	int yAxisTail;
}GraphAttrTypeDef;

typedef struct
{													    
	int graphHandle;									//graph Handle 
	int graphIndex;									//graph Index
	int numOfCurve;									//number of Curves
	int plotHandle;									//后期需要整改属于plot
	int plotCurveIndex;								//当前在画曲线
	
	GraphAttrTypeDef* pGraphAttr;                    
	CurveTypeDef* pCurveArray;						//pointer to curve array
}GraphTypeDef;
//==============================================================================
// External variables
extern GraphTypeDef Graph1;
extern GraphTypeDef Graph2;
/*------------------------------------------------------------------*/
/*     FLAG SET                                                     */
/*------------------------------------------------------------------*/

//==============================================================================
// Global functions
int GraphInit(int hGraphPanel, int graphIndex, int numOfCurve, int numOfDots, GraphTypeDef* pGraph);
int GraphDeinit(GraphTypeDef* pGraph);
void SetGraphX_Axis(int graphDispPanel,int controlfloat,GraphTypeDef* pGraph);//坐标轴自动调整
void SetGraphY_Axis(GraphTypeDef* pGraph, float currentY_Val);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __i_t Graph_H__ */
