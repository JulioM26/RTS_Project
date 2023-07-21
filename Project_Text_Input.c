#include <stdio.h>

#define MAX_TASKS 20 // Maximum number of tasks

// Struct to represent a task with its attributes
struct Task {
    int computationTime;
    int deadline;
    int period;
};

// Function to perform Deadline Monotonic Scheduling (DMS) feasibility test
int isFeasibleDMS(struct Task tasks[], int numTasks) {
    // Sort tasks based on deadlines (using bubble sort)
    for (int i = 0; i < numTasks - 1; i++) {
        for (int j = 0; j < numTasks - i - 1; j++) {
            if (tasks[j].deadline > tasks[j + 1].deadline) {
                // Swap tasks[j] and tasks[j + 1]
                struct Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    int currentTime = 0;

    for (int i = 0; i < numTasks; i++) {
        currentTime += tasks[i].computationTime;
        if (currentTime > tasks[i].deadline) {
            return 0; // Task set is not feasible under DMS
        }
    }

    return 1; // Task set is feasible under DMS
}

// Function to perform Rate Monotonic Scheduling (RMS) feasibility test
int isFeasibleRMS(struct Task tasks[], int numTasks) {
    // Sort tasks based on periods (using bubble sort)
    for (int i = 0; i < numTasks - 1; i++) {
        for (int j = 0; j < numTasks - i - 1; j++) {
            if (tasks[j].period > tasks[j + 1].period) {
                // Swap tasks[j] and tasks[j + 1]
                struct Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    int currentTime = 0;

    for (int i = 0; i < numTasks; i++) {
        currentTime += tasks[i].computationTime;
        if (currentTime > tasks[i].period) {
            return 0; // Task set is not feasible under RMS
        }
    }

    return 1; // Task set is feasible under RMS
}

int main() {
    
    int numTasks;
    char choice;
    int totalRuns = 0;
    int dmsFeasibleRuns = 0;
    int rmsFeasibleRuns = 0;
    
    // Array of structs to store the attributes of each task
    struct Task tasks[MAX_TASKS];

    //Opening .txt file to read the input
    FILE*file;
    file=fopen("file.txt", "r");

    int i=0;
    
    char str[120];

    //Reading the file and storing each Computation time, deadline and period in the struct
    
        fscanf(file, "%s %s %s", str, str, str);    
        while(!feof(file)){      
            fscanf(file, "%s %d %d %d", str, &tasks[i].computationTime, &tasks[i].deadline, &tasks[i].period);
            i++;
    }
        numTasks = i;
        
        if (numTasks <= 0 || numTasks > MAX_TASKS) {
            printf("Invalid number of tasks. Please enter a value between 1 and %d.\n", MAX_TASKS);
            return 1;
        }
        
        // Check feasibility using DMS and RMS algorithms
        int feasibleDMS = isFeasibleDMS(tasks, numTasks);
        int feasibleRMS = isFeasibleRMS(tasks, numTasks);

        // Display feasibility results
        if (feasibleDMS) {
            printf("\nTask set is feasible under Deadline Monotonic Scheduling (DMS).\n");
            dmsFeasibleRuns++;
        }
        else {
            printf("\nTask set is not feasible under Deadline Monotonic Scheduling (DMS).\n");
        }

        if (feasibleRMS) {
            printf("Task set is feasible under Rate Monotonic Scheduling (RMS).\n");
            rmsFeasibleRuns++;
        }
        else {
            printf("Task set is not feasible under Rate Monotonic Scheduling (RMS).\n");
        }

        totalRuns++;

/*
    // Calculate and display the percentages
    float dmsFeasiblePercentage = ((float)dmsFeasibleRuns / totalRuns) * 100;
    float rmsFeasiblePercentage = ((float)rmsFeasibleRuns / totalRuns) * 100;

    printf("\nFeasibility Summary after %d runs:\n", totalRuns);
    printf("DMS Feasible Percentage: %.2f%%\n", dmsFeasiblePercentage);
    printf("RMS Feasible Percentage: %.2f%%\n", rmsFeasiblePercentage);
*/

    return 0;
}
