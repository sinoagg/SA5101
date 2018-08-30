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
	int plotHandle;                                  //graph Handle
	int graphIndex;									//graph Index
	int numOfCurve;									//number of Curves
	GraphAttrTypeDef* pGraphAttr;                    
	Curve_TypeDef* pCurveArray;						//pointer to curve array
}Graph_TypeDef;
//==============================================================================
// External variables

/*------------------------------------------------------------------*/
/*     FLAG SET                                                     */
/*------------------------------------------------------------------*/

//==============================================================================
// Global functions
int i_tgraphInit(int graphIndex, int numOfCurve, int numOfDots, Graph_TypeDef* pGraph);
int graphDeinit(Graph_TypeDef* pGraph);
int receive_itdataanalysis();
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __i_t Graph_H__ */
