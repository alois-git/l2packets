#ifndef H_L2_CHAT_MESSAGE_TYPES
#define H_L2_CHAT_MESSAGE_TYPES

class L2_CHAT_MESSAGE
{
public:
	static const unsigned int ALL = 0;
	static const unsigned int SHOUT = 1; //!
	static const unsigned int TELL = 2;
	static const unsigned int PARTY = 3; //#
	static const unsigned int CLAN = 4;  //@
	static const unsigned int GM = 5;
	static const unsigned int PETITION_PLAYER = 6; // used for petition
	static const unsigned int PETITION_GM = 7; //* used for petition
	static const unsigned int TRADE = 8; //+
	static const unsigned int ALLIANCE = 9; //$
	static const unsigned int ANNOUNCEMENT = 10;
	static const unsigned int PARTYROOM_ALL = 16; //(Red)
	static const unsigned int PARTYROOM_COMMANDER = 15; //(Yellow)
	static const unsigned int HERO_VOICE = 17;
	static const unsigned int L2_CHAT_MESSAGE_LAST = HERO_VOICE;
};

/*const char *L2_CHAT_NAMES = {
  "ALL  ",
  "SHOUT",
  "TELL ",
  "PARTY",
  "CLAN ",
  "GM   ",
  "PETITION_PLAYER",
  "PETITION_GM",
  "TRADE",
  "ALLIANCE",
  "ANNOUNCEMENT", //10
  "WILLCRASHCLIENT:)",
  "FAKEALL?",
  "FAKEALL?",
  "FAKEALL?",
  "PARTYROOM_ALL",
  "PARTYROOM_COMMANDER",
  "HERO_VOICE"
};*/


#endif
