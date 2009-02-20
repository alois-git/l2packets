#ifndef H_L2NPC
#define H_L2NPC
#include "L2Character.h"

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
Every L2Npc has templateID
Every L2Npc can be attackable or not
Every L2Npc has weapon in left and in right hand
*/

class L2Npc : public L2Character
{
public:
	L2Npc();
	virtual ~L2Npc() { L2Character::~L2Character(); templateID = 0; }
public:
	virtual void setUnused();
public:
	virtual void setNpcNameByTemplate();
	virtual void setNpcTitleByTemplate();
public:
	unsigned int templateID;
	int isAttackable;
	// weapon items
	unsigned int iid_left_hand;
	unsigned int iid_right_hand;
};

#endif
