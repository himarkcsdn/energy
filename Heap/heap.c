#include<stdio.h>

#define MAXSIZE 100;
typedef int (*Compare)(HeapType a, HeapType b);

//定义堆
typedef struct Heap 
{
    HeapType data[MAXSIZE];
    size_t size;   //堆中元素的大小
    Compare cmp;   //根据传入的参数选择大堆或者小堆
}Heap;

//大堆
void Greater(HeapType a, HeapType b)
{
    return a>b ? 1:0;
}
//小堆
void Less(HeapType a, HeapType b)
{
    return a<b ? 1:0;
}

//交换函数
void swap(HeapType* a, HeapType *b)
{
    HeapType tmp
    tmp=*a;
    *a=*b;
    *b=tmp;
}

//==================================
//在堆中插入一个元素   假设是小堆

//将元素尾插到堆中
//队尾元素的根节点为，根，孩子节点中的最小值，如果不满足交换节点。更新位置下标继续上浮
//如果根节点为最小值，则满足条件直接返回。

void AdjustUp(Heap* heap, size_t start)
{
    //上浮函数
    if(heap==NULL)
    {
        //非法
        return ;
    }
    //从孩子节点开始
    size_t child=start;
    size_t parent=(child-1)/2;
    while(1)
    {
        if(child==0)
        {
            break;
        }
        //如果父节点小于孩子节点，则交换父子节点
        if(heap->cmp(heap->data[parent],heap->data[child])==0)
        {
            swap(&heap->data[parent],&heap->data[child]);
            child=parent;
            parent=(child-1)/2;
        }
        else
        {
            //满足条件
            break;
        }
    }
    return ;
}

void HeapInsert(Heap* heap, HeapType value)
{
    if(heap==NULL)
    {
        //非法
        return ;
    }
    if(heap->size>=MAXSIZE)
    {
        //堆中元素已经满了
        return ;
    }

    //插入元素
    heap->data[heap->size++]=vlaue;
    //上浮函数，使其满足小堆的条件
    AdjustUp(heap,heap->size-1);
    return ;
}

//======================================
//删除堆顶元素        假设大堆


//交换堆首与堆尾元素，删掉堆尾元素
//如果是大堆则堆顶元素是根，左，右节点中最大值
//先比较左右孩子找到最大值
//再将根节点和左右孩子最大值比较，如果根节点比最大值小就交换这两个节点
//如果根节点比较大，直接返回即可
//循环2-5

void AdjustDown(Heap* heap, size_t start_log)
{
    if(heap==NULL)
    {
        return ;
    }
    size_t child=(parent+1)*2;
    //从父节点开始
    size_t parent=star_log;

    while(1)
    {
        //原来的跟节点已经调整到元素末尾则完成
        if(child==size)
        {
            break;
        }
        //如果右孩子存在，在大堆中找左右孩子节点的最大值
        if(child+1<size&&heap->cmp(heap->data[child],heap->data[child+1])==0)
        {
            child=child+1;
        }
        //大堆中，如果孩子节点中的较大值比根节点值大，就进行交换
        if(heap->cmp(heap->data[child],heap->data[parent])==0)
        {
            swp(&heap->data[parent],&heap->data[child]);
            parent=child;
            child=(parent+1)*2
        }
        else
        {
            //此时满足了比较条件，直接返回。
            break;
        }
    }
    return ;
}

void HeapErase(Heap* heap)
{
    if(heap==NULL)
    {
        return ;
    }
    if(heap->size==0)
    {
        //堆删除完成
        return ;
    }

    //交换堆顶元素与数组结尾元素
    swap(&heap->data[0],&heap->data[size-1]);
    //删除数组结尾元素
    --heap->size;
    //进行下浮调整使其满足堆条件
    AdjustDown(heap,0);
    return ;
}

//======================================
//根据一个堆对数组进行排序   升序（大堆）
void HeapSort(HeapType arr[],size_t size,)
{
    if(heap==NULL)
    {
        return ;
    }
    if(arr==NULL||size==0)
    {
        return ;
    }

    //定义一个堆，对其初始化
    Heap heap;
    HeapInit(&heap,Greater);

    //根据数组中的元素创建堆
    size_t cur=0;
    for(;cur<size;cur++)
    {
        HeapInsert(&heap,arr[cur]);
    }
    //将堆顶元素进行删除
    for(cur=0;cur<size;++cur)
    {
        HeapErase(&heap);
    }

    memcpy(arr,heap.data,size*sizeof(Typedef));

}

//==================================
//清理堆
void HeapClear(Heap* heap)
{
    if(heap==NULL)
    {
        return ;
    }
    heap->size=0;
    return ;
}

//销毁堆
int HeapDestroy(Heap* heap)
{
    if(heap==NULL)
    {
        return 0 ;
    }
    heap->size=0;
    heap->cmp=NULL;
    return 1;
}
//统计堆中节点个数
size_t HeapSize(Heap* heap)
{
    if(heap==NULL)
    {
        return (size_t)-1 ;   
    }
    return heap->size;
}

//根据一个堆对数组进行排序
//
//首先根据数组元素创建一个堆，如果升序创建大堆
//大堆创建完成后，堆满足根节点比左右孩子节点值大
//根据删除函数对堆顶元素进行删除，依次删除（对堆顶进行删除
//     是将堆顶元素与堆尾元素进行交换，然后size--，虽然说是删除
//     其实是将该内存中的元素视为无效元素，但原堆顶元素依然存在，所以依然可以使用）
//     将排好序的元素赋值给数组元素
