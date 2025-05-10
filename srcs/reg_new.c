#include "../includes/header_files.h"

int register_student (Entry* entry, WINDOW* child) {
   char *ch;
   char *p;

   box (child, 4, 4);
   init_current_date (entry, child);
   
   wprintw (child, "\n\t\t\tSTUDENT DETAILS\n");
   wrefresh (child);

   label1:

   wprintw (child, "\t\tEnter student name:  ");
   wrefresh (child);

   if (wgetstr (child, entry -> student.student_name) != ERR) {
      if (isEmpty (entry -> student.student_name[0], "Student Name", child)) {
         wclear (child);
         box (child, 4, 4);
         wrefresh (child);
         goto label1;
      }
      if (strlen (entry -> student.student_name) < 4) {
         wprintw (child, "\t\tName is too short.\n");
         wrefresh (child);
         wclear (child);
         box (child, 4, 4);
         wrefresh (child);
         goto label1;
      }
      add_terminator (entry -> student.student_name, sizeof (entry -> student.reg_no),
                      strlen (entry -> student.reg_no), child);
   }else {
      wprintw (child, "\t\tError reading student name %s\n", strerror (errno));
      wrefresh (child);
      return  (REG_ERR);
   }

   label2:

   wprintw (child, "\t\tEnter student registration number:  ");
   wrefresh (child);

   if ((wgetstr (child, entry -> student.reg_no) != ERR)) {
      if (isEmpty (entry -> student.reg_no[0], "Student Registration Number", child)) {
         goto label2;
      }

      if (strlen (entry -> student.reg_no) < 6) {
         wprintw (child, "\t\tRegistration number too short.\n");
         wrefresh (child);
         wclear (child);
         box (child, 4, 4);
         wrefresh (child);
         goto label2;
      }

      for (ch = entry -> student.reg_no; *ch != '\0'; ++ch) {
         if (!isalnum (*ch) && *ch != '/' && *ch != '\0' && *ch != '\n') {
            wprintw (child, "\t\tError: Registration number contains invalid characters.\n");
            wrefresh (child);
            wclear (child);
            box (child, 4, 4);
            wrefresh (child);
            goto label2;
         }
      }
      add_terminator (entry -> student.reg_no, sizeof (entry -> student.reg_no),
                      strlen (entry -> student.reg_no), child); 
   } else {
      wprintw (child, "\t\tError reading registration number.\n");
      wrefresh (child);
      return (REG_ERR);
   }

   label3:

   wprintw (child, "\t\tEnter student phone number: ");
   wrefresh (child);

   if ((wgetstr (child, entry -> student.phone_no) != ERR)) {
      if (strlen (entry -> student.phone_no) < 10) {
         wprintw (child, "\t\tPhone number too short\n");
         wrefresh (child);
         wclear (child);
         box (child, 4, 4);
         wrefresh (child);
         goto label3;
      }
      for (p = entry -> student.phone_no; *p != '\0'; ++p) {
         if (!isdigit (*p) && *p != '\n') {
            wprintw (child, "\t\tError: Phone number contains invalid characters.\n");
            wrefresh (child);
            wclear (child);
            box (child, 4, 4);
            wrefresh (child);
            goto label3;
         }
      }
      add_terminator (entry -> student.phone_no, sizeof (entry -> student.reg_no),
                      strlen (entry -> student.reg_no), child);
   }else {
      wprintw (child, "\t\tError reading phone number.\n");
      wrefresh (child);
      return (REG_ERR);
   }
   
   label4:

   wprintw (child, "\t\tEnter student year of study: ");
   wrefresh (child);

   if((wgetstr (child, entry -> student.y_of_study)) != ERR) {
      if (isEmpty (entry -> student.y_of_study[0], "Year of study", child)) {
         goto label4;
      }      
      for (ch = entry -> student.y_of_study; *ch != '\0'; ++ch) {
         if (!isalpha (*ch) && *ch != '\n') {
            wprintw (child, "\t\tError: year of study contains invalid characters.\n");
            wrefresh (child);
            wclear (child);
            box (child, 4, 4);
            wrefresh (child);
            goto label4;
         }
      }   
      add_terminator (entry -> student.y_of_study, sizeof (entry -> student.reg_no),
                      strlen (entry -> student.reg_no), child);
   }else {
      wprintw (child, "\t\tError reading year of study.\n");
      wrefresh (child);
      return  (REG_ERR);
   }
   
   return (REG_OK);
}

int register_laptop (Entry* Laptop, WINDOW* child) {
   box (child, 4, 4);
   wprintw (child, "\n\t\t\tLAPTOP DETAILS \n");
   wrefresh (child);

   label5:

   wprintw (child, "\t\tEnter laptop model: ");
   wrefresh (child);

   if (wgetstr (child, Laptop -> laptop.model) != ERR) {
      if (isEmpty (Laptop -> laptop.model[0], "Laptop model", child)) {
         wclear (child);
         box (child, 4, 4);
         wrefresh (child);
         goto label5;
      }
      add_terminator (Laptop -> laptop.model, sizeof (Laptop -> student.reg_no),
                      strlen (Laptop -> student.reg_no), child);
   } else {
      wprintw (child, "\t\tError reading laptop model %s\n", strerror (errno));
      wrefresh (child);
      return  (REG_ERR);
   }

   label6:

   wprintw (child, "\t\tEnter laptop serial number: ");
   wrefresh (child);

   if (wgetstr (child, Laptop -> laptop.serial_no) != ERR) {
      if (isEmpty (Laptop -> laptop.serial_no[0], "Serial Number", child)) {
         wclear (child);
         box (child, 4, 4);
         wrefresh (child);
         goto label6;
      }
      add_terminator (Laptop -> laptop.serial_no, sizeof (Laptop -> student.reg_no),
                      strlen (Laptop -> student.reg_no), child);
   } else {
      wprintw (child, "\t\tError reading laptop serial number %s\n", strerror (errno));
      wrefresh (child);
      return  (REG_ERR);
   }

   return (REG_OK);
}
