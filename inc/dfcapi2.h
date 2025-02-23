/***************************************************************************
 *                                                                         *
 *   DFCAPI2.H                                                             *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Datafile conversion stuff                                             *
 *                                                                         *
 *                                           - Wally Muharsky 09/04/97     *
 *                                                                         *
 ***************************************************************************/
#ifndef DFCAPI2_H
#define DFCAPI2_H

#include "CVTAPI.H"

#define DFC_DOS          0         /*  Identifies dos datafile             */
#define DFC_WNT          1         /*  Identifies windows nt datafile      */
#define DFC_END          -1        /*  End of platform specific list       */

#define DFC_FORWARD      1         /*  Search forward through database     */
#define DFC_BACKWARD     2         /*  Search backward through database    */

#define DFC_NAMSIZ       20        /*  Size of name tags                   */

#define DFC_TEMPFILE "$$$___.TMP"  /*  Temporary datafile name             */

typedef struct tagDFCDATAFIELDS {  /* Datafile fields definition           */
     CHAR Name[DFC_NAMSIZ];        /*  Name of the field                   */
     UINT Type;                    /*  Type of the field                   */
     INT nelems;                   /*  Number of elements                  */
     struct tagDFCDATAFIELDS *substruct;/*  Pointer to sub structure       */
} DFCDATAFIELDS,*pDFCDATAFIELDS;

typedef struct tagDFCOFFSETS {     /* Offset information structure         */
     CHAR Name[DFC_NAMSIZ];        /*  Name of the variable                */
     UINT Type;                    /*  Type of record it is                */
     INT nelems;                   /*  Number of elements                  */
     UINT Offset;                  /*  Offset within data record           */
} DFCOFFSETS,*pDFCOFFSETS;

typedef struct tagDFCFILEINFO {    /*  File info to pass to conversions    */
     INT Platform;                 /*  Current system Platformm            */
     CHAR Name[GCMAXPTH];          /*  Conversion file                     */
     INT Type;                     /*  Conversion macros (CVTBIGEND...)    */
     pDFCDATAFIELDS Fields;        /*  Pointer to the fields in data       */
     pDFCOFFSETS Offsets;          /*  Pointers to offset information      */
     UINT Offsetsn;                /*  Number of offsets                   */
     struct flddef *fdef;          /*  Field definition array (set up)     */
     CHAR *Data;                   /*  Pointer to actual data              */
     size_t DataLength;            /*  Length of the data                  */
     struct flddef** fdefs;        /*  Used to allocate memory for fdef    */
     UINT fdefsn;                  /*  Number of field defs                */
} DFCFILEINFO,*pDFCFILEINFO;

typedef VOID* DFCFUNCTION;
typedef DFCFUNCTION (*pDFCFUNCTION)(pDFCFILEINFO from,pDFCFILEINFO to);

typedef struct tagDFCFILE {        /* Datafile information                 */
     CHAR Name[GCMAXPTH];          /*  Name of the datafile                */
     pDFCFUNCTION cnvfunc;         /*  Conversion function                 */
     pDFCDATAFIELDS cnvfields;     /*  Conversion fields                   */
} DFCFILE,*pDFCFILE;

typedef struct tagDFCLIST {        /*  Platform Specific list of files     */
     INT Platform;                 /*  Operating system for file list      */
     pDFCFILE file;                /*  Pointer to the file information     */
} DFCLIST,*pDFCLIST;

typedef struct tagDFCPFCONVERT {   /*  Platform conversion                 */
     INT PlatformFrom;             /*  Platform converting from            */
     INT PlatformTo;               /*  Platform converting to              */
     pDFCFUNCTION cnvfunc;         /*  Pointer to conversion function      */
} DFCPFCONVERT,*pDFCPFCONVERT;

