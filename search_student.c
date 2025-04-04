#include "header_files.h"

Entries* input (char *buff){
    fgets (buff, sizeof(buff), stdin);
    if (strchr(buff, '\n'))
        buff[strcspn (buff, "\n")] = '\0';
    Entries* entry = check_if_exists (buff);
    return entry;
}

//lookup in the database for the object

Entries* check_if_exists (const char *buff){
    Entries *stdnt;
    if (!(stdnt = (Entries*) malloc (sizeof(Entries)))){
        fprintf (stderr, "Error %s", strerror(errno));
    }
        
}



