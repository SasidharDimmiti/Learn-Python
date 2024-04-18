#include <stdio.h>
struct Process
{
    int pid;
    int burst_time;
    int priority;
};
// Function to calculate minimum of two integers
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// Function to calculate turnaround time and waiting time using Round Robin algorithm
void calculateTimes(int n, int bt[], int wt[], int tat[], int quantum, int remaining_time[], int p[])
{

    int t = 0; // Current time

    // Continue until all processes are done
    while (1)
    {
        int done = 1;     // Flag to check if any process is remaining
        int executed = 0; // Flag to check if any process was executed in the current iteration

        // Traverse all processes
        for (int i = 0; i < n; i++)
        {
            // If remaining time for the current process is greater than 0
            if (remaining_time[i] > 0)
            {
                done = 0; // There is a pending process

                // If burst time is greater than quantum, execute for quantum time
                if (remaining_time[i] > quantum)
                {
                    printf("Executing process P%d for time quantum %d\n", p[i], quantum);
                    // fprintf(outputFile, "%d\t\t %d\t\t %d\n", p[i], turnaround_time[i], waiting_time[i]);
                    t += quantum;
                    remaining_time[i] -= quantum;
                }
                // If burst time is smaller than or equal to quantum, execute for remaining burst time
                else
                {
                    printf("Executing process P%d for remaining time %d\n", p[i], remaining_time[i]);
                    t += remaining_time[i];
                    wt[i] = t - bt[i]; // Waiting time is current time minus original burst time
                    remaining_time[i] = 0;
                    tat[i] = t; // Turnaround time is current time
                }
                executed = 1; // Mark process as executed
            }
        }

        // If no process was executed in the current iteration, break the loop
        if (done == 1)
            break;
        if (executed == 0)
            printf("Idle\n");
    }
}

int main()
{
    int quantum;

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

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

    // struct Process processes[n];

    n = 0;
    struct Process processes[100];
    while (fscanf(inputFile, "%d %d %d", &processes[n].pid, &processes[n].burst_time, &processes[n].priority) == 3)
    {
        n++;
    }
    int turnaround_time[n];
    int waiting_time[n];
    int wt[n], tat[n], remaining_time[n];

    /*for (int i = 0; i < n; i++)
    {
        fscanf(inputFile, "%d, %d, %d", &processes[i].pid, &processes[i].burst_time, &processes[i].priority);
    }*/

    fclose(inputFile);

    // calculateTurnaroundWaitingTime(processes, n, turnaround_time, waiting_time);
    int bt[n], priority[n], process[n];
    for (int i = 0; i < 5; i++)
    {
        bt[i] = processes[i].burst_time;

        process[i] = processes[i].pid;
        priority[i] = processes[i].priority;
        remaining_time[i] = bt[i];
    }
    // Calculate waiting time and turnaround time
    calculateTimes(n, bt, wt, tat, quantum, remaining_time, process);

    // Print waiting time and turnaround time for each process
   printf("successfully written output into the file ");
    writeOutputToFile(process, n, tat, wt);

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

    fclose(outputFile);
}