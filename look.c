#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define DISK_SIZE 200

void LOOK(int arr[], int head, char* direction) {
    int seek_count = 0;
    int distance, cur_track;
    int left[SIZE], right[SIZE];
    int left_size = 0, right_size = 0;
    int seek_sequence[SIZE * 2]; // Maximum possible size

    // Appending values which are currently at left and right direction from the head
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] < head)
            left[left_size++] = arr[i];
        if (arr[i] > head)
            right[right_size++] = arr[i];
    }

    // Sorting left and right arrays for servicing tracks in the correct sequence
    qsort(left, left_size, sizeof(int), cmpfunc);
    qsort(right, right_size, sizeof(int), cmpfunc);

    // Run the loop two times, one by one scanning right and left side of the head
    int run = 2;
    while (run--) {
        if (strcmp(direction, "left") == 0) {
            for (int i = left_size - 1; i >= 0; i--) {
                cur_track = left[i];

                // Appending current track to seek sequence
                seek_sequence[seek_count++] = cur_track;

                // Calculate absolute distance
                distance = abs(cur_track - head);

                // Increase the total count
                seek_count += distance;

                // Accessed track is now the new head
                head = cur_track;
            }
            // Reversing the direction
            direction = "right";
        } else if (strcmp(direction, "right") == 0) {
            for (int i = 0; i < right_size; i++) {
                cur_track = right[i];

                // Appending current track to seek sequence
                seek_sequence[seek_count++] = cur_track;

                // Calculate absolute distance
                distance = abs(cur_track - head);

                // Increase the total count
                seek_count += distance;

                // Accessed track is now new head
                head = cur_track;
            }
            // Reversing the direction
            direction = "left";
        }
    }

    printf("Total number of seek operations = %d\n", seek_count);
    printf("Seek Sequence is:\n");

    for (int i = 0; i < seek_count; i++) {
        printf("%d\n", seek_sequence[i]);
    }
}

int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    // Request array
    int arr[SIZE] = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;
    char* direction = "right";

    printf("Initial position of head: %d\n", head);

    LOOK(arr, head, direction);

    return 0;
}