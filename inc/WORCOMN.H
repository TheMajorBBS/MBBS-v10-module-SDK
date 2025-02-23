/***************************************************************************
 *                                                                         *
 *   WORCOMN.H                                                             *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Common functions/structures WorldLink Server/Client                   *
 *                                                                         *
 *                                            - W. Muharsky 04/17/97       *
 *                                                                         *
 ***************************************************************************/
#ifndef __WORCOMN_H
#define __WORCOMN_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __BUILDWORLNK
#define EXPWORV(x)       EXPORT_VARIABLE(x)
#define EXPWORF(x,y)     EXPORT_FUNCTION(x, y)
#else
#define EXPWORV(x)       IMPORT_VARIABLE(x)
#define EXPWORF(x,y)     IMPORT_FUNCTION(x, y)
#endif // __BUILDWGSERVER

#define STGLEN  ((USHORT)0xFFFF)   /* pass as length for string length     */
                                   /* (same as that defined in GCSP.H)     */

#define WUSEPCHR     '@'           /*  WorldLink Userid seperator as CHAR  */
#define WUSEPSTG     "@"           //  WorldLink Userid seperator as CHAR* */

#define WNUMRAT     4              /*  Number of WorldLink board ratings   */
#define WRATSIZ     20			/*  Max size of rating variable		*/
#define WBUFSZ      16000          /*  WorldLink buffer size               */
#define WAPSIZ      10             /*  WorldLink Module Application size   */
#define WBOASIZ     64             /*  Board ID size including the NULL    */
#define WUIDSIZ     (UIDSIZ+WBOASIZ)/* WorldLink userid size               */
#define INFSIZ      30             /*  Information size                    */
#define DAYPWK      7              /*  Days in 1 week                      */
#define BBSSIZ      30             /*  Size of bbs in datafile             */
#define WPHOSIZ     15             /*  Phone size                          */
#define CITSIZ      40             /*  Size of city/state                  */
#define BLUSIZ      30             /*  Blurb size                          */
#define WALSIZ      30             /*  WorldLink Alias size                */
#define WORWAP      "WORLNK"       /*  WorldLink Wappid                    */

#define WLUSER_NOT_FOUND      ((ULONG)-1)/* WorldLink user not found       */
#define WLUSERS_PER_BOARD     20000/*  MAX number of users per board       */
#define WLUSER_AGEGROUPS      11   /*  Break down stats by age group       */

typedef VOID WORFILETRANSFER;      /*  File transfer pointer function      */
typedef WORFILETRANSFER       (*pWORFILETRANSFER)(LONG,CHAR*,SHORT,INT);

typedef struct tagWORUSER {        /* WorldLink Userid information         */
     CHAR Userid[UIDSIZ];          /*  Real userid of person               */
     CHAR Alias[UIDSIZ];           /*  Alias of the person                 */
     USHORT BoardNumber;           /*  Board number user belongs to        */
     ULONG UserNumber;             /*  Assigned user number                */
     USHORT Age;                   /*  Age of person                       */
     SHORT Flags;                  /*  Misc flags to store on person       */
} WORUSER,*pWORUSER;

#define WLUSER_MALE       1        /*  User is male                        */
#define WLUSER_FEMALE     2        /*  User is female                      */
#define WLUSER_INVIS      4        /*  User is invisible                   */
#define WLUSER_ALIAS      8        /*  User wants to be know by alias      */
#define WLUSER_SQUELCHED  16       /*  User is squelched from system       */

typedef struct tagWORNODE {        /* Node information structure           */
     CHAR ID[WBOASIZ];             /*  Board ID letters                    */
     CHAR Name[BBSSIZ];            /*  Name of the board                   */
     CHAR Phone[WPHOSIZ];          /*  Phone number of the board           */
     CHAR City[CITSIZ];            /*  City/State of BBS                   */
     CHAR Sysop[UIDSIZ];           /*  Sysops Name or Userid               */
     CHAR Blurb[BLUSIZ];           /*  Information about board             */
     CHAR ipaddr[BLUSIZ];          /*  IP Address of board                 */
     CHAR webaddr[BLUSIZ];         /*  World Wide Web address              */
     USHORT Number;                /*  WorldLink Node Number               */
     SHORT Timezone;               /*  Timezone the board is in            */
     SHORT Rating;                 /*  Nodes rating...                     */
} WORNODE,*pWORNODE;

EXPWORV(struct flddef) fdaWORNODE[];

