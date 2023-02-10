#include <cstdint>
#include <vector>

#include <difipack/packet.hpp>

#pragma once

namespace difipack
{
  /*! The class that represents the DIFI version context packet.
   */
  class version_context_packet : public packet
  {
  public:
    //! An enum for the valid DIFI Context Indicator Field 0s (CIFs) for the version context packet
    enum CIF0
    {
      CONTEXT_CHANGE = 0x80000002,
      NO_CHANGE = 0x00000002
    };

    //! An enum for the valid Types of devices for the version context packet
    enum TYPE
    {
      NARROWBAND = 0,
      WIDEBAND = 1
    };

    //! An enum for the valid ICD Versions for the version context packet
    enum ICD_VERSION
    {
      V_1 = 0
    };

    class builder;

    static constexpr std::uint16_t VERSION_CONTEXT_ICC = 0x001;                   //!< The only valid value for the ICC field of a version context packet
    static constexpr std::uint16_t VERSION_CONTEXT_PCC = 0x004;                   //!< The only valid value for the PCC field of a version context packet
    static constexpr std::uint16_t VERSION_CONTEXT_CIF1 = 0x0000000C;             //!< The only valid value for the CIF1 field of a version context packet
    static constexpr std::uint16_t VERSION_CONTEXT_V49_SPEC_VERSION = 0x00000004; //!< The only valid value for the V49 Spec Version field of a version context packet

    static constexpr std::uint16_t PACKET_SIZE_WORDS = 11; //!< The size of the version context packet in 32-bit words

    /*! Serialize the version context packet into a series of bytes.
     *
     * \param first the pointer to the first byte to serialize to
     * \param last the pointer to the last byte to serialize to
     *
     * \throws std::invalid_argument when the destination range is too small
     */
    void serialize(std::uint8_t *first, std::uint8_t *last);

    /*! Get the Context Indicator Field 0 (CIF0) of the version context packet.
     *
     * \returns the cif0
     */
    difipack::version_context_packet::CIF0 get_cif0();

    /*! Set the Context Indicator Field 0 (CIF0) of the version context packet.
     *
     * \param cif0 the new cif0
     */
    void set_cif0(difipack::version_context_packet::CIF0 cif0);

    /*! Get the Context Indicator Field 1 (CIF1) of the version context packet.
     *
     * \returns the cif1
     */
    const std::uint32_t get_cif1();

    /*! Get the V49 Spec Version of the version context packet.
     *
     * \returns the v49 spec version
     */
    const std::uint32_t get_v49_spec_version();

    /*! Get the Year field of the version context packet.
     *
     * \returns the year field
     */
    std::uint8_t get_year();

    /*! Set the Year field of the version context packet.
     *
     * \param year the new year field
     */
    void set_year(std::uint8_t year);

    /*! Get the Day field of the version context packet.
     *
     * \returns the day field
     */
    std::uint16_t get_day();

    /*! Set the Day field of the version context packet.
     *
     * \param day the new day field
     */
    void set_day(std::uint16_t day);

    /*! Get the Revision field of the version context packet.
     *
     * \returns the revision field
     */
    std::uint8_t get_revision();

    /*! Set the Revision field of the version context packet.
     *
     * \param revision the new revision field
     */
    void set_revision(std::uint8_t revision);

    /*! Get the Type field of the version context packet.
     *
     * \returns the type field
     */
    difipack::version_context_packet::TYPE get_type();

    /*! Set the Type field of the version context packet.
     *
     * \param type the new type field
     */
    void set_type(difipack::version_context_packet::TYPE type);

    /*! Get the ICD Version of the version context packet.
     *
     * \returns the icd version
     */
    difipack::version_context_packet::ICD_VERSION get_icd_version();

    /*! Set the ICD Version of the version context packet.
     *
     * \param icd_version the new icd version
     */
    void set_icd_version(difipack::version_context_packet::ICD_VERSION icd_version);

  private:
    version_context_packet(
        difipack::prologue prologue,
        difipack::version_context_packet::CIF0 cif0,
        std::uint8_t year,
        std::uint16_t day,
        std::uint8_t revision,
        difipack::version_context_packet::TYPE type,
        difipack::version_context_packet::ICD_VERSION icd_version);

    difipack::version_context_packet::CIF0 _cif0;
    const std::uint32_t _cif1 = VERSION_CONTEXT_CIF1;
    const std::uint32_t _v49_spec_version = VERSION_CONTEXT_V49_SPEC_VERSION;
    std::uint8_t _year;
    std::uint16_t _day;
    std::uint8_t _revision;
    difipack::version_context_packet::TYPE _type;
    difipack::version_context_packet::ICD_VERSION _icd_version;
  };

  /*! A builder class for version context packets.
   */
  class version_context_packet::builder : public difipack::packet::builder<difipack::version_context_packet::builder>
  {
  public:
    /*! Set the Context Indicator Field 0 (CIF0) of the version context packet builder.
     *
     * \param cif0 the new cif0
     */
    difipack::version_context_packet::builder *with_cif0(difipack::version_context_packet::CIF0 cif0);

    /*! Set the Year field of the version context packet builder.
     *
     * \param year the new year field
     */
    difipack::version_context_packet::builder *with_year(std::uint8_t year);

    /*! Set the Day field of the version context packet builder.
     *
     * \param day the new day field
     */
    difipack::version_context_packet::builder *with_day(std::uint16_t day);

    /*! Set the Revision field of the version context packet builder.
     *
     * \param revision the new revision field
     */
    difipack::version_context_packet::builder *with_revision(std::uint8_t revision);

    /*! Set the Type field of the version context packet builder.
     *
     * \param type the new type field
     */
    difipack::version_context_packet::builder *with_type(difipack::version_context_packet::TYPE type);

    /*! Set the ICD Version of the version context packet builder.
     *
     * \param icd_version the new icd version
     */
    difipack::version_context_packet::builder *with_icd_version(difipack::version_context_packet::ICD_VERSION icd_version);

    /*! Build a version context packet with the current builder configuration.
     */
    difipack::version_context_packet build();

  private:
    difipack::version_context_packet::CIF0 _cif0 = difipack::version_context_packet::CIF0::CONTEXT_CHANGE;
    std::uint8_t _year = 0;
    std::uint16_t _day = 0;
    std::uint8_t _revision = 0;
    difipack::version_context_packet::TYPE _type = difipack::version_context_packet::TYPE::NARROWBAND;
    difipack::version_context_packet::ICD_VERSION _icd_version = difipack::version_context_packet::ICD_VERSION::V_1;
  };
}