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

#define  CP_ADV                           1
#define  CP_ADV_PIC_SET                   2       /* control type: picture, callback function: (none) */
#define  CP_ADV_BSCSET                    3       /* control type: textMsg, callback function: CpBasicSetCallback */
#define  CP_ADV_DECORATION                4       /* control type: deco, callback function: (none) */
#define  CP_ADV_IR_COMPENSATION           5       /* control type: textMsg, callback function: (none) */
#define  CP_ADV_FEEDBACK_COMPENSATION     6       /* control type: radioButton, callback function: (none) */
#define  CP_ADV_NO_COMPENSATION           7       /* control type: radioButton, callback function: (none) */
#define  CP_ADV_INTIALPLLITY              8       /* control type: ring, callback function: (none) */
#define  CP_ADV_CURRENTSP                 9       /* control type: ring, callback function: (none) */

#define  CP_CFG                           2
#define  CP_CFG_DATASTORGEINTVL           2       /* control type: numeric, callback function: (none) */
#define  CP_CFG_ANODICTIMES               3       /* control type: numeric, callback function: (none) */
#define  CP_CFG_CATHODICTIMES             4       /* control type: numeric, callback function: (none) */
#define  CP_CFG_LOWEHOLDTIMES             5       /* control type: numeric, callback function: (none) */
#define  CP_CFG_LOWELIMIT                 6       /* control type: numeric, callback function: (none) */
#define  CP_CFG_HIGHEHOLDTIMES            7       /* control type: numeric, callback function: (none) */
#define  CP_CFG_PIC_SET                   8       /* control type: picture, callback function: (none) */
#define  CP_CFG_ADVCSET                   9       /* control type: textMsg, callback function: CpAdvancSetCallback */
#define  CP_CFG_HIGHELIMIT                10      /* control type: numeric, callback function: (none) */
#define  CP_CFG_ANODICCURRENT             11      /* control type: numeric, callback function: (none) */
#define  CP_CFG_CATHODICCURRENT           12      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CpAdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CpBasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
