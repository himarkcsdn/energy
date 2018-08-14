///////////////////////
//快速排序
//时间复杂度： 最坏O(n^2)  序列是完全逆序的
//             平均O(n*logn)
//
//空间复杂度：  O(logN)
//方法一：交换法

int64_t Partion1(int arr[], int64_t beg, int64_t end)
{
    //1. 先定义好区间的边界
    int64_t left=beg;
    int64_t right=end-1;
    //2 取最后一个元素为基准值
    int key=arr[right];
    while(left<right)
    {
        //3 从左到右找到一个大于基准值的元素
        while(left<right&& arr[left]<=key)
        {
            ++left;
        }
        //4 从右到左找到一个小于基准值的元素
        while(left<right&&arr[right]>=key)
        {
            --right;
        }
        //5 进行交换
        if(left<right)
        {
            Swap(&arr[left], &arr[right]);
        }
    }
    //6 此时是将left指向的值和最后一个元素（基准值）进行交换
        //此时的left指向的值一定大于等于基准值
    Swap(&arr[left], &arr[end-1]);
    return left;
}

void _QuickSort(int arr[], int64_t beg, int64_t end)
{
    if(end-beg<=1)
    {
        return ;
    }
    //partion函数的作用，是对当前[beg, end)区间进行调整
    //整理成以某个基准值为中心，左侧元素小于等于基准值，右测元素大于等于基准值
    //返回值表示的含义是基准值所在的下标
    int64_t mid=Partion1(arr, beg, end);
    _QuickSort(arr,beg,mid);
    _QuickSort(arr,mid+1,end);

}

void QuickSort(int arr[], int64_t size)
{
    _QuickSort(arr,0,size);
}

//========================================================
//挖坑法

int64_t Partion2(int arr[], int64_t beg, int64_t end)
{
    //定义区间边界
    int64_t left=beg;
    int64_t right=end-1;
    //取最后一个元素为基准值
    int key=arr[right];
    while(left<right)
    {
        //从左到右找到一个大于基准值的元素
        while(left<right&&arr[left]<=key)
        {
            ++left;
        }
        if(left<right)
        {
            //将找到的这个大于基准值的元素，填充到right指向的坑里
            //left也就成了一个坑
            arr[right--]=arr[left];
        }
        //从右到左找到一个小于基准值的元素
        while(left<right&&arr[right]>=key)
        {
            --right;
        }
        if(left<right)
        {
            arr[left++]=arr[right];
        }
    }
    arr[left]=key;
    return left;
}


void _QuickSort(int arr[], int64_t beg, int64_t end)
{
    if(end-beg<=1)
    {
        return ;
    }
    //Partion函数的作用，对当前[beg,end)区间进行调整
    //整理成以某个基准值为中心，左侧元素小于等于基准值，右侧元素大于等于基准值
    //返回值是基准值所在的下标

    int64_t mid=Partion2(arr, beg, end);
    _QuickSrot(arr, beg, mid);
    _QuickSort(arr, mid+1, end);
}

void QuickSort(int arr[], int64_t size)
{
    _QuickSort(arr,0,size);
}






