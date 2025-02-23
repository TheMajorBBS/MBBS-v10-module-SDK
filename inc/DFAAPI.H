/***************************************************************************
 *                                                                         *
 *   DFAAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header file for the library of routines for accessing     *
 *   data files with fixed or variable length records, compatible with     *
 *   DOS, WINDOWS NT, AND UNIX environments.                               *
 *                                                                         *
 *                                          - T. Stryker   6/24/86         *
 *                                          - R. Skurnick 12/28/95         *
 *   UNIX specifics                         - S. Thomas    1/10/95         *
 *                                                                         *
 ***************************************************************************/

#ifndef __DFAAPI_H
#define __DFAAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DFSTSZ  10                 /* dfaSetBlk()/dfaRstBlk()  stack size  */
#define SEGMAX  24                 /* maximum number of segments           */
#define MAXDFAP 56                 /* maximum length of data file path+file*/

                                   /* open modes passed to dfaMode()       */
#define PRIMBV  0                  /*   normal pre-image dfaMode()         */
#define ACCLBV -1                  /*   "accelerated" dfaMode()            */
#define RONLBV -2                  /*   read-only dfaMode()                */
#define VERFBV -3                  /*   vfy (read-after-write) dfaMode()   */
#define EXCLBV -4                  /*   "exclusive" dfaMode()              */

                                   /* file lock types for transactions     */
#define WAITBV   0                 /*   all ops within xaction should wait */
#define NOWTBV   200               /*    "   "     "     " should not wait */

                                   /* acquire/get/step operation lock types*/
#define SLWTBV 100                 /*   single record lock with wait       */
#define SLNWBV 200                 /*   single record lock with no wait    */
#define MLWTBV 300                 /*   multiple record lock with wait     */
#define MLNWBV 400                 /*   multiple record lock with no wait  */

#ifdef GCV2
#define GCVIRGIN ".\\"             /* default virgin data file directory   */
#else
#define GCVIRGIN "gcvirdat\\"      /* default virgin data file directory   */
#endif // GCV2

                                   /* file creation flags                  */
#define DFACF_VARIABLE   1         /*   variable-length records            */
#define DFACF_BLANKTRUNC 2         /*   blank truncation                   */
#define DFACF_COMPRESS   8         /*   compress data in records           */
#define DFACF_KEYONLY    16        /*   key-only file (no data)            */
#define DFACF_FREESPACE1 64        /*   10% free space                     */
#define DFACF_FREESPACE2 128       /*   20% free space                     */
#define DFACF_FREESPACE3 (64|128)  /*   30% free space                     */

struct dfaSegSpec {                /* DFA create key segment specification */
     size_t position;              /*   offset of segment in data buffer   */
     size_t length;                /*   length of segment                  */
     INT type;                     /*   key type code                      */
     INT flags;                    /*   Boolean options                    */
     CHAR nullChar;                /*   character for NULL key             */
};

                                   /* segment type flags                   */
#define DFAST_STRING     0         /*   non-terminated string              */
#define DFAST_INTEGER    1         /*   signed binary integer              */
#define DFAST_FLOAT      2         /*   IEEE floating point                */
#define DFAST_DATE       3         /*   Btrieve-style 4-byte binary date   */
#define DFAST_TIME       4         /*   Btrieve-style 4-byte binary time   */
#define DFAST_DECIMAL    5         /*   Binary Coded Decimal (BCD)         */
#define DFAST_MONEY      6         /*   Binary Coded Decimal (BCD)         */
#define DFAST_LOGICAL    7         /*   Boolean                            */
#define DFAST_NUMERIC    8         /*   signed integer stored as a string  */
#define DFAST_BFLOAT     9         /*   Btrieve-style floating point number*/
#define DFAST_LSTRING    10        /*   Pascal-style string                */
#define DFAST_ZSTRING    11        /*   zero-terminated string             */
#define DFAST_BINARY     14        /*   unsigned binary integer            */
#define DFAST_AUTOINC    15        /*   autoincrement                      */

                                   /* segment specification flags          */
#define DFASF_ALTCOLLATE 32        /*   use alternate collating sequence   */
#define DFASF_DESCENDING 64        /*   sort in descending order           */

struct dfaKeySpec {                /* DFA create key specification         */
     INT flags;                    /*   Boolean options                    */
     INT nSegments;                /*   number of segments in this key     */
     struct dfaSegSpec *segs;      /*   array of segment definitions       */
};

                                   /* key specification flags              */
#define DFAKF_DUPLICATE  1         /*   key allows duplicates              */
#define DFAKF_MODIFYABLE 2         /*   key is modifyable                  */
#define DFAKF_MANUAL     8         /*   manual key                         */
#define DFAKF_NULL       512       /*   NULL key                           */

