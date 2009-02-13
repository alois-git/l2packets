#ifndef LOGIN_INIT_H_
#define LOGIN_INIT_H_

#include "../L2LoginPacket.h"

class L2Login_Init: public L2LoginPacket
{
public:
	L2Login_Init();
	L2Login_Init( const unsigned char *bytes, unsigned int length );
public:
	//virtual bool create();
	
	// after decoding Init packet (removing Blowfish, XOR)
	// sidBytes must point to array 4 bytes long
	virtual bool         read_SessionID( unsigned char *sidBytes );
	virtual unsigned int read_ProtoVer();
	// RSApublicKeyMod must point to buffer 128 bytes len
	virtual bool         read_RSA_pubKeyMod( unsigned char *RSApublicKeyMod );
	// ggShit - 16 bytes buffer; can be NULL
	virtual bool         read_GGShit( unsigned char *ggShit );
	// newBFKey - 16 bytes buffer; can NOT be NULL
	virtual bool         read_DynamicBFKey( unsigned char *newBFKey );
public:
	virtual void         displaySelfNice( FILE *f );
};

#endif /*LOGIN_INIT_H_*/
