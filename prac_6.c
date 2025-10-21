#include <stdio.h>

typedef struct {
    int pid;
    int arr_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} process;

int main() {
    int n;
    printf("Enter Total Processes: ");
    scanf("%d", &n);

    process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the Arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].arr_time);
        printf("Enter the Burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arr_time > p[j].arr_time) {
                process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].waiting_time = 0;
    p[0].completion_time = p[0].arr_time + p[0].burst_time;
    p[0].turnaround_time = p[0].burst_time;

    for (int i = 1; i < n; i++) {
        if (p[i].arr_time > p[i - 1].completion_time)
            p[i].completion_time = p[i].arr_time + p[i].burst_time;
        else
            p[i].completion_time = p[i - 1].completion_time + p[i].burst_time;

        p[i].turnaround_time = p[i].completion_time - p[i].arr_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }

    float total_wait = 0, total_turnaround = 0;

    printf("\n====================================================================================\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    printf("====================================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n",
               p[i].pid, p[i].arr_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].completion_time);

        total_wait += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
    }
    printf("====================================================================================\n");

    printf("\nAverage Waiting Time: %.2f\n", total_wait / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}

/*
Output:
Enter Total Processes: 2
Enter the Arrival time for process 1: 1
Enter the Burst time for process 1: 4
Enter the Arrival time for process 2: 3
Enter the Burst time for process 2: 2

====================================================================================
PID	Arrival	Burst	Waiting	Turnaround	Completion
====================================================================================
1	1	4	0	4		5
2	3	2	2	4		7
====================================================================================

Average Waiting Time: 1.00
Average Turnaround Time: 4.00

*/