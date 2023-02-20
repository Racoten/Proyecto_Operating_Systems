#include <iostream>
#include "scheduling.h"

using namespace std;

/**
 * Print the linked list for processes
 * @param head Contains the head node of the linked list as a starting point
**/
void printLinkedList(Process* head) {
    Process* current = head;
    while (current != nullptr) {
        cout << "Process ID: " << current->pid << ", Burst Time: " << current->burstTime << endl;
        current = current->next;
    }
}

int main() {
    // Print menu for user to set up a process' list
    int procSelection = 0;
    cout << "Please enter the number of processes that will be fed into each algorithm: ";
    cin >> procSelection;

    Process* head = NULL; 
    head = generateProcessList(procSelection);
    printLinkedList(head);
    // exit(0);

    string algorithm = printMenu();
    
    if (algorithm == "FCFS") {
        firstComeFirstServe(head, procSelection);
        return 0;
    }
    else if (algorithm == "SJF") {
        shortestJobFirst(head, procSelection);
        return 0;
    }
    return 0;
}
