#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <fnmatch.h>

#include "header.h"
#include "util.h"

int getSearchMask(char **searchMask, size_t *lengthMask) {
    printf("Please, enter mask (? - one char, * - any char count): ");

    int charCode;
    size_t pos = 0;
    while((charCode = getc(stdin)) != EOF && (char)charCode !=  '\n') {
        char c = (char)charCode;
        if(addChar(searchMask, lengthMask, &pos, c) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    }

    if(lengthMask == 0) {
        fprintf(stderr, "Empty mask\n");
        return EXIT_FAILURE;
    }

    if(addChar(searchMask, lengthMask, &pos, '\0') != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void findEntry(char *searchMask, DIR *currentDir) {
    int countEntry = 0;
    struct dirent *entryInfo;
    while((entryInfo = readdir(currentDir)) != NULL) {
int code;
        if((code = fnmatch(searchMask, entryInfo->d_name, FNM_PATHNAME)) == 0) {
            printf("%s\n", entryInfo->d_name);
            ++countEntry;
        }
printf("%d - %d\n", code, FNM_NOMATCH);
    }
perror("1");
    if(!countEntry) {
        printf("%s\n", searchMask);
    }
}

int main() {
    DIR *currentDir = opendir(".");
    if(currentDir == NULL) {
        perror("Can't open directory");
    }

    size_t lengthMask = START_SIZE_MASK;
    char *searchMask = checkMalloc(sizeof(char) * lengthMask);
    if(searchMask == NULL) {
        closedir(currentDir);
        return EXIT_FAILURE;
    }

    if(getSearchMask(&searchMask, &lengthMask) != EXIT_SUCCESS) {
        free(searchMask);
        return EXIT_FAILURE;
    }

    findEntry(searchMask, currentDir);

    free(searchMask);
    closedir(currentDir);
    return EXIT_SUCCESS;
}


//struct __dirstream
//32   {
//33     int fd;                     /* File descriptor.  */
//34
//35     __libc_lock_define (, lock) /* Mutex lock for this structure.  */
//36
//37     size_t allocation;          /* Space allocated for the block.  */
//38     size_t size;                /* Total valid data in the block.  */
//39     size_t offset;              /* Current offset into the block.  */
//40
//41     off_t filepos;              /* Position of next entry to read.  */
//42
//43     /* Directory block.  */
//44     char data[0] __attribute__ ((aligned (__alignof__ (void*))));
//45   };

//struct dirent {
//    ino_t          d_ino;       /* inode number */
//    off_t          d_off;       /* offset to the next dirent */
//    unsigned short d_reclen;    /* length of this record */
//    unsigned char  d_type;      /* type of file; not supported
//                                 by all file system types */
//    char           d_name[256]; /* filename */
//};

