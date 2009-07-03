#ifndef L2GAME_CHARSELECTED_H_
#define L2GAME_CHARSELECTED_H_

#include "../L2GamePacket.h"

class L2Game_CharSelected : public L2GamePacket
{
public:
	L2Game_CharSelected();
	L2Game_CharSelected( const unsigned char *bytes, unsigned int length );
public:
	virtual bool parse( L2_VERSION ver = L2_VERSION_T1 );
	virtual bool create( L2_VERSION ver = L2_VERSION_T1 );
public:
	wchar_t char_name[128]; // char name
	unsigned int charId; // char id (objectId)
	wchar_t title[128];  // title (empty here)
	unsigned int sessionId;  // sessionId
	unsigned int clanId; // clan id
	int sex; // sex
	int race; // race 0x01 - elf
	unsigned int classId;  // class Id
	int isActive;  // is Active
	int x;
	int y;
	int z;
	double curHp; // currentHp
	double curMp; // currentMp
	unsigned int sp; // sp
	unsigned long long int exp; // exp
	int level; // level (64)
	int karma; // karma
	int PK_kills; // PK kills
	int s_INT; // INT
	int s_STR; // STR
	int s_CON; // CON
	int s_MEN; // MEN
	int s_DEX; // DEX
	int s_WIT; // WIT
	unsigned int opcodeObfuscatorSeed; // opcode obfuscator seed
};

#endif
