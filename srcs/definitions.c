#include "../includes/header_files.h"

void flush_input_buff () {

   char ch;
   while ((ch = getchar()) != '\n' && ch != EOF);
   return;

}

void add_terminator (char *string) {

   if (strchr(string, '\n')) //check for instance of newline and replace it with null
     string[strcspn(string, "\n")] = '\0';
   else 
     flush_input_buff ();

}

void clear_console () {

   sleep (1);
   for (int i = 0; i < 2; ++i) {//so that it can remove the error message and the typed characters from the console
      printf("\033[A\033[2K"); //move the cursor up two lines and clear the line 
      fflush (stdout);//remove the characters in the console   
   }
   return;
}

bool isEmpty (char newline, char *member) {

   if (newline == '\n') {
      printf ("\t\t%s should not be empty\n", member);
      clear_console ();
      return true;
   }
   return false;
}
void init_current_date (Entry* entry) {
   time_t now;
   time (&now);
   struct tm *current_d = localtime (&now);
   if (current_d != NULL) {
      char date_str[11]; // Buffer to hold the formatted date string (dd-mm-yyyy + null terminator)
      if (!(strftime (date_str, sizeof(date_str), "%d-%m-%Y", current_d))) {
         fprintf (stderr, "\t\tError formatting the current date.\n");
         strcpy (entry -> t_stamp.t_registration, "NULL");
      }else {
         strcpy (entry -> t_stamp.t_registration, date_str); 
      }
   } else {
      fprintf(stderr, "\t\tError retrieving the current date.\n");
   }
}
