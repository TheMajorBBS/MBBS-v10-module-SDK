/***************************************************************************
 *                                                                         *
 *   TNO.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   General-purpose Telnet option decoding.                               *
 *                                                                         *
 *                                        - RNStein  5/31/94               *
 *                                                                         *
 ***************************************************************************/

#ifndef __TNO_H
#define __TNO_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDTNTD
#       define TNTDEXP          EXPORT
#       define TNTDEXPV(x)      EXPORT_VARIABLE(x)
#       define TNTDEXPF(x, y)   EXPORT_FUNCTION(x, y)
#    else
#       define TNTDEXP          IMPORT
#       define TNTDEXPV(x)      IMPORT_VARIABLE(x)
#       define TNTDEXPF(x, y)   IMPORT_FUNCTION(x, y)
#    endif
#else
#       define TNTDEXP
#       define TNTDEXPV
#       define TNTDEXPF
#endif // GCWINNT

struct TNTDEXP tnoscb {       /* Telnet option decode, Session Control Blk */
     CHAR state;              /* state of Telnet Option handling (below)   */
     CHAR opid;               /* option ID received                        */
     INT (*tnoxit)(           /* Telnet option exit point handler          */
          INT code,           /* see TNCXXXX codes below                   */
          INT parm);          /* see TNCXXXX codes below                   */
     CHAR maxstg;             /* max subneg chars, plus 1 for NUL term     */
     CHAR stgcnt;             /* length of subneg string accumulated       */
     INT flags;               /* app-specific, managed by tnoyes(),tnono() */
     CHAR stg[1];             /* where to put SB..SE string (remaining     */
};                            /* maxstg-1 bytes of stg[] must follow here) */

/*--- TNO state codes ---*/
#define TNOQSC 0              /* quiescent (searching for an IAC)          */
#define TNOIAC 1              /* received IAC                              */
#define TNOWIL WILL           /* received IAC,WILL                         */
#define TNOWNT WONT           /* received IAC,WONT                         */
#define TNODOO DO             /* received IAC,DO                           */
#define TNODNT DONT           /* received IAC,DONT                         */
#define TNOISB SB             /* received IAC,SB                           */
#define TNOISO 7              /* received IAC,SB,OPT,...                   */
#define TNOSOI 8              /* received IAC,SB,OPT,...,IAC (SE expected) */

/*--- TNO exit point handler codes - application handles special events ---*/
#define TNCWIWO WONT          /* received WILL (parm=1) or WONT (parm=0)   */
#define TNCDODO DONT          /* received DO   (parm=1) or DONT (parm=0)   */
#define TNCSBSE 2             /* received IAC SB ... IAC SE bracketed stg  */
#define TNCOTHR 3             /* received some other IAC code (parm=code)  */
#define TNCSEND 4             /* send IAC,parm,tnoscb->opid                */

TNTDEXPV(struct tnoscb*) tnoscb;/* global variable for tnoini() and tnohose()*/

TNTDEXP VOID
tnoini(                       /* initialize Telnet Option session (tnoscb) */
INT maxstg,                   /* max subneg chars, plus 1 for NUL term     */
INT (*tnoxit)(                /* Telnet option exit point handler          */
     int code,                /* see TNCXXXX codes above                   */
     int parm));              /* see TNCXXXX codes above                   */

TNTDEXP INT
tnohose(                      /* Telnet Option byte hose (tnoscb implicit) */
CHAR ch);                     /* incoming character from other NVT party   */
                              /* returns 00-FF character or -1=nothing yet */
                              /* may call your exit point as a side effect */
                              /* Note:  whatever context you need for your */
                              /* exit points, be sure to set up before you */
                              /* call tnohose().                           */

TNTDEXP INT
tnoyes(                            /* prefer YES resp to TNCWIWO or TNCDODO*/
INT mask);                         /* flag mask, application-specific      */
                                   /* returns 1=can, 0=can't               */
                                   /* meaning of app-specific flag bit:    */
                                   /* 1=yes proposed and accepted (either  */
                                   /*   peer proposed and we accepted, or  */
                                   /*   we proposed and peer accepted)     */
                                   /* 0=no (either we proposed and peer    */
                                   /*   denied, or peer refused and we     */
                                   /*   accepted)                          */

