/******************************************************************************
 *                                                                            *
 *  VIDAPI.H                                                                  *
 *                                                                            *
 *  Copyright (C) 1994-1997 Galacticomm, Inc.      All Rights Reserved.       *
 *                                                                            *
 *  Header file for the cross-platform Galacticomm video API.                 *
 *                                                                            *
 *                          Original Assembly     (See PFWIN.ASM)             *
 *                          Unix Translation      Mahesh Neelakanta 04/04/94  *
 *                          DOS/Phar Lap Convert  R. Skurnick       07/16/95  *
 *                          Unity Spec Convert    R. Skurnick       12/01/95  *
 *                                                                            *
 *****************************************************************************/

#ifndef __VIDAPI_H
#define __VIDAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCV2S

CHAR *frzseg(VOID);

#define initvid() ((VOID)0)
#define clsvid() ((VOID)0)
#define disableConsoleVideo() ((VOID)0)
#define scn2mem(dst,ofs,cnt) memcpy(dst,frzseg()+ofs,cnt)
#define mem2scn(src,ofs,cnt) memcpy(frzseg()+ofs,src,cnt)
#define scn2scn(src,dst,cnt) memmove(frzseg()+dst,frzseg()+src,cnt)
#define scngetc(ofs) (*(frzseg()+ofs))
#define scnputc(ofs,byt) ((VOID)(*(frzseg()+ofs)=byt))

#else

VOID
initvid(VOID);                     /* initialize video subsystem           */

VOID
clsvid(VOID);                      /* shutdown video subsystem             */

VOID
disableConsoleVideo(VOID);         // disable video output

VOID
scn2mem(                           /* move real screen memory to other mem */
VOID *dest,                        /*   pointer to destination memory      */
UINT offset,                       /*   offset from start of the video scr */
UINT count);                       /*   number of bytes to move            */

VOID
mem2scn(                           /* move other memory to the real screen */
VOID *src,                         /*   pointer to source memory           */
UINT offset,                       /*   offset into the video screen       */
UINT count);                       /*   number of bytes to move            */

VOID
scn2scn(                           /* move real screen to real screen      */
UINT srcoff,                       /*   source offset for move             */
UINT dstoff,                       /*   destination offset for move        */
UINT count);                       /*   number of bytes to move            */

CHAR
scngetc(                           /* read a char/attr from the "REAL" scr */
UINT offset);                      /*   offset into the video screen       */

VOID
scnputc(                           /* change a char/attr on the "REAL" scr */
UINT offset,                       /*   offset into the video screen       */
CHAR byt);                         /*   new byte to be written to the scr  */

#endif // GCV2S

VOID
scnputw(                           /* change a char/attr pair on "REAL" scr*/
UINT offset,                       /*   offset into the video screen       */
CHAR byt,                          /*   new character                      */
CHAR atr,                          /*   new attribute                      */
UINT nwords);                      /*   number of char/attr pairs to put   */

CHAR                               /*   returns screen attrib if monochrome*/
scncolor(                          /* determine screen color               */
INT attrib);                       /*   attribute to check                 */

CHAR *
scblank(                           /* Clear a screen to blanks             */
CHAR *buf,                         /*   ptr to buffer to clear 0=real vid  */
CHAR attrib);                      /*   attribute to clear to              */

VOID
monorcol(VOID);                    /* sets up for monochrome if monochrome */

VOID
imonorcol(VOID);                   /* set 'color' flag on based on system  */

VOID
setwin(                            /* set window parameters                */
CHAR *scn,                         /*   ptr to screen to write to 0L=video */
INT xul,                           /*   upper left x coord                 */
INT yul,                           /*   upper left y coord                 */
INT xlr,                           /*   lower right x coord                */
INT ylr,                           /*   lower right y coord                */
INT sen);                          /*   scroll enable (1=yes)              */

VOID
rstwin(VOID);                      /* restore previous window parameters   */

VOID
belper(                            /* set bell ('\7') period               */
INT prd);                          /*   pitch and duration                 */

VOID
ansion(                            /* turn ANSI-handling on or off         */
INT yes);                          /* 1=on (default); 0=off                */

VOID
locate(                            /* move cursor to x,y position          */
INT x,                             /*   dest x (0=left margin)             */
INT y);                            /*   dest y (0=top line)                */

VOID
rstloc(VOID);                      /* restore cursor to previous x,y pos   */

