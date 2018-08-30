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

//==============================================================================
// External variables

//==============================================================================
// Global functions
int InitTableCells (int panel, int control, int unmOfColumn, int unmOfRow);
int AddValeToTable(int panel, int control, double* yval, double* xval);
int FormatTable(int panel, int control);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TablePanel_H__ */
