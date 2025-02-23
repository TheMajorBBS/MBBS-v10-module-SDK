/***************************************************************************
 *                                                                         *
 *   WGSMM.H                                                               *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.  All rights reserved.       *
 *                                                                         *
 *   This is the interface to WGSMAINM.DLL's exported symbols.             *
 *                                                                         *
 *                                              - D. Pitchford 8/5/96      *
 *                                                                         *
 ***************************************************************************/

#ifndef __WGSMM_H
#define __WGSMM_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDWGSMM
#       define WGSMMEXP         EXPORT
#       define WGSMMEXPV(x)     EXPORT_VARIABLE(x)
#       define WGSMMEXPF(x,y)   EXPORT_FUNCTION(x, y)
#   else
#       define WGSMMEXP         IMPORT
#       define WGSMMEXPV(x)     IMPORT_VARIABLE(x)
#       define WGSMMEXPF(x,y)   IMPORT_FUNCTION(x, y)
#   endif // __BUILDWGSERVER
#else
#   define WGSMMEXP
#   define WGSMMEXPV(x)         extern x           
#   define WGSMMEXPF(x,y)       extern x (* y)
#endif // __GCWINNT

WGSMMEXPV(CHAR*) medkey;           /* key required to use menu editor      */
                                   /*   NULL if menu editor not existent   */

struct pgllist {                   /* struct for top-of-tree page llists   */
     struct pgllist *next;         /*   next in linked list                */
     CHAR pagedata[1];             /*   page information, partially allocd */
};

WGSMMEXPV(struct pgllist *) aaftop;  /* first top-of-tree page for a/a       */
WGSMMEXPV(struct pgllist *) csftop;  /* first top-of-tree page for c/s       */
WGSMMEXPV(struct pgllist *) csfgop;  /* first goable page for c/s            */

WGSMMEXPV(SHORT) gofind;           /* option for main menu app go/find     */
                                   /* 0 = none  -1 = normal  1 = fast      */

WGSMMEXP CHAR *                    /*   returns "" for orphan              */
gofdesc(                           /* return description of page from menu */
struct mnupag *mp);                /*   page to get description of         */

WGSMMEXP VOID
pglset(                            /* set current linked list              */
struct pgllist **pgltop);

WGSMMEXP VOID
pglclear(VOID);                    /* destroy current linked list          */

WGSMMEXP VOID
pglopins(                          /* insert a page key in memory          */
CHAR *pagedata);                   /*   page name/data                     */

WGSMMEXP GBOOL                     /*   TRUE=succeeded, FALSE=no such page */
pglopdel(                          /* delete a page key from memory        */
CHAR *pagnam);                     /*   page name                          */

WGSMMEXP struct pgllist *          /*   page, or NULL if no exist          */
pglopgeq(                          /* get page struct in memory            */
CHAR *pagnam);                     /*   page name                          */

WGSMMEXP struct pgllist *          /*   page, or NULL if no exist          */
pglopggt(                          /* get next greater page struct in mem  */
CHAR *pagnam);                     /*   page name                          */

WGSMMEXP struct pgllist *          /*   page, or NULL if no exist          */
pglopglt(                          /* get next lesser page struct in mem   */
CHAR *pagnam);                     /*   page name                          */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __WGSMM_H
