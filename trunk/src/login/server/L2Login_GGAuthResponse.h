#ifndef LOGIN_GGAUTHRESPONSE_H_
#define LOGIN_GGAUTHRESPONSE_H_

#include "../L2LoginPacket.h"

class L2Login_GGAuthResponse : public L2LoginPacket
{
public:
	L2Login_GGAuthResponse();
	L2Login_GGAuthResponse( const unsigned char *bytes, unsigned int length );
public:
	unsigned int read_Response();
};

#endif /*LOGIN_GGAUTHRESPONSE_H_*/
