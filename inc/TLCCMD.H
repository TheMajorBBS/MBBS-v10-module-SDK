/////////////////////////////////////////////////////////////////////////////
//
//   TLCCMD.H
//
//   Copyright (c) 1997 Galacticomm, Inc.         All Rights Reserved
//
//   Teleconference Command
//   Declaration
//                                               - Phil Henning 5/14/97
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TLCCMD_H
#define __TLCCMD_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

const SHORT SPACE_DELIM     =1;
const SHORT NO_DELIM        =0;

typedef struct CCommandParam {
    LPUSRSTRUCT m_pUser;
    CHAR* m_pszCmdParam;
} CMDPARAM, *LPCMDPARAM;

#ifdef __cplusplus
};
#endif // __cplusplus
#endif // __TLCCMD_H