typedef struct tagWORFILEINFO {    /* File information (transferring)      */
     INT status;                   /*  #define status of structure         */
     USHORT date;                  /*  Date stamp of the file              */
     USHORT time;                  /*  Time stamp of the file              */
     ULONG totsiz;                 /*  Total size of the file              */
     ULONG sizdon;                 /*  Total size actually done            */
     CHAR dlpath[GCMAXPTH];        /*  Full path (without filename)        */
     CHAR filnam[GCSTRFNM];        /*  File information                    */
     CHAR rfilnam[GCSTRFNM];       /*  The real file name                  */
} WORFILEINFO,*pWORFILEINFO;

#define worFileInfo      ((pWORFILEINFO) worBuff)

//defines for file information status
#define FST_START        0         /*  Start of file transfer (information)*/
#define FST_CHUNK        1         /*  Chunk information (If requested)    */
#define FST_DONE         2         /*  Done with the file transfer         */

EXPWORV(UINT) worBuffSize;         /*  Current buffer size                 */

EXPWORV(GBOOL) worSquelchedBoard;  /* True if a BOARD was squelched        */

EXPWORV(SHORT) worCommand;         /*  Current command being processed     */

EXPWORV(CHAR) worRatings[WNUMRAT][WRATSIZ];/* Array of ratings             */
EXPWORV(CHAR*) worDirectorySTG;    /*  Current WorldLink working directory */

EXPWORF(VOID,worUserInvis)(const WORUSER *wu,GBOOL invis);

#define worDirectory(x)                spr("%s\\%s", worDirectorySTG, x)

//Returns to file sending callback handlers
#define SND_NOROOM   -1            /*  No room for file (never happens)    */
#define SND_INVAPP   -2            /*  Invalid appid, (not on this system  */
#define SND_INVOAP   -3            /*  Other board does not have this APP  */
#define SND_FINISH   -4            /*  Finished transferring file          */
#define SND_ABORTD   -5            /*  Connection was aborted              */
#define SND_NOCONN   -6            /*  There is no connect, can not send   */
#define SND_NOFILE   -7            /*  File not found                      */
#define SND_ERRFIL   -8            /*  Error in the real file name         */
#define SND_ERROPN   -9            /*  Error opening file                  */
#define SND_EROSPC   -10           /*  No disk space on other system       */
#define SND_ERORCV   -11           /*  Other system alread receving file   */

/***************************************************************************
* Function prototypes for file: WORCOMN.C                                  *
****************************************************************************/
UINT                               /*  Number of people squelched          */
worNumSquelched(VOID);             /* Get number of people/nodes squelched */

CHAR *                             /*  Pointer to Squelched info or ""     */
worSquelchListBynum(               /* Get list of squelched nodes/users    */
UINT Index);                       /*  0 to worNumSquelched                */

CHAR *                             /* Next string or ""                    */
worSquelchList(                    /*  Get a list of squelched users       */
const CHAR *stg);                  /*  "" to start, or returned previous   */

CHAR *                             /* Pointer to unmade userid             */
worUseridUnmake(                   /*  Take WorldLink user, make local     */
const CHAR *uid);                  /*  Userid to transform                 */

CHAR *                             /* Node ID                              */
worNodeID(                         /*  Get Node ID of WorldLink user       */
const CHAR *userid);               /*  WorldLink userid to get node from   */

CHAR *                             /* Pointer to Node ID                   */
worFindNodeID(                     /*  Find Node inside of string          */
const CHAR *userid);               /*  WorldLink userid to get node from   */

GBOOL                              /*  Returns TRUE if this is a valid ID  */
worUseridValid(                    /*  Check userid for valid structure    */
const CHAR *uid);                  /*  Userid to check (W-W/O BoardID)     */

GBOOL                              /* TRUE if still copying                */
worIsCopying(                      /*  Check if file is still copying      */
const CHAR *from);                 /*  Full name and path of file to check */

GBOOL                              /* TRUE if able to create directory     */
worMkdir(                          /*  Create FULL directory (Long path)   */
CHAR *bigdir);                     /*  Full path name to create            */

GBOOL                              /* TRUE if able to create temp file     */
worFileCreateTemp(                 /*  Create a temporary file             */
const CHAR *dir,                   /*  Directory to create the file in     */
CHAR *fil);                        /*  Buffer to save the file name in     */

GBOOL                              /* TRUE if file name is valid           */
worFilenameValid(                  /*  Filename valid function             */
const CHAR *filename);             /*  Filename to check.  This function   */
                                   /*  was mainly done for backwards       */
                                   /*  compatibility to 2.00               */

