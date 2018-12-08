//==============================================================================
//
// Title:		Timer.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:33:45 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <rs232.h>
#include "Timer.h"
#include "LoadPanel.h"
#include "asynctmr.h"
#include "Protocol.h"
#include "main.h"
//==============================================================================
// Constants
   
//==============================================================================
// Types

//==============================================================================
// Extern global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
int CVICALLBACK TimerCallback (int panel, int control, int event,								//��ʱȥ��ѯ
								void *callbackData, int eventData1, int eventData2)
{
		switch (event)
	{
		case EVENT_TIMER_TICK:
			if(measureUartFlag == 1)											//���ڽ���ʱҪ�������ݲ�ѯ
			{
				ProtocolQuery(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);
				Delay(0.3);	    //ÿ300ms��ѯһ��
			}
			//if(controlUartFlag == 1)			  //�����������ݲ�ѯ
			//{
			//	Read_CGS_Value(controlComPort);
			//	Delay(0.020);
			//}
			break;
	}
	return 0;
}




