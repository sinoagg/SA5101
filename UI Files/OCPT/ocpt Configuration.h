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

#define  OCPT_ADV                         1
#define  OCPT_ADV_PIC_SET                 2       /* control type: picture, callback function: (none) */
#define  OCPT_ADV_BSCSET                  3       /* control type: textMsg, callback function: OcptBasicSetCallback */
#define  OCPT_ADV_DECORATION              4       /* control type: deco, callback function: (none) */
#define  OCPT_ADV_IR_COMPENSATION         5       /* control type: textMsg, callback function: (none) */
#define  OCPT_ADV_FEEDBACK_COMPENSATION   6       /* control type: radioButton, callback function: (none) */
#define  OCPT_ADV_NO_COMPENSATION         7       /* control type: radioButton, callback function: (none) */

#define  OCPT_CFG                         2
#define  OCPT_CFG_RUNTIME                 2       /* control type: numeric, callback function: (none) */
#define  OCPT_CFG_SAMPLEINTERVAL          3       /* control type: numeric, callback function: (none) */
#define  OCPT_CFG_CURRENTRANGE            4       /* control type: ring, callback function: (none) */
#define  OCPT_CFG_HIGHELIMIT              5       /* control type: numeric, callback function: (none) */
#define  OCPT_CFG_LOWELIMIT               6       /* control type: numeric, callback function: (none) */
#define  OCPT_CFG_ADVCSET                 7       /* control type: textMsg, callback function: OcptAdvancSetCallback */
#define  OCPT_CFG_PIC_SET                 8       /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OcptAdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OcptBasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
