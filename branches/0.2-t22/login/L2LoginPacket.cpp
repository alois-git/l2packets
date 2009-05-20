#include "stdafx.h"
#include "L2LoginPacket.h"

//#define L2LOGINP_DEBUGOUT_BLOWFISH // can be defined in L2Packets.h

L2LoginPacket::L2LoginPacket()
{
	_initNull(); // static BF key is initialized there
	// FIXED: dynamic BF initialization moved here from _initNull()
	NEW_BLOWFISH_KEY_LEN = 0;
	memset( (void *)NEW_BLOWFISH_KEY, 0, sizeof(NEW_BLOWFISH_KEY) );
}

L2LoginPacket::L2LoginPacket( const unsigned char *bytes, unsigned int length )
{
	_initNull(); // static BF key is initialized there
	// FIXED: dynamic BF initialization moved here from _initNull()
	NEW_BLOWFISH_KEY_LEN = 0;
	memset( (void *)NEW_BLOWFISH_KEY, 0, sizeof(NEW_BLOWFISH_KEY) );
	this->setBytes( bytes, length );
}

L2LoginPacket::~L2LoginPacket()
{
	_freeSelf();
}

void L2LoginPacket::_initNull()
{
	L2BasePacket::_initNull();
	memset( (void *)STATIC_BLOWFISH_KEY, 0, sizeof(STATIC_BLOWFISH_KEY) );
	STATIC_BLOWFISH_KEY[0]  = 0x6B;
	STATIC_BLOWFISH_KEY[1]  = 0x60;
	STATIC_BLOWFISH_KEY[2]  = 0xCB;
	STATIC_BLOWFISH_KEY[3]  = 0x5B;
	STATIC_BLOWFISH_KEY[4]  = 0x82;
	STATIC_BLOWFISH_KEY[5]  = 0xCE;
	STATIC_BLOWFISH_KEY[6]  = 0x90;
	STATIC_BLOWFISH_KEY[7]  = 0xB1;
	STATIC_BLOWFISH_KEY[8]  = 0xCC;
	STATIC_BLOWFISH_KEY[9]  = 0x2B;
	STATIC_BLOWFISH_KEY[10] = 0x6C;
	STATIC_BLOWFISH_KEY[11] = 0x55;
	STATIC_BLOWFISH_KEY[12] = 0x6C;
	STATIC_BLOWFISH_KEY[13] = 0x6C;
	STATIC_BLOWFISH_KEY[14] = 0x6C;
	STATIC_BLOWFISH_KEY[15] = 0x6C;
	STATIC_BLOWFISH_KEY_LEN = 16;
	// FIXED: _initNull() should *NEVER* touch NEW_BLOWFISH_KEY
	// FIXED: dynamic BF key is changed ONLY by setDynamicBFKey()!
	//NEW_BLOWFISH_KEY_LEN = 0;
	//memset( (void *)NEW_BLOWFISH_KEY, 0, sizeof(NEW_BLOWFISH_KEY) );
	xor_key = 0;
}

bool L2LoginPacket::decodeBlowfish( bool bUseStaticBFKey )
{
	int blen = (int)getPacketSize(); // all array length
	int datalen = blen - 2;      // only data len, w/o 1st 2 bytes - packet size
	int n8bc = datalen / 8;      // 8-byte blocks count
	int rest = datalen - n8bc*8; // ostatok
	if( rest > 0 ) rest = 8;     // nado li dopolnenie
	int newdatalen = datalen + rest; // dlina novogo u4astka dannih
	int newbuflen = newdatalen + 2;  // dlina novogo paketa
	if( blen < 1 ) return false; // TODO: throw?
	
	unsigned char *buf = b.getBytesPtr();
	if( !buf ) return false; // TODO: throw?
	
	// initialize Blowfish key
	BF_KEY bfkey;
	if( bUseStaticBFKey )
		BF_set_key( &bfkey, (int)this->STATIC_BLOWFISH_KEY_LEN,
			this->STATIC_BLOWFISH_KEY );
	else
		BF_set_key( &bfkey, (int)this->NEW_BLOWFISH_KEY_LEN,
			this->NEW_BLOWFISH_KEY );
	
	int offset = 0;
	int nPasses = 0;
	unsigned char *outbuf = NULL;
	
	// we will decode to this buffer
	outbuf = (unsigned char *)malloc( newbuflen );
	if( !outbuf )
	{
#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
		printf( "L2LoginPacket::decodeBlowfish(): memory error!\n" );
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
		return false;
	}
	memset( outbuf, 0, newbuflen );
	outbuf[0] = buf[0]; // copy packet len
	outbuf[1] = buf[1];

	nPasses = 0;
#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
	if( bUseStaticBFKey ) printf( "L2LoginPacket::decodeBlowfish(): using STATIC BF KEY\n" );
	else printf( "L2LoginPacket::decodeBlowfish(): using DYNAMIC BF KEY\n" );
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
	for( offset=2; offset<newdatalen; offset+=8 )
	{
		unsigned char data[8] = {0,0,0,0,0,0,0,0};
		memcpy( data, buf+offset, 8 );
		BF_decrypt( (BF_LONG *)data, &bfkey );
		memcpy( outbuf+offset, data, 8 );
		nPasses++;
	}
#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
	printf( "L2LoginPacket::decodeBlowfish(): Decode2: %d passes, %d 8-byte blocks\n", nPasses, n8bc );
	//L2LoginPacket *dec2 = new L2LoginPacket( outbuf, blen );
	//dec2->dumpToFile( stdout );
	//dec2->saveToFileRaw( "pdecodedbf.dat" );
	//delete dec2;
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
	
	this->setBytes( outbuf, blen );
	free( outbuf );

#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
	printf( "L2LoginPacket::decodeBlowfish(): decode complete\n" );
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
	
	return true;
}

