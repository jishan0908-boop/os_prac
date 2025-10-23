#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    bool completed;
};

int main() {
    int n, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    struct Process p[20];

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time of P%d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time of P%d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].completed = false;
    }

    printf("\n==========================================================\n");

    while (completed < n) {
        int idx = -1;
        int min_burst = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; 
        } else {
            printf(" | P%d |", p[idx].pid);
            time += p[idx].burst_time;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].completed = true;
            completed++;

            total_wt += p[idx].waiting_time;
            total_tat += p[idx].turnaround_time;
        }
    }

    printf("\n========================================================\n");

    printf("\n%-10s%-15s%-15s%-15s%-15s\n", 
           "PID", "Arrival", "Burst", "Waiting", "Turnaround");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-15d%-15d\n", 
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}


/*
Enter total number of processes: 3

Enter Arrival Time of P1: 2
Enter Burst Time of P1: 4

Enter Arrival Time of P2: 5
Enter Burst Time of P2: 13

Enter Arrival Time of P3: 7
Enter Burst Time of P3: 3

==========================================================
 | P1 | | P2 | | P3 |
========================================================

PID       Arrival        Burst          Waiting        Turnaround     
1         2              4              0              4              
2         5              13             1              14             
3         7              3              12             15             

Average Waiting Time: 4.33
Average Turnaround Time: 11.00
*/
