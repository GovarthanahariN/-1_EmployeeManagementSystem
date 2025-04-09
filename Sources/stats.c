/*
Description :Implements employee statistics analysis including salary insights,
             performance highlights ,and department-wise employee distribution.

Version : C17
Author  : Govarthanahari N
Date    : 23/07/23
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stats.h"
#include"employee.h"

#define FILE_NAME "employees.txt"

//Function of Statistics
void showStatistics(){
    FILE *fp =fopen(FILE_NAME, "r");
    if(!fp){
        printf("Error opening file!\n");
        return;
    }

    Employee emp;
    int count =0;
    double totalSalary =0, maxSalary =0, minSalary =1e9;
    int totalRating =0;
    char topPerformer[50] ="";
    int maxRating =-1;

    //For department-wise count (max 100 departments)
    char departments[100][50];
    int deptCount[100] ={0};
    int deptIndex =0;

    while(fscanf(fp,"%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
                  &emp.id, emp.name, emp.dob, emp.gender, emp.nationality, emp.phone, emp.email, emp.address, emp.emergencyContact,
                  emp.jobTitle, emp.dateOfJoining, emp.department, emp.supervisor, emp.workLocation, emp.jobDescription,
                  &emp.salary, emp.bankAccount, emp.taxInfo, emp.providentFund, &emp.attendance, &emp.performanceRating, &emp.leavesTaken) !=EOF){

        count++;
        totalSalary +=emp.salary;
        totalRating +=emp.performanceRating;

        if(emp.salary>maxSalary) maxSalary =emp.salary;
        if(emp.salary<minSalary) minSalary =emp.salary;

        if(emp.performanceRating>maxRating){
            maxRating =emp.performanceRating;
            strcpy(topPerformer,emp.name);
        }

        //Department-wise count
        int found =0;
        for(int i=0;i<deptIndex;i++){
            if(strcmp(departments[i],emp.department) ==0){
                deptCount[i]++;
                found =1;
                break;
            }
        }
        if(!found){
            strcpy(departments[deptIndex],emp.department);
            deptCount[deptIndex]++;
            deptIndex++;
        }
    }

    fclose(fp);

    if(count==0){
        printf("No employee data available to analyze.\n");
        return;
    }

    printf("\n--- EMPLOYEE STATISTICS ---\n");
    printf("Total Employees         : %d\n",count);
    printf("Total Salary Payout     : %.2lf\n",totalSalary);
    printf("Average Salary          : %.2lf\n",totalSalary / count);
    printf("Average Rating          : %.2lf\n",(double)totalRating / count);
    printf("Highest Salary          : %.2lf\n",maxSalary);
    printf("Lowest Salary           : %.2lf\n",minSalary);
    printf("Top Performer           : %s (Rating: %d)\n",topPerformer, maxRating);

    printf("\nDepartment-wise Employee Count:\n");
    for(int i=0;i<deptIndex;i++) {
        printf("- %s: %d\n",departments[i],deptCount[i]);
    }
}
