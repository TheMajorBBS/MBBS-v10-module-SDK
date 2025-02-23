/***************************************************************************
 *                                                                         *
 *   FTG.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.      All Rights Reserved.   *
 *                                                                         *
 *   File Tagging for Download, header for FILEXFER.C                      *
 *                                                                         *
 *                                             - R. Stein  1/14/92         *
 *                                                                         *
 ***************************************************************************/

#ifndef __FTG_H
#define __FTG_H

#if 0

Brief Glossary for FILEXFER.C

     There are some confusing terms, data structures, and pointers
     that are commonly used in FILEXFER.  Here are a few explanations:

          "tagspec"             17-byte application specific structure
                                allowing an application to submit a file
                                (or files) for "tagging".  The application
                                may be called upon much later for actually
                                downloading it (or them), and the contents
                                of the tagspec will be presented to the
                                application at that time so the application
                                can perform each of the TSHXXX functions.

          ftgptr                pointer to the "working" tagspec, set
                                throughout FILEXFER.C by setftu(), to:
                                (1) the current single-file tagspec or
                                (2) the subtagspec (in ftfuptr->ftg) of
                                    the current multi-file tagspec.
                                This is a global variable for many of the
                                routines in FILEXFER.C and in the
                                application's tshxxx() routine.
                                Note, may also be used to scan tagspecs

          ftuptr->ftgptr        pointer to the "current" tagspec, may
                                be a multi-file tagspec, will always be
                                in ftgusr array (see ftgptr, above)

          ftgusr                array of "maxtags" tagspecs for the current
                                user (one slice of the ftgtbl[][] 2D array)

          ftuptr                allocated memory structure with variables
                                supporting each user online

          ftfpsp                protocol specifications (see FTF.H) for the
                                current file transfer session

          ftuptr->ftfpsp        protocol specifications for the current
                                user

          ftuptr->ftg           single-file subtagspec of the current
                                multi-file tagspec, as broken down by
                                the TSHSCN and TSHNXT exit points

          ftfscb                Session Control Block (see FTF.H) for the
                                current file transfer session

#endif                             /* if 0                                 */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define TSLENG 17                 /* length of application-specific Tagspec */

#define TSHLEN 80         /* max length of Tagspec Handler message "tshmsg" */
                   /* TSHLEN must be larger than TSLENG (see TSHSCN/TSHNXT) */
           /* TSHLEN must be larger than VIDCHUNK in FTFVIEW.H (see TSHVIS) */

#if TSHLEN < VIDCHUNK
#error TSHLEN must be larger than VIDCHUNK
#endif

WGSEXPV(CHAR) tshmsg[TSHLEN+1];     /* universal global Tagspec Handler msg */
    /* used for passing data to/from the TSHXXX tagspec handler exit points */
      /* e.g.: tagspec description, subtagspec, reject or abort explanation */

struct ftg {                                  /* tagspec handling structure */
     CHAR tagspc[TSLENG];                   /* application-specific tagspec */
     CHAR flags;                                /* tagspec flags, see below */
     INT (*tshndl)(                /* application's tagspec handler routine */
          INT tshcod);         /* tagspec handler function code (see below) */
};


/*--- Tagspec Flags ---*/

#define FTGWLD 0x01                  /* wild? yes=multi-file no=single file */
#define FTGABL 0x02                   /* taggable? no=download now or never */

/*
     Files that aren't taggable won't be offered the 'T' protocol option.
     If we're going to download it/them, we'll use your tshndl() routine
     now, and finish the download before you can call ftgsbm() again.
*/

WGSEXPV(struct ftg*) ftgptr;       /* global tagspec pointer               */
WGSEXPV(struct ftg*) ftgtbl;       /* file tagspec (2D array maxtagsxnterms)*/
WGSEXPV(struct ftg*) ftgusr;       /* global ptr to user's ftg array       */


/*--- Tagspec Handler Function Codes (FTG invokes appl-specific code) ---*/

#define TSHDSC 1  /* describe tagspec in English (store in tshmsg)          */
#define TSHVIS 2  /* is individual file visible? (rc=1 yes, rc=0 no)        */
                  /* for wild, multi-file tagspecs:                         */
