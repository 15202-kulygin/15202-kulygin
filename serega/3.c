#include <stdio.h>
#include <string.h>
int funkciya(char stroka[100])
{
	int return_code = 1; // 1 if palindrome
	int length=strlen(stroka) - 1;
	//printf("Length %d\n", length);
	for(int i=0;i<length/2;i++)
	{
		if(stroka[i]!=stroka[length-i-1])
		{
			return_code = 0;
			break;
		}
	}
	return return_code;
}

int main()

{
	char stroka[100];
	printf("vvedite stroky\n");
	fgets(stroka,100,stdin);
	if (1 == funkciya(stroka))
	{
		printf("palindrome\n");
	}
	else
	{
		printf("ne palindrome\n");
	}

}
