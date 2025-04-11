#include "../includes/header_files.h"

//this function consumes the remaining characters in the input buffer to avoid subsequent call to funtions
//that require input taking in what is left on the input buffer


int register_student (Entry* entry) {
   init_current_date (entry);
   
   printf ("%s%s\n\t               STUDENT DETAILS                           \n%s%s",
           TC_CYN, TC_BG_WHT, TC_NRM, TC_BG_NRM);

   label1:

   printf ("%s%s\t\tEnter student name:  ", TC_BLU, TC_NRM);
   
   if (fgets (entry -> student.student_name, sizeof (entry -> student.student_name), stdin) != NULL) {
      if (isEmpty (entry -> student.student_name[0], "Student Name")) {
         clear_console ();
         goto label1;
      }
      if (strlen (entry -> student.student_name) < 4) {
         fprintf (stderr, "\t\tName is too short.\n");
         clear_console ();
         goto label1;
      }
      add_terminator (entry -> student.student_name); //check for instance of newline and replace it with null
   }else {
      fprintf (stderr, "\t\tError reading student name %s\n", strerror (errno));
      return  (REG_ERR); //REG_ERR macro defined in variables.h exands to 1
   }

   label2:

   printf ("%s%s\t\tEnter student registration number:  ", TC_BLU, TC_NRM);
   
   if ((fgets (entry -> student.reg_no, sizeof (entry -> student.reg_no), stdin)) != NULL) {
      if (isEmpty (entry -> student.reg_no[0], "Student Registration Number")) {
         goto label2;
      }

      if (strlen (entry -> student.reg_no) < 6) {
         fprintf (stderr, "\t\tRegistration number too short.\n");
         clear_console ();
         goto label2;
      }

      for (char *ch = entry -> student.reg_no; *ch != '\0'; ++ch) {
         if (!isalnum (*ch) && *ch != '/' && *ch != '\0' && *ch != '\n') {
            fprintf (stderr, "\t\tError: Registration number contains invalid characters.\n");
            clear_console ();
            goto label2;
         }
      }
      add_terminator (entry -> student.reg_no); 
   } else {
      fprintf (stderr, "\t\tError reading registration number.\n");
      return (REG_ERR);
   }

   label3:

   printf ("%s%s\t\tEnter student phone number: ", TC_BLU, TC_NRM);
   
   if ((fgets (entry -> student.phone_no, sizeof (entry -> student.phone_no), stdin)) != NULL) {
      if (strlen (entry -> student.phone_no) < 10) {
         fprintf (stderr, "\t\tPhone number too short\n");
         clear_console ();
         goto label3;
      }
      for (char *p = entry -> student.phone_no; *p != '\0'; ++p) {
         if (!isdigit (*p) && *p != '\n') {
            fprintf (stderr, "\t\tError: Phone number contains invalid characters.\n");
            clear_console ();
            goto label3;
         }
      }
      add_terminator (entry -> student.phone_no);
   }else {
      fprintf (stderr, "\t\tError reading phone number.\n");
      return (REG_ERR);
   }
   
   label4:

   printf ("%s%s\t\tEnter student year of study: ", TC_BLU, TC_NRM);
   
   if((fgets (entry -> student.y_of_study, sizeof (entry -> student.y_of_study), stdin)) != NULL) {
      if (isEmpty (entry -> student.y_of_study[0], "Year of study")) {
         goto label4;
      }      
      for (char *ch = entry -> student.y_of_study; *ch != '\0'; ++ch) {
         if (!isalpha (*ch) && *ch != '\n') {
            fprintf (stderr, "\t\tError: year of study contains invalid characters.\n");
            clear_console ();
            goto label4;
         }
      }   
      add_terminator (entry -> student.y_of_study);
   }else {
      fprintf (stderr, "\t\tError reading year of study.\n");
      return  (REG_ERR);
   }
   
   return (REG_OK); //REG_OK macro defined in variables.h expands to 0
}

int register_laptop (Entry* Laptop) {
   printf ("%s%s\n\t               LAPTOP DETAILS                            \n%s%s", 
           TC_CYN, TC_BG_WHT, TC_NRM, TC_BG_NRM);

   label5:

   printf ("%s%s\t\tEnter laptop model: ", TC_BLU, TC_NRM);
   
   if (fgets (Laptop -> laptop.model, sizeof (Laptop -> laptop.model), stdin) != NULL) {
      if (isEmpty (Laptop -> laptop.model[0], "Laptop model")) {
         goto label5;
      }
      add_terminator (Laptop -> laptop.model);
   }else {
      fprintf (stderr, "\t\tError reading laptop model %s\n", strerror (errno));
      return  (REG_ERR);
   }

   label6:

   printf ("%s%s\t\tEnter laptop serial number: ", TC_BLU, TC_NRM);
   
   if (fgets (Laptop -> laptop.serial_no, sizeof (Laptop -> laptop.serial_no), stdin) != NULL) {
      if (isEmpty (Laptop -> laptop.serial_no[0], "Serial Number")) {
         goto label6;
      }
      add_terminator (Laptop -> laptop.serial_no);
   }else {
      fprintf (stderr, "\t\tError reading laptop serial number %s\n", strerror (errno));
      return  (REG_ERR);
   }

   return (REG_OK);
}

