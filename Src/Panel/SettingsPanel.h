/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>
#include "Curve.h"

#ifdef __cplusplus
    extern "C" {
#endif
		
#define GRAPH1 0
#define GRAPH2 1
#define CURVE1 0
#define CURVE2 1  
#define CURVE3 2 
		
		
Curve_TypeDef* GetSettingsCurveAttr(int GraphIndex, int CurveIndex);

int CVICALLBACK EnvBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2);
int CVICALLBACK GraphBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2);
int CVICALLBACK AboutBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2);
int CVICALLBACK CancelCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2);
int CVICALLBACK ProCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2);

#ifdef __cplusplus
    }
#endif
