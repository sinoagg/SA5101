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
	int lineColor;          //������ɫ
}CurveAttrTypeDef;		

 typedef struct
{
	int curveIndex;	      //�������
	int numOfTotalDots; //�������ܵ���
	int numOfPlotDots; //�Ѿ����˵ĵ���
	int numOfDotsToPlot; //��Ҫ���ĵ���
	float realNum;         //ʵ��
	float time;  			//ʱ��
	float* pDotXHead;		//X���������׵�ַ�����ֵ�ڻ�ͼ�Ĺ����б��ֲ���   plot Dot X head address
	float* pDotYHead;       //Y���������׵�ַ�����ֵ�ڻ�ͼ�Ĺ����б��ֲ���
	float* pDotX;		 //��X����������и�ֵ                 
	float* pDotY;      //��Y����������и�ֵ
	float* pDotXPlot;		//�Ѿ��������x���������ַ  ������ͼ   
	float* pDotYPlot;		//�Ѿ��������y���������ַ��������ͼ
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
