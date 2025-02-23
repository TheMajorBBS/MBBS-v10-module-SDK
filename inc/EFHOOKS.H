/***************************************************************************
 *                                                                         *
 *   EFHOOKS.H                                                             *
 *                                                                         *
 *   Copyright (c) 1988-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   E-mail and Forums hooks for customizing certain functions.            *
 *                                                                         *
 *                                                - J. Alvrus 9/1/94       *
 *                                                                         *
 ***************************************************************************/

#ifndef __EFHOOKS_H
#define __EFHOOKS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef VOID (*quotfunc)(struct message *,CHAR *,UINT);
typedef CHAR *(*ccadfunc)(CHAR *,CHAR *,CHAR *);

quotfunc                           /*   old message quoter                 */
setquoter(                         /* set message quoter function          */
quotfunc newquoter);               /*   new message quoter                 */

ccadfunc                           /*   old cc: list adder                 */
setccadder(                        /* set add-cc:-list function            */
ccadfunc newccadder);              /*   new cc: list adder                 */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __EFHOOKS_H                          */
