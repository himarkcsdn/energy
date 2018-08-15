#include<stdio.h>
//先序遍历，借助栈实现

//1根节点入栈
//2判断栈顶元素是否为空
//3访问栈顶元素，出栈
//4栈顶元素的右孩子若不为空，入栈。栈顶元素的左孩子不为空，入栈。
//5循环2-4
void TreePreLoop(TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }
    //定义一个栈
    SeqStack stack;
   //栈的初始化
    SeqStackInit;
    //定义栈顶元素类型
    SeqStackType top;
    //根节点入栈
    SeqStcakPush(&stack,top);
    while(1)
    {
        int ret=SeqStackTop(&stack,&top);
        if(ret==-1)
        {
            return ;
        }
        printf("%c",top->data);
        SeqStackPop(&stack);
        if(top->rchild!=NULL)
        {
            //入栈
            SeqStackPush(&stack,top->rchild);
        }
        if(top->lchild!=NULL)
        {
            //入栈
            SeqStcakPush(&stack,top->lchild);
        }
    }  
    return ;
}

//中序遍历 非递归版（借助栈实现）
//定义指针变量cur指向root
//1当cur不为空时，入栈，cur指向左孩子，循环直到cur左孩子为空
//2取栈顶元素如果为空则遍历完成
//3如果栈顶元素不为空，访问栈顶元素，出栈，
//4cur指向栈顶元素的右孩子
//5循环1-4
//


void TreeInOrder(TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }

    //定义一个栈
    SeqStack stack;
    //对栈进行初始化
    SeqStackInit;
    //定义指针变量指向根节点
    TreeNode* cur=root;
    while(1)
    {
        //当根节点不为空
        while(cur!=NULL)
        {
            //入栈根节点
            SeqStackPush(&stack,cur);
           //cur指向跟栈顶元素的左孩子
            cur=cur->lchild;
        }
        //判断栈顶元素是否为空
        int ret=SeqStackTop(&stack,&cur);
        if(ret==-1)
        {
            //如果为空说明遍历结束
            return ;
        }
        //如果不为空访问栈顶元素，并出栈
        printf("%c",cur->data);
        SeqStackPop(&stack);
        //cur指向栈顶元素的右孩子
        cur=cur-rchild;
    }
    return ;
}


//============================================
//后序遍历  非递归版（借用栈实现）
//cur指针变量指向root

//1当cur不为空，入栈，cur指向左孩子，循环直到cur为空
//2取栈顶元素如果为空则遍历结束
//3如果cur的右孩子为空或者右孩子与上一次节点相同
//则访问栈顶元素，出栈，将pre置为top
//4cur指向栈顶元素的右孩子
//5循环2-4

void TreeLater(TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }

    //定义一个栈
    SeqStack stack;
    //栈的初始化
    SeqStcakInit;
    //定义指针变量cur指向root
    TreeNode* cur=root;
    //指针pre为存储上一次访问的节点
    TreeNode* pre=NULL;

    while(1)
    {
        while(cur!=NULL)
        {
            //入栈cur 
            SeqStackPush(&stack,cur);
            //cur指向左孩子
            cur=cur->lchild;
        }
        TreeNode* top=NULL;
        //取栈顶元素
        int ret=SeqStackTop(&stack,&top);
        if(ret==-1)
        {
            //如果栈顶元素为空，则遍历结束
            return ;
        }
        //栈顶元素不为空，判断右孩子是为空
        //或者右孩子是否与上一次节点相同
        if(top->rchild==NULL||top->rchild==pre)
        {
            //访问栈顶元素
            printf("%c",top->data);
            //栈顶元素保存到pre里  
            pre=top;
            //出栈
            SeqStackPop(&stack);
        }
        else
        {
            //cur指向栈顶元素的右孩子
            cur=top->rchild;
        }
    }
    return ;
}

//============================================
//求二叉树的镜像
//将遍的打印操作改为交换左右节点
//先序遍历实现（递归版）
void Swap(TreeNode**a, TreeNode**b)
{
    TreeNode* tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}
void  TreeMirror(TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }
    Swap(&root->lchild,&root->rchild;)
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
    return ;
}
//层序遍历实现（非递归版）
void CenterTreeMirror(TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }

    SeqQueue queue;
    SeqQueueInit ;

    QueueType top;
    SeqQueuePush(&queue,root);
    while(1)
    {
        int ret=SeqQueueTop(&queue,&top);
        if(ret==-1)
        {
            return ;
        }
        Swap(&top->lchild,&top->rchild);
        SeqQueuePop(&queue);
        if(top->lchild!=NULL)
        {
            SeqQueuePush(top->lchild);
        }
        if(top->rchild!=NULL)
        {
            SeqQueuePush(top->rchild);
        }
    }
    return ;
}

//============================================
//判断一颗二叉树是否为完全二叉树
//
//
//





//===========================================
//根据先序和中序结果还原一颗二叉树










