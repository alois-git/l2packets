#include "stdafx.h"
#include "L2Game_CharSelectionInfo.h"

/** L2J
 * protected final void writeImpl()
    {
        writeC(0x09);
        int size = (_characterPackages.length);
        writeD(size);

        // Can prevent players from creating new characters (if 0);
        // (if 1, the client will ask if chars may be created (0x13) Response: (0x0D) )
        writeD(0x07);
        writeC(0x00);

        long lastAccess = 0L;

        // calculate last active char?
        if (_activeId == -1)
        {
            for (int i = 0; i < size; i++)
            {
                if (lastAccess < _characterPackages[i].getLastAccess())
                {
                    lastAccess = _characterPackages[i].getLastAccess();
                    _activeId = i;
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            CharSelectInfoPackage charInfoPackage = _characterPackages[i];

            writeS(charInfoPackage.getName());
            writeD(charInfoPackage.getCharId());
            writeS(_loginName);
            writeD(_sessionId);
            writeD(charInfoPackage.getClanId());
            writeD(0x00); // ??

            writeD(charInfoPackage.getSex());
            writeD(charInfoPackage.getRace());

            if (charInfoPackage.getClassId() == charInfoPackage.getBaseClassId())
                writeD(charInfoPackage.getClassId());
            else
                writeD(charInfoPackage.getBaseClassId());

            writeD(0x01); // active ??

            writeD(0x00); // x
            writeD(0x00); // y
            writeD(0x00); // z

            writeF(charInfoPackage.getCurrentHp()); // hp cur
            writeF(charInfoPackage.getCurrentMp()); // mp cur

            writeD(charInfoPackage.getSp());
            writeQ(charInfoPackage.getExp());
            writeD(charInfoPackage.getLevel());

            writeD(charInfoPackage.getKarma()); // karma
            writeD(charInfoPackage.getPkKills());

            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);

            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_HAIRALL));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_REAR));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_LEAR));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_NECK));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_RFINGER));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_LFINGER));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_HEAD));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_RHAND));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_LHAND));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_GLOVES));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_CHEST));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_LEGS));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_FEET));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_BACK));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_LRHAND));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_HAIR));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_HAIR2));

            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_RBRACELET));
            writeD(charInfoPackage.getPaperdollItemId(Inventory.PAPERDOLL_LBRACELET));
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(0x00);
            writeD(charInfoPackage.getHairStyle());
            writeD(charInfoPackage.getHairColor());
            writeD(charInfoPackage.getFace());

            writeF(charInfoPackage.getMaxHp()); // hp max
            writeF(charInfoPackage.getMaxMp()); // mp max

            long deleteTime = charInfoPackage.getDeleteTimer();
            int deletedays = 0;
            if (deleteTime > 0)
                deletedays = (int)((deleteTime-System.currentTimeMillis())/1000);
            writeD(deletedays); // days left before
            // delete .. if != 0
            // then char is inactive
            writeD(charInfoPackage.getClassId());
            if (i == _activeId)
                writeD(0x01);
            else
                writeD(0x00); //c3 auto-select char

            writeC(charInfoPackage.getEnchantEffect() > 127 ? 127 : charInfoPackage.getEnchantEffect());

            writeH(charInfoPackage.getAugmentationId());
            writeH(0x00); // this is for augmentation too

            //writeD(charInfoPackage.getTransformId()); // Used to display Transformations
            writeD(0x00); // Currently on retail when you are on character select you don't see your transformation.
        }
    }
*/

L2Game_CharSelectionInfo::L2Game_CharSelectionInfo()
{
	this->_initNull();
}

L2Game_CharSelectionInfo::L2Game_CharSelectionInfo( const unsigned char *bytes, unsigned int length )
{
	this->_initNull();
	this->setBytes( bytes, length );
}

bool L2Game_CharSelectionInfo::read_nChars( unsigned int *ret )
{
	if( !ret ) return false;
	this->readReset();
	if( !this->canReadBytes(10) ) return false;
	this->readUChar(); // pcode
	(*ret) = this->readUInt();
	return true;
}

// ret can be NULL
bool L2Game_CharSelectionInfo::read_server_maxChars( unsigned int *ret )
{
	if( !ret ) return false;
	this->readReset();
	if( !this->canReadBytes(10) ) return false;
	this->readUChar(); // pcode
	this->readUInt(); // nChars
	if( ret ) (*ret) = this->readUInt();
	this->readUChar(); // read 0x00
	return true;
}

bool L2Game_CharSelectionInfo::read_next_charSelectInfoBlock( L2_VERSION l2_version, struct CharSelectInfoBlock *c )
{
	if( !c ) return false;
	memset( c, 0, sizeof(CharSelectInfoBlock) );
	// TODO: how to detect that packet may be incorrect?
	// char info must be AT LEAST 280 bytes long (Hellbound)
	if( !this->canReadBytes(280) ) return false;
	const wchar_t *wstr = NULL;
	int i = 0;
	wstr = this->readUnicodeStringPtr();
	if( !wstr ) return false;
	wcsncpy( c->charName, wstr, 31 );
	c->charID = this->readUInt();
	wstr = this->readUnicodeStringPtr();
	if( !wstr ) return false;
	wcsncpy( c->accountName, wstr, 31 );
	c->sessionID = readUInt();
	c->clanID = readUInt();
	readUInt(); // 0x00
	c->sex = readUInt();
	c->race = readUInt();
	c->baseClassID = readUInt();
	c->isActive = readUInt();
	c->x = readUInt();
	c->y = readUInt();
	c->z = readUInt();
	c->HP_cur = readDouble();
	c->MP_cur = readDouble();
	c->SP = readUInt();
	c->Exp = readUInt64();
	c->level = readUInt();
	c->karma = readUInt();
	c->PK_kills = readUInt();
	c->PVP_kills = readUInt();
	for( i=0; i<7; i++ ) readUInt(); // 7 0x00
	c->iid_hair_all = readUInt();
	c->iid_R_ear = readUInt();
	c->iid_L_ear = readUInt();
	c->iid_neck = readUInt();
	c->iid_R_finger = readUInt();
	c->iid_L_finger = readUInt();
	c->iid_head = readUInt();
	c->iid_R_hand = readUInt();
	c->iid_L_hand = readUInt();
	c->iid_gloves = readUInt();
	c->iid_chest = readUInt();
	c->iid_legs = readUInt();
	c->iid_feet = readUInt();
	c->iid_back = readUInt();
	c->iid_LR_hand = readUInt();
	c->iid_hair = readUInt();
	c->iid_hair_2 = readUInt();
	c->iid_R_bracelet = readUInt();
	c->iid_L_bracelet = readUInt();
	for( i=0; i<6; i++ ) readUInt(); // DECO1 .. DECO6
	if( l2_version == L2_VERSION_T23 ) c->iid_belt = readUInt(); // Gracia Final T2.3
	c->hairStyle = readUInt();
	c->hairColor = readUInt();
	c->face = readUInt();
	c->HP_max = readDouble();
	c->MP_max = readDouble();
	c->deleteDays = readUInt();
	c->classID = readUInt();
	c->lastUsedChar = readUInt();
	c->enchantEffect = readUChar();
	c->augmentID = readUShort();
	c->augmentSmth = readUShort();
	c->transformID = readUInt();
	return true;
}
