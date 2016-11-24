#include <iostream>
#include <vector>

//MOVE SEMANTIC

//RVO(rvalue optimization)

//trying to call our move constructors

//std::move -- не перемещение, а, по сути, каст выражения к rvalue reference

struct A {
	

	A() : someResourceExpensiveToCopy(new int(1)){
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

	//rvalue reference -- can be initialized with temporary objects
	//move constructor
	A(A&& arg)
	{
		// example of real-world move constr
		someResourceExpensiveToCopy = arg.someResourceExpensiveToCopy;
		arg.someResourceExpensiveToCopy = nullptr;
		//the same as std::swap(someResourceExpensiveToCopy, arg.someResourceExpensiveToCopy);
		std::cout << "A move copy " << std::endl;
	}
	//move operator
	A& operator=(const A&&)
	{
		std::cout << "A move assign" << std::endl;
		return *this;
	}

private:
	int * someResourceExpensiveToCopy = nullptr;


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



	A a1, a2;
	std::cout << "\nSTD::SWAP" << std::endl;
	std::swap(a1, a2); 
	std::cout << "\n\nHANDMADE SWAP" << std::endl;
	::swap(a1,a2); // делает копию и присваивает -- это плохо





	
}


/*
//perfect swap
template<class T> // плохо, т.к. имеем 3 присваивания --- никакой оптимизации
void swap (T &t1, T &t2)
{
	T tmp(std::move(t1));
	t1 = std::move(t2);
	t2 = std::move(tmp);
}
*/