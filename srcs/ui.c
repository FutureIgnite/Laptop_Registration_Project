#include "../includes/header_files.h"

/**
 * menu of the available choice of operations
 */
char guide (WINDOW * child) {
    
    box (child, 4, 4);

    mvwprintw (child, 1, 1, "\n\n\t================CHOOSE OPERATION================"); R2(child);

    mvwprintw (child, 2, 1, "\t\t[A] :  AUTHENTICATE STUDENT\n"); R2(child);
    mvwprintw (child, 3, 1, "\t\t[R] :  REGISTER STUDENT\n"); R2(child);
    mvwprintw (child, 4, 1, "\t\t[L] :  REPORT LOST LAPTOP\n"); R2(child);
    mvwprintw (child, 5, 1, "\t\t[H] :  HELP\n"); R2(child);
    mvwprintw (child, 6, 1, "\t\t[Q] :  QUIT THE PROGRAM\n"); R2(child);

    mvwprintw (child, 7, 1, "\t\tInput: "); R2(child);
    char opt;
    opt = wgetch (child);
    return opt;
}

void help_method (WINDOW * child) {
    mvwprintw (child, 4, 1, "\n\n\t\tEnter [0] to check if the student owns the laptop"); R2(child);
    mvwprintw (child, 5, 1, "\t\t type N/Y to flag student if trying to authenticate someone else laptop\n*****>"); R2(child);
    while (1) {
        wprintw (child, "Press [B] to go back to the main menu\n");
        char opt = wgetch (child);
        if (opt == 'B' || opt == 'b') {
            break;
        }
    }
    return;
}

void display (Entry *entry, WINDOW * child) {
    box (child, 4, 4);

    mvwprintw (child, 1, 1, "\n\n\t==============STUDENT RECORD=================\n\n"); R2(child);
    mvwprintw (child, 2, 1, "\t\tName               : %s\n", entry->student.student_name); R2(child);
    mvwprintw (child, 3, 1, "\t\tReg Number         : %s\n", entry->student.reg_no); R2(child); 
    mvwprintw (child, 4, 1, "\t\tPhone Number       : %s\n", entry->student.phone_no); R2(child);
    mvwprintw (child, 5, 1, "\t\tYear of Study      `: %s\n", entry->student.y_of_study); R2(child);
    
    if (strcmp (entry->t_stamp.t_registration, "NULL")) {
        mvwprintw (child, 6, 1, "\t\tdate of registration    : %s\n", entry->t_stamp.t_registration); R2(child);
    } else {
        mvwprintw (child, 6, 1, "\t\tDate of registration not set\n"); R2(child);
    }
    mvwprintw (child, 7, 1, "\t\tLaptop Model            : %s\n", entry->laptop.model); R2(child);
    mvwprintw (child, 8, 1, "\t\tLaptop Serial Number    : %s\n", entry->laptop.serial_no); R2(child);
    mvwprintw (child, 9, 1, "\n\t============================================\n\n"); R2(child);

    /*mvwprintw (child, 10, 1, "\t\tPress [B] to go back to the main menu\n"); R2(child);
    char choice;
    while (1) {
        choice = wgetch(child);
        if (choice == 'B' || choice == 'b') {
            delwin(child);
            break;
        }
    }*/

    free(entry);
}
