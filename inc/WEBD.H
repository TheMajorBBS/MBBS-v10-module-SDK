/***************************************************************************
 *                                                                         *
 *   WEBD.H                                                                *
 *                                                                         *
 *   Copyright (c) 1994-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   World-Wide Web (WWW) server for access to HTML pages.                 *
 *                                                                         *
 *   Ref HTTP/1.0 draft of 3/8/95:                                         *
 *        ftp://ds.internic.net/internet-drafts/                           *
 *        draft-ietf-http-v10-spec-00.txt                                  *
 *                                                                         *
 *   Ref HTML - 2.0 draft of 6/16/95                                       *
 *        ftp://ds.internic.net/internet-drafts/                           *
 *        draft-ietf-html-spec-04.txt                                      *
 *                                                                         *
 *                                              - R. Stein  8/5/94         *
 *   Clickable image maps, statistics logging   - C. Yap    6/95           *
 *   HTTP 1.0, interceptable vectors, forms     - R. Stein  7/95           *
 *                                                                         *
 ***************************************************************************/

#ifndef __WEBD_H
#define __WEBD_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef GCWINNT
#   ifdef __BUILDWEBD
#       define WEBDEXP          EXPORT
#       define WEBDEXPV(x)      EXPORT_VARIABLE(x)
#       define WEBDEXPF(x, y)   EXPORT_FUNCTION(x, y)
#    else
#       define WEBDEXP          IMPORT
#       define WEBDEXPV(x)      IMPORT_VARIABLE(x)
#       define WEBDEXPF(x, y)   IMPORT_FUNCTION(x, y)
#    endif
#else
#       define WEBDEXP
#       define WEBDEXPV
#       define WEBDEXPF
#endif // GCWINNT

#if defined(UNIX)
#if !defined(ASSERT)
#define ASSERT(x)
#define ASSERTM(x,y)
#endif                             /* !ASSERT                              */
#define cr2lf(x)        strstp(x,'\r')
#else
#define cr2lf(x)        x
#endif                             /* UNIX                                 */

#define DFTWEBPORT 80              /* default TCP port for Web server      */
#define WEBNAME "World-Wide Web"   /* name of Web server                   */
#define WEBBACKLOG 5               /* listen() backlog                     */
#define URISIZ 1024                /* max size of a URI                    */
#define MAXVERT 100                /* max vertices in a polygon            */
#define MINREQBUF 2048             /* minimum guaranteed room at httpreqbuf*/
#define BDYMAX 100000UL            /* default max body size (in bdyfil)    */
#define ABWHYSIZ 80                /* room for why retrieval aborted       */
                                   /* (must sync w/all sprintf(abwhy,,)'s) */

struct WEBDEXP webdusr {           /* Web server channel information       */
     UINT reqcnt;                  /* number of bytes stored in httpreqbuf */
     UINT hdrsiz;                  /* size of req line & header, incl \n's */
     UINT reqsiz;                  /* size of entire request line, incl \n */
     USHORT flags;                 /* see below                            */
     UINT httpver;                 /* HTTP version number * 100 (100=1.0)  */
     USHORT sttime;                /* 16 Hz activity timer                 */
     ULONG conlen;                 /* Content-Length                       */
     ULONG concnt;                 /* count of content body written to file*/
     CHAR *contyp;                 /* Content-Type                         */
     CHAR *userag;                 /* User-Agent                           */
     CHAR *method;                 /* request method (GET, PUT, etc.)      */
     CHAR *uri;                    /* request URI                          */
     CHAR *vertxt;                 /* version text, or "" if none          */
     CHAR *refer;                  /* Referer                              */
     CHAR *auth;                   /* Authorization                        */
     USHORT imsdat;                /* If-Modified-Since, date part         */
     USHORT imstim;                /* If-Modified-Since, time part         */
     ULONG bytcnt;                 /* total bytes transferred to user      */
     FILE *rspfp;                  /* response coming from a file          */
     FILE *reqfp;                  /* request body stored in temporary file*/
     CHAR abwhy[ABWHYSIZ];         /* why retrieval was aborted            */
     ULONG lstcnt;                 /* bytcnt one second ago                */
     ULONG tfstart;                /* time (lngtck) retrieval started      */
     ULONG tfsupd;                 /* lngtck of last %-update              */
     ULONG filsiz;                 /* total size of file                   */
     CHAR goturi[MAXPATH];         /* path of file being retrieved         */
};                                 /* ...httpreqbuf uses up rest of VDA    */
                                   /* ...which is at least MINREQBUF bytes */

