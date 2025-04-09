/*
Description :Employee Core Functionality Header File

Version : C17
Author  : Govarthanahari N
Date    : 21/07/23
*/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

//Structure to handle Employee details
typedef struct {
    int id;
    char name[50];
    char dob[15];
    char gender[10];
    char nationality[20];
    char phone[15];
    char email[50];
    char address[100];
    char emergencyContact[15];
    char jobTitle[30];
    char dateOfJoining[15];
    char department[30];
    char supervisor[50];
    char workLocation[30];
    char jobDescription[100];
    double salary;
    char bankAccount[30];
    char taxInfo[30];
    char providentFund[30];
    int attendance;
    int performanceRating;
    int leavesTaken;
} Employee;


void addEmployee();
void updateEmployee();
void deleteEmployee();
void searchEmployee();
void displayEmployee();
void displayAllEmployees();
void sortEmployees();

#endif
