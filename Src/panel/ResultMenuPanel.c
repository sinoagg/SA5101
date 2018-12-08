//==============================================================================
//Include file
#include <cviauto.h>
#include "Result Menu.h" 
#include "toolbox.h"
#include "GraphDisp.h"
#include <cvirte.h>		
#include <userint.h>
#include "ResultMenuPanel.h"
#include "Table.h"
#include "excel2000.h"
#include "excelreport.h"

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
extern int hResultMenuPanel;
extern int hTablePanel;
extern int hGraphDispPanel;
extern int hGraphSelectPanel;
extern int hSaveDataPanel;
//============================================================================== 
// Static global variables
int sheet = 0;
int graph1 = 0;
int graph2 = 0;
static char sheetSavePath[512];
static char graph1SavePath[512];
static char graph2SavePath[512];
//static char sheetPath[512] = " C:\\SINOAGG\SA6101\\UserData\\Sheet.xls";
//static char graph1Path[512] = "C:\\SINOAGG\SA6101\\UserData\\Graph1.jpg";
//static char graph2Path[512]= "C:\\SINOAGG\SA6101\\UserData\\Graph2.jpg";
//==============================================================================  
// Static functions
static int SaveGraph(int panel, int control, int plotHandle, const char path[]); 

//==============================================================================
// Global variables
enum ResultDispSelect resultDispSelect=DISP_GRAPH;
enum GraphDispSelect graphDispSelect=DISP_SINGLE_GRAPH;
Rect rc;
int nBitmapID;  
//==============================================================================
// Global functions	
static void DispTable(void)		// display table
{
	SetPanelPos(hTablePanel, 177, 305);  
 	SetPanelSize(hTablePanel, 828, 1293);      
	DisplayPanel(hTablePanel);
	
	SetCtrlAttribute (hTablePanel, TABLE_DISTABLE , ATTR_HEIGHT, 780);
	SetCtrlAttribute (hTablePanel, TABLE_DISTABLE, ATTR_TOP,40);
	SetCtrlAttribute (hTablePanel, TABLE_DISTABLE, ATTR_WIDTH, 1240);
	SetCtrlAttribute (hTablePanel, TABLE_DISTABLE, ATTR_LEFT, 20);
}

static void DispSingleGraph(void)  //display single graph
{
	SetPanelPos(hGraphDispPanel, 177, 305);  
	SetPanelSize(hGraphDispPanel, 828, 1293);
	SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 800);
	SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
	DisplayPanel(hGraphDispPanel);
}

static void DispDoubleGraph(void) //display double graph
{
	SetPanelPos(hGraphDispPanel, 177, 305);  
	SetPanelSize(hGraphDispPanel, 828, 1293);
	SetCtrlAttribute (hGraphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //如果CheckBox是选中状态则显示两个graph     
	SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
	DisplayPanel(hGraphDispPanel);
}

static void DispGraphSelectCheckBox(void)
{
	//int val=0;
	if(graphDispSelect==DISP_SINGLE_GRAPH)
	{
		SetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, 0);
	}
	else{
		SetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, 1);
	 
	}
	SetPanelPos(hGraphSelectPanel, 177, 1450);  
	SetPanelSize(hGraphSelectPanel, 26, 140);      
 	DisplayPanel(hGraphSelectPanel);
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

