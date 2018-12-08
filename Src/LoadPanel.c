//==============================================================================
//
// Title:		LoadPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:21:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
 #include "LoadPanel.h"

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
int LoadInitPanel (void)
{
	if ((hMainPanel = LoadPanel (0, "MainPanel.uir", MAIN_PANEL)) < 0)	  //load main panel
		return -1;
	
	if ((hExpListPanel = LoadPanel (hMainPanel, "Experiment List.uir", EXP_LIST)) < 0)		//load left experiment panel
		return -1;
	
	if ((hResultMenuPanel = LoadPanel (hMainPanel, "Result Menu.uir", RESULTMENU)) < 0)		//load  panel
	     return -1;
	
	if ((hSaveDataPanel = LoadPanel (hMainPanel, "Result Menu.uir", SAVEDATA)) < 0)		//load  panel
	 return -1;
	
	if ((hTablePanel = LoadPanel (hMainPanel, "Table.uir", TABLE)) < 0)		//load  panel
	     return -1;
	
	if ((hGraphSelectPanel  = LoadPanel (hMainPanel, "Result Menu.uir", CHPANEL)) < 0)		//load  panel
	     return -1;
	
	if ((hGraphDispPanel = LoadPanel (hMainPanel, "GraphDisp.uir", GRAPHDISP)) < 0)		//load  panel
	     return -1;
	
	if ((hEnvironmentPanel = LoadPanel (hMainPanel, "Environment.uir", ENVIRONMEN)) < 0)		//load right environment panel
		return -1;
	
	if ((hSettingsPanel = LoadPanel (hMainPanel, "Settings.uir", SETTINGS)) < 0)		//用于弹出settings面板 
		return -1;	
	
	if ((hSettingsPrjPanel = LoadPanel (hSettingsPanel, "Settings.uir", ENVT)) < 0)		//用于弹出Project Settings面板
		return -1;
	
	if ((hSettingsGraphPanel = LoadPanel (hSettingsPanel, "Settings.uir", SETGRAPH)) < 0)		//用于弹出Settings->Graph面板  
		return -1;  
	
	if ((hSettingsAboutPanel = LoadPanel (hSettingsPanel, "Settings.uir", ABOUT)) < 0)		//用于弹出Settings->About面板
		return -1;

	 if ((hPrjPanel = LoadPanel (hMainPanel, "ProjectPanel.uir", PROPANEL)) < 0)		//load projects panel //弹出projects
		return -1;
	 
	 if ((hPrjListPanel = LoadPanel (hPrjPanel, "ProjectPanel.uir", LISTPANEL)) < 0)		//load projects panel
		return -1;
	 
	 if((hTwoTerminalPanel= LoadPanel(hMainPanel,"Terminal.uir",TWOTRMLPAL))<0)
		return -1;
	 
	 if ((hResultDispPanel = LoadPanel (hMainPanel, "ResultDispPanel.uir", RESULTDISP)) < 0)		//load right panel
		return -1;
	 
	 if ((hBasicSamplePanel= LoadPanel (hMainPanel, "Sample Configuration.uir", SAMPLE_CFG)) < 0)		//load right panel
		return -1;
	 
	 if ((hAdvanceSamplePanel= LoadPanel (hMainPanel, "Sample Configuration.uir", SAMPLE_ADV)) < 0)		//load right panel
		return -1;
	 
	if ((ItPanel.panelHandle = LoadPanel (hMainPanel, "I-T.uir", ITPANEL)) < 0)		//load I-T  panel
		return -1;
	   hIT_Panel = ItPanel.panelHandle;
	   
	if ((CvPanel.panelHandle = LoadPanel (hMainPanel, "C-V.uir", ITPANEL)) < 0)		//load I-T  panel
		return -1;
	   hCV_Panel = CvPanel.panelHandle;
	   
	if ((LsvPanel.panelHandle = LoadPanel (hMainPanel, "LSV.uir", ITPANEL)) < 0)		//load I-T  panel
		return -1;
	   hLSV_Panel = LsvPanel.panelHandle;
	   
	if ((TafelPanel.panelHandle = LoadPanel (hMainPanel, "TAFEL.uir", ITPANEL)) < 0)		//load I-T  panel
		return -1;
	   hTAFEL_Panel = TafelPanel.panelHandle;
	   
	if ((SvPanel.panelHandle = LoadPanel (hMainPanel, "SV.uir", SVPANEL)) < 0)		//load I-T  panel
		return -1;
	    hSV_Panel = SvPanel.panelHandle;
		
	if ((NpvPanel.panelHandle =  LoadPanel (hMainPanel, "NPV.uir", NPVPANEL)) < 0)		//load I-T  panel
		return -1;
	    hNPV_Panel = NpvPanel.panelHandle;
		
	if ((DpvPanel.panelHandle= LoadPanel (hMainPanel, "DPV.uir", DPVPANEL)) < 0)		//load I-T  panel
		return -1;
	    hDPV_Panel = DpvPanel.panelHandle;
		
	if ((DnpvPanel.panelHandle = LoadPanel (hMainPanel, "DNPV.uir", DNPVPANEL)) < 0)		//load I-T  panel
		return -1;
		hDNPV_Panel = DnpvPanel.panelHandle;
		
	if ((SwvPanel.panelHandle = LoadPanel (hMainPanel, "SWV.uir", SWVPANEL)) < 0)		//load I-T  panel
		return -1;
		hSWV_Panel = SwvPanel.panelHandle; 
	 
	if ((ImpPanel.panelHandle = LoadPanel (hMainPanel, "IMP.uir", SWVPANEL)) < 0)		//load I-T  panel
		return -1;
		hIMP_Panel = ImpPanel.panelHandle; 

	DisplayPanel (hMainPanel); 
	SetPanelPos(hExpListPanel, 105, 3);  //加载面板位置 （,top,left）   
	DisplayPanel(hExpListPanel);
	SetPanelPos(hGraphDispPanel, 172, 305);//加载graph面板位置
	DisplayPanel(hGraphDispPanel);
	SetPanelPos(hIT_Panel, 104, 305);//加载IT面板位置
	DisplayPanel(hIT_Panel);
	SetPanelPos(hTwoTerminalPanel,124,1600); //加载空面板位置
	DisplayPanel(hTwoTerminalPanel);
	
	int temp = CheckSystemClose();		//检查软件系统是不是异常关闭
	if(temp == 1)
	{
	   LaunchExcelCBShow();
	}
	InitSystemClose(1); 				//初始化异常关闭状态为1
	return 0;
}
