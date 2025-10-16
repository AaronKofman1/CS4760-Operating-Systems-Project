#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printHelp(const char* programName) {
    cout << "Usage: " << programName << " [-h] [-n proc] [-s simul] [-t iter]" << endl;
    cout << "  -h        : Show this help message" << endl;
    cout << "  -n proc   : Number of total children to launch (default: 1)" << endl;
    cout << "  -s simul  : Number of children to run simultaneously (default: 1)" << endl;
    cout << "  -t iter   : Number of iterations each child should do (default: 1)" << endl;
}

int main(int argc, char** argv) {
    int totalChildren = 1;    // -n parameter
    int simultaneous = 1;     // -s parameter
    int iterations = 1;       // -t parameter
    
    int option;
    while ((option = getopt(argc, argv, "hn:s:t:")) != -1) {
        switch (option) {
            case 'h':
                printHelp(argv[0]);
                return EXIT_SUCCESS;
            case 'n':
                totalChildren = atoi(optarg);
                break;
            case 's':
                simultaneous = atoi(optarg);
                break;
            case 't':
                iterations = atoi(optarg);
                break;
            case '?':
                cout << "Unknown option. Use -h for help." << endl;
                return EXIT_FAILURE;
        }
    }
    
    cout << "OSS starting with " << totalChildren << " total children, " 
         << simultaneous << " simultaneous, " << iterations << " iterations each" << endl;
    
    int childrenLaunched = 0;
    int childrenCompleted = 0;
    int currentlyRunning = 0;
    string iterStr = to_string(iterations);
    
    // Main loop to manage process launching and completion
    while (childrenCompleted < totalChildren) {
        // Launch new processes if we can
        while (currentlyRunning < simultaneous && childrenLaunched < totalChildren) {
            pid_t childPid = fork();
            
            if (childPid == 0) {
                // Child process - exec to user
                execlp("./user", "./user", iterStr.c_str(), (char*)NULL);
                
                // If we get here, exec failed
                cerr << "Exec failed for user process" << endl;
                exit(1);
            } else if (childPid > 0) {
                // Parent process
                childrenLaunched++;
                currentlyRunning++;
                cout << "OSS: Launched child " << childrenLaunched 
                     << " with PID " << childPid 
                     << " (currently running: " << currentlyRunning << ")" << endl;
            } else {
                // Fork failed
                cerr << "Fork failed for child " << childrenLaunched + 1 << endl;
                break;
            }
        }
        
        // Wait for at least one child to complete
        if (currentlyRunning > 0) {
            wait(NULL);
            currentlyRunning--;
            childrenCompleted++;
            cout << "OSS: A child completed (remaining: " 
                 << (totalChildren - childrenCompleted) << ")" << endl;
        }
    }
    
    cout << "OSS: All children completed. Launched " << childrenLaunched << " children total." << endl;
    return EXIT_SUCCESS;
}
