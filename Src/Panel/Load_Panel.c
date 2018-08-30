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
 #include "Load_Panel.h"

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
	if ((mainPanel = LoadPanel (0, "Ui Files/MainPanel.uir", MAIN_PANEL)) < 0)	  //load main panel
		return -1;
	
	if ((expListPanel = LoadPanel (mainPanel, "Ui Files/Experiment List.uir", EXP_LIST)) < 0)		//load left experiment panel
		return -1;
	
	if ((resultPanel = LoadPanel (mainPanel, "Ui Files/Result Menu.uir", RESULTMENU)) < 0)		//load  panel
	     return -1;
	
	if ((saveDataPanel = LoadPanel (resultPanel, "Ui Files/Result Menu.uir", SAVEDATA)) < 0)		//load  panel
	 return -1;
	
	if ((tablePanel = LoadPanel (mainPanel, "Ui Files/Table.uir", TABLE)) < 0)		//load  panel
	     return -1;
	
	if ((graphSelectPanel  = LoadPanel (mainPanel, "Ui Files/Result Menu.uir", CHPANEL)) < 0)		//load  panel
	     return -1;
	
	if ((graphDispPanel = LoadPanel (mainPanel, "Ui Files/GraphDisp.uir", GRAPHDISP)) < 0)		//load  panel
	     return -1;
	
	if ((userManagePanel = LoadPanel (mainPanel, "Ui Files/User Manage.uir", USERPANEL)) < 0)		//load left usermanage panel
	     return -1;
	
	if ((environmentPanel = LoadPanel (mainPanel, "Ui Files/Environment.uir", ENVIRONMEN)) < 0)		//load right environment panel
		return -1;
	
	if ((settingsPanel = LoadPanel (mainPanel, "Ui Files/Settings.uir", SETTINGS)) < 0)		//用于弹出settings面板 
		return -1;	
	
	if ((settingsPrjPanel = LoadPanel (settingsPanel, "Ui Files/Settings.uir", ENVT)) < 0)		//用于弹出Project Settings面板
		return -1;
	
	if ((settingsGraphPanel = LoadPanel (settingsPanel, "Ui Files/Settings.uir", GRAPH)) < 0)		//用于弹出Settings->Graph面板  
		return -1;  
	
	if ((settingsAboutPanel = LoadPanel (settingsPanel, "Ui Files/Settings.uir", ABOUT)) < 0)		//用于弹出Settings->About面板
		return -1;

	 if ((prjPanel = LoadPanel (mainPanel, "Ui Files/ProjectPanel.uir", PROPANEL)) < 0)		//load projects panel //弹出projects
		return -1;
	 
	 if ((prjListPanel = LoadPanel (prjPanel, "Ui Files/ProjectPanel.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;

	if ((itBasicPanel = LoadPanel (mainPanel, "Ui Files/IT/i_t Configuration.uir", I_T_CFG)) < 0)		//load  right panel
		return -1;	  

	if ((itAdvancePanel = LoadPanel (mainPanel, "Ui Files/IT/i_t Configuration.uir", I_T_ADV)) < 0)		//load right panel
		return -1;
	
	if ((cvBasicPanel = LoadPanel (mainPanel, "Ui Files/CV/c_v Configuration.uir", C_V_CFG)) < 0)		//load cv Configuration panel
		return -1;
	
	if ((cvAdvancePanel = LoadPanel (mainPanel, "Ui Files/CV/c_v Configuration.uir", C_V_ADV)) < 0)		//load right panel
		return -1;
	
	if ((lsvBasicPanel = LoadPanel (mainPanel, "Ui Files/LSV/lsv Configuration.uir",LSV_CFG)) < 0)		//load lsv Configuration panel
		return -1;
	
	if ((lsvAdvancePanel = LoadPanel (mainPanel, "Ui Files/LSV/lsv Configuration.uir", LSV_ADV)) < 0)		//load right panel
		return -1;
	
	if ((cpBasicPanel = LoadPanel (mainPanel, "Ui Files/CP/cp Configuration.uir", CP_CFG)) < 0)		//load lsv Configuration panel
		return -1;
	
	if ((cpAdvancePanel = LoadPanel (mainPanel, "Ui Files/CP/cp Configuration.uir", CP_ADV)) < 0)		//load right panel
	    return -1;
	
	if ((ocptBasicPanel = LoadPanel (mainPanel, "Ui Files/OCPT/ocpt Configuration.uir", OCPT_CFG)) < 0)		//load lsv Configuration panel
		return -1;
	
	if ((ocptAdvancePanel = LoadPanel (mainPanel, "Ui Files/OCPT/ocpt Configuration.uir", OCPT_ADV)) < 0)		//load right panel
	    return -1;
	
	if ((scvBasicPanel = LoadPanel (mainPanel, "Ui Files/SCV/scv Configuration.uir", SCV_CFG)) < 0)		//load lsv Configuration panel
		return -1;
	
	if ((scvAdvancePanel = LoadPanel (mainPanel, "Ui Files/SCV/scv Configuration.uir", SCV_ADV)) < 0)		//load right panel
	    return -1;
	
	 if ((npvBasicPanel = LoadPanel (mainPanel, "Ui Files/NPV/npv Configuration.uir", NPV_CFG)) < 0)		//load lsv Configuration panel
		return -1;
	 
	 if ((npvAdvancePanel = LoadPanel (mainPanel, "Ui Files/NPV/npv Configuration.uir", NPV_ADV)) < 0)		//load right panel
	    return -1;
	 
	 if ((swvBasicPanel = LoadPanel (mainPanel, "Ui Files/SWV/swv Configuration.uir", SWV_CFG)) < 0)		//load swv Configuration panel
		return -1;
	 
	 if ((swvAdvancePanel = LoadPanel (mainPanel, "Ui Files/SWV/swv Configuration.uir", SWV_ADV)) < 0)		//load right panel
	    return -1;

	
	DisplayPanel (mainPanel); 
	
	SetPanelPos(userManagePanel, 105, 3);  //加载面板位置 （,top,left）
	SetPanelSize(userManagePanel, 300, 300);//加载面板大小  (,height，width)
	//加滚动条847
	DisplayPanel(userManagePanel);
	
	SetPanelPos(expListPanel, 405, 3);  //加载面板位置 （,top,left）
	SetPanelSize(expListPanel, 621, 300);//加载面板大小  (,height，width)
	//加滚动条847
	DisplayPanel(expListPanel);

	SetPanelPos(graphDispPanel, 105, 305);     //top left
	SetPanelSize(graphDispPanel, 921, 1285);   //height width   
	DisplayPanel(graphDispPanel);
	
	SetCtrlAttribute(graphDispPanel,GRAPHDISP_GRAPH2,ATTR_VISIBLE,0); //隐藏图表二
	
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH1, ATTR_TOP,20);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH1, ATTR_LEFT,10);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH1, ATTR_WIDTH,1260);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH1, ATTR_HEIGHT,800);
	
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH2, ATTR_TOP,415);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH2, ATTR_LEFT,10);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH2, ATTR_WIDTH,1260);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH2, ATTR_HEIGHT,400);
	
	SetPanelPos(itBasicPanel, 105, 1592); //top   left
	SetPanelSize(itBasicPanel, 500, 308);// height  width
	DisplayPanel(itBasicPanel);
	
	SetPanelPos(environmentPanel, 605, 1592);
	SetPanelSize(environmentPanel, 421, 308);
	DisplayPanel(environmentPanel);
	
	int temp = CheckSystemClose();
	if(temp == 1)
	{
	   LaunchExcelCB();
	   ShowAndOpenExcelCB();
	}
	InitSystemClose(1); 
	return 0;
}
