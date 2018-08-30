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
#include "MainPanelCb.h"

//==============================================================================
// Constants

//==============================================================================
// macro define

//==============================================================================
// Extern global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int TimerID;
int TimerID2;
int TimerID3;
Graph_TypeDef Graph;
//==============================================================================
// Global functions

//===================================================
//   MAIN_PANEL_Callback

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
			    ShutDownExcelCB(); 
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}

//===================================================
//   RunCallback

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
			
			SetPanelPos(resultPanel, 105, 305);  
	     	SetPanelSize(resultPanel, 70, 1285);      
 			DisplayPanel(resultPanel);  
			
			SetPanelPos(graphDispPanel, 175, 305);  
	     	SetPanelSize(graphDispPanel, 851, 1285);
			SetCtrlAttribute (graphDispPanel,GRAPHDISP_GRAPH1 , ATTR_HEIGHT, 680);
			SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH2, ATTR_VISIBLE, 0);
 			DisplayPanel(graphDispPanel);
			
			SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED,1);         //���� ��ʼ��ť      
		    SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED, 0);       //�ָ� ֹͣ��ť
	        SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED,1);        //���� ���水ť
			DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH1, -1, VAL_IMMEDIATE_DRAW); //�������ͼ�ϵ���������
			LaunchExcelCB();
			InitExcelCB (2, 3);
			if(comSelect)
			{
				MessagePopup ("Warning", "Instrument Unconnected");   //Lost serial Connection
			}
			else
			{
				int expType;
				int graphIndex=1;	//currently only deal with one graph circumstance
				int numOfCurve=1;
				int numOfTotalDots=0;
				if(GetCtrlVal(expListPanel, EXP_LIST_LISTBOX_2, &expType)<0)
					return -1;
				switch(expType)
				{
					case 1:
						GetC_vBasicCfg(cvBasicPanel);
						GetC_vAdvanceCfg(cvAdvancePanel);
						Send_cvcmd(CvCfg.cfgC_v_high,CvCfg.cfgC_v_low,CvCfg.cfgC_v_scanrate,
								   CvCfg.cfgC_v_sweepsegments);
						break;
					case 2:
						GetLsvCfg(lsvBasicPanel);
						Send_lsvcmd(LsvCfg.cfgLsv_final,LsvCfg.cfgLsv_Initial,LsvCfg.cfgLsv_scanrate);

						break;
					case 3:
						GetScvCfg(scvBasicPanel);
						send_scvcmd(ScvCfg.cfgScv_Initial,ScvCfg.cfgScv_Final,ScvCfg.cfgScv_Incr,
									ScvCfg.cfgScv_StepPeriods);

					case 9:
						 GetNpvCfg(npvBasicPanel);
						 Send_npvCmd(NpvCfg.cfgNpv_Initial,NpvCfg.cfgNpv_Final ,NpvCfg.cfgNpv_Pluse,NpvCfg.cfgNpv_Incr,NpvCfg.cfgNpv_SamplingWidth,
										  NpvCfg.cfgNpv_PluseWdith,NpvCfg.cfgNpv_PlusePeriods);
						break;
					case 11:
						// GetSwvCfg(swvPanel);
						// Send_swvCmd();
					break;
					case 12:
						 GetI_tCfg (itBasicPanel);		 //�Ӳ�����������ȡ�û��������
						 Delay(I_tCfg.cfgI_t_quiettime);  //��ֹʱ��
						 numOfTotalDots  = I_tCfg.cfgI_t_runtime / I_tCfg.cfgI_t_sampleinterval; //һ��Ҫ���ĵ���
						 i_tgraphInit(graphIndex, numOfCurve, numOfTotalDots, &Graph); 	// graph set up
						 InitTableCells (tablePanel,TABLE_TABLE,2,5);
			             if(I_tCfg.cfgI_t_currentrange == 0)
						 {
						   TimerID = NewAsyncTimer(I_tCfg.cfgI_t_sampleinterval,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer)  
						   TimerID2 = NewAsyncTimer(I_tCfg.cfgI_t_sampleinterval * 2,-1,1,TimerCallback2,0); //����һ�������λ������һ������
						 }
						 else
						 {
						   send_itcmd();
						   TimerID = NewAsyncTimer(I_tCfg.cfgI_t_sampleinterval,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer)       
						   TimerID3 = NewAsyncTimer(1,-1,1,TimerCallback3,0);	  //����һ�������λ��һֱ��������
						 }
						 break;
					default:
						break;
				}
			break;
	         }
	}
 return 0;
}