bool L2LoginPacket::decodeXOR()
{
	unsigned int   blen   = getPacketSize();
	unsigned char *packet = b.getBytesPtr();
	if( blen < 1 || !packet ) return false; // TODO: throw?
	if( blen < 186 ) return false; // TODO: throw?
	// get xor key
	// XOR key position to the left from End-of-packet
	//unsigned int xor_offset = 4;
	unsigned int xor_offset = 8;
	xor_key = 0;
	unsigned char b = 0;
	b = packet[ blen - xor_offset ];
	xor_key |= (unsigned int)b;
	b = packet[ blen - xor_offset + 1 ];
	xor_key |= ( (unsigned int)b << 8 );
	b = packet[ blen - xor_offset + 2 ];
	xor_key |= ( (unsigned int)b << 16 );
	b = packet[ blen - xor_offset + 3 ];
	xor_key |= ( (unsigned int)b << 24 );
#ifdef L2LOGINP_DEBUGOUT_XOR
	printf( "L2LoginPacket::decodeXOR(): got XOR key: %04X\n", xor_key );
#endif // L2LOGINP_DEBUGOUT_XOR
	
	// enc xor?
	unsigned int offset = 2;
	unsigned int edx = 0;
	unsigned int ecx = xor_key;
	
	offset = blen - xor_offset - 4;
	while( offset > 2 ) // offset > 3 ?
	{
		edx  = (packet[offset+0] & 0xFF);
		edx |= (packet[offset+1] & 0xFF) << 8;
		edx |= (packet[offset+2] & 0xFF) << 16;
		edx |= (packet[offset+3] & 0xFF) << 24;

		edx ^= ecx;
		ecx -= edx;

		packet[offset+0] = (unsigned char)((edx)       & 0xFF);
		packet[offset+1] = (unsigned char)((edx >>  8) & 0xFF);
		packet[offset+2] = (unsigned char)((edx >> 16) & 0xFF);
		packet[offset+3] = (unsigned char)((edx >> 24) & 0xFF);
		offset -= 4;
	}
	return true;
}

// static function used to decrypt RSA public key modulus from Init packet
// data must be 128-byte long array
bool L2LoginPacket::unscramble_RSA_PubKeyMod( unsigned char *data )
{
	int i;
	// step 4 xor last 0x40 bytes with first 0x40 bytes
	for( i=0; i<0x40; i++ )
		data[0x40 + i] = (unsigned char)(data[0x40 + i] ^ data[i]);
	// step 3 xor bytes 0x0d-0x10 with bytes 0x34-0x38
	for( i=0; i<4; i++ )
		data[0x0d + i] = (unsigned char)(data[0x0d + i] ^ data[0x34 + i]);
	// step 2 xor first 0x40 bytes with last 0x40 bytes
	for( i=0; i<0x40; i++ )
		data[i] = (unsigned char)(data[i] ^ data[0x40 + i]);
	// step 1
	for( i=0; i<4; i++ )
	{
		unsigned char temp = data[0x00 + i];
		data[0x00 + i] = data[0x4d + i];
		data[0x4d + i] = temp;
	}
	return true;
}

bool L2LoginPacket::scramble_RSA_PubKeyMod( unsigned char *data )
{
	int i;
	for( i=0; i<4; i++ )
	{
		unsigned char temp = data[0x00 + i];
		data[0x00 + i] = data[0x4d + i];
		data[0x4d + i] = temp;
	}
	// step 2 xor first 0x40 bytes with last 0x40 bytes
	for( i=0; i<0x40; i++ )
		data[i] = (unsigned char)(data[i] ^ data[0x40 + i]);
	// step 3 xor bytes 0x0d-0x10 with bytes 0x34-0x38
	for( i=0; i<4; i++ )
		data[0x0d + i] = (unsigned char)(data[0x0d + i] ^ data[0x34 + i]);
	// step 4 xor last 0x40 bytes with first 0x40 bytes
	for( i=0; i<0x40; i++ )
		data[0x40 + i] = (unsigned char)(data[0x40 + i] ^ data[i]);
	return true;
}