GBOOL                              /* TRUE if value contains squelched stg */
worSquelched(                      /*  Check if something is squelched     */
UINT length,                       /*  Length of buffer to check           */
const CHAR *value);                /*  String to check for squelched       */

GBOOL                              /* FALSE if string is already squeched  */
worSquelchAdd(                     /*  Add a string to the squelch list    */
const CHAR *stg);                  /*  String to add                       */

GBOOL                              /* TRUE if string was removed           */
worSquelchDelete(                  /*  Remove something from squelch list  */
const CHAR *stg);                  /*  String to remove                    */

GBOOL                              /* TRUE if the node is a valid ID       */
worNodeValid(                      /*  Check if the ID is a valid ID       */
const CHAR *id);                   /*  ID to check                         */

INT                                /* Number of bytes new structure is     */
worConvertFDA(                     /*  Convert FDA in place                */
const struct flddef *fdef);        /*  FDA to use on convert               */

INT                                /* Rating number or -1                  */
worRatingNum(                      /*  Get rating number given string      */
const CHAR *rate);                 /*  String rating to check              */

LONG                               /* Hundredths of seconds since 00:00:00 */
worGetHund(VOID);                  /*  Timing function                     */

VOID
worCopyFileNOW(                    /*  Copy a file (pause system)          */
const CHAR *file1,                 /*  Full path and file to copy          */
const CHAR *file2);                /*  Full path and file to copy to       */

VOID
worCopyFile(                       /*  Copy a file in cycles               */
const CHAR *from,                  /*  Full path and file to copy          */
const CHAR *to,                    /*  Full path and file to copy to       */
SHORT priority,                    /*  Priority (Lower number = high prior)*/
SHORT deldon);                     /*  TRUE to delete when done            */

/***************************************************************************
* Function prototypes for file: WORUSR.C                                   *
****************************************************************************/
CHAR *                             /*  Pointer to userid                   */
worUserToUserid(                   /* Take user pointer, convert to UID@.. */
const WORUSER *wu);                /*  Pointer to WorldLink User Info      */

CHAR *                             /*  Pointer to alias                    */
worUserToAlias(                    /* Take user pointer, convert to ALS@.. */
const WORUSER *wu);                /*  Pointer to WorldLink User Info      */

GBOOL                              /*  TRUE if board is found              */
worNodeFirst(                      /* Gets first node that can be found    */
pWORNODE buf);                     /*  Buffer to copy into                 */

GBOOL                              /*  TRUE if next board is found         */
worNodeNext(                       /* Get next node in line                */
pWORNODE buf);                     /*  Buffer to copy into                 */

GBOOL                              /*  TRUE if user is found               */
worUserFirstWorld(                 /* Find first WorldLink user            */
pWORUSER buf);                     /*  Buffer to store info in             */

GBOOL                              /*  TRUE if next user is found          */
worUserNextWorld(                  /* Find next WorldLink user             */
pWORUSER buf);                     /*  Buffer to store info in             */

VOID
worUserAdd(                        /*  Add a WorldLink user to memory      */
WORUSER *wu);                      /*  Pointer to WorldLink user memory    */

GBOOL                              /*  TRUE if user is found               */
worUserFirstLocal(                 /* Find first local user                */
pWORUSER buf);                     /*  Buffer to store info in             */

GBOOL                              /*  TRUE if next user is found          */
worUserNextLocal(                  /* Find next local user                 */
pWORUSER buf);                     /*  Buffer to store info in             */

ULONG                              /*  WorldLink user number               */
worAliasToNumber(                  /* Transform alias into number          */
const CHAR *Alias);                /*  Alias to transform                  */

GBOOL                              /*  TRUE if user is found for node      */
worUserFirstNode(                  /* Find first user from node            */
pWORUSER buf,                      /*  Buffer to store info in             */
const CHAR *Node);                 /*  Node to find user from              */

GBOOL                              /*  TRUE if next user could be found    */
worUserNextNode(                   /* Find next user from node             */
pWORUSER buf);                     /*  Buffer to store info in             */

ULONG                              /*  WorldLink user number               */
worUseridToNumber(                 /* Translate userid into number         */
const CHAR *uid);                  /*  Userid to transform                 */

CHAR *                             /*  Pointer to userid                   */
worAliasToUserid(                  /* Transform alias into full userid     */
const CHAR *Alias);                /*  Alias to look up                    */

