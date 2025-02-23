/***************************************************************************
 *                                                                         *
 *   AUDAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Utilities for managing Galacticomm-style audit trail files.           *
 *                                                                         *
 *                                           - J. Alvrus    10/01/1997     *
 *                                                                         *
 ***************************************************************************/

#ifndef __AUDAPI_H
#define __AUDAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

                                   /* audit trail operation result codes   */
#define AUDERR_OK        0         /*   operation successful               */
#define AUDERR_NEW       1         /*   file not found, new file created   */
#define AUDERR_DAMAGED   2         /*   file damaged, recovery required    */
#define AUDERR_FIO       -1        /*   file I/O error                     */
#define AUDERR_MEMORY    -2        /*   insufficient memory for operation  */
#define AUDERR_NOTOPEN   -3        /*   file not open, close and reopen    */
#define AUDERR_MODE      -4        /*   operation not valid for open mode  */
#define AUDERR_NOTFOUND  -5        /*   entry not found (rec# out of range)*/

                                   /* special channel identifiers          */
#define AUDCHAN_CONSOLE  -1        /*   console                            */
#define AUDCHAN_CLEANUP  -2        /*   cleanup                            */
#define AUDCHAN_EVENT    -3        /*   timed event (global errcod used)   */

typedef enum {                     /* audit trail file open modes          */
     AUDMODE_READONLY,             /*   read only                          */
     AUDMODE_READWRITE             /*   read and write                     */
} AUDMODE;                         /* mode typedef                         */

typedef struct tagAUDFILE {        /* audit trail file tracking structure  */
     FILE *fp;                     /*   file stream                        */
     AUDMODE mode;                 /*   file open mode                     */
     CHAR name[GCMAXPTH];          /*   name of audit trail file           */
} *HAUDFILE;                       /* audit trail file handle type         */

#define AUDSTAMPSIZ sizeof("YYYYMMDD HHMMSS")
#define AUDBRIEFSIZ (32+1)
#define AUDCHANSIZ  (16+1)
#define AUDDETSIZ   128

struct audEntry {                  /* audit trail record format            */
     CHAR stamp[AUDSTAMPSIZ];      /*   time stamp ("YYYYMMDD HHMMSS ")    */
     CHAR brief[AUDBRIEFSIZ];      /*   brief description                  */
     CHAR channel[AUDCHANSIZ];     /*   channel/console/event/cleanup      */
     CHAR detail[AUDDETSIZ];       /*   detailed description               */
};

#define AUDRECLEN (sizeof(struct audEntry)+CSTRLEN("\r\n"))

#define AUDOLDSTAMPSIZ   14
#define AUDOLDBRIEFSIZ   33
#define AUDOLDCHANSIZ    8
#define AUDOLDDETSIZ     65

struct audOldStyle {               /* old-style audit trail record format  */
     CHAR stamp[AUDOLDSTAMPSIZ];   /*   time stamp (not nul-terminated)    */
     CHAR brief[AUDOLDBRIEFSIZ];   /*   brief description (32 chars + sp)  */
     CHAR channel[AUDOLDCHANSIZ];  /*   chan/console/event (nul-terminated)*/
     CHAR unused[12];              /*   unused space (filled with nuls)    */
     CHAR detail[AUDOLDDETSIZ];    /*   long desc (63 chars + 2 nuls)      */
};

WGSEXP INT                                /*   returns result code                */
audfOpen(                          /* open an audit trail file             */
HAUDFILE *phaud,                   /*   buffer to receive opened handle    */
const CHAR *fileName,              /*   name of file to open               */
AUDMODE mode);                     /*   mode in which to open              */

WGSEXP VOID
audfClose(                         /* close an audit trail file            */
HAUDFILE haud);                    /*   handle to close                    */

WGSEXP INT                                /*   returns result code                */
audfRecover(                       /* recover a damaged audit trail file   */
HAUDFILE haud);                    /*   handle to file to recover          */

WGSEXP ULONG
audfNumRecs(                       /* get number of records in file        */
HAUDFILE haud);                    /*   audit trail file to use            */

WGSEXP INT                                /*   returns result code                */
audfAddEntry(                      /* add an entry to audit trail file     */
HAUDFILE haud,                     /*   audit trail file to use            */
const CHAR *brief,                 /*   brief description                  */
const CHAR *detail,                /*   detailed description/format string */
...);                              /*   arguments to be formatted          */

