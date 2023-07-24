#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

int randomCi(){   //For Ci, it generates a random number between 1 and 3
    float x;
    x = ((float)rand())/RAND_MAX*3+1;
    return (int)x;
}

int randomDi(){   //For di, it generates a random number between 1 and 10
    float x;
    x = ((float)rand())/RAND_MAX*10+1;
    return (int)x;
}

int randomPe(){   //For di, it generates a random number between 1 and 10
    float x;
    x = ((float)rand())/RAND_MAX*10+1;
    return (int)x;
} 

int main() {
    int gennum, gen_ci=0, gen_deadl=0, gen_pe=0;
    char choice;
    int totalRuns = 0;
    int dmsFeasibleRuns = 0;
    int rmsFeasibleRuns = 0;
    
    srand(time(0));

    do {
        
        float x;
        x = ((float)rand())/RAND_MAX*20+1;
        gennum = (int)x;
        
        printf("Number of tasks was generated to be %d", gennum);
        
        if (gennum <= 0 || gennum > MAX_TASKS) {
            printf("Invalid number of tasks.");
            return 1;
        }

        // Array of structs to store the attributes of each task
        struct Task tasks[MAX_TASKS];

        printf("\nAttributes for each task will now be generated:");

        for (int i = 0; i < gennum; i++) {
            printf("\n\nTask %d: ", i + 1);

            gen_ci = randomCi();
            
            printf("\nComputation time for Task %d: %d", i + 1, gen_ci);
            tasks[i].computationTime = gen_ci;
           
            gen_deadl = randomDi();

            printf("\nDeadline for Task %d: %d", i + 1, gen_deadl);
            tasks[i].deadline = gen_deadl;
            
            gen_pe = randomPe();

            printf("\nPeriod for Task %d: %d", i + 1, gen_pe);
            tasks[i].period = gen_pe;
        }

        // Check feasibility using DMS and RMS algorithms
        int feasibleDMS = isFeasibleDMS(tasks, gennum);
        int feasibleRMS = isFeasibleRMS(tasks, gennum);

        // Display feasibility results
        if (feasibleDMS) {
            printf("\n\nTask set is feasible under Deadline Monotonic Scheduling (DMS).\n");
            dmsFeasibleRuns++;
        }
        else {
            printf("\n\nTask set is not feasible under Deadline Monotonic Scheduling (DMS).\n");
        }

        if (feasibleRMS) {
            printf("Task set is feasible under Rate Monotonic Scheduling (RMS).\n");
            rmsFeasibleRuns++;
        }
        else {
            printf("Task set is not feasible under Rate Monotonic Scheduling (RMS).\n");
        }

        totalRuns++;

        printf("\nDo you want to run again? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    // Calculate and display the percentages
    float dmsFeasiblePercentage = ((float)dmsFeasibleRuns / totalRuns) * 100;
    float rmsFeasiblePercentage = ((float)rmsFeasibleRuns / totalRuns) * 100;

    printf("\nFeasibility Summary after %d runs:\n", totalRuns);
    printf("DMS Feasible Percentage: %.2f%%\n", dmsFeasiblePercentage);
    printf("RMS Feasible Percentage: %.2f%%\n", rmsFeasiblePercentage);

    return 0;
}