//===================================================
//   StopCallback

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ
		  	 SetCtrlAttribute (mainPanel, MAIN_PANEL_Stop, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		     SetCtrlAttribute (mainPanel, MAIN_PANEL_Run, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_Save, ATTR_DIMMED, 0);     //�ָ� ���水ť
			 
			 graphDeinit(&Graph);
			break;
	}
	return 0;
}

//===================================================
//   SaveCallback

int CVICALLBACK SaveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
			break;
		case EVENT_LEFT_CLICK:			    //��Save�����������ʱ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "Resource\\Save_pressed.ico");
			
			break;
			
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ  
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Save, "Resource\\Save.ico");

			break;
	}
	return 0;
}
//===================================================
//   SelectCallback

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //��Select�����������ʱ,Selectͼ��ı䣬������������״̬ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select_pressed.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze.ico");
			
			SetPanelPos(graphDispPanel, 105, 305);     //top left
			SetPanelSize(graphDispPanel, 921, 1285);   //height width   
			DisplayPanel(graphDispPanel);

			HidePanel(itBasicPanel);
			HidePanel(resultPanel);
			HidePanel(environmentPanel);
			break;
	
	}
	return 0;
}

//===================================================
//   Configure_Callback

int CVICALLBACK ConfigureCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //��Configure�����������ʱ,Configureͼ��ı䣬������������״̬ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze.ico");
			
			break;
		case EVENT_LEFT_CLICK:
			
			SetPanelPos(itBasicPanel, 105, 1592); //top   left
			SetPanelSize(itBasicPanel, 500, 308);// height  width
			DisplayPanel(itBasicPanel);
			
			SetPanelPos(environmentPanel, 605, 1592);
			SetPanelSize(environmentPanel, 421, 308);
			DisplayPanel(environmentPanel);
			break;
	}
	return 0;
}

//===================================================
//   Analyze_Callback

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
				
				SetPanelPos(resultPanel, 105, 305);  
		     	SetPanelSize(resultPanel, 70, 1285);      
	 			DisplayPanel(resultPanel);  
				
				

				SetPanelPos(graphDispPanel, 175, 305);  
		     	SetPanelSize(graphDispPanel, 842, 1285);      
	 			DisplayPanel(graphDispPanel);
			


			break;
 		case EVENT_LEFT_CLICK_UP:			    //��Analyze�����������ʱ,Analyzeͼ��ı䣬������������״̬�� 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_Select, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_Configure, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_Analyze, "Resource\\Analyze_pressed.ico");
		
			break;
			
			
	}
	return 0;
}

static int SaveConfigToFile(char* pConfigSavePath)
{
	FILE * fp = NULL;							//��ʾ�򿪵��ļ�
	fp = fopen(pConfigSavePath, "w");
	if(fp == NULL)
	{
		MessagePopup ("Error", "Invalid Path, please select path to save configurations.");
		if(FileSelectPopup ("C:\\SINOAGG\\SA6101\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePath)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char comment[maxCommentSize];
		//GetIdVdCfg(IdVdPanel);						//��ȡIdVd�������
		//GetIdVgCfg(IdVgPanel);						//��ȡIdVg�������
		//GetITCfg(hIT_Panel);
		//GetRTCfg(hRT_Panel);
		//GetSampleCfg(samplePanel);
		//GetEnvironmentCfg(hEnvCfgPanel);
		PromptPopup("Message", "Please enter comment for this configuration:", comment, maxCommentSize-1);
		fprintf(fp, "Date:%s	Time:%s\r\n", DateStr(), TimeStr());
		fprintf(fp, "Comment: %s", comment);
		
		fclose(fp);//�ر��ļ�
	}
	return 0;
	
}


int CVICALLBACK SettingsCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
	         InstallPopup (settingsPanel);    //����hSettingsPanel 

			SetPanelPos(settingsPanel, 5, 170);
			SetPanelSize(settingsPanel, 350, 650);
			DisplayPanel(settingsPanel);

			break;
	}
	return 0;
}

//����projects����
int CVICALLBACK ProjectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
		
			InstallPopup (prjPanel); 
			SetPanelPos(prjListPanel, 90, -10);
			SetPanelSize(prjListPanel, 115, 1300);
			DisplayPanel(prjListPanel);  
			break;
	}	 
	 
	return 0;
}
