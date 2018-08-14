//===================================
//归并排序
//时间复杂度 O(N*logN)
//空间复杂度 O(N)
//稳定性：稳定排序
/////////////////

//第一个区间[beg,mid)
//第二个区间[mid,end)
void _MergeArr(int arr, int64_t beg, int64_t mid, int64_t end, int* tmp)
{
    int64_t cur1=beg;
    int64_t cur2=mid;
    int64_t tmp_index=beg;
    while(cur1<mid&&cur2<end)
    {
        if(arr[cur1]<arr[cur2])
        {
            tmp[tmp_index++]=arr[cur1++];
        }
        else
        {
            tmp[tmp_index++]=arr[cur2++];
        }
    }
    if(cur1<mid)
    {
        while(cur1<mid)
        {
            tmp[tmp_index++]=arr[cur1++];
        }
    }
    else
    {
        while(cur2<end)
        {
            tmp[tmp_index++]=arr[cur2++];
        }
    }
    while(cur1<mid)
    {
        tmp[tmp_index++]=arr[cur1++];
    }
    while(cur2<end)
    {
        tmp[tmp_index++]=arr[cur2++];
    }
    memcpy(arr+beg,tmp+beg, sizeof(int)*(end-beg));
}

void _MergeSort(int arr[], int64_t beg, int64_t end, int* tmp)
{
    if(end-beg<=1)
    {
        return ;
    }
    int64_t mid=beg+(end-beg)/2;
    _MergeSort(arr, beg, mid, tmp);
    _MergeSort(arr, mid, end, tmp);
    //先保证左右区间均是有序，才能进行合并
    _MergeArr(arr, beg, mid, end, tmp);
}

void MergeSort(int arr[], int64_t size)
{
    int *tmp=(int*)malloc(sizeof(int)*size);
    _MergeSort(arr,0,size,tmp);
    free(tmp);
}

//=====================================
//归并排序

        return ;
    }
    int64_t mid=beg+ (end-beg)/2;
    _MergeSort(arr, beg, mid, tmp);
    _MergeSort(arr, mid, end, tmp);
    MergeArr(arr,beg,mid,end,tmp);
}

void MergeSort(int arr[], int64_t size)
{
    int* tmp=(int*)malloc(sizeof(int)); 
    _MergeSort(arr,0,size);
    free(tmp);
}







