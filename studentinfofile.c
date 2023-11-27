// #include <stdio.h>

// typedef struct
// {
//     int roll;
//     char name[25];
//     int marks[5];
// } student;

// student s;

// void addStudent(FILE *fp)
// {
//     printf("Enter the roll number: ");
//     scanf("%d", &s.roll);
//     printf("Enter the name: ");
//     scanf("%s", s.name);
//     printf("Enter the marks: ");
//     for (int j = 0; j < 5; j++)
//         scanf("%d", &s.marks[j]);
//     fwrite(&s, sizeof(student), 1, fp);
// }

// void display(FILE *fp)
// {
//     rewind(fp);
//     while (fread(&s, sizeof(student), 1, fp))
//     {
//         printf("Roll: %d\n", s.roll);
//         printf("Name: %s\n", s.name);
//         printf("Marks: ");
//         for (int i = 0; i < 5; i++)
//             printf("%d ", s.marks[i]);
//         printf("\n");
//     }
// }

// int search(FILE *fp, int roll)
// {
//     rewind(fp);
//     while (fread(&s, sizeof(student), 1, fp))
//     {
//         if (s.roll == roll)
//             return 1;
//     }
//     return 0;
// }

// int main()
// {
//     int i, n, roll, ch;
//     FILE *fp;
//     printf("Enter the number of students: ");
//     scanf("%d", &n);
//     fp = fopen("studentinfo.txt", "w");
//     for (i = 0; i < n; i++)
//     {
//         printf("Enter the roll number: ");
//         scanf("%d", &s.roll);
//         printf("Enter the name: ");
//         scanf("%s", s.name);
//         printf("Enter the marks: ");
//         for (int j = 0; j < 5; j++)
//             scanf("%d", &s.marks[j]);
//         fwrite(&s, sizeof(student), 1, fp);
//     }
//     fclose(fp);

//     fp = fopen("studentinfo.txt", "r");
//     do
//     {
//         printf("1. Display\n2. Search\n3. Exit\nEnter your choice: ");
//         scanf("%d", &ch);
//         switch (ch)
//         {
//         case 1:
//             display(fp);
//             rewind(fp);
//             break;
//         case 2:
//             printf("Enter the roll number to search: ");
//             scanf("%d", &roll);
//             if (search(fp, roll))
//                 printf("Record found\n");
//             else
//                 printf("Record not found\n");
//             break;
//         case 3:
//             break;
//         default:
//             printf("Invalid choice\n");
//         }
//     } while (ch != 3);
//     fclose(fp);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold student information
struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function to add student information to file
void addStudentInfo() {
    FILE *fp;
    struct Student student;

    fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &student.roll);
    printf("Enter Name: ");
    scanf("%s", student.name);
    printf("Enter Marks: ");
    scanf("%f", &student.marks);

    fwrite(&student, sizeof(struct Student), 1, fp);

    fclose(fp);
}

// Function to display all student information from file
void displayAllStudents() {
    FILE *fp;
    struct Student student;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nAll Student Information:\n");
    while (fread(&student, sizeof(struct Student), 1, fp) == 1) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", student.roll, student.name, student.marks);
    }

    fclose(fp);
}

// Function to search student information by roll number
void searchStudentByRoll() {
    FILE *fp;
    struct Student student;
    int searchRoll, found = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &searchRoll);

    while (fread(&student, sizeof(struct Student), 1, fp) == 1) {
        if (student.roll == searchRoll) {
            printf("Student Information Found:\n");
            printf("Roll: %d, Name: %s, Marks: %.2f\n", student.roll, student.name, student.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", searchRoll);
    }

    fclose(fp);
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudentInfo();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudentByRoll();
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
