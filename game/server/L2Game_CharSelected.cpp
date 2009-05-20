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
