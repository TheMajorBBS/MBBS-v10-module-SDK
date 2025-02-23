/***************************************************************************
 *                                                                         *
 *   GALTEXT.H                                                             *
 *                                                                         *
 *   Copyright (c) 1988-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This module contains declarations for handling formatted text.        *
 *                                                                         *
 *                                                - J. Alvrus  7/17/95     *
 *                                                                         *
 ***************************************************************************/

#ifndef __GALTEXT_H
#define __GALTEXT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define FMTDSCSZ 11                /* format description size              */
#define RTFSTKSZ 10                /* RTF reader stack size                */

typedef GBOOL                      /*   is this text in your format?       */\
        (txtdetf)(                 /* format detection function            */\
        const CHAR *srcstr);       /*   string to examine                  */

typedef GBOOL                      /*   could handle conversion?           */\
        (txtcvtf)(                 /* text converter function type         */\
        const CHAR *srcbuf,        /*   source buffer                      */\
        char *dstbuf,              /*   destination buffer                 */\
        UINT dstsiz);              /*   destination buffer size            */

typedef GBOOL                      /*   was able to insert?                */\
        (txtinsf)(                 /* text inserter function type          */\
        GBOOL endflg,              /*   insert at end (vs. at beginning)   */\
        const CHAR *srcbuf,        /*   buffer containing ASCII text       */\
        CHAR *dstbuf,              /*   buffer containing formatted text   */\
        UINT dstsiz);              /*   destination buffer size            */

struct fmthlr {                    /* formattted text handling structure   */
     CHAR fmtdesc[FMTDSCSZ];       /*   format description (e.g. "RTF")    */
     INT flags;                    /*   format handler flags               */
     txtdetf *detect;              /*   function for detecting format      */
     txtcvtf *toasc;               /*   function for converting to ASCII   */
     txtinsf *insasc;              /*   function to insert ASCII           */
     txtcvtf *stpfmt;              /*   simple format stripping function   */
};

VOID
register_fmthlr(                   /* register formatted text handler      */
struct fmthlr *fmthlr);            /*   formatted text handling struct     */

INT
nfmthlr(VOID);                     /* number of registered format handlers */

struct fmthlr const * const *
fharr(VOID);                       /* ptr to array of ptrs to fmt handlers */

GBOOL                              /*   is this text formatted?            */
isfmtted(                          /* check for formatted text             */
const CHAR *srcstr);               /*   string to examine                  */

const CHAR *                       /*   returns name of format             */
fmtname(                           /* get name of format used in this text */
const CHAR *fmtstr);               /*   string containing formatted text   */

GBOOL                              /*   was able to convert?               */
cvt2asc(                           /* convert formatted text to ASCII      */
const CHAR *fmtsrc,                /*   formatted source string            */
CHAR *ascdst,                      /*   ASCII destination buffer           */
UINT dstsiz);                      /*   destination buffer size            */

GBOOL                              /*   was able to insert?                */
insasc(                            /* insert ASCII into formatted text     */
GBOOL endflg,                      /*   insert at end (vs. at beginning)   */
const CHAR *srcbuf,                /*   buffer containing ASCII text       */
CHAR *dstbuf,                      /*   buffer containing formatted text   */
UINT dstsiz);                      /*   destination buffer size            */

GBOOL                              /*   was able to strip?                 */
stripfmt(                          /* strip formatting                     */
const CHAR *fmtsrc,                /*   formatted source string            */
CHAR *ascdst,                      /*   ASCII destination buffer           */
UINT dstsiz);                      /*   destination buffer size            */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __GALTEXT_H                          */
