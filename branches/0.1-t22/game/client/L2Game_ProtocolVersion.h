#ifndef L2GAME_PROTOCOLVERSION_H_
#define L2GAME_PROTOCOLVERSION_H_

#include "../L2GamePacket.h"

class L2Game_ProtocolVersion : public L2GamePacket
{
public:
	L2Game_ProtocolVersion();
	L2Game_ProtocolVersion( const unsigned char *bytes, unsigned int length );
public:
	bool create( unsigned int gameProtoVer );
	bool createDefaultKamael( unsigned int gameProtoVer = 828 );
	bool createDefaultHellbound( unsigned int gameProtoVer = 831 );
	bool createDefaultGracia1( unsigned int gameProtoVer = 851 );
	bool createDefaultGracia2( unsigned int gameProtoVer = 12 );
	bool createDefaultGracia3( unsigned int gameProtoVer = 15 ); // TODO: in future
	bool read_protoVer( unsigned int *pver );
};

#endif /*L2GAME_PROTOCOLVERSION_H_*/
