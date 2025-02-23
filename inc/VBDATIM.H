/***************************************************************************
 *                                                                         *
 *   VBDATIM.H                                                             *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.      All rights reserved.   *
 *                                                                         *
 *   This is the global header file for VBDATIM.C utilities.               *
 *                                                                         *
 *                                               - Bill Hyatt 8/9/94       *
 *                                                                         *
 ***************************************************************************/

#ifndef __VBDATIM_H
#define __VBDATIM_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DOSBYR 1980                /* base year for DOS dates              */
#define DOSBVB (DOUBLE)29221.0     /* 1/1/1980 in VB format                */
#define DOSMVB (DOUBLE)75971.0     /* max DOS date (12/31/2107) in VB fmt  */
#define VBBYR  1800                /* base year for VB dates               */
#define VBBDAT (DOUBLE)(-36522.0)  /* 1/1/1800 in VB format                */
#define VBMYR  2200                /* max year for VB dates                */
#define VBMDAT (DOUBLE)109939.0    /* max date for VB format (12/31/2200)  */
#define THSCEN 1900                /* base year for this century           */

#define isleap(yr) isLeapYear(yr)  /* is this year a leap year?            */

WGSEXPV(INT) century;              /* 19-23 - ind's century for v2sdat()   */

                                   /* VBDATIM.C                            */

WGSEXP USHORT                                /*   returns DOS packed USHORT date  */
v2ddat(                            /* convert VB date to DOS packed int dat*/
DOUBLE vbdat);                     /*   VB DOUBLE precision date/time      */

WGSEXP USHORT                             /*   returns DOS packed USHORT time     */
v2dtim(                            /* convert VB time to DOS packed int tim*/
DOUBLE vbdat);                     /*   VB DOUBLE precision date/time      */

WGSEXP const CHAR *                       /*   returns ptr to MM/DD/YY            */
v2sdat(                            /* convert VB date to stg "MM/DD/YY"    */
DOUBLE vbdat);                     /*   VB DOUBLE precision date/time      */
                                   /*   implicit output: century           */

WGSEXP const CHAR *                       /*   returns ptr to MM/DD/YYYY          */
v2sdatl(                           /* convert VB date to stg "MM/DD/YYYY"  */
DOUBLE vbdat);                     /*   VB DOUBLE precision date/time      */

WGSEXP const CHAR *                       /*   returns ptr to HH:MM:SS            */
v2stim(                            /* convert VB time to stg "HH:MM:SS"    */
DOUBLE vbdat);                     /*   VB DOUBLE-precision date/time      */

WGSEXP DOUBLE                             /*   returns date/time in VB format     */
d2vdat(                            /* convert DOS date/time to VB format   */
USHORT dosdat,                     /*   DOS packed USHORT date             */
USHORT dostim);                    /*   DOS packed USHORT time             */

WGSEXP DOUBLE                             /*   returns date/time in VB format     */
s2vdat(                            /* convert string date/time to VB format*/
const CHAR *stgdat,                /*   date string in form "MM/DD/YY[YY]" */
const CHAR *stgtim);               /*   time string in form "HH:MM:SS"     */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __VBDATIM_H                          */
