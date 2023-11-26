#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Enter the number of processes: ");
    int n;
    scanf("%d", &n);
    int *bt = (int *)malloc(n * sizeof(int));
    int *priority = (int *)malloc(n * sizeof(int));
    int *p_id = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));

    printf("Enter the burst time for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    printf("Enter the priority for each process: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &priority[i]);
    }

    for (int i = 0; i < n; i++)
    {
        p_id[i] = i + 1;
    }

    // selection sort

    for (int i = 0; i < n - 1; i++)
    {
        int min = priority[i];
        int min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (priority[j] < min)
            {
                min = priority[j];
                min_index = j;
            }
        }
        int temp = priority[i];
        priority[i] = priority[min_index];
        priority[min_index] = temp;

        temp = bt[i];
        bt[i] = bt[min_index];
        bt[min_index] = temp;

        temp = p_id[i];
        p_id[i] = p_id[min_index];
        p_id[min_index] = temp;
    }

    int t = 0;
    int done = 0;

    while (done != n)
    {
        for (int i = 0; i < n; i++)
        {
            t += bt[i];
            tat[i] = t;
            wt[i] = tat[i] - bt[i];
            done++;
        }
    }

    printf("Process ID\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p_id[i], bt[i], priority[i], tat[i], wt[i]);
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