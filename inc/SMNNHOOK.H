/***************************************************************************
 *                                                                         *
 *   SMNNHOOK.H                                                            *
 *                                                                         *
 *   Copyright (c) 1999 Galacticomm, Inc.         All Rights Reserved.     *
 *                                                                         *
 *   Declarations for function hook management routines shared by SMTP     *
 *   and NNTP.                                                             *
 *                                                                         *
 *                                            - J. Alvrus   06/29/1999     *
 *                                                                         *
 ***************************************************************************/

#ifndef __SMNNHOOK_H
#define __SMNNHOOK_H

#include "gcomm.h"
#include "gme.h"

struct HookItem {                  /* hook array type                      */
    voidfunc hookfunc;            /*   hook handling function             */
    USHORT hooktype;              /*   type of hook                       */
    SHORT hookpri;                /*   hook priority (32767 to -32768)    */
};

extern struct HookItem* HookArr;  /* array of function hooks              */
extern INT nHooks;                 /* number of function hooks             */

GBOOL                              /*   returns TRUE if hook set           */
HookAdd(                           /* add a function hook                  */
    USHORT hooktype,                   /*   type of hook to set                */
    voidfunc hookfunc,                 /*   hook function pointer              */
    SHORT priority);                   /*   priority                           */

INT                                /*   returns index or NOIDX if not found*/
HookNext(                          /* find next hook function              */
    USHORT hooktype,                   /*   of a given type                    */
    INT curidx);                       /*   after this index (NOIDX == first)  */

#endif // __SMNNHOOK_H
