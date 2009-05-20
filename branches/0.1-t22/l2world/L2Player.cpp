#include "stdafx.h"
#include "L2Player.h"
#include "../l2data/L2Data.h"

L2Player::L2Player()
{
	//memset( this, 0, sizeof(class L2Player) );
	//stopMove();
	setUnused();
}

void L2Player::setUnused()
{
	L2Character::setUnused();
	classID = baseClassID = clanID = 0;
	race = sex = 0;
	relation = RELATION_NONE;
	autoAttackable = 0;
	int i;
	for( i=0; i<32; i++ ) paperdoll_iid[i] = 0;
}

void L2Player::getRaceStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getRace( this->race );
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
}

void L2Player::getSexStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getSex( this->sex );
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
}

void L2Player::getClassStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getClass( this->classID );
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
}

void L2Player::getBaseClassStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getClass( this->baseClassID );
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
}
