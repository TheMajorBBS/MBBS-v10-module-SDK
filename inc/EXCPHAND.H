/***************************************************************************
 *                                                                         *
 *   EXCPHAND.H                                                            *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Exception handler & exception report for NT version.                  *
 *                                                                         *
 *                                      - Ilya Minkin 01/30/96             *
 *                                                                         *
 ***************************************************************************/

#ifndef __EXCPHAND_H
#define __EXCPHAND_H

#if defined(GCWINNT)
#include <windows.h>
#endif // GCWINNT

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(GCWINNT)

typedef VOID (*POSTEXCPPROC)(VOID);

VOID
setPostExcpProc(                   // set function to execute after excp handler
POSTEXCPPROC pProc);               //   function pointer

LONG                               //   exit/continue/serch next handler
excpFilter(                        // handle exception and print report
EXCEPTION_POINTERS *excpPtrs);     //   ptr to exception info

#ifdef __cplusplus
#define TRY try {
#else // __cplusplus
#define TRY __try {
#endif // __cplusplus

#define EXCEPT } __except (excpFilter(GetExceptionInformation())) {}

#else

#define TRY
#define EXCEPT

#endif // GCWINNT

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __EXCPHAND_H
