#include <iostream>

using namespace std;

class Foo {
 public:
  Foo(int j) { i = new int[j]; }
  ~Foo()
  {
    cout << "Foo destr" << endl;
    delete [] i; 
  }
  Foo & operator=(const Foo &)
  {
    cout << "operator=" << endl;
    //delete [] i;
    return *this;
  }

 private:
  int* i;
};

class Bar: public Foo {
 public:
  Bar(int j) : Foo(j) { i = new char[j]; } // member initialization list
  ~Bar() {    
    cout << "Bar destr" << endl;
    delete [] i; }

 private:
  char* i;
};

int main() {
  Foo* f = new Foo(100);
  Foo* b = new Bar(200);
  *f = *b;
  delete f;
  delete b;
}

// ^^^^ правильно