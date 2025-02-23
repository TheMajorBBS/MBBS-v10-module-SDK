/***************************************************************************
 *                                                                         *
 *   DFCAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Header for use with routines in DFCAPI.LIB.                           *
 *                                                                         *
 *                                                 - Bill Hyatt 8/5/96     *
 *                                                                         *
 ***************************************************************************/
#ifndef __DFCAPI_H
#define __DFCAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "DFCAPI2.H"

#define FLDTAGSIZ 10               /* max size of field id tag             */

/* various conversion info indicators */
#define LITTLE    0                /* little endian byte order             */
#define BIG       1                /* big endian byte order                */
#define KEY       0                /* read recs from src file in key order */
#define PHYSICAL  1                /* read recs from src in physical order */
#define LEFT      1                /* truncate/justify char field, left    */
#define RIGHT     2                /* truncate/justify char field, right   */

#define MAXLSZ    300              /* max size of line from cvt desc file  */

#define NFTYP     10               /* # of different field types allowed   */

/* field types in convert descripton files */
#define T_CHAR   0                 /* character data                       */
#define T_SHORT  1                 /* short int (16 bits)                  */
#define T_LONG   2                 /* long int (32 bits)                   */
#define T_FLOAT  3                 /* floating point                       */
#define T_DOUBLE 4                 /* double                               */
#define T_VBDATE 5                 /* Visual Basic date                    */
#define T_DDATE  6                 /* DOS packed date                      */
#define T_DTIME  7                 /* DOS packed time                      */
#define T_STRUCT 8                 /* sub-structure field                  */
#define T_OPAQUE 9                 /* opaque (leave alone)                 */

/* default data field sizes (not T_CHAR or T_OPAQUE) */
#define SHORTLEN  sizeof(SHORT)    /* short ints (16 bits)                 */
#define LONGLEN   sizeof(LONG)     /* long ints (32 bits)                  */
#define FLOATLEN  sizeof(FLOAT)    /* floats                               */
#define DOUBLELEN sizeof(DOUBLE)   /* doubles                              */
#define VBDATELEN sizeof(DOUBLE)   /* Visual Basic dates                   */
#define DDATELEN  sizeof(SHORT)    /* DOS packed dates                     */
#define DTIMELEN  sizeof(SHORT)    /* DOS packed times                     */

/* indicators for conversion type */
#define DFC_NORMAL 0
#define DFC_GENDB  1

#define CVTDESCSIZ 50              /* max size of conversion description   */

#define GDBSOURCE "GenericDB"      /* cvt file indicator for generic db    */
#define GDBDOFF (UIDSIZ+MNMSIZ)    /* offset for app-spec data in gen db   */

#define GENRATIO 1.5               /* ratio for gen db & gen dpk converts  */

#define CVTCFGFIL "WGSDFCVT.CFG"   /* config file for data conversions     */
#define CVTFILDIR "WGSDFCVT"       /* default dir for conversion desc files*/

#define CVTDONEXT "CV_"            /* extension ind's cvt is done          */

#define CVTDBGFIL "WGSCVT.OUT"     /* output file for debug information    */

#define TMPDATEXT "D_T"

#define CSTCMDBSZ (7+1             + \
                   GCMAXPTH+1      + \
                   3+1             + \
                   6+1             + \
                   GCMAXPTH+1      + \
                   3+1             + \
                   6+1             + \
                   8+1             + \
                   4+1             + \
                   (MNMSIZ+UIDSIZ) + \
                   5+1)            /* size of cmd buf for cust cvt utils   */

#define MAXARGS     11
              /* max # args passed to custom cvt utils (including "debug") */
#define REQNARG     10             /* min req # args for custom cvt utils  */

/* indices to args (argv[]) for custom conversion utils */
#define KEEPIDX     1              /* keep/discard flag                    */
#define SRCIDX      2              /* source data file                     */
#define SRCPKDIDX   3              /* source packed?                       */
#define SRCBORDIDX  4              /* source byte order                    */
#define DSTIDX      5              /* destination data file                */
#define DSTPKDIDX   6              /* destination packed?                  */
#define DSTBORDIDX  7              /* destination byte order               */
#define RECORDIDX   8              /* order to traverse source data file   */
#define RATIOIDX    9              /* ratio to determine HD room needed    */

