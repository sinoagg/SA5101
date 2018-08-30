//==============================================================================
//
// Title:		AbnormalDataCache.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/8/28 at 10:40:52 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __AbnormalDataCache_H__
#define __AbnormalDataCache_H__


#include "excelreport.h" 
#include "cvidef.h"

#ifdef __cplusplus
    extern "C" {
#endif

		
#ifndef INCLUDE_AFTER_WINDOWS_H

#include <utility.h>

#define INCLUDE_AFTER_WINDOWS_H
#endif
//==============================================================================
// Include files

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
int LaunchExcelCB ();
int ShowAndOpenExcelCB ();
int ShutDownExcelCB();
int InitExcelCB (int numberOfRows, int numberOfColumns);
int SaveExcelCB(int panel, int control);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __AbnormalDataCache_H__ */
