//==============================================================================
//
// Title:		TablePanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/3 at 9:49:13 by Ma Hongwei.
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "TablePanel.h"
#include "Table.h"
#include "LoadPanel.h"
//==============================================================================
// Constants
unsigned char  Table_title_IT[2][11] ={"Current(A)","Time(s)"};
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
/*----------------------------------------------------------------------------*/
/* Initialize the table to have X_DATA_POINTS * Y_DATA_POINTS cells of        */
/* specified width.														      */
/*----------------------------------------------------------------------------*/
Table_TypeDef Table_ATTR;

char AB[11][20] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

void Table(char table_title[][20], int column,int columnWidth,int row) //��ʼ����������    
{			
		   
	                               
			InsertTableColumns(hTablePanel,TABLE_DISTABLE,1,column,VAL_CELL_STRING);                     //����в�������� 
			InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1 , row, VAL_CELL_STRING);				      //����row�� 
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
					for(int j=1;j<=column;j++)
					{	
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //��������
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //�����п�
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, AB[(j+5)%6]);          //�б��
						SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (j, 1), table_title[(j+5)%6]);	       //�ֱ����ñ���
					}
					break;
			}
}

 //������ӱ���ɫ
//int CVICALLBACK ColorCallback (int panel, int control, int event,
//							   void *callbackData, int eventData1, int eventData2)
//{		 
//	   switch(event){
//		case EVENT_LEFT_CLICK_UP:
//			int val;
//			GetCtrlVal(hTablePanel,TABLE_ADDBGCOLOR,&val); //���checkbox��ֵ
//			 int rowIndex;
//             int numRows;
//			 GetNumTableRows (hTablePanel, TABLE_DISTABLE, &numRows);
//			   for (rowIndex=1; rowIndex <= numRows; rowIndex++)
//		        {
//		         if((val) &&((rowIndex % 2) ==1))
//					 SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, 0xD0D0D0L);//��ɫ      
//		         else
//		             SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);//��ɫ   
//		        }
//		
//	 	   break;
//	    } 

//	return 0;
//}
