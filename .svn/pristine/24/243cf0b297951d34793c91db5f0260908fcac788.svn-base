#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class String {
	private:
		char * data;
	public:	
		String()
		{	
			data = new char[10];
			for (int i = 0; i < 10; ++i)
			{ 
				data[i] = ' '; //тут пробел
			}
		}
		String(const char * p)
		{
			data = new char [strlen(p)];
			strcpy(data, p);
		}
		~String()
		{
			delete [] data;
		}
		operator const char * () const
		{
			return (const char *) data;
		}
		String& operator = (String &orig) 
		{
    		delete [] data;
    		int len = strlen(orig);
		    data = new char [len];
		    for (int i = 0; i < len; ++i)
		    {
		    	data[i] = orig.data[i];
		    }
    		return *this;
		}
		void print()
		{
			for (int i = 0; i < strlen(data); ++i)
			{
				printf("%c", data[i]);
			}
			printf("\n\n");
		}
};

int main ()
{
	String a("abc");
	String b("cde");
	String c("qqq");
	a.print();
	b.print();
	c.print();
	c = a;
	c.print();

}