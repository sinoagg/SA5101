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

#define  NPV_ADV                          1
#define  NPV_ADV_PIC_SET                  2       /* control type: picture, callback function: (none) */
#define  NPV_ADV_BSCSET                   3       /* control type: textMsg, callback function: NpvBasicSetCallback */
#define  NPV_ADV_DECORATION               4       /* control type: deco, callback function: (none) */
#define  NPV_ADV_IR_COMPENSATION          5       /* control type: textMsg, callback function: (none) */
#define  NPV_ADV_FEEDBACK_COMPENSATION    6       /* control type: radioButton, callback function: (none) */
#define  NPV_ADV_NO_COMPENSATION          7       /* control type: radioButton, callback function: (none) */

#define  NPV_CFG                          2
#define  NPV_CFG_INITIAL                  2       /* control type: numeric, callback function: (none) */
#define  NPV_CFG_PLUSEWIDTH               3       /* control type: numeric, callback function: (none) */
#define  NPV_CFG_FINAL                    4       /* control type: numeric, callback function: (none) */
#define  NPV_CFG_QUIETTIME                5       /* control type: numeric, callback function: (none) */
#define  NPV_CFG_SAMPLEWIDTH              6       /* control type: numeric, callback function: (none) */
#define  NPV_CFG_PLUSEPERIOD              7       /* control type: numeric, callback function: (none) */
#define  NPV_CFG_PIC_SET                  8       /* control type: picture, callback function: (none) */
#define  NPV_CFG_ADVCSET                  9       /* control type: textMsg, callback function: NpvAdvancSetCallback */
#define  NPV_CFG_PLUSE                    10      /* control type: numeric, callback function: (none) */
#define  NPV_CFG_INCR                     11      /* control type: numeric, callback function: (none) */
#define  NPV_CFG_CURRETNRANGE             12      /* control type: ring, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK NpvAdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK NpvBasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
