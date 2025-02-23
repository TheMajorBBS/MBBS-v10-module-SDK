/***************************************************************************
 *                                                                         *
 *   FTF.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1991-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   File Transfer Software header file                                    *
 *                                                                         *
 *   With all operating-system-specific functions removed (I/O, disk,      *
 *   memory, time), the pure file transfer algorithm can be isolated.      *
 *                                                                         *
 *                                             - R. Stein  5/19/91         *
 *                                                                         *
 ***************************************************************************/

#ifndef __FTF_H
#define __FTF_H

#if 0

                             ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
                             ³               ³
                             ³  Application  ³
                             ³    Program    ³
                             ³               ³
                             ÀÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÙ
                          entry ³          ³ setup
                         points ³          ³ &
                  ÚÄ            ³          ³ maintenance
     File         ³   ÉÍÍÍÍÍÍÍÍÍ³Í»        ³
     transfer     ³   ºÉÍÍÍÍÍÍÍÍÍÍ»       
     algorithms   ³   ººÉÍÍÍÍÍÍÍÏÍÍÍ»    ÉÍÏÍÍÍÍÍÍÍÍÍ»
     (multiple   Ä´   ººº FTFxxxx.C º    º FTF.C     º
     protocols,   ³   ººº protocol- ÇÄÄÄ¶ file xfer º
     multiple     ³   Èºº specific  ÇÄÄÄ¶ utilities º
     simultaneous ³    Èº code      º    º           º
     sessions)    ³     ÈÍÍÍÍÍÍÍÑÍÍÍ¼    ÈÍÑÍÑÍÍÍÍÍÍÍ¼
                  ÀÄ            ³   exit   ³ 
                                ³  points  ³ ³ utilities
                                           ³
                              ÚÄÁÄÄÄÄÄÄÄÄÄÄÁÄÁ¿
                              ³ Operating     ³
                              ³ System        ³
                              ³ interface     ³
                              ³ (I/O, disk,   ³
                              ³ memory, time) ³
                              ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ


Non-portability issues:

     *  Expects file names to be 1 to 13 characters long

     *  Supports two date&time formats:
             DOS 16-bit YYYYYYYMMMMDDDDD HHHHHMMMMMMSSSSS format,
                  2-second resolution, 1/1/1980 to 12/31/2107
             UNIX 32-bit seconds since 1/1/1970, local time or GMT,
                  good until 2/7/2106


Notes:

     FTF expects the application program to wait until all output is
     done, and then to set the appropriate output mode (ASCII or binary).
     The application can expect FTF to be finished all significant
     transmitting (at least ftfoba() == ftfomt) before it returns control
     to the application.

#endif                             /* if 0                                 */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*--- File Transfer Protocol Specification, with Entry points ---*/

struct ftfpsp {                    /* File transfer protocol specifications */
     struct ftfpsp *next;                         /* linked list connection */
     CHAR code[4];                         /* 1-3 code letters for protocol */
     CHAR *name;              /* name of protocol (e.g. "XMODEM") max 29 ch */
     CHAR flags;                   /* protocol capability flags (see below) */
     INT scblen; /* total length of session control block (ftfscb & beyond) */
     USHORT byttmo;                      /* default byte timeout (in ticks) */
     USHORT paktmo;                    /* default packet timeout (in ticks) */
     USHORT retrys;                                  /* default max retries */
     LONG window;      /* def window size (packets or bytes as appropriate) */
     USHORT paksiz;                            /* packet size 0=auto-figure */
     VOID (*initze)(VOID);   /* Initialize this protocol (recompute scblen) */
     VOID (*start)(VOID);                       /* Start a transfer session */
     INT (*contin)(VOID);    /* Continuously call, 1=more, 0=done, -1=error */
     VOID (*hdlinc)(CHAR c);     /* Handle one incoming byte (!FTFASC mode) */
                             /* (see about pointing to ftfinc() here) */
     VOID (*hdlins)(CHAR *stg);    /* Handle inc line of text (FTFASC mode) */
                             /* NULL means (Q)uit entered by operator */
     VOID (*term)(CHAR *msg);   /* Initiate graceful term of transfer & why */
                       /* (and keep calling contin() while it returns 1) */
     VOID (*abort)(VOID);          /* Immediate uncondit abort the transfer */
                               /* (and don't bother to call contin() again) */
                        /*--- boundary of old ftfpsp structure (see FTFXTD) */
                                          /* Handle array of incoming bytes */
     INT (*hdlinb)(CHAR *bytes,USHORT nbytes);
                                        /* NOTE:  for upward compatibility, */
                     /* hdlinb() shall only be called if FTFXTD && !FTFASC. */
                 /* Use ftfinb() to resolve this (again only when !FTFASC). */
     CHAR *secur;       /* app-specific security of some kind (FTFXTD only) */
     CHAR spare[16];              /* spare space (only available if FTFXTD) */
};
    /* note: ftfpsp, ftfscb, & ftfomt are global to almost all entry points */


