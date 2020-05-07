/*
 * logger.c
 *
 *  Created on: Mar 31, 2020
 *      Author: root
 */

#include <logger.h>

void openLogFile() {
	pFile = fopen(LOG_FILE, "a");
	if (pFile == NULL) {
		// TODO handle CT
		exit(1);
	}
}

void writeLog(const char format[], ...) {
	va_list args;
	va_start(args, format);
	vfprintf(pFile, format, args);
	va_end(args);
	fprintf(pFile, "\n");
	fflush(pFile);
}
