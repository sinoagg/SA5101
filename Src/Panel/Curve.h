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
}CurveAttrTypeDef;		

 typedef struct
{
 int curveIndex;	//曲线序号
 int numOfTotalDots; //曲线内总点数
 int numOfPlotDots; //已经画了的点数
 int numOfDotsToPlot; //将要画的点数
 double time;  			//时间
 double* pDotXHead;		//X坐标数组首地址，这个值在画图的过程中保持不变   plot Dot X head address
 double* pDotYHead;       //Y坐标数组首地址，这个值在画图的过程中保持不变
 double* pDotX;		 //对X坐标数组进行赋值                 
 double* pDotY;      //对Y坐标数组进行赋值
 double* pDotXPlot;		//已经画到点的x坐标数组地址  用来画图   
 double* pDotYPlot;		//已经画到点的y坐标数组地址，用来画图
 
 CurveAttrTypeDef* pCurveAttr;
}Curve_TypeDef;


typedef struct
{
 float x;
 float y;
}Dot_TypeDef;
//==============================================================================
// External variables

//==============================================================================
// Global functions

int Declare_Your_Functions_Here (int x);
int curveInit(Curve_TypeDef* pCurve,int curveIndex,int numOfTotalDots,Curve_TypeDef* pCurveAttr);
int curveDeinit(Curve_TypeDef* pCurve);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __i_tCurve_H__ */
