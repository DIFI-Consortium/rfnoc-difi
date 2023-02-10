#include <cstdint>
#include <vector>

#include <difipack/prologue.hpp>
#include <difipack/packet.hpp>

#pragma once

namespace difipack
{
  /*! The class that represents a DIFI data packet.
   */
  class data_packet : public difipack::packet
  {
  public:
    class builder;

    /*! Serialize the data packet into a series of bytes.
     *
     * \param first the pointer to the first byte to serialize to
     * \param last the pointer to the last byte to serialize to
     *
     * \throws std::invalid_argument when the destination range is too small
     */
    void serialize(std::uint8_t *first, std::uint8_t *last);

    /*! Set the Information Class Code (ICC) of the data packet.
     *
     * \param icc the new icc
     */
    void set_icc(std::uint16_t icc);

    /*! Set the Packet Class Code (PCC) of the data packet.
     *
     * \param pcc the new pcc
     */
    void set_pcc(std::uint16_t pcc);

    /*! Get the current payload of the data packet.
     *
     * \returns the payload in byte vector form
     */
    const std::vector<std::uint8_t> &get_payload() const;

    /*! Set the payload of the packet.
     * Automatically updates the packet length.
     *
     * \param payload the new payload, as a byte vector, to attach to this data packet
     */
    void set_payload(std::vector<std::uint8_t> payload);

  private:
    data_packet(difipack::prologue prologue, std::vector<std::uint8_t> payload);

    std::vector<std::uint8_t> _payload;
  };

  /*! A builder class for data packets.
   */
  class data_packet::builder : public difipack::packet::builder<difipack::data_packet::builder>
  {
  public:
    /*! Create a data packet builder.
     * A DIFI data packet must have at least one item, so the payload is required.
     *
     * \param payload the payload, as a byte vector, to attach to this data packet builder
     */
    builder(std::vector<std::uint8_t> payload);

    /*! Set the Information Class Code (ICC) of the data packet builder.
     *
     * \param icc the new icc
     */
    difipack::data_packet::builder *with_icc(std::uint16_t icc);

    /*! Set the Packet Class Code (PCC) of the data packet builder.
     *
     * \param pcc the new pcc
     */
    difipack::data_packet::builder *with_pcc(std::uint16_t pcc);

    /*! Set the payload of the data packet builder.
     * Automatically updates the packet length.
     *
     * \param payload the new payload, as a byte vector, to attach to this data packet builder
     */
    difipack::data_packet::builder *with_payload(std::vector<std::uint8_t> payload);

    /*! Build a data packet with the current builder configuration.
     */
    difipack::data_packet build();

  private:
    std::vector<std::uint8_t> _payload;
  };
}