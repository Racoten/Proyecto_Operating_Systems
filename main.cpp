#include <iostream>
#include "scheduling.h"
#include <string>
#include <algorithm>
#include "disk.h"
#include "memory.h"
#include <unordered_set>
#include <list>

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

Process* doCPU(int procSelection) {
    Process* head = NULL; 
    head = generateProcessList(procSelection);
    printLinkedList(head);

    return head;
}

int* doDisk() {
    static int diskLineup[10] = {};

    int initialDiskPosition, nextPostion = 0;

    cout << "Please enter the initial position: ";
    cin >> initialDiskPosition;
    diskLineup[0] = initialDiskPosition;

    for (int i = 1; i < 9; i++) {
        cout << "Now enter the next position: ";
        cin >> nextPostion;
        diskLineup[i] = nextPostion;
    }

    return diskLineup;
}

void generatePageReferences(int numReferences, int pageReferences[]) {
    cout << "Enter page reference string (separated by spaces): ";
    for (int i = 0; i < numReferences; i++) {
        cin >> pageReferences[i];
    }
}

int main() {
    Process* head = NULL; 
    string allowContinue = "NO";
    // exit(0);
    do {
        string algorithm = printMenu();
        
        if (algorithm == "FCFS") {
            // Print menu for user to set up a process' list
            int procSelection = 0;
            cout << "Please enter the number of processes that will be fed into each algorithm: ";
            cin >> procSelection;
            head = doCPU(procSelection);
            firstComeFirstServe(head, procSelection);
        }
        else if (algorithm == "SJF") {
            // Print menu for user to set up a process' list
            int procSelection = 0;
            cout << "Please enter the number of processes that will be fed into each algorithm: ";
            cin >> procSelection;
            head = doCPU(procSelection);
            shortestJobFirst(head, procSelection);
        }
        else if (algorithm == "Priority") {
            // Print menu for user to set up a process' list
            int procSelection = 0;
            cout << "Please enter the number of processes that will be fed into each algorithm: ";
            cin >> procSelection;
            head = doCPU(procSelection);
            priorityScheduling(head, procSelection);
        }
        else if (algorithm == "Round Robin") {
            // Print menu for user to set up a process' list
            int procSelection = 0;
            cout << "Please enter the number of processes that will be fed into each algorithm: ";
            cin >> procSelection;
            head = doCPU(procSelection);
            roundRobin(head, procSelection);
        }
        else if (algorithm == "dFCFS") {
            int* diskLineup = doDisk();
            // for (int i = 0; i < 10; i++) {
            //     cout << diskLineup[i] << endl;
            // }
            int movements = dFCFS(diskLineup);
            cout << "Number of movements made: " << movements << endl;
        }
        else if (algorithm == "SSF") {
            int* diskLineup = doDisk();
            // for (int i = 0; i < 10; i++) {
            //     cout << diskLineup[i] << endl;
            // }
            int movements = sstf(diskLineup);
            cout << "Number of movements made: " << movements << endl;
        }
        else if (algorithm == "Scan") {
            int* diskLineup = doDisk();
            // for (int i = 0; i < 10; i++) {
            //     cout << diskLineup[i] << endl;
            // }
            int initial_head = diskLineup[0];
            string initial_direction = "left"; // or "right" depending on the initial direction you want
            scan(diskLineup, initial_head, initial_direction);
        }
        else if (algorithm == "C-Scan") {
            int* diskLineup = doDisk();
            int initial_head = diskLineup[0];
            cscan(diskLineup, initial_head);

        }
        else if (algorithm == "FIFO") {
            int numReferences, numFrames;

            cout << "Enter length of page reference string (max 20): ";
            cin >> numReferences;

            if (numReferences > 20) {
                cout << "Maximum number of references exceeded, setting to 20." << endl;
                numReferences = 20;
            }

            PageFrame* pageReferences = inputPageReferences(numReferences);

            cout << "Enter number of page frames: ";
            cin >> numFrames;

            int pageFaults = calculatePageFaultsFIFO(numFrames, pageReferences);

            cout << "Number of page faults: " << pageFaults << endl;
        } else if (algorithm == "LRU") {
            int numReferences, numFrames;

            cout << "Enter length of page reference string (max 20): ";
            cin >> numReferences;

            if (numReferences > 20) {
                cout << "Maximum number of references exceeded, setting to 20." << endl;
                numReferences = 20;
            }

            PageFrame* pageReferences = inputPageReferences(numReferences);

            cout << "Enter number of page frames: ";
            cin >> numFrames;

            int pageFaults = calculatePageFaultsLRU(numFrames, pageReferences);

            cout << "Number of page faults: " << pageFaults << endl;
        } else if (algorithm == "Optimal") {
            int numReferences, numFrames;

            cout << "Enter length of page reference string (max 20): ";
            cin >> numReferences;

            if (numReferences > 20) {
                cout << "Maximum number of references exceeded, setting to 20." << endl;
                numReferences = 20;
            }

            PageFrame* pageReferences = inputPageReferences(numReferences);

            cout << "Enter number of page frames: ";
            cin >> numFrames;

            int pageFaults = calculatePageFaultsOptimal(numFrames, pageReferences);

            cout << "Number of page faults: " << pageFaults << endl;
        }

        cout << "\nWould you like to continue? (Example: yes, y): ";
        cin >> allowContinue;
        transform(allowContinue.begin(), allowContinue.end(), allowContinue.begin(), ::toupper);

    } while (allowContinue != "NO" && allowContinue != "N");

    return 0;
}