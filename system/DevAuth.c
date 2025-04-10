#include "header_files.h"

int main (){
   
    //initscr ();

    printf  ("%s", TC_BG_NRM);
    //printf  ("%s%sProgram Stats\n%s", TC_YEL, TC_BG_NRM, TC_NRM);
    create_new_screen();
    Entry* entry = malloc (sizeof (Entry));
    if (entry == NULL) {
       fprintf (stderr, "%s\n", strerror (errno));
       exit (errno);
    }

    if (register_student (entry) == REG_ERR)
        printf ("Cannot register student.\n");

    if (register_laptop (entry) == REG_ERR)
        printf ("Cannot register laptop.\n");

    printw ("%s%s\n\t                STUDENT RECORD                         \n\n%s%s",
            TC_YEL, TC_BG_CYN, TC_NRM, TC_BG_NRM);

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
    printf ("%s%s\n\t                                                   \n\n%s%s",
            TC_YEL, TC_BG_CYN, TC_NRM, TC_BG_NRM);
    //refresh ();
    free (entry);
    
    exit_screen();
    return 0; 
}
