#include "stdafx.h"
#include "L2Login_Init.h"

L2Login_Init::L2Login_Init()
{
	_initNull();
}

L2Login_Init::L2Login_Init( const unsigned char *bytes, unsigned int length )
{
	_initNull();
	this->setBytes( bytes, length );
}

bool L2Login_Init::read_SessionID( unsigned char *sidBytes )
{
	if( !sidBytes ) return false;
	this->readReset();
	//this->readShort(); // pass packet len // already done by readReset()
	this->readChar();  // pass packet type
	sidBytes[0] = this->readUChar();
	sidBytes[1] = this->readUChar();
	sidBytes[2] = this->readUChar();
	sidBytes[3] = this->readUChar();
	return true;
}

unsigned int L2Login_Init::read_ProtoVer()
{
	unsigned int ret = 0;
	ret = this->readUInt();
	return ret;
}

// RSApublicKeyMod must point to buffer 128 bytes len
bool L2Login_Init::read_RSA_pubKeyMod( unsigned char *RSApublicKeyMod )
{
	if( !RSApublicKeyMod ) return false;
	int i = 0;
	while( i < 128 )
		RSApublicKeyMod[i++] = this->readUChar();
	return true;
}

// ggShit - 16 bytes buffer; can be NULL
bool L2Login_Init::read_GGShit( unsigned char *ggShit )
{
	int i = 0;
	char c = 0;
	while( i < 16 )
	{
		c = this->readUChar();
		if( ggShit ) ggShit[i] = c;
		i++;
	}
	return true;
}

// newBFKey - 16 bytes buffer; can NOT be NULL
bool L2Login_Init::read_DynamicBFKey( unsigned char *newBFKey )
{
	if( !newBFKey ) return false;
	int i = 0;
	while( i < 16 ) newBFKey[i++] = this->readUChar();
	return true;
}

void L2Login_Init::displaySelfNice( FILE *f )
{
	fprintf( f, "L2Login_Init: displaying self\n" );
	if( this->getPacketSize() != 186 )
	{
		fprintf( f, "L2Login_Init: this is not standard Interlude Init packet! (wrong size)\n" );
		this->dumpToFile( stdout );
		return;
	}
	char ptype = this->getPacketType();
	if( ptype != 0 )
	{
		fprintf( f, "L2Login_Init: this is not standard Interlude Init packet! (wrong packet type)\n" );
		this->dumpToFile( stdout );
	}
	
	// vars
	unsigned char sidBytes[4]    = {0,0,0,0};
	unsigned int  protoRev       = 0;
	unsigned char RSA_pubKeyMod[128];
	unsigned char GG_Shit[16]    = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
	unsigned char dyn_BF_key[16] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
	unsigned char nullTerm       = 0;
	
	// memsets
	memset( RSA_pubKeyMod, 0, sizeof(RSA_pubKeyMod) );
	
	// read ...
	this->read_SessionID( sidBytes );
	protoRev = this->read_ProtoVer();
	this->read_RSA_pubKeyMod( RSA_pubKeyMod );
	this->read_GGShit( GG_Shit );
	this->read_DynamicBFKey( dyn_BF_key );
	nullTerm = this->readUChar();
	
	// print
	int i = 0;
	fprintf( f, "Packet type     : Init (0)\n" );
	fprintf( f, "Session ID      : %02X %02X %02X %02X\n",
		sidBytes[0], sidBytes[1], sidBytes[2], sidBytes[3] );
	fprintf( f, "Protocol Rev    : %04X\n", protoRev );
	fprintf( f, "RSA pub key mod :\n" );
	for( i=0; i<128; i++ ) fprintf( f, "%02X ", (unsigned int)RSA_pubKeyMod[i] );
	fprintf( f, "\n" );
	fprintf( f, "GG Shit         : " );
	for( i=0; i<16; i++ ) fprintf( f, "%02X ", (unsigned int)GG_Shit[i] );
	fprintf( f, "\n" );
	fprintf( f, "Dynamic BF Key  : " );
	for( i=0; i<16; i++ ) fprintf( f, "%02X ", (unsigned int)dyn_BF_key[i] );
	fprintf( f, "\n" );
	fprintf( f, "NULL terminator : %u (0x%02X)\n",
		(unsigned int)nullTerm, (unsigned int)nullTerm );
	fprintf( f, "Init packet dump end ;)\n\n" );
}
