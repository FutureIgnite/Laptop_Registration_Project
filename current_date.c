// This program gets the current date and time using the time.h library
#include <time.h>

struct tm* current_date() {
    time_t now;
    struct tm *current_date; 
    time(&now); // Get the current time
    current_date = localtime(&now); // Convert to local time structure   
    return current_date;
}

// // Print the current date and time
// printf("Current Date and Time: %02d-%02d-%04d %02d:%02d:%02d\n",
//     current_date->tm_mday,       // Day of the month
//     current_date->tm_mon + 1,   // Month (0-based, so add 1)
//     current_date->tm_year + 1900, // Year (since 1900, so add 1900)
//     current_date->tm_hour,      // Hours
//     current_date->tm_min,       // Minutes
//     current_date->tm_sec); // Seconds