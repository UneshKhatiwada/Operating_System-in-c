#include <stdio.h>
#define MAX 25

int main() {
    int frag[MAX], b[MAX], f[MAX], i, j, nb, nf, temp, last_allocated = 0;

    printf("\n\tMemory Management Scheme - Next Fit");

    // Input the number of blocks
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);

    // Input the number of files
    printf("Enter the number of files: ");
    scanf("%d", &nf);

    // Input the size of the blocks
    printf("\nEnter the size of the blocks:\n");
    for (i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
    }

    // Input the size of the files
    printf("Enter the size of the files:\n");
    for (i = 1; i <= nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &f[i]);
    }

    // Next Fit allocation
    for (i = 1; i <= nf; i++) {
        temp = -1;
        for (j = last_allocated + 1; j <= nb; j++) {
            if (b[j] >= f[i]) {
                temp = j;
                last_allocated = j;
                break;
            }
        }
        if (temp == -1) {
            // If not found in the remaining blocks, search from the beginning
            for (j = 1; j <= last_allocated; j++) {
                if (b[j] >= f[i]) {
                    temp = j;
                    last_allocated = j;
                    break;
                }
            }
        }
        frag[i] = (temp == -1) ? -1 : b[temp] - f[i];
    }

    // Display allocation details
    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment\n");
    for (i = 1; i <= nf; i++) {
        if (frag[i] != -1)
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, f[i], last_allocated, b[last_allocated], frag[i]);
        else
            printf("%d\t\t%d\t\t%s\n", i, f[i], "Not Allocated");
    }

    return 0;
}