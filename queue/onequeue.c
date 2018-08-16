//两个栈实现一个队列
//
//栈：后进先出
//队：先进先出
//   （入队列）  stack1入栈
//    出队列    stack1->stack2  再出栈
//    入队列    stack2->stack1 再入栈


//队列由两个顺序栈组成
typedef struct QueueBy2Stack
{
    SeqStack input;
    SeqStack output;
}QueueBy2Stack;

//队列的初始化
void QueueBy2StackInit(QueueBy2Stack* queue)
{
    if(queue==NULL)
    {
        return ;
    }
    InitSeqStack(&queue->input);
    InitSeqStack(&queue->output);
    return ;
}

//入队列
void QueueBy2StackPush(QueueBy2Stack* queue, SeqStackType value);
{
    if(queue==NULL)
    {
        return ;
    }
    int ret;
    SeqStackType top;
    //将output中的 所有元素入栈到input中的,再
    while(1)
    {
        ret=SeqStackTop(&queue->output,&top);
        if(ret==-1)
        {
            //空栈
            break;
        }
        SeqStackPush(&queue->input,top);
        SeqStackPop(&queue->output);
        
    }
    //对input进行入栈操作
    SeqStackPush(&queue->input,value);
    return ;
}

//================================
//出队列

void QueueBy2StackPop(QueueBy2Stack* queue)
{
    if(queue==NULL)
    {
        return ;
    }
    if(queue->input.size==0&&queue->output.size==0)
    {
        //空队列
        return ;
    }
    int ret;
    SeqStackType top;
    while(1)
    {
        ret=SeqStackTop(&queue->input,&top);
        if(ret==-1)
        {
            break;
        }
        SeqStackPush(&queue->output,top);
        SeqStackPop(&queue->input);
    }
    SeqStackPop(&queue->output);
}

//==========================================
//取队首元素
int QueueBy2StackTop(QueueBy2Stack* queue,SeqStackType* value)
{
    if(queue==NULL||value==NULL)
    {
        return -1;
    }
    if(queue->input.size==0&&queue->output.size==0)
    {
        return -1;
    }
    int ret;
    SeqStackType top;
    while(1)
    {
        ret=SeqStackTop(&queue->input,&top);
        if(ret==-1)
        {
            break;
        }
        SeqStackPush(&queue->output,top);
        SeqStackPop(&queue->input);

    }
    SeqStackTop(&queue->output,value);
    return 0;
}
























