#pragma once
#include<stdio.h>
#include<stddef.h>
#include<stdint.h>  //uint64_t

#define MAXSIZE 1000

typedef  uint64_t BitMapType;

//位图以uint64_t为单位进行内存的申请
typedef struct BitMap
{
    uint64_t* data;
    size_t capacity; //位图中最大能表示的比特位个数
}BitMap;


//位图初始化
void BitMapInit(BitMap* bm, uint64_t capacity)
{
    if(bm==NULL)
    {   //非法输入
        return ;
    }
    bm->capacity=capacity;
    //如果位图最大表示100个数字，则需要2个64位的内存
    //如果位图最大表示200个数字，则需要4个64位的内存
    
    //malloc以字节为单位进行内存申请
    uint64_t size=bm->capacity/(sizeof(BitMapType)*8)+1;

    bm->data=(BitMapType*)malloc(size*sizeof(BitMapType));
    //初始化时将位图中的各个位均置为0，方便后续操作
    memset(bm->data,0,size*sizeof(BitMapType));
    return ;
}

//测试某一位是否为1
int BitMapTest(BitMap*bm, uint64_t index)
{
    if(bm==NULL||index>=bm->capacity)
    {
        //非法输入
        return 0;
    }
    uint64_t n;
    uint64_t offset;
    //获取index 所在的数组元素下标及偏移量
    GetOffset(index, &n ,&offset);

    //用1与之安位与，如果结果为0，则该位是0，否则是1
    //如果该位为1时，按位与的结果必定只有该位位1，其余位为0，所有对结果进行判断时
    //只能跟0进行比较，不能和1进行比较
    uint64_t ret=bm->data[n]&(0x1ul<<offset);
    if(ret==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

//将获取指定位所在的数组下标及其偏移量封装位函数
void GetOffset(uint64_t index, uint64_t* n, uint64_t* offset)
{
    //首先计算该位在那个数组元素中（数组元素64位为一个单元）
    //计算完之后的n表示，该位在下标位n的数组元素内（数组下标从0开始计数）
    *n =index/(sizeof(BitMapType)*8);

    //计算该位在 元素的哪个位上
    *offset= index % (sizeof(BitMapType)*8);
    return ;
}



//给某一位设置为1
void BitMapSet1(BitMap* bm, uint64_t index)
{
    if(bm==NULL||inddex >=bm->capacity)
    {
        //非法输入
        return ;
    }

    //计算该位所在的数组下标及其偏移量
    uint64_t n;
    uint64_t offset;
    GetOffset(index, &n ,&offset);
    
    //再将该位设置为1
    //但是要保证其他位不变，此时就要使其他位与0进行按位或
    //因此，该位要与1进行按位或，才能保证该位置位1，而其他位置也保持步变

    //按位操作后的结果不会改变原来的值，所以要对其进行赋值
    bm->data[n]=bm->data[n]|(0x1ul<<offset);
    return ;

}

//给某一位设置0

void BitMapSet0(BitMap* bm, uint64_t index)
{
    if(bm==NULL||index >=bm->capacity)
    {
        return ;
    }

    uint64_t n;
    uint64_t offset;
    GetOffset(index, &n, &offset);

    //根据数组元素下标和偏移量设置0
    //将该位设置为0时，保证其他位保持不变
    //所以其他位与1进行按位与（其他位可以与0进行按位或，
    //     但是index所在的位置要置为0，只能进行按位与运算）
    //~按位取反
    bm->data[n]=bm->data[n]& ~(0x1lu<<offset);
}

//将位图所以位都置为1
void BitMapFill(BitMap* bm)
{
    if(bm==NULL)
    {
        //非法输入
        return ;
    }
    //将位图所占的内存区域所有位置均置1
    //使用memset来进行置1，该函数是以字节为单位设置
    //所有要使一个字节的8个比特位均为1，则需要将一个字节置为0xff

    uint64_t size=bm->capacity/(sizeof(BitMapType)*8)+1;
    memset(bm->data,0xff,size*sizeof(BitMapType));
    return ;
}

//将位图所有位置都置为0
void BitMapClear(BitMap* bm)
{
    if(bm==NULL)
    {
        return ;
    }

    //将位图中的所有比特位置0
    //先计算位图共占了多少个64位的存储单元
    uint64_t size=bm->capacity/(sizeof(BitMapType)*8)+1;
    memset(bm->data,0x0,size*sizeof(BitMapType));
    return ;
}

//销毁位图
void BitMapDestroy(BitMap* bm)
{
    if(bm==NULL)
    {
        return ;
    }
    bm->capacity=0;
    free(bm->data);
    return ;
}



