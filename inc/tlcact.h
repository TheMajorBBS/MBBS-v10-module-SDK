/***************************************************************************
 *                                                                         *
 *   TLCACT.H                                                              *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Entertainment Collection Teleconference action handling routines.     *
 *                                                                         *
 *                                           - M. Donnelly  11/3/93        *
 *   Modified for unified Tele               - P. Henning   8/12/97        *
 *                                                                         *
 ***************************************************************************/

#ifndef __TLCACT_H
#define __TLCACT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ACTSIZ is used both for the max name of an action AND an action list.   */

const INT ACTSIZ    =16;      /* Size of an action (list) name             */
const INT RESSIZ    =300;     /* Size of an action response                */
#define RESLIN (RESSIZ/4)     /* max length of action response line (+term)*/

//const INT NLISTS    =32;       /* How many action lists can exist at all    */
//#define NACTS      1024       /* Number of actions allowable in one list   */
#define LSTNAM  "!List"       /* Key indicating this action is list header */

#define ABFSIZ     outbsz     /* Buffer size for action word expansion     */

#define KILCOLR    "[0m"     /* ANSI kill current color command           */
#define UNKMAC     "(Unknown macro)"    /* Unknown macro expansion text    */

// DUCKULA - Temp removal (ACTSIZ, const int, is apparently not suitable for a preprocessor directive? Or perhaps it is defined, and the
//      const int above isn't used? (RS: #ifdef SUPPORTREMOVED) If needed, recomment this out
#if ACTSIZ != 16
#error ACTSIZ is no longer 16!  Update IDXACT macro to not left shift!
#endif

#define IDXACT(p,n)  (p+(n<<4))


typedef struct actlst {            /* action list record                   */
     CHAR list[ACTSIZ];            /*   name of this list (must be LSTNAM) */
     CHAR name[ACTSIZ];            /*   name of this action list           */
     CHAR seekey[KEYSIZ];          /*   key to see other users of list     */
     CHAR usekey[KEYSIZ];          /*   key to use this list               */
} ACTLST, *LPACTLST;

typedef struct action {            /* action record                        */
     CHAR list[ACTSIZ];            /*   action list (btv key)              */
     CHAR name[ACTSIZ];            /*   name of action word                */
     CHAR simple[RESSIZ];          /*   output for action w/no more input  */
     CHAR complx[RESSIZ];          /*   output for action w/extra input    */
     CHAR resp[RESSIZ];            /*   output to user doing action        */
     GBOOL isyell;                 /*   action expects text (else usrid)   */
     CHAR actkey[KEYSIZ];          /*   key required to use this action    */
} ACTION, *LPACTION;

#define ACTRECSIZ max(sizeof(ACTLST),sizeof(ACTION))

/* Do not use these buffers in external programs!  These buffers are used
   internally by the action routines when updating/adding/deleting stuff.
   Anything you put here will be destroyed, so don't do it.                */

extern LPACTION tmpact;
extern LPACTLST tmplst;
extern LPACTLST actlst;

/* An array of actctl's is allocated at startup.  The array corresponds
   with an array of actlst's that is allocated, also.

   The list pointer is a pointer to a sorted list of action names.  Each
   one is simply 16 characters and they're all stuck together.  When a
   new action is inserted, everything is shifted around to insert the new
   action in order.  The list is binary-searched when users enter input.   */

typedef CHAR KEYNAME[KEYSIZ];

typedef struct actctl {            /* in-memory action list control struct */
     INT count;                    /*   number of actions in this list     */
     GBOOL deltag;                 /*   tagged for deletion                */
     CHAR *list;                   /*   pointer to dynamic list            */
     INT numxky;                   /*   number of actions w/ xkey defined  */
     INT *xkylst;                  /*   ptr to list of xkey indexes        */
     KEYNAME *xkynam;              /*   ptr to list of xkeys               */
} ACTCTL, *LPACTCTL;

extern LPACTCTL actctl;
extern DFAFILE * TLCEXP dfaAct;

/* chklst will return 1 if it's a list that already exists, but it will
   return -1 if it's a list that exists and has been tagged for deletion.

   Note that both of the chkXXX functions will fill in the structure if the
   action/list in question is there.  When calling in, you only need to set
   the list/name fields (or name only in the case of chklst) and the functions
   will fill in the rest for you.  (chklst will fill in the list structure
   even if it has been tagged for deletion)                                */

VOID iniact(VOID);                      /* Initialize the action handler   */
VOID clsact(VOID);                      /* Shut down the action handler    */

INT addact(LPACTION newact);            /* Add a new action                */
INT delact(LPACTION oldact);            /* Delete an action                */
INT chgact(LPACTION newact);            /* Change an action                */

INT chglst(LPACTLST newlst);            /* Change an action list           */

VOID acthlp(VOID);
INT asimpl(VOID);
INT acomplx(VOID);
INT isempty(const CHAR* targ);

INT addlst(LPACTLST newlst);

extern VOID (*actionAddHook)(LPACTION);
extern VOID (*actionDeleteHook)(LPACTION);
extern VOID (*actionChangeHook)(LPACTION,LPACTION);
extern VOID (*listAddHook)(LPACTLST);
extern VOID (*listDeleteHook)(LPACTLST);
extern VOID (*listChangeHook)(LPACTLST,LPACTLST);


extern const CHAR* actTmpTo;
extern GBOOL actSecret;
extern GBOOL actHasFile;

GBOOL
actHasFromUser(                    /* does this action contain @FU macro?  */
const CHAR *fmt);                  /*   action format string               */

const CHAR *                       /*   returns pointer to internal buffer */
fmtsimpall(                        /* format a simple action               */
LPACTION pAct,                     /*   action specification               */
const CHAR* user);                 /*   sending user name                  */

const CHAR *                       /*   returns pointer to internal buffer */
fmtcomplxall(                      /* format a complex action to all       */
LPACTION pAct,                     /*   action specification               */
const CHAR* user,                  /*   sending user name                  */
const CHAR* userto,                /*   receiving user name (if any)       */
const CHAR* extra);                /*   input if yell                      */

const CHAR *                       /*   returns pointer to internal buffer */
fmtcomplxto(                       /* format a complex action to a user    */
LPACTION pAct,                     /*   action specification               */
const CHAR* user,                  /*   sending user name                  */
const CHAR* userto);               /*   receiving user name                */

VOID
actPrfFrame(                       /* frame an action in prfbuf            */
SHORT iMsgNum,                     /*   action type identifier             */
const CHAR* pMsg,                  /*   text associated with action        */
const CHAR* ptr1);                 /*   additional argument                */

CHAR*
FormatActionMsg(                   /* Sets the correct number of \1's      */
CHAR *aword,                       /*  Msg to be parsed of 1's and n's     */
GBOOL add1s);                      /*  add \1's                            */

CHAR*
UnFormatActionMsg(                 /* Removes all \1's and \n's            */
CHAR *aword);                      /*  Msg to be parsed                    */

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // __TLCACT_H
