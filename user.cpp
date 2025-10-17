#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <number_of_iterations>" << endl;
        return EXIT_FAILURE;
    }
    
    int iterations = atoi(argv[1]);
    pid_t myPid = getpid();
    pid_t parentPid = getppid();
    
    for (int i = 1; i <= iterations; i++) {
        cout << "USER PID:" << myPid << " PPID:" << parentPid 
             << " Iteration:" << i << " before sleeping" << endl;
        
        sleep(1);
        
        cout << "USER PID:" << myPid << " PPID:" << parentPid 
             << " Iteration:" << i << " after sleeping" << endl;
    }
    
    return EXIT_SUCCESS;
}
