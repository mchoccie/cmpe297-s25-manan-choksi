/*
 * Copyright (c) 2019 Ritsumeikan University, Shiga, Japan.
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Alberto Gallegos Ramonet <ramonet@fc.ritsumei.ac.jp>
 *
 * This file implements Information Fields present in IEEE 802.15.4-2011.
 * Information Fields are in practice similar to the Information Elements(IE)
 * introduced in later revisions of the standard, however, they lack
 * descriptors and common format unlike the IEs. To keep this implementation
 * consistent with the IEEE 802.15.4-2011 std. the present file implements
 * Information Fields not Information Elements.
 */
#ifndef LR_WPAN_FIELDS_H
#define LR_WPAN_FIELDS_H

#include "ns3/buffer.h"
#include <ns3/mac16-address.h>
#include <ns3/mac64-address.h>

#include <array>

namespace ns3
{
namespace lrwpan
{

/**
 * \ingroup lr-wpan
 * The device Capabilities.
 */
enum DeviceType
{
    RFD = 0, //!< Reduced Functional Device (RFD)
    FFD = 1  //!< Full Functional Device (FFD)
};

/**
 * \ingroup lr-wpan
 * Represent the Superframe Specification information field.
 * See IEEE 802.15.4-2011   Section 5.2.2.1.2 Figure 41
 */
class SuperframeField
{
  public:
    SuperframeField();

    /**
     * Create a superframe Specification Information field with
     * the information specified in the bitmap.
     *
     * \param bitmap The superframe in bitmap form
     */
    SuperframeField(uint16_t bitmap);
    /**
     * Set the whole Superframe Specification Information field.
     * \param superFrm The Superframe Specification information field.
     */
    void SetSuperframe(uint16_t superFrm);
    /**
     * Set the superframe specification Beacon Order field.
     * \param bcnOrder The beacon order value to set in the superframe.
     */
    void SetBeaconOrder(uint8_t bcnOrder);
    /**
     * Set the superframe specification Superframe Order field.
     * \param frmOrder The frame Order value to set on the superframe.
     */
    void SetSuperframeOrder(uint8_t frmOrder);
    /**
     * Set the superframe specification Final CAP slot field.
     * \param capSlot Set the final slot of the Contention Access Period (CAP).
     */
    void SetFinalCapSlot(uint8_t capSlot);
    /**
     * Set the Superframe Specification Battery Life Extension (BLE).
     * \param battLifeExt Sets true or false the value of the Battery Life Extension flag of the
     * superframe field.
     */
    void SetBattLifeExt(bool battLifeExt);
    /**
     * Set the Superframe Specification PAN coordinator field.
     * \param panCoor set true or false the value for the PAN Coordinator flag of the superframe
     * field.
     */
    void SetPanCoor(bool panCoor);
    /**
     * Set the Superframe Specification Association Permit field.
     * \param assocPermit set true or false the value of the Association Permit flag of the
     * superframe field.
     */
    void SetAssocPermit(bool assocPermit);
    /**
     * Get the Superframe Specification Beacon Order field.
     * \return the Superframe Specification Beacon Order field.
     */
    uint8_t GetBeaconOrder() const;
    /**
     * Get the Superframe Specification Frame Order field.
     * \return The Superframe Specification Frame Order field.
     */
    uint8_t GetFrameOrder() const;
    /**
     * Get the the Final CAP Slot.
     * \returns The Final CAP Slot
     */
    uint8_t GetFinalCapSlot() const;
    /**
     * Check if the Battery Life Extension bit is enabled.
     * \returns true if the Battery Life Extension bit is enabled
     */
    bool IsBattLifeExt() const;
    /**
     * Check if the PAN Coordinator bit is enabled.
     * \returns true if the PAN Coordinator bit is enabled
     */
    bool IsPanCoor() const;
    /**
     * Check if the Association Permit bit is enabled.
     * \returns true if the Association Permit bit is enabled
     */
    bool IsAssocPermit() const;
    /**
     * Get the Superframe specification information field.
     * \return the Superframe Specification Information field bits.
     */
    uint16_t GetSuperframe() const;

