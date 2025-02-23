/***************************************************************************
 *                                                                         *
 *   MHSALIAS.H                                                            *
 *                                                                         *
 *   Copyright (c) 1992-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This file declares structures and functions used to create exporters  *
 *   that alias MHS.  These exporters appear to GME to be distinct         *
 *   exporters (with their own prefix, etc.), but the actual importing/    *
 *   exporting is done by MHS.                                             *
 *                                                                         *
 *                                            - J. Alvrus   1/9/95         *
 *                                                                         *
 ***************************************************************************/

#ifndef __MHSALIAS_H
#define __MHSALIAS_H

#include "gcomm.h"
#include "gme.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct mhsalias {                  /* MHS alias structure                  */
     struct exporter exp;          /*   exporter control block for GME     */
     CHAR *outmsg;                 /*   outgoing message directory         */
     CHAR *outfil;                 /*   outgoing attachment directory      */
     CHAR *inmsg;                  /*   incoming message directory         */
     CHAR *infil;                  /*   incoming attachment directory      */
     CHAR *outpfx;                 /*   outgoing message address prefix    */
     CHAR *outsfx;                 /*   outgoing message address suffix    */
};

GBOOL                              /*   returns FALSE if bad directories   */
register_mhsalias (                /* set up an MHS alias                  */
struct mhsalias *alias);           /*   alias definition block             */

GBOOL
valmhs(                            /* does addr contain valid MHS '@' char */
const CHAR *adr);                  /* ('!' is considered valid for MG/I)   */

CHAR *
aliasasp(                          /* get outbound att file path+name      */
struct mhsalias *alias,            /*   for this exporter alias            */
const CHAR *to,                    /*   address to which message being sent*/
const struct message *msg);        /*   header of message being sent       */

INT                                /*   returns GME error codes            */
sndalias(                          /* send a message for an MHS alias      */
struct mhsalias *alias,            /*   exporter alias being used          */
const CHAR *to,                    /*   to field (MHS address)             */
const struct message *msg,         /*   header of message to send off      */
const CHAR *text,                  /*   message text buffer                */
const CHAR *filatt);               /*   path+file name of attachment       */

const CHAR *
mhsGatewayName(VOID);              /* get MHS gateway name                 */
                                   /* (replaces exported gtwnme variable)  */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __MHSALIAS_H                         */
