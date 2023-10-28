#include <stdio.h>
#include <stdlib.h>
#include <string.h> // To find the student with the longest name
#include <ctype.h> // To avoid entering letters where numbers should be entered

// Define a structure for a student with studentNumber, name, age, and a pointer to the next student
struct Student {
    int studentNumber;
    char name[100];
    int age;
    struct Student* next;
};

// Declare pointers to the head and tail of the linked list
struct Student* head = NULL;
struct Student* tail = NULL;
int studentCount = 0; // Initialize the student count

// Function to add a student to the end of the list
void addStudent(int studentNumber, const char* name, int age) {
    // Allocate memory for a new student and set their data
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->studentNumber = studentNumber;
    strncpy(newStudent->name, name, sizeof(newStudent->name));
    newStudent->age = age;
    newStudent->next = NULL;

    // Add the new student to the end of the list
    if (tail == NULL) {
        head = tail = newStudent;
    } else {
        tail->next = newStudent;
        tail = newStudent;
    }

    studentCount++; // Increase the student count
}

// To display all student information with numbers
void displayStudentInformation() {
    struct Student* current = head;
    int studentNumber = 1;

    while (current != NULL) {
        // Print the student number, name, age and student number
        printf("%d- %s %d %d\n", studentNumber, current->name, current->age, current->studentNumber);
        current = current->next;
        studentNumber++;
    }
}

// To search for a student by name
struct Student* searchStudentByName(const char* name) {
    struct Student* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL; // If student not found
}

// To delete the next node (Information about the next student) after the given student name
void deleteStudentNext(const char* name) {
    struct Student* current = head;

    while (current != NULL && current->next != NULL) {
        if (strcmp(current->name, name) == 0) {
            struct Student* temp = current->next;
            current->next = current->next->next;
            free(temp); // Free the memory of the deleted student.
            studentCount--; // Decrement the student count.
            return;
        }
        current = current->next;
    }
}

// To find the student with the longest name and count the letters in the name
void LongestName() {
    struct Student* current = head;
    struct Student* longestNameStudent = NULL;
    int maxNameLength = 0;

    while (current != NULL) {
        int nameLength = strlen(current->name);
        if (nameLength > maxNameLength) {
            maxNameLength = nameLength;
            longestNameStudent = current;
        }
        current = current->next;
    }

    if (longestNameStudent != NULL) {
        printf("Student with the longest name: %s (Name length: %d)\n", longestNameStudent->name, maxNameLength);
    } else {
        printf("No student found.\n");
    }
}

// To get a valid integer (a number, not a letter) input from the user
int validInt() {
    int input;
    char numbers[100];
    while (1) {
        if (fgets(numbers, sizeof(numbers), stdin) == NULL) {
            exit(1); // Handle unexpected input or EOF
        }
        if (sscanf(numbers, "%d", &input) == 1) {
            return input;
        } else {
            printf("Enter a number.\n");
        // NOTE: For "Enter Age" in case 1, every time this printf displays
        // I could not solve it. For other exceptions, it is good
        }
    }
}

// User menu
int main() {
    int choice;
    char name[100];
    int studentNumber, age;

    while (1) {
        printf("\nStudent Information Menu:\n");
        printf("1. Add Student\n");
        printf("2. Display Students Informations\n");
        printf("3. Search Student by Name\n");
        printf("4. Delete Next Student by Name\n");
        printf("5. Find Student with Longest Name\n");
        printf("6. Exit\n");
        printf("Enter: ");

        choice = validInt();

        switch (choice) {
            case 1:
                printf("Enter Student Number: ");
                studentNumber = validInt();
                printf("Enter Name: ");
                scanf("%s", name);
                printf("Enter Age: ");
                age = validInt();
                addStudent(studentNumber, name, age);
                break;
            case 2:
                if (studentCount > 0) {
                    printf("Students Informations:\n");
                    displayStudentInformation();
                } else {
                    printf("No student to display.\n");
                }
                break;
            case 3:
                printf("Enter Name to Search: ");
                scanf("%s", name);
                struct Student* foundStudent = searchStudentByName(name);
                if (foundStudent != NULL) {
                    printf("Student found: \nStudent Number: %d, Name: %s, Age: %d\n", foundStudent->studentNumber, foundStudent->name, foundStudent->age);
                } else {
                    printf("Student not found: %s\n", name);
                }
                break;
            case 4:
                printf("Enter Name to Delete Next Student: ");
                scanf("%s", name);
                deleteStudentNext(name);
                break;
            case 5:
                LongestName();
                break;
            case 6:
                // Free the allocated memory and exit.
                while (head != NULL) {
                    struct Student* temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("\nInvalid choice.\n");
        }
    }

    return 0;
}
