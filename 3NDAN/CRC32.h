//IT NEED A FIX
//Slow, with errors etc..xd
class CRC32
{
public:
    inline CRC32() {
		Reset();
	}
    inline CRC32(const void* buf, int siz){
		Reset();
		Hash(buf,siz);
	}
    inline operator int () const {
		return Get();
	}
    inline unsigned int Get() const {
		return ~mCrc;
	}
    virtual void Reset() { 
		mCrc = ~0;                
	}
    virtual void Hash(const void* buf,int siz);
private:
    int mCrc;
    static bool mTableBuilt;
    static unsigned int  mTable[0x100];
    static const unsigned int POLYNOMIAL = 0x04C11DB7;
    static void BuildTable();
    static unsigned int  Reflect(unsigned int v,int bits);
};
static int CRC_32(void *ptr, int len) {
	CRC32 crc32;
	crc32.Hash(ptr, len);
	return crc32.Get();
}