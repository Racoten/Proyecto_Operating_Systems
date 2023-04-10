#include <iostream>

using namespace std;

/**
 * Sort Processes by Priority
 * This method will receive an unsorted linked list and reorder it
 * based on their priority. The algorithm used for sorting is 
 * Selection Sort, which will take the smallest number in the linked
 * list and will swap it with the first element in the linked list.
 * Best and worst case for it is O(n^2), unless the list is already 
 * sorted in which case the time complexity is O(n)
 * 
 * @param head unsorted linked list of all process nodes
 * @param procNumber number of total processes
*/
Process* sortByPriority(Process* head, int procNumber) {
    // If the linked list is empty or has only one node, it is already sorted, so return it
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Create a pointer to the head of the linked list and start traversing it
    Process* curr = head;
    while (curr != nullptr) {
        // Set the current node as the minimum node
        Process* minNode = curr;

        // Create a temporary pointer to the node following the current 
        Process* temp = curr->next;

        // Traverse the rest of the linked list to find the node with the smallest priority
        while (temp != nullptr) {
            if (temp->priority < minNode->priority) {
                minNode = temp;
            }
            temp = temp->next;
        }

        // If the node with the smallest priority is not the current node,
        // swap the values of the current node and the node with the smallest priority
        if (minNode != curr) {
            int tempPriority = curr->priority;
            curr->priority = minNode->priority;
            minNode->priority = tempPriority;
            int tempBurstTime = curr->burstTime;
            curr->burstTime = minNode->burstTime;
            minNode->burstTime = tempBurstTime;
        }

        // Move to the next node in the linked list
        curr = curr->next;
    }

    // Return the head of the sorted linked list
    return head;
}

/**
 * @param head unsorted linked list of all process nodes
 * @param procNumber number of total processes
*/
Process* sortByburstTime(Process* head, int procNumber) {
    // If the linked list is empty or has only one node, it is already sorted, so return it
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Create a pointer to the head of the linked list and start traversing it
    Process* curr = head;
    while (curr != nullptr) {
        // Set the current node as the minimum node
        Process* minNode = curr;

        // Create a temporary pointer to the node following the current node
        Process* temp = curr->next;

        // Traverse the rest of the linked list to find the node with the smallest priority
        while (temp != nullptr) {
            if (temp->burstTime < minNode->burstTime) {
                minNode = temp;
            }
            temp = temp->next;
        }

        // If the node with the smallest priority is not the current node,
        // swap the values of the current node and the node with the smallest priority
        if (minNode != curr) {
            int tempBurstTime = curr->burstTime;
            curr->burstTime = minNode->burstTime;
            minNode->burstTime = tempBurstTime;
        }

        // Move to the next node in the linked list
        curr = curr->next;
    }

    // Return the head of the sorted linked list
    return head;
}

/**
 * Process Reconstruct:
 * 
 * This function takes a parameter of type Process which is a singly linked list by default.
 * The function will then reconstruct it so that it can become a Circular Doubly Linked List
 * of Processes.
 * 
 * @param head unsorted linked list of all process nodes
*/
Process* processReconstruct(Process* head) {
    if (head == nullptr) {
        return nullptr;
    }

    // Traverse to the end of the list and set previous pointers
    Process* current = head;
    Process* previous = nullptr;
    while (current != nullptr) {
        current->previous = previous;
        previous = current;
        current = current->next;
    }

    // Return the new head of the list
    return head;
}