VOID
cursact(                           /* enable moving of blinking cursor     */
CHAR movit);                       /*   1=move blinking cursor, 0=still    */

VOID
cursiz(                            /* set cursor size                      */
INT howbig);                       /*   off, little or block               */

VOID
rstcur(VOID);                      /* restore cursor from cursor-size stack*/

INT
curcurs(VOID);                     /* return current cursor size code      */

INT
curcurx(VOID);                     /* get current cursor x coord           */

INT
curcury(VOID);                     /* get current cursor y coord           */

VOID
setatr(                            /* sets video attributes                */
CHAR atr);

VOID
cleareol(VOID);                    /* clear from cursor to end of line     */

#define MAXPFSIZ    8192           /* maximum size of printf() strings     */

INT
printfat(                          /* Galacticomm printf at position x,y   */
INT x,                             /*   x position to print at             */
INT y,                             /*   y position to print at             */
CHAR *fmt,                         /*   format string                      */
...);                              /*   variable number of parameters      */

VOID
proff(                             /* set offsets for certain printing     */
INT x,                             /*   the x offset                       */
INT y);                            /*   the y offset                       */

VOID
prat(                              /* print at a location relative to proff*/
INT x,                             /*   x offset to start at               */
INT y,                             /*   y offset to start at               */
CHAR *ctlstg,                      /*   control string                     */
...);

CHAR *
auxcrt(VOID);                      /* pointer to auxillary CRT             */

#ifndef GCV2S

INT
gprintf(                           /* Galacticomm flavor of printf         */
CHAR *fmt,                         /*   format string                      */
...);                              /*   variable number of parameters      */

#define printf gprintf             /* replace printf() refs with gprintf() */

#endif // GCV2S

                                   /* defines for cursor size of cursiz()  */
#define GVIDNOCURS  0              /*  cursor invisible                    */
#define GVIDLILCURS 1              /*   small underscore cursor            */
#define GVIDBIGCURS 2              /*   block (insert) cursor              */

#define GVIDSCNSIZ  4000           /* # of bytes per 80x25 screen image    */
#define gvscnoff(x,y) ((((y)*80)+(x))*2)/* xlate (x,y) to screen offset    */

#define GVIDCSZSTK  10             /* size of cursiz()/rstcur() stack      */

struct curatr {               /* screen & cursor status region             */
   CHAR attrib;                    /* attribute byte for video ram         */
   CHAR ansifls;                   /* default to ANSI disabled (below)     */
   UINT ansicnt;                   /* # of ANSI args before action letter  */
   CHAR ansiarg[20];               /* up to 20 individual args             */
   UINT scpreg;                    /* ANSI save-cursor-position register   */
   CHAR saveal;                    /* save reg for orig ANSI command char  */
   CHAR ansiatr;                   /* default ANSI attribute               */
   UINT oldcur;                    /* saved (old) cursor coords            */
   CHAR *scnstt;                   /* default screen start addr            */
   CHAR *oscnstt;                  /* saved (old) screen start addr        */
   CHAR actcur;                    /* cursor is active by default          */
   UINT nacurp;                    /* default non-active cursor-position   */
   UINT lacurp;                    /* last active cursor position          */
   UINT period;                    /* bell period (higher=>faster&shorter) */
   CHAR ulx;                       /* internal copy of window upper left x */
   CHAR uly;                       /* internal copy of window upper left y */
   CHAR lrx;                       /* internal copy of window lower right x*/
   CHAR lry;                       /* internal copy of window lower right y*/
   CHAR scropt;                    /* internal copy of window scroll option*/
   CHAR topscr;                    /* internal copy of window scroll top   */
   CHAR botscr;                    /* internal copy of window scroll down  */
   CHAR oulx;                      /* saved int. copy - window upper left x*/
   CHAR ouly;                      /* saved int. copy - window upper left y*/
   CHAR olrx;                      /* saved int. copy-window lower right x */
   CHAR olry;                      /* saved int. copy-window lower right y */
   CHAR oscropt;                   /* saved int. copy-window scroll option */
   CHAR usetop;                    /* which limit is being used            */
   CHAR usebot;                    /* which limit is being used            */
};

WGSEXPV(struct curatr) curatr;
WGSEXPV(GBOOL) color;              /* flag indicating color display avail  */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __VIDAPI_H                           */
