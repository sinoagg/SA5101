//==============================================================================
//
// Title:		Timer.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/16 at 17:33:45 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Timer_H__
#define __Timer_H__

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef INCLUDE_AFTER_WINDOWS_H

#include "AbnormalDataCache.h"

#define INCLUDE_AFTER_WINDOWS_H
#endif
//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions 
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
int CVICALLBACK TimerCallback2 (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
int CVICALLBACK TimerCallback3 (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2); 
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Timer_H__ */
