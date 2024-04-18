#include <stdio.h>
struct Process
{
    int pid;
    int burst_time;
    int priority;
};
void sortProcessesnp(int n, int bt[], int priority[], int pid[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (priority[j] < priority[j + 1])
            {
                // Swap burst times
                int temp_bt = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp_bt;

                // Swap priorities
                int temp_priority = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp_priority;

                // Swap process IDs
                int temp_pid = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp_pid;
            }
        }
    }
}

// Function to calculate turnaround time and waiting time
void calculateTimesnp(int n, int bt[], int wt[], int tat[])
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

// Function to implement Non-Preemptive Priority scheduling algorithm
void nonPreemptivePriority(int n, int bt[], int priority[], int p[])
{
    int wt[n], tat[n], pid[n];

    // Initialize process IDs
    for (int i = 0; i < n; i++)
    {
        pid[i] = p[i];
    }

    // Sort processes based on priority
    sortProcessesnp(n, bt, priority, pid);

    // Calculate waiting time and turnaround time
    calculateTimesnp(n, bt, wt, tat);

    
    writeOutputToFile(pid, n, tat, wt);
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
    int n; 
    char str[30];
    fscanf(inputFile, "%s", &str);

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
    for (int i = 0; i < 5; i++)
    {
        bt[i] = processes[i].burst_time;

        process[i] = processes[i].pid;
        priority[i] = processes[i].priority;
    }
    // Call the Non-Preemptive Priority function
    nonPreemptivePriority(n, bt, priority, process);

    return 0;
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
    printf("successfully written output into file");
    fclose(outputFile);
}