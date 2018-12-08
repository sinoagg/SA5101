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
unsigned char measureUartFlag = 1; 				//��ѧ�������ڽ���ʱҪ�������ݲ�ѯ 
unsigned char controlUartFlag = 0; 				//�����������ڽ���ʱҪ�������ݲ�ѯ
unsigned char measUartTxBuf[SA51_UART_TX_LEN]={0};
unsigned char measUartRxBuf[1024]={0};
int rows;   //graph1 table��д���ݱ�־λ
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
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time));   //����result��ʾ��ʱ���ֵ      
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time);					//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;								// ʱ������ʱ�����ķ�ʽ�����ƶ�
			*(Graph1.pCurveArray->pDotY++)= rxIdmeasured; 								//��Y�ḳֵ��������
			break;
		case LSV:
		case TAFEL:
		case CV:
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time)); //����result��ʾ��ʱ���ֵ              
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time);	//get x, set pointer to the next data
			 Graph1.pCurveArray->time+=(TestPara.voltageStep/TestPara.sampleRate);     // ʱ������ʱ�����ķ�ʽ�����ƶ� 
			*(Graph1.pCurveArray->pDotY++)=pRxData->rxVoltage1;  //��Y�ḳֵ����ѹ��
			break;
		case SV:
		case NPV:
		case DPV:
		case DNPV:
		case SWV:
			SetCtrlVal(hResultDispPanel, RESULTDISP_TIME, (Graph1.pCurveArray->time)); //����result��ʾ��ʱ���ֵ              
			*(Graph1.pCurveArray->pDotX++)=(Graph1.pCurveArray->time);	//get x, set pointer to the next data
			Graph1.pCurveArray->time+=TestPara.timeStep;								// ʱ������ʱ�����ķ�ʽ�����ƶ�       
			*(Graph1.pCurveArray->pDotY++)=pRxData->rxVoltage1;  //��Y�ḳֵ����ѹ��
			break;
	}
}
//==================================================================================================================================   
static void RxDataToTable()	//rows��table���еı�־������ÿ�����ߴ�rows=2��ʼ�����һ����;һ�����߽���ʱ��2     
{
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+1, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+2, rows), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+1, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotX-1));  //д��Xֵ
	SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (Graph1.plotCurveIndex*5+2, rows), *((Graph1.pCurveArray+Graph1.plotCurveIndex)->pDotY-1));  //д��Yֵ 
	rows++;      
}
//==================================================================================================================================   
static void TestStop(RxDataTypeDef *pRxData,int portNumber)
{
	Delay(0.5);                      //�ȴ��쳣����µ����ݻ������ 
	abnmDCThreadFlag = 0;					//�������ݵ��߳�
	measureUartFlag = 0;		 	//ֹͣʱ��ѯֹͣ��      
	Graph1.pCurveArray->numOfPlotDots=0; 
	DiscardAsyncTimer(TimerID);											//ֹͣquery��ʱ����ѯ
	Delay(0.1);															//�ڲ�ѯ��ֹͣ������0.1��
	ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART 
	Delay(0.1);	
	FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(measureComPort);
  	SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
    SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
	SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //�ָ�������������
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,0xFF4600);//��ɫϵ
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,0x24786E);//��ɫϵ
	SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,0x008FFF);//��ɫϵ
}
//===============================================================================================
static void DataAnalysis(RxDataTypeDef *pRxData,int portNumber)
{
//====================��ԭʼ���ݽ����˲�����; FFT; ��������; �������==========================================================================================	
	int k = 0, i;
	double outputArray[POINTS*2];
	double firCoefficientArray[POINTS];
	FIR_Coef (2, fsin*10, fsin*0.8, fsin*1.3, POINTS, firCoefficientArray); //�˲���ϵ��	   //ͨ��һ�����˲�
	Convolve (firCoefficientArray, POINTS, channel1Real, POINTS, outputArray); //�������
	for(i = 63;i <187;i++)
	{
		channel1Real[k++] = outputArray[i];	
	}
	k = 0;
	FIR_Coef (2, fsin*10, fsin*0.8, fsin*1.3, POINTS, firCoefficientArray); //�˲���ϵ��		//ͨ���������˲�
	Convolve (firCoefficientArray, POINTS, channel2Real, POINTS, outputArray); //�������
	for(i = 63;i <187;i++)
	{
		channel2Real[k++] = outputArray[i];	
	}
	FFT (channel1Real, channel1Imaginary, POINTS);   //ͨ��1ʵ�����飻�鲿����        ͨ������ͨ��һ��Ҫ����FFt�任    
	FFT (channel2Real, channel2Imaginary, POINTS);   //ͨ��2ʵ�����飻�鲿����
	for(int i = 0;i < POINTS;i++)
	{
		channel1[i].real = channel1Real[i];
		channel1[i].imaginary = channel1Imaginary[i];
		channel2[i].real = channel2Real[i];
		channel2[i].imaginary = channel2Imaginary[i]; 
	}
	CxPseudoInverse (channel1, 1, POINTS, 0.5, channel1Inverse); 	//��������  
	CxMatrixMul (channel2, channel1Inverse, 1, POINTS, 1, outputMatrix);	//�������
//===============================��ͼ===============================================================================
	char buf[255];
	switch(TestPara.impDrawingType)
	{
		case 0:
			(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase   
			*(Graph1.pCurveArray->pDotX++)=outputMatrix->real;	//����ʵ��Ϊx��
			*(Graph1.pCurveArray->pDotY++)=outputMatrix->imaginary;  //�����鲿Ϊy��
			PlotCurve1(&Graph1, hGraphDispPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex);
			SetCtrlVal(hResultDispPanel, RESULTDISP_V, outputMatrix->real);              //���ý����ʾʵ��ֵ  
			SetCtrlVal(hResultDispPanel, RESULTDISP_IDS, outputMatrix->imaginary);         //���ý����ʾ�鲿��ֵ  
			sprintf(buf, "%d:%fHz", j, fsin);
			AddGraphAnnotation(hGraphDispPanel, GRAPHDISP_GRAPH1, outputMatrix->real, outputMatrix->imaginary, buf, 2, 2);  //���ÿ�����ע��
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
			*(Graph1.pCurveArray->pDotX++)=log(fsin);	//����Ƶ�ʵĶ���Ϊx��
			*(Graph1.pCurveArray->pDotY++)=log(sqrt((outputMatrix->real*outputMatrix->real)+(outputMatrix->imaginary*outputMatrix->imaginary)));  //�����迹��ģ�Ķ���Ϊy��
			PlotCurve1(&Graph1, hGraphDispPanel, GRAPHDISP_GRAPH1, Graph1.plotCurveIndex);
			(Graph2.pCurveArray+Graph2.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
			*(Graph2.pCurveArray->pDotX++)=log(fsin);	//����Ƶ�ʵĶ���Ϊx��
			*(Graph2.pCurveArray->pDotY++)=(-1)*atan(outputMatrix->imaginary/outputMatrix->real);  //������λ��Ϊy��
			PlotCurve1(&Graph2, hGraphDispPanel, GRAPHDISP_GRAPH2, Graph2.plotCurveIndex);
			j++;
			Delay(3);
			break;
	}
	if(pointInNumber >= 0)  //����
	{
		ProtocolCfg(measureComPort, MEASURE_DEV_ADDR, (enum TestMode)TestPara.testMode, measUartTxBuf);	//send config to instrument via UART 
		ProtocolRun(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf); 	//send RUN command to instrument via UART
		pointInNumber--;
		totalNum++;
	}
	Delay(0.1);
	num = 0;
	FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
	FlushOutQ(measureComPort);
	if((fsin - minFreq) <= 0.00001)
	{
		measureUartFlag = 0;		 	//ֹͣʱ��ѯֹͣ��      
		DiscardAsyncTimer(TimerID);											//ֹͣquery��ʱ����ѯ
		Delay(0.1);															//�ڲ�ѯ��ֹͣ������0.1��
		ProtocolStop(measureComPort, MEASURE_DEV_ADDR, measUartTxBuf);		//send STOP command to instrument via UART 
		Delay(0.1);	
		FlushInQ(measureComPort);	   										//Clear input and output buffer,�ڲ��Կ�ʼ֮ǰ��Ӧ�����һ��
		FlushOutQ(measureComPort);
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
		SetCtrlAttribute (hMainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED, 0);   //�ָ�������������
		SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR1,0xFF4600);//��ɫϵ
		SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR2,0x24786E);//��ɫϵ
		SetCtrlVal(hSettingsGraphPanel,SETGRAPH_GRAPH1CLR3,0x008FFF);//��ɫϵ
	}
}
//==================================================================================================================================   
void  CVICALLBACK MeasureComCallback(int portNumber ,int eventMask, void * callbackData)
{
	int rxNum = 0;
	int i = 0;
	RxDataTypeDef RxData;
	float rxIdmeasured = 0;
	rxNum = GetInQLen(portNumber);  											//��ȡ�����з���������������
	if(rxNum>1024) rxNum=1024;													//��ֹ�����ڴ淶Χ
	rxNum-=rxNum%SA51_UART_RX_LEN;											//ֻ��ȡ�����ַ��������������ݣ�������ɢ����
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
				SetCtrlVal(hResultDispPanel, RESULTDISP_V, RxData.rxVoltage1);		  //���ý����ʾ����ѹ���ֵ
				SetCtrlVal(hResultDispPanel, RESULTDISP_OHM,RxData.rxResistance1);   //���ý����ʾ��������ֵ    rxResistance1
				(Graph1.pCurveArray+Graph1.plotCurveIndex)->numOfDotsToPlot++;		  //number of dots to plot increase
				rxIdmeasured = RxData.rxVoltage1 / RxData.rxResistance1; 		 
				SetCtrlVal(hResultDispPanel, RESULTDISP_IDS,rxIdmeasured);   //���ý����ʾ���������ֵ
				RxDataToGraph(&RxData, rxIdmeasured);				//�����ݵ�Graph
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
	char MeasureRXBuffer[40];   //����
//	char USART_RX_Buffer2[10];   //����
	int error = 0,uartRxLen;
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
				uartRxLen = GetInQLen (i);
				ComRd (i,MeasureRXBuffer,uartRxLen);
				if((MeasureRXBuffer[1]== 0x51) && (MeasureRXBuffer[2] == 0x01))
				{
					measureComPort = i;	
					SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//��Ӳ������   
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
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //���úʹ򿪴��� 
		    if(b<0 )
			{
				
			}else
			{	
			    ComWrt(i, IDquery2, 8);							//���Ͳ�ѯָ��
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
				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//��Ӳ������
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
		uartStatusFlag=0;															               //���ڴ�ʧ��
		MessagePopup("Error","Failed to open the serial port of electrical measuring equipment"); //Ҫ����������Ҫ���ô˴��ڵĲ�������
	}
	else 
	{
		uartStatusFlag=1;															//���ڴ򿪳ɹ�  
	}
	/*if(CheckPortStatus(controlComPort, 15, CtrlComCallback)<0)						//�жϻ��������豸��Ӧ�Ĵ����Ƿ����ӳɹ�
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

	if(uartStatusFlag==1)				//�����ѧ�豸�򿪵Ļ����ر����ʱ��Ҫ�رն�Ӧ�Ĵ��ڡ��û���ʹ�õ�ѧ�����豸ʱ��û�д򿪣����ԾͲ��ùرա�
	{
		CloseCom(measureComPort);
	}
	if(uartStatusFlag==2)				//��������豸�򿪵Ļ����ر����ʱ��Ҫ�رն�Ӧ�Ĵ��ڡ��û���ʹ�û��������豸ʱ��û�д򿪣����ԾͲ��ùرա�
	{
		CloseCom(controlComPort);
	}
	if(uartStatusFlag==3)				//�����ѧ�ͻ����Ĳ����豸���򿪵Ļ�������ʱ��Ҫͬʱ�ر�
	{
		CloseCom(controlComPort);
		CloseCom(measureComPort);
	}
	DiscardPanel (hMainPanel);
	return 0;
}