#define MODULEIDX   10             /* gen db converts: module name         */
#define USERIDIDX   11             /* gen db converts: user id             */

#define NOTSPEC     "?"            /* indicates info not found in .CVT file*/

struct fldinfo {                   /* conversion field information         */
     CHAR fldtag[FLDTAGSIZ+1];     /*   field id tag                       */
     USHORT fldtyp;                /*   field type                         */
     USHORT srcoffset;             /*   src fields: offset in source buf   */
     USHORT cvtoffset;             /*   offset in conversion buffer        */
     USHORT dstoffset;             /*   dest fields: offset in dest buffer */
     USHORT fldlen;                /*   field length                       */
     GBOOL varlen;                 /*   variable-length data in this field?*/
     USHORT maxcopy;               /*   if var len, max bytes to copy      */
     USHORT justify;               /*   dest fields: justify right or left */
     CHAR pad;                     /*   dest fields: value to pad with     */
     USHORT truncate;              /*   dest fields: truncate right or left*/
     VOID *defval;                 /*   new dest fields: default value     */
     USHORT nelems;                /*   # of elements (1 if not an array)  */
     USHORT nmembers;              /*   STRUCT: # of members               */
     USHORT largest;               /*   STRUCT: largest data type size     */
     struct fldinfo *members;      /*   STRUCT: structure members          */
     struct flddef *subFDA;        /*   STRUCT: FDA for conversions        */
};

struct fmtinfo {                   /* format information                   */
     CHAR fmttag[FLDTAGSIZ+1];     /*   format id tag                      */
     USHORT nflds;                 /*   # of fields in format              */
     struct fldinfo *fields;       /*   field list                         */
     struct flddef *fmtFDA;        /*   FDA for data conversion            */
};

struct cvtinf {                    /* info on current conversion           */
     CHAR cvtdsc[CVTDESCSIZ+1];    /*   description                        */
     CHAR srcdatfil[GCMAXPTH];     /*   source data file                   */
     GBOOL srcpacked;              /*   source data packed?                */
     USHORT srcbytord;             /*   source data byte order             */
     CHAR dstdatfil[GCMAXPTH];     /*   destination data file              */
     GBOOL dstpacked;              /*   destination data packed?           */
     USHORT dstbytord;             /*   destination data byte order        */
     CHAR *tmpsrcnam;              /*   tmp nam 4 src file if nams are same*/
     USHORT recorder;              /*   how to read source recs (key/phys) */
     SHORT keyno;                  /*   if read src by key, keyno to use   */
     FLOAT ratio;                  /*   det. disk spc needed to cvt dat fil*/
     USHORT nfmts;                 /*   # of dif formats in src data file  */
     SHORT indoffset;              /*   mult src fmts, offset for ind bytes*/
     SHORT indbuflen;              /*   mult src fmts, length of ind bytes */
     CHAR **fmtibufs;              /*   mult src fmts, various ind byt seqs*/
     struct fmtinfo *srcfmts;      /*   list of source formats             */
     struct fmtinfo *dstfmts;      /*   list of destination formats        */
     USHORT srcbuflen;             /*   length of source buffer            */
     CHAR *srcbuf;                 /*   source file data buffer            */
     USHORT cvtbuflen;             /*   length of conversion buffer        */
     CHAR *cvtbuf;                 /*   intermediate buffer for cvtData()  */
     USHORT dstbuflen;             /*   length of destination buffer       */
     CHAR *dstbuf;                 /*   destination file data buffer       */
     GBOOL variable;               /*   variable-length data files?        */
     INT srccvtflgs;               /*   srcff parm for cvtData()           */
     INT dstcvtflgs;               /*   dstff parm for cvtData()           */
     USHORT cvttype;               /*   type of conversion for generic db  */
     struct {                      /*   key struct for generic db converts */
          CHAR userid[UIDSIZ];     /*        userid                        */
          CHAR module[MNMSIZ];     /*        module name                   */
     } gendbkey;                   /*   key buffer for generic db converts */
     CHAR cstcvt[GCMAXPTH];        /*   program to run (custom/after cvt)  */
     CHAR cstcmdbuf[CSTCMDBSZ];    /*   command buffer for cstcvt          */
};

