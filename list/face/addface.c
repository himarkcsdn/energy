//复制复杂链表

//定义复杂链表的结构体
typedef char ComplexType;
typedef struct ComplexNode
{
    ComplexType data;
    struct ComplexNode* next;
    struct ComplexNode* random;
}ComplexNode;

//创建复杂链表的结点
ComplexNode* CreateNode(ComplexType data)
{
    ComplexNode* new=(ComplexNode*)malloc(sizeof(ComplexNode));
    new->data=data;
    new->next=NULL;
    new->random=NULL;
    return new;
}

//求random域头结点的偏移量
int Diff(ComplexNode* head, ComplexNode* random)
{
    ComplexNode* cur=head;
    int offset=0;

    while(cur!=random)
    {
        ++offset;
        cur=cur->next;
    }
    return offset;
}
//设置复制后的结点的random的值
ComplexNode* Step(ComplexNode* new_head,int offset)
{
    ComplexNode* cur=new_head;
    int i=0;
    for(;i<offset;++i)
    {
        cur=cur->next;
    }
    return cur;
}

//复杂链表的复制
ComplexNode* CopyComplexList(ComplexNode* head)
{
    //原链表为空，则复制后的链表也为空
    if(head==NULL)
    {
        return NULL;
    }
    ComplexNode* cur=head;
    ComplexNode* new_head=NULL;
    ComplexNode* new_tail=NULL;

    //先复制各结点的数据域及next域
    while(cur!=NULL)
    {
        if(new_head==NULL)
        {
            new_head=new_tail=CreateNode(cur->data);
        }
        else
        {
            new_tail->next=CreateNode(cur->data);
            new_tail=new_tail->next;
        }
        cur=cur->next;
    }
    //再使两链表从头开始遍历，求原链表各结点的random域的偏移量，
    //再设置各结点的random的值
    cur=head;
    ComplexNode* new_cur=new_head;
    while(cur!=NULL)
    {
        if(cur->random==NULL)
        {
            new_cur->random=NULL;
        }
        else
        {
            int offset=Diff(head,cur->random);//求偏移量
            new_cur->random=Step(new_head,offset);//设置新链表中各结点的random域
        }
        cur=cur->next;
        new_cur=new_cur->next;
    }
    return new_head;
}
