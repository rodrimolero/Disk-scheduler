#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UP 1
#define DOWN -1

// Define a structure to represent a disk request
struct Request {
    int arrival_time;
    int track;
    int served;
};

void fcfs(struct Request requests[], int R, int H) {
    int current_time = 0; // Represents the current time in the simulation
    int total_seek_time = 0; // Total seek time accumulated while serving requests
    int total_completion_time = 0; // Total completion time for all requests
    int head = H; // Current position of the disk head
    int order[R]; // Array to record the order of served requests
    int order_index = 0; // Index to keep track of the order array
    int requests_served_count = 0; // Counter to keep track of how many requests have been served

    while (requests_served_count < R) {
        int next_request_index = -1;
        // Find the next request to serve based on FCFS
        for (int i = 0; i < R; i++) {
            if (!requests[i].served && requests[i].arrival_time <= current_time) {
                next_request_index = i;
                break;
            }
        }
        // If no request is ready to be served, jump time to the next arriving request
        if (next_request_index == -1) {
            int next_time = -1; // Time of the next arriving request
            for (int i = 0; i < R; i++) {
                if (!requests[i].served) {
                    if (next_time == -1 || requests[i].arrival_time < next_time) {
                        next_time = requests[i].arrival_time;
                    }
                }
            }
            current_time = next_time; // Move to the time of the next arriving request
            continue; // Check for requests again at the new current time
        }
        // Serve the next request
        int target_track = requests[next_request_index].track;
        int seek_distance = abs(head - target_track); // Calculate the seek distance from the current head position to the target track
        total_seek_time += seek_distance; // Accumulate the total seek time
        current_time += seek_distance; // Time taken to move the head to the target track
        head = target_track; // Update the head position
        requests[next_request_index].served = 1; // Mark the request as served
        total_completion_time = current_time; // Record the total completion time
        order[order_index++] = target_track; // Record the order of served requests
        requests_served_count++; // Increment the count of served requests
    }
    // Output the result
        for (int i = 0; i < order_index; i++) {
            printf("%d ", order[i]);
        }
        printf("\n%d\n", total_seek_time);
        printf("%d\n", total_completion_time);
}

void sstf(struct Request requests[], int R, int H) {
    int current_time = 0;
    int total_seek_time = 0;
    int total_completion_time = 0;
    int head = H;
    int order[R];
    int order_index = 0;
    int requests_served_count = 0;

    while (requests_served_count < R) {
        int next_request_index = -1;
        int min_seek_distance = 1000000; // Initialize to a large number
        for (int i = 0; i < R; i++) {
            if (!requests[i].served && requests[i].arrival_time <= current_time) {
                int seek_distance = abs(head - requests[i].track);
                if (seek_distance < min_seek_distance) {
                    min_seek_distance = seek_distance;
                    next_request_index = i;
                }
            }
        }
        // If no request is ready to be served, jump time to the next arriving request
        if (next_request_index == -1) {
            int next_time = -1; // Time of the next arriving request
            for (int i = 0; i < R; i++) {
                if (!requests[i].served) {
                    if (next_time == -1 || requests[i].arrival_time < next_time) {
                        next_time = requests[i].arrival_time;
                    }
                }
            }
            current_time = next_time; // Move to the time of the next arriving request
            continue; // Check for requests again at the new current time
        }
        // Serve the next request
        int target_track = requests[next_request_index].track;
        int seek_distance = abs(head - target_track);
        total_seek_time += seek_distance;
        current_time += seek_distance; // Time taken to move the head to the target track
        head = target_track; // Update the head position
        requests[next_request_index].served = 1; // Mark the request as served
        total_completion_time = current_time; // Record the total completion time
        order[order_index++] = target_track; // Record the order of served requests
        requests_served_count++; // Increment the count of served requests
    }
    // Output the result
        for (int i = 0; i < order_index; i++) {
            printf("%d ", order[i]);
        }
        printf("\n%d\n", total_seek_time);
        printf("%d\n", total_completion_time);
}

