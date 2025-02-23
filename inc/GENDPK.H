/***************************************************************************
 *                                                                         *
 *   GENDPK.H                                                              *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header file for the generic dynapak database routine      *
 *   suite in GCOMM.LIB.                                                   *
 *                                                                         *
 *                                            - C. Robert   1/17/94        *
 *                                              T. Stryker                 *
 *                                                                         *
 ***************************************************************************/

#ifndef __GENDPK_H
#define __GENDPK_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

WGSEXPV(DFAFILE*) gdpbb;           /* generic dynapak database Btrieve ptr */

struct gdprec {                    /* generic dynapak Btrieve record layout*/
     struct saunam name;           /*   dynapak name                       */
     CHAR value[1];                /*   dynapak value                      */
};

#define GDPBTR      ((struct gdprec *)gdpbb->data)

WGSEXP VOID
opngdp(VOID);                      /* open the generic dynapak database    */

#ifdef GCV2

INT  readgdp(INT direction,struct saunam *name,USHORT length,VOID *dest);
VOID writegdp(struct saunam *name,USHORT length,VOID *value);

USHORT                             /*   return number of bytes read        */
v3readgdp(                         /* read dpk from GDP db w/ conversion   */
INT dir,                           /*   direction to read (1, -1)          */
struct saunam *name,               /*   dpk to read and dest for name read */
USHORT length,                     /*   length of passed dest buffer       */
VOID *dest,                        /*   destination (NULL=leave in GDPBTR) */
CHAR *suffix);                     /*   suffix for minimal match           */

#define readgdpEQ(dpk,len,dst,fda) readgdp(0,dpk,len,dst)
#define readgdpGT(dpk,len,dst,sfx,fda) v3readgdp(1,dpk,len,dst,sfx)
#define readgdpLT(dpk,len,dst,sfx,fda) v3readgdp(-1,dpk,len,dst,sfx)
#define writegdp(dpk,len,val,fda) writegdp(dpk,len,val)

#else

WGSEXP USHORT                             /*   return number of bytes read        */
readgdpEQ(                         /* read dnp from GDP db w/ conversion   */
struct saunam *name,               /*   dpk to read and dest for name read */
USHORT length,                     /*   length of passed dest buffer       */
VOID *dest,                        /*   destination (NULL=leave in GDPBTR) */
struct flddef *fda);               /*   field def. array                   */

WGSEXP USHORT                             /*   return number of bytes read        */
readgdpGT(                         /* read dnp from GDP db w/ conversion   */
struct saunam *name,               /*   dpk to read and dest for name read */
USHORT length,                     /*   length of passed dest buffer       */
VOID *dest,                        /*   destination (NULL=leave in GDPBTR) */
CHAR *suffix,                      /*   suffix for minimal match           */
struct flddef *fda);               /*   field def. array                   */

WGSEXP USHORT                             /*   return number of bytes read        */
readgdpLT(                         /* read dnp from GDP db w/ conversion   */
struct saunam *name,               /*   dpk to read and dest for name read */
USHORT length,                     /*   length of passed dest buffer       */
VOID *dest,                        /*   destination (NULL=leave in GDPBTR) */
CHAR *suffix,                      /*   suffix for minimal match           */
struct flddef *fda);               /*   field def. array                   */

WGSEXP VOID
writegdp(                          /* write dnp to the GDP db w/ conversion*/
struct saunam *name,               /*   name of dynapak to write           */
USHORT length,                     /*   length of dynapak value            */
VOID *value,                       /*   pointer to dynapak value           */
struct flddef *fda);               /*   field def. array                   */

#endif // GCV2

WGSEXP VOID
clsgdp(VOID);                      /* close the generic dynapak database   */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __GENDPK_H
