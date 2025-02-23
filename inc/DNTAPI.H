/***************************************************************************
 *                                                                         *
 *   DNTAPI.H                                                              *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   Gregorian date and time utilities.                                    *
 *                                                                         *
 *   Dates are represented in eight ways:                                  *
 *        Discrete components:  the year, month, and day are each separate *
 *                              integers (range 1-9999)                    *
 *        Packed 16-bit format:  YYYYYYYMMMMDDDDD (range 1980-2107)        *
 *        Count of days since 1/1/1980 (range 1980-2099)                   *
 *        ASCII:  "MM/DD/YY" as in "01/09/89" (range 1980-2079)            *
 *        ASCII long:  "MM/DD/YYYY" as in "01/09/1989" (range 1980-2107)   *
 *        ASCII European:  "DD-MMM-YY" as in "09-JAN-89" (range 1980-2107) *
 *        ASCII European long:  "DD-MMM-YYYY" as in "09-JAN-1989"          *
 *                              (range 1980-2107)                          *
 *        Sort format: "YYYYMMDD" as in "19890109" (range 15821015-9999)   *
 *                                                                         *
 *        today() returns current day (from DOS) in Packed form            *
 *        daytoday() returns current day of the week (0=Sun, 1=Mon, etc.)  *
 *        ncdate() converts Packed to ASCII                                *
 *        ncdatel() converts Packed to ASCII long                          *
 *        ncedat() converts Packed to ASCII European                       *
 *        ncedatl() converts Packed to ASCII European long                 *
 *        dcdate() converts ASCII or ASCII long to Packed                  *
 *                          (year defaults to this year)                   *
 *        cofdat() converts Packed to Count                                *
 *        datofc() converts Count to Packed                                *
 *        ddyear() converts Packed to discrete year                        *
 *        ddmon() converts Packed to discrete month                        *
 *        ddday() converts Packed to discrete day                          *
 *        dddate() converts discrete components to Packed                  *
 *        sDateEncode() converts discrete components to Sort               *
 *        sDateEncodeDOS() converts Packed to Sort                         *
 *        sDateDecode() converts Sort to discrete components               *
 *        sDateDecodeDOS() converts Sort to Packed                         *
 *                                                                         *
 *   Time-of-day is represented in four ways:                              *
 *        Discrete components:  hour, minute, and second are each separate *
 *                              integers                                   *
 *        Packed 16-bit format:  HHHHHMMMMMMSSSSS[S] (resolution 2 sec)    *
 *        ASCII:  "HH:MM:SS" as in "23:59:58" (2 seconds before midnite)   *
 *        Sort:  "HHMMSS" as in "235957" (3 seconds before midnite)        *
 *                                                                         *
 *        now() returns the current time (from DOS) in Packed form         *
 *        nctime() converts Packed to ASCII                                *
 *        dctime() converts ASCII to Packed (seconds default to 00)        *
 *        dthour() converts Packed to discrete hour                        *
 *        dtmin() converts Packed to discrete minute                       *
 *        dtsec() converts Packed to discrete seconds                      *
 *        dttime() converts discrete components to Packed                  *
 *        sTimeEncode() converts discrete components to Sort               *
 *        sTimeEncodeDOS() converts Packed to Sort                         *
 *        sTimeDecode() converts Sort to discrete components               *
 *        sTimeDecodeDOS() converts Sort to Packed                         *
 *                                                                         *
 *                                                                         *
 *                            - RNStein  B03F  2952  01/31/88  31 JAN 88   *
 *   Combined into one file   - Craig Yap 01/16/96                         *
 *   Sort format, Y2K fixes   - J. Alvrus 19971007                         *
 *                                                                         *
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   retval=prntim(mode,time)      print <time> in format <mode>           *
 *   CHAR *retval;                 return value from prntim()              *
 *   INT mode;                     formating mode that will be used        *
 *   INT time;                     the time that will be displayed         *
 *                                                                         *
 *                                 valid <mode> values (time 11:59 pm):    *
 *                                                                         *
 *                                      0 - 23:59      10 - 23:59:59       *
 *                                      1 - 11:59p     11 - 11:59:59p      *
 *                                      2 - 11:59pm    12 - 11:59:59pm     *
 *                                      3 - 11:59 p    13 - 11:59:59 p     *
 *                                      4 - 11:59 pm   14 - 11:59:59 pm    *
 *                                      5 - 23:59      15 - 23:59:59       *
 *                                      6 - 11:59P     16 - 11:59:59P      *
 *                                      7 - 11:59PM    17 - 11:59:59PM     *
 *                                      8 - 11:59 P    18 - 11:59:59 P     *
 *                                      9 - 11:59 PM   19 - 11:59:59 PM    *
 *                                                                         *
 *   retval=prndat(mode,date,sep)  print <date> in format <mode>           *
 *   CHAR *retval;                 return value from prndat()              *
 *   INT mode;                     formating mode:                         *
 *   INT date;                     the time that will be displayed         *
 *   CHAR sep;                     the separator that will be used         *
 *                                                                         *
 *                                 valid <mode> values (date 12/31/89):    *
 *                                                                         *
 *                                      0 - 12*31                          *
 *                                      1 - Not used                       *
 *                                      2 - 12*90                          *
 *                                      3 - Not used                       *
 *                                      4 - 12*31*90                       *
 *                                      5 - Not used                       *
 *                                      6 - 31*Dec*90                      *
 *                                      7 - 31*DEC*90                      *
 *                                      8 - Dec 31, 90                     *
 *                                      9 - DEC 31, 90                     *
 *                                     10 - December 31, 90                *
 *                                     11 - DECEMBER 31, 90                *
 *                                                                         *
 *                                     12 - 12*31                          *
 *                                     13 - Not used                       *
 *                                     14 - 12*1990                        *
 *                                     15 - Not used                       *
 *                                     16 - 12*31*1990                     *
 *                                     17 - Not used                       *
 *                                     18 - 31*Dec*1990                    *
 *                                     19 - 31*DEC*1990                    *
 *                                     20 - Dec 31, 1990                   *
 *                                     21 - DEC 31, 1990                   *
 *                                     22 - December 31, 1990              *
 *                                     23 - DECEMBER 31, 1990              *
 *                                                                         *
 *                                      '*' Represents separator character *
 *                                                                         *
 *   retval=prnday(date,size)      print <date> in day format              *
 *   CHAR *retval;                 return value from prntim()              *
 *   INT date;                     the date for calculating day            *
 *   INT size;                     the maximum size of <retval>            *
 *                                                                         *
 ***************************************************************************/

