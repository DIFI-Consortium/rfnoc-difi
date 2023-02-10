#pragma once

namespace difipack
{
  //! An enum for the valid DIFI Time Source Integers (TSIs).
  enum TSI
  {
    UTC = 0x1,
    GPS = 0x2,
    POSIX = 0x3
  };

  //! An enum for the DIFI packet types.
  enum PACKET_TYPE
  {
    DATA = 0x1,
    STANDARD_CONTEXT = 0x4,
    VERSION_CONTEXT = 0x5
  };
}