TNTDEXP VOID
tnono(                             /* demand NO resp to TNCWIWO or TNCDODO */
INT mask);                         /* 0=ignore WONTs/DONTs, mask=ack first */
                                   /* one only, always rejects WILLs/DOs   */
                                   /* meaning of app-specific flag bit:    */
                                   /* 1=peer has been told no (either we   */
                                   /*   rejected his proposal, or accepted */
                                   /*   peer's refusal)                    */
                                   /* 0=peer hasn't been notified yet of   */
                                   /*   our refusal/denial                 */


#define EOR    0xEF                /* 239 - end of record                  */
#define SE     0xF0                /* 240 - suboption end                  */
#define NOP    0xF1                /* 241 - no operation                   */
#define DM     0xF2                /* 242 - data mark                      */
#define BREAK  0xF3                /* 243 - break                          */
#define IP     0xF4                /* 244 - interrupt process              */
#define AO     0xF5                /* 245 - abort output                   */
#define AYT    0xF6                /* 246 - are you there?                 */
#define EC     0xF7                /* 247 - erase character                */
#define EL     0xF8                /* 248 - erase line                     */
#define GA     0xF9                /* 249 - you may reverse the line       */
#define SB     0xFA                /* 250 - suboption begin                */
#define WILL   0xFB                /* 251 - declare me on                  */
#define WONT   0xFC                /* 252 - declare me off                 */
#define DO     0xFD                /* 253 - command you on                 */
#define DONT   0xFE                /* 254 - command you off                */
#define IAC    0xFF                /* 255 - interpret as command           */

#define TNTCMD_FIRST  EOR
#define TNTCMD_LAST   IAC

#define TNTOPT_BINARY          0   /* transparent                           */
#define TNTOPT_ECHO            1   /* echo                                  */
#define TNTOPT_RCP             2   /* prepare to reconnect                  */
#define TNTOPT_SGA             3   /* suppress go ahead                     */
#define TNTOPT_NAMS            4   /* approximate message size              */
#define TNTOPT_STATUS          5   /* give status                           */
#define TNTOPT_TM              6   /* timing mark                           */
#define TNTOPT_RCTE            7   /* remote controlled transmission & echo */
#define TNTOPT_NAOL            8   /* negotiate about output line width     */
#define TNTOPT_NAOP            9   /* negotiate about output page size      */
#define TNTOPT_NAOCRD         10   /* negotiate about CR disposition        */
#define TNTOPT_NAOHTS         11   /* negotiate about horizontal tabstops   */
#define TNTOPT_NAOHTD         12   /* negotiate about horizontal tab dispos */
#define TNTOPT_NAOFFD         13   /* negotiate about formfeed disposition  */
#define TNTOPT_NAOVTS         14   /* negotiate about vertical tab stops    */
#define TNTOPT_NAOVTD         15   /* negotiate about vertical tab dispos   */
#define TNTOPT_NAOLFD         16   /* negotiate about output LF disposition */
#define TNTOPT_XASCII         17   /* extended ascii character set          */
#define TNTOPT_LOGOUT         18   /* force logout                          */
#define TNTOPT_BM             19   /* byte macro                            */
#define TNTOPT_DET            20   /* data entry terminal                   */
#define TNTOPT_SUPDUP         21   /* supdup protocol                       */
#define TNTOPT_SUPDUPOUTPUT   22   /* supdup output                         */
#define TNTOPT_SNDLOC         23   /* send location                         */
#define TNTOPT_TTYPE          24   /* terminal type                         */
#define TNTOPT_EOR            25   /* end or record                         */
#define TNTOPT_EXOPL         255   /* extended-options-list                 */

#define TNTOPT_FIRST  TNTOPT_BINARY
#define TNTOPT_LAST   TNTOPT_EOR

#define cmdname(ch) ((unsigned int)(ch) < TNTCMD_FIRST  \
                     ? spr("IAC %u",(unsigned int)(ch)) \
                     : tntcmdlist[(unsigned int)(ch)-TNTCMD_FIRST])

