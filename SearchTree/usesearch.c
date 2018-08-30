#include<stdio.h>
#include<string.h>

typedef char* SearchType;
//定义个二叉搜索树
typedef struct SearchNode
{
    struct SearchNode* lchild;
    struct SearchNode* rchild;
    SearchType data;
}SearchNode;

//二叉搜索树初始化
void SearchInit(SearchNode** proot)
{
    if(proot==NULL)
    {
        return ;
    }
    *proot=NULL;
    return ;
}
//创建节点
SearchNode* CreateNode(SearchType value)
{
    SearchNode* new=(SearchNode*)malloc(sizeof(SearchNode));
    new->data=value;
    new->lchild=NULL;
    new->rchild=NULL;
    return new;
}
//二叉搜索树插入
int SearchInsert(SearchNode**proot, SearchType value)
{
    int tmp=0;
    if(proot==NULL)
    {
        return ;
    }
    SearchNode* new_node=CreateNode(value);
    //如果是空树
    if(*proot==NULL)
    {
        *proot=new_node;
        return ;
    }
    tmp=strcmp((*proot)->data,value);
    if(tmp>0)
    {
        SearchInsert(&(*proot)->lchild,value);
    }
    else if(tmp<0)
    {
        SearchInsert(&(*proot)->rchild,value);
    }
    else  //如果插入元素已经存在则不做处理
    {
        return -1;
    }
    return 0;
}

//二叉搜索树的查找
SearchNode*  SearchFind(SearchNode* root, const SearchType to_find)
{
    if(root==NULL)
    {
        return NULL ;
    }
    int tmp=0;
    tmp=strcmp(root->data,to_find);

    if(tmp==1)
    {
        return root;
    }
    else if(tmp>0)
    {
        return SearchFind(&root->lchild,to_find);
    }
    else//tmp<0
    {
        return SearchFind(&root->rchild,to_find);
    }
}

int main()
{
    
    SearchNode* root;
    SearchInit(&root);

    SearchInsert(&root,"hello");
    SearchInsert(&root,"world");
    SearchInsert(&root,"my");
    SearchInsert(&root,"name");
    SearchInsert(&root,"is");
    SearchInsert(&root,"himark");

    printf("%s \n",SearchFind(root,"name")->data);

    printf("%s \n",SearchFind(root,"himark")->data);
    printf("%s \n",SearchFind(root,"hello")->data);
    printf("%s \n",SearchFind(root,"world")->data);
    printf("%s \n",SearchFind(root,"is")->data);
    printf("%s \n",SearchFind(root,"my")->data);
    printf("%s \n",SearchFind(root,"n")->data);
    printf("%s \n",SearchFind(root,"himar")->data);
    return 0;
}










