#include<stdio.h>
#include<stddef.h>
#include<stdint.h>  //uint64_t


#define MAXSIZE 1000
typedef uint64_t BitMapType;
//定义位图结构体
typedef struct BitMap
{
    BitMapType *data;
    size_t capacity;
}BitMap;

//===========================
//初始化
//计算大小,申请空间,比特位置0
void BitMapInit(BitMap* bm,uint64_t capacity)
{
    if(bm==NULL)
    {
        return ;
    }
    bm->capacity=capacity;
    
    uint64_t size=bm->capacity/(sizeof(BitMapType)*8)+1;
    bm->data=(BitMapType*)malloc(size*sizeof(BitMapType));
    memset(bm->data,0,size*sizeof(BitMapType));
}
//=================================
//是否为1,
//计算下标，偏移量，

void GetOffset(uint64_t index, uint64_t* n, uint64_t* offset)
{
    *n=index/(sizeof(BitMapType)*8);
    *offset=index%(sizeof(BitMapType)*8);
}

int BitMapTest(BitMap* bm , uint64_t index)
{
    if(bm==NULL||index>bm->capacity)
    {
        return ;
    }
    uint64_t offset;
    uint64_t n;
    GetOffset(index, &n ,&offset);
    
    uint64_t ret=bm->data[n]&(0x1lu<<offset);
    if(ret==0)
    {
        return 0
    }
    else
    {
        return 1;
    }
}
//===========================
//某位置1
//计算下标，偏移量， 按位或
void BitMapSet1(BitMap* bm, uint64_t index )
{
    if(bm==NULL||index>bm->capacity)
    {
        return ;
    }
    
    uint64_t n;
    uint64_t offset;
    GetOffset(index, &n, &offset);
    bm->data[n]=bm->data[n]|(0x1lu<<offset);
    return ;
}
//==========================
//某位置0
//计算下标，偏移量，按位与
void BitMapSet1(BitMap* bm, uint64_t index )
{
    if(bm==NULL||index>=bm->capacity)
    {
        return ;
    }
    
    uint64_t n;
    uint64_t offset;
    GetOffset(index, &n, &offset);
    bm->data[n]=bm->data[n]& ~(0x1lu<<offset);
    return ;
}

//==========================
//全部置1
//计算大小，拷贝内容
void BitMapFull(BitMap* bm)
{
    if(bm==NULL)
    {
        return ;
    }
    uint64_t size=capacity/(sizeof(BitMapType)*8)+1;
    memset(bt->data,0xff,size*sizeof(BitMapTye));
    
}
//==============================
//全部置0

void BitMapFull(BitMap* bm)
{
    if(bm==NULL)
    {
        return ;
    }
    uint64_t size=capacity/(sizeof(BitMapType)*8)+1;
    memset(bt->data,0x00,size*sizeof(BitMapTye));
//===============================
///销毁
//释放空间，结构体清空
void BitMapDestroy(BitMap* bm)
{
    if(bm==NULL)
    {
        return ;
    }
    bm->capacity=0;
    free(bm->data);
}















