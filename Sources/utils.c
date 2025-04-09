/*
Description :Utility functions for input handling and string processing
             used throughout the Employee Management System.

Version : C17
Author  : Govarthanahari N
Date    : 21/07/23
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"utils.h"

//Function to clear input buffer
void clearInputBuffer(){
    int c;
    while((c=getchar()) != '\n' && c != EOF);
}

// //Pauses the console until the user presses Enter
// void pauseConsole(){
//     printf("\nPress Enter to continue...");
//     getchar();
// }

// //String to lowercase
// void toLowerCase(char *str){
//     while(*str){
//         *str =tolower(*str);
//         str++;
//     }
// }

// //Removes newline character from the EOS
// void trimNewline(char *str){
//     size_t len =strlen(str);
//     if (len>0 && str[len-1] == '\n') {
//         str[len-1]='\0';
//     }
// }
