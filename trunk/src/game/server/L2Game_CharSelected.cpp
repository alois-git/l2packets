#include "stdafx.h"
#include "L2Game_CharSelected.h"

L2Game_CharSelected::L2Game_CharSelected()
{
	_initNull();
}

L2Game_CharSelected::L2Game_CharSelected( const unsigned char *bytes, unsigned int length )
{
	_initNull();
	setBytes( bytes, length );
}

bool L2Game_CharSelected::parse( L2_VERSION ver /*= L2_VERSION_T1*/ )
{
	UNREFERENCED_PARAMETER(ver);
	if( !this->canReadBytes( 200 ) ) return false; // must be at least 200 bytes

	readReset();
	readUChar(); // 0x0b CharSelected

	wcscpy( char_name, readUnicodeStringPtr() ); // char name
	charId    = readUInt();                      // char id (objectId)
	wcscpy( title, readUnicodeStringPtr() );     // title
	sessionId = readUInt();                      // sessionId
	clanId    = readUInt();                      // clanId
	readD();                                     // 0x00 (maybe allyId?)
	sex       = readD();
	race      = readD();
	classId   = readUInt();
	isActive  = readD();

	x         = readD();
	y         = readD();
	z         = readD();

	curHp     = readF();
	curMp     = readF();
	sp        = readUInt();
	exp       = readUInt64();
	level     = readD();
	karma     = readD();
	PK_kills  = readD();

	s_INT = readD();
	s_STR = readD();
	s_CON = readD();
	s_MEN = readD();
	s_DEX = readD();
	s_WIT = readD();

	readD(); // writeD( 0x0451 ); //?
	readD(); // writeD( 0x00 ); // some constants

	readD(); // writeD( classId ); // classId already read?

	//writeD(0x00); // 4 x 0x00
	//writeD(0x00);
	//writeD(0x00);
	//writeD(0x00); 
	readD(); readD(); readD(); readD();

	//writeB(new byte[64]); // some 64 bytes
	int i;
	for( i=0; i<16; i++ ) readD(); // read 4 x 16 = 64 bytes

	opcodeObfuscatorSeed = readUInt();
	return true;
}

bool L2Game_CharSelected::create( L2_VERSION ver /*= L2_VERSION_T1*/ )
{
	UNREFERENCED_PARAMETER(ver);
	writeReset();
	writeC(0x0b);

	writeS( char_name );
	writeD( charId );
	writeS( title );
	writeD( sessionId );
	writeD( clanId );
	writeD( 0x00 );  // maybe allyId?
	writeD( sex );
	writeD( race );
	writeD( classId );
	writeD( isActive ); // active ??

	writeD( x );
	writeD( y );
	writeD( z );

	writeF( curHp );
	writeF( curMp );
	writeD( sp );
	writeQ( exp );
	writeD( level );
	writeD( karma );
	writeD( PK_kills );
	writeD( s_INT );
	writeD( s_STR );
	writeD( s_CON );
	writeD( s_MEN );
	writeD( s_DEX );
	writeD( s_WIT );

	writeD( 0x0451 ); //?
	writeD( 0x00 ); // some constants

	writeD( classId );

	writeD(0x00); // 4 x 0x00
	writeD(0x00);
	writeD(0x00);
	writeD(0x00); 

	//writeB(new byte[64]); // some 64 bytes
	unsigned char *rndbuf = (unsigned char *)malloc( 64 );
	writeBytes( rndbuf, 64 );
	free( rndbuf );

	writeD( opcodeObfuscatorSeed ); // writeD(0x00);
	return true;
}
