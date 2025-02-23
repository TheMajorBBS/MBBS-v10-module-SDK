/***************************************************************************
 *                                                                         *
 *   LOCKNKEY.H                                                            *
 *                                                                         *
 *   Copyright (c) 1991-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   This is the header file for the suite of routines contained in        *
 *   LOCKNKEY.C.                                                           *
 *                                                                         *
 *                                   - S. Brinker and C. Robert  10/3/91   *
 *                                                                         *
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This routine will first clear a user's list of keys, then read in     *
 *   all his keys from disk (including all the keys on the keyring).  You  *
 *   should use this routine when assigning an online user a different     *
 *   keyring.                                                              *
 *                                                                         *
 *        VOID                                                             *
 *        loadkeys(           load keys from disk into usrptr->keys        *
 *        CHAR *keyring)           name of keyring to load (NULL if none)  *
 *                                                                         *
 *                                                                         *
 *   These three routines can be used to test if a certain user has a key  *
 *   or not.  The uidkey() routine reads the Btrieve file, and should      *
 *   therefore only be used when checking a user not online (otherwise     *
 *   use haskey() for "usrptr" checks and othkey() for "othusp" checks).   *
 *                                                                         *
 *        INT                      1=user has key, 0=user doesn't have key *
 *        haskey(             does current user have the key to this lock? *
 *        CHAR *lock)              name of lock for which key is used      *
 *                                                                         *
 *        INT                      1=user has key, 0=user doesn't have key *
 *        othkey(             does other user have the key to this lock?   *
 *        CHAR *lock)              name of lock for which key is used      *
 *                                                                         *
 *        INT                      1=user has key, 0=user doesn't have key *
 *        uidkey(             does other user have the key to this lock?   *
 *        CHAR *uid                user-id to check (whether online or not)*
 *        CHAR *lock)              name of lock for which key is used      *
 *                                                                         *
 *                                                                         *
 *   These next two routines can be used to give and remove keys from a    *
 *   user.  You can either pass them a single key name, or a list of       *
 *   keys, each separated from each other by a single space, and           *
 *   terminated with a NULL (e.g., "CUSTOMER COSYSOP BETATEST\0").  They   *
 *   both will update the user's access in real-time if he is online.      *
 *                                                                         *
 *   You can also use these routines to add or remove keys from a keyring  *
 *   by passing a keyring name with a leading ampersand ('&') tacked on    *
 *   for the "uid" parameter.                                              *
 *                                                                         *
 *        INT                      0=couldn't give key, 1=key granted      *
 *        givkey(             give a userid a particular (update if online)*
 *        CHAR *uid,               user-id (or keyring) to give key to     *
 *        CHAR *keylist)           list of lock for which key is used      *
 *                                                                         *
 *        VOID                                                             *
 *        rmvkey(             remove a key from a userid (update if online)*
 *        CHAR *uid,               user-id (or keyring) to remove key from *
 *        CHAR *keylist)           name of lock for which key is used      *
 *                                                                         *
 *                                                                         *
 *   You can also manage your own ASCII lists of keys (each key separated  *
 *   by a space, the entire list NULL-terminated).  This routine can be    *
 *   used to determine if a key name is in a given list or not (and if so, *
 *   give you the option of removing it or not).  To add keys to your own  *
 *   lists, just strcat() a space and the key name to your list.           *
 *                                                                         *
 *        INT                      1=key in list, 0=key not in list        *
 *        fndkey(             is a certain key in a ASCII list of keys     *
 *        CHAR *lock,              name of lock for which key is used      *
 *        CHAR *keylist,           ptr to NULL-termin. list of key names   *
 *        GBOOL remove)            if found, remove from list? 0=no, 1=yes *
 *                                                                         *
 ***************************************************************************/