#if 0

Compatibility issues -- introduction of the hdlinb() entry point in 8/93:

     Old applications call the hdlinc() entry point for each incoming byte
          during binary transfers.
     Old protocols will have only a hdlinc() entry point and FTFXTD will be
          clear.

     New applications may call ftfinb() with each BLOCK of incoming bytes
          during binary transfers.  This will work with both new protocols
          and old protocols.
     New protocols may define a hdlinb() routine, set the FTFXTD flag,
          and specify ftfinc() as their hdlinc() routine.

     (There's no need to use ftfinbc() until/unless spare[] is used.)

#endif                             /* if 0                                 */

WGSEXPV(struct ftfpsp*) ftfpsp;    /* global input to all entry/exit routines*/
WGSEXPV(struct ftfpsp*) fthead;    /* addr of 1st entry in prot list       */
WGSEXPV(struct ftfpsp*) fttail;    /* addr of last entry in prot list      */

/*--- File Transfer Protocol Capability and Characteristic Flags ---*/

#define FTFXMT 0x01                   /* Transmit protocol (versus receive) */
#define FTFASC 0x02                /* ASCII-session (versus binary-session) */
                                  /* where '\r' is the sole line terminator */
                               /* note: ASCII sessions do not detect errors */
#define FTFMUL 0x04                           /* capable of multiple files? */
#define FTF7BT 0x08                    /* capable of using 7-bit data path? */
#define FTFASF 0x10                      /* ASCII-file (versus binary-file) */
                                  /* where '\n' is the sole line terminator */
/*             0x20                                              (reserved) */
#define FTFAFN 0x40               /* abort is final, don't ask "try again?" */
#define FTFXTD 0x80          /* extended ftfpsp structure (flags2 & hdlinb) */

 /* Note, FTFASC refers to the session, not the file.  For example, the 'V' */
 /* protocol uses an ASCII session (text output) even though it works on    */
 /* archive files.                                                          */

/*--- Session Control Block:  for maintaining each file transfer session ---*/

struct ftfscb {                                 /* fields for external use: */
     CHAR fname[8+1+3+1];                             /* protocol file name */
     CHAR isopen;                                    /* 1=file is open 0=no */
     USHORT dosdat;                      /* DOS-style date YYYYYYYMMMMDDDDD */
     USHORT dostim;                      /* DOS-style time HHHHHMMMMMMSSSSS */
     LONG unxtim;            /* Unix-style time in seconds since 1/1/70 GMT */
     LONG estbyt;                        /* estimated size of file in bytes */
     LONG actbyt;       /* actual file bytes transferred & ACK'd, this file */
     LONG maxbyt;                   /* size limit imposed on received files */
     LONG actpak;     /* actual file packets transferred & ACK'd, this file */
     LONG acttck;         /* ticks (secs*16) so far, transferring this file */
     LONG garbag;                  /* gen'l (garbage) error count, per file */
     LONG tmouts;                                /* timeout count, per file */
     LONG retrys;                                      /* retries, per file */
     USHORT stecnt;        /* short-term error count (since last good byte) */
     LONG window;      /* max window size (packets or bytes as appropriate) */
     USHORT paksiz;                          /* actual packet size in bytes */
     USHORT tryfil;              /* files we tried to transfer this session */
     USHORT actfil;                /* actual files transferred this session */

                            /* Fields for internal use & external snooping: */
     INT state;               /* internal sub-state code (0=dead, -1=abort) */
     USHORT tckbyt;                   /* ticker when last byte was received */
     USHORT tckstt;               /* ticker when transition to latest state */
     USHORT tckfil;                              /* ticker at start of file */
     USHORT tckact;         /* ticker when last activity (progress) in xfer */
     CHAR *abwhy;                 /* abort reason (or other ad hoc message) */

         /* (many protocol-specific internal fields are expected to follow) */
};

               /* global input to all entry/exit routines, except initze() */
WGSEXPV(struct ftfscb*) ftfscb;

WGSEXPV(INT) scbmax;            /* size of biggest scb (over all protocols) */

/*--- common values for the state field ---*/
#define FTFABORT  -1                 /* state to initiate abort of transfer */
#define FTFABWAIT -2                  /* waiting period for abort to settle */
                                  /* (all states > 0 are protocol-specific) */

/*--- EXIT POINTS:  routines & vars defined by operating system, called  ---*/
/*--- via the protocol's entry points.  (ftfpsp, ftfscb, & ftfomt are    ---*/
/*--- implicit inputs, and global to all of the exit point routines.)    ---*/
/*--- These routines and variables are defined OUTSIDE the FTF code.     ---*/

VOID
ftfout(           /* Transmit binary bytes (used during non-ASCII sessions) */
CHAR *data,
INT nbytes);

VOID
ftfous(               /* Transmit ASCII string (used during ASCII sessions) */
CHAR *string);                                     /* NUL-terminated string */

INT
ftfoba(VOID);                   /* Output buffer bytes available, how many? */

VOID
ftfcli(VOID);                                         /* Clear input buffer */

VOID
ftfclo(VOID);                                        /* Clear output buffer */

INT
ftfxop(VOID);                     /* Open file for reading and transmitting */
             /* implicit outputs: ftfscb->fname,dosdat,dostim,unxtim,estbyt */
                                  /* returns 0=ok & opened, 1=no more files */
      /* ftfxcl() will be called exactly once for each ftfxop() returning 0 */
           /* multi-file protocol sessions will keep calling ftfxop() until */
                                             /* you make it return non-zero */

VOID
ftfxsk(                     /* Seek a position in the file for transmission */
LONG pos);

INT
ftfxrd(                            /* Read bytes from file for transmitting */
CHAR *datbuf,                                              /* put them here */
INT nbytes);                                 /* try to read up to this many */
                /* returns how many actually read, or 0=EOF, maybe -1=error */
               /* will usually return == nbytes, will never return > nbytes */
                           /* if 0 < return value < nbytes, EOF is imminent */
       /* after returning 0, must always return 0 until ftfxcl() & ftfxop() */

INT
ftfxrl(                  /* Read a line from an ASCII file for transmitting */
CHAR *datbuf,              /* where to put the bytes and the NUL terminator */
INT nbytes);                                 /* room for line, incl the NUL */
     /* returns how many actually read, not incl NUL, or 0=EOF, or -1=ERROR */

INT
ftfxrb(VOID);                     /* Read 1 byte from file for transmitting */
                       /* returns EOF if no more in file, or character read */
   /* after returning EOF, must always return EOF until ftfxcl() & ftfxop() */

VOID
ftfxlk(                                                      /* lock output */
INT on);                       /* 1=locked (paused) 0=unlocked (proceeding) */

VOID
ftfxsq(                     /* report that a file will be gracfully skipped */
CHAR *reason);       /* reason skipped (must copy, if not used right away) */

VOID
ftfxcl(                                    /* Close file after transmitting */
INT ok);                 /* 1=transmitted in entirety, 0=skipped or aborted */
         /* implicit inputs: fname,dat&tim fields,estbyt,actbyt from ftfscb */

INT
ftfrex(VOID);                /* check if file to be received exists already */
       /* returns 0=doesn't exist, or we don't know/care & can overwrite it */
  /* returns 1=file exists, overwrite it unless protocol options say not to */
           /* returns 2=file fragment exists, resume it if protocol capable */
                 /* if returns non-zero, also must set these ftfscb fields: */
                  /* unxtim,dosdat,dostim,estbyt (to reflect existing file) */
                                           /* implicit input: ftfscb->fname */
                   /* ok to change name in ftfscb->fname to aVOID collision */
        /* ZMODEM will use time & size fields to handle skip/noskip options */

INT
ftfrop(                              /* Open file for reception and writing */
INT append,                             /* if exists, 1=append, 0=overwrite */
INT ascii,                                             /* 1=ascii, 0=binary */
INT resume);                                    /* 1=resume, 0=from scratch */
                                   /* implicit inputs: ftfscb->fname,estbyt */
/* input file time&date option 1: ftfscb->unxtim (ftfscb->dosdat,dostim==0) */
/* input file time&date option 2: ftfscb->dosdat,dostim (ftfscb->unxtim==0) */
/* input file time&date option 3: none (ftfscb->unxtim,dosdat,dostim == 0)  */
    /* FTF may choose any one of these 3 options, depending on the protocol */
                                                   /* returns 0=ok, 1=abort */
                      /* if returns nonzero, points ftfscb->abwhy to reason */
      /* ftfrcl() will be called exactly once for each ftfrop() returning 0 */
     /* multi-file protocol sessions may call ftfrop() as many times as the */
                                /* sender sends another file in the session */

INT
ftfrwr(                                   /* Write received bytes into file */
CHAR *data,
INT nbytes);
                   /* returns # bytes written (retval == -1 on write error, */
                           /* otherwise retval != nbytes implies disk full) */


INT
ftfrwb(CHAR ch);                         /* Write 1 received byte into file */
                                                    /* returns 1=good 0=bad */
VOID
ftfrsk(           /* Seek a position in the file for receiving & writing to */
LONG pos);                                           /* (needed for resume) */

INT
ftfrrd(         /* Read bytes from file before receiving & overwriting them */
CHAR *datbuf,                                              /* put them here */
INT nbytes);                                       /* try to read this many */
                   /* returns how many actually read, or 0=EOF, or -1=error */
                           /* (needed for last-sector verify before resume) */

VOID
ftfrsq(                     /* report that a file will be gracfully skipped */
CHAR *reason);        /* reason skipped (must copy, if not used right away) */

VOID
ftfrcl(                                       /* Close file after receiving */
INT ok);                               /* 1=received in entirety, 0=aborted */
                            /* implicit inputs: ftfscb->fname,estbyt,actbyt */
 /* also input are time&date in one of the optional formats as for ftfrop() */
    /* application can decide whether ASCII files should have ^Z terminator */

    /* If the ftfrcl() exit point is invoked via the ftfscb->contin() entry */
    /* point, then that iteration of ftfscb->contin() should return 1       */
    /* (continue).  This allows the application to steal processing away    */
    /* from FTF for a few cycles while it processes the received file       */

WGSEXPV(USHORT) ftftck;    /* free-running 65K-wrapping tick counter (16Hz) */
WGSEXPV(INT) ftfomt;               /* transmitter output buffer size, EXACT */
                                      /* (global input to all entry points) */

WGSEXPV(CHAR*) ftfbuf;                /* temporary (very short-term) buffer */
WGSEXPV(INT) fbleng;                          /* length of temporary buffer */
                 /* ftfbuf[] is used only within each single contin() cycle */
            /* fbleng is started at 0 and increased by any initze() routine */

WGSEXPV(CHAR) ftfact;    /* 1=cont() cycle produced some action 0=quiescent */
     /* protocols should set whenever some progress is made in the transfer */
/* application may wish to handle consistent (ftfact == 0)'s in some manner */

/*

Note:

     For every call to ftfxop() that returns 0=ok, exactly one call to
     ftfxcl() is sure to follow, as long as you call contin() until it
     returns 0 or -1, or you call the abort() entry point.  Same for
     ftfrop()/ftfrcl().

*/


/*--- File transfer utilities, in FTF.C ---*/

VOID
ftplog(                              /* log in a new protocol specification */
struct ftfpsp *ftp);                             /* put it after all others */

VOID
ftplogh(                             /* log in a new protocol specification */
struct ftfpsp *ftp);                            /* put it BEFORE all others */

VOID
ftfnew(            /* transition to a new sub-state of the transfer session */
INT nstate);

VOID
ftfahd(                    /* transit to a new sub-state & quickly time out */
INT nstate,
INT ticks);                               /* set times BEHIND by this much! */

VOID
ftfstf(VOID);                           /* start file counters from scratch */

VOID
ftfsrt(VOID);                          /* start a(nother) transmitable file */

VOID
ftfnwp(VOID);                                        /* new packet received */

VOID
ftfabt(                                /* abort transfer session (hi level) */
CHAR *why);                              /* explanation (complete sentence) */

VOID
ftfcan(VOID);         /* Cancel file transfer, send ^X's to the other party */

VOID
ftfrca(VOID);                             /* Make sure ftfrcl() gets called */

VOID
ftfxca(VOID);                             /* Make sure ftfxcl() gets called */

INT
ftfcbl(VOID);           /* check byte-limit during receive, 1=ok, 0=aborted */

VOID
ftfinc(                  /* does protocol's hdlinc() work by using hdlinb() */
CHAR c);                            /* This is a handy hdlinc() entry point */
                        /* for new protocols to work with old applications. */

short
ftfinbc(                 /* does protocol's hdlinb() work by using hdlinc() */
CHAR *bytes,                        /* This is a handy hdlinb() entry point */
UINT nbytes);          /* for old protocol code to use the FTFXTD structure */
       /* (warning! an ftfpsp should never use BOTH ftfinc() and ftfinbc()) */

INT
ftfinb(          /* for application to handle a block of binary input bytes */
CHAR *bytes,  /* (allows new applications to work with old & new protocols) */
UINT nbytes);                                        /* (see also ftfcib()) */

VOID
ftfcib(VOID);      /* application clear input bytes coming in thru ftfinb() */
                                      /* If your application uses ftfinb(), */
                                /* then your ftfcli() should call ftfcib(). */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __FTF_H
