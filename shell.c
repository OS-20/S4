#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void searchFile(char *option, char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("Error opening file"); return; }

    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *ptr = line;
        while ((ptr = strstr(ptr, pattern)) != NULL) {
            count++;
            if (option[0] == 'a') printf("%s", line);
            ptr += strlen(pattern);
        }
    }
    if (option[0] == 'c') printf("Total occurrences: %d\n", count);
    fclose(fp);
}

int main() {
    char input[200], *args[10];

    while (1) {
        printf("myshell$ ");
        if (!fgets(input, sizeof(input), stdin)) break;
        if (!(args[0] = strtok(input, " \t\n"))) continue;

        int i = 0;
        while ((args[++i] = strtok(NULL, " \t\n")));

        if (!strcmp(args[0], "exit")) break;

        else if (!strcmp(args[0], "search")) {
            if (args[1] && args[2] && args[3])
                searchFile(args[1], args[2], args[3]);
            else
                printf("Usage: search a|c filename pattern\n");
        }

        else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                perror("Command not found");
                exit(1);
            } else wait(NULL);
        }
    }

    return 0;
}
