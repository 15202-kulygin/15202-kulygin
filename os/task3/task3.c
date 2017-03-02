#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char ** argv)
{
	if (2 != argc)
	{

	}

	int user_real_id = getuid();
	int user_effective_id = geteuid();
	printf("Real user id : %d\nEffective user id : %d\n", user_real_id, user_effective_id);

	//FILE * input = fopen(argv[1]);
	
}