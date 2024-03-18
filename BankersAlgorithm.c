#include <stdio.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
int main() {
    int n = 5; 
    int m = 3; 
    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0}, 
        {2, 0, 0}, 
        {3, 0, 2}, 
        {2, 1, 1}, 
        {0, 0, 2}  
    };
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3}, 
        {3, 2, 2},
        {9, 0, 2}, 
        {2, 2, 2},
        {4, 3, 3}  
    };
    int avail[MAX_RESOURCES] = {3, 3, 2}; 
    int f[MAX_PROCESSES], ans[MAX_PROCESSES], ind = 0;
    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    int y = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                } } } }
    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The following system is not safe\n");
            break;
        }
    }
    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (int i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d\n", ans[n - 1]);
    }
    return 0;
}