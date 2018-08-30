//==============================================================================
//
// Title:		TablePanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/3 at 9:49:13 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "TablePanel.h"

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
int InitTableCells (int panel,int control,int unmOfColumn,int unmOfRow)
{
	InsertTableRows (panel,control,-1,1,VAL_CELL_STRING);
	InsertTableColumns (panel,control,1,unmOfColumn,VAL_CELL_STRING);
	for(int i = 1;i <= unmOfColumn;i++)
	{
		SetTableColumnAttribute(panel,control,i,ATTR_USE_LABEL_TEXT,1);	   //�������ף�ʹ���Զ�������
		SetTableColumnAttribute (panel, control,i, ATTR_COLUMN_WIDTH,260);
		SetTableCellVal(panel,control,MakePoint(i,1),Table_title_IT[i- 1]);  
	}
	return 0;
}

int AddValeToTable(int panel,int control,double* yval,double* xval)
{
	int row;
	InsertTableRows (panel,control,-1,1,VAL_CELL_NUMERIC);
	GetNumTableRows (panel,control, &row); 										  //�õ���ǰ����
	SetTableCellVal (panel,control, MakePoint (1,row),*yval);//��1�е�row��
	SetTableCellVal (panel,control, MakePoint (2,row),*xval);//��2�е�row��
	int MaxRow; //����tanle�߶Ⱥ���ʾ������ʾ���һ������ 
	GetNumTableRows(panel,control,&MaxRow);
	SetCtrlAttribute(panel,control,ATTR_FIRST_VISIBLE_ROW,MaxRow);
   return 0;
}

int FormatTable(int panel,int control)
{
  DeleteTableRows (panel, control, 1, -1);
  DeleteTableColumns (panel, control, 1, -1);
  return 0;
}
