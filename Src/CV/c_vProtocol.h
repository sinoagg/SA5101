//==============================================================================
//
// Title:		c_vProtocol.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/23 at 9:57:16 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __c_vProtocol_H__
#define __c_vProtocol_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include "cvidef.h"
#include "c_vProtocol.h"
#include "c_vPanel.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables
		
extern c_v_Cfg_TypeDef CvCfg;   
extern unsigned char comSelect;

//==============================================================================
// Global functions

void SetcvArguments(double Vmax,double Vmin,double sr,double Start,double Final,char Seg);
void send_cvcmd(double Vmax,double Vmin,double ss,int seg) ;
void Send_cvcmd(double Vmax,double Vmin,double ss,int seg) ;
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __c_vProtocol_H__ */
