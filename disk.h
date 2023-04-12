#include <climits>
// Function to calculate the total number of head movements and print the sequence of movements
int dFCFS(int requests[]) {
    int head = requests[0];
    int total_moves = 0;
    int curr_pos = head;

    // Traverse the requests queue in order and calculate the total number of moves
    cout << "Sequence of movements: ";
    for (int i = 1; i < 9; i++) {
        cout << curr_pos << " -> ";
        total_moves += abs(requests[i] - curr_pos);
        curr_pos = requests[i];
    }
    cout << curr_pos << endl;

    return total_moves;
}
int sstf(int requests[]) {
    int head = requests[0];
    int total_moves = 0;
    int curr_pos = head;

    cout << "Sequence of movements: ";
    for (int i = 0; i < 9; i++) {
        int min_dist = INT_MAX;
        int closest_request;
        for (int j = i; j < 9; j++) {
            if (abs(requests[j] - curr_pos) < min_dist) {
                closest_request = requests[j];
                min_dist = abs(requests[j] - curr_pos);
                cout << curr_pos << " -> ";
            }
        }
        total_moves += min_dist;
        curr_pos = closest_request;
        swap(requests[i], requests[distance(requests, find(requests, requests + 9, closest_request))]);
    }
    return total_moves;
}