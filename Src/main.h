				   //==============================================================================
//
// Title:		main.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/23 at 13:28:04 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __main_H__
#define __main_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
#define MEASURE_DEV_ADDR 0x00
#define SA51_UART_RX_LEN 7
#define SA51_UART_TX_LEN 33 
#define QUERY_PORT_NUM 15
#define BAUDRATE 115200 
#define POINTS 129
//==============================================================================
// Types

//==============================================================================
// External variables
extern unsigned char measureComPort;				//Serial Com Number
extern unsigned char controlComPort;
extern unsigned char measUartTxBuf[];
extern unsigned char measUartRxBuf[];
extern unsigned char curveComplete;
extern unsigned char measureUartFlag; 					//电学测量串口接收时要屏蔽数据查询 
extern unsigned char controlUartFlag; 					//环境参数串口接收时要屏蔽数据查询
extern unsigned char controlFlag;
extern int uartStatusFlag;
extern int rows;
extern unsigned char j;
extern int TimerID;
extern int abnmDCThreadFlag;
extern unsigned char pointInNumber;//段内循环数量 
extern unsigned char impCloseFlag;
extern float minFreq;
extern unsigned char num;
extern unsigned char totalNum;
extern double channel1Real[POINTS];
extern double channel1Imaginary[POINTS];
extern double channel2Real[POINTS];
extern double channel2Imaginary[POINTS];
//==============================================================================
// Global functions
void  CVICALLBACK MeasureComCallback(int portNumber ,int eventMask, void * callbackData);
int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFun)(int, int, void*));
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __main_H__ */
