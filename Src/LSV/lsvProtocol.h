//==============================================================================
//
// Title:		lsvProtocol.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/23 at 10:17:44 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __lsvProtocol_H__
#define __lsvProtocol_H__

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

void SetLsvArguments(double Vmax,double Vmin,double SS);
void Send_lsvcmd(double final,double initial,double scanrate);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __lsvProtocol_H__ */
