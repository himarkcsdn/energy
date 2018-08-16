//顺式队列
#include<stdio.h>
typedef char SeqQueueType;

//定义顺序队列结构
typedef struct SeqQueue
{
    SeqQueueType* date; //指向队列的指针
    int size;         //实际长度
    int capacity;        //容量
    int head;             //头节点所在下标
    int tail;           //队尾节点下个元素所在下标[head,tail）
}SeqQueue;

//初始化
void SeqQueueInit(SeqQueue* queue)
{
    if(queue==NULL)
    {
        return ;
    }
    queue->size=0;  //初始队列为空
    queue->capacity=1000;   //设置有效长度1000
    //动态申请内存，由data指向
    queue->data=(SeqQueueType*)malloc(queue->capacity*sizeof(SeqQueueType));
    queue->head=0;  //初始队列为空
    queue->tail=0;
}



//===============================
//入队列


void Expanding(SeqQueue* queue)
{
    if(queue==NULL)
    {
        return ;
    }
    //重新设置内存的有效长度
    queue->capacity=(queue->capacity)*2+1;
    //重新申请新 的内存
    SeqQueueType* new_data=(SeqQueueType*)malloc(queue->capacity*sizeof(SeqQueueType));

    //将原来内存中的数据复制到新内存中
    //如果尾节点在头节点之后
    int i;
    if(queue->head<queue->tail)
    {
        i=queue->head;
        for(;i<queue->tail;++i)
        {
            new_data[i]=queue->data[i];
        }
    }
    else  //如果尾节点在头节点之前
    {
        i=queue->head;
        //先拷贝队首到原capacity的数据
        for(;i<queue->size;++i)
        {
            new_data[i]=queue->data[i];
        }

        //再拷贝0到队尾的数据
        i=0;
        for(;i<queue->tail;++i)
        {
            new_data[queue->size+i]=queue->data[i];
        }
        //修改扩容后的tail值
        queue->tail=queue->head+queue->size;
    }
    //释放原内存
    free(queue->data);
    queue->data=new_data;
    return ;
}

void SeqQueuePush(SeqQueue* queue, SeqQueueType value)
{
    if(queue==NULL)
    {
        return ;
    }
    
    if(queue->size>=queue->capacity)
    {
        Expanding(queue);
    }
    //如果尾节点为数组最后一个元素，但是数组前面还有空余的地方
    if(queue->tail==queue->capacity)
    {
        queue->tail=0;
        queue->data[queue->tail++]=value;
        queue->size++;
        return ;
    }
    //尾节点不为数组最后一个节点
    queeu->data[queue->tail++]=value;
    queue->size++;
    return ;
}

//==============================================
//出队列
void SeqQueuePop(SeqQueue* queue)
{
    if(queue==NULL)
    {
        return ;
    }
    if(queue->size==0)
    {
        //空队列
        return ;
    }
    //如果出队元素为最大数组下标出的元素
    if(queue->head==queue->capacity)
    {
        queue->head=0;
        queue->size--;
    }
    else //如果不是最大数组下标处的元素
    {
        queue->head++;
        queue->size--;
    }
    return ;

}


//==================================
//取队首元素

int SeqQueueTop(SeqQueue* queue, SeqQueueType* value)
{
    if(queue==NULL||value==NULL)
    {
        return -1;
    }
    if(queue->size=0)
    {
        return -1;
    }
    *value=queue->data[queue->head];
    return 0;
}

//=====================================
//销毁队列
void SeqQueueDestroy(SeqQueue* queue)
{
    if(queue==NULL)
    {
        return ;
    }
    free(queue->data);
    queue->size=0;
    queue->capacity=0;
    queue->head=0;
    queue->tail=0;
    return ;
}







