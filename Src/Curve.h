//==============================================================================
//
// Title:		i_t Curve.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/20 at 13:31:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Curve_H__
#define __Curve_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
 typedef struct
{
	int pointStyle;			//点样式
	int plotStyle;			//画图样式
	int lineStyle;			//曲线样式
	int lineColor;          //曲线颜色
}CurveAttrTypeDef;		

 typedef struct
{
	int curveIndex;	      //曲线序号
	int numOfTotalDots; //曲线内总点数
	int numOfPlotDots; //已经画了的点数
	int numOfDotsToPlot; //将要画的点数
	float realNum;         //实数
	float time;  			//时间
	float* pDotXHead;		//X坐标数组首地址，这个值在画图的过程中保持不变   plot Dot X head address
	float* pDotYHead;       //Y坐标数组首地址，这个值在画图的过程中保持不变
	float* pDotX;		 //对X坐标数组进行赋值                 
	float* pDotY;      //对Y坐标数组进行赋值
	float* pDotXPlot;		//已经画到点的x坐标数组地址  用来画图   
	float* pDotYPlot;		//已经画到点的y坐标数组地址，用来画图
	CurveAttrTypeDef* pCurveAttr;
}CurveTypeDef;


typedef struct
{
	 float x;
	 float y;
}DotTypeDef;
//==============================================================================
// External variables

//==============================================================================
// Global functions

int Declare_Your_Functions_Here (int x);
int curveInit(CurveTypeDef* pCurve,int curveIndex,int numOfTotalDots,CurveAttrTypeDef* pCurveAttr);
int curveDeinit(CurveTypeDef* pCurve);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __i_tCurve_H__ */
