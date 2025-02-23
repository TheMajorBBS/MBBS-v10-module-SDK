/***************************************************************************
 *                                                                         *
 *   LINGO.H                                                               *
 *                                                                         *
 *   Copyright (C) 1993-1997 Galacticomm, Inc.   All Rights Reserved.      *
 *                                                                         *
 *   Multilingual information gathering and storage, based on info in      *
 *   the WGERV.CFG file.                                                   *
 *                                                                         *
 *   Used by WGSCNF, WGSMTREE, WGSMSX, MSGUTL, etc.                        *
 *                                                                         *
 *                                    - Robert N. Stein 1/7/93             *
 *                                                                         *
 ***************************************************************************/

#ifndef __LINGO_H
#define __LINGO_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LNGSIZ 16                  /* 15-character language name + NUL     */
#define LNGDSC 51               /* 50-character language description + NUL */
#define LNGEDT 41                  /* 40-character language editor + NUL   */
#define LNGEXT (1+3+1)  /* dot + 3-character language file extension + NUL */
#define LNGYN  13                  /* 12-character yes/no options + NUL    */

struct lingo {                     /* INFORMATION ON A USER-LANGUAGE       */
     CHAR name[LNGSIZ];            /* spoken language / protocol           */
     CHAR desc[LNGDSC];            /* description                          */
     CHAR extans[LNGEXT];          /* for .ANS users  \  file extensions   */
     CHAR extasc[LNGEXT];          /* for .ASC users   >  for temp files   */
     CHAR extibm[LNGEXT];          /* for .IBM users  /     & menu files   */
     CHAR editor[LNGEDT];     /* editor for .MSG options or for menu files */
     CHAR yes[LNGYN],no[LNGYN];    /* (must have unique first letters)     */
};

/*--- variables set by inilingo() ---*/
WGSEXPV(INT) nlingo;               /* number of languages                  */
WGSEXPV(INT) clingo;               /* current language                     */
WGSEXPV(struct lingo**) languages; /* dyn array of ptrs to lingo structs   */

#define DFTLNG "English/ANSI"      /* default user-language                */
#define DFTSPK "English"           /* default spoken language              */
#define DFTPRT "ANSI"              /* default protocol                     */
#define DFTEDR "wgsdraw %s"        /* default language editor              */
#define DFTYES "YES"               /* default language yes                 */
#define DFTNO  "NO"                /* default language no                  */
#define LINGOFILE "wgserv.cfg"     /* where LNG lines are to be read       */
                               /* (must agree with finint() in INTEGROU.C) */

VOID
inilingo(VOID);                    /* read and construct lingo info array  */

VOID
stfext(                            /* put exts into .ANS, .ASC, .IBM fields*/
struct lingo *lp,                  /*   destination structure              */
CHAR *exts);                       /*   extentions                         */

VOID
alclng(VOID);                      /* allocate *languages[] array of ptrs  */

INT                                /*   rets idx 0..nlingo-1 or -1=not fnd */
lngfnd(                            /* find a language by name              */
CHAR *lngnam);                     /*   name to search for                 */

INT                                /*   rets idx 0..nlingo-1 or -1=not fnd */
chgspk(                            /* determine if there is an alt. lang   */
INT lgo,                           /*   lingo                              */
CHAR *spoken);                     /*   change lang to this                */

INT                                /*   rets idx 0..nlingo-1 or -1=not fnd */
chgprt(                            /* determine if an alt. protocol exists */
INT lgo,                           /*   lingo                              */
CHAR *protoc);                     /*   change protocol to this            */

VOID
alg1st(                            /* prepare to seek alternate languages  */
INT lgo);                          /*   lingo to begin with                */

INT                                /*   rets idx 0..nlingo-1 or 0=not fnd  */
algnxt(VOID);                      /* seek alternate languages             */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __LINGO_H                            */
