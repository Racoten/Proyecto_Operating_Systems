#include <iostream>
#include "menu.h"
#include "calculate.h"
#include "sortProcesses.h"
#include <climits>
#include <algorithm>

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

    // Store waiting times and calculate turnaround times in the Process struct
    current = firstProcess;
    for (int i = 0; i < procNumber; i++) {
        current->waitingTime = waitingTime[i];
        current->turnAroundTime = current->waitingTime + current->burstTime;
        current = current->next;
    }

    // Output results
    cout << "\nProcess\t\t|\t   Waiting Time\t\t|\tTurnaround Time" << endl;
    cout << "----------------------------------------------------------------" << endl;
    float totalWaitingTime = 0.0;
    float totalTurnaroundTime = 0.0;
    current = firstProcess;
    while (current != nullptr) {
        cout << "P" << current->pid << "\t\t" << "|\t\t" << current->waitingTime << "\t\t|\t" << current->turnAroundTime << endl;
        totalWaitingTime += current->waitingTime;
        totalTurnaroundTime += current->turnAroundTime;
        current = current->next;
    }

    cout << "\nAverage waiting time for all processes is: " << totalWaitingTime / procNumber << endl;
    cout << "Average turnaround time for all processes is: " << totalTurnaroundTime / procNumber << endl;

    delete[] waitingTime;
    delete[] burstTimes;
}

bool compareArrivalTime(Process* a, Process* b) {
    return a->arrivalTime < b->arrivalTime;
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
    Process** processes = new Process*[procNumber];
    Process* current = head;

    for (int i = 0; i < procNumber; i++) {
        processes[i] = current;
        current->remainingBurstTime = current->burstTime;
        current = current->next;
    }

    sort(processes, processes + procNumber, compareArrivalTime);

    int currentTime = 0;
    int completed = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;

    while (completed < procNumber) {
        int minRemainingTimeIndex = -1;
        int minRemainingTime = INT_MAX;

        for (int i = 0; i < procNumber; i++) {
            if (processes[i]->arrivalTime <= currentTime && processes[i]->remainingBurstTime > 0) {
                if (processes[i]->remainingBurstTime < minRemainingTime) {
                    minRemainingTime = processes[i]->remainingBurstTime;
                    minRemainingTimeIndex = i;
                }
            }
        }

        if (minRemainingTimeIndex != -1) {
            processes[minRemainingTimeIndex]->remainingBurstTime -= 1;
            currentTime++;

            if (processes[minRemainingTimeIndex]->remainingBurstTime == 0) {
                completed++;
                processes[minRemainingTimeIndex]->waitingTime = currentTime - processes[minRemainingTimeIndex]->arrivalTime - processes[minRemainingTimeIndex]->burstTime;
                processes[minRemainingTimeIndex]->turnAroundTime = currentTime - processes[minRemainingTimeIndex]->arrivalTime;
                totalWaitTime += processes[minRemainingTimeIndex]->waitingTime;
                totalTurnaroundTime += processes[minRemainingTimeIndex]->turnAroundTime;
            }
        } else {
            currentTime++;
        }
    }

    // Display results
    cout << "\nProcess\t\t|\t   Waiting Time\t\t|\tTurnaround Time" << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < procNumber; i++) {
        cout << "P" << processes[i]->pid << "\t\t" << "|\t\t" << processes[i]->waitingTime << "\t\t|\t" << processes[i]->turnAroundTime << endl;
    }

    cout << "\nTotal wait time: " << totalWaitTime << "\n";
    cout << "Average Waiting Time: " << (float)(totalWaitTime/(float)(procNumber)) << "\n";
    cout << "Total turnaround time: " << totalTurnaroundTime << "\n";
    cout << "Average turnaround time: " << static_cast<double>(totalTurnaroundTime) / procNumber << "\n";

    delete[] processes;
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
    
    int* burstTimes = new int[procNumber];
    Process* current = sortedHead;
    for (int i = 0; i < procNumber; i++) {
        burstTimes[i] = current->burstTime;
        current = current->next;
    }

    int* waitingTime = calculateNonPreemptive(burstTimes, procNumber);

    // Store waiting times and calculate turnaround times in the Process struct
    current = sortedHead;
    for (int i = 0; i < procNumber; i++) {
        current->waitingTime = waitingTime[i];
        current->turnAroundTime = current->waitingTime + current->burstTime;
        current = current->next;
    }

    // Sort processes by pid
    Process** processArray = new Process*[procNumber];
    current = head;
    for (int i = 0; i < procNumber; i++) {
        processArray[i] = current;
        current = current->next;
    }

    sort(processArray, processArray + procNumber, [](Process* a, Process* b) {
        return a->pid < b->pid;
    });

    // Output results
    cout << "\nProcess\t\t|\t   Waiting Time\t\t|\tTurnaround Time" << endl;
    cout << "----------------------------------------------------------------" << endl;
    float totalWaitingTime = 0.0;
    float totalTurnaroundTime = 0.0;
    for (int i = 0; i < procNumber; i++) {
        cout << "P" << processArray[i]->pid << "\t\t" << "|\t\t" << processArray[i]->waitingTime << "\t\t|\t" << processArray[i]->turnAroundTime << endl;
        totalWaitingTime += processArray[i]->waitingTime;
        totalTurnaroundTime += processArray[i]->turnAroundTime;
    }

    cout << "\nAverage waiting time for all processes is: " << totalWaitingTime / procNumber << endl;
    cout << "Average turnaround time for all processes is: " << totalTurnaroundTime / procNumber << endl;

    delete[] burstTimes;
    delete[] waitingTime;
    delete[] processArray;
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
    int quantum = 0;
    cout << "Enter quantum time: ";
    cin >> quantum;

    // Execute first process
    findWaitingTimeRoundRobin(head, quantum);

    // Calculate total waiting time and turnaround time
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    Process* current = head;
    while (current != nullptr) {
        totalWaitingTime += current->waitingTime;
        totalTurnaroundTime += current->turnAroundTime;
        current = current->next;
    }

    // Print out the waiting time and turnaround time for each process
    current = head;

    cout << "\nProcess\t\t|\t   Waiting Time\t\t|\tTurnaround Time" << endl;
    cout << "---------------------------------------------------------------" << endl;
    while (current != nullptr) {
        cout << "P" << current->pid << "\t\t" << "|\t\t" << current->waitingTime << "\t\t|\t" << current->turnAroundTime << endl;
        current = current->next;
    }

    // Calculate and display average waiting time and turnaround time
    cout << "\nAverage waiting time for all processes is: " << static_cast<double>(totalWaitingTime) / procNumber << endl;
    cout << "Average turnaround time for all processes is: " << static_cast<double>(totalTurnaroundTime) / procNumber << endl;
}