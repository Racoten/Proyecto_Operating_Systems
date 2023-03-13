#include <iostream>
#include "scheduling.h"
#include <string>
#include <algorithm>

using namespace std;

/**
 * Print the linked list for processes 
 * @param head Contains the head node of the linked list as a starting point
**/
void printLinkedList(Process* head) {
    Process* current = head;
    cout  << "" << endl;
    while (current != nullptr) {
        cout << "Process ID: " << current->pid 
             << ", Burst Time: " << current->burstTime 
             << ", Priority: " << current->priority <<  endl;
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
    string allowContinue = "NO";
    // exit(0);
    do {
        string algorithm = printMenu();
        
        if (algorithm == "FCFS") {
            firstComeFirstServe(head, procSelection);
        }
        else if (algorithm == "SJF") {
            shortestJobFirst(head, procSelection);
        }
        else if (algorithm == "Priority") {
            priorityScheduling(head, procSelection);
        }

        cout << "\nWould you like to continue? (Example: yes, y): ";
        cin >> allowContinue;
        transform(allowContinue.begin(), allowContinue.end(), allowContinue.begin(), ::toupper);

    } while (allowContinue != "NO" && allowContinue != "N");

    return 0;
}