#ifndef __LOCKNKEY_H
#define __LOCKNKEY_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define KEYSIZ      16        /* max size of key name (and class name also)*/
#define LOKSIZ      48        /* max size of lock name (can have ands/ors) */
#define RINGID      '&'       /* first character for a "keyring"-id        */
#define KLSTOF      30        /* offset of keylist into "keyrec" (kysbuf)  */
#define RINGSZ      1024      /* size of largest possible keyring record   */
#define RSZBLK      20        /* block size for alcrsz() calls in locknkey */

WGSEXPV(CHAR**) locks;        /* dynamically resized list of known locks   */

WGSEXPV(INT) nlocks;          /* current number of known locks in memory   */
WGSEXPV(INT) npkeys;          /* current number of pseudokeys in memory    */

typedef \
GBOOL                         /*   returns TRUE if has psuedokey2          */\
(*pseudoKeyFunc2)(            /* pseudokey evaluation function type        */\
struct usracc* pacc,               /*   pointer to user account being checked   */\
INT unum,                     /*   usrnum or -1 if not online              */\
const CHAR *lock);            /*   pseudokey name to evaluate              */

typedef \
GBOOL                         /*   returns TRUE if has pseudokey           */\
(*pseudoKeyFunc)(             /* pseudokey evaluation function type        */\
INT unum,                     /*   user number to check                    */\
const CHAR *lock);            /*   pseudokey name to evaluate              */

struct pskeys {               /* psuedokeys data structure definition      */
     CHAR pskbeg[KEYSIZ];     /* beginning of pseudokey name (sameto)      */
     pseudoKeyFunc pskrou;    /* does unum have this pseudokey?            */
};

struct pskeys2 {              /* 2nd generations data structure            */
     CHAR pskbeg[KEYSIZ];     /* beginning of pseudokey name (sameto)      */
     pseudoKeyFunc2 pskrou;   /* Second generation routine                 */
};

WGSEXPV(struct pskeys*) pkeys;/* dynamic array of registered pseudokeys    */

WGSEXPV(CHAR*) kysbuf;        /* pointer to one-shot internal keys buffer  */

/* LOCKNKEY.C 03/04/92 11.12.42 */

WGSEXP VOID
inikys(VOID);                      /* initialize the locks & keys interface*/

WGSEXP INT
register_pseudok(                  /* register a new pseudokey             */
const CHAR *pskbeg,                /*   beginning of pseudokey             */
pseudoKeyFunc pskrou);             /*   routine for validating pseudokey   */

WGSEXP INT
register_pseudok2(                 /* register a new generation pseudokey  */
const CHAR *pskbeg,                /*   beginning of pseudokey             */
pseudoKeyFunc2 pskrou);            /*   routine for validating pseudokey   */

WGSEXP UINT                        /*  Amount of 2nd generation pseudokeys */
numPseudokey2(VOID);               /* Get amount of pseudokeys             */

WGSEXP GBOOL                       /*  TRUE/FALSE if pseudokey is found    */
getPseudokey2(                     /* Get a pseudokey by number            */
UINT uKey,                         /*  Pseudokey number to get             */
struct pskeys2* ppskey,            /*  Structure to be filled in           */
size_t nSize);                     /*  Size of the structure to be filled  */

WGSEXP VOID
nkyrec(                            /* create a new key record              */
const CHAR *uid);                  /*   for this user-id or keyring        */

WGSEXP VOID
loadkeys(                          /* load a user's keys into memory       */
const CHAR *keyring);              /*   keyring name for this user         */

WGSEXP VOID
usetkey(                           /* turn cur user's bit on for this key  */
const CHAR *lock);                 /*   key name to turn on                */

WGSEXP INT
haskno(                            /* does this user have this key number  */
INT bitno);                        /*   bit number for this key            */

WGSEXP INT
gen_haskey(                        /* general haskey() for any user routine*/
const CHAR *lock,                  /*   lock name the key is for           */
INT unum,                          /*   user number we're dealing with     */
struct user *uptr);                /*   user pointer we're dealing with    */

