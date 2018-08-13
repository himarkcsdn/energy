#include"vector.h"


void TestVector()
{
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    v1.PushBack(4);
    v1.Print();
    size_t pos=v1.Find(2);

    cout<<"期望:1 实际: "<<pos<<endl;

    Vector v2(v1);
    v2.Insert(0,0);
    v2.Print();

    Vector v3;
    v3=v2;
    v3.Print();
    v3.Erase(1);
    v3.Print();
}

int main()
{
    cout<<"顺序表："<<endl;
    TestVector();
    return 0;
}
