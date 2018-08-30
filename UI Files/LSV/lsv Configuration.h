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

#define  LSV_ADV                          1
#define  LSV_ADV_DECORATION               2       /* control type: deco, callback function: (none) */
#define  LSV_ADV_IR_COMPENSATION          3       /* control type: textMsg, callback function: (none) */
#define  LSV_ADV_PIC_SET                  4       /* control type: picture, callback function: (none) */
#define  LSV_ADV_BSCSET                   5       /* control type: textMsg, callback function: LsvBasicSetCallback */
#define  LSV_ADV_NO_COMPENSATION          6       /* control type: radioButton, callback function: (none) */
#define  LSV_ADV_FEEDBACK_COMPENSATION    7       /* control type: radioButton, callback function: (none) */

#define  LSV_CFG                          2
#define  LSV_CFG_QUIETTIME                2       /* control type: numeric, callback function: (none) */
#define  LSV_CFG_SAMPLEINTERVAL           3       /* control type: numeric, callback function: (none) */
#define  LSV_CFG_SCANRATE                 4       /* control type: numeric, callback function: (none) */
#define  LSV_CFG_PIC_SET                  5       /* control type: picture, callback function: (none) */
#define  LSV_CFG_ADVCSET                  6       /* control type: textMsg, callback function: LsvAdvancSetCallback */
#define  LSV_CFG_FINAL                    7       /* control type: numeric, callback function: (none) */
#define  LSV_CFG_CURRETNRANGE             8       /* control type: ring, callback function: (none) */
#define  LSV_CFG_INITIAL                  9       /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK LsvAdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LsvBasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
