//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define LOG_FILE "log.txt"  // Log file (text file)

// Appends a log entry with the current timestamp to the log file.
void logAction(char* action) {
    FILE* file = fopen(LOG_FILE, "a");
    if (!file) {
        return;
    }
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    char formattedTime[80];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", lt);
    fprintf(file, "[%s] %s\n", formattedTime, action);
    fclose(file);
}

// Gets the current date/time as a string ("YYYY-MM-DD HH:MM:SS").
void getCurrentDate(char* outDate) {
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    strftime(outDate, 20, "%Y-%m-%d %H:%M:%S", lt);
}

// Computes a difference in days between two dates.
// (This calculation assumes 365 days/year and 30 days/month.)
int dateDifferenceInDays(char* date1, char* date2) {
    int y1, m1, d1;
    int y2, m2, d2;
    sscanf(date1, "%d-%d-%d", &y1, &m1, &d1);
    sscanf(date2, "%d-%d-%d", &y2, &m2, &d2);
    int total1 = y1 * 365 + m1 * 30 + d1;
    int total2 = y2 * 365 + m2 * 30 + d2;
    return (total2 - total1);
}
