#include <userint.h>
#include "Load_Panel.h"
#include "SettingsPanel.h"

#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色


char buf[800];
int vertDivision;
CurveAttrTypeDef Graph1_CurveAttr1;
CurveAttrTypeDef Graph1_CurveAttr2;
CurveAttrTypeDef Graph1_CurveAttr3;


 CurveAttrTypeDef Graph2_CurveAttr1;
 CurveAttrTypeDef Graph2_CurveAttr2;
 CurveAttrTypeDef Graph2_CurveAttr3;

char ProjectSavePath[512]="C:\\Sinoagg\\SA5101\\Users\\";	   //本地工作目录Dir



static void GetSingleCurveAttr(CurveAttrTypeDef *pCurveAttr, int GraphIndex, int CurveIndex)
{
	GetCtrlVal(settingsGraphPanel, SETGRAPH_LINE_STYLE, &(pCurveAttr->lineStyle));
	GetCtrlVal(settingsGraphPanel, SETGRAPH_PLOT_STYLE, &(pCurveAttr->plotStyle));
	GetCtrlVal(settingsGraphPanel, SETGRAPH_POINT_STYLE,&(pCurveAttr->pointStyle));
	//根据index获取颜色
													                                                                                                                                                                                                                                  
	GetCtrlVal(settingsGraphPanel,SETGRAPH_GRAPH1CLR1,&(Graph1_CurveAttr1.lineColor));
	GetCtrlVal(settingsGraphPanel,SETGRAPH_GRAPH1CLR2,&(Graph1_CurveAttr2.lineColor));
	GetCtrlVal(settingsGraphPanel,SETGRAPH_GRAPH1CLR3,&(Graph1_CurveAttr3.lineColor)); 
	GetCtrlVal(settingsGraphPanel,SETGRAPH_GRAPH2CLR1,&(Graph2_CurveAttr1.lineColor));
	GetCtrlVal(settingsGraphPanel,SETGRAPH_GRAPH2CLR2,&(Graph2_CurveAttr2.lineColor));
	GetCtrlVal(settingsGraphPanel,SETGRAPH_GRAPH2CLR3,&(Graph2_CurveAttr3.lineColor));
}

CurveAttrTypeDef* GetSettingsCurveAttr(int GraphIndex, int CurveIndex)
{
	
	if(GraphIndex==GRAPH1)  
	{
		switch(CurveIndex % 3)
		{
			case 0:
				GetSingleCurveAttr(&Graph1_CurveAttr1, GraphIndex, CurveIndex);
				pCurveAttr=&Graph1_CurveAttr1;
				break;
			case 1:
				GetSingleCurveAttr(&Graph1_CurveAttr2, GraphIndex, CurveIndex);       
				pCurveAttr=&Graph1_CurveAttr2;
				break;
			case 2:
				GetSingleCurveAttr(&Graph1_CurveAttr3, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph1_CurveAttr3;
				break;
			default:
				GetSingleCurveAttr(&Graph1_CurveAttr1, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph1_CurveAttr1;
				break;
		}
	}
	else if(GraphIndex==GRAPH2) 
	{
		switch(CurveIndex)
		{
			case CURVE1:
				GetSingleCurveAttr(&Graph2_CurveAttr1, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr1;
				break;
			case CURVE2:
				GetSingleCurveAttr(&Graph2_CurveAttr2, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr2;
				break;
			case CURVE3:
				GetSingleCurveAttr(&Graph2_CurveAttr3, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr3;
				break;
			default:
				GetSingleCurveAttr(&Graph2_CurveAttr1, GraphIndex, CurveIndex);   
				pCurveAttr=&Graph2_CurveAttr1;
				break;
		}
	}
	return pCurveAttr;
}		   

int CVICALLBACK PrjBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(settingsPrjPanel, 5, 170);
			//SetPanelSize(hSettingsPrjPanel, 350, 650);
			DisplayPanel(settingsPrjPanel);
			HidePanel(settingsGraphPanel);
			HidePanel(settingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment背景色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment文本颜色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph背景色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph文本颜色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about背景色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about文本颜色

			break;

	}
	return 0;
}

int CVICALLBACK GraphBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(settingsGraphPanel, 5, 170);
			//SetPanelSize(hSettingsGraphPanel, 350, 650);
			DisplayPanel(settingsGraphPanel);
			HidePanel(settingsPrjPanel);
			HidePanel(settingsAboutPanel);
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph背景色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph文本颜色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //about背景色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //about文本颜色
			break;
	}
	return 0;
}

int CVICALLBACK AboutBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(settingsAboutPanel, 5, 170);
			//SetPanelSize(hSettingsAboutPanel, 350, 650);
			DisplayPanel(settingsAboutPanel);
			HidePanel(settingsGraphPanel);
			HidePanel(settingsPrjPanel);
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about背景色
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about文本颜色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph背景色
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph文本颜色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
			SetCtrlAttribute (panel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			break;
	}
	return 0;
}

int CVICALLBACK PrjDirCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:

			if(DirSelectPopup ("C:\\Sinoagg\\SA6101\\Users\\", "Select Directory", 1, 1, ProjectSavePath)>0)
			{
				SetCtrlVal(panel, ENVT_PROPATH, ProjectSavePath);
			}
			else
			{
				return -1;
			}
			break;
	}
	return 0;
}

int  CVICALLBACK SettingsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			RemovePopup(settingsPanel);
			break;
	}
	return 0;
}

