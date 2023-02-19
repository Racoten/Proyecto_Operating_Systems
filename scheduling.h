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
void firstComeFirstServe(Process* head, int procNumber) {
    int* waitingTime = new int[procNumber];
    int* burstTimes = new int[procNumber];

    Process* current = head;
    for (int i = 0; i < procNumber; i++) {
        burstTimes[i] = current->burstTime;
        current = current->next;
    }

    waitingTime = calculateNonPreemptive(burstTimes, procNumber);

    Process* current = head;
    while (current != nullptr) {
        int i = 0;
        cout << "Process ID: " << current->pid << ", Waiting time: " << waitingTime[i] << endl;
        current = current->next;
        i += 1;
    }
}
