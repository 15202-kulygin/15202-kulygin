#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    char options[] = "i";  /* valid options */
    int c, invalid = 0, dflg = 0, fflg = 0, gflg = 0;
    printf("argc equals %d\n", argc);
    while ((c = getopt(argc, argv, options)) != EOF) 
    {
    	switch (c) 
    	{
    		case 'd':
       			dflg++;
       			break;
    		case 'f':
       			fflg++;
       			f_ptr = optarg;
       			break;
    		case 'g':
       			gflg++;
       			g_ptr = optarg;
       			break;
    		case '?':
       			printf("invalid option is %c\n", optopt);
       			invalid++;
    	}
	}
  	
   	printf("invalid equals %d\n", invalid);
  	printf("optind equals %d\n", optind);
  	if(optind < argc)
   	{
   		printf("next parameter = %s\n", argv[optind]);
   	}
}