#include <iostream>

// How to call a pure virtual function??
//-constructor

//put a pure virtual function into another non-virt func and call it from constructor
//--because in constructor the virtual-func table is not completed ---> functions are not virtual

struct A {

	A()
	{
		z();
	}


	virtual void f() = 0;
	void z () {
		f();
	};
};


struct B : public A{
	void f() override
	{
		std::cout << "Derived f()" << std::endl;
	}
};

/*void x(A * a)
{
	a->f(); // viryual behaviour
}*/

int main()
{
	//A a;
	B b;
}