#define CVTDFA CVTPACKED           /* cvtData*() format flag: native d-base*/

#ifdef UNIX
struct dfablk {                    /* data file block definition           */
     CHAR *filnam;                 /*   file name                          */
     INT reclen;                   /*   record length                      */
     CHAR *key;                    /*   current key                        */
     CHAR *data;                   /*   data buffer                        */
     INT lastkn;                   /*   key number of previous lookup      */
     INT keylns[SEGMAX];           /*   array of key/index lengths         */
     INT filno;                    /*   record file number                 */
     INT filmod;                   /*   file type (fixed/vlength)          */
     INT realreclen;               /*   record length of current record    */
     ULONG pos;                    /*   absolute record position           */
     INT nindex;                   /*   number of indices                  */
     struct index *indexlist;      /*   array of index information         */
     struct flddef *flddefList[SEGMAX]; /* array of flddefs for each key   */
     USHORT unpackKeySiz[SEGMAX];  /*   size of unpacked key              */
};
#elif defined(GCWINNT)
struct dfablk {                    /* btrieve file data block definition   */
     LONG posblk[128/4];           /*   position block                     */
     CHAR *filnam;                 /*   file name                          */
     USHORT reclen;                /*   maximum record length              */
     CHAR *key;                    /*   key for searching, etc.            */
     CHAR *data;                   /*   actual record contents             */
     SHORT lastkn;                 /*   last key number used               */
     USHORT keylns[SEGMAX];        /*   lengths of all possible keys       */
     struct flddef *flddefList[SEGMAX]; /* array of flddefs for each key   */
     USHORT unpackKeySiz[SEGMAX];  /*   size of unpacked key               */
};
#else
struct dfablk {                    /* btrieve file data block definition   */
     LONG posblk[128/4];           /*   position block                     */
     CHAR *filnam;                 /*   file name                          */
     USHORT reclen;                /*   maximum record length              */
     CHAR *key;                    /*   key for searching, etc.            */
     CHAR *data;                   /*   actual record contents             */
     SHORT lastkn;                 /*   last key number used               */
     USHORT keylns[SEGMAX];        /*   lengths of all possible keys       */
#ifdef GCDOSP
     USHORT realseg;               /*   real segment of this data block    */
     USHORT keyseg;                /*   real segment of the key area       */
#endif // GCDOSP
};
#endif // UNIX

struct dfaStatFileSpec {           /* create internal file specification   */
     USHORT recordLength;          /*   record length                      */
     USHORT pageSize;              /*   page size                          */
     USHORT nKeys;                 /*   number of keys                     */
     CHAR notUsed[4];              /*   unused                             */
     USHORT flags;                 /*   Boolean options                    */
     CHAR reserved[2];             /*   reserved                           */
     USHORT nPreAllocate;          /*   number of pages to pre-allocate    */
};

struct dfaStatKeySpec {            /* create internal key specification    */
     USHORT position;              /*   offset of key in data buffer       */
     USHORT length;                /*   length of key                      */
     USHORT flags;                 /*   Boolean options                    */
     CHAR notUsed[4];              /*   unused                             */
     UCHAR extendedType;           /*   extended type code                 */
     CHAR nullChar;                /*   character to use for NULL keys     */
     CHAR reserved[4];             /*   reserved                           */
};

#define DFAFILE struct dfablk

#define dfaGetAbs(r,p,k)           dfaGetAbsLock(r,p,k,0)
#define dfaAcqAbs(r,p,k)           dfaAcqAbsLock(r,p,k,0)
#define dfaAbsRec(r,k)             dfaGetAbsLock(r,dfaAbs(),k,0)

#define dfaQueryNX()               dfaQueryNP(56)
#define dfaQueryPR()               dfaQueryNP(57)
#define dfaQueryEQ(k,n)            dfaQuery(k,n,55)
#define dfaQueryGT(k,n)            dfaQuery(k,n,58)
#define dfaQueryGE(k,n)            dfaQuery(k,n,59)
#define dfaQueryLT(k,n)            dfaQuery(k,n,60)
#define dfaQueryLE(k,n)            dfaQuery(k,n,61)
#define dfaQueryLO(k)              dfaQuery(NULL,k,62)
#define dfaQueryHI(k)              dfaQuery(NULL,k,63)

#define dfaGetEQ(r,k,n)            dfaGetLock(r,k,n,5,0)
#define dfaGetNX(r)                dfaGetLock(r,NULL,-1,6,0)
#define dfaGetPR(r)                dfaGetLock(r,NULL,-1,7,0)
#define dfaGetGT(r,k,n)            dfaGetLock(r,k,n,8,0)
#define dfaGetGE(r,k,n)            dfaGetLock(r,k,n,9,0)
#define dfaGetLT(r,k,n)            dfaGetLock(r,k,n,10,0)
#define dfaGetLE(r,k,n)            dfaGetLock(r,k,n,11,0)
#define dfaGetLO(r,n)              dfaGetLock(r,NULL,n,12,0)
#define dfaGetHI(r,n)              dfaGetLock(r,NULL,n,13,0)

