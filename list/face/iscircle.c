//判断链表是否带环
//
//方法一：借助顺序表
//先将链表的头节点的地址存在顺序表中
//判断next域的地址是否在顺序表中出现过，如果没出现过则将
//next域的地址存放在顺序表中，依次往后遍历，如果next域的
//地址在顺序表中出现过，则说明带环。
//注意：该方法需要遍历 链表和顺序表  时间复杂度 O(n^2)
//  又开辟额外的空间存放各节点的地址 空间复杂度 O(n)

//方法二：借助指针
//定义快慢指针，快指针走两步，慢指针走一步
//如果没环，快指针先走完，结束条件快指针的next域或者next的next域为空
//如果带环，则快指针先进入环内，慢指针后入环，快慢指针最终会相遇
//如果带环，最坏情况是当慢指针进入环中，快指针已经在环中
//如果慢指针正好在快指针之后，则快指针需要走两个环长，
//而慢指针走一个环长，才相遇。

//判断是否带环
int linkCircle(LinkNode* head)
{
    if(head==NULL)
    {
        return 0;
    }
    LinkNode*fast=head;
    LinkNode*slow=head;
    while(fast->next!=NULL&&fast->next->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
        //相遇///有环
        if(fast==slow)
        {
            return 1;
        }
    }
    return 0;
}

//======================================================
//如果带环，求环长度
//
//如果链表带环，则快慢指针一定会相遇，则从相遇的地方绕环一周
//回到相遇的点时，走过的节点数即为环长

int linkcircleSize(LinkNode* head)
{
    if(head==NULL)
    {
        return ;
    }
    LinkNode* fast=head;
    LinkNode* slow=head;

    while(head->next!=NULL&&head->next->next!=NULL)
    {
        fast=fast->next->next;
        slow=fast->next;
        if(fast==slow)
        {
            int count=1;
            LinkNode* tmp=slow->next;
            while(tmp!=slow)
            {
                count++; 
                tmp=tmp->next;
            }
            return count;
        }
    }
    return 0;
}

//=====================================================
//求带环链表的入口点
// 相遇点到入口的距离与从头节点开始走的距离相等
// 如果要求在相同时间内走L步。他们的速度必须相同，快慢指针一次走一步

//求环的相遇点
LinkNode* linkcircleMeet(LinkNode* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    LinkNode* fast=head;
    LinkNode* slow=head;
    while(fast->next!=NULL&&fast->next->next!=NULL)
    {
        fast=fast->next->next;
        slow=slow->next;
        if(slow==fast)
        {
            return slow;
        }
    }
    return NULL;
}

LinkNode* linkcircleEntry(LinkNode* head)
{
    if(head==NULL)
    {
        return ;
    }
    LinkNode* meet=linkcircleMeet(head);
    if(meet==NULL)
    {
        return NULL;
    }
    LinkNode* cur1=head;  //从头开始走
    LinkNode* cur2=meet;  //从相遇点开始走
    while(cur1!=cur2)
    {
        cur1=cur1->next;
        cur2=cur2->next;
    }
    return cur1;
}

//=============================================
//判断两链表是否相交，若相交求出交点










