/*
 * logger.h
 *
 *  Created on: Mar 31, 2020
 *      Author: root
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define LOG_FILE "/var/log/chatd.log"
FILE *pFile;

void openLogFile();
void writeLog(const char message[], ...);

#endif /* LOGGER_H_ */
