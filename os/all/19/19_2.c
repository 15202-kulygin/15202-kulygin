#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <fnmatch.h>
#include <glob.h>

#include "header.h"
#include "util.h"

int errfunc(const char *epath, int eerrno) {
    fprintf(stderr, "Glob error\n");
    return 0;
}

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

void findEntry(char *searchMask) {
    glob_t results;

    int code = glob(searchMask, GLOB_NOCHECK, errfunc, &results);
    if(code != EXIT_SUCCESS) {
        printf("%s\n", searchMask);
    }

    int i = 0;
    while(results.gl_pathv[i]) {
        printf("%s\n", results.gl_pathv[i]);
        ++i;
    }

    globfree(&results);
}

int main() {
    size_t lengthMask = START_SIZE_MASK;
    char *searchMask = checkMalloc(sizeof(char) * lengthMask);
    if(searchMask == NULL) {
        return EXIT_FAILURE;
    }

    if(getSearchMask(&searchMask, &lengthMask) != EXIT_SUCCESS) {
        free(searchMask);
        return EXIT_FAILURE;
    }

    findEntry(searchMask);

    free(searchMask);
    return EXIT_SUCCESS;
}