#define dfaAcqNX(r)                dfaAcqNPLock(r,1,6,0)
#define dfaAcqPR(r)                dfaAcqNPLock(r,1,7,0)
#define dfaAcqNXi(r)               dfaAcqNPLock(r,0,6,0)
#define dfaAcqPRi(r)               dfaAcqNPLock(r,0,7,0)

#define dfaAcqEQ(r,k,n)            dfaAcqLock(r,k,n,5,0)
#define dfaAcqGT(r,k,n)            dfaAcqLock(r,k,n,8,0)
#define dfaAcqGE(r,k,n)            dfaAcqLock(r,k,n,9,0)
#define dfaAcqLT(r,k,n)            dfaAcqLock(r,k,n,10,0)
#define dfaAcqLE(r,k,n)            dfaAcqLock(r,k,n,11,0)
#define dfaAcqLO(r,n)              dfaAcqLock(r,NULL,n,12,0)
#define dfaAcqHI(r,n)              dfaAcqLock(r,NULL,n,13,0)

#define dfaStepLO(recp)            dfaStepLock(recp,33,0)
#define dfaStepNX(recp)            dfaStepLock(recp,24,0)
#define dfaStepPR(recp)            dfaStepLock(recp,35,0)
#define dfaStepHI(recp)            dfaStepLock(recp,34,0)

#define dfaUnlockOne()             dfaUnlock(NULL,0)
#define dfaUnlockCur()             dfaUnlock(dfaAbs(),-1)
#define dfaUnlockSel(f)            dfaUnlock((f),-1)
#define dfaUnlockAll()             dfaUnlock(NULL,-2)

WGSEXP DFAFILE *                   /*   pointer to a dfa file structure    */
dfaOpen(                           /* open data file                       */
const CHAR *filnam,                /*   filename                           */
USHORT maxlen,                     /*   maximum record length              */
const CHAR *owner);                /*   owner of file (NULL if none)       */

WGSEXP VOID                        /*   Btrieve-specific function          */
dfaMode(                           /* set data file mode                   */
SHORT mode);                       /*   access mode                        */

WGSEXP VOID
dfaSetBlk(                         /* set current dfablk to bbptr          */
struct dfablk *bbptr);             /*   datafile block pointer             */

WGSEXP VOID
dfaRstBlk(VOID);                   /* restore last dfablk pointer          */

WGSEXP VOID
dfaBegTrans(                       /* begin datafile transaction           */
USHORT loktyp);                    /*   type of record locking (Btrieve)   */

WGSEXP VOID
dfaAbtTrans(VOID);                 /* abort current datafile transaction   */

WGSEXP VOID
dfaEndTrans(VOID);                 /* end datafile transaction             */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaQuery(                          /* datafile query operation             */
const VOID *key,                   /*   key to lookup                      */
SHORT keynum,                      /*   key number or -1                   */
USHORT qryopt);                    /*   query operation to perform         */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaQueryNP(                        /* datafile query next/previous         */
USHORT qryopt);                    /*   operation to perform               */

WGSEXP VOID
dfaGetLock(                        /* datafile get operation               */
VOID *recptr,                      /*   pointer for data record            */
const VOID *key,                   /*   key to lookup                      */
SHORT keynum,                      /*   key number or -1                   */
USHORT getopt,                     /*   operation to perform               */
USHORT loktyp);                    /*   lock bias (Btrieve)                */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaAcqLock(                        /* datafile acquire operation           */
VOID *recptr,                      /*   pointer for data record            */
const VOID *key,                   /*   key to lookup                      */
SHORT keynum,                      /*   key number or -1                   */
USHORT obtopt,                     /*   operation to perform               */
USHORT loktyp);                    /*   lock bias (Btrieve)                */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaAcqNPLock(                      /* datafile acquire nxt/prv op          */
VOID *recptr,                      /*   pointer for data record            */
GBOOL chkcas,                      /*   case sensitive?                    */
USHORT anpopt,                     /*   operation to perform               */
USHORT loktyp);                    /*   lock bias (Btrieve)                */

WGSEXP USHORT                      /*   returns length of last record      */
dfaLastLen(VOID);                  /* get length of last record            */

WGSEXP LONG                        /*   returns absolute position          */
dfaAbs(VOID);                      /* get absolute position of current rec */

