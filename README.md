This is a read me file for the project   C - Simple Shell

🐚 Simple Shell command line interpreter
Table of Contents

Description
Features
Installation
Allowed functions
Requirements
Contributing
Author
License
📝 Description
The Simple UNIX Command Interpreter is a command-line interface for UNIX-like operating systems. It allows users to interact with the system by entering commands at a prompt. The interpreter supports basic commands such as ls, cd, pwd, and exit, making it easy to navigate the file system and perform common tasks. With its simple and intuitive interface, the Simple UNIX Command Interpreter is a great tool for anyone looking to work with UNIX-like systems.

⭐️ Features
The program displays a prompt and waits for the user to enter a command.
Once a command is entered and the user presses the ENTER key, the command is executed and the prompt is displayed again.
The user can exit the program by entering exit, which will return a status of 0.
The program can also be stopped by pressing Ctrl+D.
The program can handle command lines with arguments and pathways.
The program supports common shell commands such as ls, grep, find, pwd, rm, cp, mv, exit, env, and history.
If an executable cannot be found, an error message is displayed and the prompt is shown again.
💾 Installation
To install the command interpreter, simply clone this repository and run the make command:

bash
Copy code
git clone https://github.com/yourusername/simple_shell.git
cd simple_shell
📚 Allowed functions
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)
🔍 Requirements
General
Allowed editors: vi, vim, emacs
All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All your files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code

should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Your shell should not have any memory leaks
No more than 5 functions per file
All your header files should be include guarded
Use system calls only when you need to

🤝 Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue.

✍️ Author
Ismael Abdulahi
Dinar Tsegazeab

📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
