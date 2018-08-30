//==============================================================================
//
// Title:		npvProtocol.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/28 at 9:31:51 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __npvProtocol_H__
#define __npvProtocol_H__

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
int SetNpvArguments(double initial,double final,double incr,double pluse,double samplingWidth,
					double pluseWidth,double plusePeriod);
void Send_npvCmd(double initial,double final,double pluse,double incr,double samplingWidth,
				 double PluseWidth,double PlusePeriod);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __npvProtocol_H__ */
