#include<stdio.h>

//定义搜索二叉树的节点结构/孩子表示法
typedef char SearchTreeType;
typedef struct SearchTreeNode
{
    SearchTreeType data;
    struct SearchTreeNode*lchild;
    struct SearchTreeNode*rchild;
}SearchTreeNode;

//初始化二叉搜索树
void SearchTreeInit(SearchTreeNode** proot)
{
    if(proot==NULL)
    {
        return ;
    }
    *proot=NULL;
    return ;
}

//二叉搜索树插入元素（递归）
void SearchTreeInsert(SearchTreeNode**proot, SearchTreeType value)
{
    if(proot==NULL)
    {
        return ;
    }
    SearchTreeNode* ne_node=CreateNode(value);
    //根节点为空  
    if(*proot==NULL)
    {
        *proot=new_node;
        return ;
    }
    //    根节点不为空
    //如果插入元素小于根节点，递归插入左子树
    if(value<(*proot)->data)
    {
        SearchTreeInsert(&(*proot)->lchild,value);
    }
    //如果插入元素大于根节点，递归插入右子树
    else if(value>(*proot)->data)
    {
        SearchTreeInsert(&(*proot)->rchild,value);
    }
    else //如果插入元素等于根节点
    {
        //约定二叉树不允许相等的节点
        //所以不做处理
        return ;
    }
    return ;
}

//搜索二叉树的查找
SearchNode* SearchTreeFind(SearchTreeNode* root, SearchTreeType to_find)
{
    if(root==NULL)
    {
        //非法输入
        return ;
    }
    if(root->data==to_find)
    {
        return root; 
    }
    else if(to_find<root->data)
    {
        return SearchTreeFind(&root->lchild,to_find);
    }
    else
    {
        return SearchTreeFind(&root->rchild,to_find);
    }
}

//搜索二叉树的删除
void SearchTreeRemove(SearchTreeNode** proot, SearchTreeType to_remove )
{
    if(proot==NULL)
    {
        return ;
    }
    if(*proot==NULL)
    {
        return ;
    }

    SearchTreeNode* cur=*proot;
    //如果待删除值小于根节点，在左子树递归查找
    if(to_remove<cur->data)
    {
        SearchTreeRemove(&cur->lchild,to_remove);
    }
    //如果待删除值大于根节点，在右子树递归查找
    else if(to_remove>cur->data)
    {
        SearchTreeRemove(&cur->rchild,to_remove);
    }
    //找到了
    else
    {
        //要删除的节点没孩子
        if(cur->lchild==NULL&&cur->rchild==NULL)
        {
            *proot==NULL;
            DestroyNode(cur);
        }
        //要删除的节点只有左孩子
        else if(cur->lchild!=NULL&&cur->rchild==NULL)
        {
            *proot=cur->lchild;
            DestroyNode(cur);
        }
        //要删除的节点只有右孩子
        else if(cur->lchild==NULL&&cur->rchild!=NULL)
        {
            *proot==cur->rchild;
            DestroyNode(cur);
        }
        //要删除的节点有左右孩子
        else
        {
            //在右子树中查找最小值，将值赋给要删除的节点
            SearchTreeNode* min=cur->rhicld;
            while(min->rchild!=NULL)
            {
                min=min->rchild;

            }
            cur->data=min->data;
            //递归删除最小值
           SearchTreeRemove(&cur->rchild,min->data);
        }
    }
    return ;
}



