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
#include <userint.h>
#include "Graph.h"
#include "i_tPanel.h"
#include "i_tProtocol.h"
#include "Curve.h"
#include "SettingsPanel.h"

//==============================================================================
// Constants

//==============================================================================
// Types
Graph_TypeDef Graph;
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
extern unsigned char comSelect;
extern int itGraphPanel;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int i_tgraphInit(int graphIndex, int numOfCurve, int numOfDots, Graph_TypeDef* pGraph)
{
	int i;
	pGraph->graphIndex=graphIndex;
	pGraph->numOfCurve=numOfCurve;
	pGraph->pCurveArray = (Curve_TypeDef *)malloc(numOfCurve* sizeof(Curve_TypeDef)); 	//Curve Array Saving pointers to curve structure
	if(pGraph->pCurveArray == NULL) return -1;

	for(i=0;i<numOfCurve;i++)		//init curve
	{
		if(curveInit(pGraph->pCurveArray+i,i, numOfDots, GetSettingsCurveAttr(graphIndex,i)) == -1) return -1;
	}
	
	GraphAttrTypeDef* pGraphAttr = (GraphAttrTypeDef *)malloc(sizeof(Curve_TypeDef));
	if(pGraphAttr==NULL) return -1;
	pGraph->pGraphAttr=pGraphAttr;
	
	return 0;
}

int graphDeinit(Graph_TypeDef* pGraph)
{
	int i=0;
	for(i=0;i<(pGraph->numOfCurve);i++)
	{
		curveDeinit(pGraph->pCurveArray+i); 	
	}
	return 0;
}


int receive_itdataanalysis()
{
	int rxNum=GetInQLen(comSelect);  //获取串口输入队列长度
	if (rxNum > 500) rxNum = 500;
	RxDataTypeDef RxData;
	ComRd(comSelect,(char *)UartRxBuf,rxNum);     //读取指定长度数据 
	
	if(I_tCfg.cfgI_t_currentrange == 0)
	{
		while(rxNum >=12)
		{
			ProtocolGetData(UartRxBuf,&RxData);
			Graph.pCurveArray->numOfDotsToPlot++;
	    	*(Graph.pCurveArray->pDotY++) = RxData.rxvoltage / RxData.rxResistance;
			*(Graph.pCurveArray->pDotX++) = Graph.pCurveArray->time;
			Graph.pCurveArray->time += I_tCfg.cfgI_t_sampleinterval;
			rxNum -= 12;
		}
	}
	else 
	{
		while(rxNum >= 6)
		{
			ProtocolGetData1(UartRxBuf,&RxData);
			Graph.pCurveArray->numOfDotsToPlot++;
			*(Graph.pCurveArray->pDotY++) = RxData.rxvoltage;
			*(Graph.pCurveArray->pDotX++) = Graph.pCurveArray->time;
			Graph.pCurveArray->time += I_tCfg.cfgI_t_sampleinterval;
			rxNum -= 6;
		}
	}
	FlushInQ (5);
	FlushOutQ (5);
	return 0;
}


