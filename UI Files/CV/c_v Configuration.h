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

#define  C_V_ADV                          1
#define  C_V_ADV_PIC_SET                  2       /* control type: picture, callback function: (none) */
#define  C_V_ADV_BSCSET                   3       /* control type: textMsg, callback function: CvBasicSetCallback */
#define  C_V_ADV_DECORATION               4       /* control type: deco, callback function: (none) */
#define  C_V_ADV_IR_COMPENSATION          5       /* control type: textMsg, callback function: (none) */
#define  C_V_ADV_FEEDBACK_COMPENSATION    6       /* control type: radioButton, callback function: (none) */
#define  C_V_ADV_NO_COMPENSATION          7       /* control type: radioButton, callback function: (none) */
#define  C_V_ADV_INTIALSCANPOLARITY       8       /* control type: ring, callback function: (none) */

#define  C_V_CFG                          2
#define  C_V_CFG_SWEEPSEGMENTS            2       /* control type: numeric, callback function: (none) */
#define  C_V_CFG_QUIETTIME                3       /* control type: numeric, callback function: (none) */
#define  C_V_CFG_SAMPLEINTERVAL           4       /* control type: numeric, callback function: (none) */
#define  C_V_CFG_SCANRATE                 5       /* control type: numeric, callback function: (none) */
#define  C_V_CFG_FINAL                    6       /* control type: numeric, callback function: (none) */
#define  C_V_CFG_LOW                      7       /* control type: numeric, callback function: (none) */
#define  C_V_CFG_HIGH                     8       /* control type: numeric, callback function: (none) */
#define  C_V_CFG_ADVCSET                  9       /* control type: textMsg, callback function: CvAdvancSetCallback */
#define  C_V_CFG_INITIAL                  10      /* control type: numeric, callback function: (none) */
#define  C_V_CFG_CURRETNRANGE             11      /* control type: ring, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CvAdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CvBasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
