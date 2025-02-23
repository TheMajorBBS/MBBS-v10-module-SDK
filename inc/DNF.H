/***************************************************************************
 *                                                                         *
 *   DNF.H                                                                 *
 *                                                                         *
 *   Copyright (c) 1996-1997 Galacticomm, Inc.    All Rights Reserved.     *
 *                                                                         *
 *   DynaFiles, text files with special symbols and tables that can be     *
 *   converted and expanded at runtime.                                    *
 *                                                                         *
 *                                              - R. Stein  8/7/96         *
 *                                                                         *
 ***************************************************************************/

#ifndef __DNF_H
#define __DNF_H

#include <fstream.h>
#include <strstrea.h>
#include <iomanip.h>

#if defined( PPFILE )
#include "htmlpp.h"
#endif

struct dnfSwath;                   // range of text in a random-access stream
class dnfHandler;                  // DynaFile processing session
class dnfMap;                      // DynaFile info (changes when file changes)
class dnfStep;                     // one step in a DynaFile
class acthUserID;

enum DNFTYPE {                     // type of step:
     DNFTYPE_MIN,                  //   (less than minimum)
     DNFMAPEND,                    //   end of map
     DNFWATCH,                     //   next symbol to watch for
     DNFTABLE,                     //   beginning of table
     DNFCOLUMN,                    //   column of table
     DNFTABLEEND,                  //   end of table
     DNFCUT,                       //   bytes to cut, conditionally paste
     DNFTYPE_MAX                   //   (more than maximum)
};

// Step ID's are mainly used for dnfHandler::process() return codes, but they
// are also stored in dnfStep instances.

typedef SHORT DNFID;               // step identification code (agent's enum)
enum DNFIDSPECIAL {                // internally defined IDs (events, etc.)
     DNFNONE        =-1,           // step has no special ID (dnfStep only)
     DNFBEGIN       =-2,           // DynaFile processing is beginning
     DNFCONTINUE    =-3,           // process() has nothing 2 report this cycle
     DNFEND         =-4,           // end of DynaFile (stop calling process())
     DNFROWBEGIN    =-5,           // beginning of each row of a table
     DNFROWEND      =-6,           // end of each row of a table
};

typedef SHORT DNFSTEP;             // index into the steps of a map
enum DNFSTEPSPECIAL {
     DNFNOSTEP      =-1,           // step index not available
};

enum DNFMAPSTATUS {                // internal dnfMap::status
     DNFUNPRIMED,                  // map needs priming
     DNFPRIMING,                   // someone is in the process of priming map
     DNFPRIMED,                    // map primed, DynaFile ready for action
     DNFERROR,                     // error detected while priming map
};

enum DNFHANDLERSTATE {             // internal dnfHandler::process() state code
     DNFSTART,                     // starting
     DNFPRIMEWAIT,                 // waiting for another party to prime map
     DNFPRIMEDO,                   // actively doing the priming of the map
     DNFFILESTART,                 // starting in on the template file
     DNFFILEPROC,                  // working through the template file
     DNFENDED,                     // done handling DynaFile
};

//////////////////////////
// DNF handling classes //
//////////////////////////

struct EXPORT dnfSwath {           // A swath of bytes in a file or memory region
     ULONG pos;                    // offset of starting position (0-based)
     ULONG len;                    // number of bytes in swath

     VOID
     copy(                         // copy swath from one stream to another
#if defined( PPFILE )
     ppFile &sfrom,
#else
     istream& sfrom,               //   source stream (random)
#endif
     ostream& sto) const;          //   destination stream (sequential)

     VOID
     tvbCopy(                      // copy swath stream-stream w/text vars
#if defined( PPFILE )
     ppFile & sfrom,
#else
     istream& sfrom,               //   source stream (random)
#endif
     ostream& sto) const;          //   destination stream (sequential)

     friend
     ostream&
     operator<<(                   // output swath info for debugging
     ostream& out,                 //   sequential text stream
     const dnfSwath& dsw);
};

class EXPORT dnfHandler {          // handle (output) a DynaFile (one session)

public:
#if defined( PPFILE )
     dnfHandler(                   // constructor
     dnfMap& _map,                 //   map of DynaFile
     ostream& _dnfout,             //   seq stream where output is to be sent
     acthUserID *usr);
#endif

