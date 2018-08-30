/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  SCV_ADV                          1
#define  SCV_ADV_PIC_SET                  2       /* control type: picture, callback function: (none) */
#define  SCV_ADV_BSCSET                   3       /* control type: textMsg, callback function: ScvBasicSetCallback */
#define  SCV_ADV_DECORATION               4       /* control type: deco, callback function: (none) */
#define  SCV_ADV_IR_COMPENSATION          5       /* control type: textMsg, callback function: (none) */
#define  SCV_ADV_FEEDBACK_COMPENSATION    6       /* control type: radioButton, callback function: (none) */
#define  SCV_ADV_NO_COMPENSATION          7       /* control type: radioButton, callback function: (none) */

#define  SCV_CFG                          2
#define  SCV_CFG_INITIAL                  2       /* control type: numeric, callback function: (none) */
#define  SCV_CFG_FINAL                    3       /* control type: numeric, callback function: (none) */
#define  SCV_CFG_STEPPERIODS              4       /* control type: numeric, callback function: (none) */
#define  SCV_CFG_QUIETTIME                5       /* control type: numeric, callback function: (none) */
#define  SCV_CFG_SAMPLEWIDTH              6       /* control type: numeric, callback function: (none) */
#define  SCV_CFG_INCR                     7       /* control type: numeric, callback function: (none) */
#define  SCV_CFG_PIC_SET                  8       /* control type: picture, callback function: (none) */
#define  SCV_CFG_ADVCSET                  9       /* control type: textMsg, callback function: ScvAdvancSetCallback */
#define  SCV_CFG_CURRETNRANGE             10      /* control type: ring, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ScvAdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ScvBasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
