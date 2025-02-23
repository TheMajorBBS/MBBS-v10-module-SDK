/***************************************************************************
 *                                                                         *
 *   FSD.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.      All Rights Reserved.   *
 *                                                                         *
 *   Full-Screen Data Entry header file                                    *
 *                                                                         *
 *   With operating-system-specific functions removed (I/O, memory)        *
 *   the pure display/entry algorithm can be isolated.                     *
 *                                                                         *
 *                                             - R. Stein  11/9/91         *
 *                                                                         *
 ***************************************************************************/

#ifndef __FSD_H
#define __FSD_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "ain.h"

/* Requires printf() & related routines from GCOMM.LIB (Worldgroup)    */
/* Actually, requires Stein's PFWIN.ASM that has a public _curatr &    */
/* allows ANSI condition to be saved using ANSAVE bytes from _curatr...*/

#if 0

Field Specification Strings tell FSD the names of the fields and special
options, if any.  Answer strings encode results of data entry, as well as the
defaults.  Templates tell FSD where and when to display fields, how wide they
are, and what type they are.

Field Specifications and Templates are relatively static.  For a certain data
entry session you could use one Field Specification and then one Template for
ANSI users and one for non-ANSI users.


Still Under Construction
------------------------

  o  Hinging via the field specs:  HINGE <field name>=<value>,<value>,<value>
                                   HINGE <field name>#<value>,<value>,<value>

          (You can do it now anyway, via the fldvfy() routine and the
          FFFAVD field flag)

  o  Help messages via the field specs:  HELP=<message>
          (now accomodates only error messages)

  o  Typeahead buffer after field entry
          (fsdpci() and fsdpch() are empty)

These features are not yet operational but you may find code fragments for
them lying here and there...


Field Specification String
--------------------------

     <field spec> <white> <field spec> <white> <field spec> ...

<field spec>

     <field name>

     or

     <field name> ( <field opt> <white> <field opt> <white> <field opt> ... )

<field opt>

     MIN=<value>                        (number or string, as appropriate)
     MAX=<value>
     ALT=<value>
     MULTICHOICE                        (allows only ALT= values)
     SECRET                             (echo's '*'s to hide entry)
     NOSPACES                           (don't allow entry of spaces)

     Note, don't split up a <field opt> across lines (you can split
     up a <field spec> across lines)

<field name>

     1 to 12 upper case letters or numbers

     avoid reserved words:  MIN MAX ALT MULTICHOICE SECRET NOSPACES HELP HINGE

<white>

     one or more white space
     characters in any order:  ' '  '\r'  '\n'  '\t'  '\f'  etc.

<value>

     0 to 80 printable characters, not including:  = (equals)
                                               nor # (pound)
                                               nor , (comma)
                                               nor ( (parenthesis)
                                               nor )
                                               nor   (blank)

<message>

     0 to 80 printable characters, not including:  = (equals)
                                               nor ( (parenthesis)
                                               nor )
     (embedded blanks are OK though -- must be last option in field spec)


Example Field Specifications String:

     NAME
     RANK(ALT=CAPTAIN ALT=MAJOR)
     SERIALNO(MIN=1000 MAX=6999)
     DISCHARGED


Answer String
-------------

     <answer> NUL <answer> NUL <answer> NUL <answer> ... <answer> NUL NUL

     (fields not represented in an answer string are assumed to be blank)

<answer>

     <field name>=<avalue>

     Note, don't split up an <answer> across lines (you can split an
     <answer string> across lines)

<avalue>

     0 to 80 printable characters, anything from 0x20 to 0xFF

NUL = the ASCII '\0' character

Example Answer String:

     "NAME=Fred W. Friendly\0RANK=MAJOR\0SERIALNO=2609\0DISCHARGED=YES\0"


Template
--------

     <supporting text> <field template> <supporting text> <field template> ...

<supporting text>

     Any characters 01 hex to FF hex except these:  ?  #  $  !  ~

     Lines in the template supporting text must be terminated with "\r\n"
     for entry sessions (not necessarily required for display though).