#define optname(ch) ((unsigned int)(ch) > TNTOPT_LAST   \
                     ? spr("%u",(unsigned int)(ch))     \
                     : tntoptlist[(unsigned int)(ch)-TNTOPT_FIRST])

TNTDEXPV(CHAR*) tntcmdlist[];      /* command names                        */
TNTDEXPV(CHAR*) tntoptlist[];      /* option names                         */


#if 0

Example preparations and call to tnoini():

     include "gcomm.h"                  ...This is a completely independent API
     include "tno.h"                    ...(application, protocol stack, etc.)
     :
     :
     struct {
          struct tnoscb tnoscb          ...Session control block defined.
          char buffer[20-1];            ...total string buffer size is 20 bytes
     } appscb;
     :
     :
          tnoscb=&tnoapp;               ...Application can detect 18-character
          tnoini(20,appxit);            ...terminal-types, for example.

Example call to tnohose():

     char ch;
     int tch;                           ...tnohose() returns int, not char
     struct tnoscb appscb;
     :
     :
     ch=incoming();                     ...Incoming data, in the context of
     tnoscb=&appscb;                    ...associated session control block,
     if ((tch=tnohose(ch)) >= 0) {      ...is passed thru tnohose().
          process(tch);                 ...If anything comes out, process it
     }                                  ...as a literal character

Skeleton exit point handler:

     int appxit(                        ...Application exit point handler
     int code,                          ...see TNCXXXX codes above
     int parm)                          ...see TNCXXXX codes above
     {
          int rc=-1;

          switch(code) {
          case TNCWIWO:
               if (parm) {              ...respond to IAC WILL <opid>
               }
               else {                   ...respond to IAC WONT <opid>
               }
               break;
          case TNCDODO:
               if (parm) {              ...respond to IAC DO <opid>
               }
               else {                   ...respond to IAC DONT <opid>
               }
               break;
          case TNCSBSE:                 ...handle a string, stored at stg[],
               break;                   ...stgcnt bytes long, opid=option ID
          case TNCOTHR:
               switch (code) {          ...handle other IAC codes (e.g. AYT)
               }
          }
          return(rc);
     }



Note:  Return codes for tnohose() and ->tnoxit()
------------------------------------------------
The application's exit point handler routine should return -1 in most cases.
Whatever is returned will also be returned by tnohose().  An application might
use this so the exit point can signal the tnohose() caller that a character
should be input.  (For example, the TNCOTHR-case handling of option EC (erase
character) could be to return backspace ('\b'), as if a backspace were
received.)  Or an exit point handler might use a special return code like -2
(or anything other than -1 or 0x00 to 0xFF) to tell the tnohose() caller to do
something special (and entirely application-specific).


Suboption Negotiation Message Allocation and Handling
-----------------------------------------------------
Here's the RFC-855 format of the SB...SE suboption negotiation message, where
a multi-byte parameter of arbitrary length may be communicated within the
Telnet option negotiation protocol.

     <IAC> <SB> <opt> <parameter> <IAC> <SE>

The <IAC>, <SB>, and <SE> characters are constants of the Telnet option
negotiation protocol.  (See below, or RFC-854 and RFC-855.)  The <opt>
character is one of the TNTOPT_XXX option codes for one of the complex options
that uses suboption negotiation (the most famous being TNTOPT_TTYPE -- see
RFC-1091).  This ends up in the tnoscb->opid field on an TNCSBSE-case exit
point.  The <parameter> is an arbitrary length string of characters which does
not usually include a terminator.  (The <IAC> <SE> terminates it.)  The exact
format of the <parameter> is specific to the <opt>.  If the parameter bytes
have any embedded literal IAC's, they are doubled up (and tnhose() decodes
these).

The stgcnt field of tnoscb applies to the number of bytes in the <parameter>
part that end up in the stg[] array.  That is, the bytes after the <opt> and
before the <IAC> <SE> (and with double-<IAC>s decoded into single-<IAC>s).
The maxstg paramter of tnoini(), which ends up in tnoscb->maxstg, should be
chosen by the application as the maximum possible stgcnt of interest plus 1.
A terminating NUL will always be appended onto the end of the tnoscb->stg[]
array.  So stgcnt can be 0 to maxstg-1, and may be the same as
strlen(tnoscb->stg).  (It could be less if <parameter> included any NUL
characters.)

