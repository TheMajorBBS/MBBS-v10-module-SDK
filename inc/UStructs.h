#ifndef __USTRUCTS_H
#define __USTRUCTS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define KEYSIZ 16             /* key (and class) name size (ditto)         */
#define XMSGSZ 640            /* size for class exit messages              */
#define UIDSIZ 30             /* user-id size (including trailing zero)    */
#define PSWSIZ 10             /* password size (ditto)                     */
#define NADSIZ 30             /* name/address line size (ditto)            */
#define PHOSIZ 16             /* phone number field size (ditto)           */
#define XRFSIZ 15             /* maximum size for uid cross ref strings    */
#define AXSSIZ 7              /* number of ints for "access" info          */
#define DATSIZ 9              /* number of bytes for internal date format  */

#ifndef __USRACC_
#define __USRACC_
struct usracc {
    CHAR userid[UIDSIZ];     /* user-id                                   */
    CHAR psword[PSWSIZ];     /* password                                  */
    CHAR usrnam[NADSIZ];     /* user name                                 */
    CHAR usrad1[NADSIZ];     /* address line 1 (company)                  */
    CHAR usrad2[NADSIZ];     /* address line 2                            */
    CHAR usrad3[NADSIZ];     /* address line 3                            */
    CHAR usrad4[NADSIZ];     /* address line 4                            */
    CHAR usrpho[PHOSIZ];     /* phone number                              */
    CHAR systyp;             /* system type code                          */
    CHAR usrprf;             /* user preference flags                     */
    CHAR ansifl;             /* ANSI flags                                */
    CHAR scnwid;             /* screen width in columns                   */
    CHAR scnbrk;             /* screen length for page breaks             */
    CHAR scnfse;             /* screen length for FSE stuff               */
    CHAR age;                /* user's age                                */
    CHAR sex;                /* user's sex ('M' or 'F')                   */
    USHORT credat;           /* account creation date                     */
    USHORT usedat;           /* date of last use of account               */
    SHORT csicnt;            /* classified-ad counts used so far          */
    SHORT flags;             /* various saved bit flags                   */
    SHORT access[AXSSIZ];    /* array of remote sysop access bits         */
    LONG emllim;             /* e-mail limit reached so far (new/old bdy) */
    CHAR prmcls[KEYSIZ];     /* class to return user to if necessary      */
    CHAR curcls[KEYSIZ];     /* current class of this user                */
    LONG timtdy;             /* time user has been online today (in secs) */
    USHORT daystt;           /* days left in this class (if applicable)   */
    USHORT fgvdys;           /* days since debt was last "forgiven"       */
    LONG creds;              /* credits available or debt (if negative)   */
    LONG totcreds;           /* total credits ever posted (paid & free)   */
    LONG totpaid;            /* total credits ever posted (paid only)     */
    CHAR birthd[DATSIZ];     /* this user's birthday date                 */
#ifdef GCV2
#define USRACCSPARE (338-301) /* spare space, decrease when adding entries */
    CHAR spare[USRACCSPARE]; /* former spare space                        */
#endif // GCV2
};
#endif // __USRACC_

                              /* ansifl bit definitions                    */
#define ANSON       1         /*   ANSI on=1; off=0                        */
#define ANSMAN      2         /*   ANSI manual override (0=auto sensing)   */

                              /* flags bit definitions                     */
#define HASMST      1         /*   user has the "MASTER" key for the svr   */
#define UNDAXS      2         /*   this account cannot be deleted          */
#define SUSPEN      4         /*   this account is "suspended"             */
#define DELTAG      8         /*   this account is tagged for deletion     */
#define GOINVB      16        /*   this account is "invisible" upon logon  */

                              /* usrprf bit definitions                    */
#define PRFLIN      1         /*   always use line editor?   yes=1         */

#define ALTEMLSIZ   50        /* alternate email address size              */
#define HINTSIZ     80        /* password hint size                        */

#ifndef __UACCEXT__
#define __UACCEXT__
struct uaccext {              /* extended user account info                */
    CHAR userid[UIDSIZ];     /*   User-ID linked to                       */
    CHAR alteml[ALTEMLSIZ];  /*   alternate email address                 */
    CHAR pwdhint[HINTSIZ];   /*   password hint                           */
};
#endif /* __UACCEXT__ */

#ifndef __ACCLASS_
#define __ACCLASS_
struct acclass {              /* accounting class structure                */
     CHAR clname[KEYSIZ];     /*   class name                              */
     CHAR nxtcls[4][KEYSIZ];  /*   class to return to when expires         */
     SHORT limcal;            /*   limit per call (-1=no limit)            */
     SHORT limday;            /*   limit per day (-1=no limit)             */
     SHORT dftday;            /*   default days before expiring (-1=never) */
     LONG dbtlmt;             /*   debt limit (0=none)                     */
     SHORT fgvday;            /*   wait how many days before "forgiving"   */
     SHORT idlday;            /*   inactive days before delete (-1=never)  */
     SHORT flags;             /*   general bit flags                       */
     LONG seconds;            /*   seconds used so far this month          */
     USHORT users;            /*   total number of users in this class     */
     CHAR msgs[2][XMSGSZ];    /*   exiting class messages                  */
#ifdef GCV2
     CHAR spare[2032-2022];   /*   former spare space                      */
#endif // GCV2
};
#endif // __ACCLASS_H
                              /* indexes for nxtcls[] when a user...       */
#define DOUTTIM 0             /*   is out of time for the day              */
#define DLOAFER 1             /*   hasn't logged in for x number of days   */
#define DEXPIRE 2             /*   has been around x number of days        */
#define DCREDIT 3             /*   has/doesn't have credits                */

                              /* struct acclass bit flag definitions       */
#define KCKOFF 1              /*   out of time: knock the user offline     */
#define CLSCHG 2              /*   out of time: temporarily change class   */
#define NOCRED 4              /*   expire when: credits < 1                */
#define DBTLMT 8              /*   expire when: user reaches a debt limit  */
#define HASCRD 16             /*   expire when: credits > 0                */
#define DAYEXP 32             /*   expire when: x number of days passes    */
#define IDLEXP 64             /*   expire when: no log on for x # of days  */
#define MONDAY 128            /*   forgive: every Monday                   */
#define FSTMTH 256            /*   forgive: on the first of each month     */
#define NUMDAY 512            /*   forgive: every x number of days         */
#define HITLMT 1024           /*   forgive: when they hit their debt limit */
#define REPDBT 2048           /*   report debt when forgiven?              */
#define CRDXMT 4096           /*   this class exempt from credit charges?  */

struct clstab {               /* structure for in-memory class table       */
     CHAR clname[KEYSIZ];     /*   class name                              */
     CHAR nxtcls[4][KEYSIZ];  /*   class to return to when expires         */
     SHORT limcal;            /*   limit per call (-1=no limit)            */
     SHORT limday;            /*   limit per day (-1=no limit)             */
     SHORT dftday;            /*   default days before expiring (-1=never) */
     LONG dbtlmt;             /*   debt limit (-1=none)                    */
     USHORT fgvday;           /*   wait how many days before "forgiving"   */
     SHORT idlday;            /*   inactive days before delete (-1=never)  */
     SHORT flags;             /*   general bit flags                       */
     LONG seconds;            /*   seconds used so far this month          */
     USHORT users;            /*   total number of users in this class     */
     struct clstab *next;     /*   ptr to next element in linked list      */
};

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif // __USTRUCTS_H