<field template>

     ?????....             Alphanumeric entry (you may embed punctuation, but
                           not spaces), left justified

                           or multiple choice

     #####....             Digital data (you may embed punctuation, but not
                           spaces), left justified

     $$$$$....             Number (decimal), right justified blank filled
                           32-bit range -2147483648 to 2147483647
                           recommended:   -99999999 to 9999999999 (9 digits)

     !!!!!....             Space for error message, if any, minimum 40 chars

     Y/N                   Yes or No (this field should NOT have field options)

Example Template:

     Name: ??????????????????????????????
     Rank: ???????  (hit spacebar to toggle)
     Serial Number:  ####  (1000 to 5999)
     Discharged:  Y/N



Field Separation and Embedded Punctuation
-----------------------------------------
Spaces need not surround the field templates, but spaces do mean something in
one obscure case.  To support embedded punctuation, wherever the first field
template character (? #) of a field template is found, then subsequent field
template characters that are the same are deemed part of the same field
unless some kind of white space intervenes.  You crave examples, right?

     A: ##### B:#####           that's two digital fields, 5 digits each
     ##-##-##                   that's one 6-digit field with embedded puncts
     (###) ###-####             that's two fields, 3-digit and 7-digit
     (###)###-####              one 10-digit field (got it?)

Note:  ANSI commands do not count as white space.

Trick:  to make "(###) ###-####" into one field instead of two, simply put an
ANSI code for right-1 after the ")".  Or embed a <255> character, if you're
sure this will be used on an IBM screen.

Note:  fields cannot be butted up against each other, as in:  "####????", use
"#### ????" instead.  Need room for cursor anyway.


Minimum field width = 2 characters
----------------------------------
That means that any $ or # or ? that appear isolated in the template string is
taken as a literal.  Any subfield (as in ###/###-####) must also be at least 2
characters long.  So ###-#-### will be taken as a six-character numeric field
with an embedded "-#-".


Alternate Values, a few Precautions
-----------------------------------
Be sure not to encode one alternate value as a substring of another, as in
"ALT=NO ALT=NOSALE", which will never allow "NO" to be randomly chosen.  The
exception is that "ALT=" may always be used to indicate a blank answer, even
though you COULD argue that this is a substring of all strings.  Also, never
duplicate alternate values:  for example, "ALT=FROG ALT=FROG" will never allow
"FROG" randomly.

Be sure not to use alternate values that are too long (say over 40 chars) in
ASCII mode, as overflow of the quick output buffer is then possible.


Other languages
---------------
You can use other letters than Y or N for yes or no.  For example to support
"oui" or "non" in French, use "???" in the template, and in the field specs
use "(ALT=NON ALT=OUI MULTICHOICE)".  To support something like "O/N" in the
template, simply preprocess and translate it along with the corresponding
field specs.


Notes to Programmers
--------------------
FSD is fundamentally limited to a 99 by 99 screen, due to the formatting
capability in ibm2ans() and qotnum().

#endif                             /* if 0                                 */

#define ANSLEN 80                           /* Maximum length of any answer */
#define EXTHED 20                     /* Extra type-ahead bytes in typahd[] */
#define FLDNAM 12                         /* maximum length of a field name */
#define GTOLEN (2+2+1+2+1)    /* 8 = max length of ANSI cursor-goto command */
#define MINHLP 40                /* recommended minimum width of help field */
#define MAXHLP 80                           /* maximum length of help field */
#define ANSILN 25              /* maximum number of lines on an ANSI screen */
#define ANSIWD 80            /* maximum number of columns on an ANSI screen */

struct fsdfld {      /* FSD internal field information structure, per field */

          /*--- Fields computed by fsdppc() (fsdent(),etc. don't change) ---*/
     CHAR ansgto[GTOLEN+1];            /* ANSI command to go to field start */
     CHAR width;              /* max chars in this answer (width <= ANSLEN) */
     CHAR xwidth;  /* width incl embedded punct (xwidth <= ANSLEN) (nec???) */
     CHAR attr;             /* display attribute (when cursor not on field) */
     CHAR flags;                                               /* see below */
     CHAR fldtyp;                                    /* field type: ? $ # Y */
     INT fspoff;     /* offset of field name in field specifications string */
     INT tmpoff;        /* offset of first char of field in template string */
     INT mbpoff; /* offset field template in mbpunc array (or -1=no mbpunc) */

      /*--- Fields initialized by fsdans(), and updated by fsdent(),etc. ---*/
     INT ansoff;       /* offset of answer (after '=') in new answer string */
     CHAR anslen;                      /* length of answer in answer string */
};                                                       /* (23 bytes long) */

/*--- fsdfld flags ---*/
#define FFFMCH 0x01                                /* multiple choice field */
#define FFFALT 0x02            /* field hast at least some alternate values */
#define FFFMMX 0x04            /* field has a min and/or max in field specs */
#define FFFNSP 0x08                         /* field does not accept spaces */
#define FFFCHG 0x10                       /* field has changed this session */
#define FFFNNG 0x20                          /* no negative numbers allowed */
#define FFFSEC 0x40                       /* field entry needs to be secret */
#define FFFAVD 0x80            /* fields to "avoid" during entry or display */

struct fsdscb {             /* Full-Screen Data Entry Session Control Block */

                         /*--- Fields to prepare before calling fsdppc() ---*/
     CHAR *fldspc;              /* Field Specifications String (see Note 1) */
     struct fsdfld *flddat; /* room for fsdppc() to put array of field info */
     CHAR *mbpunc; /* room for fsdppc() to put embedded punctuation templts */

               /*--- Additional field to prepare before calling fsdans() ---*/
     CHAR *newans;          /* room for fsdans(), etc. to put answer output */

      /*--- Additional field to prepare before calling fsdent()/fsdlin() ---*/
     INT (*fldvfy)(                        /* field verify routine, or NULL */
          INT fldno,                               /* field number 0 to N-1 */
          CHAR *answer);                    /* proposed answer (see Note 2) */
              /*--- Additional fields to prepare before calling fsdent() ---*/
     CHAR crsatr;                       /* attribute for field cursor is on */

                                         /*--- Fields output by fsdppc() ---*/
     INT numfld;                          /* number of fields in field spec */
     INT numtpl;         /* number of fields in template (numtpl <= numfld) */
     INT mbleng;      /* actual length of mbpunc array, in bytes, incl NULs */
     INT maxans;     /* max possible length of answer string (not incl NUL) */
     CHAR hlplen;               /* help field length, or 0 if no help field */
     CHAR hlpgto[GTOLEN+1];                  /* help field position command */
     CHAR hlpatr;                                   /* help field attribute */
     INT hlpoff;                           /* help field offset in template */

                      /*--- Field output by fsdans(), updated internally ---*/
     INT allans;           /* actual length of entire current answer string */

     /*--- Internally init & used by fsdent(),fsdlin(),fsdinc(),fsdprc() ---*/
     CHAR state;                              /* see FSD state codes, below */
     CHAR ansbuf[ANSLEN+1];                  /* current answer (see Note 3) */
     CHAR anslen;              /* length of current answer + buffered chars */
     CHAR ansptr;                /* cursor position in current answer field */
     CHAR typahd[EXTHED];                 /* type-ahead buffer (see Note 4) */
     CHAR ahdptr;              /* # bytes stuffed into typahd[] by fsdinc() */
     CHAR hdlahd;              /* # bytes in typahd[] processed by fsdprc() */
     CHAR entfld;    /* index of field just entered (when state --> FSDBUF) */
     CHAR crsfld;            /* fsdinc()'s idea of the current cursor field */
     CHAR shffld;            /* shuffled field, see cursor shuffling, below */
     CHAR *ftmptr; /* pointer into field template of current (entfld) field */
     CHAR flags;                                               /* see below */
     CHAR *altptr;                /* keeps track of multiple choice options */
     INT xitkey;                  /* keystroke that initiated exit of field */
     CHAR chgcnt;                        /* count of changes during session */
     CHAR maxy;                /* maximum "Y" coordinate of session/display */
};

/*--- FSD state codes ---*/

#define FSDAPT 0                              /* beginning, ANSI point mode */
#define FSDAEN 1                               /* entering stuff, ANSI mode */
#define FSDNPT 2                                     /* Non-ANSI point mode */
#define FSDNEN 3                                     /* Non-ANSI entry mode */
#define FSDBUF 4                   /* entry ready, buffering new keystrokes */
#define FSDSTB 5         /* entry processed, but still buffering keystrokes */
#define FSDKHP 6               /* need to wipe out help message (ANSI only) */
#define FSDSAV 7                    /* exit fsd entry session, save answers */
#define FSDQIT 8                    /* exit fsd entry session, toss answers */

        /* during FSDAPT,FSDAEN,FSDNPT,FSDNEN fsdinc() controls output path */
        /* but during FSDBUF and FSDSTB, fsdprc() has control of the output */

 #if 0

Note 1:  The Field Specifications String determines just how many fields there
         are in the data entry session.  This is computed by fsdppc() and
         stored in fsdscb->numfld.

         The Template may have fewer fields than the Field Specifications
         String.  In that case, fields in the Field Specifications String
         but not in the Template will always have 0-length answers.

Note 2:  fldvfy() routine return values:

   VFYOK    accept this field entry (don't check min/max/etc.)
            You may change the answer string IN PLACE, even increasing its
            length up to ANSLEN characters.

   VFYCHK   check field's type, min, max before accepting this entry
            (will beep if invalid and almmmx: fsdouc('\7'))

   VFYREJ   reject entry, revert to old answer and make him enter this field
            over again (do your own beeping if you want: fsdouc('\7'))

   VFYDEF   revert to old answer and move on to next field

     The fldvfy() routine can count on implicit inputs: fsdscb, fldptr

     To end and entry session the field verify routine, or standard FSD
     code, sets fsdscb->state to FSDSAV (to save) or FSDQIT (to abort).


Note 3:  ansbuf[] contains the current answer being entered in the FSDAEN
         state.  A '\0' terminator is always maintained.  anslen is the
         number of characters in ansbuf[] (excl '\0'), and ansptr is the
         character cursor position (0 to N-1).  In FSDBUF state, ansbuf[]
         is ready for handling by the mainline fsdprc(), and entfld
         identifies the field number it applies to

Note 4:  In FSDBUF state, typahd[] contains the sequence of keystrokes typed
         in AFTER switching to the FSDBUF state.  ahdptr is the number of
         bytes stored there by fsdinc().  These bytes are NOT '\0' terminated.
         They are either 1-byte ASCII codes, or 2-byte scan codes (0 &
         scancode, ala getchc()).  After handling ansbuf[] (state FSDBUF),
         fsdprc() tries to catch up (state FSDSTB).  The hdlahd index tracks
         this catching up, possibly even while fsdinc() is stuffing more bytes
         into typahd[].

         Type ahead keystrokes wind up being either 0xNN00 or 0x00NN,
         when handled by fsdpci() and fsdpch().

#endif                             /* if 0                                 */

#define VFYOK  -1                            /* field entry is OK, store it */
#define VFYCHK -2                  /* OK as long as MIN, MAX, ALT check out */
#define VFYREJ -3                       /* field entry is rejected, reenter */
#define VFYDEF -4        /* ignore: revert to default field entry & move on */

/*--- fsdscb flags ---*/

#define FSDQOT 0x01        /* major fsdinc()-induced output has taken place */
                                  /* and we're not yet sure it all went out */
#define FSDSHN 0x02      /* cursor shuffle NOT sent, need to shuffle cursor */
#define FSDANT 0x04                      /* Alternate value entry has begun */
#define FSDALT 0x08                              /* Alternate value entered */
#define FSDANS 0x10                         /* ANSI supported this session? */
#define FSDIGA 0x20                      /* ignore answer, just move cursor */

/*

Note:  Cursor shuffling refers to the ANSI stream that repositions the field
cursor.  When the cursor is moved from field A to field B, you need to "turn
off" field A (display field A contents in the native display attribute), "turn
on" field B (display field B contents in cursor display attribute), and
position the cursor at the start of field B.  This heavy stream must not
overflow the quick output buffer (e.g. "echo buffer" for the GSBL's chious()).

*/

/*--- GLOBAL VARIABLES (set and/or used by FSD.C and/or application) ---*/
WGSEXPV(struct fsdscb*) fsdscb;            /* Global ptr to current FSD SCB */
                   /* Note, if fsdinc() or fsdqoe() are interrupt routines, */
     /* then you must PRESERVE fsdscb before setting it for their purposes. */
WGSEXPV(INT) fsdbln;        /* length of fsdbuf-referenced temporary buffer */
                      /* fsdbuf[] is used only within each call to fsdppc() */
                                                    /* (output by fsdini()) */
WGSEXPV(CHAR) fsdemg[];       /* error message for fsdppc(), fsdprc(), etc. */
WGSEXPV(CHAR*) xannam;                   /* global return value of fsdxan() */
                  /* if fsdxan() found an answer, xannam points to its name */
                 /* otherwise, xannam points to final '\0' of answer string */

WGSEXPV(struct fsdfld*) fldptr;             /* global pointer to field info */
                      /* used locally by many routines & their subordinates */
                  /* Note, fsdinc() and fsdqoe() will preserve and restore, */
                                    /* in case they are interrupt routines. */

/*--- OPTION VARIABLES (defaults in FSD.C, may be changed by application) --*/
WGSEXPV(INT) almmmx;                /* sound alarm for min/max violations?  */
WGSEXPV(INT) udwrap;         /* should cursor up/down arrow wrap at limits? */
WGSEXPV(CHAR) secchr;       /* character to echo when typing "secret" field */
WGSEXPV(INT) maxfld;     /* max # of fields allowed (use to limit fsdppc()) */
                               /* (initial value here is arbitrarily large) */

/*--- EXIT VARIABLES (ref'd in FSD.C, must be defined in application) ---*/
WGSEXPV(CHAR*) fsdbuf;     /* temp (non-retained) buffer, fsdbln bytes long */
             /* defined and allocated by application after calling fsdini() */
WGSEXPV(INT) fsdomt;               /* transmitter output buffer size, EXACT */
                               /* (global var used by fsdprc() entry point) */
             /* If unlimited output buffer, make fsdomt large (e.g. 32000), */
                         /* and have fsdoba() always return EXACTLY fsdomt. */

/*--- ENTRY POINTS (routines in FSD.C that are called by application) ---*/

WGSEXP VOID
fsdini(VOID);          /* power-up init for Full Screen Data Entry software */
                                                         /* computes fsdbln */

WGSEXP INT
fsdppc(               /* preprocess field information, in prep for fsdent() */
CHAR *templt,                                            /* template string */
INT ascn);             /* 1=scan in preparation for ANSI session (fsdent()) */
                                 /* 0=only fsddsp() or fsdlin() will follow */
                /* implicit input:  fsdscb  points to session control block */
       /* Must call at least once for each new scb & template & field spec. */
              /* You may call immediately before calling fsdent()/fsdlin(), */
             /* or for slightly better compute efficiency, you may call way */
                  /* ahead of time for a given scb & template & field spec, */
                           /* then call fldent() multiple times on the same */
             /* fsdscb, fsdscb->fldspc, fsdscb->flddat, and fsdscb->mbpunc. */
        /* note: fsdppc() will need to write to templt, but it will recover */
  /* any changes that it makes (sticking in '\0's for efficient printf()'s) */
                                    /* see also implicit inputs to fsdent() */
            /* only output:  fsdscb->flddat, fsdscb->mbpunc, fsdscb->numfld */
   /* YOU MUST CALL fsdppc() AT SOME POINT B4 YOU CALL fsddsp() or fsdent() */
                                    /* returns number of errors encountered */

WGSEXP VOID
fsdans(             /* Install answer string & compute ansoff,anslen fields */
CHAR *oldans);                        /* answer string, or "" for all blank */
                           /* call in prep for fsddsp() or fsdent() session */
                        /* if duplicate answer, earlier answer will prevail */
                                                   /* fsdscb implicit input */

WGSEXP VOID
fsddsp(                                /* Display screen & filled-in fields */
CHAR *templt);                      /* original template passed to fsdppc() */
                      /* expects fsdscb->flddat to contain field info, etc. */
     /* basically, requires that fsdppc() & fsdans() have been done already */
                                /* expects no intervening calls to fsdinc() */
                    /* may corrupt template (wiping out help field symbols) */

WGSEXP VOID
fsdent(                 /* begin Full Screen Data Entry session (ANSI only) */
INT inifld);                                     /* initial field, 0 to N-1 */
                     /* implicit input:  fsdscb  global var tells it all... */
     /* Before fsdent(): set fsdscb->newans to point to a big enough buffer */
             /* for the output answer string & call fsdans() with defaults. */
       /* (Big enough means fsdscb->maxans bytes, as reported by fsdppc().) */
            /* Set fsdscb->fldspc to point to a field specifications string */
                                    /* with at least a list of field names. */
       /* Set fsdscb->fldvfy to NULL or to point to a field verify routine. */
         /* Set fsdscb->flddat to point to allocated memory for an array of */
    /* fsdfld structures one per field (no need to initialize this memory). */
           /* YOU MUST CALL fsdppc() AT SOME POINT BEFORE YOU CALL fsdent() */
                 /* Set fsdscb->crsatr to attribute for field cursor is on. */

WGSEXP VOID
fsdlin(VOID);           /* begin data entry for non-ANSI (ASCII-only) users */

WGSEXP INT
fsdprc(VOID);      /* Process (entry or display) until done (ANSI or ASCII) */
                    /* returns 0=continue processing 1=save & exit -1=abort */
   /* note, if fsdprc() does not call fsdnfy(), it does no output that pass */
                              /* also, non-zero return codes have no output */

WGSEXP VOID
fsdinc(                            /* Handle Incoming character (ANSI-only) */
INT c);                                      /* keystroke code, ala GCOMM.H */
                                             /* may be called via interrupt */
                             /* basically same inputs & outputs as fsdent() */
WGSEXP VOID
fsdqoe(VOID);      /* Report q output buffer has gone empty (ANSI or ASCII) */
            /* Called by application after fsdinc() initiated output when   */
            /* that output is truly out, and (importantly) the quick output */
            /* buffer is completely empty                                   */

      /* If unlimited output buffer, may call fsdqoe() after each fsdinc(). */
/* In any event, DON'T call fsdqoe() from inside your fsdqos() or fsdqot(). */

           /* Note, fsdinc() and fsdqoe() code cannot interrupt one another */
                                   /* (because of FSDQOT and FSDSHN flags). */


/*--- EXIT POINTS (routines called by FSD.C, defined by application) ---*/

WGSEXP VOID
fsdous(CHAR *str);                        /* display a string of characters */
            /* called from a mainline routine: fsdent(), fsdlin(), fsdprc() */
                        /* or from an interrupt routine: fsdinc(), fsdqoe() */
/*
     This routine must be reentrant in the sense that fsdous() calls via
     a mainline routine may get interrupted by an interrupt routine,
     which may itself have calls to fsdous().  Interrupts will not be
     nested.

     The mainline routines must be able to assume that a series of
     strings passed to fsdous() via a single call to a mainline routine
     will be output in sequence, uninterrupted by any fsdous() calls via
     the interrupt routines.

     The output routines use "\r\n" for end-of-line.
                                                                            */

WGSEXP VOID
fsdouc(CHAR c);      /* display a character (same warnings as for fsdous()) */

WGSEXP INT
fsdoba(VOID);                   /* Output buffer bytes available, how many? */
       /* this routine will be called only from fsdprc(), NOT from fsdinc() */
 /* Say 1 call to fsdprc() generates a call to fsdous() & outputs a string. */
      /* Then if during the next call to fsdprc(), fsdoba() returns fsdomt, */
 /* then FSD must be able to assume that all of the string got out already. */
/* In other words, fsdoba()'s information can't be TOO stale.  On the other */
 /* hand FSD won't assume that fsdous() will IMMEDIATELY decrease fsdoba(). */

WGSEXP VOID
fsdqdp(VOID);         /* low-level initiation of redisplay of entire screen */

WGSEXP VOID
fsdnfy(VOID);                 /* Notify system to call fsdprc() when it can */
                     /* (but it is ok to call fsdprc() all the time anyway) */

WGSEXP CHAR *
fsdrft(VOID);                   /* refresh template (returns pointer to it) */
              /* called only via fsdprc() or fsdlin() (never via interrupt) */
                                 /* context is application's responsibility */
  /* returned copy of template only expected to last until fsdprc() returns */

/*--- VERIFY ROUTINE ---*/

WGSEXP INT
vfyadn(   /* factory-issue field verify routine, for ask-done-at-end scheme */
INT fldno,          /* field number, (fldptr is redundantly also available) */
CHAR *answer);                                           /* proposed answer */
                /* this routine also verifies a random ^Q quit-with-changes */

/*--- ANSWER HANDLING UTILITIES -- Call on any unprocessed answer string ---*/

WGSEXP INT
stranslen(              /* find length of answer string (incl final "\0\0") */
CHAR *anstg);                     /* multi-string answer string (see FSD.H) */

WGSEXP CHAR *
fsdxan(                                /* extract answer from answer string */
CHAR *answer,                                              /* answer string */
CHAR *name);                              /* field name (all caps required) */
                      /* returns extracted string, '\0' terminated if found */
        /* (and sets global xannam to point to field name in answer string) */
  /* otherwise return value and xannam point to final '\0' of answer string */

WGSEXP VOID
fsdpan(                                    /* put answer into answer string */
CHAR *answer,               /* answer string (must have room for new value) */
CHAR *name,                               /* field name (all caps required) */
CHAR *value);                                                  /* new value */

WGSEXP VOID
fsddan(VOID);  /* delete answer just found by fsdxan() fm its answer string */
           /* (this routine has no effect if fsdxan() didn't find anything) */

WGSEXP VOID
fsdbd1(                            /* 1st step to building an answer string */
CHAR *answers);                                          /* where to put it */

WGSEXP VOID
fsdbdn(                           /* next step to building an answer string */
CHAR *name,
CHAR *value);

WGSEXP VOID
fsdbdf(INT fldno);  /* build answer string from field # from recent session */

/*--- ANSWER HANDLING UTILITIES -- Call only after fsdppc() fsdans() ---*/

WGSEXP CHAR *
fldnmi(                         /* extract field name based on field number */
INT fldi);                       /* expects fsdscb as input, after fsdppc() */
               /* call only after fsdans(), or an entry session is complete */

WGSEXP CHAR *
fsdfxt(                      /* extract answer from answer string by number */
INT fldi,                             /* field number 0 to fsdscb->numfld-1 */
CHAR *buffer,                                            /* where to put it */
INT length);                            /* bytes in buffer, incl final '\0' */
               /* call only after fsdans(), or an entry session is complete */

WGSEXP CHAR *
fsdnan(                      /* extract answer from answer string by number */
INT fldi);                            /* field number 0 to fsdscb->numfld-1 */
               /* call only after fsdans(), or an entry session is complete */

WGSEXP INT
fsdsan(                                          /* set answer to new value */
INT fldi,                                            /* answer field number */
CHAR *value);                                                  /* new value */
                                           /* returns 1=changed 0=no change */
               /* call only after fsdans(), or an entry session is complete */

WGSEXP VOID
fsdman(                          /* stuff more answers into current session */
CHAR *ansstg);                             /* answer string full of answers */
               /* call only after fsdans(), or an entry session is complete */

WGSEXP INT
fsdord(  /* returns ordinal value of multiple-choice answer, per field spec */
INT fldi);                            /* field number 0 to fsdscb->numfld-1 */
                 /* if N alternate values, returns 0..N-1 or -1 if no match */
               /* call only after fsdans(), or an entry session is complete */
                                /* only returns 0..N-1 if unequivocal match */
                      /* in that case, answer is available via fsdnan(fldi) */

/*--- OTHER UTILITIES ---*/

WGSEXP VOID
tpwipe(           /* wipe out supporting text surrounding field in template */
CHAR *templt,                                              /* template text */
INT fldi,                                                   /* field number */
INT preitems,       /* 0=ignore 1=blank to preceding EOL/ANSI 2=to next ... */
INT postitems);    /* 0=ignore 1=blank to subsequent EOL/ANSI 2=to next ... */
                                  /* expects fsdscb as prepared by fsdppc() */

WGSEXP VOID
shofld(            /* show this field (goto it, attr, contents) (ANSI only) */
INT attr,                        /* implicit inputs: fsdscb, fldptr, bufptr */
INT justfy);                                         /* see dspans()        */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __FSD_H                              */