extern
struct cvtinf cvtinf;              /* global info on current conversion    */

extern
DFAFILE *srcbb,                    /* currently open src data file         */
        *dstbb;                    /* currently open dest data file        */

extern
GBOOL dbgcvt;                      /* print cvtinf info? (debugging)       */

GBOOL                              /*   returns TRUE if found info         */
readcvt(                           /* read info from conversion desc file  */
CHAR *prefix,                      /*   prefix to look for                 */
CHAR *dest,                        /*   where to put the data              */
CHAR *cvtfil,                      /*   file to search in                  */
GBOOL bomb);                       /*   catastro() if not there?           */

GBOOL                              /*   TRUE = should do conversion        */
shouldcvt(                         /* should we do the conversion...       */
CHAR *cvtfil);                     /*   ...described in this cvt desc file?*/

VOID
cvtdatfil(                         /* perform a data file conversion       */
CHAR *cvtfil,                      /*   conversion description file        */
CHAR *srcdatfil,                   /*   src file (NULL=rd fm cvt desc file)*/
CHAR *dstdatfil,                   /*   dest file (NULL=    "       "      */
GBOOL keepsrc);                    /*   keep scoure data file?             */

VOID
clrcvtinf(VOID);                   /* reset info in cvtinf                 */

#ifdef GCWINNT
CHAR *                             /*   returns ptr to stg w/ registry val */
getUpdType(VOID);                  /* get type of last upgrade from win reg*/
#endif // GCWINNT

VOID
chkSrcDstNams(                     /* mk tmp src name if src & dst are same*/
CHAR *srcdatfil,                   /*   source data file name              */
CHAR *dstdatfil,                   /*   destination data file name         */
CHAR **tmpsrcnam);                 /*   pointer to location for temp name  */

INT                                /*   0=error or EOF, 1=got line ok      */
dfgtstg(                           /* read line from cvt desc file         */
CHAR *destbuf,                     /*   destination buffer for line        */
INT size,                          /*   size of destination buffer         */
FILE *cvtfp);                      /*   file pointer to open cvt desc file */

/*----------------- display management declarations -----------------------*/

#define WINFMX1 0                  /* X1-pos to explode std window from    */
#define WINFMY1 10                 /* Y1-pos to explode std window from    */
#define WINFMX2 53                 /* X2-pos to explode std window from    */
#define WINFMY2 17                 /* Y2-pos to explode std window from    */
#define WINX    13                 /* X-pos to explode std window to       */
#define WINY    8                  /* Y-pos to explode std window to       */
#define NOSHOWIN -1                /* for dfcDspInit: don't explode window */

#define CVTNUMX 27                 /* X-pos for "Conversion X of Y"        */
#define CVTNUMY 9                  /* Y-pos for "Conversion X of Y"        */
#define CVTNUMDSIZ sizeof("9999 of 9999")
                                   /* size of "Conversion X of Y" buffer   */

#define CVTDSCX 15                 /* X-pos for conversion description     */
#define CVTDSCY 10                 /* Y-pos for conversion description     */

#define CVTFILX 32                 /* X-pos for src & dest file display    */
#define CVTFILY 12                 /* Y-pos for src & dest file display    */
#define CVTFILDSIZ sizeof("XXXXXXXX.XXX to XXXXXXXX.XXX")
                                   /* size of src & dest display buffer    */

#define CVTRECX 23                 /* X-pos for "Record X of Y"            */
#define CVTRECY 14                 /* Y-pos for "Record X of Y"            */
#define CVTRECDSIZ sizeof("9999999999 of 9999999999")
                                   /* size of "Record X of Y" buffer       */
#define NODISP 0                   /* don't display total records          */

#define _NOSCNS_ CHAR scntbl[1][GVIDSCNSIZ];
/* dummy declare - keep DFCDISP.C happy for modules which don't link in .SCN
   files but which still need to call display functions */

extern
CHAR scntbl[][GVIDSCNSIZ];         /* pre-obj'd screen files               */

VOID
dfcDspInit(                        /* init display window, save scn info   */
SHORT scnidx);                     /*   idx of std window in scntbl[]      */

VOID
dfcDspCvtNum(                      /* display "Converion X of Y"           */
USHORT cvtnum,                     /*   current conversion                 */
USHORT cvttot);                    /*   total conversions                  */

