<<<<<<< HEAD
We are excited to introduce our latest project from Holberton School, where we developed a custom simple shell in C. This project demonstrates our growing proficiency in systems programming by strictly using a limited set of standard library functions.

### Allowed Functions and System Calls:
- access
- chdir
- close
- closedir
- execve
- exit
- _exit
- fflush
- fork
- free
- getcwd
- getline
- getpid
- isatty
- kill
- malloc
- open
- opendir
- perror
- read
- readdir
- signal
- stat (__xstat)
- lstat (__lxstat)
- fstat (__fxstat)
- strtok
- wait
- waitpid
- wait3
- wait4
- write

### Project Requirements:
- Allowed editors: vi, vim, emacs
- The code will be compiled on Ubuntu 20.04 LTS using gcc with the following options: -Wall -Werror -Wextra -pedantic -std=gnu89.
- All files must end with a new line.
- A README.md file is required at the root of the project.
- The code should follow the Betty style and will be verified using betty-style.pl and betty-doc.pl.
- Ensure that the shell has no memory leaks.
- Limit the number of functions per file to 5.
- Header files should be correctly include-guarded.
- System calls should be used only when necessary.

### Project Deliverables:
- Write a README.md file.
- Create a man page for your shell.
- Include an AUTHORS file with the names of all contributors.
- Ensure the code passes Betty checks.
- Implement a UNIX command-line interpreter with the following features:
  - Display a prompt and wait for the user to enter a command. Each command line should end with a new line.
  - The prompt should reappear after each command is executed.
  - Handle basic command lines (without semicolons, pipes, or other advanced features).
  - The command line will contain only one word (no arguments passed to programs).
  - If the executable is not found, print an error message and show the prompt again.
  - Handle errors appropriately.
  - Implement handling for the "end of file" (Ctrl+D) condition.
  - Handle command lines with arguments.
  - Implement the PATH environment variable to locate executables.
  - Avoid calling fork if the command doesn’t exist.
  - Implement the exit built-in command to exit the shell (Usage: exit).
  - Implement the env built-in command to display the current environment variables.

We have diligently followed these requirements, ensuring that our project is well-structured, clean, and error-free, meeting all the criteria set out while showcasing our growing programming skills.
=======
rania 
>>>>>>> refs/remotes/origin/main
