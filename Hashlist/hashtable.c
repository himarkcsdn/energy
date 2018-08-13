#include "hashtable.h"

#define Test() printf("\n=================%s===========\n",__FUNCCTION__)
//基于线性探测解决哈希冲突的哈希表


//哈希函数
int hash_func(KeyType key)
{
    return key%max_size;
}

//哈希表的初始化
void HashInit(HashTable* ht)
{
    if(ht==NULL)
    {
        return ;
    }
    ht->size=0;
    ht->func=hash_func;
    int i=0;
    for(i=0;i<max_size;i++)
    {
        //将哈希表的每一个位置初始化为空状态
        //代表相应的位置是未被使用过的
        ht->data[i].stat=Empty;
    }
    return ;
}

//销毁
void HashDestroy(HashTable *ht)
{
    if(ht==NULL)
    {
        return ;
    }
    //先将表中的每一个位置都置为无效状态
    int i=0;
    for(;i<max_size;i++)
    {
        ht->data[i].stat=Empty;
    }
    //再将有效元素个数清0
    ht->size=0;
    ht->func=NULL;
    return ;
}
//=================================================
//插入数据
//根据Key值计算出下标offset
//如果当前位置状态不是已插入，则插入元素，修改状态，有效个数+1
//如果当前位置状态是已插入，且key值相等，默认为不处理直接返回
//其余则认为offset更新向后循环判断是否可插

void HashInsert(HashTable* ht, KeyType key, ValType value)
{
    if(ht==NULL)
    {
        return ;
    }
    //判断当前Hash表能否继续插入
    //假设负载因子0.8
    if(ht->size>=0.8max_size)
    {
        //当前Hash表已经达到负载因子的上限，不能继续插入
        return;
    }
    //由key计算offset(由hash函数计算存放位置的下标)
    int offset=0;
    offset=ht->func(key);
    //但是该位置可能之前被别的数据占据了
    //所以要先判断计算出的位置能否放入当前数据
    //如果不能就从offset位置往后查找
    while(1)
    {
        if(ht->data[offset].stat!=Valid)
        {
            //如果找到的第一个位置不是有效位置
            //可以将该数据插入
            ht->data[offset].key=key;
            ht->data[offset].value=value;
            //插入完成以后将该位置置成有效状态
            ht->data[offset].stat=Valid;
            //哈希表有效元素个数+1
            ++ht->size;
            return ;
        }
        //走到这里说明计算出当位置不能放置待插数据
        //判断当前位置的元素是否和待插元素一样
        else if(ht->data[offfset].stat==Valid\
                &&ht->data[offset].key==key)
        {
            //说明存在相同元素
            //我们约定该哈希表不存在重复元素
            //则直接插入失败返回
            return;
        }
        //则更新offset值继续下一次循环往后查找
        else
        {
            ++offset;
            if(offset>=max_size)
            {
                //如果查找时offset走到了哈希表的末尾
                //还没有找到一个可插入的位置
                //则将其置为0，从头开始往后继续查找
                offset=0;
            }
        }//else结束
    }//while结束
}
//====================================================
//查找数据
//根据Key计算出下标offset值
//如果当前位置的状态是已插入
//   a.如果Key值相等，认为找到了
//   b.更新offset循环继续向后查找
//如果当前位置的状态是空，则找不到

int HashFind(HashTable *ht, KetType key, ValType *value)
{
    if(ht==NULL)
    {
        return 0;
    }
    //判断当前hash表中是否有有效元素
    if(ht->size==0)
    {
        //空哈希表
        return 0;
    }
    //由key值计算出offset
    int offset=0;
    offset=ht->func(key);
    //从offset开始往后查找
    while(1)
    {
        //在当前位置存放的是有效数据的前提下
        if(ht->data[offset].stat==valid)
        {
            if(ht->data[offset].key==key)
            {
                //找到了
                *value=ht->data[offset].value;
                return 1;
            }
            //当前位置不是待查找的元素
            //则更新offset的值继续查找
            else
            {
                ++offset;
                if(offset>=max_size)
                {
                    offset=0;
                }
            }
        }
        else if(ht->data[offset].stat==empty)
        {
            //说明待查找的元素不存在hash表中
            return 0;
        }
    }//while循环结束
    return 0;
}
//========================================
//删除数据
//根据Key值计算出下标offset
//如果当前位置状态是已插入且key值相等，则直接进行删除，修改状态
//如果当前位置状态是已插入key值不相等，更新offset循环向后寻找
//如果当前位置状态是空，则找不到删除失败

void HashRemove(HashTable*ht, keyType key)
{
    if(ht==NULL)
    {
        return ;
    }
    if(ht->size==0)
    {
        //空哈希表
        return ;
    }
    int offset=0;
    //由key值计算出offset
    offset=ht->func(key);
    //从offset开始往后找
    while(1)
    {
        if(ht->data[offset].stat==Valid\
                &&ht->data[offset].key==key)
        {
            //找到了待删除的元素
            //直接将该位置的状态置为被删除状态
            ht->data[offset].stat=Deleted;
            //将hash表中有效元素个数-1
            --ht->size;
            return ;
        }
        else if(ht->data[offset].stat==Empty)
        {
            //走到这里说明元素不存在
            return ;
        }
        else
        {
            //走到这里说明当前offset位置的值不是我们想要删除的
            //则更新Offset值继续查找
            ++offset;
            if(offset>=max_size)
            {
                offset=0;
            }
        }
    }//while 循环结束
    return ;
}


///////====================================================////////
//////////////////        Test                   /////////////////\

void HashPrint(HashTable*ht, const char* msg)
{
    printf("[%s]\n",msg);
    int i=0;
    for(;i<max_size;i++)
    {
        if(ht->data[i].stat==Valid)
        {
            printf("(%d:%d,%d) ",i,ht->data[i].key,ht->data[i].value);
        }
    }
    printf("\n");
}
void Test1()
{
    Test();
    HashTable ht;
    HashInit(&ht);
    //这里用。是因ht在这里是一个常量而不是一个指针类型
    printf("expect size is 0, actual size is %d\n",ht.size);
    printf("expect func is %p, catual func is %p\n",hash_func,ht.func);
}

void Test2()
{

    Test();
    HashTable ht;
    HashInit(&ht);

    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,20);
    HashInsert(&ht,1000,100);
    HashInsert(&ht,2000,200);
    HashPrint(&ht,"插入5个元素");
}

main()
{
    Test1();
    Test2();

    return 0;
}









