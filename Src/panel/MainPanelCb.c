//==============================================================================
//
// Title:		MainPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <rs232.h>
#include "MainPanelCb.h"
#include <userint.h>
#include "MainPanel.h"
#include "IMP.h"
//==============================================================================
// Constants
static char configSavePath[512]={0};
static int numOfCurve=0;
//==============================================================================
// macro define
#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色
#define BGCOLOR 	                      0xFFFFFF
#define SEARCHCOLOR                       0xA8BFCB     //不可用颜色
#define MEASURE_DEV_ADDR                  0x00 	      //设备地址默认为OXOO
//==============================================================================
// Extern global variables

//==============================================================================
// Static functions
int abnmDCThreadFlag = 0; 
//==============================================================================
// Global variables
GraphTypeDef Graph;
int TimerID;
CmtThreadFunctionID  abnmDCThreadId; 
FileLableTypeDef *pFileLable[64];									//存所有FileLable的指针，最多只能加载一个文件夹下的64个文件
PrjHandleTypeDef SingleProject[64];

char table_title_IT[11][20]  ={ "t(s)","I(A)","Temp(℃)","Hum(%RH)","Press(Pa)"}; 
char table_title_VT[11][20]  ={ "t(s)","V(v)","Temp(℃)","Hum(%RH)","Press(Pa)"};
//======================================================================================
// Global functions

//======================================================================================
//   MAIN_PANEL_Callback
static void InitSingleProject(PrjHandleTypeDef *pSingleProject)
{
	int i;
	for(i=0;i<64;i++)
	{
		(pSingleProject+i)->index=-1;	
	}
}
//========================================================================================
 static void DispRuntime(int display)   //结果显示面板上时间控件的显示
{ 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_SAMPLETIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME_UNIT,ATTR_VISIBLE,display);
}
//=========================================================================================
//========================================================================================
 static void DispOHM(int display)    //结果显示面板上电阻控件的显示
{ 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_OHM,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_OHM_UNIT,ATTR_VISIBLE,display); 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TXT_R,ATTR_VISIBLE,display);
}
//=========================================================================================
//========================================================================================
 static void DispId(int display)	 //结果显示面板上电流控件的显示
{ 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_IDS,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_ID_UNIT,ATTR_VISIBLE,display); 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TXT_IDS,ATTR_VISIBLE,display);
	
}
//=========================================================================================
int CVICALLBACK MAIN_PANEL_CallBack (int panel, int event, void *callbackData,
									 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
		    	SaveSystemClose(0);  //软件正常关闭状态为0
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}
//==========================================================================================================
static void RunActive()								//激活Run控件
{
	int val;													   //检查Box的值
	int expType;												  //实验类型
	GetActiveTreeItem (hExpListPanel, EXP_LIST_LISTBOX_2, &expType);  //获取实验类型  
	TestPara.testMode=(enum TestMode)expType;              	   //赋值给枚举的实验类型
    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);	  //获取Box的值
 	SetPanelPos(hResultMenuPanel, 105, 305);  
 	DisplayPanel(hResultMenuPanel); 
	SetPanelPos(hResultDispPanel, 105, 1600);
	DisplayPanel(hResultDispPanel);
	SetPanelPos(hEnvironmentPanel, 607, 1600);
	DisplayPanel(hEnvironmentPanel);
	DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");   //,Analyze图标改变，其它两个正常状态
	DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
	DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");	
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);				//当鼠标释放时, 禁用开始按钮      
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       		//恢复 停止按钮
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        		//禁用 保存按钮
	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
	DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
	DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,1);//运行过程中禁止设置曲线属性   
    if(val) //如果CheckBox是选中状态则显示两个graph
	{	
    	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
		DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico");                          
		DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");              
		SetPanelPos(hGraphDispPanel, 177, 305);  
		SetCtrlAttribute (hGraphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400);      
		SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
	}
	else
	{   	
		DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//进入Analyze默认到graph图标
		DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
		DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
		SetPanelPos(hGraphDispPanel, 177, 305);  
		SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 750);
		SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
	}
	DisplayPanel(hGraphDispPanel);     
	switch(TestPara.testMode)
	{
		case IT:
			DispId(1);
			DispRuntime(1);
			DispOHM(1);
			break;
		case LSV:
		case TAFEL: 
		case CV:
		case SV:
		case NPV:
		case DNPV:
		case DPV:
		case SWV:
			DispId(0);
			DispRuntime(1);
			DispOHM(1);
			break;
		case IMP:
			DispId(1);
			DispRuntime(0);
			DispOHM(0);
			SetCtrlVal (hResultDispPanel, RESULTDISP_TEXTMSG, "real");
			SetCtrlVal (hResultDispPanel, RESULTDISP_TEXTMSG_3, "");
			SetCtrlVal (hResultDispPanel, RESULTDISP_TXT_IDS, "imag");
			SetCtrlVal (hResultDispPanel, RESULTDISP_ID_UNIT, "");
			break;
	}
	FlushInQ(measureComPort);	   												//Clear input and output buffer,在测试开始之前还应该清除一次
	FlushOutQ(measureComPort);
}
//====================================================================================================
 int CVICALLBACK AbnmDCThreadFunction (void *functionData)
{ 
	while(abnmDCThreadFlag == 1)
	{
		if(Graph1.pCurveArray->numOfPlotDots > 0) 
		{
		    WriteAndSaveExcel(hTablePanel, TABLE_DISTABLE);
		}
	}
	return 0;
}

