// code to simulate bankers problem additional resource allocation

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, i, j, k, pno;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    int alloc[n][m], maxmat[n][m], need[n][m], avail[m], finish[n], sequence[n];
    printf("Enter allocation matrix: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("Enter max matrix: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &maxmat[i][j]);
        }
    }
    printf("Enter available matrix: \n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = maxmat[i][j] - alloc[i][j];
        }
    }
    printf("Enter process number for additional resource request: ");
    scanf("%d", &pno);
    int request[m];
    printf("Enter request vector: \n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &request[i]);
    }
    int flagn = 0;
    for (i = 0; i < m; i++)
    {
        if (request[i] > need[pno][i])
        {
            flagn = 1;
            break;
        }
    }
    if (flagn == 1)
    {
        printf("System failure!\n");
    }
    int flaga = 0;
    for (i = 0; i < m; i++)
    {
        if (request[i] > avail[i])
        {
            flaga = 1;
            break;
        }
    }
    if (flaga == 1)
    {
        printf("Resources not available!\n");
    }
    if (flagn == 0 && flaga == 0)
    {
        for (i = 0; i < m; i++)
        {
            alloc[pno][i] += request[i];
            avail[i] -= request[i];
            need[pno][i] -= request[i];
        }
        int count = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (finish[j] == 0)
                {
                    int flag = 0;
                    for (k = 0; k < m; k++)
                    {
                        if (need[j][k] > avail[k])
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        sequence[count++] = j;
                        finish[j] = 1;
                        for (k = 0; k < m; k++)
                        {
                            avail[k] += alloc[j][k];
                        }
                    }
                }
            }
        }
        int flag = 0;
        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                flag = 1;
                printf("Request Not Granted\n");
                break;
            }
        }
        if (flag == 0)
        {
            printf("Request Granted\n");
            printf("Safe sequence: ");
            for (i = 0; i < n; i++)
            {
                printf("P%d ", sequence[i]);
            }
            printf("\n");
        }
    }
}