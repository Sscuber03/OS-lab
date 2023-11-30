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
    int *p_id = (int *)malloc(n * sizeof(int));
    int *completed = (int *)malloc(n * sizeof(int));

    printf("Enter the burst time for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n; i++)
    {
        p_id[i] = i + 1;
    }

    int t = 0, min_idx, min_bt;
    int done = 0;

    while (done < n)
    {
        min_idx = -1;
        min_bt = 100;
        for (int i = 0; i < n; i++)
        {
            if (bt[i] < min_bt && completed[i] == 0)
            {
                min_idx = i;
                min_bt = bt[i];
            }
        }
        if (min_idx != -1)
        {
            wt[min_idx] = t;
            t += bt[min_idx];
            tat[min_idx] = t;
            completed[min_idx] = 1;
            done++;
        }
    }

    printf("Process\t\tBurst Time\tWaiting Time\tTurnaround Time\n");  
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", p_id[i], bt[i], wt[i], tat[i]);
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