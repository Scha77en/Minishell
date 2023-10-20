#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../includes/minishell.h"

typedef struct Node {
    char* command;
    struct Node* next;
} Node;

void executeCommands(Node* head) {
    int pipefd[2];
    int prev_pipe = 0; // file descriptor of the previous pipe
    char *const args[] = { "/home/Schatten/.brew/bin/clear", NULL };

    // Set the TERM environment variable
    char *const env[] = { "TERM=xterm-256color", NULL };

    execve("/home/Schatten/.brew/bin/clear", args, env);

    // execve("/home/Schatten/.brew/bin/clear", NULL, NULL);
    exit(0);
    while (head != NULL) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // child process
            dup2(prev_pipe, 0); // set input from previous pipe

            if (head->next != NULL) {
                dup2(pipefd[1], 1); // set output to current pipe
            }

            close(pipefd[0]); // close unused read end
            close(pipefd[1]); // close unused write end

            execlp(head->command, head->command, NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else { // parent process
            wait(NULL);

            close(prev_pipe); // close previous pipe

            prev_pipe = pipefd[0]; // update previous pipe to current pipe
            close(pipefd[1]); // close write end of current pipe

            head = head->next;
        }
    }

    close(prev_pipe); // close the last remaining pipe
}

int main() {
    Node* head = NULL;
    // Add your commands to the linked list
    // Example: ls | cat Makefile | wc -l
    Node* node1 = (Node*)malloc(sizeof(Node));
    node1->command = "clear";
    // Node* node2 = (Node*)malloc(sizeof(Node));
    // node2->command = "cat";
    // Node* node3 = (Node*)malloc(sizeof(Node));
    // node3->command = "wc";
    node1->next = NULL;

    head = node1;
    // node1->next = node2;
    // node2->next = node3;

    executeCommands(head);

    return 0;
}