#include "stdafx.h"
#include "L2Login_PlayFail.h"

/*
writeC(0x06);
writeC(_reason.getCode());
*/

L2Login_PlayFail::L2Login_PlayFail()
{
	this->_initNull();
}

L2Login_PlayFail::L2Login_PlayFail( const unsigned char *bytes, unsigned int length )
{
	this->_initNull();
	this->setBytes( bytes, length );
}

unsigned char L2Login_PlayFail::read_reason()
{
	if( this->canReadBytes(2) )
	{
		this->readReset();
		this->readUChar();
		return this->readUChar();
	}
	return 0;
}

// str must point to buffer at least 32 bytes long
bool L2Login_PlayFail::getReasonStr( unsigned char code, char *str )
{
	if( !str ) return false;
	strcpy( str, "REASON_UNKNOWN" );
	switch( code )
	{
	case L2PF_REASON_SYSTEM_ERROR: strcpy( str, "REASON_SYSTEM_ERROR" ); break;       
	case L2PF_REASON_USER_OR_PASS_WRONG: strcpy( str, "REASON_USER_OR_PASS_WRONG" ); break; 
	case L2PF_REASON3: strcpy( str, "REASON3" ); break;
	case L2PF_REASON4: strcpy( str, "REASON4" ); break;
	case L2PF_REASON_TOO_MANY_PLAYERS: strcpy( str, "REASON_TOO_MANY_PLAYERS" ); break;
	}
	return true;
}
