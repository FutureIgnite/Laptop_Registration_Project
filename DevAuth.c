#include "header_files.h"

int main (int argc, char** argv){
    Entries* entry = malloc (sizeof (Entries));
    if (entry == NULL) {
       fprintf (stderr, "%s\n", strerror(errno));
       exit (errno);
    }
    while ((register_student (entry)) == REG_ERR)
    {
        system ("clear");
        printf ("Invalid input, please try again.\n");
    }
    laptop_entries* laptops = malloc (sizeof (laptop_entries));
    if (laptops == NULL) {
       fprintf (stderr, "%s\n", strerror(errno));
       exit (errno);
    }
    while ((register_laptop (laptops)) == REG_ERR)
    {
        system ("clear");
        printf ("Invalid input, please try again.\n");
    }
    
    printf ("student name: %s\n", entry->student.student_name);
    printf ("stdudent reg number: %s\n", entry->student.reg_no);
    printf ("student phone number: %s\n", entry->student.phone_no);
    printf ("student year of study: %s\n", entry->student.y_of_study);

    printf ("laptop model: %s\n", laptops->laptop.model);
    printf ("laptop serial number: %s\n", laptops->laptop.serial_no);

    free (entry); 
    free (laptops);
    return 0; 
}
