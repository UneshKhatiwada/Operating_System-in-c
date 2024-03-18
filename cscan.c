#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define DISK_SIZE 200

void CSCAN(int arr[], int head) {
    int seek_count = 0;
    int distance, cur_track;
    int left[SIZE + 1], right[SIZE + 1];
    int left_size = 0, right_size = 0;
    int seek_sequence[SIZE * 2 + 1]; // Maximum possible size

    // Appending end values which have to be visited before reversing the direction
    left[left_size++] = 0;
    right[right_size++] = DISK_SIZE - 1;

    // Tracks on the left of the head will be serviced once the head comes back to the beginning (left end).
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] < head)
            left[left_size++] = arr[i];
        if (arr[i] > head)
            right[right_size++] = arr[i];
    }

    // Sorting left and right arrays for servicing tracks in the correct sequence
    qsort(left, left_size, sizeof(int), cmpfunc);
    qsort(right, right_size, sizeof(int), cmpfunc);

    // First service the requests on the right side of the head
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

    // Once reached the right end, jump to the beginning.
    head = 0;

    // Adding seek count for head returning from DISK_SIZE - 1 to 0
    seek_count += (DISK_SIZE - 1);

    // Now service the requests again which are left
    for (int i = 0; i < left_size; i++) {
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

    printf("Initial position of head: %d\n", head);
    CSCAN(arr, head);

    return 0;
}