#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

void addEmployee(FILE *fp) {
    struct Employee emp;
    printf("\nEnter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fseek(fp, (emp.id - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, fp);

    printf("Employee record added successfully!\n");
}

void displayAll(FILE *fp) {
    struct Employee emp;
    rewind(fp);
    printf("\n--- Employee Details ---\n");
    while (fread(&emp, sizeof(struct Employee), 1, fp)) {
        if (emp.id != 0)
            printf("ID: %d\tName: %s\tSalary: %.2f\n", emp.id, emp.name, emp.salary);
    }
}

void searchEmployee(FILE *fp) {
    int id;
    struct Employee emp;
    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);

    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&emp, sizeof(struct Employee), 1, fp) && emp.id != 0)
        printf("Record Found — ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    else
        printf("Employee not found!\n");
}

void updateSalary(FILE *fp) {
    int id;
    struct Employee emp;
    printf("\nEnter Employee ID to update: ");
    scanf("%d", &id);

    fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&emp, sizeof(struct Employee), 1, fp) && emp.id != 0) {
        printf("Current Salary: %.2f\nEnter New Salary: ", emp.salary);
        scanf("%f", &emp.salary);

        fseek(fp, (id - 1) * sizeof(struct Employee), SEEK_SET);
        fwrite(&emp, sizeof(struct Employee), 1, fp);

        printf("Salary updated successfully!\n");
    } else {
        printf("Employee not found!\n");
    }
}

int main() {
    FILE *fp;
    int choice;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }
    }

    while (1) {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n2. Display All\n3. Search Employee\n4. Update Salary\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(fp); break;
            case 2: displayAll(fp); break;
            case 3: searchEmployee(fp); break;
            case 4: updateSalary(fp); break;
            case 5: fclose(fp); printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

