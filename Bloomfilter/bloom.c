

#include"bloom.h"
//==============================
//初始化
//布隆过滤器中的位图进行初始化
//初始化字符串哈希函数
void BloomFilterInit(BloomFilter*bf)
{
    BitMapInit(&bf->bitmap, BitMapCapacity);
    bf->hash_func[0]=HashFunc0;
    bf->hash_func[1]=HashFunc1;
}
//===============================
//插入字符串
//循环两个哈希函数计算出比特位下标
//将比特位对应下标插入到布隆过滤器的位图中
void BloomFilterInsert(BloomFilter*bf, const char* str)
{
    if(bf==NULL||str==NULL)
    {
        return ;
    }
    size_t i=0;
    for(;i<HashFuncMaxSize;i++)
    {
        size_t offset=bf->hash_func[i](str)%BitMapCapacity;
        BitMapSet1(&bf->bitmap,offset);
    }
    return ;
}

//===============================
//查找
//根据两个字符串哈希函数算出比特位下标
//如果两个比特位下标都为1近似认为字符串存在
int BloomFilterIsExist(BloomFilter*bf, const char* str)
{
    if(bf==NULL||str==NULL)
    {
        return 0;
    }
    size_t i=0;
    for(;i<HashFuncMaxSize;i++)
    {
        size_t offset=bf->hash_func[i](str)%BitMapCapacity;
        int ret=BitMapTest(&bf->bitmap,offset);
        if(ret==0)
        {
            return 0;
        }
    }
    return 1
}
//===============================
//销毁
//对布隆过滤器中的位图进行销毁，
//将字符串哈希函数指向空
void BloomFilterDestroy(BloomFilter*bf)
{
    if(bf==NULL)
    {
        return ;
    }
    BitMapDestroy(&bf->bitmap);
    bf->hash_func[0]=NULL;
    bf->hash_func[1]=NULL;
}








