/***************************************************************************
 *                                                                         *
 *   FSDBBS.H                                                              *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.      All Rights Reserved.   *
 *                                                                         *
 *   Full-Screen Data Entry interface for Worldgroup                       *
 *                                                                         *
 *   See also FSD.H for instructions on using FSD                          *
 *                                                                         *
 *                                             - R. Stein  2/12/92         *
 *                                                                         *
 ***************************************************************************/

#ifndef __FSDBBS_H
#define __FSDBBS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "fsd.h"

#if 0

FSD can perform the following functions:

     o   Display data
     o   Enter data, full-screen mode
     o   Enter data, linear mode

     Full-screen entry mode requires ANSI capability and a large enough
     user screen to hold the entire template.

     Data displaying or linear entry can take place whether the user has
     ANSI capability or not.

To use FSD with Worldgroup, you'll need to create these:

     o   Template (in .MSG file)
     o   Field specification string (usu in memory)
     o   Memory for the session's variable-length data structures
     o   Default answer string (usu created on the fly)
     o   Field-verification routine (optional)
     o   When-done routine (process answers, restore state/substate)
     o   Calls to FSDBBS routines

Procedure:

     1.  Create a Template in an .MCV file.  (See FSD.H for template
         format.  FSDBBS will automatically translate to \r\n
         terminators.) You will probably have a different template for
         ANSI users than for non-ANSI users.

     2.  Make a permanent copy of a Field Specification String in memory.
         (See FSD.H for this format also.)

     3.  Find out how much memory to allocate:
                                                  If the template
              Make a call like this:              is for an:

              nbytes=fsdroom(tmpmsg,fldspc,0);    Entry session
              nbytes=fsdroom(tmpmsg,fldspc,-1);   Displaying

         from your init__routine() and identify the above Template and
         Field Specification strings (after openning the appropriate .MCV
         file of course).  This will tell you the size of the region you
         must provide to support data entry or display.  Call fsdroom()
         for all templates/field specification combinations you will be
         using to make sure you'll have enough room for all of them.

     4.  Allocate the space fsdroom() requires.

         (fsdroom() must be called again, immediately before the display
         or entry session.)

     5.  Format your default or original answers into an Answer String
         (FSD.H), or you will be able to use "" to default to all blank.
         The answer string can come from getmsg(), but it cannot be in
         the prfbuf[].  vdatmp is a good candidate, making sure it's big
         enough.  Be sure to use only legal values in your default Answer
         String (per your own Field Specifications String).

     6a. To display data call:

              fsdroom(tmpmsg,fldspc,-1);
              fsdapr(sesbuf,seslen,answers);
              fsddsp(fsdrft());

     6b. To begin a full-screen entry session, call:

              fsdroom(tmpmsg,fldspc,1);
              fsdapr(sesbuf,seslen,answers);
              fsdbkg(fsdrft());
              fsdego(fldvfy,whndun);

     6c. To begin a linear entry session, call:

              fsdroom(tmpmsg,fldspc,0);
              fsdapr(sesbuf,seslen,answers);
              fsdego(fldvfy,whndun);

Notes:

     Fields are numbered 0 to N-1, where N is computed from the field
     specs by fsdroom() and stored in fsdscb->numfld.  The number of
     fields that are also represented in the template is fsdscb->numtpl,
     which usually equals but never exceeds N.  You can't display or
     enter a field outside the range 0 to fsdscb->numtpl-1.

     For entry sessions, you'll need to supply a custom
     field-verification routine (optional) and a when-done routine to
     restore your state code, etc.

     Remember that fsdroom() outputs a bunch of stuff to the prfbuf[].
     This stuff must be untouched between fsdroom() and fsdapr() calls.

     The results of fsdapr() are all in the sesbuf.  This means that
     after calling fsdroom() and fsdapr(), you can call the other
     routines (fsddsp(), fsdrft(), fsdbkg(), fsdego()) any time later and
     in any order as long as you maintain the sesbuf passed to fsdapr().

     If you have any prf'ing you want to show up immediately before the
     entry/display, be sure and do it AFTER the call to fsdapr(), which
     leaves the prfbuf[] empty.

     vdaptr, or a subset of vdaptr, is a good thing to use for sesbuf.

     The whndun routine must restore your usrptr->state and
     usrptr->substt codes, as well as handle the end of the session.
     The global infsdhup variable will be TRUE whenever your whndun
     routine is being called from within the FSD's hangup processing.

     To change the cursor from 0x70 attribute to some other attribute,
     just code fsdscb->crsatr=<whatever> after calling fsdapr().


Avoiding Fields
----------------
If your program needs to conditionally blank out some fields in the display,
you need to (1) modify the template, and (2) flag the appropriate fields as
"avoid".  For (1), use the tpwipe() routine on the results of fsdrft() (before
passed to fsddsp()) to modify the supporting text for the appropriate fields
of the template.  For (2), set the FFFAVD flag for the fields to be avoided
(see FSD.H) after calling fsdapr().

