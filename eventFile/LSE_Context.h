/**
 * @class eventFile::LSE_Context
 *
 * @brief Class representing the acquisition context of the event.
 *
 * @author Bryson Lee <blee@slac.stanford.edu>
 *
 * $Header$
 */

#ifndef EVENTFILE_LSE_CONTEXT_HH
#define EVENTFILE_LSE_CONTEXT_HH

#include "eventFile/LSE_GemTime.h"

namespace eventFile {

  struct FromCcsds {
    FromCcsds() {};
    void dump( const char* pre, const char* post ) const;
    int scid;
    int apid;
    double utc;
  };

  struct FromTimetone {
    FromTimetone() {};
    void dump( const char* pre, const char* post ) const;
    unsigned timeSecs;
    LSE_GemTime timeHack;
    unsigned incomplete;
    unsigned flywheeling;
    bool missingTimeTone;
    bool missingCpuPps;
    bool missingLatPps;
    bool earlyEvent;
    bool missingGps;
  };

  struct FromScalers {
    FromScalers() {};
    void dump( const char* pre, const char* post ) const;
    unsigned long long elapsed;
    unsigned long long livetime;
    unsigned long long prescaled;
    unsigned long long discarded;
    unsigned long long sequence;
    unsigned long long deadzone;
  };

  struct FromRun {
    FromRun() {};
    void dump( const char* pre, const char* post ) const;
    int platform;
    int origin;
    unsigned groundId;
    unsigned startedAt;
    char platformTxt[16];
    char originTxt[16];
  };

  struct FromOpen {
    FromOpen() {};
    void dump( const char* pre, const char* post ) const;
    unsigned modeChanges;
    unsigned datagrams;
    int action;
    int reason;
    int crate;
    int mode;
    char actionTxt[16];
    char reasonTxt[16];
    char crateTxt[16];
    char modeTxt[16];
  };

  struct FromClose {
    FromClose() {};
    void dump( const char* pre, const char* post ) const;
    int action;
    int reason;
    char actionTxt[16];
    char reasonTxt[16];
  };

  struct LSE_Context {

    LSE_Context() {};
    void dump() const;

    // from the enclosing CCSDS packet stream
    FromCcsds ccsds;

    // from the current timetone
    FromTimetone current;

    // from the previous timetone
    FromTimetone previous;

    // from the scalers
    FromScalers scalers;

    // from the run info
    FromRun run;

    // from the open info
    FromOpen open;

    // from the close info
    FromClose close;
  };

};

#endif
