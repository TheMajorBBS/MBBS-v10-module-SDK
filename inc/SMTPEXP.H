/***************************************************************************
 *                                                                         *
 *   SMTPEXP.H                                                             *
 *                                                                         *
 *   Copyright (C) 1995-1997 Galacticomm, Inc.  All rights reserved.       *
 *                                                                         *
 *   This is the SMTP exported functions/symbols header file.              *
 *                                                                         *
 *                                      7/27/95 - Bert Love                *
 *                                                Ilya Minkin              *
 *                                                Charles Dunn             *
 *                                                                         *
 ***************************************************************************/

#ifndef __SMTPEXP_H
#define __SMTPEXP_H

#include "gcomm.h"
#include "gme.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDSMTP
#       define SMTPEXP          EXPORT
#       define SMTPEXPV(x)      EXPORT_VARIABLE(x)
#       define SMTPEXPF(x, y)   EXPORT_FUNCTION(x, y)
#    else
#       define SMTPEXP          IMPORT
#       define SMTPEXPV(x)      IMPORT_VARIABLE(x)
#       define SMTPEXPF(x, y)   IMPORT_FUNCTION(x, y)
#    endif
#else
#       define SMTPEXP
#       define SMTPEXPV
#       define SMTPEXPF
#endif // GCWINNT

#define MIMIDSZ     72             /* maximum size of MIME boundary        */
#define INUIDSZ     64             /* longest user alias supported         */
#define MAILDAEM    "MAILER-DAEMON"/* "From:" line for bounced e-mail      */
#define SMTPSECTHDR "Internet Headers" /* app info section for msg headers */
#define SMTPSECTATT "Internet Section Headers" /* section for entity hdrs  */

struct SMTPEXP addrinf {           /* address information structure        */
     CHAR usrals[INUIDSZ];         /*   user alias (can be User-ID)        */
     CHAR domain[MAXADR-INUIDSZ-1];/*   domain name                        */
};

                                   /* address translation codes            */
#define BADADDR 0                  /*   address was not parseable          */
#define RMTADDR 1                  /*   address is remote address          */
#define LOCADDR 2                  /*   address is local address           */

                                   /* address translation hook types       */
#define XINT2GME 0                 /*   translate Internet -> GME address  */
#define XGME2INT 1                 /*   translate GME -> Internet address  */

typedef                                                                      \
GBOOL                              /*   returns TRUE if did translation    */\
(*addrXlatFunc)(                   /* address translation function         */\
CHAR *adrbuf,                      /*   buffer containing address to xlate */\
const CHAR *fromadr);              /*   addr mail is from (for validation) */
                                   /*   (adrbuf size must be MAXADR)       */

SMTPEXPV(GBOOL) usemgi;            /* using MG/I instead of SMTP           */
SMTPEXPV(GBOOL) smtponl;           /* SMTP exporter enabled?               */
SMTPEXPV(GBOOL) smtdonl;           /* SMTP daemon online?                  */
SMTPEXPV(CHAR*) smttmz;            /* time zone                            */
SMTPEXPV(CHAR) smtfpx[];           /* full Internet e-mail prefix          */
SMTPEXPV(CHAR*) smtdpuid;          /* ROOT/POSTMASTER User-ID              */
SMTPEXPV(GBOOL) smtihst;           /* include host name into outgoing msg  */
SMTPEXPV(GBOOL) smtdcvtf;          /* SMTP convert from addresses?         */

SMTPEXP VOID
init__galsmtp(VOID);               /* initialize SMTP module               */

SMTPEXP const CHAR*                /*   returns ptr to temp buffer         */
smtpHost(VOID);                    /* get host name used by SMTP           */

SMTPEXP GBOOL
smtval(                            /* is this a valid internet address?    */
const CHAR *addr);                 /*   address to check                   */

SMTPEXP GBOOL                      /*   returns TRUE if able to extract    */
extractAddr(                       /* extract address from header line     */
CHAR *adrbuf,                      /*   buffer to place extracted address  */
const CHAR *hdrlin);               /*   header line ("to:...", "<...>")    */

