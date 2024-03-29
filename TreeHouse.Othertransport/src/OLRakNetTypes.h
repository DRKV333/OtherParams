#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>

struct OLSystemAddress
{
	uint32_t ip;
	uint16_t port;

	bool operator==(const OLSystemAddress&) const = default;

	static const OLSystemAddress unassigned;
};

inline constexpr OLSystemAddress OLSystemAddress::unassigned = { 0xFFFFFFFF, 0xFFFF };

static_assert(sizeof(OLSystemAddress) == 8);
static_assert(std::is_standard_layout_v<OLSystemAddress>);
static_assert(offsetof(OLSystemAddress, ip)   == 0);
static_assert(offsetof(OLSystemAddress, port) == 4);

struct OLRakNetGUID
{
	uint32_t g[4];

	static const OLRakNetGUID unassigned;
};

inline constexpr OLRakNetGUID OLRakNetGUID::unassigned = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

static_assert(sizeof(OLRakNetGUID) == 16);
static_assert(std::is_standard_layout_v<OLRakNetGUID>);

struct OLPacket
{
	uint16_t systemIndex;
	OLSystemAddress systemAddress;
	OLRakNetGUID systemGUID;
	uint32_t length;
	uint32_t lengthBits;
	char* data;
	bool deleteData;

	static const uint16_t unassignedSystemIndex;
};

inline constexpr uint16_t OLPacket::unassignedSystemIndex = 0xFFFF;

static_assert(sizeof(OLPacket) == 44);
static_assert(std::is_standard_layout_v<OLPacket>);
static_assert(offsetof(OLPacket, systemIndex)   == 0);
static_assert(offsetof(OLPacket, systemAddress) == 4);
static_assert(offsetof(OLPacket, systemGUID)    == 12);
static_assert(offsetof(OLPacket, length)        == 28);
static_assert(offsetof(OLPacket, lengthBits)    == 32);
static_assert(offsetof(OLPacket, data)          == 36);
static_assert(offsetof(OLPacket, deleteData)    == 40);

enum OLDefaultMessageIDTypes : char
{
	// In a client/server environment, our connection request to the server has been accepted.
	OL_ID_CONNECTION_REQUEST_ACCEPTED = 0x0B,

	// Sent to the player when a connection request cannot be completed due to inability to connect.
	OL_ID_CONNECTION_ATTEMPT_FAILED = 0x0C,

	// This signals a successful client initiated disconnection.
	OL_ID_DISCONNECTION_NOTIFICATION = 0x10,

	// This signals an unexpected disconnection.
	OL_ID_CONNECTION_LOST = 0x11
};

struct OLBitStream
{
	uint32_t numberOfBitsUsed;
	uint32_t numberOfBitsAllocated;
	uint32_t readOffset;
	char* data;
	bool copyData;
	char stackData[1024];

	uint32_t getNumberOfBytesUsed() const
	{
		return (numberOfBitsUsed + 7) >> 3;
	}

	uint32_t getNumberOfBytesAllocated() const
	{
		return (numberOfBitsAllocated + 7) >> 3;
	}
};

static_assert(sizeof(OLBitStream) == 1044);
static_assert(std::is_standard_layout_v<OLBitStream>);
static_assert(offsetof(OLBitStream, numberOfBitsUsed)      == 0);
static_assert(offsetof(OLBitStream, numberOfBitsAllocated) == 4);
static_assert(offsetof(OLBitStream, readOffset)            == 8);
static_assert(offsetof(OLBitStream, data)                  == 12);
static_assert(offsetof(OLBitStream, copyData)              == 16);
static_assert(offsetof(OLBitStream, stackData)             == 17);
