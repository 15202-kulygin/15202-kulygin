#include <iostream>

using namespace std;

class A 
{
	protected:
		int x_;
	public:
		void MethodOfClassA()
		{
			cout << "MethodOfClassA" << endl;
		}
		A(int x) {std::cout << "A ctor with x = " << x << endl;}
		A() {std::cout << "A ctor" << std::endl;} 
		~A() {std::cout << "A dtor" << std::endl;}
		A(const A&) {cout << "A copy" << endl;}
};
class B : public A
{
		A a;
		A a2;
		//const int i;
	public:
		B() : a(1) // member initialization list (список инициализации)
		{
			std::cout << "B ctor" << endl;
		}
		B(A aaa)
		{
			a = A(1); // временный объект
			a2 = aaa;
			cout << "B copy" << endl;
		}
		int getX() const
		{
			return A::x_;
		}
		~B() 
		{
			std::cout << "B dtor" << endl;
		}

};
	
int main ()
{
	A aaa;
	B b(aaa);
	b.MethodOfClassA();
	//cout << "X = " << 
}
