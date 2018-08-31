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

#define  MAIN_PANEL                       1       /* callback function: MAIN_PANEL_CallBack */
#define  MAIN_PANEL_PICTURE_3             2       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_PICTURE_8             3       /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_3             4       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_2             5       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG               6       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_5             7       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_4             8       /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS                9       /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_6             10      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_PROJECTS              11      /* control type: picture, callback function: ProjectCallback */
#define  MAIN_PANEL_TOOLS                 12      /* control type: picture, callback function: (none) */
#define  MAIN_PANEL_SETTINGS              13      /* control type: picture, callback function: SettingsCallback */
#define  MAIN_PANEL_TEXTMSG_8             14      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_9             15      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_7             16      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_CANVAS_3              17      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_STOP                  18      /* control type: picture, callback function: StopCallback */
#define  MAIN_PANEL_RUN                   19      /* control type: picture, callback function: RunCallback */
#define  MAIN_PANEL_SELECT                20      /* control type: picture, callback function: SelectCallback */
#define  MAIN_PANEL_CONFIGURE             21      /* control type: picture, callback function: ConfigureCallback */
#define  MAIN_PANEL_ANALYZE               22      /* control type: picture, callback function: AnalyzeCallback */
#define  MAIN_PANEL_CANVAS_2              23      /* control type: canvas, callback function: (none) */
#define  MAIN_PANEL_SAVE                  24      /* control type: picture, callback function: SaveCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AnalyzeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ConfigureCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MAIN_PANEL_CallBack(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ProjectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SelectCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
