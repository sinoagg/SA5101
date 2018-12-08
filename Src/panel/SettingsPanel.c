#include <windows.h>
#include "Settings.h"
#include <userint.h>
#include "LoadPanel.h"
#include "SettingsPanel.h"
#include "cvixml.h"
#include "progressbar.h"

#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色

CurveAttrTypeDef Graph1_CurveAttr1;
CurveAttrTypeDef Graph1_CurveAttr2;
CurveAttrTypeDef Graph1_CurveAttr3;
CurveAttrTypeDef Graph2_CurveAttr1;
CurveAttrTypeDef Graph2_CurveAttr2;
CurveAttrTypeDef Graph2_CurveAttr3;

char ProjectSavePath[512]="C:\\Sinoagg\\SA5101\\Users\\";	   //本地工作目录Dir

static int builtInTestFlag = 0;
static int ftp_handle = -1;
static int error; 
static char attrName[50];
static char getProjectDir[MAX_PATHNAME_LEN];
static char getProjectDirs[MAX_PATHNAME_LEN]; 
static char updateInfoPath[MAX_PATHNAME_LEN];
static char localInfoPath[MAX_PATHNAME_LEN]; 
static char updateSoftFilePath[MAX_PATHNAME_LEN];
static char updateHardFilePath[MAX_PATHNAME_LEN];

static char *serversSoftVersion = NULL;
static char *currentSoftVersion = NULL;
static char *serversUpdateVersion = NULL;
static char *currentUpdateVersion = NULL;
static char *serversHardVersion = NULL;
static char *currentHardVersion = NULL;

