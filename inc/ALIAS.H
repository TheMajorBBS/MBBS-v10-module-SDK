/***************************************************************************
 *                                                                         *
 *   ALIAS.H                                                               *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Alias names for users (from User-ID by default, intercepted by        *
 *   GALGWI.DLL if installed).                                             *
 *                                                                         *
 *                                        - RNStein  8/2/94                *
 *                                                                         *
 *   Changed so aliasing is supported whether or not MG/I is installed,    *
 *   and sealed up alias "leaks" to prevent e-mail from being stolen.      *
 *                                                                         *
 *                                        - C. Dunn  10/18/95              *
 *                                                                         *
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   The oaofu and ouofa vectors were kept around for existing modules     *
 *   (such as MG/I), that are no longer being built, and need the old      *
 *   aliasing functionality.                                               *
 *                                                                         *
 ***************************************************************************/

#ifndef __ALIAS_H
#define __ALIAS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDALIAS
#       define ALSEXP           EXPORT
#       define ALSEXPV(x)       EXPORT_VARIABLE(x)
#       define ALSEXPF(x,y)     EXPORT_FUNCTION(x, y)
#   else
#       define ALSEXP           IMPORT
#       define ALSEXPV(x)       IMPORT_VARIABLE(x)
#       define ALSEXPF(x,y)     IMPORT_FUNCTION(x, y)
#   endif // __BUILDALIAS
#else
#   define ALSEXP
#   define ALSEXPV(x)           extern x           
#   define ALSEXPF(x,y)         extern x (* y)
#endif // __GCWINNT

#define ALSSIZ 17                  /* maximum size of user's alias         */
#define ALSAPID "GALALIAS"         /* C/S App-ID                           */
#define NOALCV "NO*ALIAS"          /* no alias "convid" value              */
#define NOALID "(No Alias Created)" /* no alias return value               */

ALSEXPV(CHAR*) alskey;       /* key required for Sysop alias funcs   */

ALSEXPV(DFAFILE*) alsbb;     /* Btrieve pointer to GALALIAS.DAT      */

__declspec(dllimport) HMCVFILE blap;

ALSEXPV(HMCVFILE) alsmb;      /* file handle to GALALIAS.MCV          */

ALSEXPV(GBOOL) useals;        /* use aliasing on the system?          */

ALSEXPV(INT) alslgn;          /* action to take at logon              */

ALSEXPF(GBOOL, alsinuse)(          /* is alias in use?                     */
const CHAR *userid,                /*   User-ID who will have alias        */
const CHAR *alias);                /*   alias to check                     */

ALSEXPF(CHAR*, alsofusr)(CHAR *userid); /* convert User-ID into alias (current) */

ALSEXPF(CHAR*, usrofals)(CHAR *alias);  /* convert alias into User-ID (current) */

ALSEXPF(CHAR*, oaofu)(CHAR *userid);    /* convert User-ID into alias (old)     */

ALSEXPF(CHAR*, ouofa)(CHAR *alias);     /* convert alias into User-ID (old)     */

ALSEXP VOID
init__galalias(VOID);              /* initialize alias handler             */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __ALIAS_H                            */
