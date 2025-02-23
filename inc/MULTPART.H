/***************************************************************************
 *                                                                         *
 *   MULTPART.H                                                            *
 *                                                                         *
 *   Copyright (c) 1997 Galacticomm, Inc.    All rights reserved.          *
 *                                                                         *
 *   Multipart partitioner.                                                *
 *                                                                         *
 *                                                - RNStein  1/8/97        *
 *                                                                         *
 ***************************************************************************/

enum MPSTATUS {MPOK,               // partition successful
               MPNOCLOSE};         // no closing boundary (preamble()=entirity)

class EXPORT multiPart {           // partition a multipart body, RFC 1521
public:
     static const string hdrCRLF;  // terminator of header fields (lines)

     multiPart::multiPart(         // construct a multiPart inquisition
     racsit& mpbegin,              //   \ outer body, eg from HTTP request
     racsit& mpend,                //   / as a stream (file or memory buffer)
     string& boundary);            //   boundary from outer Content-Type header
private:
     multiPart();                  // no default construction allowed

public:
     MPSTATUS
     multiPart::status() const;    // status of partition effort

     INT
     multiPart::nparts() const;    // Number of parts

     string *                      //   ""=none, CALLER MUST DELETE!
     multiPart::partHeaderLine(    // Get a header line from a part
     int part,                     //   part index, 0 to nparts()-1
     int line) const;              //   line within the part, 0 to #lines-1

     racsRange                     //   body part (within original outer range)
     multiPart::partBody(          // get iterators for an inner body part
     int part) const;              //   part index, 0 to nparts()-1

     racsRange
     multiPart::preamble() const;  // stuff before 1st boundary
                                   //   (RFC 1521 page 31)
     racsRange
     multiPart::epilogue() const;  // stuff after last boundary
                                   //   (RFC 1521 page 31)
     friend
     ostream&
     operator<<(                   // output partition report for debugging
     ostream& out,                 //   sequential text stream
     const multiPart& mp);         //   partitioned multiPart stream

private:
     vector<racsit> pieces;        // raw cut-points within the outer body:
                                   // built: [beginning, [boundary),..., end)
                                   // used:  [preamble), [part),..., [epilogue)
     vector<vector<racsRange> > headers; // inner header lines for each part
     vector<racsRange> bodies;     // inner bodies
     INT _nparts;                  // number of parts (same as bodies.size())
     MPSTATUS _status;             // status of partitioning effort
};