#define DFCFLD_END       0         /*  End of conversion field             */
#define DFCFLD_CHAR      1         /*  Char datafield                      */
#define DFCFLD_SHORT     2         /*  Short datafield (16 bits)           */
#define DFCFLD_LONG      3         /*  Long datafield (32 bits)            */
#define DFCFLD_FLOAT     4         /*  Float datafield                     */
#define DFCFLD_DOUBLE    5         /*  Double datafield                    */
#define DFCFLD_OPAQUE    6         /*  Opaque/Char datafield               */
#define DFCFLD_STRUCT    7         /*  Struct datafield                    */
#define DFCFLD_VCHAR     8         /*  VARIABLE CHAR field                 */
#define DFCFLD_VSHORT    9         /*  VARIABLE SHORT fields               */
#define DFCFLD_VLONG     10        /*  VARIABLE LONG fields                */
#define DFCFLD_VFLOAT    11        /*  VARIABLE FLOAT fields               */
#define DFCFLD_VDOUBLE   12        /*  VARIABLE DOUBLE fields              */
#define DFCFLD_VOPAQUE   13        /*  VARIABLE OPAQUE fields              */
#define DFCFLD_VSTRUCT   14        /*  VARIABLE STRUCT fields              */

extern GBOOL dfcAskForBackup;      /*  Ask for backup directory?           */

/***************************************************************************
 * Function declarations                                                   *
 ***************************************************************************/
UINT                               /*  Number of bytes of field size       */
dfcFieldSize(                      /* Gets field size of data type         */
UINT Type);                        /*  Type of datafield                   */

GBOOL                              /*  TRUE if conversion took place       */
dfcRegister(                       /*  Register and search for files       */
const CHAR *descrp,                /*  Description name                    */
const DFCLIST *dfc,                /*  pointer to all DFCFILES             */
const DFCPFCONVERT *pfconv,        /*  Platform Converter                  */
INT Key,                           /*  Key number to use (-1 for physical) */
INT Direction);                    /*  Direction (DFC_FORWARD/DFC_BACKWARD)*/

GBOOL                              /*  TRUE if conversion took place       */
dfcRegisterGDB(                    /*  Register conversion for GDB         */
const CHAR *descrp,                /*  Description of conversion           */
const DFCLIST *dfc,                /*  Pointer to list of information      */
const DFCPFCONVERT *pfconv,        /*  Pointer to OS conversions           */
const CHAR *ModuleName);           /*  Module name registering             */

DFCFUNCTION                        /*  Pointer to new data                 */
dfcConvertDefault(                 /* Default conversion function          */
pDFCFILEINFO from,                 /*  File information converting from    */
pDFCFILEINFO to);                  /*  File information converting to      */

DFCFUNCTION                        /*  Pointer to new data                 */
dfcConvertPFDefault(               /* Default Platform conversion          */
pDFCFILEINFO from,                 /*  File information converting from    */
pDFCFILEINFO to);                  /*  File information converting to      */

pDFCOFFSETS                        /*   returns ptr to field offset info   */
dfcFindOffset(                     /* find offset of a particular field    */
pDFCFILEINFO info,                 /*   file information converting from   */
const CHAR *fieldName);            /*   name of field to find              */

struct flddef *                    /*  Pointer to FDA structure            */
dfcGetFDA(                         /* Get an FDA from type of convert      */
UINT Type);                        /*  Type of option                      */

VOID
dfcError(                          /*  Print an error to screen            */
const CHAR *stg,                   /*  String to print                     */
...);                              /*  Extra arguments                     */

VOID
dfcDisplayInfo(                    /* Display DFC information              */
const CHAR *Description,           /*  Description to display              */
const CHAR *FileFrom,              /*  File converting from                */
const CHAR *FileTo,                /*  File converting to                  */
ULONG Records);                    /*  Number of records to display        */

VOID
dfcDisplayStats(                   /*  Display the stats bar               */
ULONG TotalRecords,                /*  Total records in conversion         */
ULONG DoneRecords);                /*  Number of records completed         */

VOID
dfcDisplayBackup(VOID);            /*  Display backup notice               */

VOID
dfcDisplayShutdown(VOID);          /*  Release captured video screen       */

VOID
dfcDeleteBackupFile(VOID);         /*  Delete the backup file (if exist)   */

INT                                /*  DFC_DOS, DFC_WNT, DFC_END           */
dfcFilePlatform(                   /* Files platform                       */
const CHAR *file);                 /*  Pointer to file to check            */

VOID
dfcAskBackup(VOID);                /*  Ask the backup directory            */

CHAR *
dfcBackupDirectory(VOID);          /*  Returns pointer to backup direc     */

GBOOL
dfcBackupRequired(VOID);           /*  Is a backup required?               */

#endif //DFCAPI2_H
