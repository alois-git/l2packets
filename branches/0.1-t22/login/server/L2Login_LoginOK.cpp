#include "stdafx.h"
#include "L2Login_LoginOK.h"

/* L2J
   protected void write()
	{
		writeC(0x03);
		writeD(_loginOk1);
		writeD(_loginOk2);
		writeD(0x00);
		writeD(0x00);
		writeD(0x000003ea);
		writeD(0x00);
		writeD(0x00);
		writeD(0x00);
		writeB(new byte[16]);
	}
*/

L2Login_LoginOK::L2Login_LoginOK()
{
	this->_initNull();
}

L2Login_LoginOK::L2Login_LoginOK( const unsigned char *bytes, unsigned int length )
{
	this->_initNull();
	this->setBytes( bytes, length );
}

// read SessionKey #1 from packet
// sessionKey1 must point to 8-byte array
bool L2Login_LoginOK::read_sessionKey1( unsigned char *sessionKey1 )
{
	if( !sessionKey1 ) return false;
	// check packet size
	if( this->real_size < 9 ) return false;
	this->readReset();
	this->readUChar(); // pass packet code byte
	this->readBytes( sessionKey1, 8 ); // read 8 bytes of sessionKey1
	return true;
}
