#include <iostream>
#include <vector>



struct A {
	

	A() {
		std::cout << "A ctor " << std::endl;
	}
	~A() 
	{
		std::cout << "A dtor " << std::endl;
	}
	A& operator=(const A&)
	{
		std::cout << "A assign" << std::endl;
		return *this;
	}
	A(const A&)
	{
		std::cout << "A copy " << std::endl;
	}


};

std::vector<int> returnVector() // нельзя по ссылке, т к временный объект удалится и ссылка повиснет
{
	std::vector<int> v = {1, 2, 3};
	return v;
}


A returnA()
{
	A a;
	return a;
}

template<class T> // плохо, т.к. имеем 3 присваивания --- никакой оптимизации
void swap (T &t1, T &t2)
{
	T tmp(t1);
	t1 = t2;
	t2 = tmp;
}



int main()
{
	// create temporary object
	//copy constructor (linear copying O(N))
	std::vector<int> v = returnVector();

	//assignment
	std::vector<int> v2;
	v2 = returnVector();


/*
	//checking whats going on
	A a = returnA(); // ON:Y ONE constructor is working --- why not 2?
*/

	// how to optimize??
	//1. use swap (empty vector swap with filled)
	// std::swap(v2, returnVector()); -- нельзя, тк returnVector() не lvalue, принимает ссылку, а ссылку нельзя инициализировать временным объектом
	//v2.swap(returnVector()); то же самое, нельзя
	// ПОПУЛЯРНЫЙ ВОПРОС
	// как оптимизировать? -- использовать swap в контейнере
	returnVector().swap(v2);
	A a = returnA();


	// чтобы не "приседать" со всеми swapam'и ---- ввели move semantic и rvalue-ссылки
	// не будем же писать метод swap каждому объекту
}