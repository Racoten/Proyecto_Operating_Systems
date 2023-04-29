#include <iostream>
#include <string>

using namespace std;

// Struct for each node in a linked list
struct Process {
    int pid;
    int burstTime;
    int arrivalTime;
    int priority;
    int turnAroundTime;// new por Fau
    int waitingTime;
    int remainingBurstTime;
    Process* next;
    Process* previous;
};

// Struct for each memory page in a linkedlist
struct Memory {
  int page;
  Memory *next;
  Memory *previous;
};

Memory *generateMemoryList(int memSelection) {
  // Before create more than 1 Node in a linked list, define first
  // a head node and set up its values
  int headPage = 0;

  cout << "\nEnter the Page for the head page: ";
  cin >> headPage;

  // Create head node with values passed
  Memory *head = new Memory();
  head->page = headPage;

  int nextNodePAGE = 0;

  Memory *current = head;

  for (int i = 1; i < memSelection; i++) {
    nextNodePAGE = i + 1;

    cout << "\nEnter Page for next node: ";
    cin >> nextNodePAGE;

    // After entering the values for a node, automatically create them and add
    // another node right beneath it
    Memory *newMemory = new Memory();
    newMemory->page = nextNodePAGE;
    current->next = newMemory;
    current = current->next;
  }

  return head;
}

/**
 * Generate Process List: 
 * This method will generate a LinkedList by first asking the user how many Nodes to add (i.e Processes to add) and then for each, ask the user for the burst time
 * It first creates a head node as the starting point
 * 
 * @param procSelection contains the number of process that will be created and added to a Node
**/
Process* generateProcessList(int procSelection) {
    // Before create more than 1 Node in a linked list, define first
    // a head node and set up its values
    int headPID = 1;
    int headBurstTime = 0;
    int headPriority = 0;
    int headArrivalTime = 0;
    // cout << "Enter the pid for the head node: ";
    // cin >> headPID;

    cout << "\nEnter the Burst Time for the head process: ";
    cin >> headBurstTime;

    cout << "Enter the Priority for the head process: ";
    cin >> headPriority;

    cout << "Enter the Arrival Time for the head process: ";
    cin >> headArrivalTime;

    // Create head node with values passed
    Process* head = new Process();
    head->pid = headPID;
    head->burstTime = headBurstTime;
    head->priority = headPriority;
    head->arrivalTime = headArrivalTime;

    // Initialize variables to hold the PID and Burst Time for each 
    // consequent node on the list
    int nextNodePID = 0;
    int nextNodeBurstTime = 0;    
    int nextNodePriority = 0;
    int nextNodeArrivalTime = 0;

    Process* current = head;
    // Subtract 1 to procSelection because we are adding a node after the head node
    for (int i = 1; i < procSelection; i++) {
        nextNodePID = i + 1;

        cout << "\nEnter Burst Time for next node: ";
        cin >> nextNodeBurstTime;

        cout << "Enter Priority for next node: ";
        cin >> nextNodePriority;

        cout << "Enter Arrival Time for next node: ";
        cin >> nextNodeArrivalTime;

        // After entering the values for a node, automatically create them and add 
        // another node right beneath it
        Process* newProcess = new Process();
        newProcess->pid = nextNodePID;
        newProcess->burstTime = nextNodeBurstTime;
        newProcess->priority = nextNodePriority;
        newProcess->arrivalTime = nextNodeArrivalTime;
        current->next = newProcess;
        current = current->next;
    }

    return head;
}

/**
 * Print the sub menu
 * After the user has selected the option from the first menu, 
 * this method will be called and it will hold a string array 
 * that contains the names of the algorithms that can be used.
 * 
 * @param algorithms String array that holds the name of each algorithm to be presented
 * @param algorithmSelected ID of the algorithm that was selected
**/
int printSubMenu(string algorithms[], int algorithmSelected) {
    // Initialize selection variable and the size of the array that holds the algorithms
    int selection = 0;
    int arraySize = 0;
    switch (algorithmSelected) {
        case 1:
            arraySize = 4;
            break;
        case 2:
            arraySize = 3;
            break;
        case 3:
            arraySize = 4;
            break;
    }

    // Print a menu by looping through each element in the algorithms array
    cout << "\n\nSelect options between 0 to " << arraySize << endl;
    for (int i = 0; i < arraySize; i++) {
        cout << i + 1 << ". " << algorithms[i] << endl;
    }
    cout << "0. Exit" << endl;
    cout << "\nPrompt: ";
    cin >> selection;
    
    selection = selection - 1;
    // Return back the ID for the selected algorithm
    return selection;
}

/**
 * Print Main Menu
 * This is the first menu that will be shown to the user for selection.
 * It will hold 3 options where each has their own correspondent algorithm
 * for processing.
**/
string printMenu() {
    // Initialize arrays that hold the algorithms for each option
    string algProcesses[] = {"FCFS", "SJF", "Priority", "Round Robin"};
    string algMemory[] = {"LRU", "Optimal", "FIFO"};
    string algDisks[] = {"dFCFS", "SSF", "Scan", "C-Scan"};

    // Present a menu prompt for the user to select an option
    int selection = 0;
    int alg = 0;
    cout << "\nPlease choose one the following to proceed (1 - 3):" << endl;
    cout << "1. Processes\n"
         << "2. Memory\n"
         << "3. Disk\n"
         << "0. Exit\n";
    cout << "Prompt: ";
    cin >> selection;

    // Switch case if a user selects any option, it will call printSubMenu() method passing it a correspondent algorithm array
    switch (selection) {
        case 1:
            alg = printSubMenu(algProcesses, 1);
            cout << algProcesses[alg] << " <- Algorithm for CPU Scheduling selected" << endl;
            return algProcesses[alg];
            break;
        case 2:
            alg = printSubMenu(algMemory, 2);
            cout << algMemory[alg] << " <- Algorithm for Memory Scheduling selected" << endl;
            return algMemory[alg];
            break;
        case 3:
            alg = printSubMenu(algDisks, 3);
            cout << algDisks[alg] << " <- Algorithm Disk Scheduling selected" << endl;
            return algDisks[alg];
            break;
        case 0:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            cout << "Option has to be between 0 and 3" << endl;
            break;
    }

    return NULL;
}