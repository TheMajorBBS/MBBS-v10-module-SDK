/***************************************************************************
 *                                                                         *
 *   CVTAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header file for data element conversion/alignment.        *
 *                                                                         *
 *                                            - I. Minkin 12/21/95         *
 *                                                                         *
 ***************************************************************************/

#ifndef __CVTAPI_H
#define __CVTAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>

struct WGSEXP flddef {                    /* field definition structure           */
     ULONG type;                   /*   type of field                      */
     INT nelem;                    /*   number of elements                 */
     INT offset;                   /*   offset of field within structure   */
     struct flddef *substruct;     /*   for structs within structs         */
};

#define MAXCVT  40                 /* maximum number of field types in FDA */

                                   /* field subtypes for add. conversion   */
#define CVTSUBFLD_RTEXT  (0x00010000L) /* readable text (translate charset)*/
#define CVTSUBFLD_ZVBSTG (0x00020000L) /* zero term. string (VB <-> C conv)*/

                                   /* FDA field types                      */
#define CVTFLD_END      (0x0)      /*   end of field-definition            */
#define CVTFLD_CHAR     (0x1)      /*   char                               */
#define CVTFLD_SHORT    (0x2)      /*   short (16 bits)                    */
#define CVTFLD_LONG     (0x3)      /*   long (32 bits)                     */
#define CVTFLD_FLOAT    (0x4)      /*   float                              */
#define CVTFLD_DOUBLE   (0x5)      /*   double                             */
#define CVTFLD_OPAQUE   (0x6)      /*   opaque (leave alone)               */
#define CVTFLD_VBDATE   (0x7)      /*   Visual Basic date/time             */
#define CVTFLD_DDATE    (0x8)      /*   DOS date                           */
#define CVTFLD_DTIME    (0x9)      /*   DOS time                           */
#define CVTFLD_STRUCT   (0x10)     /*   another structure                  */
#define CVTFLD_RTEXT    (CVTFLD_CHAR|CVTSUBFLD_RTEXT)  /* readable text    */
#define CVTFLD_ZVBSTG   (CVTFLD_CHAR|CVTSUBFLD_ZVBSTG) /* Z-string         */
#define CVTFLD_RZVBSTG  (CVTFLD_CHAR|CVTSUBFLD_RTEXT|CVTSUBFLD_ZVBSTG)
                                             /* readable text as Z-string  */

/* These numbers are used to init. array of conversion function pointers   */
/* in cvtapi.c if you need to change or add values you need to review      */
/* the array.                                                              */

                                   /* cvtData*() xxxff format flags        */
                                   /*  lowest level: flag !set == opposite */
#define CVTBIGEND      (0x0001)    /*   format is big endian (vs. little)  */
#define CVTPACKED      (0x0002)    /*   format is packed (vs. unpacked)    */
#define CVTISCLIENT    (0x0004)    /*   data is client specific            */

                                   /*  highest level: pre-set format flags */
#ifdef BIGEND
#ifdef GCPACKED
#define CVTSERVER   (CVTBIGEND|CVTPACKED) /* current server(bigend&packed) */
#else
#define CVTSERVER   CVTBIGEND      /*   current server (bigend & unpacked) */
#endif // GCPACKED
#else
#ifdef GCPACKED
#define CVTSERVER   CVTPACKED      /*   current server (litend & packed)   */
#else
#define CVTSERVER   (0x0000)       /*   current server (litend & unpacked) */
#endif // GCPACKED
#endif // BIGEND

#define CVTCLIENT   (CVTPACKED|CVTISCLIENT) /* current client (packed now) */

                                   /* register new conversion return codes */
#define CVTOOR  -3                 /*   out of range                       */
#define CVTNUL  -2                 /*   null function                      */
#define CVTXST  -1                 /*   conversion function already exists */
#define CVTOK    0                 /*   all ok                             */

#define ALLOC_BOUNDARY  4          /* allocation boundary for malloc()     */

#define fldoff(struc,field)  offsetof(struct struc,field)

#ifdef GCDOS
#define BYTEALIGN(p) (p)
#else
#define BYTEALIGN(p) ((((ULONG)p)+ALLOC_BOUNDARY-1)&(~(ALLOC_BOUNDARY-1)))
#endif // GCDOS

struct __tagT__ {
     CHAR a;
     DOUBLE b;
};
#define MAXPADDING (fldoff(__tagT__,b))

WGSEXPV(CHAR*) cvttmp;             /* rsptmp-like buf for cvtData*()'d data*/
WGSEXPV(INT) cvtbufsiz;            /* current size of conversion buffer    */
#define CVTBUFSIZ  0x7FFF          /* default size to make conversion buf  */

                                         /* generic FDA's for C-types      */
WGSEXPV(struct flddef) charFDA[];  /*   one character                      */
WGSEXPV(struct flddef) charsFDA[]; /*   array of characters                */
WGSEXPV(struct flddef) shortFDA[]; /*   one short (2-bytes)                */
WGSEXPV(struct flddef) shortsFDA[];/*   array of shorts                    */
WGSEXPV(struct flddef) intFDA[];   /*   one int (2/4-bytes)                */
WGSEXPV(struct flddef) intsFDA[];  /*   array of ints                      */
WGSEXPV(struct flddef) longFDA[];  /*   one long (4-bytes)                 */
WGSEXPV(struct flddef) longsFDA[]; /*   array of longs                     */
WGSEXPV(struct flddef) floatFDA[]; /*   one float (4-bytes)                */
WGSEXPV(struct flddef) floatsFDA[];/*   array of floats                    */
WGSEXPV(struct flddef) doubleFDA[];/*   one double (8-bytes)               */
WGSEXPV(struct flddef) doublesFDA[];/*   array of doubles                  */
WGSEXPV(struct flddef) rtextFDA[]; /*   readable text (charset conv.)      */
WGSEXPV(struct flddef) zvbstgFDA[];/*   string (C <-> VB conversion)       */
WGSEXPV(struct flddef) rzvbstgFDA[];/*   readable text string              */

