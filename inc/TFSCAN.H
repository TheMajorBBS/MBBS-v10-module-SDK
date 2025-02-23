/***************************************************************************
 *                                                                         *
 *   TFSCAN.H                                                              *
 *                                                                         *
 *   Copyright (c) 1993-1997 Galacticomm, Inc.   All Rights Reserved.      *
 *                                                                         *
 *   Text file scanning routines.  May use wildcards, but you must stay    *
 *   in the current directory (no path prefixes)                           *
 *                                                                         *
 *                                    - Robert N. Stein 1/8/93             *
 *                                                                         *
 ***************************************************************************/

#ifndef __TFSCAN_H
#define __TFSCAN_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MAXTFS 129              /* max number of characters per line + NUL */

WGSEXPV(INT) tfstate;              /* tfsrdl() state code and return value */
WGSEXPV(CHAR) tfsbuf[MAXTFS];      /* line when tfsrdl() returns TFSLIN    */
WGSEXPV(CHAR*) tfspst;             /* buf after skpwht when tfspfx() rets 1*/
WGSEXPV(struct ffblk) tfsfb;       /* ffblk structure from current file   */
WGSEXPV(FILE*) tfsfp;              /* file ptr while tfsrdl() rets TFSLIN  */

WGSEXP INT                                /*   returns number of files            */
tfsopn(                            /* prep to scan text file(s)            */
const CHAR *fname);                /* may use wildcards, may use pth prefix*/

WGSEXP INT                                /*   rets 0=done non-0=still scanning   */
tfsrdl(VOID);                      /* read a line from the file(s)         */

WGSEXP GBOOL                              /*   returns TRUE=prefix'd              */
tfspfx(                            /* is current line pfx'd with prefix stg*/
const CHAR *prefix);               /*   prefix to check for                */

WGSEXP VOID
tfsdpr(VOID);                      /* after tfspfx() == 1,use "deeper" pfx */

WGSEXP VOID
tfsabt(VOID);                      /* abort file scanning                  */

/*--- tfsrdl() return values and tfstate codes ---*/
#define TFSDUN 0                         /* tfsrdl() done scanning file(s) */
#define TFSBGN 1    /* tfsopn() has been called, tfsrdl() calls will begin */
#define TFSBOF 2                  /* tfsrdl() is about to start a new file */
#define TFSLIN 3                            /* tfsrdl() has a line for you */
#define TFSEOF 4                           /* tfsrdl() is done with a file */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __TFSCAN_H                           */
