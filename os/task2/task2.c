#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


extern char *tzname[];

int main()
{
    //putenv("TZ=:America/Los_Angeles");
    putenv("TZ=:Brazil/East");
    
    time_t now;
    time( &now );
    printf("%s", ctime( &now ) ); // tzname is initialized when ctime() is called


    struct tm *sp;
    sp = localtime(&now); // tzname is initialized when localtime() is called
    printf("%d/%d/%02d %d:%02d %s\n",
        sp->tm_mon + 1, sp->tm_mday,
        sp->tm_year + 1900, sp->tm_hour, // tm_year is the number of years since 1900
        sp->tm_min, tzname[sp->tm_isdst]); //is daylight saving time
    exit(0);
}