//==========================================================================================================  
int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
    int expType;
	int graphIndex=0;															//currently only deal with one graph circumstance
	int numOfDots=0;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			RunActive();
			abnmDCThreadFlag = 0;      //异常情况下的数据缓存线程标志位 
			GraphDeinit(&Graph1);	//内存释放在画图之后，如果在画图之前释放导致错误
			Graph1.plotCurveIndex=0;  //每次实验开始之前初始化CurveIndex
			measureUartFlag=1;	//轮询标志为1时开始查询
			impCloseFlag = 1;  //imp实验开始标志位
			Table_ATTR.columnWidth= 90;  												//列宽
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1); 		
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);					//每个实验运行之前清除上一个实验的table数据  
			DeleteGraphPlot (hGraphDispPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); 	//清空曲线图上的所有曲线
			DeleteGraphAnnotation (hGraphDispPanel, GRAPHDISP_GRAPH1,-1 );                  //清空上个实验曲线注释
			SetCtrlAttribute(hGraphDispPanel,GRAPHDISP_GRAPH2,ATTR_ENABLE_ZOOM_AND_PAN,1);	//使能控件的缩放和拖动
			GetActiveTreeItem (hExpListPanel, EXP_LIST_LISTBOX_2, &expType);  //获取实验类型   
			TestPara.testMode=(enum TestMode)expType;	//赋值给枚举的实验类型
			j = 1;
			pointInFlag	 = 0;
			totalNum = 0;
			ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf);	//send config to instrument via UART 
			numOfCurve=1;
			switch(TestPara.testMode)
			{
				case IT:
				numOfDots=(TestPara.runTime/TestPara.timeStep)/TestPara.sampleNumber;//总点数       
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots;
				rows = 2;
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");     //设置Y坐标轴名字
				Table(table_title_IT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置x坐标轴名字
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。    
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case LSV:
			    numOfDots = ((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep)/TestPara.sampleNumber)+1;
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case CV:
			    numOfDots = ((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep)/TestPara.sampleNumber) + (((abs(TestPara.start-TestPara.stop)/TestPara.voltageStep)/TestPara.sampleNumber) * (TestPara.sweepSegments-1)) + 1;   
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case TAFEL:
		    	numOfDots = (((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep) * TestPara.sweepSegments) + (TestPara.holdTime/(TestPara.voltageStep/TestPara.sampleRate)))/TestPara.sampleNumber; 
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case SV:
				numOfDots = ((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep) * TestPara.pluseWidth * TestPara.sweepSegments) / TestPara.timeStep + 1;  
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case NPV:
				numOfDots = (abs(TestPara.init-TestPara.stop) * TestPara.plusePeriod)/TestPara.timeStep;  
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case DPV:
				numOfDots = (abs(TestPara.init-TestPara.stop) * TestPara.plusePeriod)/TestPara.timeStep;  
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case DNPV:
				numOfDots = (abs(TestPara.init-TestPara.stop) * TestPara.plusePeriod)/TestPara.timeStep;
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case SWV:
				numOfDots = abs(TestPara.init-TestPara.stop)/TestPara.frequency/TestPara.timeStep;
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //设置坐标轴
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性 
					break;
				case IMP:
				numOfDots=TestPara.points_000001_00001hz+TestPara.points_00001_0001hz+TestPara.points_0001_001hz+TestPara.points_001_01hz+TestPara.points_01_1hz
						  +TestPara.points_1_10hz+TestPara.cycle_10_100hz+TestPara.cycle_100_1Khz+TestPara.points_1k_10Khz+TestPara.points_10k_100Khz+TestPara.points_100k_1Mhz;//总点数       
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //初始化图
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph2); //初始化图
				switch(TestPara.impDrawingType)
				{
					case 0:
						Graph1.pCurveArray->numOfTotalDots = numOfDots;
						Graph1.pCurveArray->realNum = -10;
						Graph1.pGraphAttr->xAxisHead=-5;
						Graph1.pGraphAttr->xAxisTail=0;
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "imag");     //设置Y坐标轴名字
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "real");	  //设置x坐标轴名字
						break;
					case 1:
						Graph1.pCurveArray->numOfTotalDots = numOfDots;
						Graph1.pCurveArray->realNum = 10;
						Graph1.pGraphAttr->xAxisHead=10;
						Graph1.pGraphAttr->xAxisTail=0;
						Graph2.pCurveArray->numOfTotalDots = numOfDots;
						Graph2.pCurveArray->realNum = 10;
						Graph2.pGraphAttr->xAxisHead=10;
						Graph2.pGraphAttr->xAxisTail=0;
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "lgf");     //设置X坐标轴名字
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "模的对数");//设置Y坐标轴名字
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_XNAME, "lgf");     //设置X坐标轴名字
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_YNAME, "相位角");	  //设置Y坐标轴名字
						SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
						Graph2.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph2.graphIndex,Graph2.plotCurveIndex); 		//得到曲线的属性
						break;
				}
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //设置缩放模式和图形轴的范围或缩放模式和条形图y轴的范围。 
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//得到曲线的属性  
				break;
			}
			Delay(0.2);		   //在设置和运行命令之间给下位机0.2秒处理 
			ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf); 	//send RUN command to instrument via UART 
			double temp=((double)TestPara.timeStep)/1000;
			if(temp<0.3) temp=0.3;
			TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);						//Create Asynchronous (Timer time interval according to sample interval, continue generating evernt, enabled, callback function name, passing no pointer) 

	       /* abnmDCThreadFlag = 1;														 //异常情况下的数据缓存功能标志位
			CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, AbnmDCThreadFunction, NULL, &abnmDCThreadId); //开辟新的线程*/
	}
 return 0;
}
//=====================================================================================================================
int CVICALLBACK StopCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
			 Delay(0.5);                      //等待异常情况下的数据缓存完成
			 abnmDCThreadFlag = 0;				//异常情况下的数据缓存标志位置0
			 measureUartFlag=0;			//轮询标志位置0
			 DiscardAsyncTimer(TimerID);	//删除异步定时器事件
			 FlushInQ(measureComPort);	   										//Clear input and output buffer,在测试开始之前还应该清楚一次
			 FlushOutQ(measureComPort);
			 Delay(0.1);
			 ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART
			 GraphDeinit(&Graph);
			 numOfCurve = 0;  //曲线条数回复0
			 
		  	 SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
		     SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
			 SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
			 SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0); //恢复曲线属性设置 
			break;
	}
	return 0;
}
//===================================================================================================================
int CVICALLBACK SaveCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
			DisplayImageFile (hMainPanel, MAIN_PANEL_SAVE, "Resource\\Save_pressed.ico");
			if(FileSelectPopup("C:\\SINOAGG\\SA5101\\Users\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 0, 1, 1,  configSavePath)>0)
				SaveConfigToFile(configSavePath);
			DisplayImageFile (hMainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");        
			break;
	}
	return 0;
}
//======================================================================================================================
//SelectCallback
int CVICALLBACK SelectCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //当Select被鼠标左键点击时,Select图标改变，其它两个正常状态 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			HidePanel(hResultMenuPanel);
			HidePanel(hEnvironmentPanel);
			break;
	}
	return 0;
}
//=======================================================================================================================
//Configure_Callback
int CVICALLBACK ConfigureCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //当Configure被鼠标左键点击时,Configure图标改变，其它两个正常状态 
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
		   	break; 
	}
	return 0;
}
//==============================================================================================================================
static void DispResultMenu(void)
{
	SetPanelPos(hResultMenuPanel, 105, 305);  
	DisplayPanel(hResultMenuPanel);
}
//==============================================================================================================================  
static void DispResultNumber(void)
{
	SetPanelPos(hResultDispPanel, 105, 1600);
	DisplayPanel(hResultDispPanel);
}
//==============================================================================================================================  
static void DispEnvironmentCfg(void)
{
	SetPanelPos(hEnvironmentPanel, 607, 1600);
	DisplayPanel(hEnvironmentPanel);
}
//==============================================================================================================================  
//   Analyze_Callback
int CVICALLBACK AnalyzeCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //当Analyze被鼠标左键点击时,Analyze图标改变，其它两个正常状态，
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
			int val;
	  	    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
	        if(val)
			{	
		    	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				SetCtrlAttribute (hGraphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //如果CheckBox是选中状态则显示两个graph     
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_VISIBLE,1); 
			}
			else
			{   	
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//进入Analyze默认到graph图标
				SetCtrlAttribute (hGraphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 750);
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_VISIBLE, 1);             
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
			}
			DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico");                          
			DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico"); 
			DisplayPanel(hGraphDispPanel);               
			DispResultMenu(); 
			DispEnvironmentCfg();
			DispResultNumber();
			break;
	}
	return 0;
}
//===================================================
//弹出projects内容
int CVICALLBACK ProjectCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hPrjPanel,150,300);
			InstallPopup (hPrjPanel);
		 	SetCtrlAttribute(hPrjPanel,PROPANEL_PIC_OPENPRJ , ATTR_DIMMED, 1);
			SetCtrlAttribute(hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_TEXT_BGCOLOR,SEARCHCOLOR);
			SetCtrlAttribute(hPrjPanel,PROPANEL_TXT_OPENPRJ , ATTR_DIMMED, 1);
			SetPanelPos(hPrjListPanel,90,0);
			DisplayPanel(hPrjListPanel); 
			LoadAllProject(ProjectSavePath);
			break;
	}	 
	return 0;
}
//===================================================
//SettingCallback
int CVICALLBACK SettingsCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			InstallPopup (hSettingsPanel);    //弹出hSettingsPanel 
			SetPanelPos(hSettingsPrjPanel, 5, 170);
			DisplayPanel(hSettingsPrjPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsAboutPanel);
			break;
	}
	return 0;
}
//===================================================
//SaveConfigToFile
static int SaveConfigToFile(char* pConfigSavePath)
{
	FILE * fp = NULL;							//表示打开的文件
	fp = fopen(pConfigSavePath, "w");
	if(fp == NULL)
	{
		MessagePopup ("Error", "Invalid Path, please select path to save configurations.");
		if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\Users\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePath)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char description[maxCommentSize];
		PromptPopup("Message", "Please enter description for this configuration:", description, maxCommentSize-1);
		//fprintf(fp, "Date:%s	Time:%s\r\n", DateStr(), TimeStr());
		SaveAllPanelState(pConfigSavePath);		//保存所有面板的数据 
		fp = fopen(pConfigSavePath, "a+");
		fprintf(fp, "\r\n%-61s\r\n", description);		//左对齐打满64字符
		fclose(fp);//关闭文件
	}
	return 0;
}
//===================================================
// SaveAllPanelState
static int SaveAllPanelState(char* pConfigSavePath)
{															  
	SavePanelState(hIT_Panel, pConfigSavePath, 1);						
	SavePanelState(hLSV_Panel, pConfigSavePath, 2);						
	SavePanelState(hCV_Panel, pConfigSavePath, 3);
	SavePanelState(hTAFEL_Panel, pConfigSavePath, 4);
	SavePanelState(hSV_Panel, pConfigSavePath, 5);						
	SavePanelState(hNPV_Panel, pConfigSavePath, 6);						
	SavePanelState(hDPV_Panel, pConfigSavePath, 7);
	SavePanelState(hDNPV_Panel, pConfigSavePath, 8);
	SavePanelState(hSWV_Panel, pConfigSavePath, 9);
	SavePanelState(hIMP_Panel, pConfigSavePath, 10);
	SavePanelState(hBasicSamplePanel, pConfigSavePath, 11);
	SavePanelState(hAdvanceSamplePanel, pConfigSavePath, 12);
	SavePanelState(hEnvCfgPanel, pConfigSavePath, 13);
	SavePanelState(hSettingsPrjPanel, pConfigSavePath, 14);
	SavePanelState(hSettingsGraphPanel, pConfigSavePath, 15);
	SavePanelState(hExpListPanel, pConfigSavePath, 16);
	return 0;
}
//=================================================== 
//LoadAndDispPrj
static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char index)						//index为prj所在位置排序
{
	int hSinglePrjPanel;
	if ((hSinglePrjPanel = LoadPanel (hPrjListPanel, "ProjectPanel.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_NAME, pFileLable->FileName);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DATE, pFileLable->FileDate);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_TIME, pFileLable->FileTime);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DESC, pFileLable->FileDesc);
	SetPanelPos(hSinglePrjPanel, index*117, -10);
	SetPanelSize(hSinglePrjPanel, 115, 1425);
	DisplayPanel(hSinglePrjPanel);
	return hSinglePrjPanel;
}
//===================================================
//LoadAllProject
static int LoadAllProject(char* pProjectSavePath)
{
	char tempFileName[512];
	char tempFilePath[512];
	char index=0;
	char tempPathToSearch[512];
	
	InitSingleProject(SingleProject);
	
	sprintf(tempPathToSearch, "%s%s", pProjectSavePath, "\\*.sac");
	if(0==GetFirstFile(tempPathToSearch, 1, 1, 1, 1, 1, 0, tempFileName))		//如果第一个文件获取成功
	{
		sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
		pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
		InitFileLable(pFileLable[index], tempFilePath); 				//读文件时间和文件名称及description，并展示
		SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
		SingleProject[index].index=index;
		index++;
		
		while(GetNextFile(tempFileName)==0)								//如果读取正确，持续读取
		{
			sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
			pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
			InitFileLable(pFileLable[index], tempFilePath); //读文件时间和文件名称及description
			SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
			SingleProject[index].index=index;
			index++;
		}
	}
	return 0;
}

int CVICALLBACK HardwareTestCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	const char IDquery[] = {0xAA, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						   0x00, 0x20};
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
				unsigned char i;
				char USART_RX_Buffer[10];   //接收
				int error,strLen;
				for(i = 1; i<=QUERY_PORT_NUM; i++)
				{
					SetBreakOnLibraryErrors (0);
					error = OpenComConfig(i, "", BAUDRATE, 0, 8, 1, SA51_UART_TX_LEN, SA51_UART_RX_LEN);  //设置和打开串口 
					if(error<0 )
					{
					}else
					{	
						ComWrt(i, IDquery, SA51_UART_TX_LEN);							//发送查询指令
						Delay(4);
						strLen = GetInQLen (i);
						ComRd (i,USART_RX_Buffer,strLen);
						if((USART_RX_Buffer[1]== 0x61) && (USART_RX_Buffer[2] == 0x01))
						{
							measureComPort = i;						
							SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//无硬件交互 
							FlushInQ(measureComPort);	   				//Clear input and output buffer
							FlushOutQ(measureComPort);
							if(CheckPortStatus(measureComPort, SA51_UART_RX_LEN, MeasureComCallback)<0)
							{
								uartStatusFlag=0;															//串口打开失败
								MessagePopup("Error","Failed to open the serial port of electrical measuring equipment"); //要想打开软件，需要禁用此串口的操作命令
							}
							else 
							{
								uartStatusFlag=1;															//串口打开成功  
							}
							break;
						}
						CloseCom(i);
					}
				}
			break;
	}
	return 0;
}

int CVICALLBACK PrintCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			DisplayImageFile (hMainPanel, MAIN_PANEL_PRINT, "Resource\\print_pressed.ico");  
			PrintPanel (hMainPanel, "", 1, VAL_VISIBLE_AREA, 1);
			DisplayImageFile (hMainPanel, MAIN_PANEL_PRINT, "Resource\\print.ico");    
			break;
	}
	return 0;
}
