/***************************************************************************
 *                                                                         *
 *   GALFXC.H                                                              *
 *                                                                         *
 *   Copyright (c) 1994-1996 Galacticomm, Inc.    All rights reserved.     *
 *                                                                         *
 *   These are common declarations for GALFAP.C and CSFAX.C.               *
 *                                                                         *
 *                                                - J. Delekto 10/31/95    *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALFXC_H
#define __GALFXC_H

#if defined (GCWINNT)
#ifdef __BUILDFAP
#define FAPEXP __export
#else
#define FAPEXP __import
#endif // __BUILDFAP
#else
#define FAPEXP
#endif // GCWINNT

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define   FTPLEN    51             /* maximum fax topic length             */
#define   DESLEN    51             /* maximum description length           */
#define   DOCLEN    9              /* maximum document name length         */

struct faplst {                    /* fax application data base structure  */
     CHAR docnam[DOCLEN];          /*   short name of fax document         */
     CHAR filnam[GCSTRPTH];        /*   fax document's actual filename     */
     SHORT numpps;                 /*   number of pages in fax file        */
     CHAR lock[KEYSIZ];            /*   visibility lock for fax file       */
     CHAR docdes[DESLEN];          /*   description of fax file            */
};

extern DFAFILE * FAPEXP fapbb;     /* btrieve file for fax queue           */
extern HMCVFILE FAPEXP fapmb;      /* galfax app message file pointer      */
extern GBOOL FAPEXP realcr;               /* charge 'real' credits for fax        */
extern LONG FAPEXP chgpp;                 /* viewing charge per page              */
extern CHAR * FAPEXP faxsky;               /* has fax 'sysop' key                  */
extern CHAR * FAPEXP faxaky;               /* has C/S key to use agent             */

VOID
inicsfax(VOID);                    /* initialize the fax/online agent      */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GALFXC_H
