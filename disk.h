#include <climits>
#include <algorithm>

/**
 * Calculate the total number of head movements using the Disk First Come First Serve (FCFS) scheduling algorithm
 * This function takes an array of disk access requests as input and returns the total number of head movements
 * required to complete all requests using the Disk FCFS algorithm.
 * 
 * @param requests An array of integers representing the disk access requests in their arrival order
 * @return The total number of head movements calculated using the Disk FCFS algorithm
 */
int dFCFS(int requests[]) {
    int head = requests[0];
    int total_moves = 0;
    int curr_pos = head;

    // Traverse the requests queue in order and calculate the total number of moves
    cout << "Sequence of movements: ";
    for (int i = 1; i < 10; i++) { //FIXED, BEFORE WAS FROM 0 TO 9 
        cout << curr_pos << " -> ";
        total_moves += abs(requests[i] - curr_pos);
        curr_pos = requests[i];
    }
    cout << curr_pos << endl;

    return total_moves;
}

/**
 * Calculate the total number of head movements using the Shortest Seek Time First (SSTF) scheduling algorithm
 * This function takes an array of disk access requests as input and returns the total number of head movements
 * required to complete all requests using the SSTF algorithm.
 * 
 * @param requests An array of integers representing the disk access requests in their arrival order
 * @return The total number of head movements calculated using the SSTF algorithm
 */
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
    for (int i = 0; i < 10; i++) {
        // Sort the remaining requests in ascending order of distance from the current position
        sort(requests + i, requests + 10, [curr_pos](int a, int b) {
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

const int num_requests = 8;
const int disk_capacity = 200;

/**
* Circular scan algorithm for disk scheduling.
*
* @param requests An array of requests to be processed.
* @param intial_head contains the head of the sequence
* @return The total number of movements made by the disk head.
*/
void cscan(int request_arr[], int initial_head) {
    int seek_operations = 0;
    int travel_distance, current_track;
    vector<int> lower_tracks, upper_tracks;
    vector<int> track_sequence;

    lower_tracks.push_back(0);
    upper_tracks.push_back(disk_capacity - 1);

    for (int i = 0; i < num_requests; i++) {
        if (request_arr[i] < initial_head)
            lower_tracks.push_back(request_arr[i]);
        if (request_arr[i] > initial_head)
            upper_tracks.push_back(request_arr[i]);
    }

    std::sort(lower_tracks.begin(), lower_tracks.end());
    std::sort(upper_tracks.begin(), upper_tracks.end());

    for (int i = 0; i < upper_tracks.size(); i++) {
        current_track = upper_tracks[i];
        track_sequence.push_back(current_track);

        travel_distance = abs(current_track - initial_head);
        seek_operations += travel_distance;
        initial_head = current_track;
    }

    initial_head = 0;
    seek_operations += (disk_capacity - 1);

    for (int i = 0; i < lower_tracks.size(); i++) {
        current_track = lower_tracks[i];
        track_sequence.push_back(current_track);

        travel_distance = abs(current_track - initial_head);
        seek_operations += travel_distance;
        initial_head = current_track;
    }

    cout << "Total number of seek operations = "
         << seek_operations << endl;

    cout << "Track Sequence is: ";

    for (int i = 0; i < track_sequence.size(); i++) {
        cout << track_sequence[i] << " -> ";
    }
}

const int size = 8;
const int disk_size = 200;

/**
 * This function calculates the total number of disk movements required 
 * to fulfill a sequence of disk requests using the SCAN algorithm.
 * 
 * @param requests An array of integers representing the sequence of disk requests
 * @return The total number of disk movements required to fulfill the sequence of disk requests
 */
void scan(int request_arr[], int initial_head, string initial_dir)
{
    int total_seek_operations = 0;
    int dist, current_track;
    vector<int> left_requests, right_requests;
    vector<int> track_sequence;

    if (initial_dir == "left")
        left_requests.push_back(0);
    else if (initial_dir == "right")
        right_requests.push_back(disk_size - 1);

    for (int i = 0; i < size; i++) {
        if (request_arr[i] < initial_head)
            left_requests.push_back(request_arr[i]);
        if (request_arr[i] > initial_head)
            right_requests.push_back(request_arr[i]);
    }

    std::sort(left_requests.begin(), left_requests.end());
    std::sort(right_requests.begin(), right_requests.end());

    int iteration = 2;
    while (iteration--) {
        if (initial_dir == "left") {
            for (int i = left_requests.size() - 1; i >= 0; i--) {
                current_track = left_requests[i];

                track_sequence.push_back(current_track);

                dist = abs(current_track - initial_head);

                total_seek_operations += dist;

                initial_head = current_track;
            }
            initial_dir = "right";
        }
        else if (initial_dir == "right") {
            for (int i = 0; i < right_requests.size(); i++) {
                current_track = right_requests[i];
                track_sequence.push_back(current_track);

                dist = abs(current_track - initial_head);

                total_seek_operations += dist;

                initial_head = current_track;
            }
            initial_dir = "left";
        }
    }

    cout << "Total number of seek operations = "
         << total_seek_operations << endl;

    cout << "Seek Sequence is: ";

    for (int i = 0; i < track_sequence.size(); i++) {
        cout << track_sequence[i] << " -> ";
    }
}
