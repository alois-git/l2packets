#ifndef H_BYTEARRAY
#define H_BYTEARRAY

class ByteArray
{
public: // constructors/destructors
	ByteArray();
	ByteArray( unsigned int length );
	ByteArray( const char *string );
	ByteArray( const ByteArray& ba );
	ByteArray( const unsigned char *newBytes, unsigned int length );
	~ByteArray();

public:	// size funcs
	inline unsigned int   getSize() const { return this->byteCount; }
	bool                  setSize( unsigned int newSize );

public: // data functions
	inline unsigned char *getBytesPtr() const { return this->bytes; }
	
	unsigned char         getByteAt( unsigned int index ) const;
	unsigned char         setByteAt( unsigned int index, unsigned char byteSet );
	
	void                  memset( unsigned char c );
	bool                  setBytes( const unsigned char *newBytes, unsigned int length );
	bool                  setBytesFromString( const char *string );
	bool                  setBytesFromPtrNoMemcpy( unsigned char *bytes, unsigned int length );

public: // operators
	unsigned char operator[]( int index ) const;

protected: // internal functions
	void                  _initNull();
	void                  _freeSelf();

	// debug functions
#ifdef _DEBUG
public:
	void                   setDebugMode( bool bDebug, FILE *flog );
	int                    _debugPrintf( const char *_Format, ... );
	void                   dumpArrayInfo( FILE * fOut );
#endif
	
protected:
	// data
	unsigned int   byteCount;
	unsigned char *bytes;
	// debug mode vars
#ifdef _DEBUG
	bool           bDebugMode;
	FILE          *fLogFile;
#endif
};

#endif