WGSEXP VOID
dfaGetAbsLock(                     /* datafile get absolute operation      */
VOID *recptr,                      /*   pointer for data record            */
LONG abspos,                       /*   absolute datafile position         */
SHORT keynum,                      /*   key number (>=0 only)              */
USHORT loktyp);                    /*   lock bias (Btrieve)                */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaAcqAbsLock(                     /* datafile acquire absolute operation  */
VOID *recptr,                      /*   pointer for data record            */
LONG abspos,                       /*   absolute datafile position         */
SHORT keynum,                      /*   key number (>=0 only)              */
USHORT loktyp);                    /*   lock bias (Btrieve)                */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaStepLock(                       /* datafile step operation              */
VOID *recptr,                      /*   pointer for data record            */
USHORT stpopt,                     /*   operation to perform               */
USHORT loktyp);                    /*   lock bias (Btrieve)                */

WGSEXP VOID
dfaUpdate(                         /* datafile update record               */
VOID *recptr);                     /*   pointer to record to update        */

WGSEXP VOID
dfaUpdateV(                        /* datafile update var len record       */
VOID *recptr,                      /*   pointer to record to update        */
USHORT length);                    /*   length of record                   */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaUpdateDup(                      /* datafile update record (w/o catastro)*/
VOID *recptr);                     /*   pointer to record to update        */

WGSEXP VOID
dfaInsert(                         /* datafile insert record               */
VOID *recptr);                     /*   pointer to record to insert        */

WGSEXP VOID
dfaInsertV(                        /* datafile insert variable length rec. */
VOID *recptr,                      /*   pointer to record to insert        */
USHORT length);                    /*   length of record                   */

WGSEXP GBOOL                       /*   return TRUE=success                */
dfaInsertDup(                      /* datafile insert record (w/o catastro)*/
VOID *recptr);                     /*   pointer to record to insert        */

WGSEXP VOID
dfaDelete(VOID);                   /* datafile delete record               */

WGSEXP VOID
dfaClose(                          /* close datafile                       */
struct dfablk *dfap);              /*   pointer to dfafile to close        */

WGSEXP VOID
dfaCreateSpec(                     /* create file from specification       */
const CHAR *fileName,              /*   path and name of file to create    */
GBOOL overwrite,                   /*   overwrite existing file?           */
size_t recordLength,               /*   fixed-size record length           */
size_t pageSize,                   /*   page size (must be multiple of 512)*/
INT flags,                         /*   file creation flags                */
INT nPreAllocate,                  /*   number of pages to pre-allocate    */
INT nKeys,                         /*   number of keys (not segments)      */
struct dfaKeySpec *keys,           /*   array of key info                  */
const CHAR *altFile);              /*   alternating colating sequence file */

WGSEXP VOID
dfaCreate(                         /* create datafile                      */
const VOID *filnam,                /*   filename to create                 */
VOID *databuf,                     /*   pointer to databuffer              */
SHORT keyno,                       /*   number of keys                     */
USHORT lendbuf);                   /*   length of data buffer              */

WGSEXP ULONG                       /*    returns number of records         */
dfaCountRec(VOID);                 /* count records in datafile            */

WGSEXP USHORT                      /*   returns record length              */
dfaRecLen(VOID);                   /* get record length of current record  */

WGSEXP VOID
dfaUnlock(                         /* unlock record                        */
LONG abspos,                       /*   position to unlock                 */
SHORT keynum);                     /*   key number or -1                   */

WGSEXP GBOOL                       /*   return TRUE=record was locked      */
dfaWasLocked(VOID);                /* check record lock status             */

#ifdef UNIX
VOID
dfaPerfMon(                        /* get statistics on c-tree dfa access  */
ULONG *bufptr);                    /*   pointer to result buffer (8 longs) */
#endif // UNIX

WGSEXP GBOOL
dfaAcquireAbs(                     /* "acquire" a record from a file pos   */
VOID *recptr,                      /*   ptr to area to retrieve record into*/
LONG abspos,                       /*   abspos to used for acq-absolute    */
INT keynum,                        /*   key number to use for acq-absolute */
INT loktyp);                       /*   lock bias (Btrieve)                */

WGSEXP VOID
dfaStop(VOID);                     /* stop btrieve operation               */

#ifndef GCDOSP

WGSEXP VOID
dfaStat(                           /* return stats on current datafile     */
USHORT len);                       /*   length of buffer                   */

WGSEXP VOID
dfaStatus(                         /* Low level status routine             */
VOID *Buffer,                      /*  Buffer to store status in           */
USHORT BufferLength,               /*  Length of the buffer                */
INT Key);                          /*  Key number to call by               */

#endif // GCDOSP

WGSEXP GBOOL                       /*   returns TRUE=success               */
dfaVirgin(                         /* copy virgin file into database file  */
const CHAR *src,                   /*   virgin database file name w/o ext  */
const CHAR *dst);                  /*   destination file name or NULL      */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __DFAAPI_H
 