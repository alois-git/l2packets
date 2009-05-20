#ifndef L2GAME_KEYPACKET_H_
#define L2GAME_KEYPACKET_H_

#include "../L2GamePacket.h"

class L2Game_KeyPacket : public L2GamePacket
{
public:
	L2Game_KeyPacket();
	L2Game_KeyPacket( const unsigned char *bytes, unsigned int length );
public:
	// key must point to buffer large enough to hold 8 bytes
	bool          read_key( unsigned char *key );
	unsigned char read_GameServerID();
	unsigned int  read_OpcodeObfuscator();
public:
	// keyPacket array points to key bytes received from KeyPacket (8 bytes)
	// keyResult will hold resultig key (16 bytes)
	static void createInitialHellboundKey(
		const unsigned char *keyPacket,
		unsigned char *keyResult );
};

#endif /*L2GAME_KEYPACKET_H_*/