bool L2LoginPacket::setDynamicBFKey( unsigned char *newKey, unsigned int newKeyLen )
{
	if( !newKey ) return false;
	if( newKeyLen < 1 ) return false;
	memcpy( this->NEW_BLOWFISH_KEY, newKey, newKeyLen );
	this->NEW_BLOWFISH_KEY_LEN = newKeyLen;
#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
	printf( "L2LoginPacket::setDynamicBFKey(): set dynamic BF key of len = %u\n",
		newKeyLen );
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
	return true;
}

/*bool L2LoginPacket::appendChecksum()
{
	// save packet len bytes
	//unsigned char plenbytes[2] = {0,0}
	//plenbytes[0] = b.getByteAt( 0 );
	//plenbytes[1] = b.getByteAt( 1 );
	// get packet length
	unsigned int count = this->getPacketSize();
	if( count > 2 )
	{
		unsigned char *rawbytes = b.getBytesPtr();
		unsigned int chksum = 0;
		unsigned int i = 0;
		for( i=2; i<count; i += 4 ) chksum ^= *( (unsigned int *)&rawbytes[i] );
		this->writeUInt( chksum );
		// restore plen bytes
		//b.setByteAt( 0, plenbytes[0] );
		//b.setByteAt( 1, plenbytes[1] );
		return true;
	}
	return false;
}*/

bool L2LoginPacket::appendChecksum( bool append4bytes )
{
	unsigned char *raw = b.getBytesPtr();
	int size = (int)this->real_size;
	unsigned int chksum = 0;
	int count = size; // size-4; // we do not reserve space for checksum
	unsigned int ecx = 0;
	int i = 0;
	int offset = 2;
#ifdef L2LOGINP_DEBUGOUT_CHKSUM
	printf( "L2LoginPacket::appendChecksum(): for( i=%d; i<%d; i+=4)\n",
		offset, count );
#endif // L2LOGINP_DEBUGOUT_CHKSUM
	for( i = offset; i<count; i+=4 )
	{
		ecx  = (raw[i])           & 0x000000ff;
		ecx |= (raw[i+1] << 0x08) & 0x0000ff00;
		ecx |= (raw[i+2] << 0x10) & 0x00ff0000;
		ecx |= (raw[i+3] << 0x18) & 0xff000000;

		chksum ^= ecx;
	}

	ecx  = raw[i]           & 0x000000ff;
	ecx |= raw[i+1] << 0x08 & 0x0000ff00;
	ecx |= raw[i+2] << 0x10 & 0x00ff0000;
	ecx |= raw[i+3] << 0x18 & 0xff000000;

	// write chksum to end of packet
	/*/// L2J style :)
	raw[i]   = (unsigned char)((chksum)         & 0xff);
	raw[i+1] = (unsigned char)((chksum >> 0x08) & 0xff);
	raw[i+2] = (unsigned char)((chksum >> 0x10) & 0xff);
	raw[i+3] = (unsigned char)((chksum >> 0x18) & 0xff);
	*/
	//this->write_ptr = i+4;
	
#ifdef L2LOGINP_DEBUGOUT_CHKSUM
	printf( "L2LoginPacket::appendChecksum(): writing chksum [%04X] at indexes [%d..%d]\n",
		chksum, this->write_ptr, this->write_ptr+3 );
#endif // L2LOGINP_DEBUGOUT_CHKSUM
	
	writeUChar( (unsigned char)((chksum)         & 0xff) );
	writeUChar( (unsigned char)((chksum >> 0x08) & 0xff) );
	writeUChar( (unsigned char)((chksum >> 0x10) & 0xff) );
	writeUChar( (unsigned char)((chksum >> 0x18) & 0xff) );
	// Should we also automatically append 4 0x00 symbols to packet?
	// Before calling appendChecksum(), packet is considered to be
	// aligned at 8-byte border, so adding 4 bytes of checksum
	// breaks this alignment. And adding more 4 zero bytes will
	// resore 8-byte border alignment.
	// But sometimes this adding is not necessary, for example,
	// when encoding packet from Login Server to Client.
	if( append4bytes )
	{
		writeUChar( 0x00 );
		writeUChar( 0x00 );
		writeUChar( 0x00 );
		writeUChar( 0x00 );
	}
	return true;
}

