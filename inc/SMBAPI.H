/***************************************************************************
 *                                                                         *
 *   SMBAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1987-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header file for the library of routines for accessing     *
 *   memroy data files with fixed length records.                          *
 *                                                                         *
 *                                          - W. Muharsky  5/19/97         *
 *                                                                         *
 ***************************************************************************/
#ifndef __SMBAPI_H
#define __SMBAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef GCWINNT
#   ifdef __BUILDGALSMB
#       define SMBEXP          EXPORT
#       define SMBEXPV(x)      EXPORT_VARIABLE(x)
#       define SMBEXPF(x,y)    EXPORT_FUNCTION(x, y)
#   else
#       define SMBEXP          IMPORT
#       define SMBEXPV(x)      IMPORT_VARIABLE(x)
#       define SMBEXPF(x,y)    IMPORT_FUNCTION(x, y)
#   endif
#else
#   define SMBEXP
#	define SMBEXPV
#	define SMBEXPF
#endif // __BUILDGSBL


#ifdef GCWINNT
typedef VOID * SMBPTR;
#define SMBNULL NULL
#else
typedef ULONG  SMBPTR;
#define SMBNULL 0
#endif

#define BALANCED    0              /*  Tree is balanced                    */
#define RIGHTHIGH   1              /*  Right side high (Tree or compare)   */
#define LEFTHIGH    2              /*  Left side high (Tree or compare)    */
#define EQUAL       3              /*  Items are equal (Compare routine)   */

#ifdef GCDOS
#define SMBMINCACHE 7              /* minimum cache size for tree to work  */
#endif // GCDOS

typedef struct smbHeader {         /* Header for tree records              */
     SMBPTR Right;                 /*  Pointer to right record             */
     SMBPTR Left;                  /*  Pointer to left record              */
     SMBPTR Equal;                 /*  Pointer to equal record             */
     SMBPTR Parent;                /*  Pointer to parent record            */
     SCHAR Balance;                /*  Balance information                 */
} SMBHEADER, *pSMBHEADER;

typedef \
INT                                /* Returns comparison identifier        */\
(*smbCompFunc)(                    /*  Key comparison routine              */\
const VOID *target,                /*  Pointer to target object            */\
const VOID *test);                 /*  Pointer to object to compare to     */

typedef struct smbKeyTable {       /* Key table structure for datafile     */
     USHORT Offset;                /*  Offset of where the key starts      */
     smbCompFunc Compare;          /*  Key comparison routine              */
} SMBKEYTABLE, *pSMBKEYTABLE;

typedef struct smbRecordInfo {     /* Record information pointers          */
     SMBPTR Number;                /*  Record Number                       */
     VOID *Record;                 /*  Pointer to the beginning of record  */
     pSMBHEADER KeyHeader;         /*  Pointer to the key being used       */
     VOID *Data;                   /*  Pointer to the actual data          */
     UINT Key;                     /*  Current key                         */
} SMBRECORDINFO, *pSMBRECORDINFO;

typedef struct smbHandle {         /* File information                     */
#ifdef GCDOS
     VOID *Cache;                  /*  Cache information                   */
     VOID *SwapFile;               /*  File pointer                        */
#endif // GCDOS
     size_t RecordLength;          /*  Length of maximum record            */
     USHORT Keys;                  /*  Number of keys in file              */
     pSMBKEYTABLE keyptr;          /*  Key table list (also counts keys)   */
     SMBPTR *Roots;                /*  Pointers to the roots of keys       */
     SMBRECORDINFO currec;         /*  Current record being worked on      */
} * SMBHANDLE;

#define RecordData(smb,head)    ((VOID *) (((CHAR *)head)+(sizeof(SMBHEADER)*(smb)->Keys)))

SMBEXPV(GBOOL) smbInserting;  /*  Currently inserting a record        */

/***************************************************************************
 * Function prototypes for file: SMBAPI.C                                  *
 ***************************************************************************/

VOID
smbInit(VOID);                     /* initialize SMB API before using      */

SMBHANDLE                          /* Pointer to open file                 */
smbOpen(                           /*  Open an in memory file              */
size_t DataLength,                 /*  Maximum length of file to open      */
pSMBKEYTABLE keyptr,               /*  Pointer to the key table            */
UINT CachedRecords);               /*  Records to Cache                    */

VOID
smbClose(                          /*  Close an SMBHANDLE                  */
SMBHANDLE mda);                    /*  Pointer to file to close            */

VOID *
smbInsert(                         /*  Insert a record into datafile       */
SMBHANDLE smb,                     /*  Pointer to file to insert to        */
const VOID *data);                 /*  Data to insert                      */

VOID
smbDelete(                         /*  Deletes the current record pointer  */
SMBHANDLE smb);                    /*  Pointer to file to delete           */

VOID *                             /* Pointer to data or NULL              */
smbGetEqual(                       /*  Get a record from a database        */
SMBHANDLE smb,                     /*  Pointer to file to update           */
const VOID *KeyInfo,               /*  Key we are searching for            */
UINT Key);                         /*  Key number to look up by            */

