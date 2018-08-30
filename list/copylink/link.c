#include"link.h"
#include<string.h>
#include<stdlib.h>

//创建节点
LinkNode* Create(void)
{
    LinkNode* new=(LinkNode*)malloc(sizeof(LinkNode));
    return new;
}
//销毁节点
void Destroy(LinkNode* head)
{
    if(head==NULL)
    {
        return ;
    }
    free(head);
    head=NULL;
}
//初始化链表
void Init(LinkNode** phead)
{
    if(phead==NULL)
    {
        return ;
    }
    *phead==NULL;
}
//尾插
void Push_back(LinkNode**phead, Datatype x)
{
    if(phead==NULL)
    {
        return ;
    } 
    //空节点
    if(*phead==NULL)
    {
        *phead=Create();
        (*phead)->data=x;
        (*phead)->next=NULL;
        return ;
    }
    //常规尾插
    LinkNode* cur=*phead;
    LinkNode* new=Create();
    new->data=x;
    new->next=NULL;
    while(cur->next!=NULL)
    {
        cur=cur->next;
    }
    cur->next=new;
    return ;
}
//尾删
void Pop_back(LinkNode**phead)
{
    if(phead==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return ;
    }
    //只有一个节点
    if((*phead)->next==NULL)
    {
        LinkNode* cur=*phead;
        *phead=NULL;
        Destroy(cur);
        return ;
    }
    //常规尾删
    LinkNode* cur=*phead;
    LinkNode* pre=NULL;
    while(cur->next!=NULL)
    {
        pre=cur;
        cur=cur->next;
    }
    pre->next=NULL;
    Destroy(cur);
    return ;
}
//头插
void Push_front(LinkNode** phead, Datatype x)
{
    if(phead==NULL)
    {
        return ;
    }
    LinkNode* cur=*phead;
    LinkNode* new=Create();
    new->data=x;
    *phead=new;
    new->next=cur;
    return ;
}
//头删
void Pop_front(LinkNode**phead)
{
    if(phead==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return;
    }
    LinkNode* cur=*phead;
    while(cur!=NULL)
    {
        *phead=(*phead)->next;
    }
    Destroy(cur);
    return ;
}
//查找元素下标
size_t Find1(LinkNode* head, Datatype to_find)
{
    if(head==NULL)
    {
        return 0 ;
    }
    size_t count=0;
    LinkNode* cur=head;
    while(cur!=NULL)
    {
        ++count;
        if(cur->data==to_find)
        {
            return count;
        }
        cur=cur->next;
    }
    printf("no find\n");
    return -1;
}
//查找元素地址
LinkNode* Find2(LinkNode* head, Datatype to_value)
{
    if(head==NULL)
    {
        return NULL;
    }
    LinkNode* cur=head;
    while(cur!=NULL)
    {
        if(cur->data==to_value)
        {
            return cur;
        }
        cur=cur->next;
    }
    printf("no find\n");
    return NULL;
}