VOID
dfcDspCvtDesc(                     /* display conversion description       */
CHAR *cvtdesc);                    /*   description to display             */

VOID
dfcDspFiles(                       /* display source and destination files */
CHAR *srcdatfil,                   /*   source file name                   */
CHAR *dstdatfil);                  /*   destination file name              */

VOID
dfcDspRecs(                        /* display "Record X of Y"              */
ULONG currec,                      /*   current record                     */
ULONG totrec);                     /*   total records                      */

VOID
dfcClrRecs(VOID);                  /* clear record display                 */

VOID
dfcDspFin(VOID);                   /* restore screen                       */

/*----- declarations and routines for custom conversion utilities ---------*/

extern CHAR *takeptr;              /* current take API source pointer      */
extern size_t takeleft;            /* number of bytes left in take source  */
extern INT takesf;                 /* source conversion flags              */
extern INT takedf;                 /* destination conversion flags         */

VOID
takeInit(                          /* initialize take API for new source   */
VOID *src,                         /* data input source                  */
size_t len,                        /*   length of source                   */
INT srcflg,                        /*   source conversion flags            */
INT dstflg);                       /*   destination conversion flags       */

INT                                /*   returns 1 if ok, 0 if overflow     */
takeUtil(                          /* take bytes out of source             */
VOID *dst,                         /*   where to put bytes (NULL to eat)   */
size_t num,                        /*   bytes to take (0 for rest)         */
struct flddef *fda);               /*   FDA to use for conversion          */

#define takeChar(dst,num)  takeUtil((dst),(num),charsFDA)
#define takeShort(dst,num) takeUtil((dst),sizeof(SHORT)*(num),shortsFDA)
#define takeLong(dst,num)  takeUtil((dst),sizeof(LONG)*(num),longsFDA)

/* error codes returned by dfcCustxxx() functions */
#define ERR_NARG    1                   /* wrong # arguments passed        */
#define ERR_VIR     2                   /* unable to create dest data file */
#define ERR_SRCPKD  3                   /* SourcePacked not specified      */
#define ERR_SRCBORD 4                   /* SourceByteOrder not specified   */
#define ERR_DSTPKD  5                   /* DestPacked not specified        */
#define ERR_DSTBORD 6                   /* DestByteOrder not specified     */
#define ERR_MODNAM  7                   /* ModuleName not specified        */
#define ERR_USERID  8                   /* UserID not specified            */
#define ERR_TMPNAM  9                   /* unable to rename src to tmp name*/

USHORT                                  /*   0=all ok, err otherwise       */
dfcCustInit(                            /* chk things / init environment   */
INT argc,                               /*   # args passed to cust util    */
CHAR *argv[],                           /*   args passed to cust util      */
CHAR *id);                              /*   cust utility id stg           */

USHORT                                  /*   0=all ok, err otherwise       */
dfcCustInitGen(                         /* init evironment for gen db cvt  */
INT argc,                               /*   # args passed to cust util    */
CHAR *argv[],                           /*   args passed to cust util      */
CHAR *id);                              /*   cust utility id stg           */

VOID
dfcOpenFiles(                           /* open data files                 */
USHORT srcreclen,                       /*   source record length          */
USHORT dstreclen);                      /*   destination record length     */

GBOOL                                   /*   TRUE=opened ok                */
dfcOpenFilesGen(                        /* open data files for gen db cvt  */
USHORT srcreclen,                       /*   source record length          */
LONG *srcfsiz,                          /*   size of source data file      */
USHORT dstreclen);                      /*   destination record length     */

GBOOL                                   /*   TRUE=enough disk space        */
dfcChkDskSpc(                           /* check HD room for conversion    */
ULONG ratiobase);                       /*   base ratio multiplier         */

USHORT                                  /*   0=all ok, err otherwise       */
dfcSupFlags(                            /* set up conversion flags         */
INT *srcflg,                            /*   source conversion flags       */
INT *dstflg);                           /*   dest conversion flags         */

CHAR *                                  /*   returns pointer to buffer     */
dfcLastErr(VOID);                       /* get last error message          */

VOID
WriteOldRegistry(VOID);            /*  Write old registry information      */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __DFCAPI_H