     dnfHandler(                   // constructor
     dnfMap& _map,                 //   map of DynaFile
     ostream& _dnfout);            //   seq stream where output is to be sent

     ~dnfHandler();                // destructor
private:
     dnfHandler();                 // no default constructor
     dnfHandler(                   // no copy constructor
     dnfHandler& dh);
     VOID operator=(               // no assignment operator
     dnfHandler& dh);


public:                            // public functions:

     DNFID                         //   returns ID of what to do this step
     process();                    // process the dynaFile, one step at a time

     INT
     rowNumber() const;            // *inside* a table, indicates row, 0 to N-1
                                   // *after* a table, indicates total # rows

     VOID
     tableDone();                  // application declares a table done

     VOID
     sayAgain();                   // make next process give same return code

     VOID
     doTextVars(                   // do translate Text Variables (tvb.h)
     GBOOL onoff);                 //   TRUE=translate (default) FALSE=turn off

     VOID
     paste();                      // insert text cut by DNFCUT

     DNFHANDLERSTATE               //   e.g. DNFENDED, see enumeration
     getState() const;             // get current state of handler

     DNFSTEP                       //   0 to dnfMap::ntsteps-1
     getStep() const;              // get index of step in map's array of steps

     inline
     dnfMap const &
     getMap() const                // get map used by handler
     {
          return(map);
     }

private:                           // private variables:
     ostream& dnfout;              // output stream
     dnfMap& map;                  // DynaFile map structure
     DNFSTEP istep;                // index of step within map's array of steps
     DNFHANDLERSTATE state;        // current state of handler
#if defined( PPFILE )
     ppFile *minp;
#else
     ifstream *minp;               // reading from file
#endif
     INT _rowNumber;               // count of rows of the table (0-based)
     GBOOL _tableDone;             // flag set by tableDone() member
     GBOOL intable;                // TRUE=in a table, FALSE=outside
     GBOOL _sayAgain;              // flag set by sayAgain() member
     GBOOL _doTextVars;            // flag set by doTextVars() member
     DNFID ridlast;                // last return code from process()
     INT endcount;                 // detects unheeded DNFEND of process()

#if defined( PPFILE )
     acthUserID *m_usr;
#endif

private:                           // private functions:
     VOID
     closein();                    // close the input file

     VOID
     copy(                         // copy swath from template to output stream
     dnfSwath& swat);              //   swath (range of bytes)
};

class EXPORT dnfMap {              // map of DynaFile

public:
#if defined( PPFILE )
     dnfMap(                       // map constructor
     const CHAR *_filepath,        //   path of DynaFile (template file)
     const CHAR *_filedesc,        //   text description of DynaFile
     dnfStep *_step,               //   array of DynaFile steps
     acthUserID *usr);
#endif

     dnfMap(                       // map constructor
     const CHAR *_filepath,        //   path of DynaFile (template file)
     const CHAR *_filedesc,        //   text description of DynaFile
     dnfStep *_step);              //   array of DynaFile steps

     ~dnfMap();                    // destructor

private:
     dnfMap();                     // no default constructor
     dnfMap(                       // no copy constructor
     dnfMap& dm);
     VOID operator=(               // no assignment operator
     dnfMap& dm);

     void
     init(                         // common init function
     const CHAR *_filepath,        //   file path
     const CHAR *_filedesc);       //   file description

public:
     VOID
     primeInit();                  // prepare for priming the map

     GBOOL                         //   TRUE=call again FALSE=done
     primeDo();                    // continue priming the map

     VOID
     primeQuit();                  // abort priming the map before done

     GBOOL                         //   TRUE=errors detected
     isbad() const;                // did priming the map produce any errors?

     GBOOL                         //   same return as isbad()
     errReport(                    // report priming errors to text stream
     ostream& eout);

     const dnfStep&
     getStep(                      // get one step from the map's step array
     DNFSTEP ist) const;           //   index, must be 0 to nsteps [sic]

     DNFMAPSTATUS                  //   e.g. DNFUNPRIMED, DNFPRIMED, see enum
     getStatus() const;            // get status of map