#ifndef __DNTAPI_H
#define __DNTAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GCINVALIDDOT  0xFFFF       /* error ret value if dctime() fails    */
#define DATSIZ 9                   /* size of a date in MM/DD/YY format    */
#define LDATSIZ 11                 /* size of a date in MM/DD/YYYY format  */

                                   /* prnTime format identifiers           */
#define PRNT_HM          0         /*   23:59                              */
#define PRNT_HMP         1         /*   11:59p                             */
#define PRNT_HMPM        2         /*   11:59pm                            */
#define PRNT_HM_P        3         /*   11:59 p                            */
#define PRNT_HM_PM       4         /*   11:59 pm                           */
#define PRNT_HMPC        6         /*   11:59P                             */
#define PRNT_HMPMC       7         /*   11:59PM                            */
#define PRNT_HM_PC       8         /*   11:59 P                            */
#define PRNT_HM_PMC      9         /*   11:59 PM                           */
#define PRNT_HMS         10        /*   23:59:59                           */
#define PRNT_HMSP        11        /*   11:59:59p                          */
#define PRNT_HMSPM       12        /*   11:59:59pm                         */
#define PRNT_HMS_P       13        /*   11:59:59 p                         */
#define PRNT_HMS_PM      14        /*   11:59:59 pm                        */
#define PRNT_HMSPC       16        /*   11:59:59P                          */
#define PRNT_HMSPMC      17        /*   11:59:59PM                         */
#define PRNT_HMS_PC      18        /*   11:59:59 P                         */
#define PRNT_HMS_PMC     19        /*   11:59:59 PM                        */
#define PRNT_PAD         20        /*   add to zero-pad hour               */

                                   /* prnDate format identifiers           */
