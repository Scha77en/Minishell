# Minishell

### ***Note***

*In order to view the `excalidraw` files, download the `excalidraw extension` on your code editor.*

## Starting the Project.

Starting the minishell project in the 42 curriculum involves creating a simplified shell that can execute basic commands, handle built-in functions, and manage environment variables. Here are the general steps to get started:

Read the Project Instructions:
Carefully read and understand the project instructions provided by your 42 school. Make sure you understand the requirements and what is expected from your minishell implementation.

Set Up Your Development Environment:
Ensure you have the necessary tools and dependencies installed on your computer to work on the project. The 42 school typically provides a specific environment with the required libraries and configurations. If you are working on your personal machine, ensure you have a suitable development environment, a text editor (like Vim or VSCode), and a compiler (like GCC).

Plan Your Project Structure:
Before diving into coding, take some time to plan your project structure and design. Break down the requirements into smaller tasks and consider how you will implement them in your code. Plan the data structures you'll use and the overall flow of your shell.

Handle Command Line Input:
Your minishell needs to read and process user input. Implement a loop that will continuously read user commands from the standard input.

Parse User Input:
Create a parser to tokenize the user input into individual command arguments and handle special characters like pipes (|) or redirection (<, >).

Implement Built-in Commands:
Handle built-in commands like echo, cd, pwd, export, unset, and exit. These commands should be executed directly by your minishell and not by creating child processes.

Execute External Commands:
For non-built-in commands, you need to execute external programs. Implement a function to spawn child processes using the fork() and execve() system calls.

Manage Environment Variables:
Your minishell should allow users to set, unset, and list environment variables. Implement functions to manage the environment variable list.

Handle Redirection and Pipes:
Add support for file redirection (<, >) and pipes (|) to allow users to redirect input/output and create pipelines between commands.

Implement Signal Handling:
Handle signals such as CTRL+C (SIGINT) and CTRL+\ (SIGQUIT) to exit the minishell or handle them according to the project requirements.

Test Thoroughly:
Test your minishell thoroughly with various command combinations and edge cases to ensure it behaves correctly and handles errors gracefully.

Submit and Discuss:
Once you've completed the project, submit it for evaluation. Prepare yourself to discuss your code and design choices during the evaluation.

Remember to refer to the official 42 project instructions and ask for guidance from your peers or instructors if you encounter any challenges during the project. Good luck!