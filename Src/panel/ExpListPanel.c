//==============================================================================
//
// Title:		ExperimentList.c
// Purpose:		实验列表面板的回调函数.
//
// Created on:	18/7/11 at 9:55:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <userint.h>
#include "Experiment List.h"
#include "ExpListPanel.h"
#include "MainPanel.h"
#include "ResultDispPanel.h"
#include "Protocol.h"
#include "Sample Configuration.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//===================================================================================================== 
static void SetCtrlDisp(int panel, int control, int controlLabel, int controlUnit, int display)
{
	SetCtrlAttribute (panel, control, ATTR_VISIBLE, display);
	SetCtrlAttribute (panel, controlLabel, ATTR_VISIBLE, display);
	SetCtrlAttribute (panel, controlUnit, ATTR_VISIBLE, display); 
}
//===================================================================================================== 
int CVICALLBACK ExpListCallBack (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			int expType,val;
			GetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,&val);
			SetCtrlAttribute (hMainPanel, MAIN_PANEL_ANALYZE, ATTR_DIMMED,0); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");			
			if(val == 1)
			{
				SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,0);
				SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,0); //运行状态停止时可设置曲线属性 
			}
			else 
			{
				SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);
			}
			DiscardPanel (hTwoTerminalPanel);
			SetPanelPos(hEnvironmentPanel, 607, 1600);
			DisplayPanel(hEnvironmentPanel);
			SetPanelPos(hBasicSamplePanel, 105, 1600);
			DisplayPanel(hBasicSamplePanel);
			GetActiveTreeItem (panel, control, &expType);
			TestPara.testMode=(enum TestMode)expType;
			switch(TestPara.testMode)
			{
				case IT:
					SetPanelPos(hIT_Panel, 104, 305);
					DisplayPanel(hIT_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4, 0) ;  //设置采样率控件不可见
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 1) ;  //设置运行控件可见 
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 1) ;  //设置采样时间间隔 不可见  
					break;
				case LSV:
					SetPanelPos(hLSV_Panel, 104, 305);
					DisplayPanel(hLSV_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 0) ;  //设置采样时间间隔 不可见
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 1);  //设置采样率控件可见
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见
					break;
				case CV:
					SetPanelPos(hCV_Panel, 104, 305);
					DisplayPanel(hCV_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 0) ;  //设置采样时间间隔 不可见
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 1);  //设置采样率控件可见
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
				case TAFEL:
					SetPanelPos(hTAFEL_Panel, 104, 305);
					DisplayPanel(hTAFEL_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 0) ;  //设置采样时间间隔 不可见
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 1);  //设置采样率控件可见
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
				case SV:
					SetPanelPos(hSV_Panel, 104, 305);
					DisplayPanel(hSV_Panel);
					
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 1) ;  //设置采样时间间隔可见  
				    SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 0);  //设置采样率控件不可见  		
			        SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
				case NPV:
					SetPanelPos(hNPV_Panel, 104, 305);
					DisplayPanel(hNPV_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 1) ;  //设置采样时间间隔可见  
				    SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 0);  //设置采样率控件不可见  		
			        SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
				case DPV:
					SetPanelPos(hDPV_Panel, 104, 305);
					DisplayPanel(hDPV_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 1) ;  //设置采样时间间隔可见  
				    SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 0);  //设置采样率控件不可见  		
			        SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
				case DNPV:
					SetPanelPos(hDNPV_Panel, 104, 305);
					DisplayPanel(hDNPV_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 1) ;  //设置采样时间间隔可见  
				    SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 0);  //设置采样率控件不可见  		
			        SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
				case SWV:
					SetPanelPos(hSWV_Panel, 104, 305);
					DisplayPanel(hSWV_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 1) ;  //设置采样时间间隔可见  
				    SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 0);  //设置采样率控件不可见  		
			        SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
				case IMP:
					SetPanelPos(hIMP_Panel, 104, 305);
					DisplayPanel(hIMP_Panel);
					SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_TIMESTEP, SAMPLE_CFG_TEXTMSG_2, SAMPLE_CFG_RUNTIME_UNIT_3, 0) ;  //设置采样时间间隔可见  
				    SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_SAMPLERATE, SAMPLE_CFG_TEXTMSG_4, SAMPLE_CFG_RUNTIME_UNIT_4 , 0);  //设置采样率控件不可见  		
			        SetCtrlDisp(hBasicSamplePanel, SAMPLE_CFG_RUNTIME, SAMPLE_CFG_TXT_RUNTIME, SAMPLE_CFG_RUNTIME_UNIT, 0) ;  //设置运行控件不可见 
					break;
			}
			break;
	}
	return 0;
}