     friend
     ostream&
     operator<<(                   // output map info for debugging
     ostream& out,                 //   sequential text stream
     dnfMap& dm);

     inline
     CHAR const *
     getFile() const               // get file handled by this map
     {
          return(filepath);
     }

     inline
     CHAR const *
     getDesc() const               // get description of this map
     {
          return(filedesc);
     }

     friend class dnfHandler;      // handlers are privy to map internals
     friend dnfStep * dnfCopySteps(dnfMap const *);

private:
     const CHAR *filepath;         // path of DynaFile (template)
     const CHAR *filedesc;         // description of DynaFile
#if defined( PPFILE )
     ppFile *minp;
#else
     ifstream *minp;               // reading from file
#endif
     dnfStep *step;                // array of steps for the map
     DNFSTEP nsteps;               // not including DNFMAPEND step
     DNFSTEP istep;                // primeInit()/primeDo() step in map
     SHORT isym;                   // primeInit()/primeDo() symbol in step
     DNFSTEP iref;                 // primeInit()/primeDo() alternate step
     ULONG lastpos;                // primeInit()/primeDo() symbol ending point
     ULONG filegmt;                // file modified, seconds since 1/1/70 GMT
     ULONG nowgmt;                 // prime started, seconds since 1/1/70 GMT
     ostrstream *emg;              // accumulated error messages, if any
     DNFMAPSTATUS status;          // priming status (see enum)
     GBOOL scanning;               // primeInit()/primeDo() scanmem'ing DynaFile

#if defined( PPFILE )
     acthUserID *m_usr;
#endif

private:
     VOID
     scanInit();                   // internal work of primeInit()

     GBOOL                         //   FALSE=done
     scanDo();                     // internal work of primeDo()

     VOID
     symInit();                    // prepare to find symbols in DynaFile

     GBOOL                         //   FALSE=done
     symDo();                      // find next symbol in DynaFile

     GBOOL                         //   TRUE=ok, FALSE=problems
     presolve();                   // priming a map, final resolutions
                                   // e.g. table prefixes and postfixes
     VOID
     closein();                    // close input file

     VOID
     errDelete();                  // delete accumulated error messages

     VOID
     errReset();                   // delete error messages & prepare for more
};

class EXPORT dnfStep {             // one step in a DynaFile (a symbol and the
                                   // preceding inter-symbol swath)
public:
     dnfStep(                      // step constructor
     DNFTYPE _type,                //   type of step (see enumeration)
     DNFID _id=DNFNONE,            //   application IDs, internally defined IDs
     const CHAR *sym0=NULL,        //   symbol sought (1st row if DNFCOLUMN)
     const CHAR *sym1=NULL);       //   symbol sought for 2nd row (DNFCOLUMN)

     ~dnfStep();                   // destructor

private:
     dnfStep(                      // no copy constructor
     dnfStep &ds);
     VOID operator=(               // no assignment operator
     dnfStep &ds);

     dnfStep();                    // default constructor (internal use only)

     void
     init(                         // constructor work
     DNFTYPE _type,                //   type of step (see enumeration)
     DNFID _id,                    //   application IDs, internally defined IDs
     const CHAR *sym0,             //   symbol sought (1st row if DNFCOLUMN)
     const CHAR *sym1);            //   symbol sought for 2nd row (DNFCOLUMN)

public:
     DNFTYPE                       //   e.g. DNFCOLUMN, DNFMAPEND (see enum)
     gettype() const;              // get type of step

     friend
     ostream&
     operator<<(                   // output step info for debugging
     ostream& out,                 //   sequential text stream
     const dnfStep& ds);

     friend class dnfMap;          // maps are privy to step internals
     friend class dnfHandler;      // handlers are privy to step internals
     friend dnfStep * dnfCopySteps(dnfMap const *);

private:
     DNFTYPE type;                 // e.g. DNFCOLUMN, DNFMAPEND (see enum)
     DNFID id;                     // application enumeration, or internal code
     DNFSTEP ref;                  // index of some other step
     const CHAR *sym[2];           // symbol(s) of step (2 rows for DNFCOLUMN)
     dnfSwath preswath[2];         // swath of bytes preceding symbol(s)
};

#endif // __DNF_H
