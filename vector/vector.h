#pragma once
#include<stdio.h>
#include<iostream>
#include<assert.h>
#include<string.h>

using namespace std;

typedef int Datatype;

class Vector
{
public:
    Vector()
        :_first(NULL)
         ,_finish(NULL)
         ,_end(NULL)
        {}
    Vector(const Vector& v)
    {
        if(v.Size()>0)
        {
            //开辟元数据所占大小的空间，将数据拷贝过去
            _first=new Datatype[v.Size()];
            memcpy(_first,v._first,sizeof(Datatype)*v.Size());
            if(_first)
            {
                _finish=_first+v.Size();
                _end=_first+v.Size();
            }
            else
            {
                _first=_finish=_end=NULL;
            }
        }
    }

    Vector& operator=(Vector& v)
    {
        if(this!=&v)
        {
            //传统写法
            //Datatype* tmp=new Datatype[v.Size()];
            //memcpy(tmp,_first,sizeof(Datatype)*v.Size());
            //delete[]_first;
            //_first=tmp;
            //_finish=_first+v.Size();
            //_end=_first+v.Size();

            //现代写法
            swap(_first,v._first);
            swap(_finish,v._finish);
            swap(_end,v._end);
        }
        return *this;
    }

    ~Vector()
    {
        delete[] _first;
        _first=_finish=_end=NULL;
    }

    void Print()
    {
        Datatype* cur=_first;
        while(cur!=_finish)
        {
            cout<<*cur<<" ";
            ++cur;
        }
        cout<<endl;
    }

    size_t Size() const ;
    size_t Capacity() const;
    void Expand(size_t n);
    void PushBack(Datatype x);
    void Reserve(size_t n);
    void PopBack();
    void Insert(size_t pos, Datatype x);
    void Erase(size_t pos);
    size_t Find(Datatype x);

private:
    Datatype* _first;
    Datatype* _finish;
    Datatype* _end;

};

size_t Vector::Size() const 
{
    return _finish-_first;
}
size_t Vector::Capacity() const
{
    return _end-_first;
}
void Vector::Expand(size_t n)
{
    if(n>Capacity())
    {
        size_t size=Size();
        Datatype* tmp=new Datatype[n];
        memcpy(tmp,_first,sizeof(Datatype)*size);
        delete[]_first;
        _first=tmp;
        _finish=_first+size;
        _end=_first+n;
    }
}
void Vector::PushBack(Datatype x)
{
//    if(_finish==_end)
//    {
//        if(Capacity()==0)
//        {
//            Expand(3);
//        }
//        else
//        {
//            Expand(Capacity()*2);
//        }
//    }
//    *_finish=x;
//    ++_finish;
    Insert(Size(),x);
}
void Vector::Reserve(size_t n)
{
    if(n>Capacity())
    {
        Expand(n);
    }
}
void Vector::PopBack()
{
    assert(_finish>_first);
    --_finish;
}
void Vector::Insert(size_t pos, Datatype x)
{
    assert(pos<=Size());
    if(_finish==_end)
    {
        if(Capacity()==0)
        {
            Expand(3);
        }
        else
        {
            Expand(Capacity()*2);
        }
    }
    int end=Size()-1;
    while(end>=(int)pos)
    {
        _first[end+1]=_first[end];
        --end;
    }
    _first[pos]=x;
    ++_finish;
}

void Vector::Erase(size_t pos)
{
    assert(pos<Size());
    size_t cur=pos;
    while(cur<Size()-1)
    {
        _first[cur]=_first[cur+1];
        ++cur;
    }
    --_finish;
}
size_t Vector::Find(Datatype x)
{
    Datatype* cur=_first;
    while(cur!=_finish)
    {
        if(*cur==x)
        {
            return cur-_first;
        }
        ++cur;
    }
    return -1;
}















