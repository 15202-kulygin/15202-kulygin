#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <ulimit.h>




int main(int argc, char *argv[])
{
	char options[] = "ispuU:cC:dvV:";  
	int c, invalid = 0;
	long int limit;
	struct rlimit rlimit_struct;
	int check;
	while ((c = getopt(argc, argv, options)) != EOF) 
	{
		switch (c) 
		{
			case 'i':
				printf("Real UID : %d\n", getuid());
				printf("Effective UID : %d\n", geteuid());
				printf("Real GID      : %d\n", getgid());
    			printf("Effective GID : %d\n\n", getegid());
				break;
			case 's':
				setpgrp();
				break;
			case 'p':
				printf("Process ID : %d\n", getpid());
				printf("Parent process ID : %d\n", getppid());
				printf("Process group ID : %d\n\n", getpgid(0));
				break;
			case 'u':
				printf("ulimit = %ld\n", ulimit(UL_GETFSIZE));
        		break;
		    case 'U':
				limit = atol(optarg);
				if (0 == limit)
				{
					printf("Wrong ulimit argument - it must be a non-zero integer value\n");
					break;
				}
				// printf("qwe %ld\n", limit);
				check = ulimit(UL_SETFSIZE, limit);
	        	if(-1 == check)
	    		    printf("Error while changing ulimit\n");
	    		break;
		    case 'c':
	    		getrlimit(RLIMIT_CORE, &rlimit_struct);
	    		printf("Core size = %ld\n", rlimit_struct.rlim_cur);
	    		break;
		    case 'C':
	    		getrlimit(RLIMIT_CORE, &rlimit_struct);
	    		if (0 == atol(optarg))
	    		{
	    			printf("Wrong core-file size argument - it must be a non-zero integer value\n");
	    			break;
	    		}
			    rlimit_struct.rlim_cur = atol(optarg);
			    if (setrlimit(RLIMIT_CORE, &rlimit_struct) == -1)
					printf("Error while changing core-file size\n");
			    break;
	    	case 'd':
	        	printf("Current work directory is: %s\n", getcwd(0,255));
	    	    break;
		    case 'v':
				system("printenv");
	        	break;
	    	case 'V':
	    		putenv(optarg);
        		break;
			case '?':
				printf("Invalid option : %c\n\n", optopt);
				invalid++;
		}
	}
  
	printf("\n\n\nargc equals %d\n", argc);
	printf("invalid equals %d\n", invalid);
	printf("optind equals %d\n", optind);
	// if(optind < argc)
	// {
	// 	printf("next parameter = %s\n", argv[optind]);
	// }
}