#include "../includes/header_files.h"

void flush_input_buff (WINDOW * child) {

   char ch;
   while ((ch = wgetch(child)) != '\n' && ch != EOF);
   return;

}

void add_terminator (char *string, int size, int length, WINDOW * child) {

   if (strchr(string, '\n')){ //check for instance of newline and replace it with null
     string[strcspn(string, "\n")] = '\0';
   return;
   }
   if (size - 1 == length) {
      string[length] = '\0';
      flush_input_buff (child);
   }

}

void clear_console (int time, WINDOW * child) {

   sleep (time);
   for (int i = 0; i < 2; ++i) {//so that it can remove the error message and the typed characters from the console
      wprintw (child, "\033[A\033[2K"); wrefresh (child); //move the cursor up two lines and clear the line 
      mvwdelch (child, -2, 1);//remove the characters in the console   
   }
   return;
}

bool isEmpty (char newline, char *member, WINDOW * child) {

   if (newline == '\n') {
      wprintw (child, "\t\t%s should not be empty\n", member); wrefresh (child);
      clear_console (1, child);
      return true;
   }
   return false;
}
void init_current_date (Entry* entry, WINDOW * child) {
   time_t now;
   time (&now);
   struct tm *current_d = localtime (&now);
   if (current_d != NULL) {
      char date_str[11]; // Buffer to hold the formatted date string (dd-mm-yyyy + null terminator)
      if (!(strftime (date_str, sizeof(date_str), "%d-%m-%Y", current_d))) {
         wprintw (child, "\t\tError formatting the current date.\n"); wrefresh (child);
         strcpy (entry -> t_stamp.t_registration, "NULL");
      }else {
         strcpy (entry -> t_stamp.t_registration, date_str); 
      }
   } else {
      wprintw (child, "\t\tError retrieving the current date.\n"); wrefresh (child);
   }
}
