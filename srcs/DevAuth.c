#include "../includes/header_files.h"

#define R refresh ()

void clearscr (WINDOW * child) {
        wclear (child);
        box (child, 4, 4);
        wrefresh (child); 
}

int main () {

    initscr ();
    if (db_init ()) {
        printw ("Could not initialize a database\n"); R;
        exit (EXIT_FAILURE);
    }

    printw ("Database initialized succesfully\n"); R;

    Entry* entry;
    if (!(entry = malloc (sizeof (Entry)))) {
       printw ("%s\n", strerror(errno)); R;
       exit (errno);
    }

    int counter = 0; // option
    char res = 'Y', opt;//response descision option
    char reg_no[20];
    Entry *stdnt = NULL;
    WINDOW *child = newwin (1000, 1000, 0, 0);
    box (child, 4, 4);

    while (1) {
        clearscr (child);
        opt = guide (child);
        clearscr (child);
        switch (opt) {
            case 'R':
                do {
                    clearscr (child);
                    if (register_student (entry, child) == REG_ERR) {
                        wprintw (child, "\t\tCannot register student :(\n"); wrefresh (child);
                        break;
                    }
             
                    clearscr (child);
                    if (register_laptop (entry, child) == REG_ERR) {
                        wprintw (child, "\t\tCannot register laptop :(\n"); wrefresh (child);
                        break;
                    }

                    if (save_data (entry))  {
                        wprintw (child, "\t\tStudent not saved :)\n"); wrefresh (child);
                    }
                    else
                        wprintw (child, "\t\tStudent saved successfully :(\n"); wrefresh (child);
                    
                    wprintw (child, "\t\tPress [B] to go back to the main menu | Press [Enter] to continue: "); wrefresh (child);
                    res = wgetch (child);
                    if (res == 'B') {
                        wprintw (child, "\t\t%i students successfully registered :(\n", counter + 1); wrefresh (child);
                        sleep (1);
                        clearscr (child);
                        break;
                    }
                    ++counter;
                } while (1);
                break;

            case 'A':
                clearscr (child);
                do  {
                    wprintw (child, "\n\n\t\t\tAUTHENICATING STUDENT\n"); wrefresh (child);
                    wprintw (child, "\n\t\tEnter students registation number: "); wrefresh (child);
                    if (wgetstr (child, reg_no) != ERR) {
                        wprintw (child, "Could not read reg_no\n"); wrefresh (child);
                    }
                    add_terminator (reg_no, sizeof (reg_no), strlen (reg_no), child);
                    if (!(stdnt = lookup_db (reg_no))){
                        wprintw (child, "\t\tStudent dont exists\n"); wrefresh (child);
                        goto label;
                    } else {
                        display (stdnt, child);
                    }
                    wprintw (child, "\n\t\tDoes the serial provided match in system ? (Y/N): "); wrefresh (child);
                    res = toupper (wgetch (child));
                    if (res == 'N'){
                        wprintw (child, "\n\t\tREPORTING...\n"); wrefresh (child);
                        if (flag_student (reg_no)) {
                            wprintw (child, "\n\t\tCannot report student :(\n"); wrefresh (child);
                        }
                    }
                    label:
                    wprintw (child, "\n\t\tPress [B] to go back to the main menu | Press [Enter] to register: "); wrefresh (child);
                    res = toupper (wgetch (child));
                    if (res == 'B') {
                        break;
                    }
                    clearscr (child);                    
                } while (1);
                break;
            case 'H':
                clearscr (child);
                help_method (child);
                break;
            case 'Q':
                delwin (child);
                printw ("Goodbye...\n");
                sleep (1);
                free (entry);
                endwin ();
                return (0);
        }
    }
}
