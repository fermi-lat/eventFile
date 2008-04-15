/** 
 * @class eventFile::LPA_Handler
 *
 * @brief Class encapsulating event-handler information
 *
 * @author Bryson Lee <blee@slac.stanford.edu>
 *
 * $Header$
 */

#ifndef EVENTFILE_LPA_HANDLER_HH
#define EVENTFILE_LPA_HANDLER_HH

#include <vector>

namespace eventFile {

  /** structures representing V0 of the handler-specific RSD's */
  struct DgnHandlerRsdV0 {
    unsigned int status;
  };
    
  struct GammaHandlerRsdV0 {
    unsigned int status;
    unsigned int stage;
    unsigned int energyValid;
    signed int energyInLeus;
  };

  struct HipHandlerRsdV0 {
    unsigned int status;
  };

  struct MipHandlerRsdV0 {
    unsigned int status;
  };

  struct PassthruHandlerRsdV0 {
    unsigned int status;
  };

  /** union of all RSD-specific structures */
  union RsdUnion {
    DgnHandlerRsdV0      dgn0;
    GammaHandlerRsdV0    gamma0;
    HipHandlerRsdV0      hip0;
    MipHandlerRsdV0      mip0;
    PassthruHandlerRsdV0 passthru0;
  };

  /** class representing the result info from each active handler */
  class LPA_Handler {
  public:

    /** enumerate the types of handlers */
    enum HandlerType {
      Unknown = -1,
      Filter  =  0,
      Monitor =  1,

      // management values
      HandlerTypeMin = -1,
      HandlerTypeMax =  1,
      HandlerTypeCnt = HandlerTypeMax - HandlerTypeMin + 1,
    };

    /** enumerate the handler identities */
    enum HandlerId {
      PASS_THRU = 0,
      GAMMA     = 1,
      ASC       = 2,
      MIP       = 3,
      HIP       = 4,
      DGN       = 5,
      MaxHandlerIds,
    };

    /** enumerate the overall result states for an event */
    enum RsdState {
      INVALID    = -1,  /// Invalid state
      PASSED     =  0,  /// Event passed the filter
      SUPPRESSED =  1,  /// Event passed but was suppressed by an output prescaler
      VETOED     =  2,  /// Event vetoed by the filter
      LEAKED     =  3,  /// Event vetoed but leaked by an output prescaler
      IGNORED    =  4,  /// Event ignored due to input prescaler
    };

    /** enumerate valid values for the prescaler data member 
	note the values > 0 indicate which condition-specifc
	prescaler expired.
    */
    enum LeakedPrescaler {
      UNSUPPORTED = -3, /// prescaler info not available (always for RSD V0)
      INPUT       = -2, /// event not analyzed due to input prescaler
      OUTPUT      = -1, /// event leaked by overall output prescaler

      /** event leaked by condition-specific prescaler */
      COND00, COND01, COND02, COND03, COND04, COND05, COND06, COND07,
      COND08, COND09, COND10, COND11, COND12, COND13, COND14, COND15,
      COND16, COND17, COND18, COND19, COND20, COND21, COND22, COND23,
      COND24, COND25, COND26, COND27, COND28, COND29, COND30, COND31,
    };

    /** ctor and dump routine */
    LPA_Handler() : 
      type(Unknown), masterKey(0xFFFFFFFF), cfgKey(0xFFFFFFFF), cfgId(0xFFFFFFFF),
      state(INVALID), prescaler(UNSUPPORTED), version(0), id(MaxHandlerIds),
      has(false) {};
    void dump( const char* pre, const char* post ) const;

    HandlerType       type;
    unsigned int      masterKey;  /// FMX key of master CDM for handler (fixed for a run)
    unsigned int      cfgKey;     /// FMX key of current CDM for handler (may vary by mode)
    unsigned int      cfgId;      /// unique identifier of handler config (may vary by mode)
    RsdState          state;      /// overall filter result for the event
    LeakedPrescaler   prescaler;  /// Unsupported in RSD V0, otherwise indicates how event was leaked
    unsigned int      version;    /// Encoding version of handler-specific RSD
    HandlerId         id;         /// Handler identifier
    bool              has;        /// Indicates whether handler generated summary data
    RsdUnion          rsd;        /// union of handler-specific RSD types

    const DgnHandlerRsdV0*          dgnRsdV0()      const;
    const GammaHandlerRsdV0*        gammaRsdV0()    const;
    const HipHandlerRsdV0*          hipRsdV0()      const;
    const MipHandlerRsdV0*          mipRsdV0()      const;
    const PassthruHandlerRsdV0*     passthruRsdV0() const;
    const char*                     typeName() const;
    const char*                     handlerName() const;

  };
};

#endif // EVENTFILE_LPA_HANDLER_HH
