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

#define  I_T_ADV                          1
#define  I_T_ADV_DECORATION               2       /* control type: deco, callback function: (none) */
#define  I_T_ADV_IR_COMPENSATION          3       /* control type: textMsg, callback function: (none) */
#define  I_T_ADV_BSCSET                   4       /* control type: textMsg, callback function: ItBasicSetCallback */
#define  I_T_ADV_FEEDBACK_COMPENSATION    5       /* control type: radioButton, callback function: (none) */
#define  I_T_ADV_NO_COMPENSATION          6       /* control type: radioButton, callback function: (none) */

#define  I_T_CFG                          2
#define  I_T_CFG_CURRENTRANGE             2       /* control type: ring, callback function: (none) */
#define  I_T_CFG_QUIETTIME                3       /* control type: numeric, callback function: (none) */
#define  I_T_CFG_RUNTIME                  4       /* control type: numeric, callback function: (none) */
#define  I_T_CFG_SAMPLEINTERVAL           5       /* control type: numeric, callback function: (none) */
#define  I_T_CFG_INITIAL                  6       /* control type: numeric, callback function: (none) */
#define  I_T_CFG_ADVCSET                  7       /* control type: textMsg, callback function: ItAdvancSetCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ItAdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ItBasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