Example suboption negotiation message (from TCP/IP illustrated, V1, pg 404):

     <IAC> <SB> <TNTOPT_TTYPE> 0 'I' 'B' 'M' 'P' 'C' <IAC> <SE>

There are three separate issues with potential off-by-one errors here, so be
careful:  the 0 prefix (the RFC-1091 "IS" field) that comes from the
<parameter> byte sequence; the NUL that tnohose() automatically sticks
onto the end of the <parameter> byte sequence; and the first byte of the
tnoscb->stg[] array that's allocated inside the formal tnoscb structure
"(struct tnoscb)".

The above example has the 5-character terminal name "IBMPC", so there are 6
bytes in the entire <parameter>.  (Remember, the <parameter> bytes that flow
through the Telnet connection have an *initial* 0-byte, not a terminating
0-byte.)  The total space needed in tnoscb->stg[] is at least 7 bytes, to make
room for the terminating NUL that tnohose() supplies.  The array of bytes
appended to (struct tnoscb) must be at least 6 bytes long because the tnoscb
structure has the first byte.

So, to receive the example string, maxstg should be at least 7.  When the
final <SE> is passed to tnohose(), the exit point tnoscb->tnoxit(TNCSBSE,0)
will be called.  Then tnoscb->opid will be TNTOPT_TTYPE, tnoscb->stgcnt will
be 6 (the number of bytes in <parameter>), tnoscb->stg[0] will be 0, and
sameas(tnoscb->stg+1,"IBMPC") will be true.  The character array allocated by
the application physically immediately after tnoscb should be at least 6 bytes
long.  Lo and behold, the NUL-terminated terminal name string winds up sitting
squarely in this character array.  Here's a diagram of the bytes:


                                             .<-- maximum possible ->.
                                             :    value of stgcnt    :
                                             :                       :
                                             :<--------- maxstg -------->.
                                             :                       :   :
                                             :   tnoscb->stg[] array :   :
                                             : _________________________ :
                                             :/                      :  \:
      ___ ___ ___ ___ ___ ___ ___ ___ ___ ___:___ ___ ___ ___ ___ ___:___:
     |   |op |               |max|stg|       |                           |
     |st  id       tnoxit     stg cnt  flags | 0  'I' 'B' 'M' 'P' 'C' NUL|
     |___|___|___ ___ ___ ___|___|___|___ ___|___ ___ ___ ___ ___ ___ ___|

      \_________________________________________/ \_____________________/
                     struct tnoscb                    character array
                        proper                     (maxstg-1) bytes long
                                                  that application must
                                                     append to tnoscb

We recommend you reveal all these off-by-one issues in your source code rather
than hide them.  If you want at least an 8-character terminal name (so you
could accomodate up to "BBS-ANSI" for example), then define a symbol for the
"maxstg" parameter you'll pass to tnoini():

     #define TNMSIZ (1+8+1)

This accounts for the "IS" 0-byte prefix and the terminating NUL.  Then
allocate the tnoscb structure with TNMSIZ-1 bytes following it:

     struct tntinf {               ...Telnet server session info
          struct tnoscb tnoscb;    ...TNO session control block   \ keep to-
          char stgrem[TNMSIZ-1];   ...rest of tntinf.tnoscb.stg[] / gether!
          :
          :
     } *tntinf;

Here's the initialization call:

     tnoscb=&tntinf->tnoscb;
     tnoini(TNMSIZ,tntops);

Of course, don't forget to account for "TNTOPT_TTYPE" in your tntops handler:

     static int
     tntops(                       ...Telnet option exit point handler
     int code,                     ...see TNCXXXX codes
     int parm)                     ...see TNCXXXX codes
     {
          int rc=-1;
          :
          switch (code) {
          :
          case TNCSBSE:            ...IAC SB ... IAC SE received, see opid
               switch(tnoscb->opid) {
               :
               case TNTOPT_TTYPE:
                    handle_terminal_name(&tnoscb->stg[1]);
                    break;
               :
               }
          }
          return(rc);
     }

#endif                             /* if 0                                 */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __TNO_H                              */
