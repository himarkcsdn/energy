//逆置单链表
// a->b->c->d   d->c->b->a
// 将指针一直指向头节点，  取头节点的下一个为待删节点保存起来
// 删掉待删节点，将待删节点头插，直到头节点的下一个为空，即逆置完成
 //方法一（循环头插法）


void LinkReserve(LinkNode** phead)
{
    if(phead==NULL)
    {
        return ;
    }
    if(*phead==NULL)
    {
        return ;
    }
    LinkNode* cur=head;
    while(head->next!=NULL)
    {

        LinkNode* to_delete=cur->next;
        cur->next=to_delete->next;
        //头插
        to_delete->next=*phead;
        *phead=to_delete;
    }
    return ;
}


//===================================
//合并两个有序的单链表
//定义两个指针，比较两个链表的数据域，数据域小的进行尾插然后后移动
//如果两个数据域相等则只插入一个数据，当有一个链表为空时，将另一个
//链表剩余数据尾插到新链表中

LinkNode* linkunion(LinkNode* head1,LinkNode* head2)
{
    if(head1==NULL)
    {
        return head2;
    }
    if(head2==NULL)
    {
        return head1;
    }
    LinkNode* cur1=head1;
    LinkNode* cur2=head2;
    LinkNode* new_head=NULL;
    LinkNode* new_tail=NULL;

    while(head1!=NULL&&head2!=NULL)
    {
        if(cur1->data<cur2->data)
        {
            //新链表空
            if(new_tail==NULL)
            {
                new_head=new_tail=CreateNode(cur1->data);
            }
            else
            {//新链表不为空尾插
                new_tail->next=cur1->data;
                new_tail=new_tail->next; //尾指针后移
            }
            cur1=cur1->next;
        }
        else  //如果cur2<=cur1
        {
            if(new_tail==NULL)
            {
                new_head=new_tail=CreateNode(cur2->data);
            }
            else
            {
                new_tail->next=cur2->data;
                new_tail=new_tail->next;
            }
            cur2=cur2->next;
        }
    }   
    if(cur1!=NULL)
    {
        new_tail->next=cur1;
    }
    if(cur2!=NULL)
    {
        new_tail-next=cur2;
    }
    return new_head;
}

//==================================
//只遍历一次找到链表的中间节点
//
//定义快指针：一次走两步  慢指针：一次走一步
//当快指针走到结尾时刚好慢指针走到中间
//如果链表有奇数个节点，则找到条件，快指针的next为空
//如果链表有偶数个节点，则找到条件，快指针的next->next为空

LinkNode* linkfindpos(LinkNode* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    if(head->next=NULL)
    {
        //只有一个节点
        return head;
    }
    LinkNode* slow=head;
    LinkNode* fast=head;
    while(fast->next!=NULL&&fast->next->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
    }
    return slow;
}


//=================================
//查找倒数第K个节点只遍历一次
//
//快指针走一步，慢指针走一步
//让快指针先走K步，然后快慢指针再出发，当快指针下一个节点为空
//慢指针走到了倒数第K个节点
//注意：K不能大于等于链表的长度

LinkNode* linkfindk(LinkNode* head, int k)
{
    if(head==NULL)
    {
        return NULL;
    }
    LinkNode* fast=head;
    LinkNode* slow=head;
    int i=0;
    for(;i<k;i++)
    {
        if(fast==NULL)
        {
            return NULL;
        }
        fast=fast->next;
    }
    if(i<k)
    {
        return NULL;
    }

    while(fast->next!=NULL)
    {
        fast=fast->next;
        slow=slow->next;
    }
    return slow;
}









