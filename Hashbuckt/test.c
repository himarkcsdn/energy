#include"bucket.h"
#include<stdio.h>
#include<windows.h>


#define Test_Header printf("==============%s==========\n",__FUNCTION__)i




void TestInit()
{
    Test_Header;
    HashTable ht;
    HashInit(&ht,hash_func);
    printf("expect size is 0,actual size is %lu\n",ht.size);
    printf("expect func is %p,actual func is %p",hash_func,ht.hash_func);
}

int main()
{
    TestInit();
    return 0;
}