WGSEXP INT                                /*   returns result code                */
audfVAddEntry(                     /* add entry with variable argument list*/
HAUDFILE haud,                     /*   audit trail file to use            */
const CHAR *brief,                 /*   brief description                  */
const CHAR *detail,                /*   detailed description/format string */
va_list argList);                  /*   argument list                      */

WGSEXP INT                                /*   returns result code                */
audfReadEntry(                     /* read an entry by record number       */
HAUDFILE haud,                     /*   audit trail file to use            */
ULONG recNum,                      /*   record number to read              */
struct audEntry *buf,              /*   buffer to receive data             */
size_t bufSiz);                    /*   size of destination buffer         */

WGSEXP INT                                /*   returns result code                */
audfFindEntryDOS(                  /* find an entry by DOS date and time   */
HAUDFILE haud,                     /*   audit trail file to use            */
USHORT dosDate,                    /*   DOS-style date to search for       */
USHORT dosTime,                    /*   DOS-style time to search for       */
ULONG *pRecNum,                    /*   buf for rec # (NULL if don't want) */
struct audEntry *buf,              /*   buf for entry (NULL if don't want) */
size_t bufSiz);                    /*   size of destination buffer         */

WGSEXP INT                                /*   returns result code                */
audfFindEntryStr(                  /* find an entry by string date & time  */
HAUDFILE haud,                     /*   audit trail file to use            */
const CHAR *strDate,               /*   YYYYMMDD date to search for        */
const CHAR *strTime,               /*   HHMMSS time to search for          */
ULONG *pRecNum,                    /*   buf for rec # (NULL if don't want) */
struct audEntry *buf,              /*   buf for entry (NULL if don't want) */
size_t bufSiz);                    /*   size of destination buffer         */

WGSEXP INT                                /*   returns result code                */
audfReadOldStyle(                  /* read an old-style entry              */
HAUDFILE haud,                     /*   audit trail file to use            */
ULONG recNum,                      /*   record number to read              */
struct audOldStyle *buf,           /*   buffer to receive data             */
size_t bufSiz);                    /*   size of destination buffer         */

/* miscellaneous utility functions */

WGSEXP CHAR *                             /*   returns pointer to buffer          */
audfChannelStr(                    /* generate channel description string  */
CHAR *buf,                         /*   buffer (must be AUDCHANSIZ long)   */
size_t bufSiz);                    /*   size of buffer                     */
                                   /*   (implicit inputs: usrnum, nterms,  */
                                   /*    channel[], errcod)                */

WGSEXP struct audEntry *                  /*   returns pointer to destination     */
audfFormatEntry(                   /* create properly-formatted entry      */
struct audEntry *buf,              /*   buffer to receive entry            */
size_t bufSiz,                     /*   size of destination buffer         */
const CHAR *brief,                 /*   brief description                  */
const CHAR *chanStr,               /*   channel description string         */
const CHAR *detail,                /*   detailed description/format string */
va_list argList);                  /*   argument list                      */

WGSEXP struct audEntry *                  /*   returns pointer to buffer          */
audfCvtRawToEntry(                 /* convert raw file data to entry       */
const CHAR *src,                   /*   raw file data                      */
struct audEntry *buf,              /*   buffer to receive converted entry  */
size_t bufSiz);                    /*   size of destination buffer         */

WGSEXP struct audOldStyle *               /*   returns pointer to buffer          */
audfCvtEntryToOld(                 /* convert an entry to old-style        */
const struct audEntry *src,        /*   new-style audit trail entry        */
struct audOldStyle *buf,           /*   buffer to receive converted entry  */
size_t bufSiz);                    /*   size of destination buffer         */

/* low-level functions */

WGSEXP INT                                /*   returns result code                */
audfOpenLowLevel(                  /* low-level open file                  */
HAUDFILE haud);                    /*   audit trail file to use            */

WGSEXP INT                                /*   returns result code                */
audfAddLowLevel(                   /* low-level add entry                  */
HAUDFILE haud,                     /*   audit trail file to use            */
struct audEntry *src,              /*   formatted record to add            */
size_t srcSiz);                    /*   size of source buffer              */

WGSEXP INT                                /*   returns result code                */
audfReadLowLevel(                  /* low-level read an entry utility      */
HAUDFILE haud,                     /*   audit trail file to use            */
ULONG recNum,                      /*   record number to read              */
CHAR *buf,                         /*   buffer (must be AUDRECLEN+1 long)  */
size_t bufSiz);                    /*   size of buffer                     */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __AUDAPI_H
