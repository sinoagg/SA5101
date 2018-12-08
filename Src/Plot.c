//==============================================================================
//
// Title:		Plot.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:35:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include "Plot.h"
#include <userint.h>
#include "Graph.h"
#include"LoadPanel.h"
#include "GraphDisp.h"
#include "SettingsPanel.h"
#include "Protocol.h"	  
#include <userint.h> 

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

CurveAttrTypeDef* pCurveAttr; 
int graph2tempclr;
int graph2humclr; 
int graph2preclr;
int CurveNums;
//==============================================================================
// Global functions
int PlotCurve1(GraphTypeDef* pGraph, int graphDispPanel, int control, int plotCurveIndex)       
{   
		int numOfDotsToPlot=(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot;		//防止中断端去写入这个数据
		if((numOfDotsToPlot + plotCurveIndex) >0)
			{
				if((pGraph->pCurveArray+plotCurveIndex)->numOfPlotDots >= 1)	//如果已经画了一个点，从上一个点开始画进行连线
				{
					pGraph->plotHandle=PlotXY(hGraphDispPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot-1, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT,
					pGraph->pCurveArray->pCurveAttr->plotStyle,
					pGraph->pCurveArray->pCurveAttr->pointStyle,
					pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
					pGraph->pCurveArray->pCurveAttr->lineColor);
				}
				else											//如果一个点没画，只画一个点
				{
					pGraph->plotHandle=PlotXY(hGraphDispPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,
					pGraph->pCurveArray->pCurveAttr->plotStyle,
					pGraph->pCurveArray->pCurveAttr->pointStyle,
					pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
					pGraph->pCurveArray->pCurveAttr->lineColor);
				}
			 }	
			(pGraph->pCurveArray + plotCurveIndex)->numOfPlotDots+=numOfDotsToPlot;		//画图总点数递增
			(pGraph->pCurveArray + plotCurveIndex)->pDotXPlot+=numOfDotsToPlot;			//画图点X坐标指针递增
			(pGraph->pCurveArray + plotCurveIndex)->pDotYPlot+=numOfDotsToPlot;			//画图点Y坐标指针递增
			(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot-=numOfDotsToPlot;	//防止中断端在画图期间接收到新的数据.
	if(pGraph->plotHandle<0)
		return -1;
	else
		return 0;
}

