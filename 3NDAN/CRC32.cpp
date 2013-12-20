#include "CRC32.h"
unsigned int CRC32::mTable[0x100];
bool CRC32::mTableBuilt;
void CRC32::BuildTable()
{
    int i, j;
    for(i = 0; i < 0x100; ++i)
    {
        mTable[i] = Reflect(static_cast<unsigned int>(i),8) << 24;

        for(j = 0; j < 8; ++j)
            mTable[i] = (mTable[i] << 1) ^ ( (mTable[i] & (1<<31))  ? POLYNOMIAL : 0);

        mTable[i] = Reflect(mTable[i],32);
    }
    mTableBuilt = true;
}

unsigned int CRC32::Reflect(unsigned int v,int bits)
{
    unsigned int ret = 0;
    int i;

    --bits;
    for(i = 0; i <= bits; ++i)
    {
        if(v & (1<<i))
            ret |= 1 << (bits-i);
    }
    return ret;
}

void CRC32::Hash(const void* buf, int siz)
{
    const unsigned char* p = reinterpret_cast<const unsigned char*>(buf);
    if(!mTableBuilt)
        BuildTable();
    int i;
    for(i = 0; i < siz; ++i)
        mCrc = (mCrc >> 8) ^ mTable[ (mCrc & 0xFF) ^ p[i] ];
}