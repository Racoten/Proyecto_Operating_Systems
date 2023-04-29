#include <iostream>
#include "menu.h"
#include "calculate.h"
#include "sortProcesses.h"

// Define prototypes
Process* generateNewList(Process* head);
void deleteLinkedList(Process* head);

using namespace std;

/**
 * First Come First Serve:
 * 
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

    waitingTime = calculateNonPreemptive(burstTimes, procNumber);

    int i = 0;
    current = firstProcess;
    cout << "\nProcess\t\t|\t   Waiting Time" << endl;
    cout << "----------------------------------------------" << endl;
    while (current != nullptr) {
        cout << "P" << current->pid << "\t\t" << "|\t\t" << waitingTime[i] << endl;
        current = current->next;
        i += 1;
    }
}

/**
 * Shortest Job First (SJF):
 * 
 * This function will calculate the waiting time of each process in a linkedlist:
 * It will first take the arrival time and the burst time to decide which process
 * will go first and at what time (ms) the dispatcher will step over to the second 
 * process considering the size of its burst time
 * 
 * @param head this parameter will contain the linkedlist of all the processes and
 * their burst time
 * @param procNumber number of total processes
*/
void shortestJobFirst(Process* head, int procNumber) {
    // Sort processes by burst time
    Process* current = sortByburstTime(head, procNumber);

    // Calculate waiting times
    int* waitingTime = new int[procNumber];
    int* burstTimes = new int[procNumber];
    current = head;
    for (int i = 0; i < procNumber; i++) {
        burstTimes[i] = current->burstTime;
        current = current->next;
    }
    waitingTime = calculateNonPreemptive(burstTimes, procNumber);

    // Display results
    cout << "\nProcess\t\t|\t   Waiting Time" << endl;
    cout << "----------------------------------------------" << endl;
    int i = 0;
    current = head;
    while (current != nullptr) {
        cout << "P" << current->pid << "\t\t" << "|\t\t" << waitingTime[i] << endl;
        current = current->next;
        i += 1;
    }

    // Calculate and display total wait time, turnaround time, and average turnaround time
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int currentTime = 0;
    current = head;

    cout << "\n";
    while (current != nullptr) {
        int waitTime = currentTime - current->arrivalTime;
        totalWaitTime += waitTime;
        int turnaroundTime = waitTime + current->burstTime;
        totalTurnaroundTime += turnaroundTime;

        currentTime += current->burstTime;

        // Update arrival time of next process
        if (current->next != nullptr) {
            current->next->arrivalTime = currentTime;
        }

        current = current->next;
    }

    cout << "\nTotal wait time: " << totalWaitTime << "\n";
    cout << "Total turnaround time: " << totalTurnaroundTime << "\n";
    cout << "Average turnaround time: " << static_cast<double>(totalTurnaroundTime) / procNumber << "\n";
}


/**
 * Priority Process Scheduling: 
 * 
 * This function will receive a Sorted linked list of process in the order based off
 * the lowest priority among them
 * 
 * @param head sorted linked list of all process to be used
 * @param procNumber number of total processes
*/
void priorityScheduling(Process* head, int procNumber) {
    Process* sortedHead = sortByPriority(head, procNumber);
    
    /** Copy paste same algorithm for First Come First Serve because the linked list is
     * already sorted and ready for processing
    **/
    int* waitingTime = new int[procNumber];
    int* burstTimes = new int[procNumber];

    Process* current = sortedHead;
    for (int i = 0; i < procNumber; i++) {
        burstTimes[i] = current->burstTime;
        current = current->next;
    }

    waitingTime = calculateNonPreemptive(burstTimes, procNumber);

    int i = 0;
    float totalWaitingTime = 0.0;
    current = sortedHead;
    cout << "\nProcess\t\t|\t   Waiting Time" << endl;
    cout << "----------------------------------------------" << endl;
    while (current != nullptr) {
        cout << "P" << current->pid << "\t\t" << "|\t\t" << waitingTime[i] << endl;
        current = current->next;
        totalWaitingTime += waitingTime[i];
        i += 1;
    }

    cout << "\nAverage waiting time for all processes is: " << totalWaitingTime / procNumber << endl;
}

/**
 * Round Robin:
 * 
 * This function will calculate the waiting time and turn around time of a process
 * it receives from a linked list and will schedule them using Round Robin taking 
 * into account the Quantum time
 * 
 * @param head sorted linked list of all process to be used
 * @param procNumber number of total processes
**/
void roundRobin(Process* head, int procNumber) {
    // Reconstruct the singly linked list of processes to become a Circular Doubly Linked List
    Process* reconstructedHead = processReconstruct(head);

    int quantum = 0;
    cout << "Enter quantum time: ";
    cin >> quantum;

    // Execute first process
    findWaitingTimeRoundRobin(reconstructedHead, quantum);


    // Print out the waiting time for each process
    Process* current = reconstructedHead;
    int totalWaitingTime = 0;
    int i = 0;
    int* waitingTime = new int[procNumber];

    for (int i = 0; i < procNumber; i++) {
        waitingTime[i] = reconstructedHead->waitingTime;
    }

    cout << "\nProcess\t\t|\t   Waiting Time" << endl;
    cout << "----------------------------------------------" << endl;
    while (current != nullptr) {
        cout << "P" << current->pid << "\t\t" << "|\t\t" << waitingTime[i] << endl;
        current = current->next;
        totalWaitingTime += waitingTime[i];
        i += 1;
    }

    deleteLinkedList(reconstructedHead);
}

void deleteLinkedList(Process* head) {
    Process* current = head;
    Process* next;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    head = nullptr; // Set head to null after deleting all nodes
}