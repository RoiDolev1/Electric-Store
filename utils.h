//* Oren Nizry - ID:208708784 *//
//* Roi Dolev - ID:207252479 *//
#pragma once

// Utility functions for logging and handling date/time.
void logAction(char* action);// Logs an action with a timestamp to the log file.
void getCurrentDate(char* outDate);// Gets the current date/time as a string in "YYYY-MM-DD HH:MM:SS" format.
int dateDifferenceInDays(char* date1, char* date2);// Computes a difference in days between two date strings.

