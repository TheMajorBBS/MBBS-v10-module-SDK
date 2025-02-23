/***************************************************************************
 *                                                                         *
 *   WORLDLNK.H                                                            *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Client side functions and structures.                                 *
 *                                                                         *
 *                                            - W. Muharsky 04/22/97       *
 *                                                                         *
 ***************************************************************************/
#ifndef __WORLDLNK_H
#define __WORLDLNK_H

#include "worcomn.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef VOID WORCONNECT;           /*  WorldLink connect function          */
typedef VOID WORDISCONNECT;        /*  WorldLink Disconnect routine        */
typedef VOID WORNODECONNECT;       /*  Node connect routine                */
typedef VOID WORNODEDISCONNECT;    /*  Node disconnect routine             */
typedef VOID WORCOMMANDHANDLER;    /*  Command handler routine             */
typedef VOID WORSQUELCHHANDLER;    /*  Squelch handler routine             */
typedef INT WORLIST;               /*  WorldLink listing function define   */


typedef WORCONNECT        (*pWORCONNECT)(VOID);
typedef WORDISCONNECT     (*pWORDISCONNECT)(VOID);
typedef WORNODECONNECT    (*pWORNODECONNECT)(const WORNODE *);
typedef WORNODEDISCONNECT (*pWORNODEDISCONNECT)(const WORNODE *);
typedef WORCOMMANDHANDLER (*pWORCOMMANDHANDLER)(SHORT,UINT,VOID *);
typedef WORSQUELCHHANDLER (*pWORSQUELCHHANDLER)(SHORT,UINT,VOID *);
typedef WORLIST           (*pWORLIST)(INT,INT);

typedef struct tagWORMODULE {      /* WorldLink module structure           */
     CHAR wappid[WAPSIZ];          /*  Module APPID                        */
     CHAR name[MNMSIZ];            /*  Name of the module                  */
     pWORCONNECT conrou;           /*  Your systems connect routine        */
     pWORDISCONNECT disrou;        /*  Your systems disconnect routine     */
     pWORNODECONNECT oconrou;      /*  Other boards connect routine        */
     pWORNODEDISCONNECT odisrou;   /*  Other boards disconnect routine     */
     pWORCOMMANDHANDLER cmdrou;    /*  Modules command handler routine     */
     pWORSQUELCHHANDLER squrou;    /*  Modules squelch handler routine     */
} WORMODULE,*pWORMODULE;

EXPWORV(CHAR) worGlobal;           /*  WorldLink global character          */
EXPWORV(CHAR) worGlobalSYS;        /*  WorldLink sysop global character    */
EXPWORV(CHAR) worBuff[WBUFSZ];     /*  WorldLink input buffer              */

EXPWORV(INT) worListon;            /*  Current number in ANSI/ASCII list   */

EXPWORV(UINT) worNodeNUM;          /*  Boards current node number          */

EXPWORV(HMCVFILE) wormsg;          /*  Worldlink message file pointer      */

// Ansi/ASCII list program #defines
#define LST_NEWPAG   -1            /*  New page being sent                 */
#define LST_DONE     -2            /*  Done with the list generator        */
#define LST_WAIPAG   -3            /*  Wait for a new page                 */

#define LST_CHAR     1             /*  Character was pushed, ret CHAR      */
#define LST_RETURN   2             /*  Return was pushed, ret which opt    */
#define LST_UPARR    3             /*  Up arrow was pushed                 */
#define LST_DWNARR   4             /*  Down arrow was pushed               */

#define WORMAXLST   25             /*  Maximum number of tokens in list    */

/***************************************************************************
 * Function prototypes for file: WORCORE.C                                 *
 ***************************************************************************/
GBOOL                              /*  TRUE on success                     */
worIsVirtualDomain(VOID);          /*  Is this system using virtual domain */

CHAR *                             /*  Regular userid or ""                */
worMailAliasToUser(                /* Change Mail alias to local userid    */
const CHAR *alias);                /*  Alias to transform                  */

CHAR *                             /*  Mail alias or ""                    */
worMailUserToAlias(                /* Change local userid to mail alias    */
const CHAR *uid);                  /*  Userid to transform                 */

GBOOL                              /* TRUE if you are able to extend       */
worExtend(                         /*  Extend WorldLink connect minutes    */
INT mins);                         /*  Number of minutes to extend time by */

