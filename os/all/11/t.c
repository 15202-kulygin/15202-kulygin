#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"
#include "util.h"


extern char **environ;

int execvpe(const char *file, char *const argv[], char *envp[]){
	char *path = getenv("PATH");
	printf("%s\n", path);

	// size_t maxLen = strlen(path);
	// char *dir = (char *)checkCalloc(maxLen, sizeof(char));
	// if(dir == NULL) {
	// 	return EXEC_ERROR;
	// }

	printf("%d\n", PATH_MAX);

    environ = envp;
    execvp(file, argv);
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
	// for(char **p = environ; *p != 0; ++p) {
	// 	printf("%s\n", *p);
	// }

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

