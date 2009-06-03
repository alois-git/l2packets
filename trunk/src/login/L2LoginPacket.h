#ifndef H_L2LOGINPACKET
#define H_L2LOGINPACKET

#include "../base/L2BasePacket.h"

/** \class L2LoginPacket
 * A base class for all login server communication packets.
 * Includes functions to handle Blowfish encryption/decryption and checksum calculations. */

class L2LoginPacket: public L2BasePacket
{
public:
	/** Default constructor */
	L2LoginPacket();
	/** Constructs object and calls setBytes() with parameters bytes, length
	 * \param bytes data to set
	 * \param length data size */
	L2LoginPacket( const unsigned char *bytes, unsigned int length );
	virtual ~L2LoginPacket();
public:
	/** Does Blowfish decryption of packet data.
	 * \param bUseStaticBFKey set to true to use static BF key, or false to dynamic.
	          Dynamic BF key must be set before by setDynamicBFKey()
	 * \return success status */
	virtual bool         decodeBlowfish( bool bUseStaticBFKey );
public:
	/** Appends checksum to packet
	 * \param append4bytes in Hellbound, set to true to keep packet data length 8-byte aligned */
	virtual bool         appendChecksum( bool append4bytes = true );
	/** Does padding of packet data by zeroes to 8-byte border (before BF encryption) */
	virtual bool         padPacketTo8ByteLen();
	/** In Hellbound, packets are padded by more 8 zero bytes after adding checksum & 4 bytes */
	virtual bool         appendMore8Bytes();
	/** Sets dynamic Blowfish key (which is taken from Init packet)
	 * \param newKey must point at 16 bytes buffer
	 * \param newKeyLen currently must be = 16 */
	virtual bool         setDynamicBFKey( unsigned char *newKey, unsigned int newKeyLen );
	/** Does Blowfish encryption.
	 * \param bUseStaticBFKey set to true to use static BF key, or false to dynamic.
	          Dynamic BF key must be set before by setDynamicBFKey()
	 * \return success status */
	virtual bool         encodeBlowfish( bool bUseStaticBFKey );
protected:
	/** Also initializes STATIC_BF_KEY, which is constant. */
	virtual void _initNull();
protected:
	unsigned char STATIC_BLOWFISH_KEY[32]; ///< Static Blowfish key (First packet from login server is encrypted by this)
	unsigned int  STATIC_BLOWFISH_KEY_LEN; ///< length of static BF key
	unsigned char NEW_BLOWFISH_KEY[32]; ///< Buffer to hold dynamic blowfish key
	unsigned int  NEW_BLOWFISH_KEY_LEN; ///< Dynamic BF key size
	unsigned int  xor_key; ///< current XOR key (for Init packet)
};

#endif /* H_L2LOGINPACKET */