static void SaveGraphs(int control,char path[])
{
	GetPanelDisplayBitmap (hGraphDispPanel, VAL_FULL_PANEL,VAL_ENTIRE_OBJECT, &nBitmapID);		//截取整个屏幕
	SaveBitmapToJPEGFile (nBitmapID, path, JPEG_INTERLACE, 100);
	DiscardBitmap (nBitmapID);
	
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

char  ToNumberSystem(int tmp)
{
    char str;
    str = 65 + (char)tmp - 1;		//对应的ASCII码		   A==65     tmp = column % 26
    return str;
}

void Reverse(char strs[],char str[],int row)
{
	int i, j;
	i = 0;
	j = strlen(str)-1;
	while (i < j)
	{
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	sprintf(strs,"%s%s%d","A1:",str,row);    
}

static void SaveSheet(char path[])
{
	int row,column;
	char strs[80];
	static ExcelObj_App               ExcelAppHandle = 0;       
	static ExcelObj_Workbooks         ExcelWorkbooksHandle = 0; 
	static ExcelObj_Workbook          ExcelWorkbookHandle = 0;  
	static ExcelObj_Sheets            ExcelSheetsHandle = 0;    
	static ExcelObj_Worksheet         ExcelWorksheetHandle = 0;
	GetNumTableRows (hTablePanel,TABLE_DISTABLE,&row);
	GetNumTableColumns (hTablePanel,TABLE_DISTABLE,&column);
	int tmp;
	char mydata[1000];
	int k=0;
	while (column)					//将列int型转换为 对应的ASCII码 在转为int 计算 最后转为26进制显示
	{
		tmp = column;
		tmp = column % 26;	   
		mydata[k++] = ToNumberSystem(tmp);
		column = column / 26;
	}
	mydata[k] = '\0';
    Reverse(strs,mydata,row); 
	Excel_NewApp (NULL, 1, LOCALE_NEUTRAL, 0, &ExcelAppHandle);	  //create a new Application object, and obtain a handle to the object.
	Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppWorkbooks, CAVT_OBJHANDLE, &ExcelWorkbooksHandle);
	Excel_WorkbooksAdd (ExcelWorkbooksHandle, NULL, CA_DEFAULT_VAL,&ExcelWorkbookHandle);
	Excel_GetProperty (ExcelAppHandle, NULL, Excel_AppSheets,CAVT_OBJHANDLE, &ExcelSheetsHandle);
	Excel_SheetsItem (ExcelSheetsHandle, NULL, CA_VariantInt(1),&ExcelWorksheetHandle);
	Excel_WorksheetActivate (ExcelWorksheetHandle, NULL);	 
	ExcelRpt_WriteDataFromTableControl (ExcelWorksheetHandle, strs, hTablePanel, TABLE_DISTABLE);	//write data from table control
	ExcelRpt_WorkbookSave (ExcelWorkbookHandle, sheetSavePath,ExRConst_DefaultFileFormat );   //ExRConst_Excel2						 ExRConst_DefaultFileFormat
	Excel_AppQuit (ExcelAppHandle, NULL);
	CA_DiscardObjHandle(ExcelAppHandle);
	CA_DiscardObjHandle(ExcelWorkbooksHandle); 
	CA_DiscardObjHandle(ExcelWorkbookHandle); 
	CA_DiscardObjHandle(ExcelSheetsHandle); 
	CA_DiscardObjHandle(ExcelWorksheetHandle); 
}

int CVICALLBACK TableCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)   //点击table图标切换到table面板 
{
	switch(event){
		case EVENT_LEFT_CLICK:
			    DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico");
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico"); 
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 

			break;
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table_pressed.ico");
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
		case EVENT_LEFT_CLICK_UP:
				DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");  
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
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
				GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
				if(val)
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				else
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico"); 
			break;
	}	
	return 0;
}

int CVICALLBACK GraphSelectCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{  
	if(event == EVENT_COMMIT)
	{      	
		HidePanel(hGraphSelectPanel); 
		int val;
	  	GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
	    if(val)
		{	
		    DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
			DispDoubleGraph();
			graphDispSelect=DISP_DOUBLE_GRAPH;
		}
		else
		{   
			DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
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
			DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph.ico");
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\SaveData_pressed.ico"); 
			InstallPopup(hSaveDataPanel);
			break;
	}	
	return 0;
}

int CVICALLBACK ExitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	if (event == EVENT_COMMIT)
	{
		RemovePopup(hSaveDataPanel);  	//移除、关闭savedata面板 
		DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\SaveData.ico");
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
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath); 
			if(graph1SavePath[0]=='\0')
				MessagePopup ("Message", "Please select a valod plot");
			else
			{
				InstallPopup(hSaveDataPanel);  
				SaveGraphs(GRAPHDISP_GRAPH1,graph1SavePath);
				HidePanel(hSaveDataPanel);
				MessagePopup ("Tips", "Saved successfully");
				RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			}
			break;
	}
	return 0;
}

