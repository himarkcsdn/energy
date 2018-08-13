#include"bucket.h"
//哈希函数
size_t hash_func(keyType key)
{
    return (key%max_size);
}
//===========================
//哈希表的初始化
void HashInit(HashTable* ht, HashFunc hash_func)
{
    if(ht==NULL)
    {
        return ;
    }

    ht->size=0;
    ht->func=hash_func;
    size_t i=0;
    //采用不带头节点的链表
    //将所有数组元素即链表头指针置为NULL;
    for(;i<max_size;i++)
    {
        ht->data[i]=NULL;
    }
    return;
}
//==============================
//哈希表的销毁


void HashDestroyNode(HashElem* p)
{
    free(p);
    p=NULL;
}
void HashDestroy(HashTable* ht)
{
    if(ht==NULL)
    {
        return ;
    }
    ht->size=0;
    ht->func=NULL;
    //遍历所有链表进行释放
    size_t i=0;
    for(;i<max_size;i++)
    {
        HashElem* cur=ht->data[i];
        if(cur==NULL)
        {
            continue;
        }
        while(cur!=NULL)
        {
            HashElem* pre=cur;
            HashDestroyNode(cur);
            cur=pre->next;
        }
        return ;
    }
}
//=========================================
//哈希表的插入


//在哈希桶中查找
HashElem* HashBucketFind(HashElem*head, keyType to_find)
{
    HashElem* cur=head;
    while(cur!=NULL)
    {   
        if(cur->key==to_find)
        {
            return cur;
        }
        cur=cur->next;
    }
    return NULL;
}

HashElem* CreateNode(KeyType key, ValType value)
{
    HashElem* new_node=(HashElem*)malloc(sizeof(HashElem));
    new_node->key=key;
    new_node->value=value;
    new_node->next=NULL;
    return new_node;
}

void HashInsert(HashTable*ht, KeyType key, ValType value)
{
    if(ht==NULL)
    {
        return ;
    }
    //约定哈希表中每个链表的平均元素个数（哈希表实际元素个数/数组长度）达到10就扩容或者插入失败
    //为了方便处理，达到10约定插入失败
    if(ht->size>=10*max_size)
    {
        return ;
    }

    size_t offset=ht->hash_func(key);
    //在对应链表中查找当前key是否存在，如果存在认为查找失败
    HashElem* ret=HashBucketFind(ht->data[offset],key);
    if(ret！=NULL)
    {
        //插入失败
        return ;
    }
    else
    {
        //插入元素不存在,对链表进行头插
        HashElem* new_node=CreateNode(key,value);
        //将新元素插入到当前的链表中
        new_node->next=ht->data[offset];
        //更新头节点的值为新插入的元素
        ht->data[offset]=new_node;
        ht->size++;
        return 1;
    }
}
//====================================================
//哈希桶的元素的查找
//
int HashFind(HashTable* ht, KeyType key, ValType* value)
{
    if(ht==NULL||value==NULL)
    {
        //非法输入
        return 0;
    }
    if(ht->size==0)
    {
        //空表
        return 0;
    }
    size_t offset=ht->hash_func(key);
    //找到offset的链表，遍历链表查找指定的key值
    HashElem* ret=HashBucketFind(ht->data[offset],key);
    if(ret==NULL)
    {
        return 0;
    }
    else
    {
        *value=ret->value;
        return 1;
    }
}
//===========================================
//哈希表中删除删除指定Key值

int HashBucketFindEx(HashElem* head, KetType to_find, HashElem** prenode, HashElem** curnode)
{
    HashElem* cur=head;
    HashElem* pre=NULL;
    while(cur!=NULL)
    {
        pre=cur;
        if(cur->key==to_find)
        {
            *prenode=pre;
            *curnode=cur;
            return 1;
        }
        cur=cur->next;
    }
    return 0;
}
void HashRemove(HashTable* ht, KeyType key)
{
    if(ht==NULL)
    {
        return ;
    }
    if(ht->size==0)
    {
        return ;
    }
    size_t offset=ht->hash_func(key);
    //通过offset找出相应的链表，在链表中查找指定的元素并进行删除
    HashElem* pre=NULL;
    HashElem* cur=NULL;
    int ret=HashBuckFindEx(ht->data[offset],key,&pre,&cur);
    if(ret==0)
    {
        return ;
    }
    else
    {
        //找到了
        if(pre==NULL)
        {
            //pre是cur的前一个元素，那么要删除的就是头节点
            //必须更新头节点的指针
            ht->data[offset]=cur->next;
        }
        else
        {
            //cur为待删除的元素，pre指向cur->next
            pre->next=cur->next;
        }
        HashDestroyNode(cur);
        --ht->size;
        return ;
    }
}




