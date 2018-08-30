#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>

#include "system_ini.h"
#include "Load_Panel.h"
#include "MainPanelCb.h" 

unsigned char comSelect;				//Serial Com Number


int CVICALLBACK ComCallback(int portNumber ,int eventMask, void * callbackData);
int CheckPortStatus(int portNumber,void (*pFun)(int,int,void*));

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
    //comSelect=argc;		//pass comSelect variable 
	/*comSelect= 3;
	if((CheckPortStatus(comSelect,ComCallback)) < 0)
		return -1;*/
	LoadInitPanel ();
	RunUserInterface ();
	CloseCom(comSelect);
	int temp = DiscardPanel (mainPanel);
	SaveSystemClose(temp);
	return 0;
}

int CVICALLBACK ComCallback(int portNumber ,int eventMask, void * callbackData)
{
	int expType;
	if(GetCtrlVal(expListPanel, EXP_LIST_LISTBOX_2, &expType)<0)
		return -1;
	switch(expType)
	{
		case 1:
			break;
		case 2:
			
			
			
            break;
		case 3:
			break;
		case 12:
			receive_itdataanalysis(); 
			break;
	}
	return 0;
}

int CheckPortStatus(int portNumber,void (*pFun)(int,int,void*))
{
    int status;  
	status = OpenComConfig(portNumber, "", 115200, 0, 8, 1, 512, 512);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected!");
		return -1;
	}
	InstallComCallback (portNumber, LWRS_RECEIVE, 12, 0, pFun, 0);   //binding Callback function to serial input data 12 bytes received will calling for an interrupt
	SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
	FlushInQ(portNumber);	   //Clear input and output buffer
	FlushOutQ(portNumber);
	
	return 0;
}