#define PRND_MD          0         /*   12*31                              */
#define PRND_MY          2         /*   12*90                              */
#define PRND_MDY         4         /*   12*31*90                           */
#define PRND_DMMY        6         /*   31*Dec*90                          */
#define PRND_DMMCY       7         /*   31*DEC*90                          */
#define PRND_MMDY        8         /*   Dec 31, 90                         */
#define PRND_MMCDY       9         /*   DEC 31, 90                         */
#define PRND_MMMDY       10        /*   December 31, 90                    */
#define PRND_MMMCDY      11        /*   DECEMBER 31, 90                    */
#define PRND_MYY         14        /*   12*1990                            */
#define PRND_MDYY        16        /*   12*31*1990                         */
#define PRND_DMMYY       18        /*   31*Dec*1990                        */
#define PRND_DMMCYY      19        /*   31*DEC*1990                        */
#define PRND_MMDYY       20        /*   Dec 31, 1990                       */
#define PRND_MMCDYY      21        /*   DEC 31, 1990                       */
#define PRND_MMMDYY      22        /*   December 31, 1990                  */
#define PRND_MMMCDYY     23        /*   DECEMBER 31, 1990                  */

/* macros to decode DOS Packed date */
#define ddyear(date) ((((date)>>9)&0x007F)+1980)
#define ddmon(date)   (((date)>>5)&0x000F)
#define ddday(date)    ((date)    &0x001F)
#define dddate(mon,day,year) (((mon)<<5)+(day)+(((year)-1980)<<9))

/* macros to decode DOS Packed time */
#define dthour(time)  (((time)>>11)&0x001F)
#define dtmin(time)   (((time)>> 5)&0x003F)
#define dtsec(time)   (((time)<< 1)&0x003E)
#define dttime(hour,min,sec) (((hour)<<11)+((min)<<5)+((sec)>>1))

#define isLeapYear(yr) (((yr)&3) == 0 && (((yr)%100) != 0 || ((yr)%400) == 0))
/* Note: x&3 is equivalent to x%4 for integer types but much faster */

WGSEXPV(CHAR) moname[16][4];  /* short month names (1 = JAN)          */
WGSEXPV(CHAR) strMonths[12][10]; /* long month names (0 = January)    */
WGSEXPV(CHAR) strDays[7][10]; /* long day names (0 = Sunday)          */

WGSEXP USHORT                      /*   returns current day in             */
today(VOID);                       /*   YYYYYYYMMMMDDDDD format            */

WGSEXP USHORT                      /*   returns current day of week. 0=Sun */
daytoday(VOID);                    /* gets current day of the week         */

WGSEXP USHORT                      /*   returns current time in            */
now(VOID);                         /* HHHHHMMMMMMSSSSS[S] format           */

WGSEXP const CHAR *                /*   returns ascii date string MM/DD/YY */
ncdate(                            /* encodes date into "MM/DD/YY"         */
USHORT date);                      /*   packed date                        */

WGSEXP const CHAR *                /*   returns ASCII long date string     */
ncdatel(                           /* encodes date into "MM/DD/YYYY"       */
USHORT date);                      /*   packed date                        */

WGSEXP const CHAR *                /*   returns ascii time string HH:MM:SS */
nctime(                            /* encodes time into "HH:MM:SS"         */
USHORT time);                      /*   packed time                        */

WGSEXP const CHAR *                /*   rets date string in european format*/
ncedat(                            /* encodes date to DD-MMM-YY            */
USHORT date);                      /*   packed date                        */

WGSEXP const CHAR *                /*   date string in European long format*/
ncedatl(                           /* encodes date to DD-MMM-YYYY          */
USHORT date);                      /*   packed date                        */

WGSEXP const CHAR *                /*   returns  MMM DD HH:MM              */
ncudnt(                            /* encodes Unix style date/time         */
USHORT date,                       /*   packed date                        */
USHORT time);                      /*   packed time                        */

WGSEXP VOID
dateDecode(                        /* decode date from "MM/DD[/YY[YY]]"    */
const CHAR *src,                   /*   date string                        */
INT *pYear,                        /*   buffer for year (-1 if bad)        */
INT *pMonth,                       /*   buffer for month (-1 if bad)       */
INT *pDay);                        /*   buffer for day (-1 if bad)         */

WGSEXP VOID
timeDecode(                        /* decode time from  "HH:MM[:SS]"       */
const CHAR *src,                   /*   encoded date string                */
INT *pHour,                        /*   buffer for hour (-1 if bad)        */
INT *pMinute,                      /*   buffer for minute (-1 if bad)      */
INT *pSecond);                     /*   buffer for second (-1 if bad)      */

