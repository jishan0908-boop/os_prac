#include <stdio.h>
#include <pthread.h>

#define MAX 1000      // maximum number of elements
#define THREAD_MAX 4  // number of threads

int arr[MAX];         // array of numbers
int n;                // total numbers
int sum[THREAD_MAX];  // partial sums by each thread
int part = 0;         // used to divide array among threads

void* sum_array(void* arg)
{
    int thread_part = part++;

    int start = thread_part * (n / THREAD_MAX);
    int end = (thread_part + 1) * (n / THREAD_MAX);

    sum[thread_part] = 0;

    for (int i = start; i < end; i++) {
        sum[thread_part] += arr[i];
    }

    return NULL;
}

int main()
{
    printf("Enter total number of elements (<= %d): ", MAX);
    scanf("%d", &n);

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pthread_t threads[THREAD_MAX];

    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&threads[i], NULL, sum_array, NULL);


    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);

    int total_sum = 0;
    for (int i = 0; i < THREAD_MAX; i++)
        total_sum += sum[i];

    printf("\nTotal Sum = %d\n", total_sum);

    return 0;
}

/*
Enter total number of elements (<= 1000): 5
Enter 5 numbers:
10
23
34
2
3

Total Sum = 67

*/