#include <cstdint>
#include <vector>
#include <map>
#include <memory>

#include <difipack/common.hpp>

#pragma once

namespace difipack
{
  /*! The class that represents the DIFI prologue.
   *
   * The prologue is the common first 7 words of each DIFI packet.
   */
  class prologue
  {
  public:
    class builder;

    static constexpr difipack::TSI DEFAULT_TSI = difipack::TSI::UTC; //!< The default TSI as defined by DIFI
    static constexpr std::uint32_t DEFAULT_OUI = 0x7c386c;           //!< The default OUI as defined by DIFI
    static constexpr std::uint16_t DEFAULT_ICC = 0x0;                //!< The default ICC as defined by DIFI
    static constexpr std::uint16_t DEFAULT_PCC = 0x0;                //!< The default PCC as defined by DIFI

    static constexpr std::size_t PROLOGUE_SIZE_WORDS = 7;                                           //!< The size of the DIFI prologue in 32-bit words
    static constexpr std::size_t PROLOGUE_SIZE_BYTES = difipack::prologue::PROLOGUE_SIZE_WORDS * 4; //!< The size of the DIFI prologue in bytes

    static const std::map<difipack::PACKET_TYPE, std::uint32_t> STATIC_BITS; //!< A map corresponding to the unchanging bits of the prologue for each packet type

    /*! A basic constructor for a DIFI prologue object.
     */
    prologue(
        PACKET_TYPE packet_type,
        difipack::TSI tsi,
        std::uint8_t seqnum,
        std::uint16_t packet_size,
        std::uint32_t stream_id,
        std::uint32_t oui,
        std::uint16_t icc,
        std::uint16_t pcc,
        std::uint32_t int_timestamp,
        std::uint64_t frac_timestamp);

    /*! Serialize the prologue into a series of bytes.
     *
     * \param first the pointer to the first byte to serialize to
     * \param last the pointer to the last byte to serialize to
     *
     * \throws std::invalid_argument when the destination range is too small
     */
    void serialize(std::uint8_t *first, std::uint8_t *last);

    /*! Get the packet type of the prologue.
     *
     * \returns the packet type of the prologue
     */
    difipack::PACKET_TYPE get_packet_type();

    /*! Set the packet type of the prologue.
     *
     * \param packet_type the new packet type
     */
    void set_packet_type(difipack::PACKET_TYPE packet_type);

    /*! Get the Time Source Integer (TSI) of the prologue.
     *
     * \returns the tsi of the prologue
     */
    difipack::TSI get_tsi();

    /*! Set the Time Source Integer (TSI) of the prologue.
     *
     * \param tsi the new tsi
     */
    void set_tsi(difipack::TSI tsi);

    /*! Get the sequence number (seqnum) of the prologue.
     *
     * \returns the seqnum of the prologue
     */
    std::uint8_t get_seqnum();

    /*! Set the sequence number (seqnum) of the prologue.
     *
     * \param seqnum the new seqnum
     */
    void set_seqnum(std::uint8_t seqnum);

    /*! Get the packet size field of the prologue.
     *
     * \returns the packet size field
     */
    std::uint16_t get_packet_size();

    /*! Set the packet size field of the prologue.
     *
     * \param packet_size the new packet size
     */
    void set_packet_size(std::uint16_t packet_size);

    /*! Get the Stream ID of the prologue.
     *
     * \returns the stream id of the prologue
     */
    std::uint32_t get_stream_id();

    /*! Set the Stream ID of the prologue.
     *
     * \param stream_id the new stream id
     */
    void set_stream_id(std::uint8_t stream_id);

    /*! Get the Organization Unique Identifier (OUI) of the prologue.
     *
     * \returns the oui of the prologue
     */
    std::uint32_t get_oui();

    /*! Set the Organization Unique Identifier (OUI) of the prologue.
     *
     * \param oui the new oui
     */
    void set_oui(std::uint32_t oui);

    /*! Get the Information Class Code (ICC) of the prologue.
     *
     * \returns the icc of the prologue
     */
    std::uint16_t get_icc();

    /*! Set the Information Class Code (ICC) of the prologue.
     *
     * \param icc the new icc
     */
    void set_icc(std::uint16_t icc);