void scan(struct Request requests[], int N, int R, int H, int direction) {
    int current_time = 0;
    int total_seek_time = 0;
    int total_completion_time = 0;
    int head = H;
    int order[R];
    int order_index = 0;
    int requests_served_count = 0;

    while (requests_served_count < R) {
        int next_request_index = -1;
        int min_seek_distance = 1000000; // Initialize to a large number
        // Find the next request to serve based on the current head direction
        for (int i = 0; i < R; i++) {
            if (!requests[i].served && requests[i].arrival_time <= current_time) {
                if ((direction == UP && requests[i].track >= head) ||
                    (direction == DOWN && requests[i].track <= head)) {
                        int seek_distance = abs(head - requests[i].track);
                        if (seek_distance < min_seek_distance) {
                            min_seek_distance = seek_distance;
                            next_request_index = i;
                        }
                    }
            }
        }
        // No request is ready to be served in the current direction
        if (next_request_index == -1) {
            int has_request_ready = 0; // Flag to check if there are any pending requests
            int next_time = -1; // Time of the next arriving request
            for (int i = 0; i < R; i++) {
                if (!requests[i].served) {
                    if (next_time == -1 || requests[i].arrival_time < next_time) {
                        next_time = requests[i].arrival_time;
                    }
                    if (requests[i].arrival_time <= current_time) {
                        has_request_ready = 1;
                    }
                }
            }
            // If there are no requests ready, move time to the next arriving request
            if (!has_request_ready) {
                current_time = next_time; // Move to the time of the next arriving request
                continue; // No more requests to serve yet
            }
            // Requests exist but in the wrong direction, so move the head to the end of the disk and reverse direction
            int target_track;
            if (direction == UP) {
                target_track = N - 1; // Move to the end of the disk
            } else {
                target_track = 0; // Move to the start of the disk
            }
            int seek_distance = abs(head - target_track); // Calculate the seek distance from the current head position to the end/start of the disk
            total_seek_time += seek_distance; // Accumulate the total seek time for moving to the end/start of the disk
            current_time += seek_distance; // Time taken to move the head to the end/start of the disk
            head = target_track; // Update the head position
            direction *= -1; // Reverse the head direction
            continue; // Check for requests again at the new current time
        }
        // Serve the next request
        int target_track = requests[next_request_index].track;
        int seek_distance = abs(head - target_track);
        total_seek_time += seek_distance;
        current_time += seek_distance; // Time taken to move the head to the target track
        head = target_track; // Update the head position
        requests[next_request_index].served = 1; // Mark the request as served
        total_completion_time = current_time; // Record the total completion time
        order[order_index++] = target_track; // Record the order of served requests
        requests_served_count++; // Increment the count of served requests
    }
    // Output the result
        for (int i = 0; i < order_index; i++) {
            printf("%d ", order[i]);
        }
        printf("\n%d\n", total_seek_time);
        printf("%d\n", total_completion_time);
}

void c_scan(struct Request requests[], int N, int R, int H, int direction) {
    int current_time = 0;
    int total_seek_time = 0;
    int total_completion_time = 0;
    int head = H;
    int order[R];
    int order_index = 0;
    int requests_served_count = 0;

    while (requests_served_count < R) {
        int next_request_index = -1;
        int min_seek_distance = 1000000; // Initialize to a large number
        // Find the next request to serve based on the current head direction
        for (int i = 0; i < R; i++) {
            if (!requests[i].served && requests[i].arrival_time <= current_time) {
                if ((direction == UP && requests[i].track >= head) ||
                    (direction == DOWN && requests[i].track <= head)) {
                        int seek_distance = abs(head - requests[i].track);
                        if (seek_distance < min_seek_distance) {
                            min_seek_distance = seek_distance;
                            next_request_index = i;
                        }
                    }
            }
        }
        // No request is ready to be served in the current direction
        if (next_request_index == -1) {
            int has_request_ready = 0; // Flag to check if there are any pending requests
            int next_time = -1; // Time of the next arriving request
            for (int i = 0; i < R; i++) {
                if (!requests[i].served) {
                    if (next_time == -1 || requests[i].arrival_time < next_time) {
                        next_time = requests[i].arrival_time;
                    }
                    if (requests[i].arrival_time <= current_time) {
                        has_request_ready = 1;
                    }
                }
            }
            // If there are no requests ready, move time to the next arriving request
            if (!has_request_ready) {
                current_time = next_time; // Move to the time of the next arriving request
                continue; // No more requests to serve yet
            }
            // Move the head to the end of the disk and wrap around to the start (C-SCAN)
            int end_track;
            if (direction == UP) {
                end_track = N - 1; // Move to the end of the disk
            } else {
                end_track = 0; // Move to the start of the disk
            }
            int seek_distance = abs(head - end_track); // Calculate the seek distance from the current head position to the end/start of the disk
            total_seek_time += seek_distance; // Accumulate the total seek time for moving to the end/start of the disk
            current_time += seek_distance; // Time taken to move the head to the end/start of the disk
            head = end_track; // Update the head position to the end/start of the disk
            // Wrap around to the opposite end of the disk
            int target_track;         
            if (direction == UP) {
                target_track = 0; // Wrap around to the start
            } else {
                target_track = N - 1; // Wrap around to the end
            }
            total_seek_time += (N - 1); // Accumulate the total seek time for moving from the end/start to the opposite end of the disk
            current_time += (N - 1); // Time taken to move the head from the end/start to the opposite end of the disk
            head = target_track; // Update the head position to the opposite end of the disk
            continue; // Check for requests again at the new current time
        }
        // Serve the next request
        int target_track = requests[next_request_index].track;
        int seek_distance = abs(head - target_track);
        total_seek_time += seek_distance;
        current_time += seek_distance; // Time taken to move the head to the target track
        head = target_track; // Update the head position
        requests[next_request_index].served = 1; // Mark the request as served
        total_completion_time = current_time; // Record the total completion time
        order[order_index++] = target_track; // Record the order of served requests
        requests_served_count++; // Increment the count of served requests
    }
    // Output the result
        for (int i = 0; i < order_index; i++) {
            printf("%d ", order[i]);
        }
        printf("\n%d\n", total_seek_time);
        printf("%d\n", total_completion_time);
}

