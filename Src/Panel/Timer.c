//==============================================================================
//
// Title:		Timer.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:33:45 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <rs232.h>
#include "Timer.h"
#include "GraphDisp.h"
#include "Load_Panel.h"
#include "i_tProtocol.h"
#include "asynctmr.h" 
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Extern global variables
extern Graph_TypeDef Graph;
extern int TimerID2;
extern int TimerID3;
//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	
	int numOfDotsToPlot=Graph.pCurveArray->numOfDotsToPlot;							//防止中断端去写入这个数据 
	
	if(numOfDotsToPlot>0)
	{
	   	if(Graph.pCurveArray->numOfPlotDots >= 1)																//如果有需要画图的点
		{
			//把电流在曲线图上从左至右实时更新
			 PlotXY (graphDispPanel, GRAPHDISP_GRAPH1, Graph.pCurveArray->pDotXPlot-1,Graph.pCurveArray->pDotYPlot-1,
							numOfDotsToPlot+1, VAL_DOUBLE, VAL_DOUBLE, VAL_CONNECTED_POINTS, 
							VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
		}
		else
		{
		     PlotXY(graphDispPanel, GRAPHDISP_GRAPH1, Graph.pCurveArray->pDotXPlot, Graph.pCurveArray->pDotYPlot,
									   numOfDotsToPlot, VAL_DOUBLE, VAL_DOUBLE, VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE,
									   VAL_SOLID, 1, VAL_BLUE);

		}
		Graph.pCurveArray->numOfPlotDots+=numOfDotsToPlot;		//画图总点数递增
		Graph.pCurveArray->pDotXPlot+=numOfDotsToPlot;			//画图点X坐标指针递增
		Graph.pCurveArray->pDotYPlot+=numOfDotsToPlot;			//画图点Y坐标指针递增
		Graph.pCurveArray->numOfDotsToPlot-=numOfDotsToPlot;		//防止中断端在画图期间接收到新的数据
	}
		
	return 0;
}

int CVICALLBACK TimerCallback2 (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	if(I_tCfg.cfgI_t_runtime < I_tCfg.cfgI_t_sampleinterval)
	 {
	   DiscardAsyncTimer(TimerID2);
	   graphDeinit(&Graph);
	 }
	 else
	 {
	   send_itcmd();
	   I_tCfg.cfgI_t_runtime -= I_tCfg.cfgI_t_sampleinterval;	 
	 }
	 return 0;
}

int CVICALLBACK TimerCallback3 (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	if(I_tCfg.cfgI_t_runtime > 0)
	 {
	   I_tCfg.cfgI_t_runtime -= 1;
	 }
	 else
	 {
	   send_itClosecmd();
	   DiscardAsyncTimer(TimerID3);
	   graphDeinit(&Graph);	 
	 }
	 return 0;
}
