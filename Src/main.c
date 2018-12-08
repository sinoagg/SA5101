//==============================================================================
// Include files
#include <analysis.h>
#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "LoadPanel.h"
#include "system_ini.h"
#include "MainPanelCb.h"
#include "Plot.h"
#include "Graph.h"
//==============================================================================
// Constants
const char IDquery[] = {0xAA, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20};
//==============================================================================
// Types

//==============================================================================
// Global variables
unsigned char measureComPort;				    //Serial Com Number
unsigned char controlComPort;
unsigned char measureUartFlag = 1; 				//电学测量串口接收时要屏蔽数据查询 
unsigned char controlUartFlag = 0; 				//环境参数串口接收时要屏蔽数据查询
unsigned char measUartTxBuf[SA51_UART_TX_LEN]={0};
unsigned char measUartRxBuf[1024]={0};
int rows;   //graph1 table填写数据标志位
unsigned char j = 1;
int uartStatusFlag=0; 
ComplexNums channel1[POINTS];
ComplexNums channel2[POINTS]; 
ComplexNums channel1Inverse[POINTS];
ComplexNums outputMatrix[2];
//==============================================================================
// const variables  

//==============================================================================
// Global functions
static void RxDataToGraph(RxDataTypeDef *pRxData, float rxIdmeasured)
{  
	switch(TestPara.testMode)
	{
		case IT:
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time));   //设置result显示中时间的值      
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time);					//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;								// 时间轴以时间间隔的方式往后移动
			*(Graph1.pCurveArray->pDotY++)= rxIdmeasured; 								//给Y轴赋值（电流）
			break;
		case LSV:
		case TAFEL:
		case CV:
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time)); //设置result显示中时间的值              
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time);	//get x, set pointer to the next data
			 Graph1.pCurveArray->time+=(TestPara.voltageStep/TestPara.sampleRate);     // 时间轴以时间间隔的方式往后移动 
			*(Graph1.pCurveArray->pDotY++)=pRxData->rxVoltage1;  //给Y轴赋值（电压）
			break;
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV:
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time)); //设置result显示中时间的值              
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time);	//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;								// 时间轴以时间间隔的方式往后移动       
			*(Graph1.pCurveArray->pDotY++)=pRxData->rxVoltage1;  //给Y轴赋值（电压）
			break;
	}
}
//==================================================================================================================================   
static void RxDataToTable()	//rows是table中行的标志来量，每条曲线从rows=2开始到最后一个点;一条曲线结束时置2     
{
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //写入X值
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //写入Y值 
	rows++;      
}
//==================================================================================================================================   
static void TestStop(RxDataTypeDef *pRxData,int portNumber)
{
	Delay(0.5);                      //等待异常情况下的数据缓存完成 
	abnmDCThreadFlag = 0;					//缓存数据的线程
	measureUartFlag = 0;		 	//停止时查询停止，      
	Graph1.pCurveArray->numOfPlotDots=0; 
	DiscardAsyncTimer(TimerID);											//停止query定时器查询
	Delay(0.1);															//在查询和停止命令间隔0.1秒
	ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART 
	Delay(0.1);	
	FlushInQ(measureComPort);	   										//Clear input and output buffer,在测试开始之前还应该清楚一次
	FlushOutQ(measureComPort);
  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //恢复曲线属性设置
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,0xFF4600);//红色系
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,0x24786E);//绿色系
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,0x008FFF);//蓝色系
}
//===============================================================================================
static void DataAnalysis(RxDataTypeDef *pRxData,int portNumber)
{
//====================对原始数据进行滤波处理; FFT; 数据求逆; 矩阵相乘==========================================================================================	
	int k = 0, i;
	double outputArray[POINTS*2];
	double firCoefficientArray[POINTS];
	FIR_Coef (2, fsin*10, fsin*0.8, fsin*1.3, POINTS, firCoefficientArray); //滤波器系数	   //通道一进行滤波
	Convolve (firCoefficientArray, POINTS, channel1Real, POINTS, outputArray); //卷积运算
	for(i = 63;i <187;i++)
	{
		channel1Real[k++] = outputArray[i];	
	}
	k = 0;
	FIR_Coef (2, fsin*10, fsin*0.8, fsin*1.3, POINTS, firCoefficientArray); //滤波器系数		//通道二进行滤波
	Convolve (firCoefficientArray, POINTS, channel2Real, POINTS, outputArray); //卷积运算
	for(i = 63;i <187;i++)
	{
		channel2Real[k++] = outputArray[i];	
	}
	FFT (channel1Real, channel1Imaginary, POINTS);   //通道1实部数组；虚部数组        通道二和通道一都要进行FFt变换    
	FFT (channel2Real, channel2Imaginary, POINTS);   //通道2实部数组；虚部数组
	for(int i = 0;i < POINTS;i++)
	{
		channel1[i].real = channel1Real[i];
		channel1[i].imaginary = channel1Imaginary[i];
		channel2[i].real = channel2Real[i];
		channel2[i].imaginary = channel2Imaginary[i]; 
	}
	CxPseudoInverse (channel1, 1, POINTS, 0.5, channel1Inverse); 	//数据求逆  
	CxMatrixMul (channel2, channel1Inverse, 1, POINTS, 1, outputMatrix);	//矩阵相乘
//===============================画图===============================================================================
	char buf[255];
	switch(TestPara.impDrawingType)
	{
		case 0:
			(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase   
			*(Graph1.pCurveArray->pDotX++)=outputMatrix->real;	//设置实部为x轴
			*(Graph1.pCurveArray->pDotY++)=outputMatrix->imaginary;  //设置虚部为y轴
			PlotCurve1(&Graph1, hGraphDispPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex);
			SetCtrlVal(hResultDispPanel, RESULTDISP_V, outputMatrix->real);              //设置结果显示实部值  
			SetCtrlVal(hResultDispPanel, RESULTDISP_IDS, outputMatrix->imaginary);         //设置结果显示虚部的值  
			sprintf(buf, "%d:%fHz", j, fsin);
			AddGraphAnnotation(hGraphDispPanel, GRAPHDISP_GRAPH1, outputMatrix->real, outputMatrix->imaginary, buf, 2, 2);  //添加每个点的注释
			SetAnnotationAttribute(hGraphDispPanel, GRAPHDISP_GRAPH1, j, ATTR_ANNOTATION_OFFSET_MODE, VAL_GLYPH_OFFSET);
			SetAnnotationAttribute(hGraphDispPanel, GRAPHDISP_GRAPH1, j, ATTR_ANNOTATION_LINE_COLOR, VAL_TRANSPARENT);
			SetAnnotationAttribute(hGraphDispPanel, GRAPHDISP_GRAPH1, j, ATTR_ANNOTATION_GLYPH_COLOR, VAL_TRANSPARENT);
			SetAnnotationAttribute(hGraphDispPanel, GRAPHDISP_GRAPH1, j, ATTR_ANNOTATION_CAPTION_ALWAYS_IN_VIEW, TRUE);
			SetAnnotationAttribute(hGraphDispPanel, GRAPHDISP_GRAPH1, j, ATTR_ANNOTATION_CAPTION_BOLD, 1);
			SetAnnotationAttribute(hGraphDispPanel, GRAPHDISP_GRAPH1, j, ATTR_ANNOTATION_CAPTION_BGCOLOR, 0x555588);
			j++;
			Delay(3);
			break;
		case 1:
			(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
			*(Graph1.pCurveArray->pDotX++)=log(fsin);	//设置频率的对数为x轴
			*(Graph1.pCurveArray->pDotY++)=log(sqrt((outputMatrix->real*outputMatrix->real)+(outputMatrix->imaginary*outputMatrix->imaginary)));  //设置阻抗的模的对数为y轴
			PlotCurve1(&Graph1, hGraphDispPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex);
			(Graph2.pCurveArray+Graph2.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
			*(Graph2.pCurveArray->pDotX++)=log(fsin);	//设置频率的对数为x轴
			*(Graph2.pCurveArray->pDotY++)=(-1)*atan(outputMatrix->imaginary/outputMatrix->real);  //设置相位角为y轴
			PlotCurve1(&Graph2, hGraphDispPanel, GRAPHDISP_GRAPH2, Graph2.plotCurveIndex);
			j++;
			Delay(3);
			break;
	}
	if(pointInNumber >= 0)  //段数
	{
		ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf);	//send config to instrument via UART 
		ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf); 	//send RUN command to instrument via UART
		pointInNumber--;
		totalNum++;
	}
	Delay(0.1);
	num = 0;
	FlushInQ(measureComPort);	   										//Clear input and output buffer,在测试开始之前还应该清楚一次
	FlushOutQ(measureComPort);
	if((fsin - minFreq) <= 0.00001)
	{
		measureUartFlag = 0;		 	//停止时查询停止，      
		DiscardAsyncTimer(TimerID);											//停止query定时器查询
		Delay(0.1);															//在查询和停止命令间隔0.1秒
		ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART 
		Delay(0.1);	
		FlushInQ(measureComPort);	   										//Clear input and output buffer,在测试开始之前还应该清楚一次
		FlushOutQ(measureComPort);
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //恢复曲线属性设置
		SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,0xFF4600);//红色系
		SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,0x24786E);//绿色系
		SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,0x008FFF);//蓝色系
	}
}
//==================================================================================================================================   
void  CVICALLBACK MeasureComCallback(int portNumber ,int eventMask, void * callbackData)
{
	int rxNum = 0;
	int i = 0;
	RxDataTypeDef RxData;
	float rxIdmeasured = 0;
	rxNum = GetInQLen(portNumber);  											//读取串口中发送来的数据数量
	if(rxNum>1024) rxNum=1024;													//防止超过内存范围
	rxNum-=rxNum%SA51_UART_RX_LEN;											//只读取接收字符组整数倍的数据，不读零散数据
    ComRd(portNumber, (char *)measUartRxBuf, rxNum);							//Read UART Buffer to local buffer at one time
	switch(TestPara.testMode)
	{
		case IT:
		case LSV:
		case TAFEL:
		case CV:
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV:
			while(rxNum>=SA51_UART_RX_LEN)
			{	
				ProtocolGetData(measUartRxBuf+i*SA51_UART_RX_LEN, &RxData);			//get data from uart buffer
				if(RxData.rxDevAddr == 0x55)
				{
					TestStop(&RxData,portNumber);
					break;
				}
				SetCtrlVal(hResultDispPanel, RESULTDISP_V, RxData.rxVoltage1);		  //设置结果显示面板电压框的值
				SetCtrlVal(hResultDispPanel, RESULTDISP_OHM,RxData.rxResistance1);   //设置结果显示面板电阻框的值    rxResistance1
				(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
				rxIdmeasured = RxData.rxVoltage1 / RxData.rxResistance1; 		 
				SetCtrlVal(hResultDispPanel, RESULTDISP_IDS,rxIdmeasured);   //设置结果显示面板电流框的值
				RxDataToGraph(&RxData, rxIdmeasured);				//读数据到Graph
				RxDataToTable();
				rxNum-=SA51_UART_RX_LEN;
				i++; 
			}
			PlotCurve1(&Graph1, hGraphDispPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex);
			SetGraphX_Axis(hGraphDispPanel,GRAPHDISP_GRAPH1,&Graph1);
			break;
		case IMP:
			while(rxNum>=SA51_UART_RX_LEN)
			{	
				ProtocolGetImpData(measUartRxBuf+i*SA51_UART_RX_LEN, &RxData);			//get data from uart buffer
				if(RxData.dataFlag == 0x55)
					DataAnalysis(&RxData,portNumber);
				rxNum-=SA51_UART_RX_LEN;
				i++; 
			} 
			break;
	}
}
//==================================================================================================================================   
int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFun)(int, int, void*))
{
    int status;  
	status = OpenComConfig(portNumber, "", BAUDRATE, 0, 8, 1, 1024, 1024);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected!");
		return -1;
	}
	else
	{
		InstallComCallback (portNumber, LWRS_RECEIVE, uartRxLen, 0, pFun, 0);   //binding Callback function to serial input data 12 bytes received will calling for an interrupt
		SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
		FlushInQ(portNumber);	   //Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;  	
	}
}
//==================================================================================================================================   
static void DeviceQuery()
{
	unsigned char i;
	char MeasureRXBuffer[40];   //接收
//	char USART_RX_Buffer2[10];   //接收
	int error = 0,uartRxLen;
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
				uartRxLen = GetInQLen (i);
				ComRd (i,MeasureRXBuffer,uartRxLen);
				if((MeasureRXBuffer[1]== 0x51) && (MeasureRXBuffer[2] == 0x01))
				{
					measureComPort = i;	
					SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//无硬件交互   
					FlushInQ(measureComPort);	   				//Clear input and output buffer
					FlushOutQ(measureComPort);
					break;
				}
				CloseCom (i); 
			 }
          }
	   
	   	/*for(i = 1; i<=15; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //设置和打开串口 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery2, 8);							//发送查询指令
				Delay(3);
				strLen = GetInQLen (i);
				ComRd (i,USART_RX_Buffer2,strLen);
				if((UART_RX_Buffer2[0]== 0x11) && (UART_RX_Buffer2[1] == 0x03) && (UART_RX_Buffer2[2] == 0x0a))
				{
					controlComPort = i;							
					FlushInQ(controlComPort);	   				//Clear input and output buffer
					FlushOutQ(controlComPort);
					CloseCom (controlComPort);
					break;
				}
				else
				{
					CloseCom(i);
				}
				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//无硬件交互
			}
       }*/
}
//==================================================================================================================================   
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	DeviceQuery();
	if(CheckPortStatus(measureComPort, SA51_UART_RX_LEN, MeasureComCallback)<0)
	{
		uartStatusFlag=0;															               //串口打开失败
		MessagePopup("Error","Failed to open the serial port of electrical measuring equipment"); //要想打开软件，需要禁用此串口的操作命令
	}
	else 
	{
		uartStatusFlag=1;															//串口打开成功  
	}
	/*if(CheckPortStatus(controlComPort, 15, CtrlComCallback)<0)						//判断环境测量设备对应的串口是否连接成功
	{
		control_Uart_Flag = 0;
		usartStatusFlag=uartStatusFlag + 0;     
		MessagePopup("Error","Failed to open the serial port of the environmental measuring equipment.Please check the communication line "); 
	}
	else
	{
		usartStatusFlag=uartStatusFlag + 2; 
	}*/
	LoadInitPanel ();
	RunUserInterface ();  

	if(uartStatusFlag==1)				//如果电学设备打开的话，关闭软件时需要关闭对应的串口。用户不使用电学测量设备时就没有打开，所以就不用关闭。
	{
		CloseCom(measureComPort);
	}
	if(uartStatusFlag==2)				//如果环境设备打开的话，关闭软件时需要关闭对应的串口。用户不使用环境测量设备时就没有打开，所以就不用关闭。
	{
		CloseCom(controlComPort);
	}
	if(uartStatusFlag==3)				//如果电学和环境的测量设备都打开的话，结束时需要同时关闭
	{
		CloseCom(controlComPort);
		CloseCom(measureComPort);
	}
	DiscardPanel (hMainPanel);
	return 0;
}





