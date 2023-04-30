#include <climits>
#include <algorithm>

// Function to calculate the total number of head movements and print the sequence of movements
int dFCFS(int requests[]) {
    int head = requests[0];
    int total_moves = 0;
    int curr_pos = head;

    // Traverse the requests queue in order and calculate the total number of moves
    cout << "Sequence of movements: ";
    for (int i = 1; i < 9; i++) { //FIXED, BEFORE WAS FROM 0 TO 9 
        cout << curr_pos << " -> ";
        total_moves += abs(requests[i] - curr_pos);
        curr_pos = requests[i];
    }
    cout << curr_pos << endl;

    return total_moves;
}

int sstf(int requests[]) {
    // Set the initial head position as the first request
    int head = requests[0];
    // Initialize the total number of disk movements to 0
    int total_moves = 0;
    // Initialize the current position as the head position
    int curr_pos = head;

    // Print a message to indicate that the sequence of disk movements is being printed
    cout << "Sequence of movements: ";

    // Process all disk requests
    for (int i = 0; i < 9; i++) {
        // Sort the remaining requests in ascending order of distance from the current position
        sort(requests + i, requests + 9, [curr_pos](int a, int b) {
            return abs(a - curr_pos) < abs(b - curr_pos);
        });

        // Select the request with the smallest distance from the current position
        int closest_request = requests[i];
        // Calculate the distance between the current position and the selected request
        int min_dist = abs(closest_request - curr_pos);

        // Update the total number of disk movements
        total_moves += min_dist;
        // Update the current position to the selected request
        curr_pos = closest_request;

        // Print the selected request as the next disk movement
        cout << curr_pos << " -> ";
    }

    // Return the total number of disk movements
    return total_moves;
}

int cscan(int requests[]) {// VERIFICAR Y ARREGLAR LOS OUTPUT YA QUE AVECES LO QUE DA ES EL SORTED ARRAY Y NO EL MOVEMENT DE LOS REQUEST EN EL ORDEN QUE SE SUPONE
    int edgeLeft = 0;
    int edgeRight = 199;
    int movements = 0;
    int head = requests[0];
    int size = 10;
    cout << "Head is -> " << head << endl;

    // Sort in ascending order
    sort(requests, requests + size);

    int newLineUp[10];

    // Copy contents of old array to new array
    for(int i = 0; i < 10; i++) {
        newLineUp[i] = requests[i];
    }
    
    
    // Divide arrays into two new arrays
    int newSmallsLineUp[5];
    for (int i = 0; i < 5; i++) {
        newSmallsLineUp[i] = newLineUp[i];
    }

    int newBigsLineUp[5];
    int startingPosition = 5;
    for (int i = 0; i < 5; i++) {
        newBigsLineUp[i] = newLineUp[startingPosition];
        startingPosition += 1;
    }
    
    return movements;
}
int scan(int requests[]) {
    int edgeLeft = 0;
    int edgeRight = 199;
    int movements = 0;
    int head = requests[0];
    int size = 10;
    cout << "Head is -> " << head << endl;

    // Sort in ascending order
    sort(requests, requests + size);

    // Find position of head in requests array
    int headPosition = 0;
    for (int i = 0; i < size; i++) {
        if (requests[i] == head) {
            headPosition = i;
            break;
        }
    }

    // Go right
    for (int i = headPosition; i < size; i++) {
        movements += abs(requests[i] - head);
        head = requests[i];
    }

    // Go left
    for (int i = headPosition - 1; i >= 0; i--) {
        movements += abs(requests[i] - head);
        head = requests[i];
    }

    // Print sorted request
    cout << "Sorted Requests: ";
    for (int i = 0; i < size; i++) {
        cout << requests[i] << " ";
    }
    cout << endl;

    return movements;
}