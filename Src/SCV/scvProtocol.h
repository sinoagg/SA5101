//==============================================================================
//
// Title:		scvProtocol.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/26 at 15:44:52 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __scvProtocol_H__
#define __scvProtocol_H__

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

//==============================================================================
// External variables

//==============================================================================
// Global functions
int setScvArguments(double initial,double final,double incr,double stepPeriods,double samplingWidth);
void send_scvcmd(double initial,double final,double incr,double stepPeriods);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __scvProtocol_H__ */
