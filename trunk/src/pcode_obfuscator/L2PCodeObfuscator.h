#ifndef L2PCODEOBFUSCATOR_H_
#define L2PCODEOBFUSCATOR_H_

#define L2_VERSION_T1   0
#define L2_VERSION_T15  1
#define L2_VERSION_T2   2
#define L2_VERSION_T22  3
#define L2_VERSION_T23  4

class L2PCodeObfuscator
{
public:
	L2PCodeObfuscator();
	virtual ~L2PCodeObfuscator();

public:
	void           setVersionMode( int new_version ) { m_version = new_version; }
	void           setVersionMode_T15() { setVersionMode( L2_VERSION_T15 ); }
	void           setVersionMode_T2()  { setVersionMode( L2_VERSION_T2  ); }
	void           setVersionMode_T22() { setVersionMode( L2_VERSION_T22 ); }
	
	void           clear();
	void           init_tables( unsigned int seed );
	int            isEnabled() const { return m_enabled; }

	int            decodeIDs( unsigned char *packet_data_raw );
	int            encodeIDs( unsigned char *packet_data_raw );

protected:
	void           pseudo_srand( unsigned int seed ) { m_seed = seed; }
	unsigned int   pseudo_rand();

protected:
	int            m_version;
	int            m_enabled;

	unsigned char *m_DecodeTable1;
	unsigned char *m_DecodeTable2;
	unsigned char *m_EncodeTable1;
	unsigned char *m_EncodeTable2;

	unsigned int   m_seed;
	unsigned int   m_s1; ///< size of 1-byte opcode obfuscator table
	unsigned int   m_s2; ///< size of 2-byte opcode obfuscator table
};

#endif /* L2PCODEOBFUSCATOR_H_ */
