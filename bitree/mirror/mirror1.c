#include<stdio.h>



#define ROW 6
#define COL 6

//定义结构体存放地图和路
typedef struct Warehouse
{
    int map[ROW][COL];
}Warehouse;

//地图中的行列点
typedef struct Point
{
    int row;
    int col;
}Point;

//初始化地图
void MapInit(Warehouse* house)
{
    if(house==NULL)
    {
        return ;
    }
    int tmp[ROW][COL]=
    {

    }
    int row=0;
    for(;row<ROW;++row)
    {
        int col=0;
        for(;col<COL;++col)
        {
            house->map[row][col]=tmp[row][col]
        }
    }
    return ;
}

//判断当前点是否可以落脚
int CanStay(Warehouse*house, Point cur)
{
    if(house==NULL)
    {
        return 0;
    }
    if(cur.row<0||cur.col<0||cur.row>ROW||cur.col>COL)
    {
        return 0;
    }
    if(house->map[cur.row][cur.col]==1)
    {
        return 1;
    }
    return 0;
}

//标记当前点
void Mark(Warehouse*house, Point cur)
{
    if(house==NULL)
    {
        return ;
    }
    house->map[cur.row][cur.col]=2;
    return ;
}
//判断当前点是否为出口
int IsExit(Point cur,Point entry)
{
    //入口不能为出口
    if(cur.row==entry.row||cur.col==entry.col)
    {
        return 0;
    }
    if(cur.row=0||cur.row=ROW-1||cur.col==0||cur.col==COL-1)
    {
        return 1;
    }
    return 0;
}

void _Path(Warehouse*house, Point cur,Point entry)
{
    if(house==NULL)
    {
        return ;
    }
    printf("%(%d%d)\n",cur.row,cur.col);
    //是否可以落脚
    if(CanStay(house,cur)==0)
    {
        return 0;
    }
    Mark(house,cur);
    //是否为出口
    if(IsExit(house,cur)==1)
    {
        printf("找到一条出口");
        return ;
    }
    
    //如果不是出口探索四周（按照顺时针）
    Point up
    up.row-=1;
    _Path(house,up,entry);

    Point right
    right.col+=1;
    _Path(house,right,entry);

    Point down
    down.row+=1;
    _Path(house,down,entry);
    
    Point left
    left.col-=1;
    _Path(house,left,entry);

    return ;

}
//根据一条入口找到出口
void Path(Warehouse*house ,Point entry)
{
    if(house==NULL)
    {
        return ;
    }
    _Path(house,entry,entry);
    return ;
}


////////////借用栈实现
//
void PathStack(Warehouse*house,Point entry)
{
    if(house==NULL)
    {
        return ;
    }
    //定义 初始化栈
    SeqStack stack;
    SeqStackInit(&stack);
    //如果能落脚，标记，入栈
    if(CanStay(house,entry)==0)
    {
        return 0;
    }
    Mark(house,entry);
    SeqStackPush(&stack,entry);

    while(1)
    {
        Point cur;
        int ret=SeqStackTop(&stack,cur);
        if(ret==-1)
        {
            printf("没找到");
            return ;
        }
        printf("(%d%d)\n",cur.row,cur->col);
        if(IsExit(cur,entry)==1)
        {
            printf("找到了");
            return ;
        }

        //探索四周
        Point up;
        up.row-=1;
        if(CanStay(house,up)==1)
        {
            Mark(house,up);
            SeqStackPush(&stack,up);
            continue;
        }

        Point right;
        right.col+=1;
        if(CanStay(house,right)==1)
        {
            Mark(house,right);
            SeqStackPush(&stack,right);
            continue;
        }
        
        Point down;
        down.row+=1;
        if(CanStay(house,down)==1)
        {
            Mark(house,down);
            SeqStackPush(&stack,down);
            continue;
        }
        Point left;
        left.col-=1;
        if(CanStay(house,left)==1)
        {
            Mark(house,left);
            SeqStackPush(&stack,left);
            continue;
        }
        SeqStackPop(&stack);
    }
    return ;
}


