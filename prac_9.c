#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;          
    int arrival_time; 
    int burst_time;    
    int priority;       
    int waiting_time;     
    int turnaround_time; 
    int completion_time;  
    bool completed;      
};

int main() {
    int n, time = 0, completed = 0;
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
        printf("Enter Priority for P%d (Lower number = Higher priority): ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].completed = false;
    }

    printf("\n=============================================================\n");

    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    idx = i;
                }
                else if (p[i].priority == highest_priority) {
                    if (p[i].arrival_time < p[idx].arrival_time)
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

    printf("\n%-10s%-15s%-15s%-15s%-15s%-15s\n", 
           "PID", "Arrival", "Burst", "Priority", "Waiting", "Turnaround");
    for (int i = 0; i < n; i++) {
        printf("%-10d%-15d%-15d%-15d%-15d%-15d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}

/*
Enter number of processes: 3

Enter Arrival Time for P1: 0
Enter Burst Time for P1: 6
Enter Priority for P1 (Lower number = Higher priority): 2

Enter Arrival Time for P2: 4
Enter Burst Time for P2: 2
Enter Priority for P2 (Lower number = Higher priority): 1

Enter Arrival Time for P3: 7
Enter Burst Time for P3: 9
Enter Priority for P3 (Lower number = Higher priority): 3

=============================================================
 | P1 | | P2 | | P3 |
========================================================

PID       Arrival        Burst          Priority       Waiting        Turnaround     
1         0              6              2              0              6              
2         4              2              1              2              4              
3         7              9              3              1              10             

Average Waiting Time: 1.00
Average Turnaround Time: 6.67
*/