#define WFLIMS 0x0002              /* If-Modified-Since request received   */

#define webdptr ((struct webdusr *)vdaptr)
#define httpreqbuf (vdaptr+sizeof(struct webdusr))
#define maxreqbuf (vdasiz-sizeof(struct webdusr))
#define bodyarea (httpreqbuf+webdptr->hdrsiz)
                                   /* where body is stored (freed up after */
                                   /* calling bdy2fil())                   */
#define bodyroom (maxreqbuf-webdptr->hdrsiz)

#define webdptru(u) ((struct webdusr *)vdaoff(u))
#define httpreqbufu(u) (vdaoff(u)+sizeof(struct webdusr))
#define bodyareau(u) (httpreqbufu(u)+webdptru(u)->hdrsiz)
                                   /* where body is stored (freed up after */
                                   /* calling bdy2fil())                   */
#define bodyroomu(u) (maxreqbuf-webdptru(u)->hdrsiz)

                                   /*--- Web server substate codes      ---*/
#define WEBHDR 0                   /* collect request header to httpreqbuf */
#define WEBBDY 1                   /* record body of request to a file     */
#define WEBHDL 2                   /* handle request                       */
#define WEBFIL 3                   /* dump file to client as response body */

WEBDEXPV(CHAR*) webroot;           /* path prefix to all Web HTML pages    */
WEBDEXPV(CHAR*) imgroot;           /* path prefix for image maps           */
WEBDEXPV(CHAR*) dftfil;            /* default file for "GET /" response    */
WEBDEXPV(CHAR*) imgpfix;           /* prefix for (*hdlimgmap)() i'ceptors  */
                                   /* always begins and ends with "/"      */
WEBDEXPV(CHAR*) noclick;           /* pseudo-URL for image maps: ignore clk*/
WEBDEXPV(CHAR*) webd_version;      /* Web server version string (for tvar) */
WEBDEXPV(INT) webtzone;            /* minutes behind GMT (240=EDT)         */

                                   /*   returns 1=ok, 0=byeweb() called    */
WEBDEXPF(SHORT, prswebhdr)(VOID);  /* parse web request header             */
                                   /*   see webdptr->reqsiz and hdrsiz     */
                                   /*   (first vector called for new req)  */

                                   /*   returns 1=handled, 0=not recognized*/
WEBDEXPF(SHORT, prshdrlin)(        /* handle header line of incoming req   */
     CHAR *hdrlin);                /*   for each header line (not req line)*/

WEBDEXPF(VOID, hdlwebreq)(        /* request interceptor                  */
     CHAR *uri);                   /*   URI following method in req line   */

                                   /*   ret 1=handled, 0=404 err (no found)*/
WEBDEXPF(SHORT, hdlwebget)(        /* GET request interceptor              */
     CHAR *uri);                   /*   URI following 'GET' in request line*/

                                   /*   ret 1=handled, 0=404 err (no found)*/
WEBDEXPF(SHORT, filwebsnd)(        /* File send interceptor                */
     CHAR *pth);                   /*   full path of file                  */

                                   /*   ret 1=mapped, 0=no action, -1=error*/
WEBDEXPF(INT, hdlimgmap)(          /* Image map mouse-click interceptor    */
     CHAR *mapnam,                 /*   Image map file name (after imgpfix)*/
     UINT xt,                      /*   pixel X of mouse click             */
     UINT yt,                      /*   pixel Y of mouse click             */
     CHAR **newurl);               /*   where to put pointer to mapped URL */
                                   /*   (useful when returning 1 only)     */

                                   /*   returns no. bytes sent as rsp body */
