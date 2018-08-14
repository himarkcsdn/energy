#pragma warning(disable:4996)
#include<iostream>
#include<cstring>

using namespace std;

//==================================================
//引用计数浅拷贝
//class String
//{
//public:
//	String(const char* pstr = "")
//		:_pstr(new char[strlen(pstr)+1])//为字符串开辟空间
//	{
//		if (0 == *pstr)  //如果字符串为空
//		{
//			*_pstr = '\0'; 
//		}
//		else   //字符串不为空
//		{
//			strcpy(_pstr, pstr);
//			cout << "String" << endl;
//		}
//		_count++;
//	}
//	//s2(s1)
//	String(const String& s) //拷贝构造函数
//	{
//		_pstr = s._pstr;
//		s._count++;
//		_count = s._count;
//		cout << "Stirng kaobei" << endl;
//	}
//
//	~String()
//	{
//		if (NULL == _pstr)
//		{
//			return;
//		}
//		else
//		{
//			cout << "~String" << endl;
//			if (--_count == 0)
//			{
//				delete[] _pstr;
//				_pstr = NULL;
//			}
//		}
//	}
//	String& operator=(String& s)  //运算符重载
//	{
//		if (_pstr != s._pstr)
//		{
//			cout << "operator=" << endl;
//			_pstr = s._pstr;
//			s._count = _count;
//			_count++;
//		}
//		return *this;
//	}
//
//private:
//
//	char* _pstr;
//	static int _count;
//};
//
//int String::_count = 0;
//
//void Fun1()
//{
//	String s1("abcd");
//	String s2(s1); 
//	String s3 = s2;  
//	String s4;
//	s4 = s3;
//
//}
//
//int main()
//{
//	Fun1();
//	system("pause");
//	return 0;
//}

//=====================================
//写时拷贝
//class String
//{
//public:
//	String(const char* pstr = "")
//		:_pstr(new char[strlen(pstr) + 4+1])//每次多开辟4个空间存放当前地址有几个对象
//	{
//		if (NULL == pstr)    //如果当前字符为空
//		{
//			(*(int*)_pstr) = 1; //将前4个字节用来计数
//			_pstr += 4;
//			*_pstr = '\0';
//		}
//		else   //字符串不为空
//		{
//			(*(int*)_pstr) = 1;//将前4个字节用来计数
//			_pstr += 4;//指针向后偏移4个字节
//			strcpy(_pstr, pstr); //将pstr内容拷贝到当前对象_pstr中
//			cout << "String" << endl;
//		}
//	}
//	//s2(s1)
//	String(const String& s) //拷贝构造函数
//		:_pstr(s._pstr)
//	{
//		++(*(int*)(_pstr - 4)); //向前偏移4个字节将计数加1
//		cout << "Stirng kaobei" << endl;
//	}
//
//	~String()
//	{
//		if (NULL == _pstr)
//		{
//			return;
//		}
//		else
//		{
//			cout << "~String" << endl;
//			if (--(*(int*)(_pstr-4)) == 0) //向前偏移4个字节判断计数是否为0，是0则是否
//			{
//				delete (_pstr-4);
//				_pstr = NULL;
//			}
//		}
//	}
//	String& operator=(String& s)  //运算符重载
//	{
//		if (_pstr != s._pstr)
//		{
//			if (--(*(int*)(_pstr - 4)) == 0) //释放旧空间
//			{
//				delete (_pstr - 4);
//				_pstr = NULL;
//			}
//			_pstr = s._pstr;  //指向新空间
//			++(*(int*)(_pstr - 4)); //计数加1
//		}
//		return *this;
//	}
//
//private:
//
//	char* _pstr;
//};
//
//
//void Fun1()
//{
//	String s1("abcd");
//	String s2(s1);
//	String s3 = s2;
//	String s4;
//	s4 = s3;
//
//}
//
//int main()
//{
//	Fun1();
//	system("pause");
//	return 0;
//}

//==================================
//深拷贝
//class String
//{
//public:
//	String(const char* pstr = "")
//		:_pstr(new char[strlen(pstr)+1]) //开辟空间
//	{
//		if (0 == *_pstr)      //如果是空内容
//		{
//			*_pstr = '\0';
//		}
//		else
//		{
//			strcpy(_pstr, pstr); //拷贝字符串
//		}
//	}
//	String(String& s)  //拷贝构造函数
//		:_pstr(NULL) //防止交换后temp指向随机空间，本函数调用结束导致内存泄漏致崩溃
//	{
//		String temp(s._pstr);//如果不给出临时变量，交换后s的值将为NULL
//		std::swap(_pstr, s._pstr);
//	}
//
//	String& operator=(const String &s)//赋值运算符重载
//	{
//		if (_pstr != s._pstr) //防止自己给自己赋值
//		{
//			String temp(s._pstr); //如果不给出临时变量交换后的值为NULL
//			std::swap(_pstr, temp._pstr);
//		}
//		return *this;
//	}
//	~String()
//	{
//		if (NULL == _pstr)
//		{
//			return;
//		}
//		else
//		{
//			delete[]_pstr;
//			_pstr = NULL;
//		}
//	}
//private:
//	char* _pstr;
//};
//
//void Funtest()
//{
//	String s1("abcd");
//	String s2(s1);
//	String s3 = s2;//调用拷贝构造函数(编译器会s2直接初始化s3)
//	String s4;//s4对象已经存在了
//	s4 = s3;//编译器会调用赋值运算符重载将s3的值赋给s4
//}
//int main()
//{
//	Funtest();
//	system("pause");
//	return 0;
//}


//===========================================
//浅拷贝（指针计数）
class String
{
public:
	String(const char* pstr = "")//构造函数
		:count(new int(0))
		, _pstr(new char[strlen(pstr)+1])
	{
		if (NULL == pstr)
		{
			*_pstr = '\0';
		}
		else
		{
			strcpy(_pstr, pstr);
		}
		*count = 1;
	}
	String(const String& s)//拷贝构造
		:count(s.count)
	{
		_pstr = (char*)s._pstr;
		count = s.count;
		(*count)++;
	}
	~String()//析构函数
	{
		if (NULL == _pstr)
		{
			return;
		}
		else
		{
			if (--(*count) == 0)
			{
				delete[]count;
				delete[]_pstr;
				_pstr = NULL;
				count = NULL;
			}
		}
	}
	String& operator=(String& s)//赋值运算符重载
	{
		if (_pstr != s._pstr)
		{
			_pstr = s._pstr;
			count = s.count;
			(*count)++;
		}
		return *this;
	}
private:
	int* count;
	char* _pstr;
};


void Funtest()
{
	String s1("abcd");
	String s2(s1);
	String s3 = s2;//调用拷贝构造函数(编译器会s2直接初始化s3)
	String s4;//s4对象已经存在了
	s4 = s3;//编译器会调用赋值运算符重载将s3的值赋给s4
}
int main()
{
	Funtest();
	system("pause");
	return 0;
}