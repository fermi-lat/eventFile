/**
 * @class eventFile::LSEReader
 *
 * @brief Class for reading a file containing per-event context, meta-info, and EBF data
 *
 * @author Bryson Lee <blee@slac.stanford.edu>
 *
 * $Header$
 */

#ifndef LSEREADER_H
#define LSEREADER_H

#include <stdio.h>

#include <string>
#include <utility>

#include "eventFile/LSE_Info.h"
#include "eventFile/LSEHeader.h"
#include "eventFile/LSE_Keys.h"

namespace eventFile {

  class LSE_Context;
  class EBF_Data;
  
  class LSEReader {
  public:
    LSEReader( const std::string& filename );
    virtual ~LSEReader();

    bool read( LSE_Context&, EBF_Data&, 
	       LSE_Info::InfoType&, LPA_Info&, LCI_ACD_Info&, LCI_CAL_Info&, LCI_TKR_Info&, 
	       LSE_Keys::KeysType&, LPA_Keys&, LCI_Keys& );
    void close();

#ifdef _FILE_OFFSET_BITS
    int seek( off_t ofst );
#else
    int seek( int ofst );
#endif

    // header accessors
    unsigned runid() const { return m_hdr.m_runid; };
    unsigned begSec() const { return m_hdr.m_secs_beg; };
    unsigned endSec() const { return m_hdr.m_secs_end; };
    unsigned long long evtcnt() const { return m_hdr.m_evtcnt; };
    unsigned long long begGEM() const { return m_hdr.m_GEMseq_beg; };
    unsigned long long endGEM() const { return m_hdr.m_GEMseq_end; };
    std::pair<unsigned, unsigned> seqErr( int islot ) const
      {
	if ( islot < LSEHEADER_MAX_APIDS ) {
	  return std::pair<unsigned, unsigned>( m_hdr.m_src_apids[islot], m_hdr.m_src_seqerr[islot] );
	} else {
	  return std::pair<unsigned, unsigned>( 0, 0 );
	}
      };
    std::pair<unsigned, unsigned> dfiErr( int islot ) const
      {
	if ( islot < LSEHEADER_MAX_APIDS ) {
	  return std::pair<unsigned, unsigned>( m_hdr.m_dfi_apids[islot], m_hdr.m_dfi_dfierr[islot] );
	} else {
	  return std::pair<unsigned, unsigned>( 0, 0 );
	}
      };

  private:
    std::string m_name;
    LSEHeader m_hdr;
    FILE* m_FILE;

    bool read( LSE_Context&, EBF_Data& );
    void read( unsigned char*, size_t& );
    void read( LPA_Keys& );
    void read( LCI_Keys& );
    void read( LSE_Keys& );
    void readKeys( LSE_Keys::KeysType&, LPA_Keys&, LCI_Keys& );
    void readInfo( LSE_Info::InfoType&, LPA_Info&, LCI_ACD_Info&, LCI_CAL_Info&, LCI_TKR_Info& );
    void readHeader();
  };
  
};

#endif
