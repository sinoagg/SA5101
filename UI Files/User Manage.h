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

#define  USERPANEL                        1
#define  USERPANEL_LISTBOX_2              2       /* control type: listBox, callback function: (none) */
#define  USERPANEL_TEXTMSG                3       /* control type: textMsg, callback function: (none) */
#define  USERPANEL_LOOKALLUSER            4       /* control type: command, callback function: LookAllUser */
#define  USERPANEL_DELETEUSER             5       /* control type: command, callback function: DeleteUser */
#define  USERPANEL_ADDUSER                6       /* control type: command, callback function: AddUser */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AddUser(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DeleteUser(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LookAllUser(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
