#pragma once
#include "Alloc.h"

template<class T>
struct  ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
};

template<class T, class Ref, class Ptr>
struct __ListIterator
{
	typedef ListNode<T> Node;
	typedef __ListIterator<T, T&, T*> Self;
	Node* _node;

	__ListIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Self& operator++()
	{
		_node = _node->_next;

		return *this;
	}

	bool operator != (const Self& s)
	{
		return _node != s._node;
	}
};

template<class T, class Alloc = alloc>
class List
{
	typedef ListNode<T> Node;
	typedef SimpleAlloc<Node, Alloc> ListNodeAlloctor;
public:
	typedef __ListIterator<T, T&, T*> Iterator;

	Node* BuyNode(const T& x)
	{
		Node* node = ListNodeAlloctor::Allocate();
		node->_next = NULL;
		node->_prev = NULL;
		//node->_data = x;
		new(&node->_data)T(x);

		return node;
	}
	
	void DestoryNode(Node* node)
	{
		node->_data.~T();
		ListNodeAlloctor::Deallocate(node);
	}

	List()
		:_head(BuyNode(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		Clear();
		DestoryNode(_head);
		_head = NULL;
	}

	void Clear()
	{
		Iterator it = Begin();
		while (it != End())
		{
			Iterator cur = it;
			++it;
			DestoryNode(cur._node);
		}

		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	void PushBack(const T& x)
	{
		Insert(End(), x);
	}

	void Insert(Iterator pos, const T& x)
	{
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newnode = BuyNode(x);

		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = cur;
		cur->_prev = newnode;
	}

private:
	Node* _head;
};

void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);

	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		std::cout << *it << " ";
		++it;
	}

	std::cout << std::endl;
}

#include <time.h>

template<class Container>
void TestContainer(Container& con)
{
	for (size_t i = 0; i < 1000; ++i)
	{
		con.PushBack(i);
	}
	con.Clear();
}

void TestOP()
{
	const size_t N = 100000;

	size_t begin1 = clock();
	List<int, __MallocAllocTemplate<0>> l1;
	for (size_t i = 0; i < N; ++i)
	{
		TestContainer(l1);
	}
	size_t end1 = clock();

	size_t begin2 = clock();
	List<int, __DefaultAllocTemplate<false, 0>> l2;
	for (size_t i = 0; i < N; ++i)
	{
		TestContainer(l2);
	}
	size_t end2 = clock();

	cout << end1 - begin1 << endl;
	cout << end2 - begin2 << endl;
}