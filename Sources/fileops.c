/*
Description :Handles file operations related to exporting employee records from
             the system's data file to a CSV format for external use or backup.

Version : C17
Author  : Govarthanahari N
Date    : 23/07/23
*/

#include<stdio.h>
#include<stdlib.h>
#include"fileops.h"
#include"employee.h"

#define FILE_NAME "employees.txt"
#define CSV_FILE "employees.csv"

//Function to write on CSV file
void exportToCSV(){
    FILE *fp =fopen(FILE_NAME,"r");
    FILE *csv =fopen("employees.csv","w");

    if(!fp || !csv){
        printf("Error opening files!\n");
        return;
    }

    //CSV header
    fprintf(csv,"ID,Name,DOB,Gender,Nationality,Phone,Email,Address,EmergencyContact,JobTitle,DateOfJoining,Department,Supervisor,WorkLocation,JobDescription,Salary,BankAccount,TaxInfo,ProvidentFund,Attendance,PerformanceRating,LeavesTaken\n");

    Employee emp;
    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                  emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                  &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken) != EOF){

        //Write data to CSV
        fprintf(csv, "%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%.2lf,\"%s\",\"%s\",\"%s\",%d,%d,%d\n",
                emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, emp.attendance, emp.performanceRating, emp.leavesTaken);
    }

    fclose(fp);
    fclose(csv);
    printf("Employees exported to 'employees.csv' successfully!\n");
}
