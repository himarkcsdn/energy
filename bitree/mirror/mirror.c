#include<stdio.h>

#define COL 6;
#define ROW 6;

//定义地图存放墙和路
typedef struct Warehouse
{
    int map[ROW][COL];
}Warehouse;

//================================
//初始化地图
void MapInit(Warehouse* house)
{
    if(house==NULL)
    {
        return ;
    }

    int temp[ROW][COL]=
    {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,0,0,0},
        {0,1,1,0,0,0},
        {0,1,0,0,0,0},
        {0,1,0,0,0,0}
    };

    int row=0;
    for(;row<ROW;++row)
    {
        int col=0;
        for(;col<COL;++col)
        {
           house->map[row][col]=temp[row][col];
        }
    }
}

//=============================================
//从入口进入迷宫开始寻找出口
void Path(Warehouse* house,Point entry);

//表示迷宫各处的行列坐标
typedef struct Point
{
    int row;
    int col;
}Point;

//判断当前点能否落脚
int CanStay(Warehouse* house, Point cur)
{
    if(cur.row<0||cur.row>=ROW||cur.col<0||cur.col>=COL)
    {
        //当前点的位置在地图之外
        return 0;
    }
    if(house->map[cur.row][cur.col]==1)
    {
        //说明是路，且是未走过的路，可以落脚
        return 1;
    }
    else
    {
        //不能落脚
        return 0;
    }
}

//标记走过的路
void Mark(Warehouse* house, Point cur)
{
    if(house==NULL)
    {
        return ;
    }
    house->map[cur.row][cur.col]=2;
    return ;
}

//判断是否为出口
void IsExit(Point cur, Point entry)
{
    if(cur.row==entry.row&&cur.col==entry.col)
    {
        //入口点不能为出口点
        return 0;
    }
    if(cur.row==0||cur.row==ROW-1||cur.col==0||cur.col==COL-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//辅助判断函数
void _Path(Warehouse* house, Point cur, Point entry)
{
    if(house==NULL)
    {
        return ;
    }
    printf("(%d,%d)\n",cur.row,cur.col);

    //判断当前点能否落脚
    if(CanStay(house,cur)==0)
    {
        return ;
    }
    //如果可以落脚对其标记走过
    Mark(house,cur);
    //判断当前点是否为出口，如果是出口打印消息
    if(IsExit(cur,entry)==1)
    {
        printf("找到一条出路\n");
        return ;
    }
    //如果不是出口从当前点的周围顺时针探索（上，右，下，左）
    Point up=cur;
    up.row-=1;
    _Path(house,up,entry);

    Point right=cur;
    right.col+=1;
    _Path(house,right,entry);

    Point down=cur;
    dowm.row+=1;
    _Path(house,down,entry);

    Point left=cur;
    left.col-=1;
    _Path(house,left,entry);
    //如果四周探索完成，就回溯其他的路
    return ;
}
//方法一   回溯判断出口
void Path(Warehouse* house, Point entry)
{
    if(house==NULL)
    {
        return ;
    }
    //从入口开始探索是否满足走下去的要求
    //借用辅助函数判断
    _Path(house,cur,entry);
    return ;
}

//方法二借用栈实现判断出口
void Pathstack(Warehouse* house,Point entry)
{
    if(house==NULL)
    {
        return;
    }

    //定义栈，对其初始化
    SeqStack stack;
    SeqStackInit(&stack);

    //若能落脚，标记，入栈
    if(CanStay(house,entry)==0)
    {
        return ;
    }
    Mark(house,entry);
    SeqStackPush(&stack,entry);

    //循环判断
    while(1)
    {

        Point cur;
        int ret=SeqStackTop(&stack);
        if(ret==-1)
        {
            printf("没有找到");
            return ;
        }
        printf("(%d%d)\n",cur.row,cur.col);
        if(IsExit(cur,entry)==1)
        {
            printf("找到一条出口");
            return ;
        }

       //如果不是出口，对四周探索（例如顺时针）
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
}


