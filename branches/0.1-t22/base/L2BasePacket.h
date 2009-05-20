#ifndef H_L2BASEPACKET
#define H_L2BASEPACKET

#include "ByteArray.h"
//#include "../pcode_obfuscator/L2PCodeObfuscator.h"

class L2BasePacket
{
public:
	L2BasePacket();
	L2BasePacket( const unsigned char *bytes, unsigned int length ); // does memcpy()
	virtual ~L2BasePacket();
public:
	virtual unsigned char  getByteAt( unsigned int index );
	virtual unsigned char  setByteAt( unsigned int index, unsigned char byte );
	virtual bool           setBytes( const unsigned char *bytes, unsigned int length ); // does memcpy()
	virtual bool           setBytesPtr( unsigned char *bytes, unsigned int length ); // does not do memcpy
	virtual void           setPacketType( unsigned char type );
	virtual unsigned char  getPacketType() { readReset(); return readUChar(); }
	virtual unsigned short getPacketSize() const { return (unsigned short)(this->real_size); }
	// number of DATA bytes in packet
	virtual unsigned short getDataSize() const { return (unsigned short)(this->datasize); }
public: // write funcs
	virtual bool           ensureCanWriteBytes( unsigned int nBytes );
	virtual void           writeReset();
	virtual void           writeChar( char c );
	virtual void           writeUChar( unsigned char c );
	virtual void           writeShort( short int s );
	virtual void           writeUShort( unsigned short int s );
	virtual void           writeInt( int i );
	virtual void           writeUInt( unsigned int i );
	virtual void           writeInt64( long long int i64 );
	virtual void           writeUInt64( unsigned long long int i64 );
	virtual void           writeDouble( double d );
	virtual void           writeString( const char *str );
	virtual void           writeUnicodeString( const wchar_t *ustr );
	virtual void           writeBytes( const unsigned char *bytes, unsigned int len );
public: // read funcs
	virtual bool           canReadBytes( unsigned int nBytes );
	virtual void           readReset();
	virtual char           readChar();
	virtual unsigned char  readUChar();
	virtual short int      readShort();
	virtual unsigned short int readUShort();
	virtual int            readInt();
	virtual unsigned int   readUInt();
	virtual long long int  readInt64();
	virtual unsigned long long int readUInt64();
	virtual double         readDouble();
	virtual char          *readString();
	virtual wchar_t       *readUnicodeString(); // allocates buffer, reads string, and returns buffer
	virtual const wchar_t *readUnicodeStringPtr(); // returns read-only pointer to wchar_t into internal buffer
	virtual bool           readBytes( unsigned char *bytes, unsigned int num );
//public:
//	virtual bool           opcodeObfuscate( L2PCodeObfuscator *obfuscator );
//	virtual bool           opcodeDeObfuscate( L2PCodeObfuscator *obfuscator );
public:
	virtual void           dumpToFile( FILE *f );
	virtual void           saveToFileRaw( const char *filename );
	virtual void           displaySelfNice( FILE *f );
public: // typeconv
	virtual operator const unsigned char *() const;
	virtual const unsigned char *getBytesPtr() const;
protected:
	virtual void _initNull();
	virtual bool _preAllocateBuffer();
	virtual bool _growBuffer();
	virtual void _freeSelf();
protected:
	unsigned int buffer_size;
	unsigned int real_size; // number of used bytes in buffer
	unsigned int write_ptr; // index of next byte that will bw written (in buffer)
	unsigned int read_ptr;  // index of next byte that will be read from buffer
	unsigned int datasize;  // number of data bytes in packet (excluding 1st 2)
	ByteArray b;
};

#endif
