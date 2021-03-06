#pragma once

#include "telnetpp/core.hpp"

namespace telnetpp { namespace options { namespace mccp {

//* =========================================================================
/// \brief Represents an object that can compress arbitrary byte sequences.
//* =========================================================================
class compressor
{
public :
    //* =====================================================================
    /// \brief Destructor
    //* =====================================================================
    virtual ~compressor() {}
    
    //* =====================================================================
    /// \brief Compress the given byte sequence and return the compressed
    /// sequence.
    //* =====================================================================
    virtual telnetpp::byte_stream compress(
        telnetpp::byte_stream const &sequence) = 0;

    //* =====================================================================
    /// \brief Ends the compression stream.  Compressing further will cause
    /// the stream to restart.
    //* =====================================================================
    virtual telnetpp::byte_stream end_compression() = 0;
};

}}}
