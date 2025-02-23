/////////////////////////////////////////////////////////////////////////////
//
//   TLCAPI.H
//
//   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved
//
//   Teleconference API Declaration
//
//                                              - Phil Henning 5/14/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TLCAPI_H
#define __TLCAPI_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SYSUID      "^^^^"          // id FROM used for system messages.
                                    // internally.
const INT SYSUIDN = 0;

#if defined(GCWINNT)
#ifdef __BUILDTELE
#define TLCEXP __export
#else
#define TLCEXP __import
#endif // __BUILDTELE
#else
#define TLCEXP
#endif // GCWINNT

#ifndef __NOTLCMSG
#include "galtele.h"
#endif // _NOTLCMSG
#include "gme.h"
#include "fsdbbs.h"
#include "tlcfunc.h"
#include "tlctrans.h"
#include "tlcchan.h"
#include "tlcuser.h"
#include "tlccmd.h"
#include "tlc.h"
#include "tlcact.h"
#include "tlcpal.h"
#include "tlcapic.h"
#include "phasedbg.h"
#include "tlccmdm.h"

#define UNREF(X)  ((VOID)X)

const SHORT CHAN_PRIVATE_FOUND      =0;
const SHORT CHAN_PRIVATE_NOTFND     =1;
const SHORT CHAN_PRIVATE_AMBIG      =2;

const SHORT CHAN_SWITCH_USER_LOGOFF =1;
const SHORT CHAN_SWITCH_NODE_LOGOFF =2;
const SHORT CHAN_SWITCH_DELETED     =3;

extern VOID (* TLCEXP tlcenter)(const CHAR*);
extern VOID (* TLCEXP tlcexit)(const CHAR*);

typedef struct usrlist {
    CHAR userid[TLCUIDSIZ];
    CHAR channel[CHAN_MAX_SIZE];
} USRLIST, *LPUSRLIST;

typedef struct tlcnumxrf {
    ULONG number;
    CHAR userid[UIDSIZ];
} TLCNUMXRF, *LPTLCNUMXRF;
#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __TLCAPI_H

