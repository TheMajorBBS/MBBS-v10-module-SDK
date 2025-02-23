/***************************************************************************
 *                                                                         *
 *   BBSUTILS.H                                                            *
 *                                                                         *
 *   Copyright (c) 1990-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   These are general purpose server functions.                           *
 *                                                                         *
 *                                            - R. Skurnick   12/5/89      *
 *                                            - S. Brinker                 *
 *                                            - A. Von Gauss               *
 *                                                                         *
 ***************************************************************************/
/***************************************************************************/
/** Variable Definitions                                                  **/
/***************************************************************************/

#ifndef __BBSUTILS_H
#define __BBSUTILS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MTRBUF_SIZ       127       /* Size of MTRBUF character array       */

WGSEXPV(INT) mtretv;               /* CNC last return value                */
WGSEXPV(INT) mtrint;               /* CNC returned integer                 */

WGSEXPV(UINT) mtruni;              /* CNC returned unsigned integer        */

WGSEXPV(LONG) mtrlng;              /* CNC returned long integer            */

WGSEXPV(CHAR) mtrbuf[MTRBUF_SIZ];  /* CNC string buffer                    */

/***************************************************************************/
/** Function Types (Semi-Prototyping)                                     **/
/***************************************************************************/

                                   /* Get hexidecimal integer using CNC    */
#define mtghex(min,max)            mtgbas(16,(LONG)min,(LONG)max)

                                   /* Get integer using CNC                */
#define mtgint(min,max)            mtgbas(10,(LONG)min,(LONG)max)

                                   /* Get unsigned integer using CNC       */
#define mtguni(min,max)            mtgbas(10,(LONG)min,(LONG)max)

                                   /* Get long integer using CNC           */
#define mtglng(min,max)            mtgbas(10,min,max)

                                   /* Get binary integer using CNC         */
#define mtgbin(min,max)            mtgbas(2,(LONG)min,(LONG)max)

VOID
dspmsg(                            /* Display Message based on ANSI flag   */
INT msgno,
CHAR *parm1,
CHAR *parm2,
CHAR *parm3);

VOID
dspmlt(                            /* Display Message based on ANSI flag   */
INT msgno,
CHAR *parm1,
CHAR *parm2,
CHAR *parm3);

INT genrdn(INT min,INT max);
LONG lngrnd(LONG min,LONG max);
INT mtgstg(INT mulwrd,INT maxlen);
INT mtgchn(INT min,INT max);
INT mtgbas(INT base,LONG min,LONG max);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __BBSUTILS_H