WEBDEXPF(INT, hdlrspbdy)(          /* response body bytes en route client  */
     CHAR *buffer,                 /*   bytes to send in response body     */
     INT nbytes);                  /*   number of bytes                    */
                                   /*   CAUTION: buffer may be vdatmp      */

WEBDEXPV(CHAR*) bdyfil;            /* temporary file for incom. Entity Body*/
WEBDEXPV(ULONG) bdymax;            /* maximum size of body (in bdyfil)     */

WEBDEXP VOID
init__webd(VOID);                  /* Initialization                       */

WEBDEXP SHORT                      /*   return 1=ok, 0=byeweb() called     */
prsreqlin(VOID);                   /* parse request line (meth,uri,ver)    */
                                   /*   may call in (*prswebhdr)() handler */

WEBDEXP SHORT                              /*   ret 1=handled, 0=not recognized    */
mapwebget(                         /* NCSA-style image map file interpreter*/
CHAR *uri);                        /* URI from client                      */

WEBDEXP SHORT                              /*   ret 1=handled, 0=404 err (no found)*/
filwebget(                         /* file-retrieval form of GET request   */
CHAR *uri);                        /*   URI (file path rel to WEBROOT{})   */
                                   /*   (corrupts vdatmp)                  */

WEBDEXP SHORT                              /*   returns 1=success, 0=byeweb called */
bdy2fil(VOID);                     /* write request body (so far) to file  */
                                   /*   leaves file open for read & write  */

WEBDEXP SHORT                              /*   ret 1=bad (byeweb() called), 0=ok  */
badfspec(                          /* Is URI-based filespec dangerous?     */
CHAR *uri);                        /*   URI or filespec based on a URI     */

WEBDEXP SHORT                              /*   returns 1=match, 0=not             */
hdrstg(                            /* parse a named token                  */
CHAR *source,                      /*   line, eg 'Content-Type: text/html' */
CHAR *token,                       /*   token name, eg 'Content-Type:'     */
CHAR **var);                       /*   where to put value, eg 'text/html' */

WEBDEXP ULONG
udif2(                             /* square of difference of two u-ints   */
UINT a,
UINT b);

WEBDEXP CHAR*
webpth(                            /* format path name of web page         */
CHAR *pagnam);                     /* page name (can start with "/" or "\")*/
                                   /* returns "" if combination too long   */

WEBDEXP CHAR*
imgpth(                            /* format path name of web page         */
CHAR *pagnam);                     /* page name (can start with "/" or "\")*/
                                   /* returns "" if combination too long   */
WEBDEXP VOID
byeweb(                            /* say goodbye to a Web user w/msg      */
INT msgno,                         /*   message number to use              */
...);                              /*   variable number of parameters      */
                                   /*   usrnum is implicit                 */
                                   /*   do not use NO_MESSAGE or PAMSG     */
WEBDEXP VOID
endwebd(                           /* terminate the WWW session            */
INT complt);                       /* 1=finished, 0=aborted                */

WEBDEXP VOID
datu2d(                            /* convert Unix time/date to DOS format */
ULONG uxtime,                      /*   Unix seconds since 1/1/70          */
USHORT* dat,                       /*   pointer to DOS packed date output  */
USHORT* tim);                      /*   pointer to DOS packed time output  */

WEBDEXP VOID
datd2u(                            /* convert DOS time/date to Unix format */
USHORT dat,                        /*   DOS packed date                    */
USHORT tim,                        /*   DOS packed time                    */
ULONG *uxtime);                    /*   ptr, Unix secs since 1/1/70 output */

WEBDEXP CHAR*                      /*   returns pointer to formatted date  */
enchttpdate(                       /* Encode an HTTP date                  */
USHORT dat,                        /*   DOS packed date format             */
USHORT tim);                       /*   DOS packed time format             */

WEBDEXP INT                        /*   returns 1=ok, 0=bad format         */
dechttpdate(                       /* Decode an HTTP date                  */
CHAR *dnt,                         /*   RFC 822, RFC 850, or ANSI C format */
USHORT *dat,                       /*   DOS packed date format             */
USHORT *tim);                      /*   DOS packed time format             */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __WEBD_H                             */
