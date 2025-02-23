/***************************************************************************
 *                                                                         *
 *   PROTSTUF.H                                                            *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Protected mode initialization and handling routines                   *
 *    (formerly PLSTUFF.C)                                                 *
 *                                                                         *
 *                                    - Robert A. Rose 02/18/92            *
 *                                    - Robert N. Stein 12/29/92           *
 *                                                                         *
 ***************************************************************************/

#ifndef __PROTSTUF_H
#define __PROTSTUF_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern GBOOL gphdlr;               /* FALSE=report&abort, else silent/cont */
extern GBOOL gpboot;               /* Cold Boot after GP?                  */
extern UINT gpcntr;                /* counter of GP's (reset if recovery)  */
extern UINT gpslmt;                /* how many times to continue thru GP   */

#ifdef GCDOSP

extern CHAR *dstname;              /* report file name (GP.OUT)            */
extern VOID *lastexcro;            /* address of last exception            */
extern GBOOL prtdnam;              /* ok to print DLL name on screen       */
extern VOID (*hdlgpr)(CHAR *);     /* app-specific GP report handler vector*/
extern VOID (*gpdblflt)(VOID);     /* GP double fault exit vector          */

VOID loaddll(CHAR *modnam);        /* load and link a DLL into memory      */
VOID initdlls(VOID);               /* initialize all DLLs just loaded      */
VOID setgphand(CHAR *title);       /* set the GP handler routine           */
VOID appgprept(VOID);              /* application-specific gp report       */
VOID appgprecd(VOID);              /* application-specific gp record       */

VOID plcatast(INT plerr,CHAR *msg);/* phar-lap catastro()                 */
VOID DosBlockIntr(VOID);           /* Block all interrupts at 8259         */
VOID DosUnblockIntr(VOID);         /* Unblock all interrupts at 8259       */

VOID
plstak(                            /* Phar Lap stack report                */
CHAR *filnam,                      /*   file name to append report to      */
VOID *sssp,                        /*   SS:SP where to start               */
USHORT bp);                        /*   initial BP in chain                */

#endif // GCDOSP

VOID protinit(                     /* initialize for protected mode        */
CHAR *pgmname);                    /*   prog name (end with a space) or "" */


#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __PROTSTUF_H
