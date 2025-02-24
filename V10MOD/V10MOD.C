/*****************************************************************************
 *   V10MOD.C   V1.0                        The Major BBS V10 Module Example *
 *                                                                           *
 *   Copyright (C) 2025 Galacticomm.  All Rights Reserved.                   *
 *                                                                           *
 *   Description:        A simple module to demonstrate how to               *
 *                 build a module for The Major BBS V10 with Visual          *
 *                     Studio on modern versions of Windows OSes.            *
 *                                                                           *
 *                            - Duckula / Questman 2/22/2025                 *
 *                                                                           *
 *   See LICENSE file in SDK root for terms and conditions.                  *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "V10MOD.H"

// function declarations
GBOOL user_logon(VOID);              /* Logon routine                        */
GBOOL module_main(VOID);             /* Main module routine                  */         
VOID  user_deleted(CHAR* userid);    /* Delete account routine               */
VOID  store_user_record(CHAR* userid); /* Store user record in DAT file      */
VOID  display_user_records(VOID);    /* Display users in DAT file            */
VOID  system_shutdown(VOID);         /* Shutdown routine                     */    
VOID  end_v10mod(VOID);              /* empty fcn to show EOF for debug      */

// module definition
INT usrstt;                          /* User state in this module            */
struct module V10MOD={               /* module interface block               */
     "",                             /* name used to refer to this module    */
     user_logon,                     /* user logon supplemental routine      */
     module_main,                    /* input routine if selected            */
     NULL,                           /* status-input routine if selected     */
     NULL,                           /* "injoth" routine for this module     */
     NULL,                           /* user logoff supplemental routine     */
     NULL,                           /* hangup (lost carrier) routine        */
     NULL,                           /* midnight cleanup routine             */
     user_deleted,                   /* delete-account routine               */
     system_shutdown                 /* finish-up (sys shutdown) routine     */
};

// global variables
GBOOL display_logon_msg;             /* Display logon message?               */
HMCVFILE modmb;                      /* Module message file                  */
DFAFILE* moddat;                     /* Module data file                     */

struct moddat {                      /* Example module data file structure   */
    CHAR name[UIDSIZ];               /* userid                               */
};

// begin routines

void EXPORT
init__v10mod(VOID)                   /* initialize Module                    */
{
    // register the module
    stzcpy(V10MOD.descrp, gmdnam("V10MOD.MDF"), MNMSIZ);
    usrstt = register_module(&V10MOD);

    // open the message file
    modmb = opnmsg("V10MOD.MCV");
    display_logon_msg = ynopt(DISPLOM);

    // open the data file
    moddat = dfaOpen("V10MOD.DAT", sizeof(struct moddat), NULL);
    
    // Add message to audit log that module has been loaded
    shocst(spr("MBBS V10 example module"),"Loaded version X.XX - Copyright..");
}

GBOOL EXPORT
user_logon(VOID)                     /* User Logon Message                   */
{
    // If option to display logon message is true then output message to user
    if (display_logon_msg) {
        setmbk(modmb);
        prfmsg(LOGIN);
        outprf(usrnum);
        rstmbk();
    }

    return(0);
}

GBOOL EXPORT
module_main(VOID)                   /* Main module input routine              */
{
    setmbk(modmb);
    switch (usrptr->substt) {
    case 0:
        // Check if user exists in DAT file then display menu
        store_user_record(usaptr->userid);
        prfmsg(usrptr->substt=DISPMEN);
        break;
    case DISPMEN:        
        if (sameas(margv[0], "x")) {
            prfmsg(LEAVE, usaptr->userid); // User selected to exit the module
            return(0);
        }        
        else if (sameas(margv[0], "\0") || sameas(margv[0], "")) 
            prfmsg(SHORTM);                // Display short menu on no entry
        else if (sameas(margv[0], "?")) {
            prfmsg(DISPMEN);               // Re-display the menu on ?
            break;
        }        
        else if (sameas(margv[0], "d")) 
            display_user_records();        // list users stored in V10MODULE.DAT
        else 
            prfmsg(INVSEL);                // Invalid selection message
        prfmsg(SHORTM);
        break;
    }
    outprf(usrnum);
    rstmbk();
    return 1;
}

VOID EXPORT
store_user_record(CHAR *userid)      /* Store user into DAT file              */
{
    struct moddat modd;

    dfaSetBlk(moddat);

    // If user not already in DAT file, insert them
    if (!dfaAcqEQ(&modd, userid, 0)) {
        setmem(&modd, sizeof(struct moddat), 0);
        strcpy(modd.name, userid);
        dfaInsert(&modd);
    }
    dfaRstBlk();
}

VOID EXPORT 
display_user_records(VOID)           /* List users from data file             */
{
    struct moddat modd;
    dfaSetBlk(moddat);

    INT recpos = 0;

    // Read first record in DAT file
    recpos = dfaStepLO(&modd);

    if (recpos == 1) {
        prfmsg(USRLSTS);
        prfmsg(USRLSTU, modd.name);
        while ((recpos = dfaStepNX(&modd)) != 0)
            prfmsg(USRLSTU, modd.name);        
        prfmsg(USRLSTE);
        outprf(usrnum);
    } else {
        prfmsg(NOUSERS);
        outprf(usrnum);
    }
    dfaRstBlk();
}

/*
 * If a user is deleted from the BBS, 
 * delete them from the module's database.
 */
VOID EXPORT
user_deleted(CHAR* userid)       
{
    dfaSetBlk(moddat);
    if (dfaAcqEQ(NULL, userid, 0)) 
        dfaDelete();
    dfaRstBlk();
}

VOID EXPORT
system_shutdown(VOID)                /* close MSG and DAT files for shutdown  */
{
    clsmsg(modmb);
    dfaClose(moddat);
}

VOID EXPORT
end_v10mod(VOID)                     /* used to help GALEXCEP.OUT analysis    */
{
}
