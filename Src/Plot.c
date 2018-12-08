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
		int numOfDotsToPlot=(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot;		//��ֹ�ж϶�ȥд���������
		if((numOfDotsToPlot + plotCurveIndex) >0)
			{
				if((pGraph->pCurveArray+plotCurveIndex)->numOfPlotDots >= 1)	//����Ѿ�����һ���㣬����һ���㿪ʼ����������
				{
					pGraph->plotHandle=PlotXY(hGraphDispPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot-1, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot-1, numOfDotsToPlot+1, VAL_FLOAT, VAL_FLOAT,
					pGraph->pCurveArray->pCurveAttr->plotStyle,
					pGraph->pCurveArray->pCurveAttr->pointStyle,
					pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
					pGraph->pCurveArray->pCurveAttr->lineColor);
				}
				else											//���һ����û����ֻ��һ����
				{
					pGraph->plotHandle=PlotXY(hGraphDispPanel, control, (pGraph->pCurveArray + plotCurveIndex)->pDotXPlot, (pGraph->pCurveArray + plotCurveIndex)->pDotYPlot, numOfDotsToPlot, VAL_FLOAT, VAL_FLOAT,
					pGraph->pCurveArray->pCurveAttr->plotStyle,
					pGraph->pCurveArray->pCurveAttr->pointStyle,
					pGraph->pCurveArray->pCurveAttr->lineStyle, 1,
					pGraph->pCurveArray->pCurveAttr->lineColor);
				}
			 }	
			(pGraph->pCurveArray + plotCurveIndex)->numOfPlotDots+=numOfDotsToPlot;		//��ͼ�ܵ�������
			(pGraph->pCurveArray + plotCurveIndex)->pDotXPlot+=numOfDotsToPlot;			//��ͼ��X����ָ�����
			(pGraph->pCurveArray + plotCurveIndex)->pDotYPlot+=numOfDotsToPlot;			//��ͼ��Y����ָ�����
			(pGraph->pCurveArray + plotCurveIndex)->numOfDotsToPlot-=numOfDotsToPlot;	//��ֹ�ж϶��ڻ�ͼ�ڼ���յ��µ�����.
	if(pGraph->plotHandle<0)
		return -1;
	else
		return 0;
}