WGSEXP USHORT                      /*   returns GCINVALIDDOT if invalid    */
dcdate(                            /* decode DOS date from "MM/DD[/YY[YY]]"*/
const CHAR *datstr);               /*   date string to convert             */

WGSEXP USHORT                      /*   returns GCINVALIDDOT if invalid    */
dctime(                            /* decode DOS time from "HH:MM[:SS]"    */
const CHAR *timstr);               /*   time string to convert             */

WGSEXP LONG                        /*   < 0 if end year before beg year    */
difYear(                           /* get # days between 1JAN of two years */
INT begYear,                       /*   beginning year                     */
INT endYear);                      /*   ending year                        */

WGSEXP LONG                        /*   < 0 if end date before beg date    */
difDate(                           /* compute # days between dates         */
INT begYear,                       /*   year component of first date       */
INT begMonth,                      /*   month component of first date      */
INT begDay,                        /*   day component of first date        */
INT endYear,                       /*   year component of second date      */
INT endMonth,                      /*   month component of second date     */
INT endDay);                       /*   day component of second date       */

WGSEXP VOID
addDaysToDate(                     /* get date by adding # days to base    */
LONG nDays,                        /*   # days to add (can be negative)    */
INT *pYear,                        /*   base year (updated w/ new year)    */
INT *pMonth,                       /*   base month (updated w/ new month)  */
INT *pDay);                        /*   base day (updated w/ new day)      */

WGSEXP USHORT                      /*   returns number of days since 1/1/80*/
cofdat(                            /* Compute number of days since 1/1/80  */
USHORT date);                      /*   date in DOS format:YYYYYYYMMMMDDDDD*/

WGSEXP USHORT                      /*   returns packed date                */
datofc(                            /* Compute date form YYYYYYYMMMMDDDDD   */
USHORT count);                     /*   count of days since 1/1/80         */

WGSEXP CHAR *                      /*   returns pointer to buffer          */
prnDate(                           /* form formatted date string           */
INT year,                          /*   year component (1-9999)            */
INT month,                         /*   month component (1-12)             */
INT day,                           /*   day component (1-31)               */
CHAR *buf,                         /*   buffer to receive formatted date   */
size_t bufSiz,                     /*   size of buffer                     */
INT mode,                          /*   format mode                        */
CHAR sep);                         /*   separator character                */

WGSEXP CHAR *                      /*   returns pointer to buffer          */
prnTime(                           /* form formatted time string           */
INT hour,                          /*   hour component (0-23)              */
INT minute,                        /*   minute component (0-59)            */
INT second,                        /*   second component (0-59)            */
CHAR *buf,                         /*   buffer to receive formatted time   */
size_t bufSiz,                     /*   size of buffer                     */
INT mode);                         /*   format mode                        */

WGSEXP INT                         /*   day of week (0 = Sun, <0 = error)  */
dayFromDate(                       /* get day of week given date           */
INT year,                          /*   year component (1-9999)            */
INT month,                         /*   month component (1-12)             */
INT day);                          /*   day component (1-31)               */

WGSEXP const CHAR *                /*   returns string in requested format */
prntim(                            /* print <time> in format <mode>        */
INT mode,                          /*   format mode                        */
USHORT time);                      /*   time to format                     */

WGSEXP const CHAR *                /*   returns string in requested format */
prndat(                            /* print <date> in format <mode>        */
INT mode,                          /*   format mode                        */
USHORT date,                       /*   date to format                     */
CHAR sep);                         /*   separator character                */

WGSEXP const CHAR *                /*   returns string in day format       */
prnday(                            /* print <date> in day format           */
USHORT date,                       /*   date to format                     */
INT size);                         /*   size of buffer                     */

WGSEXP GBOOL
validDate(                         /* check for valid date                 */
INT year,                          /*   year component (1-9999)            */
INT month,                         /*   month component (1-12)             */
INT day);                          /*   day component (1-31)               */

WGSEXP GBOOL
validTime(                         /* check for valid time                 */
INT hour,                          /*   hour component (0-23)              */
INT minute,                        /*   minute component (0-59)            */
INT second);                       /*   second component (0-59)            */

