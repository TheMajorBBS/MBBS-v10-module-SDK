/***************************************************************************
 *                                                                         *
 *   WORLDLNK.H                                                            *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Server side functions and structures.                                 *
 *                                                                         *
 *                                            - W. Muharsky 04/22/97       *
 *                                                                         *
 ***************************************************************************/
#ifndef __WORLDSRV_H
#define __WORLDSRV_H

#define WLSERVER                   /*  Generic WorldLink server define     */

#include "worcomn.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef GBOOL WORCONNECT;          /*  WorldLink connect routine           */
typedef VOID WORDISCONNECT;        /*  WorldLink disconnect routine        */
typedef VOID WORCOMMANDHANDLER;    /*  WorldLink command handler           */
typedef VOID WORSQUELCHHANDLER;    /*  WorldLink squelch handler           */
typedef GBOOL WORSENDCHECK;        /*  Send checking function              */
typedef GBOOL WORCYCLE;            /*  Cycling routine                     */

typedef WORCYCLE              (*pWORCYCLE)(VOID);
typedef WORCONNECT            (*pWORCONNECT)(const WORNODE *);
typedef WORDISCONNECT         (*pWORDISCONNECT)(const WORNODE *);
typedef WORCOMMANDHANDLER     (*pWORCOMMANDHANDLER)(SHORT,UINT,VOID*);
typedef WORSQUELCHHANDLER     (*pWORSQUELCHHANDLER)(SHORT,UINT,VOID*);
typedef WORSENDCHECK          (*pWORSENDCHECK)(INT,SHORT);

typedef struct WORMODULE {         /* WorldLink Server module structure    */
     CHAR wappid[WAPSIZ];          /*  WorldLink APPID                     */
     CHAR Name[MNMSIZ];            /*  WorldLink module name               */
     CHAR Key[KEYSIZ];             /*  Key required for access to module   */
     pWORCONNECT conrou;           /*  WorldLink node connect routine      */
     pWORDISCONNECT disrou;        /*  WorldLink node connect routine      */
     pWORCOMMANDHANDLER cmdrou;    /*  Module command routine              */
     pWORSQUELCHHANDLER squrou;    /*  Squelch command routine             */
     pWORSENDCHECK sndrou;         /*  Module send routine                 */
} WORMODULE,*pWORMODULE;

EXPWORV(CHAR) worBuff[WBUFSZ*2];   /*  WorldLink buffer                    */

EXPWORV(WORNODE) worNodeCurrent;   /*  Current WorldLink node (cmd rou)    */

#define worNodeptr     ((pWORNODE) &worNodeCurrent)

/***************************************************************************
* Function prototypes for file: SRVCORE.C                                  *
****************************************************************************/
VOID
worSendNow(                        /*  Send something immediately          */
INT number,                        /*  Channel number to send to           */
const CHAR *wappid,                /*  Wappid sending module               */
SHORT cmdnum,                      /*  Command number                      */
UINT length,                       /*  Length of the command               */
const VOID *inform);               /*  Info being sent                     */

VOID
worSendAllBut2(                    /*  Send command to all but 2 nodes     */
INT  number,                       /*  Node NOT to send to or -1           */
INT  number2,                      /*  Node NOT to send to or -1           */
const CHAR *wappid,                /*  APPID of module sending command     */
SHORT cmdnum,                      /*  Command number to process           */
UINT length,                       /*  Length of the command buffer        */
const VOID *inform);               /*  Command buffer                      */

VOID
worSend(                           /*  Send WorldLink command to a node    */
INT number,                        /*  Nodes usrnum                        */
const CHAR *wappid,                /*  APPID of module sending command     */
SHORT cmdnum,                      /*  Command number to execute           */
UINT length,                       /*  Length of the command buffer        */
const VOID *inform);               /*  Commad buffer                       */

VOID
worSendAllBut2FDA(                 /*  Send to all but 2 nodes with FDA    */
INT  number,                       /*  Node NOT to send to or -1           */
INT  number2,                      /*  Node NOT to send to or -1           */
const CHAR *wappid,                /*  APPID of module sending command     */
SHORT cmdnum,                      /*  Command number to process           */
UINT length,                       /*  Length of the command buffer        */
const VOID *string,                /*  Command buffer                      */
const struct flddef *fdef);        /*  FDA to apply to command buffer      */

VOID
worSendFDA(                        /*  Send WorldLink command with FDA     */
INT number,                        /*  Nodes usrnum                        */
const CHAR *wappid,                /*  APPID of module sending command     */
SHORT cmdnum,                      /*  Command number to execute           */
UINT length,                       /*  Length of the command buffer        */
const VOID *inform,                /*  Commad buffer                       */
const struct flddef *fdef);        /*  Field definition array to apply     */

