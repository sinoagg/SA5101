#include <userint.h>
#include "MainPanel.h"
#include "SettingsPanel.h"
#include "Load_Panel.h"

#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色

Curve_TypeDef Graph1_CurveAttr1;
Curve_TypeDef Graph1_CurveAttr2;
Curve_TypeDef Graph1_CurveAttr3;

Curve_TypeDef Graph2_CurveAttr1;
Curve_TypeDef Graph2_CurveAttr2;
Curve_TypeDef Graph2_CurveAttr3;

Curve_TypeDef* GetSettingsCurveAttr(int GraphIndex, int CurveIndex)
{
	Curve_TypeDef* pCurveAttr;
	if(GraphIndex==GRAPH1)
	{
		switch(CurveIndex)
		{
			case CURVE1:
				pCurveAttr=&Graph1_CurveAttr1;
				break;
			case CURVE2:
				pCurveAttr=&Graph1_CurveAttr2;
				break;
			case CURVE3:
				pCurveAttr=&Graph1_CurveAttr3;
				break;
			default:
				pCurveAttr=&Graph1_CurveAttr1; 
		}
	}
	else
	{
		switch(CurveIndex%3)
		{
			case CURVE1:
				pCurveAttr=&Graph2_CurveAttr1;
				break;
			case CURVE2:
				pCurveAttr=&Graph2_CurveAttr2;
				break;
			case CURVE3:
				pCurveAttr=&Graph2_CurveAttr3;
				break;
			default:
				pCurveAttr=&Graph2_CurveAttr1; 
		}	
	}
	return pCurveAttr;
}


int CVICALLBACK EnvBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			SetPanelPos(settingsPrjPanel, 3 , 170);
			SetPanelSize(settingsPrjPanel, 350, 650);
			DisplayPanel(settingsPrjPanel); 
			
		//	HidePanel (hGraphPanel);
			HidePanel (settingsAboutPanel); 
			
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment背景色
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment文本颜色
			
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
			SetPanelSize(settingsGraphPanel, 350, 650);
			DisplayPanel(settingsGraphPanel);
			
			HidePanel (settingsPrjPanel); 
			HidePanel (settingsAboutPanel);
			
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph背景色
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			
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
			SetPanelSize(settingsAboutPanel, 350, 650);
			DisplayPanel(settingsAboutPanel);
			
		    HidePanel (settingsPrjPanel); 
			HidePanel (settingsGraphPanel);
		
			
			SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about背景色
	     	SetCtrlAttribute (panel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about文本颜色
			
			SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph背景色
	     	SetCtrlAttribute (panel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph文本颜色
	
			SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
	     	SetCtrlAttribute (panel, SETTINGS_ENVBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			break;

	}
	return 0;
}


int CVICALLBACK CancelCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 	RemovePopup(settingsPanel);   
			break;
	}
	return 0;
}

//本地工作目录
char projectSavePath[512];

int CVICALLBACK ProCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		
			if(DirSelectPopup ("E:\\GitWorkplace\\Sinoagg\\Software\\", "Select Directory", 1, 1, projectSavePath)>0)     
			{
			 SetCtrlVal(panel, ENVT_PROPATH, projectSavePath); 
			}
			else 
			{
				return -1;
			}
			break;
	}
	return 0;
}

