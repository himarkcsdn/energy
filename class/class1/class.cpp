#include<iostream>
using namespace std;

class father
{
    public:
        /*static father* GetObj()
        {
            return new father();
        }*/
        static father GetObj()
        {
            return father();
        }
    private:
        father()
        {
            cout<<"father()"<<endl;
        }
    private:
        int _num;
};
class child:public father
{
    private:
        int _a;
};

int main()
{
    father A=father::GetObj();
    //father *fptr=father::GetObj();
   // child c;
    return 0;
}
