#include "../includes/header_files.h"

/* Flushes the input buffer for the given window */
void flush_input_buff (WINDOW * child) {

   char ch;
   while ((ch = wgetch(child)) != '\n' && ch != EOF)
      ;
   return;

}

/* Adds a null terminator to the string if needed and flushes input buffer if necessary */
void add_terminator (char *string, int size, int length, WINDOW * child) {

   if (strchr(string, '\n')) { /* check for instance of newline and replace it with null */
      string[strcspn(string, "\n")] = '\0';
      return;
   }
   if (size - 1 == length) {
      string[length] = '\0';
      flush_input_buff (child);
   }

}

/* Clears the console after a delay */
void clear_console (int time, WINDOW * child) {
   int i;

   sleep (time);
   /* so that it can remove the error message and the typed characters from the console */
   for (i = 0; i < 2; ++i) {
      wprintw (child, "\033[A\033[2K"); wrefresh (child); /* move the cursor up two lines and clear the line */
      mvwdelch (child, -2, 1); /* remove the characters in the console */
   }
   return;
}

/* Checks if the input is empty and prints a message if so */
int isEmpty (char newline, char *member, WINDOW * child) {

   if (newline == '\n') {
      wprintw (child, "\t\t%s should not be empty\n", member); wrefresh (child);
      clear_console (1, child);
      return 1;
   }
   return 0;
}

/* Initializes the current date in the entry structure */
void init_current_date (Entry* entry, WINDOW * child) {
   time_t now;
   struct tm *current_d;
   char date_str[11]; /* Buffer to hold the formatted date string (dd-mm-yyyy + null terminator) */

   time (&now);
   current_d = localtime (&now);
   if (current_d != NULL) {
      if (!(strftime (date_str, sizeof(date_str), "%d-%m-%Y", current_d))) {
         wprintw (child, "\t\tError formatting the current date.\n"); wrefresh (child);
         strcpy (entry -> t_stamp.t_registration, "NULL");
      } else {
         strcpy (entry -> t_stamp.t_registration, date_str); 
      }
   } else {
      wprintw (child, "\t\tError retrieving the current date.\n"); wrefresh (child);
   }
}
