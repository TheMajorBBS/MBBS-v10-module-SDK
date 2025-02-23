/***************************************************************************
 *                                                                         *
 *   CRNUL.H                                                               *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Encodes and Decodes Network Virtual Terminal's CR-NUL pairs, per      *
 *   RFC 854, the Telnet RFC.                                              *
 *                                                                         *
 *                                        - R. Stein and C. Dunn 2/15/96   *
 *                                                                         *
 ***************************************************************************/

#ifndef __CRNUL_H
#define __CRNUL_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct crnul {                     /* session control block for crndec()   */
     GBOOL crlast;                 /*   TRUE=last block ended with a CR    */
};

VOID
crndinit(                          /* initialize crndec() session          */
struct crnul *crnp);               /*   session control block              */
                                   /*   setmem(,,0) acceptable alternative */

UINT                               /*   ret # of decoded bytes (< nbytes)  */
crndec(                            /* decode CR-NUL pairs, per RFC 854     */
struct crnul *crnp,                /*   session control block for crndec() */
CHAR *block,                       /*   encoded bytes                      */
UINT nbytes);                      /*   number of bytes in encoded form    */
                                   /*   Note:  crndec(), if it is called   */
                                   /*   at all, should be called *AFTER*   */
                                   /*   iacdec() (i.e. CR-NUL encoding is  */
                                   /*   a higher level than IAC encoding). */
                                   /*   Otherwise, suboption negotiation   */
                                   /*   fields could be corrupted.         */

UINT                               /*   returns number of converted bytes  */
crnenc(                            /* encode CR-NUL pairs, per RFC 854 NVT */
CHAR *block,                       /*   bytes, converted in-place          */
UINT nbytes,                       /*   original number of bytes           */
UINT maxbytes);                    /*   max converted bytes (eg nbytes*2)  */
                                   /*   crenc() will never grow a block to */
                                   /*   more than double its origional     */
                                   /*   size.  Therefore, the ideal value  */
                                   /*   for maxbytes is nbytes*2.          */
                                   /*   Moreover, crenc() combined with    */
                                   /*   iacenc() will never grow a block   */
                                   /*   to more than double it's           */
                                   /*   pre-encoded "raw" form.            */
                                   /*   Note:  crnenc(), if it is called   */
                                   /*   at all, should be called *BEFORE*  */
                                   /*   iacdec() (i.e. CR-NUL encoding is  */
                                   /*   a higher level than IAC encoding). */
                                   /*   There is no penalty for violating  */
                                   /*   this rule, it's just consistent    */
                                   /*   with the rule for crndec().        */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __CRNUL_H                            */
