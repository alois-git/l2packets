#ifndef L2GAME_CHARSELECTED_H_
#define L2GAME_CHARSELECTED_H_

#include "../L2GamePacket.h"

class L2Game_CharSelected : public L2GamePacket
{
public:
	L2Game_CharSelected();
	L2Game_CharSelected( const unsigned char *bytes, unsigned int length );
public:
};

#endif
