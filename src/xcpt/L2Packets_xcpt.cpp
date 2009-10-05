#include "stdafx.h"
#include "L2Packets_xcpt.h"

L2P_Exception::~L2P_Exception()
{
	if( m_what )
	{
		free( m_what );
		m_what = NULL;
	}
}

const char *L2P_Exception::what() const { return m_what; }

const L2P_Exception& L2P_Exception::operator=( const L2P_Exception& other )
{
	if( this == &other ) return (*this);
	if( m_what ) free( m_what );
	m_what = NULL;
	if( other.m_what )
	{
		size_t ssize = strlen( other.m_what ) + 1;
		m_what = (char *)malloc( ssize );
		if( m_what ) strncpy( m_what, other.m_what, ssize-1 );
	}
	return (*this);
}

L2P_MemoryError::L2P_MemoryError( size_t bytes )
{
	m_what = (char *)malloc( 32 );
	if( m_what )
	{
		sprintf( m_what, "Tried to allocate: %u bytes", (unsigned int)bytes );
	}
}

L2P_ReadException::L2P_ReadException( int nBytesTriedToRead, int nPos, int nSize )
{
	m_what = (char *)malloc( 32 );
	if( m_what )
	{
		sprintf( m_what, "Tried to read: %d bytes; pos: %d/%d", nBytesTriedToRead, nPos, nSize );
	}
}

L2P_WriteException::L2P_WriteException( int nBytesTriedToWrite, int nPos, int nSize )
{
	m_what = (char *)malloc( 32 );
	if( m_what )
	{
		sprintf( m_what, "Tried to write: %d bytes; pos: %d/%d", nBytesTriedToWrite, nPos, nSize );
	}
}