typedef VOID (*CVTFUNC)(const VOID *src,VOID *dst,INT *srcUsed,INT *dstUsed,
                        INT nelem,size_t size);

                                   /* implicit inputs to CVTFUNCs          */
WGSEXPV(ULONG) cvtType;            /*   full field type (inc'ing sub-types)*/
WGSEXPV(ULONG) cvtFlags;           /*   internal conversion flags (below)  */
WGSEXPV(INT) cvtChan;              /*   channel number (or CHAN_NUL)       */

                                   /* internal flags for data conversion   */
#define CVTFLAG_SWAPBYTES   0x01   /*   must flip int bytes (endianness)   */
#define CVTFLAG_C2SCVT      0x02   /*   actual client -> server conversion */
#define CVTFLAG_S2CCVT      0x04   /*   actual server -> client conversion */

#ifdef GCV2S

#define inicvt() ((VOID)0)
#define cvtData(src,dst,sln,fd,sf,df,u) (memcpy(dst,src,sln),sln)
#define cvtDataIP(buf,iln,omx,fd,if,of,u) ((INT)iln)
#define cvtRegister(id,f,siz,ovr) (0)
#define lngval(p) (*((LONG *)(p)))
#define ulngval(p) (*((ULONG *)(p)))
#define shtval(p) (*((SHORT *)(p)))
#define ushtval(p) (*((USHORT *)(p)))
#define shtset(p,v) ((VOID)(*((SHORT *)(p))=(v)))
#define ushtset(p,v) ((VOID)(*((USHORT *)(p))=(v)))
#define lngset(p,v) ((VOID)(*((LONG *)(p))=(v)))
#define ulngset(p,v) ((VOID)(*((ULONG *)(p))=(v)))

#else

#define inicvt() if (cvttmp == NULL) cvttmp=alcmem(cvtbufsiz=CVTBUFSIZ)
                                   /* pseudo initialize CVTAPI macro       */

WGSEXP INT                                /*   returns size of converted dst      */
cvtData(                           /* convert data from buffer to buffer   */
const VOID *src,                   /*   source data (one format)           */
VOID *dst,                         /*   destination data (maybe dif format)*/
INT srclen,                        /*   length of source data              */
const struct flddef *fdef,         /*   field definition array to use      */
INT srcff,                         /*   format flags for src (from)        */
INT dstff,                         /*   format flags for dst (to)          */
INT userNum);                      /*   user number (or CHAN_NUL)          */

WGSEXP INT                                /*   returns number of bytes converted  */
cvtDataIP(                         /* convert data in-place                */
VOID *buf,                         /*   buffer (source and destination)    */
INT inlen,                         /*   length of buffer IN                */
INT outmax,                        /*   max length of buffer OUT           */
const struct flddef *fdef,         /*   field definition array to use      */
INT inff,                          /*   format flags for buffer IN (from)  */
INT outff,                         /*   format flags for buffer OUT (to)   */
INT userNum);                      /*   user number (or CHAN_NUL)          */

WGSEXP INT                                /*   returns 0 if ok, otherwise error # */
cvtRegister(                       /* register a new conversion function   */
ULONG cvtID,                       /*   id you wish to register            */
CVTFUNC cvtFunction,               /*   function to register               */
size_t elementSize,                /*   size of element                    */
GBOOL fOverride);                  /*   override existing function flag    */

/* Handy functions for aligning (not byte-swapping) data    */

WGSEXP LONG                               /*   returns LONG value aligned properly*/
lngval(                            /* align a LONG value properly          */
const VOID *ptr);                  /*   pointer to source buffer           */

WGSEXP ULONG                              /*   rets ULONG value aligned properly  */
ulngval(                           /* align a ULONG value properly         */
const VOID *ptr);                  /*   pointer to source buffer           */

WGSEXP SHORT                              /*   returns SHORT value aligned proper */
shtval(                            /* align a SHORT value properly         */
const VOID *ptr);                  /*   pointer to source buffer           */

WGSEXP USHORT                             /*   returns USHORT value aligned proper*/
ushtval(                           /* align a USHORT value properly        */
const VOID *ptr);                  /*   pointer to source buffer           */

WGSEXP VOID
shtset(                            /* sets the offset in a buff to value   */
VOID *ptr,                         /*   pointer to buffer                  */
SHORT value);                      /*   value to put into buffer           */

WGSEXP VOID
ushtset(                           /* sets the offset in a buff to value   */
VOID *ptr,                         /*   pointer to buffer                  */
USHORT value);                     /*   value to put into buffer           */

WGSEXP VOID
lngset(                            /* sets the offset in a buff to value   */
VOID *ptr,                         /*   pointer to buffer                  */
LONG value);                       /*   value to put into buffer           */

WGSEXP VOID
ulngset(                           /* sets the offset in a buff to value   */
VOID *ptr,                         /*   pointer to buffer                  */
ULONG value);                      /*   value to put into buffer           */

#endif // GCV2S

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __CVTAPI_H
