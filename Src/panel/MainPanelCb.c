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
#define VAL_TEXTBG                        0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED                0x065279L    //��ѡ�б���ɫ
#define BGCOLOR 	                      0xFFFFFF
#define SEARCHCOLOR                       0xA8BFCB     //��������ɫ
#define MEASURE_DEV_ADDR                  0x00 	      //�豸��ַĬ��ΪOXOO
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
FileLableTypeDef *pFileLable[64];									//������FileLable��ָ�룬���ֻ�ܼ���һ���ļ����µ�64���ļ�
PrjHandleTypeDef SingleProject[64];

char table_title_IT[11][20]  ={ "t(s)","I(A)","Temp(��)","Hum(%RH)","Press(Pa)"}; 
char table_title_VT[11][20]  ={ "t(s)","V(v)","Temp(��)","Hum(%RH)","Press(Pa)"};
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
 static void DispRuntime(int display)   //�����ʾ�����ʱ��ؼ�����ʾ
{ 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_SAMPLETIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TIME_UNIT,ATTR_VISIBLE,display);
}
//=========================================================================================
//========================================================================================
 static void DispOHM(int display)    //�����ʾ����ϵ���ؼ�����ʾ
{ 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_OHM,ATTR_VISIBLE,display);
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_OHM_UNIT,ATTR_VISIBLE,display); 
	SetCtrlAttribute(hResultDispPanel,RESULTDISP_TXT_R,ATTR_VISIBLE,display);
}
//=========================================================================================
//========================================================================================
 static void DispId(int display)	 //�����ʾ����ϵ����ؼ�����ʾ
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
		    	SaveSystemClose(0);  //��������ر�״̬Ϊ0
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}
//==========================================================================================================
static void RunActive()								//����Run�ؼ�
{
	int val;													   //���Box��ֵ
	int expType;												  //ʵ������
	GetActiveTreeItem (hExpListPanel, EXP_LIST_LISTBOX_2, &expType);  //��ȡʵ������  
	TestPara.testMode=(enum TestMode)expType;              	   //��ֵ��ö�ٵ�ʵ������
    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);	  //��ȡBox��ֵ
 	SetPanelPos(hResultMenuPanel, 105, 305);  
 	DisplayPanel(hResultMenuPanel); 
	SetPanelPos(hResultDispPanel, 105, 1600);
	DisplayPanel(hResultDispPanel);
	SetPanelPos(hEnvironmentPanel, 607, 1600);
	DisplayPanel(hEnvironmentPanel);
	DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");   //,Analyzeͼ��ı䣬������������״̬
	DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
	DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");	
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);				//������ͷ�ʱ, ���ÿ�ʼ��ť      
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       		//�ָ� ֹͣ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        		//���� ���水ť
	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");
	DisplayImageFile (hResultMenuPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
	DisplayImageFile (hResultMenuPanel, RESULTMENU_SAVE, "Resource\\saveData.ico");
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,1);//���й����н�ֹ������������   
    if(val) //���CheckBox��ѡ��״̬����ʾ����graph
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
		DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//����AnalyzeĬ�ϵ�graphͼ��
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
	FlushInQ(measureComPort);	   												//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
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
			abnmDCThreadFlag = 0;      //�쳣����µ����ݻ����̱߳�־λ 
			GraphDeinit(&Graph1);	//�ڴ��ͷ��ڻ�ͼ֮������ڻ�ͼ֮ǰ�ͷŵ��´���
			Graph1.plotCurveIndex=0;  //ÿ��ʵ�鿪ʼ֮ǰ��ʼ��CurveIndex
			measureUartFlag=1;	//��ѯ��־Ϊ1ʱ��ʼ��ѯ
			impCloseFlag = 1;  //impʵ�鿪ʼ��־λ
			Table_ATTR.columnWidth= 90;  												//�п�
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1); 		
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);					//ÿ��ʵ������֮ǰ�����һ��ʵ���table����  
			DeleteGraphPlot (hGraphDispPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); 	//�������ͼ�ϵ���������
			DeleteGraphAnnotation (hGraphDispPanel, GRAPHDISP_GRAPH1,-1 );                  //����ϸ�ʵ������ע��
			SetCtrlAttribute(hGraphDispPanel,GRAPHDISP_GRAPH2,ATTR_ENABLE_ZOOM_AND_PAN,1);	//ʹ�ܿؼ������ź��϶�
			GetActiveTreeItem (hExpListPanel, EXP_LIST_LISTBOX_2, &expType);  //��ȡʵ������   
			TestPara.testMode=(enum TestMode)expType;	//��ֵ��ö�ٵ�ʵ������
			j = 1;
			pointInFlag	 = 0;
			totalNum = 0;
			ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf);	//send config to instrument via UART 
			numOfCurve=1;
			switch(TestPara.testMode)
			{
				case IT:
				numOfDots=(TestPara.runTime/TestPara.timeStep)/TestPara.sampleNumber;//�ܵ���       
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots;
				rows = 2;
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");     //����Y����������
				Table(table_title_IT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "I");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����x����������
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��    
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case LSV:
			    numOfDots = ((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep)/TestPara.sampleNumber)+1;
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case CV:
			    numOfDots = ((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep)/TestPara.sampleNumber) + (((abs(TestPara.start-TestPara.stop)/TestPara.voltageStep)/TestPara.sampleNumber) * (TestPara.sweepSegments-1)) + 1;   
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case TAFEL:
		    	numOfDots = (((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep) * TestPara.sweepSegments) + (TestPara.holdTime/(TestPara.voltageStep/TestPara.sampleRate)))/TestPara.sampleNumber; 
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case SV:
				numOfDots = ((abs(TestPara.init-TestPara.stop)/TestPara.voltageStep) * TestPara.pluseWidth * TestPara.sweepSegments) / TestPara.timeStep + 1;  
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case NPV:
				numOfDots = (abs(TestPara.init-TestPara.stop) * TestPara.plusePeriod)/TestPara.timeStep;  
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case DPV:
				numOfDots = (abs(TestPara.init-TestPara.stop) * TestPara.plusePeriod)/TestPara.timeStep;  
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case DNPV:
				numOfDots = (abs(TestPara.init-TestPara.stop) * TestPara.plusePeriod)/TestPara.timeStep;
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case SWV:
				numOfDots = abs(TestPara.init-TestPara.stop)/TestPara.frequency/TestPara.timeStep;
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ 
				Graph1.pCurveArray->numOfTotalDots = numOfDots;
				Graph1.pCurveArray->time=0;
				Graph1.pGraphAttr->xAxisHead=0;
				Graph1.pGraphAttr->xAxisTail=10;
				Table_ATTR.column =5*numOfCurve ;          
				Table_ATTR.row =  numOfDots+1;
				rows = 2;
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ��
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");	  //����������
				Table(table_title_VT, Table_ATTR.column, Table_ATTR.columnWidth,Table_ATTR.row);   
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");
				SetCtrlAttribute (hResultDispPanel,RESULTDISP_TXT_IDS , ATTR_CTRL_VAL, "V");
				SetCtrlAttribute (hResultDispPanel, RESULTDISP_TXT_IDS, ATTR_LEFT, 95);
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ����� 
					break;
				case IMP:
				numOfDots=TestPara.points_000001_00001hz+TestPara.points_00001_0001hz+TestPara.points_0001_001hz+TestPara.points_001_01hz+TestPara.points_01_1hz
						  +TestPara.points_1_10hz+TestPara.cycle_10_100hz+TestPara.cycle_100_1Khz+TestPara.points_1k_10Khz+TestPara.points_10k_100Khz+TestPara.points_100k_1Mhz;//�ܵ���       
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph1); //��ʼ��ͼ
				GraphInit(hGraphDispPanel, graphIndex,numOfCurve,numOfDots+10,&Graph2); //��ʼ��ͼ
				switch(TestPara.impDrawingType)
				{
					case 0:
						Graph1.pCurveArray->numOfTotalDots = numOfDots;
						Graph1.pCurveArray->realNum = -10;
						Graph1.pGraphAttr->xAxisHead=-5;
						Graph1.pGraphAttr->xAxisTail=0;
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "imag");     //����Y����������
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "real");	  //����x����������
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
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "lgf");     //����X����������
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "ģ�Ķ���");//����Y����������
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_XNAME, "lgf");     //����X����������
						SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_YNAME, "��λ��");	  //����Y����������
						SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph2.pGraphAttr->xAxisHead,Graph2.pGraphAttr->xAxisTail); 
						Graph2.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph2.graphIndex,Graph2.plotCurveIndex); 		//�õ����ߵ�����
						break;
				}
				SetAxisScalingMode(hGraphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, Graph1.pGraphAttr->xAxisHead,Graph1.pGraphAttr->xAxisTail); //��������ģʽ��ͼ����ķ�Χ������ģʽ������ͼy��ķ�Χ�� 
				Graph1.pCurveArray->pCurveAttr = GetSettingsCurveAttr(Graph1.graphIndex,Graph1.plotCurveIndex); 		//�õ����ߵ�����  
				break;
			}
			Delay(0.2);		   //�����ú���������֮�����λ��0.2�봦�� 
			ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf); 	//send RUN command to instrument via UART 
			double temp=((double)TestPara.timeStep)/1000;
			if(temp<0.3) temp=0.3;
			TimerID = NewAsyncTimer(temp, -1, 1, TimerCallback, 0);						//Create Asynchronous (Timer time interval according to sample interval, continue generating evernt, enabled, callback function name, passing no pointer) 

	       /* abnmDCThreadFlag = 1;														 //�쳣����µ����ݻ��湦�ܱ�־λ
			CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, AbnmDCThreadFunction, NULL, &abnmDCThreadId); //�����µ��߳�*/
	}
 return 0;
}
//=====================================================================================================================
int CVICALLBACK StopCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
			 Delay(0.5);                      //�ȴ��쳣����µ����ݻ������
			 abnmDCThreadFlag = 0;				//�쳣����µ����ݻ����־λ��0
			 measureUartFlag=0;			//��ѯ��־λ��0
			 DiscardAsyncTimer(TimerID);	//ɾ���첽��ʱ���¼�
			 FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
			 FlushOutQ(measureComPort);
			 Delay(0.1);
			 ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART
			 GraphDeinit(&Graph);
			 numOfCurve = 0;  //���������ظ�0
			 
		  	 SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		     SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			 SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
			 SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0); //�ָ������������� 
			break;
	}
	return 0;
}
//===================================================================================================================
int CVICALLBACK SaveCallback (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
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
		case EVENT_LEFT_CLICK_UP:			    //��Select�����������ʱ,Selectͼ��ı䣬������������״̬ 
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
		case EVENT_LEFT_CLICK_UP:			    //��Configure�����������ʱ,Configureͼ��ı䣬������������״̬ 
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
		case EVENT_LEFT_CLICK_UP:			    //��Analyze�����������ʱ,Analyzeͼ��ı䣬������������״̬��
			DisplayImageFile (hMainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (hMainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (hMainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
			int val;
	  	    GetCtrlVal(hGraphSelectPanel, CHPANEL_CHECKBOX, &val);
	        if(val)
			{	
		    	DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\DoubleGraph.ico");
				SetCtrlAttribute (hGraphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 400); //���CheckBox��ѡ��״̬����ʾ����graph     
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 1);
				SetCtrlAttribute (hGraphDispPanel, GRAPHDISP_GRAPH1, ATTR_VISIBLE,1); 
			}
			else
			{   	
				DisplayImageFile (hResultMenuPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico");//����AnalyzeĬ�ϵ�graphͼ��
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
//����projects����
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
			InstallPopup (hSettingsPanel);    //����hSettingsPanel 
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
	FILE * fp = NULL;							//��ʾ�򿪵��ļ�
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
		SaveAllPanelState(pConfigSavePath);		//���������������� 
		fp = fopen(pConfigSavePath, "a+");
		fprintf(fp, "\r\n%-61s\r\n", description);		//��������64�ַ�
		fclose(fp);//�ر��ļ�
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
static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char index)						//indexΪprj����λ������
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
	if(0==GetFirstFile(tempPathToSearch, 1, 1, 1, 1, 1, 0, tempFileName))		//�����һ���ļ���ȡ�ɹ�
	{
		sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
		pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
		InitFileLable(pFileLable[index], tempFilePath); 				//���ļ�ʱ����ļ����Ƽ�description����չʾ
		SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
		SingleProject[index].index=index;
		index++;
		
		while(GetNextFile(tempFileName)==0)								//�����ȡ��ȷ��������ȡ
		{
			sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
			pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
			InitFileLable(pFileLable[index], tempFilePath); //���ļ�ʱ����ļ����Ƽ�description
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
				char USART_RX_Buffer[10];   //����
				int error,strLen;
				for(i = 1; i<=QUERY_PORT_NUM; i++)
				{
					SetBreakOnLibraryErrors (0);
					error = OpenComConfig(i, "", BAUDRATE, 0, 8, 1, SA51_UART_TX_LEN, SA51_UART_RX_LEN);  //���úʹ򿪴��� 
					if(error<0 )
					{
					}else
					{	
						ComWrt(i, IDquery, SA51_UART_TX_LEN);							//���Ͳ�ѯָ��
						Delay(4);
						strLen = GetInQLen (i);
						ComRd (i,USART_RX_Buffer,strLen);
						if((USART_RX_Buffer[1]== 0x61) && (USART_RX_Buffer[2] == 0x01))
						{
							measureComPort = i;						
							SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//��Ӳ������ 
							FlushInQ(measureComPort);	   				//Clear input and output buffer
							FlushOutQ(measureComPort);
							if(CheckPortStatus(measureComPort, SA51_UART_RX_LEN, MeasureComCallback)<0)
							{
								uartStatusFlag=0;															//���ڴ�ʧ��
								MessagePopup("Error","Failed to open the serial port of electrical measuring equipment"); //Ҫ����������Ҫ���ô˴��ڵĲ�������
							}
							else 
							{
								uartStatusFlag=1;															//���ڴ򿪳ɹ�  
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
