/***************************************************************************
 *                                                                         *
 *   WELOG.H                                                               *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Event logging for Worldgroup server (NT/Win95 only)                   *
 *                                                                         *
 *                                        - I. Minkin 9/09/96              *
 *                                                                         *
 ***************************************************************************/

#ifndef __WELOG_H
#define __WELOG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT

VOID WINAPI
welogAdd(                          // adds new entry to WG event log
const CHAR *data);                 //   data to add

typedef VOID (WINAPI * WELOGADD)(const CHAR *); // prt to welogAdd()

#endif // GCWINNT

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __WELOG_H
