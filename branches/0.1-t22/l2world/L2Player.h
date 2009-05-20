#ifndef H_L2PLAYER
#define H_L2PLAYER
#include "L2Character.h"
#include "L2PlayerpaperDoll.h"

/*
Every L2Npc is L2Character:
Every L2Character is L2Object (has objectID, x, y, z)
Every L2Character has LEVEL!
Every L2Character has its charName and charTitle
Every L2Character has its heading
Every L2Character has moving speed in states: running, walking
Every L2Character has its move destination: xDst, yDst, zDst
Every l2Character can calc its position based on destnation point and time passed since last calc
Every L2Character has its base stats: INT WIT MEN CON STR DEX
Every L2Character has its stats: pAtk, mAtk, ..., curHp, maxHp, ...
Every L2Character has abnormalEffect
Every L2Character has its target

Additionally:
Every L2Player has classID, baseClassID
Every L2Player has its appearance (Race, Sex, ...)
Every L2Player has its clan, ally
Every L2Player has its pvpFlag, karma
Every L2Player has enchantEffect

Additionally, some values come from RelationChanged packet, not in CharInfo
Every L2Player has relation to current user
Every L2Player can be autoAttackable

Every L2Player has its paperdoll: items equipped on it.
*/

class L2Player : public L2Character
{
public:
	L2Player();
	virtual ~L2Player() { setUnused(); }
public:
	virtual void setUnused();
public:
	virtual void getRaceStr( wchar_t *out ) const;
	virtual void getSexStr( wchar_t *out ) const;
	virtual void getClassStr( wchar_t *out ) const;
	virtual void getBaseClassStr( wchar_t *out ) const;

public:
	static const int RELATION_NONE         = 0;
	static const int RELATION_PVP_FLAG     = 0x00002; // pvp ???
	static const int RELATION_HAS_KARMA    = 0x00004; // karma ???
	static const int RELATION_LEADER       = 0x00080; // leader
	static const int RELATION_INSIEGE      = 0x00200; // true if in siege
	static const int RELATION_ATTACKER     = 0x00400; // true when attacker
	static const int RELATION_ALLY         = 0x00800; // blue siege icon, cannot have if red
	static const int RELATION_ENEMY        = 0x01000; // true when red icon, doesn't matter with blue
	static const int RELATION_MUTUAL_WAR   = 0x08000; // double fist
	static const int RELATION_1SIDED_WAR   = 0x10000; // single fist

public:
	unsigned int classID;
	unsigned int baseClassID;
	int race;
	int sex;
	unsigned int clanID;
	int pvpFlag;
	int karma;
	unsigned int enchantEffect;
	// from RelationChanged
	unsigned int relation;
	int autoAttackable;
	unsigned int paperdoll_iid[32]; // really there are 30 slots, but for align ^^
	int isFakeDeath;
};

#endif
