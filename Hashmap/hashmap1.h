#pragma once
#include<stddef.h>
#include<stdint.h>

//位图以uint64_t 为单位申请内存
typedef uint64_t BitMapType;


//定义结构体
typedef struct BitMap
{
    BitMapType* data;   
    size_t capacity;    //位图中最大嫩表示的容量
}

//初始化
void BitMapInit(BitMap*bm, size_t index)
{
    if(bm==NULL)
    {
        return ;
    }
    //如果位图最大表示100个数字，则需2个64位的内存
    //malloc以字节为单位申请空间
    //初始化位图时将各个比特位置0方便以后的操作
    bm->capacity=index;
    uint64_t size=index/(sizeof(BitMapType)*8)+1;
    bm->data=(BitMapType*)malloc(size*sizeof(BitMapType));
    memset(bm->data,0,size*sizeof(BitMapType));
}


//测试某个位置上是否为1
void GetOffset(uint64_t index, size_t* n, size_t* offset)
{
    //计算下标，计算偏移量
    *n=index/(sizeof(BitMapType)*8)+1;
    *offset=index% (size*sizeof(BitMapType))+1;
}


int BitMapIs(BitMap* bm, size_t index)
{
    if(bm==NULL||index>= bm->capacity)
    {   //非法输入
        return ;
    }
    uint64_t n;//数组元素下标
    uint64_t offset;  //元素比特位的偏移量

    //获取index所在数组的下标，及其比特位的偏移量
    GetOffset(index, &n, &offset);
    //用1与该位与 如果该位为0则结果0，该位为1结果1
    //其他位与1 不会影响原来位的结果
    uint64_t ret=bm->data[n]&(0x1ul<<offset);
    if(ret==0)
    {
        return 0;
    }
    else
    {
        //该位是1
        return 1;
    }
}
//设置某个位置为1
void BitMapSet1(BitMap*bm , size_t index)
{
    if(bm==NULL||index>=bm->capacity)
    {
        //非法输入
        return ;
    }
    uint64_t n;  //下标
    uint64_t offset;  //偏移量
    //根据Index获取下标，及其偏移量
    GetOffset(index, &n, &offset);
    //按位操作不会改变结果，即赋值给原来的元素
    //按位或1不会影响其他位置的值
    bm->data[n]=bm->data[n]| (0x1ul<<offset);
    return ;
}

//设置某个位置0
void BitMapSet0(BitMap* bm, size_t index)
{
    if(bm==NULL||index>= bm->capacity)
    {
        //非法输入
        return ;
    }
    uint64_t n;  //下标
    uint64_t offset; //偏移量
    //获取下标，及其偏移量
    GetOffset(index, &n, &offset);
    //将偏移后结果按位取反，该位与0进行按位与操作，不会影响其他位置
    bm->data[n]=bm->data[n] & ~(0x1<<offset);
    return ;
}

//全部设置1
void BitMapFull(BitMap*bm)
{
    if(bm==NULL)
    {
        return ;
    }
    //
    uint64_t size=bm->capacity/(sizeof(BitMapType)*8)+1;
    //拷贝为0xff：即全满。
    memset(bm->data,0xff,size*sizeof(BitMapType));
    return ;
}

//全部设置0
void BitMapclear(BitMap*bm)
{
    if(bm==NULL)
    {
        return ;
    }
    uint64_t size=bm->capacity/(sizeof(BitMapType)*8)+1;
    //拷贝0X0：即全空
    memset(bm->data,0x00,(size*sizeof(BitMapType)));
    return ;
}
//销毁
void BitMapDestroy(BitMap* bm)
{
    if(bm==NULL)
    {
        return ;
    }
    bm->capacity=0;
    //释放内存
    free(bm->data);
    return ;
}












