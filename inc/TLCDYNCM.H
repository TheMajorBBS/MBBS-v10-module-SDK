#ifndef __TLCDYNCM_H
#define __TLCDYNCM_H

const SHORT MAX_CMD_SIZEL   =16;
const SHORT MAX_CMD_SIZES   =8;

typedef struct cmdstruct {
     CHAR pszLong[MAX_CMD_SIZEL];
     CHAR pszShort[MAX_CMD_SIZES];
     SHORT fNSpace;
     GBOOL bTOnly;
     VOID (*construct)(VOID);
     VOID (*destruct)(VOID);
     SHORT (*docmdfunc)(LPCMDPARAM param);
} CMDSTRUCT, *LPCMDSTRUCT;

#endif // __TLCDYNCM_H
