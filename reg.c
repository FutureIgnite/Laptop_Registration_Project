#include "header_files.h"

//this function consumes the remaining characters in the input buffer to avoid subsequent call to funtions
//that require input taking in what is left on the input buffer
void flush_input_buff () {
   char ch;
   while ((ch = getchar()) != '\n' && ch != EOF);
}

void init_current_date () {
   struct tm *current_d = current_date();
   if (current_d != NULL) {
      char date_str[11]; // Buffer to hold the formatted date string (dd-mm-yyyy + null terminator)
      if (strftime(date_str, sizeof(date_str), "%d-%m-%Y", current_d)) {
         printf("Current date: %s\n", date_str);
      } else {
         fprintf(stderr, "Error formatting the current date.\n");
      }
   } else {
      fprintf(stderr, "Error retrieving the current date.\n");
   }
}

/* 
I think this should be first time registration because it would be 
useless and time consuming to key in this credentials every time 
a student is at the gate , the solution is to save this meatadata 
in a qr code uniquely for every student. So i think we need another file
*/

/* Also should this data not be saved in a database? */
int register_student (Entries* entry) {
   init_current_date ();
   printf ("....Enter student details....\n");
   printf ("Enter student name:  "); 
   /* Here i think if student name doesn't march the students on our database
   should also return error to the standard error because we cannot be registering a laptop
   of a student who is not in our school*/
   if (fgets(entry->student.student_name, sizeof(entry->student.student_name), stdin) != NULL){
      if (strlen(entry->student.student_name) < 4){
         fprintf (stderr, "Name is too short.\n");
         return REG_ERR;
      } 
      if (strchr(entry->student.student_name, '\n')) //check for instance of newline and replace it with null
         entry->student.student_name[strcspn(entry->student.student_name, "\n")] = '\0';
      else 
         flush_input_buff ();
   }else {
      fprintf(stderr, "Error reading student name %s\n", strerror(errno));
      return (REG_ERR); //REG_ERR macro defined in variables.h exands to 1
   }
   printf ("Enter student registration number:  ");
   if (scanf("%19s", entry->student.reg_no) == 1){
      flush_input_buff (); //to flush the input buffer;
      if (strlen(entry->student.reg_no) < 6){
         fprintf (stderr, "Registration number too short.\n");
         return REG_ERR;
      }
      for (char *ch = entry->student.reg_no; *ch != '\0'; ++ch) {
         if (!isalnum(*ch) && *ch != '/' && *ch != '\0' && *ch != ' ') {
            fprintf(stderr, "Error: Registration number contains invalid characters.\n");
            return (REG_ERR);
         }
      }
   } else {
      fprintf(stderr, "Error reading registration number.\n");
      return (REG_ERR);
   }
   printf ("Enter student phone number: ");// print newline character
   if ((scanf ("%14s", entry->student.phone_no)) == 1){
      flush_input_buff ();
      if (strlen(entry->student.phone_no) < 10) {
         fprintf (stderr, "Phone number too short\n");
         return REG_ERR;
      }
      for (char *p = entry->student.phone_no; *p != '\0'; ++p){
         if (!isdigit(*p)){
            fprintf (stderr, "Error: Phone number contains invalid characters.\n");
            return (REG_ERR);
         }
      }
   }else {
      fprintf (stderr, "Error reading phone number.\n");
      return (REG_ERR);
   } 
   printf ("Enter student year of study: ");
   if((scanf ("%8s", entry->student.y_of_study)) == 1) {
      flush_input_buff ();
      for (char *ch = entry->student.y_of_study; *ch != '\0'; ++ch){
         if (!isalpha(*ch)){
            fprintf (stderr, "Error: year of study contains invalid characters.\n");
            return (REG_ERR);
         }
      }
   }else {
      fprintf (stderr, "Error reading year of study.\n");
      return (REG_ERR);
   }
   return (REG_OK); //REG_OK macro defined in variables.h expands to 0
}

int register_laptop (Entries* Laptop) {
   printf ("....Enter laptop details....\n");
   printf ("Enter laptop model: ");
   if (fgets(Laptop->laptop.model, sizeof(Laptop->laptop.model), stdin) != NULL) {
      if (strchr(Laptop->laptop.model, '\n')) 
         Laptop->laptop.model[strcspn(Laptop->laptop.model, "\n")] = '\0';
      else
         flush_input_buff ();
   }else {
      fprintf(stderr, "Error reading laptop model %s\n", strerror(errno));
      return (REG_ERR);
   }
   printf ("Enter laptop serial number: ");
   if (fgets(Laptop->laptop.serial_no, sizeof(Laptop->laptop.serial_no), stdin) != NULL) {
      if (strchr(Laptop->laptop.serial_no, '\n')) 
         Laptop->laptop.serial_no[strcspn(Laptop->laptop.serial_no, "\n")] = '\0';
      else 
         flush_input_buff ();
   }else {
      fprintf(stderr, "Error reading laptop serial number %s\n", strerror(errno));
      return (REG_ERR);
   }
   return (REG_OK);
}

