#ifndef H_L2OBJECT
#define H_L2OBJECT

/*

Every object has its objectID and can also have its coordinates in L2World

*/

class L2Object
{
public:
	L2Object(): x(0), y(0), z(0), objectID(0) {}
	virtual ~L2Object() { setUnused(); }
public:
	virtual void setXYZ( int sx, int sy, int sz ) { x = sx; y = sy; z = sz; }
public:
	virtual int  isUnused() const { return (objectID == 0); }
	virtual void setUnused() { objectID = 0; x = 0; y = 0; z = 0; }
public:
	int x;
	int y;
	int z;
	unsigned int objectID;
};

#endif
