#include "header_files.h"

//this function consumes the remaining characters in the input buffer to avoid subsequent call to funtions
//that require input taking in what is left on the input buffer
void flush_input_buff () {
   char ch;
   while ((ch = getchar()) != '\n' && ch != EOF);
   return;
}

void add_terminator (char *string){
   if (strchr(string, '\n')) //check for instance of newline and replace it with null
     string[strcspn(string, "\n")] = '\0';
   else 
     flush_input_buff ();
}

void clear_console (){
   sleep (2);
   for (int i = 0; i < 2; ++i){//so that it can remove the error message and the typed characters from the console
      printf("\033[A\033[2K"); //move the cursor up one line and clear the line 
      fflush (stdout);//remove the characters in the console   
   }
   return;
}

bool isEmpty (char newline, char *member){
   if (newline == '\n'){
      printf ("%s should not be empty\n", member);
      clear_console ();
      return true;
   }
   return false;
}
void init_current_date (Entries* entry) {
   struct tm *current_d = current_date();
   if (current_d != NULL) {
      char date_str[11]; // Buffer to hold the formatted date string (dd-mm-yyyy + null terminator)
      if (!(strftime(date_str, sizeof(date_str), "%d-%m-%Y", current_d))) {
         fprintf(stderr, "Error formatting the current date.\n");
         strcpy (entry -> t_stamp.t_registration, "NULL");
      }else {
         strcpy (entry -> t_stamp.t_registration, date_str); 
      }
   } else {
      fprintf(stderr, "Error retrieving the current date.\n");
   }
}

int register_student (Entries* entry) {
   init_current_date (entry);
   printf ("\n....Enter student details....\n");
label1:
   printf ("Enter student name:  ");
   if (fgets(entry -> student.student_name, sizeof(entry -> student.student_name), stdin) != NULL){
      if (isEmpty (entry -> student.student_name[0], "Student Name")){
         clear_console();
         goto label1;
      }
      if (strlen(entry -> student.student_name) < 4){
         fprintf (stderr, "Name is too short.\n");
         clear_console ();
         goto label1;
      }
      add_terminator(entry -> student.student_name); //check for instance of newline and replace it with null
   }else {
      fprintf(stderr, "Error reading student name %s\n", strerror(errno));
      return (REG_ERR); //REG_ERR macro defined in variables.h exands to 1
   }
label2:
   printf ("Enter student registration number:  ");
   if ((fgets(entry -> student.reg_no, sizeof (entry -> student.reg_no), stdin)) != NULL){
      if (isEmpty(entry -> student.reg_no[0], "Student Registration Number")){
         goto label2;
      }
      if (strlen(entry -> student.reg_no) < 6){
         fprintf (stderr, "Registration number too short.\n");
         clear_console ();
         goto label2;
      }
      for (char *ch = entry -> student.reg_no; *ch != '\0'; ++ch) {
         if (!isalnum(*ch) && *ch != '/' && *ch != '\0' && *ch != '\n') {
            fprintf(stderr, "Error: Registration number contains invalid characters.\n");
            clear_console ();
            goto label2;
         }
      }
      add_terminator (entry -> student.reg_no); 
   } else {
      fprintf(stderr, "Error reading registration number.\n");
      return (REG_ERR);
   }
label3:
   printf ("Enter student phone number: ");
   if ((fgets (entry -> student.phone_no, sizeof (entry -> student.phone_no), stdin)) != NULL){
      if (strlen(entry -> student.phone_no) < 10) {
         fprintf (stderr, "Phone number too short\n");
         clear_console ();
         goto label3;
      }
      for (char *p = entry -> student.phone_no; *p != '\0'; ++p){
         if (!isdigit(*p) && *p != '\n'){
            fprintf (stderr, "Error: Phone number contains invalid characters.\n");
            clear_console ();
            goto label3;
         }
      }
      add_terminator (entry -> student.phone_no);
   }else {
      fprintf (stderr, "Error reading phone number.\n");
      return (REG_ERR);
   } 
label4:
   printf ("Enter student year of study: ");
   if((fgets (entry -> student.y_of_study, sizeof (entry -> student.y_of_study), stdin)) != NULL) {
      if (isEmpty (entry -> student.y_of_study[0], "Year of study")){
         goto label4;
      }
      for (char *ch = entry -> student.y_of_study; *ch != '\0'; ++ch){
         if (!isalpha(*ch) && *ch != '\n'){
            fprintf (stderr, "Error: year of study contains invalid characters.\n");
            clear_console ();
            goto label4;
         }
      }
      add_terminator (entry -> student.y_of_study);
   }else {
      fprintf (stderr, "Error reading year of study.\n");
      return (REG_ERR);
   }
   return (REG_OK); //REG_OK macro defined in variables.h expands to 0
}

int register_laptop (Entries* Laptop) {
   printf ("\n....Enter laptop details....\n");
label5:
   printf ("Enter laptop model: ");
   if (fgets(Laptop -> laptop.model, sizeof(Laptop -> laptop.model), stdin) != NULL) {
      if (isEmpty (Laptop -> laptop.model[0], "Laptop model")){
         goto label5;
      }
      add_terminator (Laptop -> laptop.model);
   }else {
      fprintf(stderr, "Error reading laptop model %s\n", strerror(errno));
      return (REG_ERR);
   }
label6:
   printf ("Enter laptop serial number: ");
   if (fgets(Laptop -> laptop.serial_no, sizeof(Laptop -> laptop.serial_no), stdin) != NULL) {
      if (isEmpty (Laptop -> laptop.serial_no[0], "Serial Number")){
         goto label6;
      }
      add_terminator (Laptop -> laptop.serial_no);
   }else {
      fprintf(stderr, "Error reading laptop serial number %s\n", strerror(errno));
      return (REG_ERR);
   }
   return (REG_OK);
}

