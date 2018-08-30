#pragma once

#include<stdio.h>
#include<stddef.h>


typedef  (char*)BloomFilter()
//两个哈希函数
#define HASHMAXSIZE 2
#define Capcity 1000;
//定义布隆过滤器
typedef struct BloomFilter
{
    BitMap bitmap;
    HashFunc hash_func[HASHMAXSIZE];
}

//=============================
//初始化
//对位图进行初始化，对函数进行初始化
void BloomFilterInit(BloomFilter* bf)
{
    if(bf==NULL)
    {
        return ;
    }
    BitMapInit(&bf->bitmap, Capacity);
    bf->hash_func[0]=Hash_Func0;
    bf->hash_func[1]=Hash_Func1;
}
//==============================
//插入
//找出比特位下标，插入位图
void BloomFilterInsert(BloomFilter* bf, const char* str )
{
    if(bf==NULL||str==NULL)
    {
        return ;
    }
    
    size_t i=0;
    for(i=0;i<HASHMAXSIZE;i++)
    {
        size_t offset=bf->hash_func[i](str)%Capacity;
        BitMapSet1(&bf->bitmap, offset);
    }
    return ;
}
//================================
//查找
//根据字符串哈希函数找出比特位下标，测试对应位置是否为1
int BloomFilterFind(BloomFilter*bf, const char* str)
{
    if(bf==NULL||str==NULL)
    {
        return 0;
    }
    size_t i=0;
    for(;i<HASHMAXSIZE;i++)
    {
        size_t offset=bf->hash_func[i](str)%Capcity;
        int ret=BitMapTest(&bf->bitmap,offset);
        if(ret==0)
        {
            return 0;
        }
    }
    return 1
}
//==============================
//销毁
//位图清空，函数置空
void BloomFilterClear(BloomFilter*bf)
{
    if(bf==NULL)
    {
        return ;
    }
    BitMapDestroy(&bf->bitmap);
    bf->hash_func[0]=NULL;
    bf->hash_func[1]=NULL;
}











