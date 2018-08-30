//==============================================================================
//
// Title:		i_tProtocol.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/7/18 at 10:51:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __i_tProtocol_H__
#define __i_tProtocol_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "i_tPanel.h"

//==============================================================================
// Constants
static  char O_1[] = {0xAA ,0X9A, 0X00, 0X00, 0X84, 0X1E};
static  char O_10[] = {0xAA ,0X9A, 0X00, 0X00, 0X44, 0XDE};
static  char O_100[] = {0xAA ,0X9A, 0X00, 0X02, 0X04, 0X9C};
static  char O_1K[] = {0xAA ,0X9A, 0X00, 0X01, 0X04, 0X9F};
static  char O_10k[] = {0xAA ,0X9A, 0X00, 0X08, 0X04, 0X96}; 
static  char O_100K[] = {0xAA ,0X9A, 0X00, 0X04, 0X04, 0X9A};
static  char O_1M[] = {0xAA ,0X9A, 0X00, 0X20, 0X04, 0XBE};
static  char O_10M[] = {0xAA ,0X9A, 0X00, 0X10, 0X04, 0X8E};
static  char O_100M[] = {0xAA ,0X9A, 0X00, 0X80, 0X04, 0X1E}; 
static  char O_1G[] = {0xAA ,0X9A, 0X00, 0X40, 0X04, 0XDE}; 


static  char O1_1[] = {0xAA ,0X9A, 0X01, 0X00, 0X84, 0X1F};
static  char O1_10[] = {0xAA ,0X9A, 0X01, 0X00, 0X44, 0XDF};
static  char O1_100[] = {0xAA ,0X9A, 0X01, 0X02, 0X04, 0X9D};
static  char O1_1K[] = {0xAA ,0X9A, 0X01, 0X01, 0X04, 0X9E};
static  char O1_10k[] = {0xAA ,0X9A, 0X01, 0X08, 0X04, 0X97}; 
static  char O1_100K[] = {0xAA ,0X9A, 0X01, 0X04, 0X04, 0X9B};
static  char O1_1M[] = {0xAA ,0X9A, 0X01, 0X20, 0X04, 0XBF};
static  char O1_10M[] = {0xAA ,0X9A, 0X01, 0X10, 0X04, 0X8F};
static  char O1_100M[] = {0xAA ,0X9A, 0X01, 0X80, 0X04, 0X1F}; 
static  char O1_1G[] = {0xAA ,0X9A, 0X01, 0X40, 0X04, 0XDF};

static  char Closesend[] = {0xAA ,0X09, 0X01, 0X00, 0X03, 0X0B};
static  char Closesend_1[] = {0xAA ,0X09, 0X94, 0X00, 0X00, 0X9D}; //�̶�����ģʽ����λ���������ص�ѹֵ������1��2��������ر�
static  char Closesend_2[] = {0xAA ,0X09, 0X98, 0X00, 0X00, 0X91};
static  char Closesend_3[] = {0xAA ,0X09, 0X01, 0X00, 0X04, 0X0C}; //�رչ̶���������

//==============================================================================
// Types
 typedef struct
 {
	 int rxResistance;				   //received resistance
	 double rxvoltage;				   //received vlotage
 }RxDataTypeDef;
//==============================================================================
// External variables
extern i_tCfg_TypeDef I_tCfg; 
//==============================================================================
// Global functions
/*  �궨�� */
#define  BANDERATE          115200   //  ������
#define  NOTIFYCOUNTSIZE	4		//һ�δӶ˿�ȡ4�ֽ�
#define  CYCLICCACHESIZE    1048576	//ѭ�������������ֵ 
#define  DATABUFSIZE        10      //һ֡���ݵ��ֽ�  
#define  FRAMESIZE          6		//һ֡��6����
#define  SETCOMTIME         5		// ��д��ʱʱ��
#define  ADC1_RFLAG         32		//  ADC1_R��־
#define  ADC2_RFLAG         48 		//   ADC2_R��־
#define  DATABITS           8        //  ����λ
#define  STOPBITS           1        //  ֹͣλ
#define  PARITYBITS         0        //  ��żУ��λ

int Declare_Your_Functions_Here (int x);
void send_cmd_vol(double vol);//�����û�����ĵ�ѹֵ����ֵ��
void send_cmd_SamInt (int time);
void send_itcmd(void);
void send_itClosecmd();
int ProtocolGetData (unsigned char *pUartRxBuf,RxDataTypeDef *pRxData);
void ProtocolGetData1 (unsigned char *pUartRxBuf,RxDataTypeDef *pRxData); 
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __i_tProtocol_H__ */
