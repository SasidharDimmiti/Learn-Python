#include <stdio.h>

struct Process 
{
    int pid;
    int burst_time;
    int priority;
};

void calculateTurnaroundWaitingTime(struct Process processes[], int n, int turnaround_time[], int waiting_time[])
{
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;

    for (int i = 1; i < n; i++)
    {
        printf("p -> %d\n", processes[i]);
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

void writeOutputToFile(int processes[], int n, int turnaround_time[], int waiting_time[])
{
    FILE *outputFile;
    outputFile = fopen("output.txt", "w");

    if (outputFile == NULL)
    {
        printf("Error opening output file!\n");
        return;
    }
    fprintf(outputFile, "Process\t\tTurnaround_Time\t\tWaiting_Time\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d\t\t %d\t\t %d\n", processes[i], turnaround_time[i], waiting_time[i]);
    }

    fclose(outputFile);
}

int main()
{
    FILE *inputFile;
    inputFile = fopen("input.txt", "r");

    if (inputFile == NULL)
    {
        printf("Error opening input file!\n");
        return 1;
    }
    int n; // number of processes
    // fscanf(inputFile, "%d", &n);
    // printf("%d ff ", n);
    char str[30];
    fscanf(inputFile, "%s", &str);
    printf("%s\n", str);

    struct Process processes[100];

    n = 0;
    while (fscanf(inputFile, "%d %d %d", &processes[n].pid, &processes[n].burst_time, &processes[n].priority) == 3)
    {
        n++;
    }
    int turnaround_time[n];
    int waiting_time[n];
    

    fclose(inputFile);

    // calculateTurnaroundWaitingTime(processes, n, turnaround_time, waiting_time);
    int bt[n], priority[n], process[n];
   // printf("  \n  ");
    for (int i = 0; i < 5; i++)
    {
        bt[i] = processes[i].burst_time;

        process[i] = processes[i].pid;
        priority[i] = processes[i].priority;
    }

    fcfs(n, bt, priority, process);
printf("Data Stored into Output file");
    // writeOutputToFile(process, n, turnaround_time, waiting_time);

    return 0;
}

void calculateTimes(int n, int bt[], int wt[], int tat[])
{
    wt[0] = 0; // Waiting time for the first process is 0

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to implement FCFS scheduling algorithm with priorities
void fcfs(int n, int bt[], int priority[], int p[])
{
    int wt[n], tat[n];
    int process[n];

    // Initialize process array
    for (int i = 0; i < n; i++)
    {
        process[i] = p[i];
        //  printf("test %d\n", process[i]);
    }

    // Sort processes based on their priorities (using Selection Sort)
    for (int i = 0; i < n - 1; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (priority[j] > priority[max_index])
            {
                max_index = j;
            }
        }
        // Swap priority
        int temp = priority[i];
        priority[i] = priority[max_index];
        priority[max_index] = temp;

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[max_index];
        bt[max_index] = temp;

        // Swap process index
        temp = process[i];
        process[i] = process[max_index];
        process[max_index] = temp;
    }

    // Calculate waiting time and turnaround time
    calculateTimes(n, bt, wt, tat);

    // Print waiting time and turnaround time for each process
   /* printf("Process\t\tBurst_Time\t\tPriority\t\tWaiting_Time\t\tTurnaround_Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", process[i], bt[i], priority[i], wt[i], tat[i]);
    }*/
    // start
    writeOutputToFile(process, n, tat, wt);
    // end
}