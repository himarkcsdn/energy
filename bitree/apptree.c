//2018-07-06
#include<stdio.h>

typedef char TreeType ;

//定义树的结点
typedef struct TreeNode
{
    TreeType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

//初始化
void treeInit(TreeNode** proot)
{
    if(proot==NULL)
    {
        return ;
    }
    *proot=NULL;
    return ;
}
//根据先序遍历的结果创建一颗树
TreeNode* _TreeCreate(TreeType arr[], size_t size , size_t *index , char null_flag)
{
    if(arr==NULL||size<0||index==NULL)
    {
        //非法输入
        return NULL ;
    }
    if(*index==NULL)
    {
        //数组已经遍历结束，树创建完成
        return NULL
    }
    if(arr[*index]==null_flag)
    {
        //空树
        return NULL;
    }
    //创建根结点
    TreeNode* root=CreateNode(arr[*index]);
    (*index)++;
    //递归创建左子树
    root->lchild=_TreeCreate(arr,size,index,null_flag);
    (*index)++;
    //递归创建右子树
    root->rchild=_TreeCreate(arr,size,index,null_flag);
    return root ;
}
TreeNode* TreeCreate(TreeType arr[], size_t size , char null_flag)
{
    size_t index=0;
    TreeNode* root=_TreeCreate(arr,size,&index,null_flag);
    return root ;
}

//=====================================================
//已知道先序遍历和空子树的位置，还原一颗二叉树 
//#表示空子树  
//判断是否非法，是否还原结束，
//创建根结点，递归创建左子树，递归创建右子树

TreeNode* _TreeCreate(TreeType arr[], size_t size, size_t* index, char null_flag)
{
    if(size<0||arr==NULL||index==NULL)
    {
        //非法
        return NULL;
    }
    if(arr[*index]==null_flag)
    {
        //空子树
        return NULL;
    }
    if(*index==NULL)
    {
        //数组遍结束，树还原完成
        return NULL;
    }
    TreeNode* root=CreateNode(arr[*index]);
    (*index)++;
    root->lchild=_TreeCreate(arr,size,index,null_flag);
    (*index)++;
    root->rchild=_TreeCreate(arr,size,index,null_flag);
    return root;
}


TreeNode* TreeCreate(TreeType arr[],size_t size, char null_flag)
{
    size_t index=0;
    TreeNode* root=_TreeCreate(arr,size,&index,null_flag);
    return root;
}

//===============================================
//克隆一棵树   （递归实现）下面采用的是先序遍历

//克隆根节点
//递归克隆左子树
//递归克隆右子树      遇到空树直接返回跳出递归函数

TreeNode* TreeClone(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return NULL;
    }
    //克隆根节点
    TreeNode* new_root=CreateNode(root->data);
    //递归克隆左子树
    new_root->lchild=TreeClone(root->lchild);
    //递归克隆右子树
    new_root->rchild=TreeClone(root->rchild);
    //返回根节点
    return new_root;
}

//=================================================
//二叉树中结点的个数    
//方法一 : 结点个数= 树的左子树结点，加右子树结点+根结点

size_t TreeSize(TreeNode* root)
{
    if(root==NULL)
    {
        return 0
    }
    //统计左子树的节点个数
    size_t lsize=TreeSize(root->lchild);
    //统计右子树的节点个数
    size_t rsize=TreeSize(root->rchild);
    return 1+lsize+rsize;
}
//方法二  递归遍历用计数器统计
void _TreeSize(TreeNode* root, size_t* count)
{
    if(root==NULL)
    {
        //空树
        return ;
    }
    if(count==NULL)
    {
        //非法输入
        return ;
    }
    (*count)++;
    _TreeSize(root->lchild,count);
    _TreeSize(root->rchild,count);
    return ;
}
size_t TreeSize(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return 0;
    }
    size_t count=0;
    _TreeSize(&root,&count);
    return count;
}


//====================================
//求二叉树中叶子节点的个数
//方法一
size_t Treeleaf(TreeNode* root)
{
    if(root==NULL)
    {
        //空树
        return 0;
    }
    size_t count=0;
    if(root->lchild==NULL&&root->rchild==NULL)
    {   
        //只有根节点
        return 1;
    }
    //统计左子树
    size_t lsize=Treeleaf(root->lchild);
    //统计右子树
    size_t rsize=Treeleaf(root->rchild);
    return lsize+rsize;
}


void _Treeleaf(TreeNode* root, size_t * size)
{
    if(root==NULL)
    {
        //空树
        return ;
    }
    if(size==NULL)
    {
        //非法输入
        return ;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        (*count)++;
    }
    _Treeleaf1(root->lchild,count);
    _Treeleaf1(root->rchild,count);
    return ;
    
}

size_t Treeleaf1(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    size_t count=0;
    _Treeleaf1(&root,&count);
    return count;
    
}

//==============================
//
//求二叉树第k层节点的个数

//即先序遍历根节点的左右孩子的K-1层

size_t TreeKLevelSize(TreeNode* root,int K)
{
    if(k<1)
    {
        return 0;
    }
    if(k==1)
    {
        return 1;
    }
    if(root==NULL)
    {
        return 0;
    }
    return TreeKLevelSize(root->lchild,k-1)+TreeKLevelSize(root->rchild,k-1);
}

//===============================
//求二叉树的深度或高度
//遍历左右孩子，左右孩子中节点数多的即为树的高度
size_t TreeHeight(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->lchild==NULL&&root->rchild==NULL)
    {
        return 1;
    }
    size_t lheight = TreeHeight(root->lchild);
    size_t rheight = TreeHeight(root->rchild);

    return (lheight > rheight)? 1+lheight : 1+rheight;
}

//=======================================
//在二叉树中查找节点(给定数值，求对应节点的指针，假设二叉树中的节点是不重复的)
//先序遍历改为查找，节点为空即为递归出口
TreeNode* TreeFind(TreeNode* root,TreeType to_find)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->data==to_find)
    {
        return root;
    }
    TreeNode* lret = TreeFind(root->lchild,to_find);
    TreeNode* rret = TreeFind(root->rchild,to_find);
    return (lret == NULL)? rret : lret;
}


//=======================================
//求当前节点的父节点
//先序遍历树，如果节点的左右孩子值等于当前值，则找到返回。
TreeNode* Parent(TreeNode* root,TreeNode* child)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(child==NULL)
    {
        return NULL;
    }
    if(root->lchild == child || root->rchild == child)
    {
        return root;
    }
    TreeNode* lret = Parent(root->lchild,child);
    TreeNode* rret = Parent(root->rchild,child);
    return (lret != NULL)? lret : rret;
}

//========================================
//查找指定节点的左孩子

TreeNode* LChild(TreeNode* node)
{
    if(node==NULL)
    {
        return NULL;
    }
    return node->lchild;
}


//查找指定节点的右孩子

TreeNode* RChild(TreeNode* node)
{
    if(node==NULL)
    {
        return NULL;
    }
    return node->rchild;
}


//======================================
//销毁一颗树

void DestroyNode(TreeNode* node)
{
    free(node);
    return ;
}
//二叉树的销毁(后序遍历销毁)
void TreeDestroy(TreeNode* root)
{
    if(root==NULL)
    {
        //非法输入
        return ;
    }
    if(*root==NULL)
    {
        //空树
        return ;
    }
     TreeDestroy(&((*root)->lchild));//销毁左子树
     TreeDestroy(&((*root)->rchild));//销毁右子树
     DestroyNode(*root);//销毁根节点
     *root = NULL;//将销毁的结点置为空
     return ;
}