  private:
    // Superframe Specification field
    // See IEEE 802.14.15-2011 5.2.2.1.2
    uint8_t m_sspecBcnOrder;    //!< Superframe Specification field Beacon Order (Bit 0-3)
    uint8_t m_sspecSprFrmOrder; //!< Superframe Specification field Superframe Order (Bit 4-7)
    uint8_t m_sspecFnlCapSlot;  //!< Superframe Specification field Final CAP slot (Bit 8-11)
    bool m_sspecBatLifeExt;     //!< Superframe Specification field Battery Life Extension (Bit 12)
                            //!< Superframe Specification field Reserved (not necessary) (Bit 13)
    bool m_sspecPanCoor;     //!< Superframe Specification field PAN Coordinator (Bit 14)
    bool m_sspecAssocPermit; //!< Superframe Specification field Association Permit (Bit 15)
};

/**
 * \brief Stream insertion operator.
 *
 * \param [in] os The reference to the output stream.
 * \param [in] superframeField The Superframe fields.
 * \returns The reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const SuperframeField& superframeField);

/**
 * \ingroup lr-wpan
 * Represent the GTS information fields.
 * See IEEE 802.15.4-2011   Section 5.2.2 Figure 39
 */
class GtsFields
{
  public:
    GtsFields();
    /**
     * Get the GTS Specification Field from the GTS Fields
     * \return The GTS Specification Field
     */
    uint8_t GetGtsSpecField() const;
    /**
     * Get the GTS Direction Field from the GTS Fields
     * \return The GTS Direction Field
     */
    uint8_t GetGtsDirectionField() const;
    /**
     * Set the GTS Specification Field to the GTS Fields
     * \param gtsSpec The GTS Specification Field to set.
     */
    void SetGtsSpecField(uint8_t gtsSpec);
    /**
     * Set the GTS direction field to the GTS Fields
     * \param gtsDir The GTS Direction Field to set
     */
    void SetGtsDirectionField(uint8_t gtsDir);
    /**
     * Get the GTS Specification Permit. TRUE if coordinator is accepting GTS requests.
     * \return True if the coordinator is accepting GTS request.
     */
    bool GetGtsPermit() const;
    /**
     * Get the size of the serialized GTS fields.
     * \return the size of the serialized fields.
     */
    uint32_t GetSerializedSize() const;
    /**
     * Serialize the entire GTS fields.
     * \param i an iterator which points to where the superframe specification field should be
     * written.
     * \return an iterator.
     */
    Buffer::Iterator Serialize(Buffer::Iterator i) const;
    /**
     * Deserialize the entire GTS fields.
     * \param i an iterator which points to where the superframe specification field should be read.
     * \return an iterator.
     */
    Buffer::Iterator Deserialize(Buffer::Iterator i);

  private:
    /**
     * GTS Descriptor
     */
    struct GtsDescriptor
    {
        Mac16Address m_gtsDescDevShortAddr; //!< GTS Descriptor Device Short Address (Bit 0-15)
        uint8_t m_gtsDescStartSlot;         //!< GTS Descriptor GTS Starting Slot(Bit 16-19)
        uint8_t m_gtsDescLength;            //!< GTS Descriptor GTS Length (Bit 20-23)
    };

    // GTS specification field
    uint8_t m_gtsSpecDescCount; //!< GTS specification field Descriptor Count (Bit 0-2)
    // GTS specification field Reserved (Not necessary) (Bit 3-6)
    uint8_t m_gtsSpecPermit; //!< GTS specification field GTS Permit (Bit 7)
    // GTS Direction field
    uint8_t m_gtsDirMask; //!< GTS Direction field Directions Mask (Bit 0-6)
    // GTS Direction field Reserved (Not Necessary) (Bit 7)
    // GTS List
    GtsDescriptor m_gtsList[7]; //!< GTS List field (maximum descriptors stored == 7)
};

/**
 * \brief Stream insertion operator.
 *
 * \param [in] os The reference to the output stream.
 * \param [in] gtsFields The GTS fields.
 * \returns The reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const GtsFields& gtsFields);

/**
 * \ingroup lr-wpan
 * Represent the Pending Address Specification field.
 * See IEEE 802.15.4-2011   Section 5.2.2.1.6. Figure 45
 */
class PendingAddrFields
{
  public:
    PendingAddrFields();
    /**
     * Add a short Pending Address to the Address List.
     * \param shortAddr The extended Pending Address List.
     */
    void AddAddress(Mac16Address shortAddr);
    /**
     * Add a extended Pending Address to the Address List.
     * \param extAddr The extended Pending Address List.
     */
    void AddAddress(Mac64Address extAddr);
    /**
     * Search for the short Pending Address in the Address List.
     * \param shortAddr The extended Address to look in the Address List.
     * \return True if the address exist in the extended Address List.
     */
    bool SearchAddress(Mac16Address shortAddr);
    /**
     * Search for the extended Pending Address in the Address List.
     * \param extAddr The extended Address to look in the Address List.
     * \return True if the address exist in the extended Address List.
     */
    bool SearchAddress(Mac64Address extAddr);
    /**
     * Get the whole Pending Address Specification Field from the Pending Address Fields.
     * \return The Pending Address Specification Field.
     */
    uint8_t GetPndAddrSpecField() const;
    /**
     * Get the number of Short Pending Address indicated in the Pending Address Specification Field.
     * \return The number Short Pending Address.
     */
    uint8_t GetNumShortAddr() const;
    /**
     * Get the number of Extended Pending Address indicated in the Pending Address Specification
     * Field.
     * \return The number Short Pending Address.
     */
    uint8_t GetNumExtAddr() const;

    /**
     * Set the whole Pending Address Specification field. This field is part of the
     * Pending Address Fields header.
     * \param pndAddrSpecField The Pending Address Specification Field
     */
    void SetPndAddrSpecField(uint8_t pndAddrSpecField);
    /**
     * Get the size of the serialized Pending Address Fields.
     * \return the size of the serialized fields.
     */
    uint32_t GetSerializedSize() const;
    /**
     * Serialize the entire Pending Address Fields.
     * \param i an iterator which points to where the Pending Address Fields should be written.
     * \return an iterator.
     */
    Buffer::Iterator Serialize(Buffer::Iterator i) const;
    /**
     * Deserialize the all the Pending Address Fields.
     * \param i an iterator which points to where the Pending Address Fields should be read.
     * \return an iterator.
     */
    Buffer::Iterator Deserialize(Buffer::Iterator i);

