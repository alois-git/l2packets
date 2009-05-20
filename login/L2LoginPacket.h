#ifndef H_L2LOGINPACKET
#define H_L2LOGINPACKET

#include "../base/L2BasePacket.h"

class L2LoginPacket: public L2BasePacket
{
public:
	L2LoginPacket();
	L2LoginPacket( const unsigned char *bytes, unsigned int length );
	virtual ~L2LoginPacket();
public:
	// static BF key used when decoding Init packet
	virtual bool         decodeBlowfish( bool bUseStaticBFKey );
	// used also only when decoding init packet, immediately after BF decoding
	virtual bool         decodeXOR();
public:
	// static function used to decrypt RSA public key modulus from Init packet
	// data must be 128-byte long array
	static bool          unscramble_RSA_PubKeyMod( unsigned char *data );
	// static function used to encrypt RSA public key modulus from Init packet
	// data must be 128-byte long array
	static bool          scramble_RSA_PubKeyMod( unsigned char *data );
public:
	// appends checksum to packet
	virtual bool         appendChecksum( bool append4bytes );
	virtual bool         padPacketTo8ByteLen();
	virtual bool         appendMore8Bytes();
	// sets dynamic Blowfish key (taken from Init packet)
	// newKey must point at 16 bytes long buffer
	virtual bool         setDynamicBFKey( unsigned char *newKey, unsigned int newKeyLen );
	virtual bool         encodeBlowfish( bool bUseStaticBFKey );
protected:
	virtual void _initNull();
protected:
	unsigned char STATIC_BLOWFISH_KEY[32];
	unsigned int  STATIC_BLOWFISH_KEY_LEN;
	unsigned char NEW_BLOWFISH_KEY[32];
	unsigned int  NEW_BLOWFISH_KEY_LEN;
	unsigned int  xor_key;
};

#endif /* H_L2LOGINPACKET */
