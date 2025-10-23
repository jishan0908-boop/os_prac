#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;          
    int arrival_time;    
    int burst_time;    
    int remaining_time; 
    int waiting_time;   
    int turnaround_time;  
    int completion_time;
    bool completed;      
};

int main() {
    int n, completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0;
    struct Process p[20];
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }
    
    printf("\n====================================================\n");

    while (completed != n) {
        int idx = -1;
        int min_remaining = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].completed) {
                if (p[i].remaining_time < min_remaining) {
                    min_remaining = p[i].remaining_time;
                    idx = i;
                }
                else if (p[i].remaining_time == min_remaining) {
                    if (p[i].arrival_time < p[idx].arrival_time)
                        idx = i;
                }
            }
        }

        if (idx != -1) {
            printf(" | P%d |", p[idx].pid);
            p[idx].remaining_time--;
            current_time++;

            if (p[idx].remaining_time == 0) {
                p[idx].completed = true;
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                total_wt += p[idx].waiting_time;
                total_tat += p[idx].turnaround_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    printf("\n========================================================\n");

    printf("\n%-10s%-15s%-15s%-15s%-15s%-15s\n",
           "PID", "Arrival", "Burst", "Waiting", "Turnaround", "Completion");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-15d%-15d%-15d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].completion_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}

/*
Enter number of processes: 3

Enter Arrival Time for P1: 1
Enter Burst Time for P1: 5

Enter Arrival Time for P2: 3
Enter Burst Time for P2: 10

Enter Arrival Time for P3: 4
Enter Burst Time for P3: 3

====================================================
 | P1 | | P1 | | P1 | | P1 | | P1 | | P3 | | P3 | | P3 | | P2 | | P2 | | P2 | | P2 | | P2 | | P2 | | P2 | | P2 | | P2 | | P2 |
========================================================

PID       Arrival        Burst          Waiting        Turnaround     Completion     
1         1              5              0              5              6              
2         3              10             6              16             19             
3         4              3              2              5              9              

Average Waiting Time: 2.67
Average Turnaround Time: 8.67

*/
