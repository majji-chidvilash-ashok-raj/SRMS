#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

char currentUser[20];
char currentRole[10];

int loginSystem();
void mainMenu();
void adminMenu();
void userMenu();
void guestMenu();
void staffMenu();

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void updateStudentMarksByStaff();

int main() {
    while (1) {
        if (loginSystem()) {
            mainMenu();  
        } else {
            printf("\nLogin failed. Try again.\n");
        }
    }
    return 0;
}

int loginSystem() {
    char username[20], password[20];
    char fileUser[20], filePass[20], fileRole[10];

    printf("============ Login Screen ==============\n");
    printf("Username: ");
    scanf("%19s", username);

    if (strcmp(username, "guest") == 0) {
        strcpy(currentUser, "guest");
        strcpy(currentRole, "GUEST");
        system("cls");
        return 1;
    }

    printf("Password: ");
    scanf("%19s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: %s not found!\n", CREDENTIAL_FILE);
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            system("cls");
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0) {
        adminMenu();
    } else if (strcmp(currentRole, "USER") == 0) {
        userMenu();
    } else if (strcmp(currentRole, "GUEST") == 0) {
        guestMenu();
    } else if (strcmp(currentRole, "STAFF") == 0) {
        staffMenu();
    } else {
        printf("Unknown role '%s'. Defaulting to GUEST view.\n", currentRole);
        guestMenu();
    }
}

void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU (%s) =====\n", currentUser);
        printf("1. Add New Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student (Name / Marks)\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return; 
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU (%s) =====\n", currentUser);
        printf("1. Display All Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: return;  
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

void guestMenu() {
    int choice;
    do {
        printf("\n===== GUEST MENU (%s) =====\n", currentUser);
        printf("1. Display All Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: return;  
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU (%s) =====\n", currentUser);
        printf("1. Display All Students\n");
        printf("2. Search Student\n");
        printf("3. Update Student Marks (Only Marks)\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudentMarksByStaff(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

void addStudent() {
    FILE *fp = fopen(STUDENT_FILE, "a");
    if (!fp) {
        printf("Error opening %s!\n", STUDENT_FILE);
        return;
    }

    struct Student st;

    printf("Enter Roll No: ");
    scanf("%d", &st.roll);
    printf("Enter Name: ");
    scanf("%s", st.name);  
    printf("Enter Marks: ");
    scanf("%f", &st.marks);

    fprintf(fp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    fclose(fp);

    printf("Student added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found!\n");
        return;
    }

    struct Student st;

    printf("\n%-10s %-15s %-10s\n", "ROLL", "NAME", "MARKS");
    printf("---------------------------------------------\n");

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) == 3) {
        printf("%-10d %-15s %-10.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
}

void searchStudent() {
    int r, found = 0;
    struct Student st;

    printf("Enter roll number to search: ");
    scanf("%d", &r);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("File not found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) == 3) {
        if (st.roll == r) {
            printf("\nRecord Found!\n");
            printf("Roll: %d\nName: %s\nMarks: %.2f\n", st.roll, st.name, st.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No record found!\n");

    fclose(fp);
}

void updateStudent() {
    int r, found = 0;
    struct Student st;

    printf("Enter roll number to update: ");
    scanf("%d", &r);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error creating temp file!\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) == 3) {
        if (st.roll == r) {
            found = 1;
            printf("Enter new Name: ");
            scanf("%s", st.name);
            printf("Enter new Marks: ");
            scanf("%f", &st.marks);
        }
        fprintf(temp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record Updated!\n");
    else
        printf("Record Not Found!\n");
}

void deleteStudent() {
    int r, found = 0;
    struct Student st;

    printf("Enter roll number to delete: ");
    scanf("%d", &r);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error creating temp file!\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) == 3) {
        if (st.roll != r) {
            fprintf(temp, "%d %s %.2f\n", st.roll, st.name, st.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record Deleted!\n");
    else
        printf("Record Not Found!\n");
}

void updateStudentMarksByStaff() {
    int r, found = 0;
    struct Student st;

    printf("Enter roll number to update marks: ");
    scanf("%d", &r);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error creating temp file!\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) == 3) {
        if (st.roll == r) {
            found = 1;
            printf("Current Marks: %.2f\n", st.marks);
            printf("Enter new Marks: ");
            scanf("%f", &st.marks);
        }
        fprintf(temp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Marks Updated by Staff!\n");
    else
        printf("Record Not Found!\n");
}
