#include <iostream>
#include "menu.h"
#include "calculate.h"

using namespace std;

/**
 * First Come First Serve:
 * This method will receive a linked list in order as presented and return an array,
 * or rather a pointer to the first element in the array that contains the waiting
 * time for each process
 * 
 * @param head this parameter will contain the linkedlist of all the processes and
 * their burst time
 * @param procNumber number of total processes
*/
void firstComeFirstServe(Process* firstProcess, int procNumber) {
    int* waitingTime = new int[procNumber];
    int* burstTimes = new int[procNumber];

    Process* current = firstProcess;
    for (int i = 0; i < procNumber; i++) {
        burstTimes[i] = current->burstTime;
        current = current->next;
    }

    cout << "Before calculateNonPreemptive" << endl;
    waitingTime = calculateNonPreemptive(burstTimes, procNumber);

    int i = 0;
    current = firstProcess;
    cout << "Process\t\t|\t   Waiting Time" << endl;
    cout << "----------------------------------------------" << endl;
    while (current != nullptr) {
        cout << "P" << current->pid << "\t\t" << "|\t\t" << waitingTime[i] << endl;
        current = current->next;
        i += 1;
    }
}
