#include <stdio.h>
#include <stdlib.h>
int page_fault(int a[], int frame[], int n, int no) {
    int i, j, is_available, count = 0, k;
    for (i = 0; i < no; i++) {
        frame[i] = -1;
    }
    j = 0;
    for (i = 0; i < n; i++) {
        is_available = 0; 
        for (k = 0; k < no; k++) {
            if (frame[k] == a[i]) {
                is_available = 1;
                break;
            }
        }
        if (is_available == 0) {
            frame[j] = a[i];
            j = (j + 1) % no;
            count++;
        }
    }
    return count;
}
int main() {
    int n, i, *a, *frame, no, fault;
    printf("\nENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);
    a = (int *)malloc(n * sizeof(int));
    printf("ENTER THE PAGE NUMBERS:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("ENTER THE NUMBER OF FRAMES :");
    scanf("%d", &no);
    frame = (int *)malloc(no * sizeof(int));
    fault = page_fault(a, frame, n, no);
    printf("Page Faults: %d", fault);
    free(a);
    free(frame);

    return 0;
}