GBOOL                              /* TRUE if a dialout is being attempted */
worConnect(                        /*  Connect WorldLink up                */
const CHAR *phone,                 /*  Phone number or NULL for default    */
INT mins);                         /*  Number of minutes to connect for    */

GBOOL                              /* TRUE if module iexists               */
worModuleExists(                   /*  Check if WorldLink mod is online    */
const CHAR *wappid);               /*  APPID of module to check            */

GBOOL                              /* TRUE if connected                    */
worConnected(VOID);                /*  Checks to see if WorldLink is conn  */

GBOOL                              /* TRUE if connected for module         */
worConnectedModule(                /*  Check if connected for specific mod */
const CHAR *wappid);               /*  APPID of module to check            */

GBOOL                              /* TRUE if connected only for module    */
worConnectedOnly(                  /*  Check if connected for mod only     */
const CHAR *wappid);               /*  APPID of module to check for        */

GBOOL                              /* TRUE if able to place call           */
worConnectModule(                  /*  Connect WorldLink w/ specific apps  */
const CHAR *phone,                 /*  Phone number or NULL for default    */
INT mins,                          /*  Number of minutes to connect for    */
const CHAR *waps);                 /*  APPIDS to connect for (space delim) */

GBOOL                              /* TRUE if userid has rating key        */
worRatingHaskeyUserid(             /*  Check userid permission on rating   */
const CHAR *uid,                   /*  Userid to check                     */
const CHAR *rating);               /*  Rating to check against userid      */

GBOOL                              /* TRUE if usaptr->userid has rating key*/
worRatingHaskey(                   /*  Check if current user has rating key*/
const CHAR *rating);               /*  Rating to check for                 */

GBOOL                              /* TRUE if uid has rating number access */
worRatingHaskeyUseridBynum(        /*  Check rating by number              */
const CHAR *uid,                   /*  Userid to check rating on           */
UINT rnum);                        /*  Rating number to check against      */

GBOOL                              /* TRUE if current user has rating num  */
worRatingHaskeyBynum(              /*  Check user rating by number         */
UINT rnum);                        /*  Number to check vs. current user    */

CHAR *                             /*  Pointer to the key                  */
worRatingKey(                      /* Get key for specific rating          */
const CHAR *rating);               /*  Rating to get key for               */

CHAR *                             /*  Pointer to rating key               */
worRatingKeyBynum(                 /* Get rating key by number             */
INT Number);                       /*  Number to search for                */

INT                                /* Number of bytes left in the          */
worOutputBytes(VOID);              /*  WorldLink channel output buffer     */

USHORT                             /* WorldLink Module number              */
worRegisterModule(                 /*  Register a WorldLink module         */
const WORMODULE *moddat);          /*  Pointer to WorldLink module struct  */

VOID
worSendNow(                        /*  Send something immediately          */
const CHAR *wappid,                /*  Wappid sending module               */
SHORT cmdnum,                      /*  Command number                      */
UINT length,                       /*  Length of the command               */
const VOID *inform);               /*  Info being sent                     */

VOID
worSend(                           /*  Send a command to the server        */
const CHAR *wappid,                /*  APPID of module sending command     */
SHORT cmdnum,                      /*  Command number (For callback)       */
UINT length,                       /*  Length of buffer being sent         */
const VOID *string);               /*  Buffer to send                      */

VOID
worSendFDA(                        /*  Send information with attached FDA  */
const CHAR *wappid,                /*  APPID of module sending command     */
SHORT cmdnum,                      /*  Command number (For callback)       */
UINT length,                       /*  Length of buffer being sent         */
const VOID *string,                /*  Buffer to send                      */
const struct flddef *fdef);        /*  FDA to apply to before before send  */

VOID
worExecute(                        /*  Call module command processer       */
const CHAR *wappid,                /*  Module APPID to call                */
SHORT cmdnum,                      /*  Command number to execute           */
UINT length,                       /*  Length of buffer to pass in         */
const VOID *stg);                  /*  Buffer to pass in                   */

VOID
worExecuteSquelch(                 /*  Execute module squelch routine      */
const CHAR *wappid,                /*  APPID of module to execute          */
SHORT cmdnum,                      /*  Command number to call              */
UINT length,                       /*  Length of command buffer            */
const VOID *stg);                  /*  Buffer to execute                   */

