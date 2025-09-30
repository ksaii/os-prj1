Group Member Names:
- Javier Rios
- Abram Ortiz

Files in Dir:
-shell.c:Main source code for the shell program.
-Makefile: Build automation file for compiling the program.
-README.txt: This documentation file.


To compile the program:
nav to the dir using cd and then run the commmand:
make

To clean compiled files:

make clean


Then to run the shell use:

./shell
and then you can run our built in cmds 

exit: terminates the shell

cd <path>: changes the working  dir  to <path>

showpid:shows last 5 child process ids


Challenges:

- External command testing: testing the external commands someetimes didn't work so we had to troubleshoot around this which took a little bit of time .
-  PID Logic Implementation: Managing the PID to store the last 5 IDs was a little more difficult but I think that tokenizing the logic was the hardest.
- Tokenizing Logic: This was hard as we had to parse user input into  tokens but it wasn't too bad and overall the project wasn't too difficult and it was interesting.

Our Main Sources:

- Lecture Slides
- Operating System Concepts the ZyBook
- Official Linux Command Documentation

