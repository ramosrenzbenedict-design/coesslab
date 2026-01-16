#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
    int numprocess=1;
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    } 
    else if (pid == 0) {
        numprocess++;//increments numprocess for childprocess
        cout << "Process " << numprocess << ": PID = " << getpid() << endl;
        return 0;
    } 
    else {
        // Parent process
        cout << "Process " << numprocess << ": PID = " << getpid() << endl;
        wait(NULL);
        numprocess++;//increments numprocess for second childprocess
        pid_t pid2 = fork();
        if (pid2 < 0) {
            cerr << "Fork failed" << endl;
            return 1;
        } 
        else if (pid2 == 0) {
            numprocess++;//increments numprocess for childprocess
            cout << "Process " << numprocess << ": PID = " << getpid() << endl;
            return 0;
        } 
        else {
            wait(NULL);
        }
    }
    return 0;
}