INT                                /* LEFTHIGH, EQUAL, or RIGHTHIGH        */
smbCompareString(                  /*  Generic string compare routine      */
const VOID *target,                /*  target string                       */
const VOID *test);                 /*  string to compare to                */

INT                                /* LEFTHIGH, EQUAL, or RIGHTHIGH        */
smbCompareLONG(                    /*  Generic Long comaprison             */
const VOID *target,                /*  1st LONG variable                   */
const VOID *test);                 /*  2nd LONG variable                   */

INT                                /* LEFTHIGH, EQUAL, or RIGHTHIGH        */
smbCompareINT(                     /*  Generic integer compare routine     */
const VOID *target,                /*  1st INT variable                    */
const VOID *test);                 /*  2nd INT variable                    */

INT                                /* LEFTHIGH, EQUAL, or RIGHTHIGH        */
smbCompareSHORT(                   /*  Generic short compare routine       */
const VOID *target,                /*  1st SHORT variable                  */
const VOID *test);                 /*  2nd SHORT variable                  */

VOID *                             /* Pointer to data or NULL              */
smbGetPrevious(                    /*  Get previous from current record    */
SMBHANDLE smb);                    /*  Handle to current smb pointer       */

VOID *                             /* Pointer to data or NULL              */
smbGetHigh(                        /*  Get highest record in the tree      */
SMBHANDLE smb,                     /*  Handle to smb information           */
UINT Key);                         /*  Key to get highest on               */

VOID *                             /* Pointer to data or NULL              */
smbGetLow(                         /*  Get the lowest record in the tree   */
SMBHANDLE smb,                     /*  Handle to smb information           */
UINT Key);                         /*  Key to get lowest on                */

VOID *                             /* Pointer to data or NULL              */
smbGetNext(                        /*  Get next from current record        */
SMBHANDLE smb);                    /*  Handle to current smb pointer       */

VOID *                             /* Pointer to data or NULL              */
smbCurrentData(                    /*  Gets data of current record         */
SMBHANDLE smb);                    /*  Pointer to smb information          */

SMBPTR                             /* Absolute number of current record    */
smbCurrentNumber(                  /*  Gets current position of record     */
SMBHANDLE smb);                    /*  Handle to smb information           */

VOID *                             /* Pointer to data or NULL              */
smbGetBynum(                       /*  Get record by absolute number       */
SMBHANDLE smb,                     /*  Handle to smb information           */
SMBPTR Number,                     /*  Record number to get                */
UINT Key);                         /*  Key number to load as current       */

VOID *
smbGetGreater(                     /* Get greater than a key               */
SMBHANDLE smb,                     /*  Pointer to file to update           */
const VOID *KeyInfo,               /*  Key we are searching for            */
UINT Key);                         /*  Key number to look up by            */

VOID *
smbGetLess(                        /* Get less than a key                  */
SMBHANDLE smb,                     /*  Pointer to file to update           */
const VOID *KeyInfo,               /*  Key we are searching for            */
UINT Key);                         /*  Key number to look up by            */

#define smbQueryEqual(x,y,z)       ((GBOOL)(smbGetEqual(x,y,z) != NULL))
#define smbQueryPrevious(x)        ((GBOOL)(smbGetPrevious(x) != NULL))
#define smbQueryNext(x)            ((GBOOL)(smbGetNext(x) != NULL))
#define smbQueryGreater(x)         ((GBOOL)(smbGetGreater(x) != NULL))
#define smbQueryLess(x)            ((GBOOL)(smbGetLess(x) != NULL))
#define smbQueryLow(x)             ((GBOOL)(smbGetLow(x) != NULL))
#define smbQueryHigh(x)            ((GBOOL)(smbGetHigh(x) != NULL))

#ifdef DEBUG

INT
smbCountLevels(                    // count levels in tree
SMBHANDLE smb,                     //   block handle
UINT key);                         //   key to display

ULONG
smbCountNodes(                     // count total # of nodes in tree
SMBHANDLE smb);                    //   block handle

GBOOL
smbVerifyNodeCount(                // make sure node count matches on all keys
SMBHANDLE smb);                    //   block handle

SMBPTR                             //   returns node with error or SMBNULL
smbVerifyBalance(                  // verify tree's balance values
SMBHANDLE smb,                     //   block handle
UINT key);                         //   key to display

SMBPTR                             //   returns node with error or SMBNULL
smbVerifyPointers(                 // verify tree's pointers
SMBHANDLE smb,                     //   block handle
UINT key);                         //   key to check

typedef \
VOID                                                                         \
(*smbOutputFunc)(                  /* element output function              */\
FILE *fp,                          /*   file to output to                  */\
const VOID *data,                  /*   element data to display            */\
INT width);                        /*   display width                      */

VOID
smbDumpTree(                       // dump binary tree to a file
SMBHANDLE smb,                     //   block handle
FILE *fp,                          //   file to output to
smbOutputFunc outFunc,             //   element output function
INT elemWidth,                     //   maximum element width
UINT key);                         //   key to display

#endif // DEBUG

#ifdef __cplusplus
};
#endif
#endif // __SMBAPI_H
