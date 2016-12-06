#include <iostream>

using namespace std;

class A
{
    const int i = 100;
    const int j = i;
public:
    A() : i(42)
    {
        cout << j << endl;
    }
};

int main()
{
    int a = 20;
    while (10 <-- a){
        printf("%d\n", a);
    }
    return 0;
}