CHAR *                             /*  Pointer to user alias               */
worUseridToAlias(                  /* Userid to alias transform            */
const CHAR *uid);                  /*  Userid to look up                   */

CHAR *                             /*  Userid that number belongs to       */
worNumberToUserid(                 /* Translate userid from number         */
ULONG Number);                     /*  Number to look up as                */

CHAR *                             /*  Alias that number belongs to        */
worNumberToAlias(                  /* Translate alias from number          */
ULONG Number);                     /*  Number to look up as                */

GBOOL                              /*  TRUE if user exists                 */
worGetUserInfo(                    /* Get user info                        */
pWORUSER buf,                      /*  Buffer to write into                */
const CHAR *uid);                  /*  Userid to look up by                */

GBOOL                              /*  TRUE if user exists                 */
worGetUserInfoByAlias(             /* Get user info by alias               */
pWORUSER buf,                      /*  Buffer to write into                */
const CHAR *Alias);                /*  Alias to look up by                 */

GBOOL                              /*  TRUE if user exists                 */
worGetUserInfoByNumber(            /* Get user information                 */
pWORUSER buf,                      /*  Buffer to write into                */
LONG Number);                      /*  Number to look up by                */

CHAR *                             /* Name of node in memory               */
worNodeName(                       /*  Get node name from ID               */
const CHAR *id);                   /*  Node ID to search                   */

CHAR *                             /* Phone number of node in memory       */
worNodePhone(                      /*  Get phone number of node in memory  */
const CHAR *id);                   /*  Node ID to search                   */

CHAR *                             /* City name of node in memory          */
worNodeCity(                       /*  Get city of node in memory          */
const CHAR *id);                   /*  Node ID to search                   */

CHAR *                             /* Sysop name of node in memory         */
worNodeSysop(                      /*  Get sysop name of node              */
const CHAR *id);                   /*  Node ID to search                   */

CHAR *                             /* Blurb of node in memory              */
worNodeBlurb(                      /*  Get blurb of node in memory         */
const CHAR *id);                   /*  Node ID to search                   */

CHAR *                             /* IP Address of node in memory         */
worNodeIP(                         /*  Get IP address of node              */
const CHAR *id);                   /*  Node ID to search                   */

CHAR *                             /* WEB Address of node in memory        */
worNodeWEB(                        /*  Get WEB address of node             */
const CHAR *id);                   /*  Node ID to search                   */

GBOOL                              /* TRUE if user is online               */
worUserOnline(                     /*  Check if user is oline (Like ONSYS) */
const CHAR *userid);               /*  Userid to check                     */

GBOOL                              /* TRUE if node is linked               */
worNodeLinked(                     /*  Check if a node is currently linked */
const CHAR *node);                 /*  Node to check                       */

SHORT                              /* Timzone the node is in               */
worNodeTimezone(                   /*  Get timezone of Node                */
const CHAR *id);                   /*  Node to retrieve timezone for       */

SHORT                              /* Returns nodes rating number          */
worNodeRating(                     /*  Get nodes rating number             */
const CHAR *id);                   /*  Node to get rating number for       */

UINT                               /* 1=MALE, 0=FEMALE                     */
worUserSex(                        /*  Get a users sex                     */
const CHAR *userid);               /*  Userid to check                     */

USHORT                             /* Node number of board                 */
worNodeNumber(                     /*  Gets the assigned node number       */
const CHAR *id);                   /*  Node to get the number of           */

ULONG                              /* Total number of users on all nodes   */
worUsers(VOID);                    /*  Gets total users                    */

ULONG                              /* Total number of male users           */
worUsersMale(VOID);                /*  Gets total number of male users     */

ULONG                              /* Total number of local male users     */
worUsersLocalMale(VOID);           /*  Gets number of local male users     */

ULONG                              /* Total number of female users         */
worUsersFemale(VOID);              /*  Gets number of female users         */

ULONG                              /* Number of users in age groups        */
worUsersAge(                       /*  Number of users in age groups       */
INT sex,                           /*  1=MALE, 0=FEMALE                    */
INT group);                        /*  0=<10 ... 10=100>                   */

ULONG                              /* Total of local users                 */
worUsersLocal(VOID);               /*  Total of local users                */

ULONG                              /* Total number of local female users   */
worUsersLocalFemale(VOID);         /*  Gets number of local female users   */

ULONG                              /* Total of WorldLink users (not local) */
worUsersWorld(VOID);               /*  Gets number of WorldLink Users      */

