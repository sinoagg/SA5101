//==============================================================================
//Include file
#include "toolbox.h"
#include "GraphDisp.h"
#include <cvirte.h>		
#include <userint.h>
#include "Result Menu.h"
#include "Table.h"

//==============================================================================
//Types

enum ResultDispSelect
{
	DISP_TABLE=0,
	DISP_GRAPH=1
};

enum GraphDispSelect
{
	DISP_SINGLE_GRAPH=0,
	DISP_DOUBLE_GRAPH=1	
};

//==============================================================================
//extern global variables

extern int resultPanel;
extern int tablePanel;
extern int graphDispPanel;
extern int graphSelectPanel;
extern int saveDataPanel;

//============================================================================== 
// Static global variables

char sheetSavePath[512];
char graph1SavePath[512];
char graph2SavePath[512];

//==============================================================================  
// Static functions

static int SaveGraph(int panel, int control, int plotHandle, const char path[]); 

//==============================================================================
// Global variables

enum ResultDispSelect resultDispSelect=DISP_GRAPH;
enum GraphDispSelect graphDispSelect=DISP_SINGLE_GRAPH;

//==============================================================================
// Global functions	

static void DispTable(void)		// display table
{
	SetPanelPos(tablePanel, 175, 305);  
 	SetPanelSize(tablePanel, 851, 1285);      
	DisplayPanel(tablePanel);
	
	SetCtrlAttribute (tablePanel, TABLE_TABLE , ATTR_HEIGHT, 780);
	SetCtrlAttribute (tablePanel, TABLE_TABLE, ATTR_TOP,40);
	SetCtrlAttribute (tablePanel, TABLE_TABLE, ATTR_WIDTH, 1240);
	SetCtrlAttribute (tablePanel, TABLE_TABLE, ATTR_LEFT, 20);
}

static void DispSingleGraph(void)  //display single graph
{
	SetPanelPos(graphDispPanel, 175, 305);  
	SetPanelSize(graphDispPanel, 851, 1285);
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 800);
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
	DisplayPanel(graphDispPanel);
}

static void DispDoubleGraph(void) //display double graph
{
	SetPanelPos(graphDispPanel, 175, 305);  
	SetPanelSize(graphDispPanel, 851, 1285);
	SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //如果CheckBox是选中状态则显示两个graph     
	SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
	DisplayPanel(graphDispPanel);
}

static void DispGraphSelectCheckBox(void)
{
	//int val=0;
	if(graphDispSelect==DISP_SINGLE_GRAPH)
	{
		SetCtrlVal(graphSelectPanel, CHPANEL_CHECKBOX, 0);
	}
	else{
		SetCtrlVal(graphSelectPanel, CHPANEL_CHECKBOX, 1);
	 
	}
	SetPanelPos(graphSelectPanel, 175, 1457);  
	SetPanelSize(graphSelectPanel, 26, 140);      
 	DisplayPanel(graphSelectPanel);
}

void DispResultTableGraph(void)	   //display result table graph
{
	if(resultDispSelect==DISP_TABLE)
		DispTable();
	else
	{
	  	if(graphDispSelect==DISP_SINGLE_GRAPH) 
		DispSingleGraph();
		else if(graphDispSelect==DISP_DOUBLE_GRAPH)
		DispDoubleGraph();
	}
}

int CVICALLBACK TableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)   //点击table图标切换到table面板 
{
	switch(event){
		case EVENT_LEFT_CLICK:
			    DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico");
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico"); 
				DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 

			break;
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico");
				resultDispSelect = DISP_TABLE;
				DispResultTableGraph();
		break;
	}
	return 0;
}


int CVICALLBACK GraphCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
		//点击graph图标切换到graph面板
	switch(event){
		case EVENT_LEFT_CLICK:
			 DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
             DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
			 DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");  
			break;
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
				if(resultDispSelect == DISP_GRAPH) //如果此时在显示图的时候还去点击图的图标，则认为是想切换显示
				{
					DispGraphSelectCheckBox();
				}
				else
				{
					resultDispSelect = DISP_GRAPH;
					DispResultTableGraph();
				}
				
				int val;
				GetCtrlVal(graphSelectPanel, CHPANEL_CHECKBOX, &val);
				if(val)
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				else
				DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico"); 
			break;
	}	
	return 0;
}



int CVICALLBACK GraphSelectCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{  
	if(event == EVENT_COMMIT)
	{      	
		HidePanel(graphSelectPanel); 
		int val;
	  	GetCtrlVal(graphSelectPanel, CHPANEL_CHECKBOX, &val);
	    if(val)
		{	
		    DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
			DispDoubleGraph();
			graphDispSelect=DISP_DOUBLE_GRAPH;
		}
		else
		{   
			DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
			DispSingleGraph();
			graphDispSelect=DISP_SINGLE_GRAPH;
		}
	}
	return 0;
}

int CVICALLBACK SaveDataCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)

{
	   switch(event){
		case EVENT_LEFT_CLICK_UP:
				
				
			break;
			
		case EVENT_LEFT_CLICK:
			DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico");
			DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
			DisplayImageFile (resultPanel, RESULTMENU_SAVE, "Resource\\SaveData_pressed.ico"); 
			InstallPopup(saveDataPanel);
			break;
	}	
	return 0;
}

int CVICALLBACK ExitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_COMMIT)
	{
		RemovePopup(saveDataPanel);  	//移除、关闭savedata面板    
	}
	return 0;
}

int CVICALLBACK BrowseSheetCallback (int panel, int control, int event,
								   	 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{			
		case EVENT_LEFT_CLICK_UP:
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".xls", "*.xls", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, sheetSavePath)>0)
				SetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath);
			else 
				return -1;
			break;
	}
	return 0;
}
		 
int CVICALLBACK BrowseGraph1Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		     
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph1SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath);
			else 
				return -1;
			break;
	}
	return 0;
}

int CVICALLBACK BrowseGraph2Callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\UserData", ".jpg", "*.jpg;*.png;*.bmp;*.tif", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1, graph2SavePath)>0)
				SetCtrlVal(panel, SAVEDATA_GRAPH2PATH, graph2SavePath);
			else 
				return -1;
			break;
	}
	return 0;
}

int CVICALLBACK SaveGraph1Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		//	SaveGraph(panel, GRAPHDISP_GRAPH1, Graph1.plotHandle, graph1SavePath);
			break;
	}
	return 0;
}

int CVICALLBACK SaveGraph2Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		//	SaveGraph(panel, GRAPHDISP_GRAPH2, Graph2.plotHandle, graph2SavePath); 
			break;
	}
	return 0;
}

int CVICALLBACK SaveAllCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		//	SaveGraph(panel, GRAPHDISP_GRAPH1, Graph1.plotHandle, graph1SavePath);
		//	SaveGraph(panel, GRAPHDISP_GRAPH2, Graph2.plotHandle, graph2SavePath);
			break;
	}
	return 0;
}

static int SaveGraph(int panel, int control, int plotHandle, const char path[])
{
	int bitmapID;
	if(plotHandle<=0)		//no valid plot behavior
		MessagePopup ("Message", "No valod plot. Please run test first.");
	else
	{
		if(GetCtrlBitmap(panel, control, plotHandle,&bitmapID)<0)
			return -1;
		if(SaveBitmapToFile(path, bitmapID)<0)		 //need check the file format
			return -1;
		DiscardBitmap(bitmapID);
	}
	return 0;
}

int CVICALLBACK SaveSheetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	

   return 0;
}
