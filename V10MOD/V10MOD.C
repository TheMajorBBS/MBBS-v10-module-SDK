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
 *   This example C file is free for you to use, however no rights to the    *
 *   compiled library files are assigned beyond the right to use them to     *
 *   build your modules. Any other use including, but not limited to,        *
 *   decompilation, reverse-engineering, etc. is prohibited.                 *
 *                                                                           *
 *****************************************************************************/

#include "gcomm.h"
#include "majorbbs.h"
#include "V10MOD.H"

// function declarations
GBOOL lonmod(VOID);                 /* Logon routine                        */
GBOOL modrou(VOID);                 /* Main module routine                  */         
VOID  delrou(CHAR* userid);         /* Delete account routine               */
VOID storeUserRecord(CHAR* usr);    /* Store user record in DAT file        */
VOID displayUserRecords(VOID);      /* Display users in DAT file            */
VOID modcls(VOID);                  /* Shutdown routine                     */    
VOID end_v10mod(VOID);              /* empty fcn to show EOF for debug      */

// module definition
INT usrstt;                         /* User state in this module            */
struct module V10MOD={              /* module interface block               */
     "",                            /* name used to refer to this module    */
     lonmod,                        /* user logon supplemental routine      */
     modrou,                        /* input routine if selected            */
     NULL,                          /* status-input routine if selected     */
     NULL,                          /* "injoth" routine for this module     */
     NULL,                          /* user logoff supplemental routine     */
     NULL,                          /* hangup (lost carrier) routine        */
     NULL,                          /* midnight cleanup routine             */
     delrou,                        /* delete-account routine               */
     modcls                         /* finish-up (sys shutdown) routine     */
};

// global variables
INT displom;                        /* Display logon message?               */
HMCVFILE modmb;                     /* Module message file                  */
DFAFILE* moddat;                    /* Module data file                     */

struct moddat {                     /* Example module data file structure   */
    CHAR name[UIDSIZ];              /* userid                               */            
};

// begin routines

void EXPORT
init__v10mod()                      /* initialize Module                    */
{
    // register the module
    stzcpy(V10MOD.descrp, gmdnam("V10MOD.MDF"), MNMSIZ);
    usrstt = register_module(&V10MOD);

    // open the message file
    modmb = opnmsg("V10MOD.MCV");
    displom = ynopt(DISPLOM);

    // open the data file
    moddat = dfaOpen("V10MOD.DAT", sizeof(struct moddat), NULL);
    
    // Add message to audit log that module has been loaded
    shocst(spr("MBBS V10 example module"),"Loaded version X.XX - Copyright..");
}

GBOOL EXPORT
lonmod(VOID)                        /* User Logon Message                   */
{
    // If option to display logon message is true then output message
    // to user
    if (displom) {
        setmbk(modmb);
        prfmsg(LOGIN);
        outprf(usrnum);
        rstmbk();
    }

    return(0);
}

GBOOL EXPORT
modrou(VOID)                        /* Main module routine                  */
{
    setmbk(modmb);
    switch (usrptr->substt) {
    case 0:
        // Check if user exists in DAT file then display menu
        storeUserRecord(usaptr->userid);
        prfmsg(usrptr->substt=DISPMEN);
        break;
    case DISPMEN:
        // User selected to exit the module
        if (sameas(margv[0], "x")) {
            prfmsg(LEAVE, usaptr->userid);
            return(0);
        }
        // Display short menu on no entry
        else if (sameas(margv[0], "\0") || sameas(margv[0], "")) {
            prfmsg(SHORTM);
        }
        // Re-display the menu on ?
        else if (sameas(margv[0], "?")) {
            prfmsg(DISPMEN);
            break;
        }
        // Call routine to show users that are strored in V10MODULE.DAT
        else if (sameas(margv[0], "d")) {
            displayUserRecords();
        }
        // Invalid selection message
        else {
            prfmsg(INVSEL);
        }
        prfmsg(SHORTM);
        break;
    }
    outprf(usrnum);
    rstmbk();
    return 1;
}

VOID EXPORT
storeUserRecord(CHAR *usr)     /* Store user into DAT file */
{
    struct moddat modd;

    dfaSetBlk(moddat);

    // If user not already in DAT file, insert them
    if (!dfaAcqEQ(&modd, usr, 0)) {
        setmem(&modd, sizeof(struct moddat), 0);
        strcpy(modd.name, usr);
        dfaInsert(&modd);
    }
    dfaRstBlk();
}

VOID EXPORT 
displayUserRecords(VOID)
{
    struct moddat modd;
    dfaSetBlk(moddat);

    INT recpos = 0;

    // Read first record in DAT file
    recpos = dfaStepLO(&modd);

    if (recpos == 1)
    {
        prfmsg(USRLSTS);
        prfmsg(USRLSTU, modd.name);
        while ((recpos = dfaStepNX(&modd)) != 0)
        {
            prfmsg(USRLSTU, modd.name);
        };
        prfmsg(USRLSTE);
        outprf(usrnum);
    }
    else
    {
        prfmsg(NOUSERS);
        outprf(usrnum);
    }
    dfaRstBlk();
}

VOID EXPORT
delrou(CHAR* userid)                /* if a user is deleted from the BBS, delete them if they're in our file */
{
    dfaSetBlk(moddat);
    if (dfaAcqEQ(NULL, userid, 0)) dfaDelete();
    dfaRstBlk();
}

VOID EXPORT
modcls(VOID)                        /* close MSG and DAT files for shutdown */
{
    clsmsg(modmb);
    dfaClose(moddat);
}

VOID EXPORT
end_v10mod(VOID)
{
}