ULONG                              /* Total WorldLink male users           */
worUsersWorldMale(VOID);           /*  Total WorldLink male users          */

ULONG                              /* Total number of WorldLink males      */
worUsersWorldFemale(VOID);         /*  Gets number of WorldLink males      */

UINT                               /*  Number of Nodes currently linked    */
worNodes(VOID);                    /*  Get number of nodes linked          */

UINT                               /* Age of specific user (or 0)          */
worUserAge(                        /*  Get age of a user                   */
const CHAR *userid);               /*  Userid to get age of                */

UINT                               /* Users on a specific node             */
worUsersNode(                      /*  Gets users on specific node         */
const CHAR *nodeid);               /*  Node to count users on              */

VOID
worUserDump(VOID);                 /*  Dumps a text file of userid info    */

VOID
worUserDelete(                     /*  Delete a user from memory           */
const CHAR *uid);                  /*  Userid to delete                    */

VOID
worNodeInfo(                       /*  Get information on a node           */
pWORNODE datbuf,                   /*  Buffer to copy information to       */
const CHAR *let);                  /*  Node id to get info on              */

VOID
worNodeInfoBynum(                  /*  Get node information by number      */
pWORNODE datbuf,                   /*  Data buffer                         */
USHORT Number);                    /*  Number to search on                 */

VOID
worNodeAdd(                        /*  Add a node to memory                */
const WORNODE *boaptr);            /*  Node structure to add to memory     */

VOID
worNodeDelete(                     /*  Remove a node from memory           */
const CHAR *let);                  /*  Node ID to remove                   */

GBOOL                              /*  TRUE if board is squelched          */
worNodeSquelched(                  /* Check if node is squelched           */
const CHAR *let);                  /*  letters of system to check          */

VOID
worNodeEraseALL(VOID);             /*  Removes all nodes from memory       */

UINT                               /*  Number of users matching criteria   */
worUserFindWorld(                  /* Find WorldLink Users matching stg    */
pWORUSER pwu,                      /*  Buffer to store 1 user              */
const CHAR *stg);                  /*  String to search for                */

UINT                               /*  Number of local users matching stg  */
worUserFindLocal(                  /* Find local users                     */
pWORUSER pwu,                      /*  Buffer to store 1 user              */
const CHAR *stg);                  /*  String to search for                */

UINT                               /*  Number of users found that match    */
worUserFind(                       /* Find users >= your criteria          */
pWORUSER pwu,                      /*  Buffer to store 1 found user or NULL*/
const CHAR *stg);                  /*  String to search for                */

UINT                               /*  Number of nodes matching criteria   */
worNodeFind(                       /* Find number of nodes w/ partial match*/
pWORNODE pwn,                      /*  Buffer to store 1 match             */
const CHAR *node);                 /*  Partial node to search for          */

#define worUserFirstMOD(x, y)      worUserFirst(x, y, ANYMAT, ANYMAT, ANYMAT)
#define worUserNextMOD(x)          worUserNext(x)
#define worUserFirstNUM(x, y, z)   worUserFirst(x, y, z, ANYMAT, ANYMAT)
#define worUserNextNUM(x)          worUserNext(x)

#define worUserCountMOD(x)         worUserCount(x, ANYMAT, ANYMAT, ANYMAT)
#define worUserCountNUM(x, y)      worUserCount(x, y, ANYMAT, ANYMAT)

#define worWorldUser(x)            samein(WUSEPSTG, x)
#define worLocalUser(x)            !samein(WUSEPSTG, x)

/***************************************************************************
* Function prototypes for file: WORCORE.C & SRVCORE.C                      *
****************************************************************************/
VOID
worInitialize(VOID);               /*  Main initialization routine         */

CHAR *                             /* Module description                   */
worModuleName(                     /*  Get module description given number */
UINT num);                         /*  Number of module for description    */

CHAR *                             /* Module appid                         */
worModuleWAPPID(                   /*  Given number return APPID           */
UINT num);                         /*  Number of modue 0 to worModules()-1 */

INT                                /* Module number or -1                  */
worModuleNum(                      /*  Get module number of appid          */
const CHAR *wappid);               /*  APPID of module to search for       */

UINT                               /* Number of modules currently loaded   */
worModules(VOID);                  /*  Gets number of modules on system    */

CHAR *                             /*  Pointer to domain name              */
worDomain(VOID);                   /*  WorldLink board domain name         */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             // __WORCOMN_H
