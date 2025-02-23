/***************************************************************************
 *                                                                         *
 *   AIN.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.      All Rights Reserved.   *
 *                                                                         *
 *   ANSI X3.64 keystroke sequence - to - keystroke code translator        *
 *                                                                         *
 *   With operating-system-specific functions removed (I/O, memory)        *
 *   the pure translation algorithm can be isolated.                       *
 *                                                                         *
 *                                             - R. Stein  11/9/91         *
 *                                                                         *
 ***************************************************************************/

#ifndef __AIN_H
#define __AIN_H

#if 0
/*
This module can interpret a stream of incoming ASCII characters and detect
special ANSI coded keystrokes.  The keystrokes are reported in single integer
values which code either an ASCII value, or a special keystroke as if it came
from the IBM PC keyboard.  Actually that's the IBM keyboard scancode times
256.  See FKCODE.H (C source code with Worldgroup) for special values.  The
routine getchc() (in GCOMM.LIB with Worldgroup C source code) also returns
these values.  The resulting value is real handy because it can be used in a
big switch statement.

For example if you pass the 3 characters:

     <ESC>   [    A

to ainchr() in sequence, then the routine returns

       0     0    0x4800

That 0x4800 represents IBM keyboard scan code 48 hex or 72 decimal.  This is
the "up arrow" scan code.  The sequence <ESC> [ A is ANSI X3.64 for cursor up.
By the way if you pass 72 69 76 76 79 in sequence to ainchr(), what do you
think it will return?  The same stuff:  72 69 76 76 79!  This spells HELLO and
is pure ASCII so it gets passes through unchanged.

You can have multiple "AIN sessions" going on at once.  First you need to
initialize an AIN session using ainbeg().  Then simply call ainchr() with each
incoming character.  Process the output as you wish.

By the way, <ESC> followed by non-[ is also passed through by returning the
oddball value 0x0100 plus whatever the non-[ was.  01 hex is the IBM keyboard
scan code for the ESC key, by the way.
*/
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct ainscb {                    /* ANSI input session control block     */
     CHAR state;                   /* state code (see below)               */
};

extern struct ainscb *ainscb;      /* Global pointer to scb                */

/*--- AIN session state codes ---*/

#define WT4ESC 0                   /* Waiting for ESC                      */
#define WT4BKT 1                   /* Wait for [ (ANSI) or O (VT100 FUNKEY)*/
#define WT4ALP 2                   /* Wait for actual ANSI code            */
#define WT4LTO 3                   /* Wait for actual VT100 Function Key   */

VOID
ainbeg(VOID);                      /* begin an ANSI input translation sess */
                                   /* ainscb is implicit input             */

INT
ainchr(                            /* handle incoming ASCII/ANSI-coded seqs*/
CHAR c);                           /* the next character                   */
                                   /* ainscb is implicit input             */
                                   /* Returns 0 for nothing,               */
                  /* or the 2-byte keystroke code ala getchc() or FKCODE.H */
                                   /* That's usually the ASCII code,       */
                            /* but can be the IBM keyboard scan code * 256 */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /*  __AIN_H                             */
