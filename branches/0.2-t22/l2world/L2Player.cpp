#include "stdafx.h"
#include "L2Player.h"
#include "../l2data/L2Data.h"

L2Player::L2Player()
{
	setUnused();
}

void L2Player::setUnused()
{
	L2Character::setUnused();
	classID = baseClassID = 0;
	clanID = clanCrestID = clanCrestLargeID = allyID = allyCrestID = 0;
	race = sex = 0;
	hairStyle = hairColor = face = 0;
	relation = RELATION_NONE;
	autoAttackable = 0;
	int i;
	for( i=0; i<32; i++ )
	{
		paperdoll_iid[i] = 0;
		paperdoll_augid[i] = 0;
	}
	isFishing = 0;
	fishX = fishY = fishZ = 0;
	privateStoreType = 0;
	privateStoreMsgBuy[0] = privateStoreMsgSell[0] = privateStoreMsgRecipe[0] = 0;
	mountType = mountNpcId = 0;
	recomLeft = recomHave = 0;
	isNoble = isHero = 0;
}

void L2Player::getRaceStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getRace( this->race );
#ifdef L2PACKETS_WINDOWS
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
#endif
#ifdef L2PACKETS_LINUX
	swprintf( out, 64, L"%ls", ansi );
#endif
}

void L2Player::getSexStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getSex( this->sex );
#ifdef L2PACKETS_WINDOWS
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
#endif
#ifdef L2PACKETS_LINUX
	swprintf( out, 64, L"%ls", ansi );
#endif
}

void L2Player::getClassStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getClass( this->classID );
#ifdef L2PACKETS_WINDOWS
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
#endif
#ifdef L2PACKETS_LINUX
	swprintf( out, 64, L"%ls", ansi );
#endif
}

void L2Player::getBaseClassStr( wchar_t *out ) const
{
	if( !out ) return;
	out[0] = 0;
	const char *ansi = L2Data_getClass( this->baseClassID );
#ifdef L2PACKETS_WINDOWS
	if( ansi ) MultiByteToWideChar( CP_ACP, 0, ansi, -1, out, 64 );
#endif
#ifdef L2PACKETS_LINUX
	swprintf( out, 64, L"%ls", ansi );
#endif
}
