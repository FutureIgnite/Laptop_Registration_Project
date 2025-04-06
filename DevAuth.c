#include "header_files.h"




int main (int argc, char** argv){
    Entries* entry = malloc (sizeof (Entries));
    if (entry == NULL) {
       fprintf (stderr, "%s\n", strerror(errno));
       exit (errno);
    }
    while ((register_student (entry)) == REG_ERR)
    {
        sleep(2);
        system ("clear");
        printf ("Invalid input, please try again.\n");
    }

    while ((register_laptop (entry)) == REG_ERR)
    {
        sleep(2);
        system ("clear");
        printf ("Invalid input, please try again.\n");
    }
    printf ("\n\t=============STUDENT RECORD===========================\n\n");
    printf ("\t\tstudent name: %s\n", entry->student.student_name);
    printf ("\t\tstdudent reg number: %s\n", entry->student.reg_no);
    printf ("\t\tstudent phone number: %s\n", entry->student.phone_no);
    printf ("\t\tstudent year of study: %s\n", entry->student.y_of_study);
    if (strcmp(entry->t_stamp.t_registration, "NULL"))
        printf ("\t\tdate of registration: %s\n", entry->t_stamp.t_registration);
    else
        fprintf (stderr, "\t\tDate of registration not set\n");
    printf ("\t\tlaptop model: %s\n", entry->laptop.model);
    printf ("\t\tlaptop serial number: %s\n", entry->laptop.serial_no);
    printf ("\n\t=====================================================\n\n");
    free (entry);
    
    return 0; 
}
