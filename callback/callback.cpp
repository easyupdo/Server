// callback.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
class A
{
public:
	 void pri();
	void fun(void(*hand)());
private:
	A * per;
	int num;
};


void pri()
{
	cout << "This is from fun call back Fun" << endl;
}

void A::fun(void (*hand)())
{
	hand();
}
template<class T1,class T2>
class MyClass
{
public:
	MyClass();
	void F(T1 a,T2 b);
	~MyClass();

private:

};

template <class T1, class T2>
MyClass<T1,T2>::MyClass()
{
}
template <class T1, class T2>
MyClass<T1, T2>::~MyClass()
{
}

template <class T1, class T2>
void MyClass<T1, T2>::F(T1 a, T2 b)
{
	cout << a << endl;
	cout << b << endl;
}

template<typename T1,typename T2>
void F2(T1 a,T2 b)
{
	cout << a << endl;
	cout << b << endl;
	cout << "Fuck You" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a = 1;
	
	
	//A ta;
	//ta.fun(pri);
	//void(*p)();
	A tb;
	tb.fun(pri);
	//
	/*

	MyClass<int,float> Tb;
	Tb.F(1,2.12);
	F2(10,2.125);
	*/
	getchar();
	
	return 0;
}

