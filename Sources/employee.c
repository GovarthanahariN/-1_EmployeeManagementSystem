/*
Description :This file contains all the core logic and operations related to
             employee data management in the Employee Management System. It
             implements functions to add, update, delete, display, search and sort employee records.

Version : C17
Author  : Govarthanahari N
Date    : 22/07/23
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"employee.h"
#include"utils.h" //for clearInputBuffer()

#define FILE_NAME "employees.txt"
#define TEMP_FILE "temp.txt"
#define MAX_EMPLOYEES 1000

int compareByName(const void *a,const void *b) {
    return strcmp(((Employee*)a)->name,((Employee*)b)->name);
}

int compareBySalary(const void *a,const void *b) {
    double salA =((Employee*)a)->salary;
    double salB =((Employee*)b)->salary;
    return (salB>salA)-(salB<salA); //Descending
}

int compareByRating(const void *a,const void *b) {
    return ((Employee*)b)->performanceRating -((Employee*)a)->performanceRating; //Descending
}

// Function to add an employee
void addEmployee() {
    FILE *fp =fopen(FILE_NAME,"a");
    if(!fp){
        printf("Error opening file!\n");
        return;
    }
    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d",&emp.id);
    clearInputBuffer();
    printf("Enter Full Name: ");
    fgets(emp.name,50,stdin);
    strtok(emp.name,"\n");
    printf("Enter Date of Birth (DD/MM/YYYY): ");
    scanf("%s",emp.dob);
    printf("Enter Gender: ");
    scanf("%s",emp.gender);
    printf("Enter Nationality: ");
    scanf("%s",emp.nationality);
    printf("Enter Phone Number: ");
    scanf("%s",emp.phone);
    printf("Enter Email: ");
    scanf("%s",emp.email);
    clearInputBuffer();
    printf("Enter Address: ");
    fgets(emp.address,100,stdin);
    strtok(emp.address,"\n");
    printf("Enter Emergency Contact: ");
    scanf("%s",emp.emergencyContact);
    clearInputBuffer();
    printf("Enter Job Title: ");
    fgets(emp.jobTitle,30,stdin);
    strtok(emp.jobTitle,"\n");
    printf("Enter Date of Joining: ");
    scanf("%s",emp.dateOfJoining);
    printf("Enter Department: ");
    scanf("%s",emp.department);
    clearInputBuffer();
    printf("Enter Supervisor: ");
    fgets(emp.supervisor,50,stdin);
    strtok(emp.supervisor,"\n");
    printf("Enter Work Location: ");
    scanf("%s",emp.workLocation);
    clearInputBuffer();
    printf("Enter Job Description: ");
    fgets(emp.jobDescription,100,stdin);
    strtok(emp.jobDescription,"\n");
    printf("Enter Salary: ");
    scanf("%lf",&emp.salary);
    printf("Enter Bank Account: ");
    scanf("%s",emp.bankAccount);
    printf("Enter Tax Information: ");
    scanf("%s",emp.taxInfo);
    printf("Enter Provident Fund Details: ");
    scanf("%s",emp.providentFund);
    printf("Enter Attendance Record: ");
    scanf("%d",&emp.attendance);
    printf("Enter Performance Rating (1-10): ");
    scanf("%d",&emp.performanceRating);
    printf("Enter Leaves Taken: ");
    scanf("%d",&emp.leavesTaken);

    fprintf(fp,"%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%.2lf|%s|%s|%s|%d|%d|%d\n",
            emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
            emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
            emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, emp.attendance, emp.performanceRating, emp.leavesTaken);
    fclose(fp);
    printf("Employee added successfully!\n");
}

// Function to update an employee
void updateEmployee() {
    int id,found =0;
    printf("Enter Employee ID to update: ");
    scanf("%d",&id);
    clearInputBuffer();

    FILE *fp =fopen(FILE_NAME,"r");
    FILE *temp =fopen("temp.txt","w");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }
    Employee emp;
    char line[500]; //Buffer to hold each line of the file

    while (fgets(line,sizeof(line),fp)) {
        sscanf(line,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d",
               &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
               emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
               &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken);

        if (emp.id==id) {
            found =1;
            printf("Enter new Full Name: ");
            fgets(emp.name,sizeof(emp.name),stdin);
            strtok(emp.name,"\n"); //remove newline character

            printf("Enter new Phone Number: ");
            scanf("%s",emp.phone);
            clearInputBuffer();

            printf("Enter new Email: ");
            scanf("%s",emp.email);
            clearInputBuffer();

            printf("Enter new Salary: ");
            scanf("%lf",&emp.salary);
            clearInputBuffer();
        }

        //Write the updated or unmodified employee data back to the file
        fprintf(temp,"%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%.2lf|%s|%s|%s|%d|%d|%d\n",
                emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, emp.attendance, emp.performanceRating, emp.leavesTaken);
    }
    fclose(fp);
    fclose(temp);

    if(found){
        remove(FILE_NAME);
        rename("temp.txt",FILE_NAME);
        printf("Employee updated successfully!\n");
    }
    else{
        remove("temp.txt");
        printf("Employee ID not found!\n");
    }
}

//Function to delete an employee
void deleteEmployee(){
    int id, found =0;
    printf("Enter Employee ID to delete: ");
    scanf("%d",&id);
    clearInputBuffer();

    FILE *fp =fopen(FILE_NAME, "r");
    FILE *temp =fopen("temp.txt","w");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }
    Employee emp;
    char line[500]; //Buffer to hold each line of the file

    while(fgets(line,sizeof(line),fp)){
        sscanf(line,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d",
               &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
               emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
               &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken);

        if(emp.id!=id){
            fprintf(temp,"%s",line);  //Write the line as-is if the ID doesn't match
        }
        else{
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);

    if(found){
        remove(FILE_NAME);
        rename("temp.txt",FILE_NAME);
        printf("Employee deleted successfully!\n");
    }
    else{
        remove("temp.txt");
        printf("Employee ID not found!\n");
    }
}

//Function to search for an employee
void searchEmployee() {
    int choice;
    char searchTerm[100];
    int id;
    int found =0;

    printf("\nSearch Employee By:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Department\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
    clearInputBuffer();

    FILE *fp = fopen(FILE_NAME, "r");
    if(!fp){
        printf("Error opening file!\n");
        return;
    }

    Employee emp;
    switch(choice){
        case 1:
            printf("Enter ID: ");
            scanf("%d",&id);
            while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                          &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                          emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                          &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken) != EOF) {
                if(emp.id==id) {
                    found =1;
                    printf("\nEmployee Found:\nName: %s\nPhone: %s\nEmail: %s\nDepartment: %s\nSalary: %.2lf\n", emp.name, emp.phone, emp.email, emp.department, emp.salary);
                    break;
                }
            }
            break;
        case 2:
            printf("Enter Name: ");
            fgets(searchTerm,sizeof(searchTerm),stdin);
            strtok(searchTerm,"\n");
            while (fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                          &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                          emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                          &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken) != EOF) {
                if (strcasecmp(emp.name,searchTerm)==0) {
                    found =1;
                    printf("\nEmployee Found:\nID: %d\nPhone: %s\nEmail: %s\nDepartment: %s\nSalary: %.2lf\n", emp.id, emp.phone, emp.email, emp.department, emp.salary);
                }
            }
            break;
        case 3:
            printf("Enter Department: ");
            fgets(searchTerm,sizeof(searchTerm),stdin);
            strtok(searchTerm,"\n");
            while (fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                          &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                          emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                          &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken) != EOF) {
                if (strcasecmp(emp.department,searchTerm)==0) {
                    found =1;
                    printf("\nEmployee Found:\nID: %d\nName: %s\nPhone: %s\nEmail: %s\nSalary: %.2lf\n", emp.id,emp.name,emp.phone,emp.email,emp.salary);
                }
            }
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    if (!found)
        printf("No matching employee found.\n");

    fclose(fp);
}

//Function to display an employee
void displayEmployee() {
    int id,found =0;
    printf("Enter Employee ID to display: ");
    scanf("%d",&id);
    clearInputBuffer();

    FILE *fp =fopen(FILE_NAME,"r");
    if(!fp){
        printf("Error opening file or file does not exist!\n");
        return;
    }
    Employee emp;
    char line[500];

    while(fgets(line,sizeof(line),fp)) {
        sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d",
               &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
               emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
               &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken);

        if (emp.id==id) {
            found = 1;
            printf("\nEmployee Details:\n");
            printf("ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("DOB: %s\n", emp.dob);
            printf("Gender: %s\n", emp.gender);
            printf("Nationality: %s\n", emp.nationality);
            printf("Phone: %s\n", emp.phone);
            printf("Email: %s\n", emp.email);
            printf("Address: %s\n", emp.address);
            printf("Emergency Contact: %s\n", emp.emergencyContact);
            printf("Job Title: %s\n", emp.jobTitle);
            printf("Date of Joining: %s\n", emp.dateOfJoining);
            printf("Department: %s\n", emp.department);
            printf("Supervisor: %s\n", emp.supervisor);
            printf("Work Location: %s\n", emp.workLocation);
            printf("Job Description: %s\n", emp.jobDescription);
            printf("Salary: %.2lf\n", emp.salary);
            printf("Bank Account: %s\n", emp.bankAccount);
            printf("Tax Info: %s\n", emp.taxInfo);
            printf("Provident Fund: %s\n", emp.providentFund);
            printf("Attendance: %d\n", emp.attendance);
            printf("Performance Rating: %d\n", emp.performanceRating);
            printf("Leaves Taken: %d\n", emp.leavesTaken);
            break;
        }
    }
    fclose(fp);

    if(!found)
        printf("Employee ID not found!\n");
}

// Function to display all employees
void displayAllEmployees(){
    FILE *fp = fopen(FILE_NAME,"r");
    if(!fp){
        printf("Error opening file!\n");
        return;
    }
    Employee emp;
    int count =0;

    printf("\n%-5s | %-20s | %-10s | %-15s | %-10s | %-10s\n", "ID", "Name", "Gender", "Department", "Salary", "Rating");
    printf("-------------------------------------------------------------------------------------------\n");

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                  emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                  &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken) != EOF) {

        printf("%-5d | %-20s | %-10s | %-15s | %-10.2lf | %-10d\n",
               emp.id,emp.name,emp.gender,emp.department,emp.salary,emp.performanceRating);
        count++;
    }
    fclose(fp);

    if(count==0) {
        printf("No employee records found.\n");
    }
    else{
        printf("-------------------------------------------------------------------------------------------\n");
        printf("Total Employees: %d\n", count);
    }
}

//Function to Sort Employees
void sortEmployees() {
    FILE *fp =fopen(FILE_NAME,"r");
    if(!fp){
        printf("Error opening file!\n");
        return;
    }
    Employee employees[MAX_EMPLOYEES];
    int count =0;

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  &employees[count].id, employees[count].name, employees[count].dob, employees[count].gender,
                  employees[count].nationality, employees[count].phone, employees[count].email, employees[count].address,
                  employees[count].emergencyContact, employees[count].jobTitle, employees[count].dateOfJoining,
                  employees[count].department, employees[count].supervisor, employees[count].workLocation,
                  employees[count].jobDescription, &employees[count].salary, employees[count].bankAccount,
                  employees[count].taxInfo, employees[count].providentFund, &employees[count].attendance,
                  &employees[count].performanceRating, &employees[count].leavesTaken) != EOF) {
        count++;
    }
    fclose(fp);

    if(count==0) {
        printf("No employees found to sort.\n");
        return;
    }
    int choice;
    printf("\nSort Employees By:\n");
    printf("1. Name (A-Z)\n");
    printf("2. Salary (High to Low)\n");
    printf("3. Performance Rating (High to Low)\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            qsort(employees, count, sizeof(Employee), compareByName);
            break;
        case 2:
            qsort(employees, count, sizeof(Employee), compareBySalary);
            break;
        case 3:
            qsort(employees, count, sizeof(Employee), compareByRating);
            break;
        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("\n%-5s | %-20s | %-15s | %-10s | %-10s | %-10s\n", "ID", "Name", "Department", "Salary", "Rating", "Phone");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | %-15s | %-10.2lf | %-10d | %-10s\n",
               employees[i].id, employees[i].name, employees[i].department,
               employees[i].salary, employees[i].performanceRating, employees[i].phone);
    }
}

