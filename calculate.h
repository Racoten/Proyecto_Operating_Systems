#include <iostream>
#include <queue>

using namespace std;
/**
 * Calculate Waiting Time with Non-preemption
 * This function will caculate the waiting time for each process sequentially in the order that they are passed
 * 
 * @param burstTime holds the burst time of each process
 * @param procNumber total number of processes being passed
*/
int* calculateNonPreemptive(int burstTime[], int procNumber) {
    int* waitingTime = new int[procNumber];
    waitingTime[0] = 0;

    int lastWait = 0;
    for (int i = 0; i < procNumber; i++) {
        waitingTime[i + 1] = lastWait + burstTime[i];
        lastWait = waitingTime[i + 1];
    }

    return waitingTime;
}

// Function to calculate waiting times of processes
void findWaitingTimeRoundRobin(Process* head, int quantum) {

    // Create a queue to store processes
    queue<Process*> processQueue;

    // Initialize waiting time of all processes to 0
    Process* current = head;
    while (current != nullptr) {
        current->waitingTime = 0;
        current = current->next;
    }

    // Start with the first process
    current = head;

    // Initialize current time and remaining time
    int currentTime = 0;

    // Loop through all the processes
    while (current != nullptr || !processQueue.empty()) {

        // Add all the processes that have arrived to the queue
        while (current != nullptr && current->arrivalTime <= currentTime) {
            processQueue.push(current);
            current = current->next;
        }

        // If the queue is empty, move on to the next process
        if (processQueue.empty()) {
            currentTime = current->arrivalTime;
            continue;
        }

        // Get the next process from the queue
        Process* nextProcess = processQueue.front();
        processQueue.pop();

        // Calculate the waiting time for this process
        nextProcess->waitingTime += currentTime - nextProcess->burstTime - nextProcess->arrivalTime;


        // Calculate the remaining time for this process
        int remainingTime = nextProcess->burstTime - quantum;

        // If the process has completed, update its turnaround time
        if (remainingTime <= 0) {
            currentTime += nextProcess->burstTime;
            nextProcess->turnAroundTime = currentTime;
        } else {
            // Add the process back to the queue with updated remaining time
            nextProcess->burstTime = remainingTime;
            processQueue.push(nextProcess);
            currentTime += quantum;
        }
    }
}