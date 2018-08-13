#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#define max_size 1000
typedef int KeyType;
typedef int ValType;
typedef int DataType;
typedef int (*HashFunc)(KeyType key);

//枚举元素状态
typedef enum Stat
{
    Empty,
    Deleted,
    Valid,
}Stat;
//定义元素类型
typedef struct HashElem
{
    KeyType key;   //键值
    ValType value;  //值
    Stat stat;      //状态
}HashElem;

//定义哈希表类型
typedef struct HashTable
{
    HashElem data[max_size];   //容量
    size_t size;   //有效个数
    HashFunc func;  
}HashTable;


//初始化
void HashInit(HashTable*ht);
//销毁
void HashDestroy(HashTable*ht);
//插入
void HashInsert(HashTable*ht, KeyType key, ValType value);
//查找
int HashFind(HashTable*ht, KeyType key, ValType* value);
//删除
void HashRemove(HashTable*ht,KeyType key);