bool L2LoginPacket::padPacketTo8ByteLen()
{
	unsigned char *packet = b.getBytesPtr();
	unsigned int plen = getPacketSize();
	if( !packet || plen<3 ) return false;
	unsigned int datalen = plen-2;
	
#ifdef L2LOGINP_DEBUGOUT_PADDING
	printf( "L2LoginPacket::padPacketTo8ByteLen(): len = %u (data len = %d)\n",
		plen, datalen );
#endif // L2LOGINP_DEBUGOUT_PADDING
	
	unsigned int rest = datalen % 8;
	unsigned int addsize = 0;
	if( rest > 0 ) addsize = 8 - rest;
	
#ifdef L2LOGINP_DEBUGOUT_PADDING
	printf( "L2LoginPacket::padPacketTo8ByteLen(): We should add %u bytes (rest is %u)\n",
		addsize, rest );
#endif // L2LOGINP_DEBUGOUT_PADDING
	
	// save packet len bytes
	//unsigned char plenbytes[2] = {0,0};
	//plenbytes[0] = b.getByteAt( 0 );
	//plenbytes[1] = b.getByteAt( 1 );
	
	// append by NULLs if we must append something
	if( addsize > 0 )
	{
		unsigned int i;
		for( i=0; i<addsize; i++ ) this->writeUChar( 0x00 );
		// restore plen bytes
		//b.setByteAt( 0, plenbytes[0] );
		//b.setByteAt( 1, plenbytes[1] );
#ifdef L2LOGINP_DEBUGOUT_PADDING
		printf( "L2LoginPacket::padPacketTo8ByteLen(): "
				"after padding real_size = [%u] ==== \n", this->real_size );
		//this->dumpToFile( stdout );
#endif // L2LOGINP_DEBUGOUT_PADDING
	}
	
	return true;
}

bool L2LoginPacket::appendMore8Bytes()
{
	int i;
	for( i=0; i<8; i++ ) writeUChar( 0x00 );
	return true;
}

bool L2LoginPacket::encodeBlowfish( bool bUseStaticBFKey )
{
	unsigned char *buf = this->b.getBytesPtr();
	if( !buf ) return false; // TODO: throw
	unsigned int blen = getPacketSize();
	if( blen < 1 ) return false; // TODO: throw
	//unsigned int datalen = blen - 2; // C4189: local variable is initialized but not referenced
	//this->padPacketTo8ByteLen(); // manually
	
	// initialize Blowfish key
	BF_KEY bfkey;
	if( bUseStaticBFKey )
		BF_set_key( &bfkey, (int)this->STATIC_BLOWFISH_KEY_LEN,
			this->STATIC_BLOWFISH_KEY );
	else
		BF_set_key( &bfkey, (int)this->NEW_BLOWFISH_KEY_LEN,
			this->NEW_BLOWFISH_KEY );
	
	unsigned int offset = 0;
	int nPasses = 0;
	unsigned char *outbuf = NULL;

	// we will decode to this buffer
	outbuf = (unsigned char *)malloc( blen );
	if( !outbuf )
	{
#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
		printf( "L2LoginPacket::encodeBlowfish(): memory error!\n" );
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
		return false;
	}
	memset( outbuf, 0, blen );
	outbuf[0] = buf[0]; // copy packet len
	outbuf[1] = buf[1];

#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
	if( bUseStaticBFKey ) printf( "L2LoginPacket::encodeBlowfish(): using STATIC BF KEY\n" );
	else printf( "L2LoginPacket::encodeBlowfish(): using DYNAMIC BF KEY\n" );
	printf( "L2LoginPacket::encodeBlowfish(): blen = %u, datalen = %u\n",
		blen, datalen );
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
	for( offset=2; offset<real_size-2; offset+=8 )
	{
		unsigned char data[8] = {0,0,0,0,0,0,0,0};
		memcpy( data, buf+offset, 8 );
		BF_encrypt( (BF_LONG *)data, &bfkey );
		memcpy( outbuf+offset, data, 8 );
		nPasses++;
	}
#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
	int n8bc = datalen / 8;
	printf( "L2LoginPacket::encodeBlowfish(): %d passes, %d 8-byte blocks ==\n",
		nPasses, n8bc );
	//L2LoginPacket dec2; // = new L2LoginPacket();
	//printf( "here\n" );
	//bool bret = dec2.setBytes( outbuf, real_size );
	//if( bret ) printf( "true\n" ); else printf( "false\n" );
	//dec2.dumpToFile( stdout );
	//delete dec2;
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
	
	this->setBytes( outbuf, blen );
	free( outbuf );
	
#ifdef L2LOGINP_DEBUGOUT_BLOWFISH
	printf( "L2LoginPacket::encodeBlowfish(): encode complete\n" );
#endif // L2LOGINP_DEBUGOUT_BLOWFISH
	return true;
}

