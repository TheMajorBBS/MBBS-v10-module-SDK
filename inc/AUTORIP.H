/***************************************************************************
 *                                                                         *
 *   AUTORIP.H                                                             *
 *                                                                         *
 *   Copyright (c) 1993-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Globally defined RIP constants and exported variables.                *
 *                                                                         *
 *                                            - Bill Hyatt 10/27/93        *
 *                                                                         *
 ***************************************************************************/

#ifndef __AUTORIP_H
#define __AUTORIP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define RIPSFX     "/RIP"        /* RIP language names have this suffix    */
#define RIP_BUTTON "|1U"         /* RIP_BUTTON command only                */
#define BCSIZ      3             /* size of    "                           */
#define RBUTSZ     15            /* size of complete RIP_BUTTON, w/o "!"   */
#define RIP_BUTTON_STYLE "|1B"   /* RIP_BUTTON_STYLE cmd only              */
#define BSSIZ      3             /* size of    "                           */
#define RBSYSZ     39            /* sz of cmplt RIP_BUTTON_STYLE, w/o "!"  */
#define RIP_FONT_STYLE "|Y"      /* RIP_FONT_STYLE command only            */
#define FSSIZ      2             /* size of    "                           */
#define RFNTSZ     10            /* sz of cmplt RIP_FONT_STYLE, w/o "!"    */
#define RIP_RESET_WINDOWS "|*"   /* RIP_RESET_WINDOWS command only         */
#define RIP_TEXT_WINDOW   "|w"   /* RIP_TEXT_WINDOW command only           */
#define TWSIZ      2             /* size of     "      "    "              */
#define RTWSIZ     12            /* sz of cmplt RIP_TEXT_WINDOW, w/o "!"   */
#define RIPEBM     "|907040000<>" /* RIP_ENTER_BLOCK_MODE command stg     */
#define RIP_NO_MORE "|#"         /* RIP_NO_MORE command                    */
#define RNMOR3     "|#|#|#"      /* need 3 RIP_NO_MORE's at times          */
#define BCLST8     "00000000"    /* last 8 bytes b4 txt for def auto-btns  */
#define RIPVSZ     7             /* maximum size of a RIP version code     */

#define isripu()   (samend(languages[clingo]->name,RIPSFX))
                                 /* is this guy logged on using a RIP lang?*/
#define isripo(u)  (samend(languages[usroff((u))->lingo]->name,RIPSFX))
                                   /* is other user logged on w/ a RIP lang?*/

WGSEXPV(INT) ripdfd;               /* any RIP language defined on this svr?*/
WGSEXPV(INT) ripidx;               /* idx into languages[] of 1st /RIP lang*/

WGSEXPV(CHAR***) autscns;          /* RIP_BUTTON cmd stgs, 1..MAXSEL, for all*/
                                   /*      possible #'s of displayed button*/

WGSEXPV(CHAR*) lgrfnt[];           /* enabled/dimmed large button font sty */
WGSEXPV(CHAR*) lgrsty[];           /*    "      "    large button styles   */
WGSEXPV(CHAR*) smrfnt[];           /*    "      "    small button font sty */
WGSEXPV(CHAR*) smrsty[];           /*    "      "    small button styles   */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __AUTORIP_H                          */
