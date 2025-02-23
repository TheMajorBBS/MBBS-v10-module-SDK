////////////////////////////////////////////////////////////////////////////
//
//   TLCFUNC.H
//
//   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved
//
//   Misc. Teleconference Functions
//   Declaration
//                                               - Phil Henning 7/20/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TLCFUNC_H
#define __TLCFUNC_H
                                   // tele profanity level codes
#define PFN_NONE    0              //   no profanity in input
#define PFN_WARNED  1              //   user warned about profanity
#define PFN_HANGUP  2              //   too much profanity, hang up on user
#define HANGUP 2

#ifdef __cplusplus
extern "C" {
#endif

VOID
chgnot(
const CHAR* userid,
const CHAR* type);

VOID
logcrd(
const CHAR* user,
LONG credits);

VOID
RemoveInviteNUM(
ULONG user,
USHORT board);

VOID
RemoveForgetNUM(
ULONG user,
USHORT board);

bool
chkalph(
const CHAR* stg);

VOID
ExitChat(
GBOOL hangup,
const CHAR* userid,
GBOOL didleave);

SHORT                              //   returns value
chk4pfn(VOID);                     // check input for profanity

VOID
tlcusrson(VOID);

#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __TLCFUNC_H