#define TSHSCN 3  /*      initiate scan                                     */
#define TSHNXT 4  /*      break down into next non-wild, visible, tagspec   */
                  /* for single-file tagspecs (incl broken-down multi's)    */
#define TSHBEG 5  /*      check download permission & begin (1=ok 0=denied) */
#define TSHEND 6  /*      end complete download                             */
#define TSHSKP 7  /*      abort incomplete download, unreserve etc          */
#define TSHFIN 8  /* finished downloading or tagging files                  */
#define TSHHUP 9  /* user disconnected (called in place of TSHFIN)          */
#define TSHUNT 10 /* untag a file that was tagged                           */


WGSEXP INT
ftgnew(VOID);                                /* Issue a new tagspec pointer */
                                  /* output is ftgptr, returns 0 if no room */
                     /* call ftgnew(), fill up ftgptr->, then call ftgsbm() */
                   /* Note: ftgnew() doesn't reserve or increment anything. */
        /* You can call ftgnew() just to find out whether there is any room */
  /* for tagging or downloading.  Calling ftgnew() twice will have the same */
                                              /* effect as calling it once. */


/* After calling ftgnew() > 0, fill in ftgptr-> fields, then call ftgsbm(). */

                /* If ftgnew() == 0, you must not touch ftgptr->xxx fields, */
                      /* but you can call ftgsbm() to get an error message. */


WGSEXP INT
ftgsbm(                                    /* Submit a tagspec for download */
CHAR *prot); /* Protocol code: single-file for immediate download:  1 M C V */
                      /* multi-file for immediate download:  L A B G Z ZR K */
                                           /* tag for later download:  T TQ */
                                         /* or ask for download options:  ? */
                                   /* assumes that you just called ftgnew() */
                                           /* assumes caller calls outprf() */
            /* returns 1=usurped state/substate, will call TSHFIN or TSHHUP */
            /* returns 0=state/substate unchanged, or TSHFIN already called */

WGSEXP INT
ftgdn1(     /* ftgsbm() replacement for copies of files already in tag list */
CHAR *prot,  /* Protocol code: single-file for immediate download:  1 M C V */
VOID (*retrou)());                          /* when done, call this routine */
                      /* multi-file for immediate download:  L A B G Z ZR K */
                                           /* tag for later download:  T TQ */
                                         /* or ask for download options:  ? */
                                   /* assumes that you just called ftgnew() */
                                           /* assumes caller calls outprf() */
            /* returns 1=usurped state/substate, will call TSHFIN or TSHHUP */
            /* returns 0=state/substate unchanged, or TSHFIN already called */

WGSEXP VOID
untag(                             /* notify application of file un-tagging */
INT tagnum);                               /* number, 0 to ftuptr->numtag-1 */
                                       /* (expects setftu() to be in effect */
                 /* NOTE: for an application to untag a file, call rmvtag() */

WGSEXP VOID
numftg(    /* perform untag notification to the extent needed by new numftg */
INT newnum);                                /* new value for ftuptr->numftg */
                                       /* (expects setftu() to be in effect */
                 /* NOTE: for an application to untag a file, call rmvtag() */

WGSEXP VOID
rmvtag(                                          /* handle command to untag */
CHAR *untcmd);                   /* the command, e.g. "-1" "-2" "-3" "-ALL" */
                                       /* (expects setftu() to be in effect */

WGSEXP VOID
ftgsho(VOID);          /* list out the tagged files (caller calls outprf()) */

WGSEXP VOID
ftgdnl(                       /* download all tagged files (or untag, etc.) */
CHAR *prot,                        /* protocol for download (or "?" to ask) */
VOID (*retrou)(VOID));            /* what to call when you're done handling */
                                            /* assumes caller does outprf() */

WGSEXP INT
valdpc(                               /* Is this a valid download protocol? */
CHAR *prot);                        /* protocol code (may modify & restore) */
                                                      /* returns 1=yes 0=no */

WGSEXP INT
ftgnum(VOID);                       /* number of tagged files for this user */

WGSEXP CHAR *
tagths(               /* return tagspec of othusn/othusp if handler is same */
INT (*tshndl)(INT tshcod));                        /* return NULL otherwise */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __FTG_H                              */
