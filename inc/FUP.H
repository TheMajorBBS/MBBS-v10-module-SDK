/***************************************************************************
 *                                                                         *
 *   FUP.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.      All Rights Reserved.   *
 *                                                                         *
 *   File Uploading, header for FILEXFER.C                                 *
 *   See the latest Developer's Guide for uploading instructions           *
 *                                                                         *
 *                                             - R. Stein  3/18/92         *
 *                                                                         *
 ***************************************************************************/

#ifndef __FUP_H
#define __FUP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

 /*--- Upload Handler Function Codes (exit points to app-specific code) ---*/

#define FUPPTH 2                   /* Where would we put this file?        */
#define FUPBEG 5                   /* Begin uploading this file            */
#define FUPREF 10                  /* Refer to file, don't upload it       */
#define FUPEND 6                   /* This file uploaded successfully      */
#define FUPSKP 7                   /* This file upload aborted             */
#define FUPFIN 8                   /* End of uploading session             */
#define FUPHUP 9                   /* Channel hanging up                   */

WGSEXP VOID
fileup(                            /* Begin file upload session            */
CHAR *fname,     /* proposed "visible" file name, or "" for multiple files */
CHAR *prot,    /* Protocol code, single-file: A 1 M C, multi-file: B G Z K */
INT (*fuphdl)(                     /* application's upload handler routine */
     INT fupcod));             /* upload handler function code (see above) */
      /* if single-file upload, put the file name (or "") in ftfscb->fname */


WGSEXP INT
valupc(                            /* Is this a valid upload protocol?     */
CHAR *prot);                       /* protocol code (may modify & restore) */
                                   /* returns 1=yes 0=no                   */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __FUP_H                              */