static CVIXMLDocument	hLoDocument = 0;
static CVIXMLDocument   hUpDocument = 0;
static CVIXMLElement	hRootElem = 0;
static CVIXMLElement    hChildElem = 0;
static CVIXMLAttribute  hSoftwareCurrAttr = 0;
static CVIXMLAttribute  hUpdateCurrAttr = 0; 
static CVIXMLAttribute  hHardCurrAttr = 0; 
//==================================================================================================================== 
static void GetSingleCurveAttr(CurveAttrTypeDef *pCurveAttr, int GraphIndex, int CurveIndex)
{
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_LINE_STYLE, &(pCurveAttr->lineStyle));
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_PLOT_STYLE, &(pCurveAttr->plotStyle));
	GetCtrlVal(hSettingsGraphPanel, SETGRAPH_POINT_STYLE,&(pCurveAttr->pointStyle));
	//根据index获取颜色
													                                                                                                                                                                                                                                  
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,&(Graph1_CurveAttr1.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,&(Graph1_CurveAttr2.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,&(Graph1_CurveAttr3.lineColor)); 
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH2CLR1,&(Graph2_CurveAttr1.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH2CLR2,&(Graph2_CurveAttr2.lineColor));
	GetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH2CLR3,&(Graph2_CurveAttr3.lineColor));
}
//==================================================================================================================== 
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
//==================================================================================================================== 
int CVICALLBACK PrjBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsPrjPanel, 5, 170);
			DisplayPanel(hSettingsPrjPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsAboutPanel);
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
//==================================================================================================================== 
int CVICALLBACK GraphBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hSettingsGraphPanel, 5, 170);
			DisplayPanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
			HidePanel(hSettingsAboutPanel);
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
//==================================================================================================================== 
int CVICALLBACK AboutBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			int len = 0;
			int versionVal = 0;
			char text[4];
			GetProjectDir (getProjectDir);  
			MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
			MakePathname(getProjectDirs, "localInfo.xml", localInfoPath);
			CVIXMLLoadDocument (localInfoPath, &hLoDocument);
			CVIXMLGetRootElement (hLoDocument, &hRootElem);
			CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //获得标签UpdateVersion 子元素
			CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
			CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
			CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
			currentUpdateVersion = malloc (len + 1); 
			CVIXMLGetAttributeValue(hUpdateCurrAttr,currentUpdateVersion);   //从本地目录下XML文件中获取软件当前版本号
			versionVal = (currentUpdateVersion[4] - '0')*100+(currentUpdateVersion[5]- '0')*10+(currentUpdateVersion[6]- '0');
			sprintf(text, "%d", versionVal);
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUM_TV, text);                  //改变测试版本号的值
			
			CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //获得标签SoftwareVersion 子元素
			CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
			CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
			CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
			CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
			currentSoftVersion = malloc (len + 1); 
			CVIXMLGetAttributeValue(hSoftwareCurrAttr,currentSoftVersion);   //从本地目录下XML文件中获取软件当前版本号	
			versionVal = (currentSoftVersion[4] - '0')*100+(currentSoftVersion[5]- '0')*10+(currentSoftVersion[6]- '0');
			sprintf(text, "%d", versionVal);
			SetCtrlVal (hSettingsAboutPanel, ABOUT_NUM_SV, text);                  //改变测试版本号的值

			SetPanelPos(hSettingsAboutPanel, 5, 170);
			DisplayPanel(hSettingsAboutPanel);
			HidePanel(hSettingsGraphPanel);
			HidePanel(hSettingsPrjPanel);
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
//==================================================================================================================== 
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
//==================================================================================================================== 
int  CVICALLBACK SettingsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			RemovePopup(hSettingsPanel);
			break;
	}
	return 0;
}
//====================================================================================================================
static int HardwareSystemUpdate_Download()             //下载嵌入式硬件更新升级包 （下载文件）
{
	GetProjectDir (getProjectDir);
	if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //用户匿名登陆服务器
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftp通信方式为主动模式
	{
		MessagePopup ("An Error Occurred", "Current communication mode is active mode");
		return -1;
	}
	if ((InetFTPChangeDir (ftp_handle, ".//SA5101//")) < 0)	
	{
		MessagePopup ("An Error Occurred", "Server current directory error");
		return -1;
	}
	MakePathname(getProjectDir, "..\\hardFileBackups\\SA5101.bin", updateHardFilePath);
	SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateHardFilePath);  
	error = InetFTPRetrieveFile (ftp_handle, updateHardFilePath, ".//SA6101.bin", INET_FTP_FILE_TYPE_BINARY);
	if(error == -13)  
	{
		MessagePopup ("An Error Occurred", "Can't find the hardFileBackups file");
		return -2;	
	}
	if ( error < 0)  //下载服务器当前列表中的硬件文件
	{
		MessagePopup ("An Error Occurred", "Failed to download hardware file");
		return -1;
	}
	ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 100, 0); InetFTPClose(ftp_handle);
	return 0;
}
//============================================================================================================================  
static void ChangeStatus(int display)
{
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_TEXTMSG, ATTR_VISIBLE, display);    //“下载中”文本显示
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_FILEDIS_TEXTMSG, ATTR_VISIBLE, display);	  //“路径”文本显示
	SetCtrlAttribute (hSettingsAboutPanel,ABOUT_PROGRESSBAR, ATTR_VISIBLE, display);	 //“进度条”文本显示
}
//============================================================================================================================  
static int GetVersions()
{
	int		num, i;
	double j = 1.0;
	char	**files = NULL;
	int len;
    if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //用户匿名登陆服务器
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftp通信方式为主动模式
	{
		MessagePopup ("An Error Occurred", "Current communication mode is active mode");
		return -1;
	}
	if ((InetFTPChangeDir (ftp_handle, ".//SA5101//updates")) < 0)			
	{
		MessagePopup ("An Error Occurred", "Server current directory error");
		return -1;
	}
	if (( InetFTPGetDirList (ftp_handle, &files, &num)) < 0) 
	{
		MessagePopup ("An Error Occurred", "Failed to get directory list");
		return -1;
	}
	GetProjectDir (getProjectDir);  
	MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
	MakePathname(getProjectDirs, files[4], updateSoftFilePath); 
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[4], INET_FTP_FILE_TYPE_BINARY);
	if(error == -13)  
	{
		MessagePopup ("An Error Occurred", "Can't find the updates file");
		return -2;	
	}
	for(i = 3;i<num;i++)
	{    
		MakePathname(getProjectDirs, files[i], updateSoftFilePath);
		SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateSoftFilePath); 
		error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY);
		if(error < 0)
		{
			MessagePopup ("An Error Occurred", "Can't Connect To Server");
			return -1;	
		}
		ProgressBar_SetPercentage (hSettingsAboutPanel, ABOUT_PROGRESSBAR, 5+j, 0); 
		j+=(5.0/(num - 2));
	}
	InetFTPClose(ftp_handle); 
	GetProjectDir (getProjectDir);  
	MakePathname(getProjectDir, "..\\updates\\", getProjectDirs);
	MakePathname(getProjectDirs, "updateInfo.xml", updateInfoPath);
	MakePathname(getProjectDirs, "localInfo.xml", localInfoPath);
	
	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //获得标签UpdateVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
	CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
	CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
	serversUpdateVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hUpdateCurrAttr,serversUpdateVersion);   //从服务器下载.xml文件到本地目录下，再从该XML文件中获取最新更新版本号
     
    CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //获得标签UpdateVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
	CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
	CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
	currentUpdateVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hUpdateCurrAttr,currentUpdateVersion);   //从本地目录下XML文件中获取软件当前版本号
	
	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //获得标签SoftwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
	CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
	CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
	serversSoftVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hSoftwareCurrAttr,serversSoftVersion);   //从服务器下载.xml文件到本地目录下，再从该XML文件中获取最新软件版本号
    
    CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //获得标签SoftwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
	CVIXMLGetAttributeNameLength(hSoftwareCurrAttr, &len);
	CVIXMLGetAttributeName(hSoftwareCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hSoftwareCurrAttr, &len);
	currentSoftVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hSoftwareCurrAttr,currentSoftVersion);   //从本地目录下XML文件中获取软件当前版本号

	CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
	CVIXMLGetRootElement (hUpDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "HardwareVersion", &hChildElem); //获得标签HardwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hHardCurrAttr);
	CVIXMLGetAttributeNameLength(hHardCurrAttr, &len);
	CVIXMLGetAttributeName(hHardCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hHardCurrAttr, &len);
	serversHardVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hHardCurrAttr,serversHardVersion);   //从服务器下载.xml文件到本地目录下，再从该XML文件中获取最新硬件版本号
	
	CVIXMLLoadDocument (localInfoPath, &hLoDocument);
	CVIXMLGetRootElement (hLoDocument, &hRootElem);
	CVIXMLGetChildElementByTag(hRootElem, "HardwareVersion", &hChildElem); //获得标签HardwareVersion 子元素
	CVIXMLGetAttributeByIndex(hChildElem, 0, &hHardCurrAttr);
	CVIXMLGetAttributeNameLength(hHardCurrAttr, &len);
	CVIXMLGetAttributeName(hHardCurrAttr, attrName);
	CVIXMLGetAttributeValueLength (hHardCurrAttr, &len);
	currentHardVersion = malloc (len + 1); 
	CVIXMLGetAttributeValue(hHardCurrAttr,currentHardVersion);   //从本地目录下XML文件中获取硬件当前版本号
	return 0;
}
//============================================================================================================================  
static int CheckHardware()   //检车硬件是否为最新
{
	int	j;
	int len = strlen(serversHardVersion);
	for(j=0;j<=len;j++)
	{
	 if(serversHardVersion[j] != currentHardVersion[j])
	 {
		int temp = ConfirmPopup ("Version update", "Whether to update to the latest hard version");  //更新软件版本提醒
		if(temp  == 1)
		{
		   ChangeStatus(0);
	       return 1;
		}else
		{
			MessagePopup ("Warning", "Please update");
			ChangeStatus(0); 
			return 0;
		}
	 }
	if(j == len)
		MessagePopup ("Warning", "It is the latest hard version");
		ChangeStatus(0); 
	}
	return 0;
}
//============================================================================================================================
int CVICALLBACK UpdateHardware (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	//char temp[MAX_PATHNAME_LEN]="..\\hardFileBackups\\SA5101.bin";
	//char temp1[MAX_PATHNAME_LEN]={0x01,0x16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	//							  0,0,0,0,0,0,0,0,0,0,0x17};
	int i = 0;
	switch (event)
	{
	   case EVENT_LEFT_CLICK_UP:
			int updateFlag = 0;
			ChangeStatus(1);
			ProgressBar_ConvertFromSlide (hSettingsAboutPanel, ABOUT_PROGRESSBAR);
			ProgressBar_SetAttribute (hSettingsAboutPanel, ABOUT_PROGRESSBAR, ATTR_PROGRESSBAR_UPDATE_MODE, VAL_PROGRESSBAR_MANUAL_MODE);
			ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 5, 0);
			updateFlag = GetVersions();
			if(updateFlag == -1)
			{
				MessagePopup ("Update failed", "Check your network connection");
				ChangeStatus(0); 
				return 0;
			}
			if(updateFlag == -2) 
			{
			    ChangeStatus(0); 
				return 0;	
			}
		    i = CheckHardware();
			if(i == 1)
			{
				updateFlag = HardwareSystemUpdate_Download();
				if(updateFlag == -1)
				{
					MessagePopup ("Update failed", "Check your network connection");
					ChangeStatus(0); 
					return 0;
				}
				if(updateFlag == -2)
				{
					ChangeStatus(0); 
					return 0;	
				}
				CVIXMLSetAttributeValue (hHardCurrAttr, serversHardVersion);  //将修改本地xml文件中的版本号  
				CVIXMLSaveDocument (hLoDocument, 0, NULL);
			    ChangeStatus(0); 
				//ReadFromConfigFile(temp,temp1);
			}
		    break;
	}
	return 0;
}
//============================================================================================================================  
static int SoftwareSystemUpdate_Download()             //下载软件更新升级包 （下载文件）
{
	int	num, i;
	float j = 1.0;
	char **files = NULL;
	GetProjectDir (getProjectDir);
	if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)//用户匿名登陆服务器
	{
		MessagePopup ("An Error Occurred", "Can't Connect To Server");
		return -1;
	}
	if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftp通信方式为主动模式
	{
		MessagePopup ("An Error Occurred", "Current communication mode is active mode");
		return -1;
	}
	if ((InetFTPChangeDir (ftp_handle, ".//SA5101//SA5101//Resource//")) < 0)
	{
		MessagePopup ("An Error Occurred", "Server current directory error");
		return -1;
	}
	if (( InetFTPGetDirList (ftp_handle, &files, &num)) < 0) 
	{
		MessagePopup ("An Error Occurred", "Failed to get directory list");
		return -1;
	}
	MakePathname(getProjectDir, "..\\softwareFileBackups\\Resource\\", getProjectDirs);
	MakePathname(getProjectDirs, files[2], updateSoftFilePath);
	
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[2], INET_FTP_FILE_TYPE_BINARY);  //下载服务器当前列表中的软件文件
	if(error == -13)
	{
		MessagePopup ("An Error Occurred", "Can't find the softwareFileBackups\\Resource file");
			return -2;
	}
	for(i = 2;i<num;i++)
	{    
		MakePathname(getProjectDir, "..\\softwareFileBackups\\Resource\\", getProjectDirs);
		MakePathname(getProjectDirs, files[i], updateSoftFilePath);
		SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateSoftFilePath);
		if((InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY)) < 0)  //下载服务器当前列表中的软件文件
		{
			MessagePopup ("An Error Occurred", "Check the network");
			return -1;
		}
		 ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 20+j, 0); 
		j+=(40.0/(num - 2));
	}
	if ((InetFTPChangeDir (ftp_handle, "..//Uir//")) < 0)
	{
	   MessagePopup ("An Error Occurred", "Server current directory error");
	   return -1;
	}
	if ((InetFTPGetDirList (ftp_handle, &files, &num)) < 0)
	{
		MessagePopup ("An Error Occurred", "Failed to get directory list"); 
		return -1;
	}
	MakePathname(getProjectDir, "..\\softwareFileBackups\\Uir\\", getProjectDirs);
	MakePathname(getProjectDirs, files[2], updateSoftFilePath);
	error = InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[2], INET_FTP_FILE_TYPE_BINARY);  //下载服务器当前列表中的软件文件
	if(error == -13)
	{
		MessagePopup ("An Error Occurred", "Can't find the softwareFileBackups\\Uir file");
			return -2;
	}
	j = 1.0;
	for(i = 2;i<num;i++)
		{    
			 MakePathname(getProjectDir, "..\\softwareFileBackups\\Uir\\", getProjectDirs);
			 MakePathname(getProjectDirs, files[i], updateSoftFilePath);
			 SetCtrlVal (hSettingsAboutPanel, ABOUT_FILEDIS_TEXTMSG, updateSoftFilePath); 
		     if((InetFTPRetrieveFile (ftp_handle, updateSoftFilePath, files[i], INET_FTP_FILE_TYPE_BINARY)) < 0)   //下载服务器当前列表中的软件文件
		     {
				 MessagePopup ("An Error Occurred", "Check the network");
				 return -1;
			 }
			 ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 60+j, 0);
			 j+=(40.0/(num - 2));
		}
	ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR,100.0, 0); 
	InetFTPClose(ftp_handle);
	return 0;
}
//============================================================================================================================  
static int CheckTestSoftware()   //检车软件是否为最新  
{
	int i;
	int len = strlen(serversUpdateVersion);
	for(i=0;i<=len;i++)
	{
		if(serversUpdateVersion[i] != currentUpdateVersion[i])
		{
			int temp = ConfirmPopup ("Version update", "Whether to update to the latest Software version");  //更新软件版本提醒
			if(temp  == 1)
			{
				return 1;
			}else
			{
				MessagePopup ("Warning", "Please update");
				ChangeStatus(0);
				return 0;
			}
		}
		if(i == len)
		{
			MessagePopup ("Warning", "It is the latest Software version");
			ChangeStatus(0);
		}
	}
return 0;
}
//============================================================================================================================  
static int CheckSoftware()   //检车软件是否为最新  
{
	int i;
	int len = strlen(serversSoftVersion);
	for(i=0;i<=len;i++)
	{
		if(serversSoftVersion[i] != currentSoftVersion[i])
		{
			int temp = ConfirmPopup ("Version update", "Whether to update to the latest Software version");  //更新软件版本提醒
			if(temp  == 1)
			{
				return 1;
			}else
			{
				MessagePopup ("Warning", "Please update");
				ChangeStatus(0);
				return 0;
			}
		}
		if(i == len)
		{
			MessagePopup ("Warning", "It is the latest Software version");
			ChangeStatus(0);
		}
	}
return 0;
}
//============================================================================================================================  
int CVICALLBACK UpdateSoftware (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			int updateFlag = 0;
			int temp = 0;  
			ChangeStatus(1); 
			ProgressBar_ConvertFromSlide (hSettingsAboutPanel, ABOUT_PROGRESSBAR);
			ProgressBar_SetAttribute (hSettingsAboutPanel, ABOUT_PROGRESSBAR, ATTR_PROGRESSBAR_UPDATE_MODE, VAL_PROGRESSBAR_MANUAL_MODE);
			ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 2, 0);
			ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 2, 0);
			ProgressBar_SetPercentage ( hSettingsAboutPanel, ABOUT_PROGRESSBAR, 1, 0);  
			updateFlag = GetVersions();
			if(updateFlag == -1)
			{
				MessagePopup ("Update failed", "Check your network connection");
				ChangeStatus(0); 
				return 0;
			}
			if(updateFlag == -2)
			{
				ChangeStatus(0); 
				return 0;
			}
			if(builtInTestFlag == 1)
			{
				temp = CheckTestSoftware();//检车公司内部测试的软件是否为最新
				builtInTestFlag = 0;
			}else
			{
				temp = CheckSoftware();//检车客户端软件是否为最新 	
			}
			if(temp == 1)
			{
				updateFlag = SoftwareSystemUpdate_Download();
				if(updateFlag == -1)
				{
					MessagePopup ("Update failed", "Check your network connection");
					ChangeStatus(0); 
					return 0;
				}
				if(updateFlag == -2)
				{
					ChangeStatus(0); 
					return 0;
				}
				CVIXMLLoadDocument (localInfoPath, &hLoDocument);
				CVIXMLGetRootElement (hLoDocument, &hRootElem);
				CVIXMLGetChildElementByTag(hRootElem, "SoftwareVersion", &hChildElem); //获得标签SoftwareVersion 子元素
				CVIXMLGetAttributeByIndex(hChildElem, 0, &hSoftwareCurrAttr);
				CVIXMLSetAttributeValue (hSoftwareCurrAttr, serversSoftVersion);  //将修改本地xml文件中的版本号
				CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //获得标签UpdateVersion 子元素
				CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
				CVIXMLSetAttributeValue (hUpdateCurrAttr, serversUpdateVersion);  //将修改本地xml文件中的版本号 
				CVIXMLSaveDocument (hLoDocument, 0, NULL);
				MessagePopup ("Warning", "Update successfully");
				ChangeStatus(0);
				QuitUserInterface (0);
				LaunchExecutableEx ("..\\updates\\replace.exe", LE_HIDE, &ftp_handle);
			}
		break;
	}
	return 0;
}
//============================================================================================================================
int CVICALLBACK TxtSoftwareCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 UpdateSoftware ( panel,control, event,callbackData, eventData1, eventData2);
			break;
	}
	return 0;
}
//============================================================================================================================
int CVICALLBACK TxtHardwareCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			UpdateHardware (panel,  control, event,callbackData,  eventData1, eventData2) ;
			break;
	}
	return 0;
}

int CVICALLBACK LedCB (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetCtrlAttribute (hSettingsAboutPanel, ABOUT_LED, ATTR_OFF_COLOR, VAL_BLACK);
            builtInTestFlag = 1;
			break;
	}
	return 0;
}
