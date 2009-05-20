#ifndef L2LOGIN_LOGINFAIL_H_
#define L2LOGIN_LOGINFAIL_H_

#include "../L2LoginPacket.h"

#define L2LF_REASON_SYSTEM_ERROR         0x01
#define L2LF_REASON_PASS_WRONG           0x02
#define L2LF_REASON_USER_OR_PASS_WRONG   0x03
#define L2LF_REASON_ACCESS_FAILED        0x04
#define L2LF_REASON_ACCOUNT_IN_USE       0x07
#define L2LF_REASON_SERVER_OVERLOADED    0x0f
#define L2LF_REASON_SERVER_MAINTENANCE   0x10
#define L2LF_REASON_TEMP_PASS_EXPIRED    0x11
#define L2LF_REASON_DUAL_BOX             0x23

class L2Login_LoginFail : public L2LoginPacket
{
public:
	L2Login_LoginFail();
	L2Login_LoginFail( const unsigned char *bytes, unsigned int length );
public:
	unsigned int read_reason();
	// converts login fail code to human-readable error string :)
	// s must point to buffer at least 32 bytes long
	static void getReasonStr( unsigned int code, char *s );
};

#endif /*L2LOGIN_LOGINFAIL_H_*/