WGSEXP INT
low_haskey(                        /* low-level haskey() hdlr (no ands/ors)*/
const CHAR *lock,                  /*   lock name the key is for           */
INT unum,                          /*   user number we're dealing with     */
struct user *uptr);                /*   user pointer we're dealing with    */

WGSEXP INT                         /*   -1 = not found, 1 = pass, 0 = fail */
scnpsk(                            /* scan through pseudo-keys for a lock  */
INT unum,                          /*   user number trying to use key      */
const CHAR *lock);                 /*   lock name the key is for           */

WGSEXP INT                         /*   -1 = not found, 1 = pass, 0 = fail */
scnpsk2(                           /* scan through pseudo-keys for a lock  */
struct usracc* pacc,                    /*   user account structure using key   */
INT unum,                          /*   user number trying (-1 if none)    */
const CHAR* lock);                 /*   lock name the key is for           */

WGSEXP INT
uhsmkey(                           /* passed user have this key (in msg)?  */
const CHAR *uid,                   /*   user-id (online or offline)        */
INT mnum);                         /*   message number with key name       */

WGSEXP INT
hasmkey(                           /* does cur usr have key in message?    */
INT mnum);                         /*   message number with key name       */

WGSEXP INT
uhskey(                            /* does passed user have this key?      */
const CHAR *uid,                   /*   user-id (online or offline)        */
const CHAR *lock);                 /*   key name to check for              */

WGSEXP INT
haskey(                            /* does the current user have this key? */
const CHAR *lock);                 /*   lock name to check for             */

WGSEXP INT
othkey(                            /* does other user have this key(othusn)*/
const CHAR *lock);                 /*   lock name to check for             */

WGSEXP INT
uidkey(                            /* does passed user have this key?      */
const CHAR *uid,                   /*   user-id to look up (not online)    */
const CHAR *lock);                 /*   lock name to check for             */

WGSEXP INT
getlst(                            /* get a list of keys from BTRIEVE      */
const CHAR *uid,                   /*   user-id or keyring name to get     */
CHAR *buffer);                     /*   buffer to put end result           */

WGSEXP INT
findkey(                           /* find a key (or remove) in list       */
const CHAR *lock,                  /*   lock name to search for            */
CHAR *keylist,                     /*   pointer to list of keys            */
GBOOL remove);                     /*   remove?                            */

WGSEXP INT
givkey(                            /* give user or keyring list of keys    */
const CHAR *uid,                   /*   uid or keyring name to update      */
CHAR *keylist);                    /*   list of keys to give               */

WGSEXP INT
addkyu(                            /* add a key to the kysbuf buffer       */
const CHAR *keyptr,                /*   pointer to the key name            */
GBOOL update);                     /*   update the BTRIEVE record?         */

WGSEXP VOID
ustkey(                            /* turn off user's bit for this key     */
const CHAR *lock);                 /*   key name to turn off               */

WGSEXP VOID
rmvkey(                            /* remove a list of keys from user      */
const CHAR *uid,                   /*   user (or keyring) to remove from   */
CHAR *keylist);                    /*   list of keys to remove             */

WGSEXP INT
lockbit(                           /* find bit number for a certain lock   */
const CHAR *lock,                  /*   lock name to look for              */
GBOOL ins);                        /*   insert if not found?               */

WGSEXP INT
keynam(                            /* validate a proposed keyname          */
const CHAR *keyname);              /*   name to validate, 0=bad 1=ok       */

WGSEXP INT
loknam(                            /* validate a proposed lock name        */
const CHAR *lokname);              /*   name to validate, 0=bad 1=ok       */

WGSEXP VOID
dlkeys(                            /* locks & keys delete account routine  */
const CHAR *uid);                  /*   user's account that was deleted    */

WGSEXP VOID
clslnk(VOID);                      /* locks & keys system shutdown routine */

WGSEXP VOID
axschg(                            /* access changed for passed User-ID    */
const CHAR *uid);

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __LOCKNKEY_H
