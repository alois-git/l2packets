#ifndef LOGIN_REQUESTGGAUTH_H_
#define LOGIN_REQUESTGGAUTH_H_

#include "../L2LoginPacket.h"

class L2Login_RequestGGAuth: public L2LoginPacket
{
public:
	L2Login_RequestGGAuth();
	L2Login_RequestGGAuth( const unsigned char *bytes, unsigned int length );
	
public:
	// sesionID - 4 bytes array
	virtual bool create( unsigned char *sessionID );
};

#endif /*LOGIN_REQUESTGGAUTH_H_*/
