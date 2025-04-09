/*
Description :Provides a terminal-based interactive UI for the Employee Management System
             using ncurses.
             Handles user navigation,UI transitions and integration
             with core functionalities like employee operations,statistics and file exports.

Version : C17
Author  : Govarthanahari N
Date    : 05/12/24
*/

#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"employee.h"
#include"fileops.h"
#include"stats.h"
#include"utils.h"

//Function to keep the console for user input
void pauseAndWait(){
    printf("\n\nPress Enter to return to menu...");
    while(getchar()!='\n');
}

//Reinitializes ncurses UI settings,colors,mouse and keyboard input modes
void reinitUI(){
    initscr(); cbreak(); noecho(); curs_set(0);
    keypad(stdscr,TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION,NULL);
    start_color();
    init_pair(1,COLOR_CYAN,COLOR_BLACK);  //Title
    init_pair(2,COLOR_WHITE,COLOR_BLUE);  //Highlight
    init_pair(3,COLOR_GREEN,COLOR_BLACK); //Normal text
}

//Wraps a function call outside ncurses mode,pauses,then restores UI and redraws static elements
void wrapAndPauseUI(void (*func)()){
    clear();refresh();endwin();  //Exit ncurses
    func();                      //Run your logic function
    pauseAndWait();              //Wait for user to continue
    reinitUI();                  //Back to ncurses mode

    //Redraw static UI (title, border) when returning
    int row,col;
    getmaxyx(stdscr,row,col);
    box(stdscr,0,0);

    attron(COLOR_PAIR(1) | A_BOLD);
    char *title ="EMPLOYEE MANAGEMENT SYSTEM";
    mvprintw(2,(col-strlen(title))/2,"%s",title);
    attroff(COLOR_PAIR(1) | A_BOLD);
    mvhline(3,1,ACS_HLINE,col-2);

    attron(COLOR_PAIR(1));
    mvprintw(4,(col-8)/2,"MENU");
    attroff(COLOR_PAIR(1));
}

//Core UI starter function
void startUI(){
    reinitUI();

    const char *options[] ={
        "1. Add Employee",
        "2. Update Employee",
        "3. Delete Employee",
        "4. Display Employee",
        "5. Search Employee",
        "6. Sort Employee",
        "7. Display All Employees",
        "8. Show Statistics",
        "9. Export CSV File",
        "10. Exit"
    };
    int numOptions =sizeof(options)/sizeof(options[0]);
    int highlight =0,choice =0;

    //Slide animation
    for(int step=0;step<=5;step++) {
        clear();
        int row,col;
        getmaxyx(stdscr,row,col);
        box(stdscr,0,0);

        attron(COLOR_PAIR(1) | A_BOLD);
        char *title ="EMPLOYEE MANAGEMENT SYSTEM";
        mvprintw(2,(col-strlen(title))/2,"%s",title);
        attroff(COLOR_PAIR(1) | A_BOLD);
        mvhline(3,1,ACS_HLINE,col-2);

        attron(COLOR_PAIR(1));
        mvprintw(4,(col-8)/2,"MENU");
        attroff(COLOR_PAIR(1));

        for(int i=0;i<numOptions;i++) {
            int y =6+i*2;
            int x =(col-40)/2;
            if(i<=step) {
                attron(COLOR_PAIR(3));
                mvprintw(y, x, "   %-36s   ",options[i]);
                attroff(COLOR_PAIR(3));
            }
        }
        refresh();
        usleep(70*1000); // 70ms
    }

    while(1){
        int row,col;
        getmaxyx(stdscr,row,col);

        for(int i=0;i<numOptions;i++) {
            int y =6+i*2;
            int x =(col-40)/2;
            if(i==highlight) {
                attron(COLOR_PAIR(2) | A_BOLD);
                mvprintw(y,x, ">> %-36s <<",options[i]);
                attroff(COLOR_PAIR(2) | A_BOLD);
            }
            else{
                attron(COLOR_PAIR(3));
                mvprintw(y,x, "   %-36s   ",options[i]);
                attroff(COLOR_PAIR(3));
            }
        }

        attron(COLOR_PAIR(1));
        mvprintw(row-2,(col-40)/2,"Use Arrow || Mouse to navigate, Enter to select");
        attroff(COLOR_PAIR(1));
        refresh();

        int ch =getch();
        MEVENT event;

        switch(ch){
            case KEY_UP:
                highlight =(highlight-1 + numOptions)%numOptions;
                break;
            case KEY_DOWN:
                highlight =(highlight+1)%numOptions;
                break;
            case 10: //enter
                choice =highlight+1;
                break;
            case KEY_MOUSE:
                if(getmouse(&event) ==OK) {
                    for(int i=0;i<numOptions;i++) {
                        int y =6+i*2;
                        int x =(col-40)/2;
                        if (event.y==y &&
                            event.x>=x && event.x<=x+40){
                            highlight =i;
                            choice =i+1;
                            break;
                        }
                    }
                }
                break;
        }

        if(choice>0) {
            switch(choice){
                case 1: wrapAndPauseUI(addEmployee); break;
                case 2: wrapAndPauseUI(updateEmployee); break;
                case 3: wrapAndPauseUI(deleteEmployee); break;
                case 4: wrapAndPauseUI(displayEmployee); break;
                case 5: wrapAndPauseUI(searchEmployee); break;
                case 6: wrapAndPauseUI(sortEmployees); break;
                case 7: wrapAndPauseUI(displayAllEmployees); break;
                case 8: wrapAndPauseUI(showStatistics); break;
                case 9: wrapAndPauseUI(exportToCSV); break;
                case 10:
                    endwin();
                    printf("Exiting Employee Management System...\n");
                    exit(0);
            }
            choice =0;
        }
    }
    endwin();
}