int CVICALLBACK SaveAllCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, SAVEDATA_GRAPH2PATH, graph2SavePath);   
			GetCtrlVal(panel, SAVEDATA_GRAPH1PATH, graph1SavePath);  
			GetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath); 
			if((sheetSavePath[0]=='\0') || (graph1SavePath[0]=='\0') ||(graph2SavePath[0]=='\0') )
				 MessagePopup ("Message", "Please select a valod plot");   
			else
			{
				if(sheet == 1 && graph1==1 && graph2 ==1)
				{
					if(graphDispSelect==DISP_DOUBLE_GRAPH)	   //保存graph2时只有在选中双图模式才能
					{   
						InstallPopup(hSaveDataPanel);    
						SaveSheet(sheetSavePath); 
						SaveGraphs(GRAPHDISP_GRAPH1,graph1SavePath); 
						SaveGraphs(SAVEDATA_GRAPH2PATH,graph2SavePath);
						HidePanel(hSaveDataPanel);
						MessagePopup ("Tips", " successfully");
						RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
						DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
					} 
					else
						MessagePopup ("Message", " Please select the 'Double Graph' mode.");  
				  }
				else if(sheet==1 && graph1==1)
				{   
					InstallPopup(hSaveDataPanel);     
					SaveSheet(sheetSavePath); 
					SaveGraphs(GRAPHDISP_GRAPH1,graph1SavePath); 
					HidePanel(hSaveDataPanel);
					MessagePopup ("Tips", " successfully");  
					RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
					DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
				}
				else if(sheet==1 && graph2==1)			//保存graph2时默认保存两张图到一张图片上
				{
					if(graphDispSelect==DISP_DOUBLE_GRAPH)
					{  
						InstallPopup(hSaveDataPanel);                   
						SaveSheet(sheetSavePath); 
						SaveGraphs(SAVEDATA_GRAPH2PATH,graph2SavePath); 
						HidePanel(hSaveDataPanel);
					    MessagePopup ("Tips", " successfully");
						RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
						DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
					} 
					else
						MessagePopup ("Message", " Please select the 'Double Graph' mode.");  
				}
				else if(graph1==1 && graph2==1)
				{
					if(graphDispSelect==DISP_DOUBLE_GRAPH)
					{
						InstallPopup(hSaveDataPanel);  
						SaveGraphs(GRAPHDISP_GRAPH1,graph1SavePath); 
						SaveGraphs(SAVEDATA_GRAPH2PATH,graph2SavePath); 
						HidePanel(hSaveDataPanel);
					    MessagePopup ("Tips", " successfully");  
						RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
						DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
					}
					else
						MessagePopup ("Message", " Please select the 'Double Graph' mode.");  
				 }
	 		   DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");  
		}
		break;
	}
	return 0;
}

int CVICALLBACK SaveSheetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{									          
		case EVENT_LEFT_CLICK_UP:
			GetCtrlVal(panel, SAVEDATA_SHEETPATH, sheetSavePath);  
			if(sheetSavePath[0]=='\0')
				MessagePopup ("Message", "Please select a valod plot"); 
			else
			{
				InstallPopup(hSaveDataPanel);
				SaveSheet(sheetSavePath);
				HidePanel(hSaveDataPanel);
				MessagePopup ("Tips", "successfully");
				RemovePopup(hSaveDataPanel);  	 //移除、关闭savedata面板
				DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			}
			break;
	}
   return 0;
}

int CVICALLBACK SaveDatePanelCallback (int panel, int event, void *callbackData,
									   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			RemovePopup(hSaveDataPanel);
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");     
			break;
	}
	return 0;
}
