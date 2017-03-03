#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "header.h"
#include "util.h"

extern char **environ;

int execvpe(const char *file, char *const argv[], char *envp[]){
	char *path = getenv("PATH");
	if(path == NULL) {
		return EXEC_ERROR;
	}

	char dir[PATH_MAX] = {};
	int flag = FALSE;
	char *found = NULL;
	char *offset = path;
	while(flag != TRUE) {
		found = strstr(offset, ":");
		if(found == NULL) {
			return EXEC_ERROR;
		}
		strncpy(dir, offset, found - offset);
		dir[found - offset] = '\0';
		strcat(dir, "/");
		strcat(dir, file);
		
		int f = open(dir, O_RDONLY);
		if(f != OPEN_ERROR) {
			flag = TRUE;
		}

		offset = found + 1;
	}

    environ = envp;
    execv(dir, argv);
    perror("Error exec");
    return EXEC_ERROR;
}

void destroyEnv(char **env) {
    for(int i = 0; i < COUNT_STRINGS; ++i) {
        free(env[i]);
    }

    free(env);
}

int initEnv(char ***env) {
    *env = (char **)checkCalloc(COUNT_STRINGS, sizeof(char));
    if (*env == NULL){
        return CALLOC_ERROR;
    }

    for(int i = 0; i < COUNT_STRINGS; ++i){
        (*env)[i] = (char *)checkCalloc(LENGTH_STRING, sizeof(char));

        if ((*env)[i] == NULL){
            destroyEnv(*env);
            return CALLOC_ERROR;
        }
    }

    (*env)[0] = "FIRST=1";
    (*env)[1] = "VARIABLE=TEST";
    (*env)[2] = "NAME=kir55rus";
    (*env)[3] = NULL;

    return EXIT_SUCCESS;
}

int main(int argc,  char **argv){
	printf("%d\n", MAXPATHLEN);

    if(argc < 2) {
        fprintf(stderr, "Enter programm's name, which you want to execute\n");
        return EXIT_FAILURE;
    }

    char **env = NULL;
    if(initEnv(&env) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    execvpe(argv[1], &argv[1], env);

    return EXIT_FAILURE;
}

