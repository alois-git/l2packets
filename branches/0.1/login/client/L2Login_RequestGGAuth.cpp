#include "stdafx.h"
#include "L2Login_RequestGGAuth.h"

L2Login_RequestGGAuth::L2Login_RequestGGAuth()
{
	this->_initNull();
}

L2Login_RequestGGAuth::L2Login_RequestGGAuth( const unsigned char *bytes, unsigned int length )
{
	this->_initNull();
	this->setBytes( bytes, length );
}

/*L2Login_RequestGGAuth::~L2Login_RequestGGAuth()
{
}*/

// sesionID - 4 bytes array
bool L2Login_RequestGGAuth::create( unsigned char *sessionID )
{
	if( !sessionID ) return false;
	// set packet type
	this->setPacketType( 0x07 );
	// write sessionID
	this->writeUChar( sessionID[0] );
	this->writeUChar( sessionID[1] );
	this->writeUChar( sessionID[2] );
	this->writeUChar( sessionID[3] );
	// write 16 0x00
	int i;
	for( i=0; i<16; i++ ) this->writeUChar( 0x00 );
	return true;
}
