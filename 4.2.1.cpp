#include <future>
#include <iostream>

#include<Windows.h>

using namespace std;

//int find_the_answer_to_ltuae() { cout << "find_the_answer_to_ltuae" << endl; Sleep(10000); return 666; }
//void do_other_stuff() { cout << "do_other_stuff" << endl; }
//int main()
//{
//	std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
//	Sleep(10);
//	do_other_stuff();
//	std::cout << "The answer is " << the_answer.get() << std::endl;
//
//	return 0;
//}


#include <string>
#include <future>
struct X
{
	void foo(int, std::string const&) { cout << "foo" << endl; }
	std::string bar(std::string const& s) { cout << "bar" << endl; return s; }
};
X x;
//auto f1 = std::async(&X::foo, &x, 42, "hello");  // 调用p->foo(42, "hello")，p是指向x的指针
//auto f2 = std::async(&X::bar, x, "goodbye");  // 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本
struct Y
{
	double operator()(double d) { cout << "Y::operator()" << endl; return d; }
};
Y y;
//auto f3 = std::async(Y(), 3.141);  // 调用tmpy(3.141)，tmpy通过Y的移动构造函数得到
//auto f4 = std::async(std::ref(y), 2.718);  // 调用y(2.718)


//std::async(baz, std::ref(x));  // 调用baz(x)
//std::async(baz, 2);
class move_only
{
public:
	move_only() { cout << "move_only()" << endl; }
	move_only(move_only&&) { cout << "move_only(move_only&&)" << endl; }
	move_only(move_only const&) = delete;
		move_only& operator=(move_only&&) { cout << "operator=(move_only&&)" << endl; return *this; }
	move_only& operator=(move_only const&) = delete;

	void operator()() { cout << "move_only::operator()" << endl; }
};

int tt(int &i) { return 2; }
X baz(X& i) { cout << "baz" << endl; return i; }

int main()
{
	//f1.get();
	//f2.get();
	//f3.get();
	//f4.get();
	auto f5 = std::async(move_only());  // 调用tmp()，tmp是通过std::move(move_only())构造得到
	f5.get();

	int i = 2;
	tt(i);
	auto ff = std::async(std::launch::deferred, tt, std::ref(i));

	//auto f6 = std::async(std::launch::async, Y(), 1.2);  // 在新线程上执行
	//auto f7 = std::async(std::launch::deferred, baz, std::ref(x));  // 在wait()或get()调用时执行
	auto f8 = std::async(
		std::launch::deferred | std::launch::async,
		baz, std::ref(x));  // 实现选择执行方式
	Sleep(3000);
	//auto f9 = std::async(baz, std::ref(x));
	//f7.wait();  //  调用延迟函数

	return 0;
}
