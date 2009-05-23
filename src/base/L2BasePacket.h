#ifndef H_L2BASEPACKET
#define H_L2BASEPACKET

#include "ByteArray.h"

/** \class L2BasePacket
* Represents base class for all L2 packets. Provides way to create packets,
* write data to packets, read data from them.\n
* Internally uses ByteArray object to hold raw packet data bytes.
* Allows writing data/reading data from packet, using readXXXX or writeXXXX functions.\n
* \n
* In Lineage protocol, all packets start with 2 bytes, which hold all packet length (including these first 2 bytes). 
* These 2 bytes are never encrypted, so client application receives first 2 bytes,
* treates them as packet length and then reads the rest length-2 bytes.\n
* \n
* L2BasePacket internally uses ByteArray object to hold packet data. Initially created L2BasePacket object
* has preallocated space for 256 bytes in its internal storage (ByteArray::setSize(256)), so most write
* operations do not cause packet to grow. If 256 bytes is not enough, L2BasePacket automatically doubles
* size of its internal buffer, and so on.\n
* \n
* \n
*<pre>
*  Lineage II packet structure:\n
*        Size field               packet data
*  |----------------------|--------------------------|
*  | low byte | high byte | opcode | ... ... ... ... |
*  |----------------------|--------------------------|
*    0          1           2        3      ..........  << byte ordinal numbers
* </pre>
* \n
* Size field is 16-bit integer, defines size of ALL packet, including size field itself. So,
* maximum length of L2 packet is 65536 bytes (maximum data size is 65534).
*/

class L2BasePacket
{
public:
	/** Default constructor for empty packet. Preallocates buffer size for 256 bytes. */
	L2BasePacket();
	/** Copies length bytes to packet */
	L2BasePacket( const unsigned char *bytes, unsigned int length ); // does memcpy()
	/** Frees object memory */
	virtual ~L2BasePacket();

public:
	/** Reads byte at index from internal storage. Calls ByteArray::getByteAt()
	 \param index - byte index to read
	 \return byte value, or 0 if index is out of range.
	 */
	virtual unsigned char  getByteAt( unsigned int index );
	/** Sets byte at specified index to value. Does nothing if index out of bounds. Calls ByteArray::setByteAt()
	 * \param index byte index
	 * \param byte byte value to set
	 * \return previous byte value
	 */
	virtual unsigned char  setByteAt( unsigned int index, unsigned char byte );
	/** Copies bytes to internal storage buffer. Resizes internal buffer if needed. Calls ByteArray::setBytes()
	 * \param bytes pointer to source data buffer to copy from
	 * \param length source buffer size
	 * \return success state
	 */
	virtual bool           setBytes( const unsigned char *bytes, unsigned int length );
	/** Sets internal ByteArray's buffer pointer to [bytes], and length to [length]. Does no memcpy()\n
	 * Do not use this function!
	 * \param bytes pointer to new data buffer
	 * \param length source buffer size
	 * \return success state
	 * \see ByteArray::setBytesFromPtrNoMemcpy() */
	virtual bool           setBytesPtr( unsigned char *bytes, unsigned int length );
	/** Sets 3rd byte of packet (which holds packet opcode).
	 * Equivalent to call writeReset() and writeUChar(type).
	 * \param type new packet opcode. */
	virtual void           setPacketType( unsigned char type );
	/** Reads packet opcode. Calls readReset(); readUChar()
	 * \return read packet opcode. */
	virtual unsigned char  getPacketType() { readReset(); return readUChar(); }
	/** Gets packet length in bytes (not size of internal data buffer, which is larger)
	 * \return packet lentgh */
	virtual unsigned short getPacketSize() const { return (unsigned short)(this->real_size); }
	/** Gets number of data bytes in packet (excluding 1st 2 bytes, which hold all packet size).
	 * Equivalent to getPacketSize()-2.
	 * \return number of <b>data</b> bytes in buffer. */
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
public: // L2J aliases
	// writers
	virtual inline void writeC( char c )                 { writeChar( c ); }
	virtual inline void writeH( short h )                { writeShort( h ); }
	virtual inline void writeD( int d )                  { writeInt( d ); }
	virtual inline void writeQ( long long int Q )        { writeInt64( Q ); }
	virtual inline void writeF( double f )               { writeDouble( f ); }
	virtual inline void writeS( const wchar_t *string )  { writeUnicodeString( string ); }
	virtual inline void writeB( const ByteArray& bytes ) { writeBytes( bytes.getBytesPtr(), bytes.getSize() ); }
	// readers
	virtual inline char           readC() { return readChar(); }
	virtual inline short          readH() { return readShort(); }
	virtual inline int            readD() { return readInt(); }
	virtual inline double         readF() { return readDouble(); }
	virtual inline long long int  readQ() { return readInt64(); }
	virtual inline wchar_t       *readS() { return readUnicodeString(); }
	virtual        ByteArray     *readB( unsigned int count ); // not inline :)
public: // parsers
	virtual bool           parse();
	
	// DEBUG funcs
public:
	virtual void           dumpToFile( FILE *f );
	virtual void           saveToFileRaw( const char *filename );
	virtual void           displaySelfNice( FILE *f );
public: // typeconv
	//virtual operator const unsigned char *() const;
	virtual const unsigned char *getBytesPtr() const;
protected:
	virtual void _initNull();
	virtual bool _preAllocateBuffer();
	virtual bool _growBuffer();
	virtual void _freeSelf();
protected:
	unsigned int buffer_size; ///< current buffer size
	unsigned int real_size; ///< number of used bytes in buffer
	unsigned int write_ptr; ///< index of next byte that will be written to buffer
	unsigned int read_ptr;  ///< index of next byte that will be read from buffer
	unsigned int datasize;  ///< number of data bytes in packet (excluding first 2 bytes that hold packet size)
	ByteArray b; ///< internal buffer to hold raw packet data
};

#endif
