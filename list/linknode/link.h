#pragma once
#include<stdio.h>
#include<stdlib.h>
#define DataType char
typedef struct LinkNode
{
    DataType data;
    struct LinkNode* next;
}LinkNode;


//创建节点
LinkNode* linkCreate(void);
void linkDestroy(LinkNode* head);
void linkInit(LinkNode**phead);
void linkfrontPush(LinkNode** phead,DataType value );
void linkafterPush(LinkNode** phead, DataType value);
void linkfrontPop(LinkNode** phead);
void linkafterPop(LinkNode** phead);
//查找下标
size_t linkFind1(LinkNode* head,DataType to_find);
LinkNode* linkFind2(LinkNode*head, DataType to_value);


//pos前插
void linkfrontInsert(LinkNode** phead, LinkNode* pos, DataType value);
//pos后插
void linkafterInsert(LinkNode** phead, LinkNode* pos, DataType value );

//删除指定位置
void linkErase(LinkNode** phead, LinkNode* pos);
//删除指定元素
void linkRemove(LinkNode** phead, DataType to_remove);
//删除指定所有元素
void linkRemoveall(LinkNode** phead, DataType to_delete);
//判断链表是否为空
int linkisEmpty(LinkNode* head);
//求链表的长度
size_t linkSize(LinkNode* head);
//逆序打印单链表
void linkReserve(LinkNode* head);












