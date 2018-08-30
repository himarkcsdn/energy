#include"link.h"

//创建节点
LinkNode* linkCreate(void)
{
    LinkNode* new=(LinkNode*)malloc(sizeof(LinkNode));
    return new ;
}
//删除节点
void linkDestroy(LinkNode* head)
{
    if(head==NULL)
    {
        return ;
    }
    free(head);
}
//初始化链表头节点
void linkInit(LinkNode**phead)
{
    if(phead==NULL)
    {
        return ;
    }
    *phead=NULL;
}
//头插
void linkfrontPush(LinkNode** phead,DataType value )
{
    if(phead==NULL)
    {
        return ;
    }
    
    LinkNode* new=linkCreate();
    new->data=value;
    LinkNode* cur=*phead;//cur 指向头
    *phead=new;
    new->next=cur;     //新节点指向头节点
    
}
//尾插
void linkafterPush(LinkNode** phead, DataType value)
{
    if(phead==NULL)
    {
        return ;
    }
    //空链表
    if(*phead==NULL)
    {
        *phead=linkCreate();
        (*phead)->data=value;
        (*phead)->next=NULL;
        return;
    }
    //常规尾插
    LinkNode* new=linkCreate();
    new->data=value;
    new->next=NULL;
    LinkNode* cur=*phead;
    while(cur->next!=NULL)
    {
        cur=cur->next;
    }
    cur->next=new;
    return ;
}
//头删
void linkfrontPop(LinkNode** phead)
{
    if(phead==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return ;
    }
    LinkNode* cur=*phead;
    (*phead)=(*phead)->next;
    linkDestroy(cur);
    return ;
}
//尾删
void linkafterPop(LinkNode** phead)
{
    if(phead==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return ;
    }
    //如果只有一个节点
    if((*phead)->next==NULL)
    {
        LinkNode* cur=*phead;
        *phead=NULL;
        linkDestroy(cur);
        return ;
    }
    //两个或者以前的节点
    LinkNode* cur=*phead;
    LinkNode* pre=NULL;
    while(cur->next!=NULL)
    {
        pre=cur;
        cur=cur->next;
    }
    pre->next=NULL;
    linkDestroy(cur);
    return ;
}
//查找下标
size_t linkFind1(LinkNode* head,DataType to_find)
{
    if(head==NULL)
    {
        return 0;
    }
    int count=0;
    LinkNode* cur=head;
    while(cur!=NULL)
    {
        count++;
        if(cur->data==to_find)
        {
            
            return count;
        }
        cur=cur->next;
    }
    printf("没找到");
    return 0;
}
//查找地址
LinkNode* linkFind2(LinkNode*head, DataType to_value)
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
    printf("meizhaodao");
    return NULL;
}


//===================================================/














//pos前插
void linkfrontInsert(LinkNode** phead, LinkNode* pos, DataType value)
{
    if(phead==NULL||pos==NULL)
    {
        return ;
    }
    //如果Pos为头
    if(*phead==pos)
    {
        linkfrontPush(phead,value);
        return ;
    }
    //如果为常规位置
    //
    //方法一： 遍历到pos前 
    //LinkNode* new=linkCreate();
    //new->data=value;
    //LinkNode* cur=*phead;
    //LinkNode*pre=cur->next;
    //while(pre->next!=pos)
   // {
   //     pre=pre->next;
   // }
   // new->next=pre->next;
   // pre->next=new;
   // return ;
    //方法二： 乾坤大挪移
    LinkNode* new=linkCreate();
    new->data=pos->data;    //先将Pos拷给new , 在给pos赋值new
    new->next=pos->next;

    pos->data=value;
    pos->next=new;
    return ;

}
//pos后插
void linkafterInsert(LinkNode** phead, LinkNode* pos, DataType value )
{
    if(phead==NULL||pos==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return ;
    }
    LinkNode* new=linkCreate();
    new->data=value;
    new->next=pos->next;
    pos->next=new;
    return ;
}
//删除指定位置
void linkErase(LinkNode** phead, LinkNode* pos)
{
    if(phead==NULL||pos==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return;
    }
    //如果第一个为pos
    while(*phead==pos)
    {
        LinkNode* cur=*phead;
        (*phead)=(*phead)->next;
        linkDestroy(cur);
        return ;
    }
    //常规位置Pos
    LinkNode* cur=*phead;
    LinkNode* pre=NULL;
    while(cur!=NULL)
    {
        if(cur==pos)
        {
            LinkNode* tmp=cur;
            pre->next=cur->next;
            linkDestroy(tmp);
            return;
        }

        pre=cur;
        cur=cur->next;
    }
    return ;
}
//删除指定元素
void linkRemove(LinkNode** phead, DataType to_remove)
{
    if(phead==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return;
    }
    //如果是第一个元素
    if((*phead)->data=to_remove)
    {
        LinkNode* tmp=*phead;
        *phead=(*phead)->next;
        linkDestroy(tmp);
        return ;
    }
    //不是第一一个
    LinkNode* cur=*phead;
    LinkNode* pre=(*phead)->next;
    while(cur!=NULL)
    {
        if(cur->data==to_remove)
        {
            pre->next=cur->next;
            linkDestroy(cur);
            return ;
        }
        pre=pre->next;
        cur=cur->next;
    }
    return ;
}
//删除指定所有元素
void linkRemoveall(LinkNode** phead, DataType to_delete)
{

    if(phead==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return ;
    }
    LinkNode*cur=linkFind2(*phead, to_delete);
    while(cur!=NULL)
    {
        linkErase(phead,cur);
        cur=linkFind2(*phead,to_delete);
    }
    return ;
}
//判断链表是否为空
int linkisEmpty(LinkNode* head)
{
    if(head==NULL)
    {
        return 1;
    }
    return -1;
}
//求链表的长度
size_t linkSize(LinkNode* head)
{
    
    if(head==NULL)
    {
        return 0;
    }
    size_t count=0;
    LinkNode* cur=head;
    while(cur!=NULL)
    {
        cur=cur->next;
        count++;
    }
    return count;
}
//逆序打印单链表(递归)
void linkReserve(LinkNode* head)
{
    if(head==NULL)
    {
        return;
    }
    linkReserve(head->next);
    printf("%c\n",head->data);
}







