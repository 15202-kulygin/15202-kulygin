#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>

int main(int ac, char **av)
{
    int mas[100], i=0, j=0, n=0;
    int fp;
    char ch;
    char ss[256];
    if(ac!=2)
	return printf("Wrong number of parameters!\nUsage:  a.out file_name\n");
	
    
    if( ( fp = open( av[1], O_RDONLY, 0 ) ) == -1)
    {
	fprintf( stderr, "Error in opening file\n" );
	return 1;
    }
    
    while( read( fp, &ch, sizeof(char) ) )
    {
	if(ch == '\n')
	{
	    if (i==100)
	    {
		fprintf( stderr, "Too many strings!!\n" );
		return 2;
	    }
	    mas[i++] = j+1;
	}
	j++;
    }
    
    while(1)
    {
	if(!scanf("%d", &n))
	{
	    gets(ss);
	    fprintf( stderr, "Impossible string number!!\n" );
	    continue;
	}
	
	if( n > i || n < 0)
	{
	    fprintf( stderr, "Impossible string number!!\n" );
	    continue;
	}
	if(n==0)
	    return 0;
	if(n>1)
	    lseek( fp, mas[ n - 2 ], SEEK_SET );
	else
	    lseek( fp, 0, SEEK_SET );
					      
	for(j=(n>1)?(mas[n - 2]):0; j < mas[n - 1]; j++)
	{ 
	    read(fp, &ch, sizeof(char));
	    printf("%c", ch);
	}
    }
}
