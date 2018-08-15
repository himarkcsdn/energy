//2018-07-06
#include<stdio.h>

typedef char Treetype;

//定义树的节点
typedef struct TreeNode
{
    Treetype data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

//初始化
void treeInit(TreeNode** proot)
{
    if(proot==NULL)
    {              
        printf("#"); //#表示节点为空
        return ;
    }
    *proot=NULL;
    return ;
}

//先序遍历（递归） V L R
void treePrior(TreeNode* root)
{
    if(root==NULL)
    {
        printf("#");
        return ;
    }
    //输出 根节点
    printf("%c",root->data);
    //递归遍历左子树
    treePrior(root->lchild);
    //递归遍历右子树
    treePrior(root->rchild);
    return ;
}
//中序遍历   L V  R
void treeCenter(TreeNode* root)
{
    if(root==NULL)
    {
        print("#") //输出空节点
        return ;
    }
    //递归遍历左子树
    treeCenter(root->lchild);
    //输出根节点
    printf("%c",root->data);
    //递归遍历右子树
    treeCenter(root->rchild);
    return ;
    
}

//后序遍   L  R   V
void treeLater(TreeNode* root)
{
    if(root==NULL)
    {
        printf("#")//#表示输出空节点
        return ;
    }
    //递归遍历左子树
    treeLater(root->lchild);
    //递归遍历右子树
    treeLater(root->rchild);
    //输出根节点
    printf("%c",root->data);
    return ;
}
//层序遍历   借用队列实现
void treeLevel(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return ;
    }
    //定义队列
    SeqQueue queue;
    //初始化队列
    SeqQueueInit(&queue);
    
   //1根节点入队列
    SeqQueuePush(&queue, root);
   int ret;
   SeqQueueType front;
   while(1)
   {
        //2取队首元素，如果为空则结束
        ret=SeqQueueTop(&queue, &front);
        if(ret==-1)
        {
        //队列已空，树已经遍历完了
            return ;
        }
        //3如果队首元素不为空，访问队首元素
        print("%c",front->data);
        //4将队首元素出队列，
        SeqQueuePop(&queue);
        //5如果队首元素左右孩子不为空，将左右节点的指针入队列
        if(front->lchild!=NULL)
        {
            SeqQueuePush(&queue,front->lchild);
        }
        if(front->rchild!=NULL)
        {
            SeqQueuePush(&queue,front->rchild);
        }
                  //循环2~5即可
    }
   return ;
}




