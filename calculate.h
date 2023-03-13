#include <iostream>

using namespace std;
/**
 * Calculate Waiting Time with Non-preemption
 * This function will caculate the waiting time for each process sequentially in the order that they are passed
 * 
 * @param burstTime holds the burst time of each process
 * @param procNumber holds the total number of processes being passed
*/
int* calculateNonPreemptive(int burstTime[], int procNumber) {
    int* waitingTime = new int[procNumber];
    waitingTime[0] = 0;

    int lastWait = 0;
    for (int i = 0; i < procNumber; i++) {
        waitingTime[i + 1] = lastWait + burstTime[i];
        lastWait = waitingTime[i + 1];
    }

    for (int i = 0; i < procNumber; i++) {
        cout << waitingTime[i] << endl;
    }

    return waitingTime;
}