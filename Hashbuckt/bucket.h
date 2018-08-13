#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

#define max_size 1000

typedef enum Stat
{
    Empty,
    Valid,
    Deleted,
}Stat;

typedef int KeyType;
typedef int HashType;
typedef int ValType;

typedef size_t (*HashFunc)(KeyType key);

//定义哈希链表中的元素
typedef struct HashElem
{
    KeyType key;
    ValType value;
    struct HashElem* next;
}HashElem;

//定义哈希表
typedef struct HashTable
{
    //如果hash桶中的链表不带头节点，就用HashElem*
    //如果hash桶中的链表带头节点，直接用HashElem
    HashElem* data[max_size]; //哈希表中的数组元素定义
    size_t size;   //哈希表中的元素个数
    HashFunc func;  //哈希函数
}HashTable;


//哈希表初始化    
void HashInit(HashTable* ht, HashFunc hash_func);
//哈希表销毁
void HashDestroyNode(HashElem* p);
//哈希表中插入元素
void HashInsert(HashTable*ht, KeyType key, ValType value);
//哈希表中查找元素
int HashFind(HashTable* ht, KeyType key, ValType* value);
//哈希表中删除元素
void HashRemove(HashTable*ht, KeyType key);

size_t hash_func(keyType key);















