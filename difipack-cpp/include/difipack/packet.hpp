#include <cstdint>
#include <vector>
#include <variant>

#include <difipack/prologue.hpp>
#include <difipack/common.hpp>

#pragma once

namespace difipack
{
  /*! The class that represents a generic DIFI packet.
   */
  class packet
  {
  public:
    /*! Serialize the packet into a series of bytes.
     *
     * \param first the pointer to the first byte to serialize to
     * \param last the pointer to the last byte to serialize to
     *
     * \throws std::invalid_argument when the destination range is too small
     */
    virtual void serialize(std::uint8_t *first, std::uint8_t *last) = 0;

    /*! Serialize the packet into a byte vector.
     *
     * \returns a byte vector containing the packet bytes
     */
    std::vector<std::uint8_t> serialize_to_byte_vector();

    /*! Get the packet type.
     *
     * \returns the packet type
     */
    difipack::PACKET_TYPE get_packet_type();

    /*! Get the Time Source Integer (TSI) of the packet.
     *
     * \returns the tsi of the packet
     */
    difipack::TSI get_tsi();

    /*! Set the Time Source Integer (TSI) of the packet.
     *
     * \param tsi the new tsi
     */
    void set_tsi(difipack::TSI tsi);

    /*! Get the packet sequence number (seqnum).
     *
     * \returns the seqnum of the packet
     */
    std::uint8_t get_seqnum();

    /*! Set the packet sequence number (seqnum).
     *
     * \param seqnum the new seqnum
     */
    void set_seqnum(std::uint8_t seqnum);

    /*! Get the packet size in DIFI words.
     *
     * \returns the packet size in 32-bit DIFI words
     */
    std::uint16_t get_packet_size();

    /*! Get the Stream ID of the packet.
     *
     * \returns the stream id of the packet
     */
    std::uint32_t get_stream_id();

    /*! Set the Stream ID of the packet.
     *
     * \param stream_id the new stream id
     */
    void set_stream_id(std::uint8_t stream_id);

    /*! Get the Organization Unique Identifier (OUI) of the packet.
     *
     * \returns the oui of the packet
     */
    std::uint32_t get_oui();

    /*! Set the Organization Unique Identifier (OUI) of the packet.
     *
     * \param oui the new oui
     */
    void set_oui(std::uint32_t oui);

    /*! Get the Information Class Code (ICC) of the packet.
     *
     * \returns the icc of the packet
     */
    std::uint16_t get_icc();

    /*! Get the Packet Class Code (PCC) of the packet.
     *
     * \returns the pcc of the packet
     */
    std::uint16_t get_pcc();

    /*! Get the integer timestamp portion of the packet's timestamp.
     *
     * \returns the integer timestamp of the packet, as a 32-bit integer
     */
    std::uint32_t get_int_timestamp();

    /*! Set the integer timestamp portion of the packet's timestamp.
     *
     * \param int_timestamp the new integer timestamp of the packet, as a 32-bit integer
     */
    void set_int_timestamp(std::uint32_t int_timestamp);

    /*! Get the fractional portion of the packet's timestamp
     *
     * \returns the fractional portion of the packet, as a 64-bit integer
     */
    std::uint64_t get_frac_timestamp();

    /*! Set the fractional timestamp portion of the packet's timestamp.
     *
     * \param frac_timestamp the new fractional timestamp of the packet, as a 32-bit integer
     */
    void set_frac_timestamp(std::uint64_t frac_timestamp);

  protected:
    /*! A generic builder class for other packet builders to inherit from.
     */
    template <class packet_builder>
    class builder
    {
    public:
      /*! Creates a packet builder with a default prologue builder.
       */
      builder(){};

      /*! Set the Time Source Integer (TSI) of the packet builder.
       *
       * \param tsi the new tsi
       */
      packet_builder *with_tsi(difipack::TSI tsi)
      {
        this->_prologue_builder.with_tsi(tsi);
        return (packet_builder *)this;
      };

      /*! Set the packet sequence number (seqnum) builder.
       *
       * \param seqnum the new seqnum
       */
      packet_builder *with_seqnum(std::uint8_t seqnum)
      {
        this->_prologue_builder.with_seqnum(seqnum);
        return (packet_builder *)this;
      };

      /*! Set the Stream ID of the packet builder.
       *
       * \param stream_id the new stream id
       */
      packet_builder *with_stream_id(std::uint32_t stream_id)
      {
        this->_prologue_builder.with_stream_id(stream_id);
        return (packet_builder *)this;
      };

      /*! Set the Organization Unique Identifier (OUI) of the packet builder.
       *
       * \param oui the new oui
       */
      packet_builder *with_oui(std::uint32_t oui)
      {
        this->_prologue_builder.with_oui(oui);
        return (packet_builder *)this;
      };

      /*! Set the integer timestamp portion of the packet's timestamp builder.
       *
       * \param int_timestamp the new integer timestamp of the packet, as a 32-bit integer
       */
      packet_builder *with_int_timestamp(std::uint32_t int_timestamp)
      {
        this->_prologue_builder.with_int_timestamp(int_timestamp);
        return (packet_builder *)this;
      };

      /*! Set the fractional timestamp portion of the packet's timestamp builder.
       *
       * \param frac_timestamp the new fractional timestamp of the packet, as a 32-bit integer
       */
      packet_builder *with_frac_timestamp(std::uint64_t frac_timestamp)
      {
        this->_prologue_builder.with_frac_timestamp(frac_timestamp);
        return (packet_builder *)this;
      };

    protected:
      difipack::prologue::builder _prologue_builder; //!< the DIFI prologue builder of this packet builder
    };

    packet() = delete;

    /*! Creates a DIFI packet with the given prologue
     *
     * \param prologue the prologue for this packet
     */
    packet(difipack::prologue prologue);

    difipack::prologue _prologue; //!< the DIFI prologue of this packet
  };
}