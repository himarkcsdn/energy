#include<stdio.h>
//实现最小栈
//  方法： 一次出入栈两个元素
//顺序栈

typedef struct MinStack
{
    SeqStack stack;
}MinStack;
//===============================
//栈的初始化（顺序栈）
void MinStackInit(MinStack* ms)
{
    if(ms==NULL)
    {
        return ;
    }
    //调用顺序栈的初始化
    InitSeqStack(&ms->stack);
    return;
}
//================================
//入栈
void MinStackPush(MinStack* ms,SeqStackType value)
{
    if(ms==NULL)
    {
        return ;
    }
    SeqStackType min=value;

    SeqStackType top;
    int ret=SeqStackTop(&ms->stack,&top);
    if(ret==0&&top<value)
    {
        min=top;
    }
    //入栈正常元素
    SeqStackPush(&ms->stack, value);
    //入栈新的最小值
    SeqStackPush(&ms->stack,min);
}

//==========================================
//出栈
void MinStackPop(MinStack* ms)
{
    if(ms==NULL)
    {
        return ;
    }
    if(ms->stack.size==0)
    {
        //空栈
        return ;
    }
    //出栈栈顶元素
    SeqStackPop(&ms->stack);
    //出栈正常元素
    SeqStackPop(&ms->stack);
    return ;
}

//==============================
//取栈顶元素 时间复杂度0（1）

int MinStackTop(MinStack* ms, SeqStackType* value)
{
    if(ms==NULL||value==NULL)
    {
        return -1;
    }
    if(ms->stack.size==0)
    {
        //空栈
        return -1;
    }
    //取栈顶元素；
    return SeqStackTop(&ms->stack,value);
}

//==================================================
//方法二：   利用两个栈保存正常元素和最小元素


//定义栈结构
typedef struct MinStack
{
    //该栈存放正常出入栈的元素
    SeqStack bstack;
    //该栈栈顶一直为最小元素，两栈的元素一直相同
    SeqStack tstack;
}MinStack;
//============================
//初始化
void MinStackInit(MinStack* ms)
{
    if(ms==NULL)
    {
        return ;
    }

    InitSeqStack(&ms->bstack);//正常栈
    InitSeqStack(&ms->tstack); //最小值的栈
    return ;
}
//================================
//入栈
void MinStackPush(MinStack* ms, SeqStackType value)
{
    if(ms==NULL)
    {
        return ;
    }
    //正常入栈
    SeqStackPush(&ms->bstack,value);
    SeqStackType top;
    SeqStackType min=value;
    //最小栈中取栈顶元素
    int ret=SeqStackTop(&ms->tstack,&top);
    if(ret==0&&top<value)
    {
        min=top;
    }
    SeqStackPush(&ms->tstack, min);
    return ;
}

//===================================
//出栈
void MinStackPop(MinStack* ms)
{
    if(ms==NULL)
    {
        return;
    }
    if(ms->bstack.size==0)
    {
        return ;
    }

    SeqStackPop(&ms->bstack);
    SeqStackPop(&ms->tstack);
    return ;
}

//==================================
//取栈顶元素
int MinStackTop(MinStack* ms, SeqStackType* value)
{
    if(ms==NULL||value==NULL)
    {
        return -1;
    }
    if(ms->tstack.size==0)
    {
        return -1;
    }
    return SeqStackTop(&ms->tstack,value);
}





