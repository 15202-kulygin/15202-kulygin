#ifndef ARR_H
#define ARR_H

class Arr {
	private:
		int * arr;
		int capacity;
		int size;
	public:	
		Arr();
		Arr(int _capacity, int value);
		~Arr(); //destructor
		void add (int elem);
		void insert (int elem);
		void printArr();
		void setArr(int value, int ind);
		int get (int ind);
		int operator [] (int ind);
		Arr& operator = (Arr &curArr);
};

#endif