  private:
    // Pending Address Specification Field
    uint8_t m_pndAddrSpecNumShortAddr; //!< Pending Address Specification field Number of Short
                                       //!< Address (Bits 0-2) Pending Address Specification field
                                       //!< Reserved (Not Necessary)(Bit  3)
    uint8_t m_pndAddrSpecNumExtAddr;   //!< Pending Address Specification field Number of Extended
                                       //!< Address (Bits 4-6) Pending Address Specification field
                                       //!< Reserved (Not Necessary) (Bit  7)
    // Address List
    std::array<Mac16Address, 7> m_shortAddrList; //!< Pending Short Address List
    std::array<Mac64Address, 7> m_extAddrList;   //!< Pending Extended Address List
};

/**
 * \brief Stream insertion operator.
 *
 * \param [in] os The reference to the output stream.
 * \param [in] pendingAddrFields The Pending Address fields.
 * \returns The reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const PendingAddrFields& pendingAddrFields);

/**
 * \ingroup lr-wpan
 *
 * Represent the Capability Information Field.
 * See IEEE 802.15.4-2011   Section 5.3.1.2 Figure 50
 */
class CapabilityField
{
  public:
    CapabilityField();

    /**
     * Construct a Capability field based on a bitmap.
     *
     * \param bitmap The bitmap representing the capability
     */
    CapabilityField(uint8_t bitmap);

    /**
     * Get the bitmap representing the device capability.
     *
     * \return The bitmap representing the device capability.
     */
    uint8_t GetCapability() const;

    /**
     * Set the bitmap representing the device capability.
     *
     * \param bitmap The bitmap representing the capability
     */
    void SetCapability(uint8_t bitmap);

    /**
     * True if the device type is a Full Functional Device (FFD) false if is a Reduced Functional
     * Device (RFD).
     *
     * \return True if the device type is a Full Functional Device (FFD) false if is a Reduced
     * Functional Device (RFD).
     */
    bool IsDeviceTypeFfd() const;

    /**
     * True if the device is receiving power from alternating current mains.
     *
     * \return True if the device is receiving power from alternating current mains.
     */
    bool IsPowSrcAvailable() const;

    /**
     * True if the device does not disable its receiver to conserve power during idle periods.
     *
     * \return True if the device does not disable its receiver to conserve power during idle
     * periods.
     */
    bool IsReceiverOnWhenIdle() const;

    /**
     * True if the device is capable of sending and receiving cryptographically protected MAC
     * frames.
     *
     * \return True if the device is capable of sending and receiving cryptographically protected
     * MAC frames.
     */
    bool IsSecurityCapability() const;

    /**
     * True if the device wishes the coordinator to allocate a short address as result of the
     * association procedure.
     *
     * \return True if the device wishes the coordinator to allocate a short address as result of
     * the association procedure.
     */
    bool IsShortAddrAllocOn() const;

    /**
     * Set the Device type in the Capability Information Field.
     * True = full functional device (FFD)  False = reduced functional device (RFD).
     *
     * \param devType The device type described in the Capability Information Field.
     */
    void SetFfdDevice(bool devType);

    /**
     * Set the Power Source available flag in the Capability Information Field.
     *
     * \param pow Set true if a Power Source is available in the Capability Information Field.
     */
    void SetPowSrcAvailable(bool pow);

    /**
     * Indicate if the receiver is On on Idle
     *
     * \param rxIdle Set true if the receiver is on when Idle
     */
    void SetRxOnWhenIdle(bool rxIdle);

    /**
     * Set the Security Capability flag in the Capability Information Field.
     *
     * \param sec Set true if the device have Security Capabilities.
     */
    void SetSecurityCap(bool sec);

    /**
     * Set the Short Address Flag in the Capability Information Field.
     *
     * \param addrAlloc Describes whether or not the coordinator should allocate a short
     *                  address in the association process.
     */
    void SetShortAddrAllocOn(bool addrAlloc);

  private:
    bool m_reservedBit0;       //!< Capability Information Field, Reserved (bit 0)
    bool m_deviceType;         //!< Capability Information Field, Device Type  (bit 1)
    bool m_powerSource;        //!< Capability Information Field, Power Source (bit 2)
    bool m_receiverOnWhenIdle; //!< Capability Information Field, Receiver On When Idle (bit 3)
    uint8_t m_reservedBit45;   //!< Capability Information Field, Reserved (bit 4 & 5)
    bool m_securityCap;        //!< Capability Information Field, Security Capability (bit 6)
    bool m_allocAddr;          //!< Capability Information Field, Allocate Address (bit 7)
};

std::ostream& operator<<(std::ostream& os, const CapabilityField& capabilityField);

} // namespace lrwpan
} // namespace ns3

#endif /* LR_WPAN_FIELDS_H */
