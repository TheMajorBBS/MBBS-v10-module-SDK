/***************************************************************************
 *                                                                         *
 *   GCWINVER.H                                                            *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   These routines perform Windows version control on files.              *
 *                                                                         *
 *                                            - D. Pitchford 12/26/95      *
 *                                                                         *
 ***************************************************************************/

#ifndef __GCWINVER_H
#define __GCWINVER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SSFDIR "GALSSF"            /* shared support file directory        */

struct WGSEXP dpkwv {                     /* dynapak structure for Windows vers   */
     ULONG msl;                    /*   version number - major             */
     ULONG lsl;                    /*   version number - minor             */
     USHORT date;                  /*   date of file                       */
     USHORT time;                  /*   time of file                       */
     ULONG size;                   /*   size of file                       */
     CHAR filnam[GCMAXPTH];        /*   full path to file                  */
};

WGSEXPV(struct flddef) dpkwvFDA[];

WGSEXP INT                         /*   returns 0 if files are same version*/
winvertest(                        /* compare Windows versions of 2 files  */
CHAR *f1,                          /*   file 1 - returns -1 if newer       */
CHAR *f2);                         /*   file 2 - returns 1 if newer        */

WGSEXP INT                         /*   rtns -1, 0, 1 (newer, same, older) */
wvcompare(                         /* compare Windows file versions        */
struct dpkwv *v1,                  /*   info for file 1  (-1 if this newer)*/
struct dpkwv *v2);                 /*   info for file 2  (1 if this newer) */

WGSEXP GBOOL                       /*   returns FALSE if no file           */
getwinver(                         /* read Windows file version            */
struct dpkwv *info);               /*   version info (needs filnam)        */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __GCWINVER_H                         */
