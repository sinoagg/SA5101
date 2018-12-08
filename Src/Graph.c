//==============================================================================
//
// Title:		i_t Graph.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:40:53 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include "Graph.h"
#include "Protocol.h"
#include "Curve.h"
#include "SettingsPanel.h"
#include "GraphDisp.h"
//==============================================================================
// Constants

//==============================================================================
// Types
GraphTypeDef Graph1;
GraphTypeDef Graph2;
//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
unsigned char UartTxBuf[64];
unsigned char UartRxBuf[500];
//==============================================================================
// Extern variables
unsigned char comSelect;
extern int itGraphPanel;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int GraphInit(int hGraphPanel, int graphIndex, int numOfCurve, int numOfDots, GraphTypeDef* pGraph)
{
	int i;
	pGraph->graphHandle=hGraphPanel;
	pGraph->graphIndex=graphIndex;
	pGraph->numOfCurve=numOfCurve;
	pGraph->pCurveArray = (CurveTypeDef *)malloc(numOfCurve* sizeof(CurveTypeDef)); 	//Curve Array Saving pointers to curve structure
	if(pGraph->pCurveArray == NULL) return -1;

	for(i=0;i<numOfCurve;i++)		//init curve
	{
		if(curveInit(pGraph->pCurveArray+i,i, numOfDots, GetSettingsCurveAttr(graphIndex,i)) == -1) return -1;
	}
	
	GraphAttrTypeDef* pGraphAttr = (GraphAttrTypeDef *)malloc(sizeof(CurveTypeDef));
	if(pGraphAttr==NULL) return -1;
	pGraph->pGraphAttr=pGraphAttr;
	
	return 0;
}
//============================================================================= 
int GraphDeinit(GraphTypeDef* pGraph)
{
	int i=0;
	for(i=0;i<(pGraph->numOfCurve);i++)
	{
		curveDeinit(pGraph->pCurveArray+i); 	
	}
	return 0;
}
//============================================================================= 
  void SetGraphY_Axis(GraphTypeDef* pGraph, float currentY_Val)  //currentY_ Val ==>Id  
{
	 switch(TestPara.testMode)
	{   
		case IT:
			if(Graph1.pCurveArray->numOfPlotDots<=1)   //�Ѿ����ĵ���<=1
			{
				if(currentY_Val>=0)   //��ǰ��Yֵ���ڵ���0
				{
					if(currentY_Val >= Graph1.pGraphAttr->yAxisTail )   //��ǰ��Yֵ����y������ֵ
					{
						Graph1.pGraphAttr->yAxisHead=currentY_Val*0.99;	   //y���ͷΪ��ǰ��ֵ*0.99
						Graph1.pGraphAttr->yAxisTail=currentY_Val*1.01;    //y���βΪ��ǰ��ֵ*1.01
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <=Graph1.pGraphAttr->yAxisHead) //��ǰ��Yֵ С��y�����Сֵ  
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*0.99;
						Graph1.pGraphAttr->yAxisTail=currentY_Val*1.01; 
					    SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
				 }
			    else
				{
				  	if(currentY_Val >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=currentY_Val*0.99;
						Graph1.pGraphAttr->yAxisHead=currentY_Val*1.01;  
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <= Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*1.01;
						Graph1.pGraphAttr->yAxisTail=currentY_Val*0.99;     
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
			   }
			}
			else					   //�Ѿ����ĵ�������1
			{
				if(currentY_Val >= 0)
				{
					if(currentY_Val >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=currentY_Val*1.09;   
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <=Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*0.99;
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
				}
				else
				{
				  	if(currentY_Val >= Graph1.pGraphAttr->yAxisTail )
					{
						Graph1.pGraphAttr->yAxisTail=currentY_Val*0.99;
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					} 		    
					else if(currentY_Val <= Graph1.pGraphAttr->yAxisHead)
					{
					    Graph1.pGraphAttr->yAxisHead=currentY_Val*1.09;
						SetAxisScalingMode(Graph1.graphHandle, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph1.pGraphAttr->yAxisHead,Graph1.pGraphAttr->yAxisTail);//���� Y  ��ķ�Χ
					}
				}
			}
			break;
	}
}
void SetGraphX_Axis(int graphDispPanel,int controlfloat,GraphTypeDef* pGraph) //�������Զ�����  
{
	switch(TestPara.testMode)
	{  
		case IT:
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV:
				if(pGraph->pGraphAttr->xAxisTail <= pGraph->pCurveArray->numOfPlotDots * TestPara.timeStep) //�ѻ�����*Step ===��ʵ��x�᳤��
				{
					pGraph->pGraphAttr->xAxisTail=(pGraph->pCurveArray->numOfPlotDots * TestPara.timeStep)*1.1; 
					SetAxisScalingMode(graphDispPanel, controlfloat, VAL_BOTTOM_XAXIS, VAL_MANUAL, pGraph->pGraphAttr->xAxisHead, pGraph->pGraphAttr->xAxisTail);//���� X  ��ķ�Χ
				}
			break;
		case LSV:
		case TAFEL:
		case CV:
			   	if(pGraph->pGraphAttr->xAxisTail <= pGraph->pCurveArray->numOfPlotDots * (TestPara.voltageStep/TestPara.sampleRate)) //�ѻ�����*Step ===��ʵ��x�᳤��
				{
					pGraph->pGraphAttr->xAxisTail=(pGraph->pCurveArray->numOfPlotDots * (TestPara.voltageStep/TestPara.sampleRate))*1.1; 
					SetAxisScalingMode(graphDispPanel, controlfloat, VAL_BOTTOM_XAXIS, VAL_MANUAL, pGraph->pGraphAttr->xAxisHead, pGraph->pGraphAttr->xAxisTail);//���� X  ��ķ�Χ
				}
			break;
	  }
}
