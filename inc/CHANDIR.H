/***************************************************************************
 *                                                                         *
 *   CHANDIR.H                                                             *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Channel-specific directories, named CHANXX, where XX is the hex       *
 *   channel number, 00 to FF.                                             *
 *                                                                         *
 *                                              - R. Stein  7/20/94        *
 *                                                                         *
 ***************************************************************************/

#ifndef __CHANDIR_H
#define __CHANDIR_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#	ifdef __BUILDGALCHDIR
#       define CHDIREXP         EXPORT
#		define CHDIREXPV(x) 	EXPORT_VARIABLE(x)
#		define CHDIREXPF(x, y)	EXPORT_FUNCTION(x, y)
#	else
#       define CHDIREXP         IMPORT
#		define CHDIREXPV(x)		IMPORT_VARIABLE(x)
#		define CHDIREXPF(x, y)	IMPORT_FUNCTION(x, y)
#	endif
#else
#   define CHDIREXP
#	define CHDIREXPV(x)         extern x
#	define CHDIREXPF(x,y)       extern x (* y)
#endif                            /* GCWINNT                              */

CHDIREXPV(CHAR*) chdpfx;      /* channel directory prefix             */
CHDIREXPV(LONG) chdsiz;       /* max bytes users allowed to store here*/

CHDIREXP VOID
chdmak(VOID);                      /* make a channel directory             */

CHDIREXP INT
chdrem(VOID);                      /* remove a channel directory           */
                                   /* returns 0=ok, else=error             */

CHDIREXP CHAR *
chdpath(                           /* path of file in current channel dir  */
CHAR *filespec);                   /* file name, wildcard, or NULL=dir name*/

CHDIREXP CHAR *
uchdpath(                          /* path of file in a channel directory  */
INT unum,                          /* user number, 0 to nterms-1           */
CHAR *filespec);                   /* file name, wildcard, or NULL=dir name*/

CHDIREXP LONG
chdroom(VOID);                     /* find room in current channel dir     */
                                   /* also sets numfils, numbyts, numbytp  */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __CHANDIR_H                          */
