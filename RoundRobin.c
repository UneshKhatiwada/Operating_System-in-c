#include <stdio.h>
#define MAX_PROCESSES 10
typedef struct {
    int id;
    int at; 
    int bt; 
    int rt; 
    int ct; 
    int tat;
    int wt;
} Proc;
void rr_sched(Proc p[], int n, int quantum) {
    int rem_procs = n;
    int current_time = 0;

    while (rem_procs > 0) {
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                int exec_time = (p[i].rt < quantum) ? p[i].rt : quantum;
                p[i].rt -= exec_time;
                current_time += exec_time;

                p[i].ct = current_time;

                if (p[i].rt == 0) {
                    rem_procs--;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}
int main() {
    Proc p[MAX_PROCESSES];
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the quantum time: ");
    scanf("%d", &quantum);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Process %d Arrival Time: ", p[i].id);
        scanf("%d", &p[i].at);
        printf("Process %d Burst Time: ", p[i].id);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("\nRound-Robin Scheduling:\n");
    rr_sched(p, n, quantum);

    // Output results
    printf("\nPid\tA.T\tB.T\tC.T\tT.A.T\tW.T\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
    return 0;
}
