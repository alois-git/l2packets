#include "stdafx.h"
#include "L2Character.h"
#include "../game/L2GamePacket.h"

L2Character::L2Character()
{
	//memset( this, 0, sizeof(class L2Character) );
	//stopMove();
	setUnused();
}

void L2Character::setUnused()
{
	L2Object::setUnused();
	stopMove();
	charName[0] = charTitle[0] = 0;
	level = 0;
	heading = 0;
	runSpeed = walkSpeed = isRunning = 0;
	lastMoveTickTime = 0;
	curHp = maxHp = curMp = maxMp = curCp = maxCp = 0.0;
	abnormalEffect = 0;
	targetObjectID = 0;
	isAlikeDead = 0;
	isSitting = 0;
	isRunning = 0;
}

void L2Character::setName( const wchar_t *name )
{
	if( name )
	{
		wcsncpy( charName, name, sizeof(charName)/sizeof(charName[0]) - 1 );
		charName[ sizeof(charName)/sizeof(charName[0]) - 1 ] = 0;
	}
}

void L2Character::setTitle( const wchar_t *title )
{
	if( title )
	{
		wcsncpy( charTitle, title, sizeof(charTitle)/sizeof(charTitle[0]) - 1 );
		charTitle[ sizeof(charTitle)/sizeof(charTitle[0]) - 1 ] = 0;
	}
}

const wchar_t *L2Character::getName()
{
	this->charName[sizeof(this->charName) - 1] = 0;
	return (const wchar_t *)(this->charName);
}

const wchar_t *L2Character::getTitle()
{
	this->charTitle[sizeof(this->charTitle) - 1] = 0;
	return (const wchar_t *)(this->charTitle);
}

bool L2Character::parse_MoveToLocation( void *l2_game_packet )
{
	L2GamePacket *p = (L2GamePacket *)l2_game_packet;
	p->getPacketType();
	unsigned int oid = p->readUInt();
	if( oid != this->objectID ) return false; // not my move
	xDst = p->readInt();
	yDst = p->readInt();
	zDst = p->readInt();
	x = p->readInt();
	y = p->readInt();
	z = p->readInt();
	this->lastMoveTickTime = GetTickCount(); // last time when x,y,z, xDst,yDst,zDst were known exactly
	return true;
}

void L2Character::processMoveTick()
{
	unsigned int curTick = GetTickCount();
	unsigned int millisecsPassed = curTick - lastMoveTickTime;
	if( millisecsPassed < 100 ) return;
	lastMoveTickTime = curTick;
	const int near_range = 50;
	if( isMoving() )
	{
		int dx = xDst - x;
		int dy = yDst - y;
		int dz = zDst - z;
		if( ((dx > -near_range)&&(dx < near_range)) && 
			((dy > -near_range)&&(dy < near_range)) && 
			((dz > -near_range)&&(dz < near_range)) ) // target ~ reached?
		{
			stopMove();
			return;
		}
		float useSpeed = (float)runSpeed;
		if( isRunning ) useSpeed = (float)walkSpeed;
		float secs = ((float)millisecsPassed) / 1000;
		float movedDist = useSpeed * secs;
		float totalDist = sqrtf( (float)(dx*dx + dy*dy) );
		float k = totalDist / movedDist;
		if( k < 1.1 ) // cannot be < 1
		{
			stopMove();
			return;
		}
		float xDelta = (float)dx / k;
		float yDelta = (float)dy / k;
		x += (int)xDelta;
		y += (int)yDelta;
	}
}

void L2Character::startMoveTo( int mxd, int myd, int mzd, int mx, int my, int mz )
{
	x = mx;
	y = my;
	z = mz;
	xDst = mxd;
	yDst = myd;
	zDst = mzd;
	lastMoveTickTime = GetTickCount();
}
