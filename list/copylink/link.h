#include<stdio.h>
#include<string.h>

typedef char Datatype;


typedef struct LinkNode
{
    Datatype* data;
    struct LinkNode* next;
}LinkNode;

//创建节点
LinkNode* Create(void);
//销毁节点
void Destroy(LinkNode* head);
//初始化链表
void Init(LinkNode** phead);
//尾插
void Push_back(LinkNode**phead, Datatype x);
//尾删
void Pop_back(LinkNode**phead);
//头插
void Push_front(LinkNode** phead, Datatype x);
//头删
void Pop_front(LinkNode**phead);
//查找元素下标
size_t Find1(LinkNode* head, Datatype to_find);
//查找元素地址
LinkNode* Find2(LinkNode* head, Datatype to_value);