WGSEXP GBOOL
validDateDOS(                      /* check for valid DOS date             */
USHORT dosDate);                   /*   DOS packed date                    */

WGSEXP GBOOL
validTimeDOS(                      /* check for valid DOS time             */
USHORT dosTime);                   /*   DOS packed time                    */

WGSEXP INT                         /*   number of last day (e.g. Jan = 31) */
lastDayOfMonth(                    /* get highest day in given month/year  */
INT month,                         /*   number of month (1-12)             */
INT year);                         /*   year in question (1-9999)          */

WGSEXP CHAR *                      /*   returns pointer to buffer          */
sDateEncode(                       /* encode date to "YYYYMMDD"            */
INT year,                          /*   year component (1-9999)            */
INT month,                         /*   month component (1-12)             */
INT day,                           /*   day component (1-31)               */
CHAR *buf,                         /*   buffer to receive encoded date     */
size_t bufSiz);                    /*   size of buffer                     */

WGSEXP CHAR *                      /*   returns pointer to buffer          */
sTimeEncode(                       /* encode time to "HHMMSS"              */
INT hour,                          /*   hour component (0-23)              */
INT minute,                        /*   minute component (0-59)            */
INT second,                        /*   second component (0-59)            */
CHAR *buf,                         /*   buffer to receive encoded time     */
size_t bufSiz);                    /*   size of buffer                     */

WGSEXP CHAR *                      /*   returns pointer to buffer          */
sDateEncodeDOS(                    /* encode DOS date to "YYYYMMDD"        */
USHORT dosDate,                    /*   DOS packed date                    */
CHAR *buf,                         /*   buffer to receive encoded date     */
size_t bufSiz);                    /*   size of buffer                     */

WGSEXP CHAR *                      /*   returns pointer to buffer          */
sTimeEncodeDOS(                    /* encode DOS time to "HHMMSS"          */
USHORT dosTime,                    /*   DOS packed time                    */
CHAR *buf,                         /*   buffer to receive encoded time     */
size_t bufSiz);                    /*   size of buffer                     */

WGSEXP VOID
sDateDecode(                       /* decode "YYYYMMDD"                    */
const CHAR *src,                   /*   encoded date string                */
INT *pYear,                        /*   buffer for year (-1 if bad)        */
INT *pMonth,                       /*   buffer for month (-1 if bad)       */
INT *pDay);                        /*   buffer for day (-1 if bad)         */

WGSEXP VOID
sTimeDecode(                       /* decode "HHMMSS"                      */
const CHAR *src,                   /*   encoded date string                */
INT *pHour,                        /*   buffer for hour (-1 if bad)        */
INT *pMinute,                      /*   buffer for minute (-1 if bad)      */
INT *pSecond);                     /*   buffer for second (-1 if bad)      */

WGSEXP USHORT                      /*   DOS date or GCINVALIDDOT           */
sDateDecodeDOS(                    /* decode "YYYYMMDD" to DOS format      */
const CHAR *src);                  /*   encoded date string                */

WGSEXP USHORT                      /*   DOS time or GCINVALIDDOT           */
sTimeDecodeDOS(                    /* decode "HHMMSS" to DOS format        */
const CHAR *src);                  /*   encoded time string                */

WGSEXP VOID
sDecodeDT(                         /* decode "YYYYMMDD[ ]HHMMSS"           */
const CHAR *src,                   /*   encoded date string                */
INT *pYear,                        /*   buffer for year (-1 if bad)        */
INT *pMonth,                       /*   buffer for month (-1 if bad)       */
INT *pDay,                         /*   buffer for day (-1 if bad)         */
INT *pHour,                        /*   buffer for hour (-1 if bad)        */
INT *pMinute,                      /*   buffer for minute (-1 if bad)      */
INT *pSecond);                     /*   buffer for second (-1 if bad)      */

WGSEXP VOID
sDecodeDTDOS(                      /* decode "YYYYMMDD[ ]HHMMSS" to DOS fmt*/
const CHAR *src,                   /*   encoded date string                */
USHORT *pDate,                     /*   buf for date (GCINVALIDDOT if bad) */
USHORT *pTime);                    /*   buf for time (GCINVALIDDOT if bad) */

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

#endif                             /* __DNTAPI_H                           */