VOID
worExecute(                        /*  Execute a WorldLink command         */
const CHAR *wappid,                /*  APPID to execute                    */
SHORT cmdnum,                      /*  Command number to execute           */
UINT length,                       /*  Length of the command               */
const VOID *stg);                  /*  Actual command                      */

VOID
worExecuteSquelch(                 /*  Execute a WorldLink squelch routine */
const CHAR *wappid,                /*  APPID to execute                    */
SHORT cmdnum,                      /*  Command number to execute           */
UINT length,                       /*  Length of command to execute        */
const VOID *stg);                  /*  Command buffer                      */

USHORT
worRegisterModule(                 /*  Register WorldLink Server module    */
const WORMODULE *moddat);          /*  Pointer to WorldLink server module  */

INT                                /* Usrnum of a node or -1               */
worNodeChannel(                    /*  Get the user number for a node      */
const CHAR *node);                 /*  Node to transfer into a usrnum      */

GBOOL                              /* TRUE if module exists                */
worModuleExists(                   /*  Check if module exists on server    */
const CHAR *wappid);               /*  APPID to check for                  */

GBOOL                              /* TRUE if client has module online     */
worModuleExistsClient(             /*  Checks if client has module         */
INT unum,                          /*  Usernumber to check                 */
const CHAR *wappid);               /*  Module to check for                 */

CHAR *                             /* Pointer to WorldLink userid          */
worUseridMake(                     /*  Make a WorldLink userid from board  */
INT bnum,                          /*  Board number to make userid from    */
const CHAR *uid);                  /*  Userid to make into WorldLini uid   */

CHAR *                             /* Pointer to registratino number       */
worNodeToReg(                      /*  Get reg # given system ID           */
const CHAR *id);                   /*  Node ID to transform                */

CHAR *                             /*  Pointer to board id or ""           */
worRegToNode(                      /* Transform reg# to Node ID            */
const CHAR *reg);                  /*  Reg number to look up by            */

VOID
worDebug(                          /*  WorldLink debug command             */
const CHAR *string);               /*  String to display in debug window   */

#define worSendAll(a,b,c,d)             worSendAllBut2(-1,-1,a,b,c,d)
#define worSendAllBut(a,b,c,d,e)        worSendAllBut2(a,-1,b,c,d,e)
#define worSendAllFDA(a,b,c,d,e)        worSendAllBut2FDA(-1,-1,a,b,c,d,e)
#define worSendAllButFDA(a,b,c,d,e,f)   worSendAllBut2FDA(a,-1,b,c,d,e,f)

/***************************************************************************
* Function prototypes for file: SRVEXT.C                                   *
****************************************************************************/
GBOOL                              /* TRUE if able to set file             */
worFileNameSet(                    /*  Set incoming file name              */
UINT Channel,                      /*  User number of board to set         */
const CHAR *fname);                /*  File name to set                    */

GBOOL                              /* TRUE if able to set directory        */
worFileDirectorySet(               /*  Set incoming file directory         */
UINT Channel,                      /*  Channel number to set               */
const CHAR *dirstg);               /*  Directory to set to                 */

GBOOL                              /* TRUE if able to abort file           */
worFileAbortSender(                /*  Abort the sending of a file         */
UINT Channel,                      /*  Board number to abort file on       */
LONG filnum);                      /*  File number to abort                */

GBOOL                              /*  TRUE if able to abort file          */
worFileAbortSenderCurrent(         /*  Abort sending of current file       */
UINT Channel);                     /*  User number to abort transfer on    */

VOID
worFileAbortReceiver(              /*  Abort the receiving of a file       */
UINT Channel,                      /*  User number to abort from           */
INT reason);                       /*  Reson for abort (transmitted)       */

VOID
worFileChunkSet(                   /*  Set the amount of chunks/callback   */
UINT Channel,                      /*  User number to check                */
INT perchunk);                     /*  Amount of chunks per callback       */

ULONG                              /* Size of incoming file                */
worFileSize(                       /*  Get size of incoming file           */
UINT Channel);                     /*  User number of incoming file        */

LONG                               /* File number or #define ERROR         */
worSendFile(                       /*  Send a file to the client           */
UINT Channel,                      /*  User number to send to              */
const CHAR *wappid,                /*  APPID to call when done             */
SHORT cmdnum,                      /*  Command number to call              */
const CHAR *file,                  /*  Actual file/full path to send       */
const CHAR *rname,                 /*  Real file name                      */
pWORFILETRANSFER infrou);          /*  Info routine or NULL                */

/***************************************************************************
* Function prototypes for file: SRVCYCLE.C                                 *
****************************************************************************/
VOID
worCycle(                          /*  WorldLink Cycle routine             */
INT unum,                          /*  Usrnum context to be current        */
pWORCYCLE cycrou);                 /*  Pointer to routine to cycle         */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif //__WORLDSRV_H
