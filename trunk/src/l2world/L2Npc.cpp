#include "stdafx.h"
#include "L2Npc.h"
#include "../l2data/L2Data.h"

L2Npc::L2Npc()
{
	setUnused();
}

void L2Npc::setUnused()
{
	L2Character::setUnused();
	templateID = 0;
	isAttackable = 0;
	// weapon
	iid_left_hand = iid_right_hand = 0;
}

void L2Npc::setNpcNameByTemplate()
{
}

void L2Npc::setNpcTitleByTemplate()
{
}