    /*! Get the Packet Class Code (PCC) of the prologue.
     *
     * \returns the pcc of the prologue
     */
    std::uint16_t get_pcc();

    /*! Set the Packet Class Code (PCC) of the prologue.
     *
     * \param pcc the new pcc
     */
    void set_pcc(std::uint16_t pcc);

    /*! Get the integer timestamp portion of the prologue.
     *
     * \returns the integer timestamp field of the prologue
     */
    std::uint32_t get_int_timestamp();

    /*! Set the integer timestamp portion of the prologue.
     *
     * \param int_timestamp the new integer timestamp field
     */
    void set_int_timestamp(std::uint32_t int_timestamp);

    /*! Get the fractional timestamp portion of the prologue.
     *
     * \returns the fractional timestamp field of the prologue
     */
    std::uint64_t get_frac_timestamp();

    /*! Set the fractional timestamp portion of the prologue.
     *
     * \param frac_timestamp the new fractional timestamp field
     */
    void set_frac_timestamp(std::uint64_t frac_timestamp);

  private:
    prologue() = delete;

    difipack::PACKET_TYPE _packet_type;
    difipack::TSI _tsi;
    std::uint8_t _seqnum;
    std::uint16_t _packet_size;
    std::uint32_t _stream_id;
    std::uint32_t _oui;
    std::uint16_t _icc;
    std::uint16_t _pcc;
    std::uint32_t _int_timestamp;
    std::uint64_t _frac_timestamp;
  };

  /*! A builder class for prologues.
   */
  class prologue::builder
  {
  public:
    /*! Create a prologue builder with all default values.
     */
    builder();

    /*! Set the packet type of the prologue builder.
     *
     * \param packet_type the new packet type
     */
    difipack::prologue::builder *with_packet_type(difipack::PACKET_TYPE packet_type);

    /*! Set the Time Source Integer (TSI) of the prologue builder.
     *
     * \param tsi the new tsi
     */
    difipack::prologue::builder *with_tsi(difipack::TSI tsi);

    /*! Set the sequence number (seqnum) of the prologue builder.
     *
     * \param seqnum the new seqnum
     */
    difipack::prologue::builder *with_seqnum(std::uint8_t seqnum);

    /*! Set the packet size field of the prologue builder.
     *
     * \param packet_size the new packet size
     */
    difipack::prologue::builder *with_packet_size(std::uint16_t packet_size);

    /*! Set the Stream ID of the prologue builder.
     *
     * \param stream_id the new stream id
     */
    difipack::prologue::builder *with_stream_id(std::uint32_t stream_id);

    /*! Set the Organization Unique Identifier (OUI) of the prologue builder.
     *
     * \param oui the new oui
     */
    difipack::prologue::builder *with_oui(std::uint32_t oui);

    /*! Set the Information Class Code (ICC) of the prologue builder.
     *
     * \param icc the new icc
     */
    difipack::prologue::builder *with_icc(std::uint16_t icc);

    /*! Set the Packet Class Code (PCC) of the prologue builder.
     *
     * \param pcc the new pcc
     */
    difipack::prologue::builder *with_pcc(std::uint16_t pcc);

    /*! Set the integer timestamp portion of the prologue builder.
     *
     * \param int_timestamp the new integer timestamp field
     */
    difipack::prologue::builder *with_int_timestamp(std::uint32_t int_timestamp);

    /*! Set the fractional timestamp portion of the prologue builder.
     *
     * \param frac_timestamp the new fractional timestamp field
     */
    difipack::prologue::builder *with_frac_timestamp(std::uint64_t frac_timestamp);

    /*! Build a prologue with the current builder configuration.
     */
    difipack::prologue build();

  private:
    difipack::PACKET_TYPE _packet_type;
    difipack::TSI _tsi;
    std::uint8_t _seqnum;
    std::uint16_t _packet_size;
    std::uint32_t _stream_id;
    std::uint32_t _oui;
    std::uint16_t _icc;
    std::uint16_t _pcc;
    std::uint32_t _int_timestamp;
    std::uint64_t _frac_timestamp;
  };
}
