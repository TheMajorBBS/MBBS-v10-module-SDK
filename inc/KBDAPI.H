/***************************************************************************
 *                                                                         *
 *   KBDAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Header file for keyboard API.                                         *
 *                                                                         *
 *                                        - Craig Yap 01/17/96             *
 *                                                                         *
 ***************************************************************************/

#ifndef __KBDAPI_H
#define __KBDAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef UNIX
#include <conio.h>
#endif // UNIX

#undef CTRL                        /* BSDI has this defined                */

                                   /* func key codes returned from getchc()*/
#define F1        (59*256)
#define F2        (60*256)
#define F3        (61*256)
#define F4        (62*256)
#define F5        (63*256)
#define F6        (64*256)
#define F7        (65*256)
#define F8        (66*256)
#define F9        (67*256)
#define F10       (68*256)
#define SHIFT     ((84-59)*256)    /* form shift-, alt-, and ctrl-func     */
#define CTRL      ((94-59)*256)    /* keys, add these values to the above  */
#define ALT       ((104-59)*256)   /* e.g. alt-F1's code is ALT+F1         */

                                   /* special key codes ret'd from getchc()*/
#define HOME      (71*256)
#define END       (79*256)
#define PGUP      (73*256)
#define PGDN      (81*256)
#define CRSRUP    (72*256)
#define CRSRDN    (80*256)
#define CRSRLF    (75*256)
#define CRSRRT    (77*256)
#define BAKTAB    (15*256)
#define INS       (82*256)
#define DEL       (83*256)
#define TAB       9
#define ESC       27
#define CTRLEND   (117*256)
#define CTRLHOME  (119*256)
#define CTRLPGUP  (132*256)
#define CTRLPGDN  (118*256)
#define CTRLLF    (115*256)
#define CTRLRT    (116*256)
#define CTRLUP    (141*256)
#define CTRLDN    (145*256)
#define ALT_A     (30*256)
#define ALT_B     (48*256)
#define ALT_C     (46*256)
#define ALT_D     (32*256)
#define ALT_E     (18*256)
#define ALT_F     (33*256)
#define ALT_G     (34*256)
#define ALT_H     (35*256)
#define ALT_I     (23*256)
#define ALT_J     (36*256)
#define ALT_K     (37*256)
#define ALT_L     (38*256)
#define ALT_M     (50*256)
#define ALT_N     (49*256)
#define ALT_O     (24*256)
#define ALT_P     (25*256)
#define ALT_Q     (16*256)
#define ALT_R     (19*256)
#define ALT_S     (31*256)
#define ALT_T     (20*256)
#define ALT_U     (22*256)
#define ALT_V     (47*256)
#define ALT_W     (17*256)
#define ALT_X     (45*256)
#define ALT_Y     (21*256)
#define ALT_Z     (44*256)
#define ALT_0     (129*256)
#define ALT_1     (120*256)
#define ALT_2     (121*256)
#define ALT_3     (122*256)
#define ALT_4     (123*256)
#define ALT_5     (124*256)
#define ALT_6     (125*256)
#define ALT_7     (126*256)
#define ALT_8     (127*256)
#define ALT_9     (128*256)

USHORT                             /*   returns character/function code    */
getchc(VOID);                      /* get composite key id                 */

#ifdef GCDOS

USHORT                             /*   scan code                          */
lascan(VOID);                      /* get scan code assoc w/last getchc()  */

#endif // GCDOS

#ifdef UNIX

INT                                /*   returns 0 if no character waiting  */
kbhit(VOID);                       /* check if keyboard char is available  */

USHORT                             /*   returns next character/scan code   */
getch(VOID);                       /* get next keyboard character          */

#endif // UNIX

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __KBDAPI_H
