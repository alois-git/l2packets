#ifndef H_L2CHARACTER
#define H_L2CHARACTER
#include "L2Object.h"

/*

Every character is L2Object:
Every L2Object has its objectID and can also have its coordinates in L2World)

Additionally:
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
Every L2Character can be in combat
Every L2Character has its collision radius and height

*/

class L2Character : public L2Object
{
public:
	L2Character();
	virtual ~L2Character() { setUnused(); }
public:
	virtual  void setUnused();
public:
	virtual  bool parse_MoveToLocation( void *l2_game_packet );
	virtual  void processMoveTick();
	virtual  void startMoveTo( int mxd, int myd, int mzd, int mx, int my, int mz );
	virtual  void stopMove() { xDst = 0x7FFFFFFF; yDst = 0x7FFFFFFF; zDst = 0x7FFFFFFF; }
	virtual  int  isMoving() { return ((xDst != 0x7FFFFFFF) && (yDst != 0x7FFFFFFF) && (zDst!=0x7FFFFFFF)); }
public:
	virtual  void setName( const wchar_t *name );
	virtual  void setTitle( const wchar_t *title );
	virtual  const wchar_t *getName();
	virtual  const wchar_t *getTitle();
public:
	int level;
	wchar_t charName[128];
	wchar_t charTitle[128];
	int xDst;
	int yDst;
	int zDst;
	unsigned int heading;
	int runSpeed;
	int walkSpeed;
	int isRunning;
	int isSitting;
	int isAlikeDead;
	unsigned int lastMoveTickTime;
	int s_STR;
	int s_DEX;
	int s_CON;
	int s_INT;
	int s_WIT;
	int s_MEN;
	int pAtk;
	int pDef;
	int mAtk;
	int mDef;
	int pAtkSpd;
	int mAtkSpd;
	int accuracy;
	int evasion;
	int critical;
	double curHp;
	double maxHp;
	double curMp;
	double maxMp;
	double curCp;
	double maxCp;
	unsigned int abnormalEffect;
	unsigned int targetObjectID;
	int isInCombat;
	double collisionRadius;
	double collisionHeight;
};

#endif