void look(struct Request requests[], int N, int R, int H, int direction) {
    int current_time = 0;
    int total_seek_time = 0;
    int total_completion_time = 0;
    int head = H;
    int order[R];
    int order_index = 0;
    int requests_served_count = 0;

    while (requests_served_count < R) {
        int next_request_index = -1;
        int min_seek_distance = 1000000; // Initialize to a large number
        // Find the next request to serve based on the current head direction
        for (int i = 0; i < R; i++) {
            if (!requests[i].served && requests[i].arrival_time <= current_time) {
                if ((direction == UP && requests[i].track >= head) ||
                    (direction == DOWN && requests[i].track <= head)) {
                        int seek_distance = abs(head - requests[i].track);
                        if (seek_distance < min_seek_distance) {
                            min_seek_distance = seek_distance;
                            next_request_index = i;
                        }
                    }
            }
        }
        // No request is ready to be served in the current direction
        if (next_request_index == -1) {
            int has_request_ready = 0; // Flag to check if there are any pending requests
            int next_time = -1; // Time of the next arriving request
            for (int i = 0; i < R; i++) {
                if (!requests[i].served) {
                    if (next_time == -1 || requests[i].arrival_time < next_time) {
                        next_time = requests[i].arrival_time;
                    }
                    if (requests[i].arrival_time <= current_time) {
                        has_request_ready = 1;
                    }
                }
            }
            // If there are no requests ready, move time to the next arriving request
            if (!has_request_ready) {
                current_time = next_time; // Move to the time of the next arriving request
                continue; // No more requests to serve yet
            }
            // Requests exist but in the wrong direction, so reverse the head direction (LOOK)
            direction *= -1; // Reverse the head direction
            continue; // Check for requests again at the new current time
        }
        // Serve the next request
        int target_track = requests[next_request_index].track;
        int seek_distance = abs(head - target_track);
        total_seek_time += seek_distance;
        current_time += seek_distance; // Time taken to move the head to the target track
        head = target_track; // Update the head position
        requests[next_request_index].served = 1; // Mark the request as served
        total_completion_time = current_time; // Record the total completion time
        order[order_index++] = target_track; // Record the order of served requests
        requests_served_count++; // Increment the count of served requests
    }
    // Output the result
        for (int i = 0; i < order_index; i++) {
            printf("%d ", order[i]);
        }
        printf("\n%d\n", total_seek_time);
        printf("%d\n", total_completion_time);
}

void clook(struct Request requests[], int N, int R, int H, int direction) {
    // Implement CLOOK algorithm
}

void main() {
    char algorithm[10]; // Algorithm name
    int N; // Number of tracks
    int H; // Initial head position
    char head_direction[10]; // Head direction for SCAN, C-SCAN, LOOK and CLOOK
    int R; // Number of requests

    // Read input values
    scanf("%s %d %d", algorithm, &N, &H);

    // Read head direction only for SCAN, C-SCAN, LOOK and CLOOK algorithms
    if (strcmp(algorithm, "SCAN") == 0 || strcmp(algorithm, "C-SCAN") == 0 || strcmp(algorithm, "LOOK") == 0 || strcmp(algorithm, "CLOOK") == 0) {
        scanf("%s", head_direction);
    } else {
        head_direction[0] = '\0'; // No head direction needed for FCFS and SSTF
    }

    // Read the number of requests
    scanf("%d", &R);

    // Determine the head direction for SCAN, C-SCAN, LOOK and CLOOK algorithms
    int direction;
    if (head_direction[0] == 'U') {
        direction = 1;   // UP
    } else {
        direction = -1;  // DOWN
    }

    // Array to hold the requests
    struct Request requests[R];

    // Read the requests
    for (int i = 0; i < R; i++) {
        int request_number = i + 1;
        scanf("%d %d", &requests[i].arrival_time, &requests[i].track);
        requests[i].served = 0; // Initialize served status
    }

    printf("------------------------------\n");
    printf("Algorithm: %s\n", algorithm);
    printf("Number of tracks: %d\n", N);
    printf("Initial head position: %d\n", H);
    printf("Head direction: %s\n", head_direction);
    for (int i = 0; i < R; i++) {
        printf("Request %d: Arrival Time = %d, Track = %d\n", i + 1, requests[i].arrival_time, requests[i].track);
    }
    printf("------------------------------\n");

    // Call the appropriate scheduling algorithm based on the input
    if (strcmp(algorithm, "FCFS") == 0) {
        fcfs(requests, R, H);
    } else if (strcmp(algorithm, "SSTF") == 0) {
        sstf(requests, R, H);
    } 
    else if (strcmp(algorithm, "SCAN") == 0) {
        scan(requests, N, R, H, direction);
    } 
    else if (strcmp(algorithm, "C-SCAN") == 0) {
        c_scan(requests, N, R, H, direction);
    } 
    else if (strcmp(algorithm, "LOOK") == 0) {
        look(requests, N, R, H, direction);
    } 
    else if (strcmp(algorithm, "CLOOK") == 0) {
        clook(requests, N, R, H, direction);
    } 
    else {
        printf("Invalid algorithm name.\n");
    }
}