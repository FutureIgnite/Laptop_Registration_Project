#include "../includes/header_files.h"

int main () {
    if (db_init ()) {
        fprintf (stderr, "Could not initialize a database\n");
        exit (EXIT_FAILURE);
    }

    printf ("Database initialized succesfully\n");

    Entry* entry;
    if (!(entry = malloc (sizeof (Entry)))) {
       fprintf (stderr, "%s\n", strerror(errno));
       exit (errno);
    }

    prompt (entry);
    free (entry);
    
    return 0; 
}
