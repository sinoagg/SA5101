//==============================================================================
//
// Title:		TablePanel.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/8/3 at 9:49:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __TablePanel_H__
#define __TablePanel_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files
#include <userint.h> 
#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int column;									    //ап
	int columnWidth;								//ап©М  
	int row;										//пп
}Table_TypeDef;


extern Table_TypeDef Table_Date;
extern Table_TypeDef Table_ATTR; 
//==============================================================================
// External variables

//==============================================================================
// Global functions
void Table(char table_title[][20], int column,int columnWidth,int row);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TablePanel_H__ */
