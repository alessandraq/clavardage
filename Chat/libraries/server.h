/*
 * server.h
 *
 *  Created on: Mar 31, 2020
 *      Author: root
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <logger.h>

#define BUFFER_LEN 200
#define PORT 1234
#define BACKLOG 3

struct sockaddr_in sockAddrServer;

int initSocket();

#endif /* SERVER_H_ */
