

#pragma once
#include<stdio.h>

//两个字符串哈希函数
#define HashFuncMaxSize 2 
//布隆过滤器中位图最大存储的比特位数量
#define BitMapCapacity 1024

typedef size_t(*HashFunc)(const char* );
//定义一个布隆过滤器
typedef struct BloomFilter
{
    BitMap bitmap;                      //布隆过滤器的位图
    HashFunc hash_func[HashFuncMaxSize];  //字符串哈希函数
}BloomFilter;

//初始化布隆过滤器
void BloomFilterInit(BloomFilter*bf);
//插入字符串
void BloomFilterInsert(BloomFilter*bf, const char* str);
//查找字符串
int BloomFilterIsExist(BloomFilter*bf, const char* str);
//销毁布隆过滤器
void BloomFilterDestroy(BloomFilter*bf);






