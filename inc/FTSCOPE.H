/***************************************************************************
 *                                                                         *
 *   FTSCOPE.H                                                             *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header for using FT datascope routines for monitoring     *
 *   file transfer and other things.                                       *
 *                                                                         *
 *                                                 - Bob Stein, 6/8/94     *
 *                                                                         *
 ***************************************************************************/

#ifndef __FTSCOPE_H
#define __FTSCOPE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

WGSEXPV(INT) whomon;     /* channel being monitored by GALFTSC.C (-1=none) */
WGSEXPF(VOID,ftscope)(INT,...);    /* GALFTSC.C entry point, if any        */
                                    /* (see FILEXFER.C for these variables) */

#define FTSSRT 0  /* File xfer starting:           (*ftscope)(0)            */
#define FTSINS 1  /* File xfer inputing a string:  (*ftscope)(1,stg,nbytes) */
#define FTSOUS 2  /* File xfer outputing a string: (*ftscope)(2,stg,nbytes) */
#define FTSEND 3  /* File xfer ending:             (*ftscope)(3)            */
#define FTSHUP 4  /* File xfer user hanging up     (*ftscope)(4)            */
#define FTSCMT 5  /* File xfer diagnostic comment  (*ftscope)(5,comment)    */
#define FTSLON 6  /* File xfer user logging on     (*ftscope)(6)            */

VOID
prtchs(                                     /* print transferred characters */
CHAR *string,
INT nbytes);

VOID
ftstrm(VOID);                  /* terminate current line of xfer characters */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                            /* __FTSCOPE_H                          */
