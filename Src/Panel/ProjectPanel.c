#include <userint.h>
#include "ProjectPanel.h"
#include "Load_Panel.h"
#define CHANGECOLOR 0x94CEFF//ǳ��
#define BGCOLOR 0xFFFFFF
#define COLOR  0x065279		//����
int CVICALLBACK OpenCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK ProExitCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{	
	
	 if(event==EVENT_COMMIT)
			  RemovePopup (prjPanel);  

	return 0;
}

int CVICALLBACK DefaultCallback (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute (panel, ATTR_BACKCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TXT, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TXT_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (prjPanel,PROPANEL_OPEN , ATTR_DIMMED, 0);
			SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, COLOR);
			break;
	}
	return 0;
}

int CVICALLBACK ImgCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	   int val;
	   GetCtrlVal(panel,PROPANEL_IMGBOX,&val);
	   if(event == EVENT_VAL_CHANGED){
	   
   			  if(val){
				   SetCtrlAttribute(prjListPanel, DEFPANEL_PICS, ATTR_VISIBLE,1);
				  
			  }else{
			  	 SetCtrlAttribute(prjListPanel, DEFPANEL_PICS, ATTR_VISIBLE,0);
			  }
   
   }
	return 0;
}

int CVICALLBACK DescCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
		 int val;
  		 GetCtrlVal(panel,PROPANEL_DESCBOX,&val);
  		 if(event == EVENT_VAL_CHANGED){
	   
   			  if(val){
				  SetCtrlAttribute(prjListPanel, DEFPANEL_TXT_DESC, ATTR_VISIBLE,1);
				   
			  }else{
			  	  SetCtrlAttribute (prjListPanel, DEFPANEL_TXT_DESC, ATTR_VISIBLE, 0);
			  }
   
   }
	return 0;
}

int CVICALLBACK SearchCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute (prjListPanel, ATTR_BACKCOLOR, BGCOLOR);
			SetCtrlAttribute (prjListPanel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (prjListPanel, DEFPANEL_TXT, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (prjListPanel, DEFPANEL_TXT_DESC, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (prjPanel,PROPANEL_OPEN , ATTR_DIMMED, 1);
			break;
	}
	return 0;
}