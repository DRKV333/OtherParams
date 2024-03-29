#pragma once

#include "OLRakNetTypes.h"

#include <cstdint>

#define UNIMPLEMENTED(name) virtual void name() final { unimplementedPurecall(#name); }

// This class has virtual methods laid out strategically, so that the vftable will match the one
// from the game's version of RakPeerInterface. The signature and behavior of individual functions
// are usually similar to the open source RakNet version. 
class OLRakPeerInterface
{
private:
	static void unimplementedPurecall(const char* name);

public:
	virtual ~OLRakPeerInterface() = default;

	// Called with maxConnections = 1, _threadSleepTimer = 8, socketDescriptorCount = 1
	virtual bool startup(uint16_t maxConnections, int32_t _threadSleepTimer, void* socketDescriptor, uint32_t socketDescriptorCount, void* logger1, void* logger2) final
	{
		return true;
	};

	// This is called with all 0s after GetRakPeerInterface.
	virtual void initializeSecurity(void* arg1, void* arg2, int arg3, int arg4) final { }

	UNIMPLEMENTED(disableSecurity)
	UNIMPLEMENTED(addToSecurityExceptionList)
	UNIMPLEMENTED(removeFromSecurityExceptionList)
	UNIMPLEMENTED(isInSecurityExceptionList)

	UNIMPLEMENTED(setMaximumIncomingConnections)
	UNIMPLEMENTED(getMaximumIncomingConnections)

	virtual uint16_t numberOfConnections() = 0;
	
	UNIMPLEMENTED(setIncomingPassword)
	UNIMPLEMENTED(getIncomingPassword)

	// Host is provided as a string here, but the game later expects to see parsed uint32s that match what it gets by calling it's own parseIpV4 function.
	// This returns the ip in network byte order. Custom implementations should call this same function to parse addresses (or patch it).
	virtual bool connect(char* host, uint16_t remotePort, char* passwordData, uint32_t passwordDataLenght, uint32_t connectionSocketIndex) = 0;

	UNIMPLEMENTED(shutdown)
	UNIMPLEMENTED(isActive)

	virtual bool getConnectionList(OLSystemAddress* remoteSystems, uint16_t* numberOfSystems) = 0;

	UNIMPLEMENTED(send1)

	// Settings seem to be almost always: 
	// priority = 2 (MEDIUM_PRIORITY)
	// reliability = 3 (RELIABLE_ORDERED)
	// orderingChannel = 0
	// broadcast = false
	virtual bool send2(OLBitStream* stream, uint32_t priority, uint32_t reliability, uint8_t orderingChannel, OLSystemAddress address, bool broadcast) = 0;

	UNIMPLEMENTED(send3)
	UNIMPLEMENTED(send4)
	UNIMPLEMENTED(send5)

	// If the argument is not null, is set by the function to an int somehow derived from maximumNumberOfPeers and endThreads.
	// But it looks like here it's always just a nullptr.
	virtual OLPacket* receive(void* arg) = 0;

	UNIMPLEMENTED(allocatePacket)

	virtual void deallocatePacket(OLPacket* packet) = 0;

	UNIMPLEMENTED(getMaximumNumberOfPeers)

	virtual void closeConnection(OLSystemAddress target, bool sendDisconnectNotification, uint8_t orderingChannel) = 0;
	
	virtual bool isConnected(OLSystemAddress address, bool flag1, bool flag2) = 0;

	UNIMPLEMENTED(GetRemoteSystemFromSystemAddressPub)

	virtual OLSystemAddress* getSystemAddressFromIndex(OLSystemAddress* address, int index) = 0;

	UNIMPLEMENTED(FUN_0174d910)
	UNIMPLEMENTED(FUN_0174d8e0)
	UNIMPLEMENTED(getUIDFromIndex)
	UNIMPLEMENTED(getSystemList)
	UNIMPLEMENTED(addToBanList)
	
	// Set to true after GetRakPeerInterface.
	virtual void setOccasionalPing(bool value) final { }

	UNIMPLEMENTED(setOfflinePingResponse)
	UNIMPLEMENTED(getOfflinePingResponse)
	UNIMPLEMENTED(FUN_0174dd00)
	UNIMPLEMENTED(FUN_0174ddb0)
	UNIMPLEMENTED(getConnectionSocketsLength)
	UNIMPLEMENTED(getInternalID)
	UNIMPLEMENTED(FUN_0174df90)
	UNIMPLEMENTED(FUN_0174e090)
	
	// This is called immediately after GetRakPeerInterface with constants (30000, 0xFFFFFFFF, 0x0000FFFF)
	virtual void unknownCalledBeforeStartup2(uint32_t arg1, uint32_t arg2, uint32_t arg3) final { }
	
	// This is called immediately after GetRakPeerInterface with constants (0x5D4, 0xFFFFFFFF, 0x0000FFFF)
	virtual bool unknownCalledBeforeStartup1(uint32_t arg1, uint32_t arg2, uint32_t arg3) final
	{
		return false;
	}

	UNIMPLEMENTED(FUN_0174e320)
	UNIMPLEMENTED(getNumberOfAddresses)
	UNIMPLEMENTED(getLocalIP)
	UNIMPLEMENTED(isLocalIP)
	UNIMPLEMENTED(allowConnectionResponseIPMigration)
	UNIMPLEMENTED(setSplitMessageProgressInterval)
	UNIMPLEMENTED(getSplitMessageProgressInterval)
	UNIMPLEMENTED(setUnreliableTimeout)
	UNIMPLEMENTED(sendTTL)
	UNIMPLEMENTED(setCompileFrequencyTable)
	UNIMPLEMENTED(getOutgoingFrequencyTable)
	UNIMPLEMENTED(FUN_0174e6d0)
	UNIMPLEMENTED(FUN_0174e760)
	UNIMPLEMENTED(FUN_0174e7f0)
	UNIMPLEMENTED(FUN_0174e850)
	UNIMPLEMENTED(attachPlugin)
	UNIMPLEMENTED(detachPlugin)
	UNIMPLEMENTED(pushBackPacket)
	UNIMPLEMENTED(applyNetworkSimulator)
	UNIMPLEMENTED(setPerConnectionOutgoingBandwidthLimit)
	UNIMPLEMENTED(isNetworkSimulationActive)
	
	// Not sure what this is, but its probably important. It's called periodically.
	// When a peer with the given address is found, or the given address is the unassigned address,
	// it returns a pointer to a large and complicated structure (possibly RakNetSocket2).
	virtual void* FUN_0174ea60(OLSystemAddress address) final
	{
		return nullptr;
	}

	UNIMPLEMENTED(FUN_0174d4c0)
	UNIMPLEMENTED(setLogger)
	UNIMPLEMENTED(FUN_01753ba0)
};