CHAR *                             /*  Pointer to WorldLink userid         */
worUseridMake(                     /*  Make WorldLink userid from local    */
const CHAR *userid);               /*  Userid to make from local one       */

/***************************************************************************
* Function prototype in file: WORLNK.C                                     *
****************************************************************************/
VOID
worAbortCall(                      /*  Abort current WorldLink connection  */
const CHAR *string);               /*  Reason why disconnect is happening  */


/***************************************************************************
* Function prototypes for file: WOREXT.C                                   *
****************************************************************************/
GBOOL                              /* TRUE if able to set file name        */
worFileNameSet(                    /*  Set incoming file name              */
const CHAR *fname);                /*  File name to set to                 */

GBOOL                              /* TRUE if able to set directory        */
worFileDirectorySet(               /*  Set directory of incoming file      */
const CHAR *dirstg);               /*  Directory to set file path to       */

GBOOL                              /* TRUE if outgoing file was aborted    */
worFileAbortSender(                /*  Abort an outgoing file transfer     */
LONG filnum);                      /*  File number to abort (assigned)     */

GBOOL                              /* TRUE if outgoing file was aborted    */
worFileAbortSenderCurrent(VOID);   /*  Abort current outgoing file         */

ULONG                              /* File size                            */
worFileSize(VOID);                 /*  Get incoming file size              */

LONG                               /* File number or various #defines      */
worSendFile(                       /*  Send a file to the WorldLink Server */
const CHAR *wappid,                /*  APPID of WorldLink program sending  */
SHORT cmdnum,                      /*  Command # to be called on server    */
const CHAR *file,                  /*  Full path and name of file          */
const CHAR *rname,                 /*  Real name of file                   */
pWORFILETRANSFER infrou);          /*  Information callback routine        */

VOID
worFileAbortReceiver(              /*  Abort an incoming file              */
INT reason);                       /*  Reason number (Will be passed over) */

VOID
worFileChunkSet(                   /*  Set the amount of checks per call   */
INT perchunk);                     /*  Number of chuncks per callback      */

VOID
worRegList(                        /*  Register/Start ANSI/ASCII list      */
INT  xcoord,                       /*  Xcoordinate on screen to print list */
INT  ycoord,                       /*  Ycoordinate on screen to print list */
INT  numlst,                       /*  Number of items in the list         */
CHAR *tlist[],                     /*  Pointer to the items in the list    */
pWORLIST rouptr);                  /*  Pointer to a routine to pass params */

VOID
worUpdateList(                     /*  Update a registered list            */
CHAR *tlist[],                     /*  Pointers to the new items in list   */
INT  numlst);                      /*  New number of items in the list     */

/***************************************************************************
* Function prototypes for file: WORSCN.C                                   *
****************************************************************************/
VOID
worSysopInjoth(VOID);              /*  INJOTH to all WorldLink Sysops      */

VOID
worDebug(                          /*  WorldLink debug function            */
const CHAR *wappid,                /*  APPID of the WorldLink module       */
INT  level,                        /*  Level of debug 1=LOW 3=HIGH         */
CHAR *string);                     /*  String to print in debug window     */

/***************************************************************************
 * Function prototypes for file: WORUSR.C                                  *
 ***************************************************************************/

VOID
worUserAssignNum(                  /*  Add a user to the WorldLink Memory  */
const CHAR *uid);                  /*  Userid to add to memory             */

VOID
worUserDeleteNum(                  /*  Remove a user from WorldLink Memory */
const CHAR *uid);                  /*  Userid to remove                    */


EXPWORF(INT,worGlobalHDL)(VOID);
EXPWORF(INT, worGlobalSysopHDL)(VOID);

EXPWORF(VOID,worGlobalHelpHDL)(VOID);
EXPWORF(VOID,worGlobalSysopHelpHDL)(VOID);

EXPWORF(VOID,worUsrAddHook)(const CHAR*);
EXPWORF(VOID,worUsrRemHook)(const CHAR*);

EXPWORF(GBOOL,worPreUsrDelHook)(const CHAR*);

#ifdef __cplusplus
}; // extern "C"
#endif
#endif //__WORLDLNK_H
