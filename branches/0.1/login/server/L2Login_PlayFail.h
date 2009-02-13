#ifndef L2LOGIN_PLAYFAIL_H_
#define L2LOGIN_PLAYFAIL_H_

#include "../L2LoginPacket.h"

#define L2PF_REASON_SYSTEM_ERROR       0x01
#define L2PF_REASON_USER_OR_PASS_WRONG 0x02
#define L2PF_REASON3                   0x03
#define L2PF_REASON4                   0x04
#define L2PF_REASON_TOO_MANY_PLAYERS   0x0f

class L2Login_PlayFail : public L2LoginPacket
{
public:
	L2Login_PlayFail();
	L2Login_PlayFail( const unsigned char *bytes, unsigned int length );
public:
	unsigned char read_reason();
	// str must point to buffer at least 32 bytes long
	static bool getReasonStr( unsigned char code, char *str );
};

#endif /*L2LOGIN_PLAYFAIL_H_*/
