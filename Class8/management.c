#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float gpa;
};

void addStudent(struct Student **students, int *count) {
    // Allocate memory for a new student
    *students = realloc(*students, (*count + 1) * sizeof(struct Student));

    if(*students == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    printf("Enter student name: ");
    scanf("%s", (*students)[*count].name);
    printf("Enter student age: ");
    scanf("%d", &(*students)[*count].age);
    printf("Enter student GPA: ");
    scanf("%f", &(*students)[*count].gpa);          

    // Increment the student count
    (*count)++;
}

void printStudent(struct Student *students, int count) {
    printf("Student List:\n");
    for(int i = 0; i < count; i++) {
        printf("Student %d: Name: %s, Age: %d, GPA: %.2f\n", i + 1, students[i].name, students[i].age, students[i].gpa);
    }
}

int main () {
    int count = 0;
    struct Student *students = NULL;
    char choice;

    do {
        printf("1. Add Student\n");
        printf("2. Print Students\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                addStudent(&students, &count);
                break;
            case '2':
                printStudent(students, count);
                break;
            case '3':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    }   while (choice!=3);


    free(students);

    {
        int y = 0;
        int *p;
        p = &y;

        printf("Value of y: %d\n", y);
        printf("Address of y: %p\n", (void*)&y); //cast to the variable
        printf("Value stored in pointer p: %p\n", (p+1));
        printf("Value pointer to by p: %d\n", ((*p)+1));
    }
    
    
    return 0;
}
