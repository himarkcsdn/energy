//实现一个只能在堆上生成对象的类
#include<iostream>
using namespace std;
class father
{
    public:
        static father* GetObj()
        {
            return new father();
        }
    public:
        int num_;
    private:
        father()
        {};
        father(const int num_)
        {};
        father&operator=(const int&num_)
        {};
};

//实现一个只能在栈上生成对象的类

class father
{
    public:
        static father GetObj()
        {
            return father();
        }
    private:
        father();
    private:
        int _name;
};

int main()
{
    //father* ptr=father::GetObj();
    father f=father::GetObj();
    return 0;
}





