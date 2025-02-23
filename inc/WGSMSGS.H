//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x1
#define STATUS_SEVERITY_INFORMATIONAL    0x0
#define STATUS_SEVERITY_ERROR            0x2


//
// MessageId: ELOG_SERVICE_STARTED
//
// MessageText:
//
//  %1 has been successfuly started
//
#define ELOG_SERVICE_STARTED             ((DWORD)0x000003E8L)

//
// MessageId: ELOG_SERVICE_STOPPED
//
// MessageText:
//
//  %1 has been shut down
//
#define ELOG_SERVICE_STOPPED             ((DWORD)0x000003E9L)

//
// MessageId: ELOG_SERVICE_FAILED
//
// MessageText:
//
//  %1 failed. %2 %3
//
#define ELOG_SERVICE_FAILED              ((DWORD)0x800003EAL)

//
// MessageId: ELOG_SERVICE_FAILEDTOSTART
//
// MessageText:
//
//  %1 failed to start
//
#define ELOG_SERVICE_FAILEDTOSTART       ((DWORD)0x800003EBL)

//
// MessageId: ELOG_SERVICE_FAILEDTOSTOP
//
// MessageText:
//
//  %1 failed to stop
//
#define ELOG_SERVICE_FAILEDTOSTOP        ((DWORD)0x800003ECL)

//
// MessageId: ELOG_SERVICE_CANNOTSTART
//
// MessageText:
//
//  %1 failed to start %2
//
#define ELOG_SERVICE_CANNOTSTART         ((DWORD)0x800003EDL)

//
// MessageId: ELOG_SERVICE_CANNOTSTOP
//
// MessageText:
//
//  %1 failed to stop %2
//
#define ELOG_SERVICE_CANNOTSTOP          ((DWORD)0x800003EEL)

//
// MessageId: ELOG_RUNOK
//
// MessageText:
//
//  %2 has been successfuly run by %1
//
#define ELOG_RUNOK                       ((DWORD)0x000007D0L)

//
// MessageId: ELOG_FAILEDTORUN
//
// MessageText:
//
//  %1 failed to run %2
//
#define ELOG_FAILEDTORUN                 ((DWORD)0x800007D1L)

//
// MessageId: ELOG_APPISRUNNING
//
// MessageText:
//
//  %1 is running
//
#define ELOG_APPISRUNNING                ((DWORD)0x000007D2L)

//
// MessageId: ELOG_EXCEPTION
//
// MessageText:
//
//  %1 has been terminated.  Error: %2
//
#define ELOG_EXCEPTION                   ((DWORD)0x80000834L)

