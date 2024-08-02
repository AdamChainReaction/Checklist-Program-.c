#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TASKS 100 

typedef struct {
    char name[255];
    bool completed;
} Task;

// Function prototypes
void addTask();
void rmTask();
void listTasks();
void completeTask();
void editTaskName();
void listActions();
int getChoice();
void saveTasks();
void loadTasks();

// Global variables
Task tasks[MAX_TASKS];
int taskCounter = 0; 

int main() {

    printf("\nLoading . . .\n");
    loadTasks();
    bool shouldExit = false;
    short int choice;

    printf("|===========================================|\n|================= WELCOME =================|\n|===========================================|");
    printf("\nYou can pick what to do using the action number");
    printf("\nPlease do not add any spaces after your choice");

    while (!shouldExit) {
        listActions();
        choice = getChoice();

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                rmTask();
                break;
            case 3:
                listTasks();
                break;
            case 4:
                completeTask();
                break;
            case 5:
                editTaskName();
                break;
            case 6:
                shouldExit = true;
                break;
            default:
                printf("! Please enter a valid action number !\n");
                break;
        }
    }
    printf("\nSaving tasks. . .");
    saveTasks();
    printf("\nTasks saved successfully !\n");
    printf("\nGoodbye !\n");

    return 0;
}

void addTask() {
    if (taskCounter >= MAX_TASKS) {
        printf("\nTask list is FULL! Delete some tasks first.\n");
        return;
    }

    char taskName[255];

    printf("\nPick a name for the task");
    printf("\n==> ");
    fgets(taskName, sizeof(taskName), stdin);

    size_t len = strlen(taskName);
    if (len > 0 && taskName[len - 1] == '\n') {
        taskName[len - 1] = '\0';
    }

    Task task;
    strncpy(task.name, taskName, sizeof(task.name) - 1);
    task.name[sizeof(task.name) - 1] = '\0';
    task.completed = false;

    tasks[taskCounter++] = task;
}

void rmTask() {
    int index;

    printf("\nEnter the task number to remove");
    printf("\n==> ");
    scanf("%d", &index);

    if (index >= 1 && index <= taskCounter) {
        for (int i = index - 1; i < taskCounter - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        taskCounter--;
    } else {
        printf("Invalid task number.\n");
    }
}

void listTasks() {
    for (int i = 0; i < taskCounter; i++) {
        printf("\n%d. %s [%s]", i + 1, tasks[i].name, tasks[i].completed ? "Completed" : "Pending");
    }
    printf("\n");
}

void completeTask(){
    int index;

    printf("\nEnter the task number to complete");
    printf("\n==> ");
    scanf("%d", &index);

    tasks[index - 1].completed = true;
}

void editTaskName(){

    char newName[255];
    int index;

    printf("\nEnter the task number to edit");
    printf("\n==> ");
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= taskCounter) {
        printf("\nEnter the new name for the task");
        printf("\n==> ");
        fgets(newName, sizeof(newName), stdin);

        size_t len = strlen(newName);
        if (len > 0 && newName[len - 1] == '\n') {
            newName[len - 1] = '\0';
        }

        
        strncpy(tasks[index - 1].name, newName, sizeof(tasks[index - 1].name) - 1);
        tasks[index - 1].name[sizeof(tasks[index - 1].name) - 1] = '\0';

        printf("Task %d name updated to: %s\n", index, tasks[index - 1].name);
    } else {
        printf("Invalid task number.\n");
    }
}

void saveTasks() {
    FILE *pF = fopen("storage.txt", "w");

    if (pF == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < taskCounter; i++) {
        fprintf(pF, "%s|%d", tasks[i].name, tasks[i].completed);
        if (i < taskCounter - 1) {
            fprintf(pF, "#"); 
        }
    }

    fclose(pF);
}

void loadTasks() {
    FILE *pF = fopen("storage.txt", "r"); 

    if (pF == NULL) {
        perror("Error opening file for reading");
        return;
    }

    char line[1024]; 
    while (fgets(line, sizeof(line), pF)) {
        char *token;
        char *rest = line;

        while ((token = strtok_r(rest, "#", &rest))) {
            Task task;
            char *name = strtok(token, "|");
            char *completedStr = strtok(NULL, "|");

            if (name && completedStr) {
                strncpy(task.name, name, sizeof(task.name) - 1);
                task.name[sizeof(task.name) - 1] = '\0'; 
                task.completed = atoi(completedStr);

                if (taskCounter < MAX_TASKS) {
                    tasks[taskCounter++] = task;
                } else {
                    printf("Task list is full!\n");
                }
            }
        }
    }

    fclose(pF);
}

void listActions() {
    printf("\n1. Add a Task");
    printf("\n2. Delete Task");
    printf("\n3. List Tasks");
    printf("\n4. Complete Task");
    printf("\n5. Edit Task Name");
    printf("\n6. EXIT");
    printf("\n==> ");
}

int getChoice() {
    short int container;
    scanf("%hd", &container);
    while (getchar() != '\n');
    return container;
}
