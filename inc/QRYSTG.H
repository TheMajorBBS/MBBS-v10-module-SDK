/***************************************************************************
 *                                                                         *
 *   QRYSTG.H                                                              *
 *                                                                         *
 *   Copyright (c) 1995-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   World-Wide Web Query-String handling utilities.                       *
 *                                                                         *
 *   Ref HTML Sourebook, 1995, Ian S. Graham, pages 162-165, 225-227.      *
 *                                                                         *
 *                                              - R. Stein  7/12/95        *
 *                                                                         *
 ***************************************************************************/

#ifndef __QRYSTG_H
#define __QRYSTG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct qrsinf {                    /*--- Query-string info block        ---*/
     CHAR *name;                   /* pointer to name (NUL-terminated)     */
     CHAR *value;                  /* pointer to value (NUL-terminated)    */
     CHAR spare[8];                /* (future exp w/binary compatibility)  */
};

GBOOL                              /*   return TRUE if got first           */
qrs1st(                            /* initialize parsing a query string    */
struct qrsinf *qip,                /*   ptr to query-string info block     */
CHAR *qstring);                    /*   query string (after '?' in uri for */
                                   /*   GET method, body for POST method)  */
                                   /*   (query string modified in place)   */
                                   /* Caller should not wait before calling*/
                                   /* qrsnxt() to exhaustion, as strtok()  */
                                   /* may be used internally.              */

GBOOL                              /*   return TRUE if got next            */
qrsnxt(                            /* next name/value pair fm query string */
struct qrsinf *qip);               /*   ptr to query-string info block     */

CHAR *                             /*   returns same value as passed       */
decurl(                            /* decode URL escape coding             */
CHAR *url);                        /*   URL string, converted in place     */
                                   /*   (string never expands, may shrink) */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __QRYSTG_H                           */
