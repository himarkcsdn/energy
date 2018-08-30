
#include"link.h"

void printChar(LinkNode* head, const char* msg)
{
    if(head==NULL)
    {
        printf("空指针");
        return ;
    }
    printf("%s\n",msg);
    for(;head!=NULL;head=head->next)
    {
        printf("%c\n",head->data);
    }
    printf("\n");
    return ;
}

void AfterPush()
{

    LinkNode* head;
    linkInit(&head);

    linkafterPush(&head,'a');
    linkafterPush(&head,'b');
    linkafterPush(&head,'c');
    linkafterPush(&head,'d');
   
    printChar(head,"尾插 a b c d");
}

void AfterPop()
{

    LinkNode* head;
    linkInit(&head);

    linkafterPush(&head,'a');
    linkafterPush(&head,'b');
    linkafterPush(&head,'c');
    linkafterPush(&head,'d');   
    printChar(head,"尾插 a b c d");

    linkafterPop(&head);
    linkafterPop(&head);
    linkafterPop(&head);
   
    printChar(head,"尾删 3个元素");
}
void FrontPush()
{
    LinkNode* head;
    linkInit(&head);

    linkfrontPush(&head, 'd');
    linkfrontPush(&head, 'c');
    linkfrontPush(&head, 'b');
    linkfrontPush(&head, 'a');
    printChar(head,"头插 4个元素");

}

void FrontPop()
{
    LinkNode* head;
    linkInit(&head);

    linkfrontPush(&head, 'd');
    linkfrontPush(&head, 'c');
    linkfrontPush(&head, 'b');
    linkfrontPush(&head, 'a');
    printChar(head,"头插 4个元素");
    
    linkfrontPop(&head);
    linkfrontPop(&head);
    linkfrontPop(&head);
    
    printChar(head,"头删 3个元素");
}


void Find1()
{
    LinkNode* head;
    linkInit(&head);

    linkfrontPush(&head, 'd');
    linkfrontPush(&head, 'c');
    linkfrontPush(&head, 'b');
    linkfrontPush(&head, 'a');
    printChar(head,"头插 4个元素");

    size_t ret=0;
    linkFind1(head,'c');
    ret=linkFind1(head,'c');
    printf("%lu\n",ret);

}

//============================================
void alltest()
{
    LinkNode* head;
    linkInit(&head);

    linkfrontPush(&head, 'd');
    linkfrontPush(&head, 'c');
    linkfrontPush(&head, 'b');
    linkfrontPush(&head, 'a');
    printChar(head,"头插 4个元素");

    linkfrontInsert(&head, head->next,'y');
    printChar(head,"第二个位置插入y");
    linkafterInsert(&head, head->next,'z');
    printChar(head,"第二个位置之后插入z");
    
    linkErase(&head,head->next);
    printChar(head,"删除第二个位置的y");

    linkRemove(&head,'c');
    printChar(head, "删除指定元素c");
    
    size_t t=linkSize(head);
    printf("链表长度%d\n",t);
    
    linkReserve(head);
    printChar(head,"逆序打印链表");
}

int main()
{
//    AfterPush();
//    AfterPop();
//   FrontPush();
//   FrontPop();   
//    Find1();
    alltest();
    return 0 ;
}

