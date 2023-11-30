#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    int *bt = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));

    printf("Enter the burst time for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    int t = 0;

    for (int i = 0; i < n; i++)
    {
        wt[i] = t;
        t += bt[i];
        tat[i] = t;
    }

    printf("Process\t\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    float avg_wt = 0;
    float avg_tat = 0;
    for (int i = 0; i < n; i++)
    {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("Average waiting time: %f\n", avg_wt);
    printf("Average turnaround time: %f\n", avg_tat);
    return 0;
}
