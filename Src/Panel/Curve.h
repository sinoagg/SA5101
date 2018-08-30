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
	int pointStyle;			//����ʽ
	int plotStyle;			//��ͼ��ʽ
	int lineStyle;			//������ʽ
}CurveAttrTypeDef;		

 typedef struct
{
 int curveIndex;	//�������
 int numOfTotalDots; //�������ܵ���
 int numOfPlotDots; //�Ѿ����˵ĵ���
 int numOfDotsToPlot; //��Ҫ���ĵ���
 double time;  			//ʱ��
 double* pDotXHead;		//X���������׵�ַ�����ֵ�ڻ�ͼ�Ĺ����б��ֲ���   plot Dot X head address
 double* pDotYHead;       //Y���������׵�ַ�����ֵ�ڻ�ͼ�Ĺ����б��ֲ���
 double* pDotX;		 //��X����������и�ֵ                 
 double* pDotY;      //��Y����������и�ֵ
 double* pDotXPlot;		//�Ѿ��������x���������ַ  ������ͼ   
 double* pDotYPlot;		//�Ѿ��������y���������ַ��������ͼ
 
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
