How to compile the project:
Type 'make'

Example of how to run the project:
./oss -n 3 -s 2 -t 5

Description:
This project implements a parent process (oss) that manages multiple child processes (user).
The oss process can control how many total children to launch, how many can run simultaneously,
and how many iterations each child should perform.

The user process outputs its PID, parent PID, and iteration number before and after each sleep cycle.
