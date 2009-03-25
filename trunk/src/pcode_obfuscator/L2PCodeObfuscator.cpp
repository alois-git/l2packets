#include "stdafx.h"
#include "L2PCodeObfuscator.h"

L2PCodeObfuscator::L2PCodeObfuscator()
{
	m_version = 0;
	m_DecodeTable1 = m_DecodeTable2 = m_EncodeTable1 = m_EncodeTable2 = NULL;
	m_seed = 0;
	m_enabled = 0;
}

L2PCodeObfuscator::~L2PCodeObfuscator()
{
	clear();
}

void L2PCodeObfuscator::clear()
{
	if( m_DecodeTable1 ) free( m_DecodeTable1 );
	if( m_DecodeTable2 ) free( m_DecodeTable2 );
	if( m_EncodeTable1 ) free( m_EncodeTable1 );
	if( m_EncodeTable2 ) free( m_EncodeTable2 );
	m_version = 0;
	m_DecodeTable1 = m_DecodeTable2 = m_EncodeTable1 = m_EncodeTable2 = NULL;
	m_seed = 0;
	m_enabled = 0;
}

unsigned int L2PCodeObfuscator::pseudo_rand()
{
	unsigned int a;
	a = ( m_seed * 0x343fd + 0x269EC3 ) & 0xFFFFFFFF;
	m_seed = a;
	unsigned int result = ( m_seed >> 0x10 ) & 0x7FFF;
//	writelogln( format( 'rand = %x; seed = %x', [result, _seed] ) );
	return result;
}

void L2PCodeObfuscator::init_tables( unsigned int seed )
{
	unsigned int i = 0;
	unsigned char tmp = 0;
	unsigned int pos;
	unsigned int cpos;

	m_s1 = 0xD0;
	m_s2 = 0x4E; // T1.5 Hellbound

/*	if gSys.Protocol = 871 then _init_tables(GInt(_dBuff, $16, 4), $58); // CT2.2
	if gSys.Protocol = 851 then _init_tables(GInt(_dBuff, $16, 4), $55); // CT2
	if gSys.Protocol = 831 then _init_tables(GInt(_dBuff, $16, 4), $4E); // CT1.5+ */
	if( m_version == L2_VERSION_T2  ) m_s2 = 0x55; // T2   Gracia Part 1
	if( m_version == L2_VERSION_T22 ) m_s2 = 0x58; // T2.2 Gracia Part 2

	if( m_DecodeTable1 ) free( m_DecodeTable1 );
	if( m_DecodeTable2 ) free( m_DecodeTable2 );
	m_DecodeTable1 = NULL;
	m_DecodeTable2 = NULL;
	m_DecodeTable1 = (unsigned char *)malloc( sizeof(unsigned char) * (m_s1 + 1) );
	m_DecodeTable2 = (unsigned char *)malloc( sizeof(unsigned char) * (m_s2 + 1) );

	for( i = 0; i <= m_s1; i++ ) m_DecodeTable1[i] = (unsigned char)i;
	for( i = 0; i <= m_s2; i++ ) m_DecodeTable2[i] = (unsigned char)i;

	this->pseudo_srand( seed );

	for( i = 1; i <= m_s1; i++ )
	{
		pos = this->pseudo_rand() % (i + 1);
		// swap bytes [pos] and [i] in DecodeTable1
		tmp = m_DecodeTable1[pos];
		m_DecodeTable1[pos] = m_DecodeTable1[i];
		m_DecodeTable1[i] = tmp;
	}

	for( i = 1; i <= m_s2; i++ )
	{
		pos = this->pseudo_rand() % (i + 1);
		// swap bytes [pos] and [i] in DecodeTable2
		tmp = m_DecodeTable2[pos];
		m_DecodeTable2[pos] = m_DecodeTable2[i];
		m_DecodeTable2[i] = tmp;
	}

	cpos = 0;
	while( m_DecodeTable1[cpos] != 0x12 ) cpos++;
	tmp = m_DecodeTable1[0x12];
	m_DecodeTable1[0x12] = 0x12;
	m_DecodeTable1[cpos] = tmp;

	cpos = 0;
	while( m_DecodeTable1[cpos] != 0xB1 ) cpos++;
	tmp = m_DecodeTable1[0xB1];
	m_DecodeTable1[0xB1] = 0xB1;
	m_DecodeTable1[cpos] = tmp;

	m_EncodeTable1 = (unsigned char *)malloc( sizeof(unsigned char) * (m_s1 + 1) );
	m_EncodeTable2 = (unsigned char *)malloc( sizeof(unsigned char) * (m_s2 + 1) );
	for( i = 0; i <= m_s1; i++ ) m_EncodeTable1[ m_DecodeTable1[i] ] = (unsigned char)i;
	for( i = 0; i <= m_s2; i++ ) m_EncodeTable2[ m_DecodeTable2[i] ] = (unsigned char)i;

	m_enabled = 1;
}

int L2PCodeObfuscator::decodeIDs( unsigned char *packet_data_raw )
{
	if( !packet_data_raw ) return 0;
	unsigned char *data = packet_data_raw;
	int ofs = 2; // offset of packet ID in raw data
	int ret_val = 0;
	if( m_DecodeTable1 )
	{
		if( data[ofs] >= m_s1 ) return -1;
		else data[ofs] = m_DecodeTable1[ data[ofs] ];
		ret_val = 1;
		if( data[ofs] == 0xD0 ) // double-byte packet
		{
			ret_val = 2;
			if( data[ofs + 1] >= m_s2 ) return -2;
			else data[ofs + 1] = m_DecodeTable2[ data[ofs + 1] ];
		}
	}
	return ret_val;
}

int L2PCodeObfuscator::encodeIDs( unsigned char *packet_data_raw )
{
	if( !packet_data_raw ) return 0;
	unsigned char *data = packet_data_raw;
	int ofs = 2; // offset of packet ID in raw data
	int ret_val = 0;
	if( m_EncodeTable1 )
	{
		if( data[ofs] >= m_s1 ) return -1;
		else data[ofs] = m_EncodeTable1[ data[ofs] ];
		ret_val = 1;
		if( data[ofs] == 0xD0 ) // double-byte packet
		{
			ret_val = 2;
			if( data[ofs + 1] >= m_s2 ) return -2;
			else data[ofs + 1] = m_EncodeTable2[ data[ofs + 1] ];
		}
	}
	return ret_val;
}
