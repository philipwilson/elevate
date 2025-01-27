#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "pathfinder.h"

int exec_elevated(char *path, char **args, char **environment) {
    pid_t pid = fork();
    if (pid == 0) { // child process
      if (setuid(0) == -1) {
	perror("Error: setuid failed");
	return 1;
      }
      if (execve(path, args, environment) == -1) {
        perror("Error: execve failed");
        return 1;
      }
    }
    else { // parent process
      int status;
      waitpid(pid, &status, 0);
      return (WIFEXITED(status)) ? WEXITSTATUS(status) : -1;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *path = pathfinder(argv[1]);
    char **args = &argv[1];      
    extern char **environ;

    if (path == NULL) {
      fprintf(stderr, "%s: can\'t find %s\n", argv[0], argv[1]);
      exit(EXIT_FAILURE);
    }

    exit(exec_elevated(path, args, environ));
}