SMTPEXP VOID
parseIntAddr(                      /* parse internet-style address         */
const CHAR *address,               /*   address to parse                   */
struct addrinf *addrinf);          /*   buffer to return results           */

SMTPEXP GBOOL                      /*   return TRUE on successful parse    */
parseAddrLine(                     /* parse internet address header line   */
const CHAR *adrlin,                /*   address line ("to:...", "<...>")   */
struct addrinf *addrinf);          /*   buffer to return info              */

SMTPEXP VOID
hookAddrXlat(                      /* hook into address translation utility*/
INT xltType,                       /*   type of hook                       */
addrXlatFunc hookFunc);            /*   translation function               */

SMTPEXP INT                        /*   returns address translation code   */
xltInt2GME(                        /* translate internet addr to GME format*/
CHAR *adrbuf,                      /*   buffer containing address to xlate */
const CHAR *fromadr);              /*   addr mail is from (for validation) */
                                   /*   (adrbuf size must be MAXADR)       */

SMTPEXP GBOOL                      /*   returns TRUE if successful         */
xltGME2Int(                        /* translate GME addr to internet format*/
CHAR *adrbuf);                     /*   buffer containing address to xlate */
                                   /*   (adrbuf size must be MAXADR)       */

SMTPEXP CHAR*                      /*   returns pointer to buffer          */
smtpCvtFrom(                       /* convert from address to GME format   */
CHAR *adrbuf,                      /*   buffer to accept addr (MAXADR long)*/
struct addrinf *addrinf);          /*   parsed Internet address            */

SMTPEXP GBOOL                      /*   return TRUE if we are "name"       */
ourHost(                           /* check if name is one of our aliases  */
const CHAR *name);                 /*   host name to check                 */

SMTPEXP const CHAR*                /*   returns ptr to static buffer       */
cvtDate(                           /* convert DOS date to rfc1036 format   */
USHORT dtim,                       /*   DOS time                           */
USHORT ddat);                      /*   DOS date                           */

SMTPEXP CHAR*                      /*   (returns passed value)             */
nmsgid(                            /* generate an rfc822 message-id        */
CHAR *cp);                         /*   destination (max room=MAXADR+24)   */

SMTPEXP VOID
gmimid(                            /* generate MIME boundary               */
CHAR *midbuf,                      /*   MIME boundary buffer               */
LONG msgid);                       /*   local message ID                   */

SMTPEXP GBOOL                      /*   returns: FALSE when done           */
mimecode(                          /* MIME encode 'inf' to 'outf'          */
FILE *inf,                         /*   source file                        */
FILE *outf,                        /*   destination file                   */
const CHAR *lineTerm,              /*   line termination string            */
INT lineTermSize);                 /*   length of line terminator          */

SMTPEXP CHAR*
crpstr(                            /* crops string after passed character  */
const CHAR *string,                /*   string to crop                     */
CHAR cropch);                      /*   crop character                     */

SMTPEXP GBOOL                      /*   returns FALSE if too many files    */
makeUniqueFName(                   /* create unique temporary file name    */
CHAR *fpath,                       /*   path prefix with FNEXSZ extra room */
CHAR *extName);                    /*   extension name (e.g. "$$$")        */

/*
 * SMTP hook declarations
 */

 /* hook type identifiers                */
#define SMTPHOOK_EXPORT       0    /*   message being exported             */

typedef
GBOOL                              /*   return TRUE to stop calling hooks  */
(*smtphook_export)(                /*   message being exported handler     */
    INT* pRet,                     /*   GME status code                    */
    struct message* pMsg,          /*   header of message to send off      */
    CHAR const** pTo,              /*   to field                           */
    CHAR const** pAtt,             /*   path+file name of attachment       */
    CHAR** pText,                  /*   message text buffer                */
    size_t TextBufSize);           /*   current text buffer size           */

SMTPEXP GBOOL                      /*   returns TRUE if hook set           */
smtpHook(                          /*   set a SMTP function hook           */
    INT hooktype,                  /*   type of hook to set                */
    voidfunc hookfunc,             /*   hook handler function              */
    SHORT hookpri);                /*   priority (0=normal >0=high <0=low) */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __SMTPEXP_H
