#pragma once
#include<iostream>
using namespace std;

//设计简易内存池，固定大小的内存池，也称作对象池
template<calss T>
class ObjPool
{
    //定义一个内部类，保存每个大块内存的结点
    struct Node
    {
        Node* _memory;//指向大块内存的指针
        size_t _n;    //当前结点里面的对象个数
        Node* _next;  //指向下一个大块内存的结点
    }

    Node(size_t nobj)
    {
        _n=nobj;
        _memory=(Node*)::operator new(_n *Get)
    }
}