For example, to display all data but blank out field 5 and some of the
supporting text surrounding field 5, you could code something like:

              CHAR *tp;

              fsdroom(tmpmsg,fldspc,0);
              fsdapr(sesbuf,seslen,answers);
              tp=fsdrft();
              tpwipe(tp,5,1,1);
              fsdscb->flddat[5].flags|=FFFAVD;
              fsddsp(tp);

This works almost identically for "avoiding" fields in a full screen entry
mode, except you need to interecept things before fsdbkg() is called (instead
of before fsddsp()).

On the other hand, to show a "protected" field that the user can see but can't
change, the FFFAVD flag should not be set until AFTER fsdbkg() is called (but
before fsdego()), and don't call tpwipe() at all.

In linear entry mode, you just need to set the FFFAVD flag for the appropriate
fields after calling fsdapr().


Getting Answers After a Session
-------------------------------
After an entry session is over there are a few ways to get the answers.
See FSD.H for more details.

     stg=fsdnan(fldno)                  Get a pointer to the '\0'
                                        terminated answer for field fldno.

     fsdfxt(fldno,buffer,maxlength)     Store answer for field fldno into
                                        buffer, making sure that you write
                                        no more than maxlen bytes (incl \0).

     index=fsdord(fldno)                Get the index 0 to N-1 for the N
                                        possible "ALT=" alternate values for
                                        field fldno, in the order defined in
                                        the field specs.  Returns -1 if the
                                        answer was not one of the ALT='s.

Handling Answers at Other Times
-------------------------------
After a session, the data structures allocated by fsdapr() allow quick access
to pieces of the answer string.  But at other times, the following routines
from FSD.C can be used to deal with answer strings (see FSD.H for more
details):

     length=stranslen(answers);         Find length of an answer string,
                                        including the the final double '\0'.

     value=fsdxan(answers,name);        Get the value of a field of an answer
                                        string.  Returns "" if not found.

     fsdpan(answers,name,value);        Put a new value into an answer string.

     fsddan();                          Delete the answer just found by
                                        fsdxan() from that answer string.

Here's an example of creating an answer string from scratch using sprintf():

     sprintf(answers,"NAME=%s%cRANK=%s%cSERIALNO=%s%c,name,'\0',
                                                      rank,'\0',
                                                      serno,'\0');

#endif                             /* if 0                                 */

#define MBPMAX 200     /* maximum size of mbpunc array (subfield templates) */

struct fsdbbs {
     struct fsdscb fsdscb;                                     /* see FSD.H */
     struct ainscb ainscb;         /* ANSI - getchc() conversion, see AIN.H */
     HMCVFILE curmbk;                          /* template setmbk() pointer */
     INT tmpmsg;                                     /* template message ID */
     INT amode;          /* 1=fullscreen mode 0=linear mode -1=display only */
     CHAR flags;                                               /* see below */
     VOID (*whndun)(            /* routine to call when FSD session is over */
          INT save);                                       /* 1=save 0=quit */
};

#define FBRDSP 0x01                     /* Redisplay of whole screen needed */
#define FBFULL 0x02                                     /* full-screen mode */
#define FBSAVE 0x04                                        /* save vs. quit */

WGSEXPV(struct fsdbbs*) fsdusr;              /* above info for current user */

WGSEXPV(GBOOL) infsdhup;    /* are we in the middle of FSD hangup handling? */

WGSEXP VOID
inifsd(VOID);                     /* fsdbbs initializer under Worldgroup    */

WGSEXP VOID
setfsd(INT chan);            /* set fsd context, acc to channel 0..nterms-1 */

WGSEXP INT
fsdroom(
INT tmpmsg,                                      /* .MCV index for template */
CHAR *fldspc,                     /* permanent copy of field spec in memory */
INT amode);               /* 1=full-screen entry, 0=linear entry -1=display */
          /* returns number of bytes session will need, or -1=error in data */
                      /* WARNING:  corrects invalid usrnum, corrupts prfbuf */

WGSEXP VOID
fsdapr(                           /* prepare answers (call after fsdroom()) */
CHAR *sesbuf,                /* region of bytes, size returned by fsdroom() */
INT sbleng,          /* allocated bytes at sesbuf (for error checking only) */
CHAR *answers);              /* default answers (ok if comes from getmsg()) */
             /* expects prfbuf contents exactly as left over from fsdroom() */
                                       /* clears prfbuf[] when done with it */

WGSEXP VOID
fsdbkg(                    /* display background for full-screen entry mode */
CHAR *templt);                                 /* template in raw text form */

WGSEXP VOID
fsdego(         /* begin FSD entry session (call after fsdroom(), fsdapr()) */
INT (*fldvfy)(                             /* field verify routine, or NULL */
     INT fldno,                                    /* field number 0 to N-1 */
     CHAR *answer),                                      /* proposed answer */
VOID (*whndun)(             /* when-done routine (must restore state, etc.) */
     SHORT save));                                         /* 1=save 0=quit */
                                      /* (expects caller to outprf(usrnum)) */

WGSEXP VOID
fsdrhd (CHAR *titl);

INT
infsd(
INT usn,
VOID (*exipnt)());                  /* is user in FSD from here?            */

WGSEXP CHAR
fsdchi(                        /* btuchi() character input  handler for FSD */
INT chan,
INT c);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __FSDBBS_H                           */
