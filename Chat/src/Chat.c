/*
 ============================================================================
 Name        : Chat.c
 Author      : jcf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <logger.h>
#include <server.h>

#define CMD_QUIT "!quit"

int end = 0;

struct sockaddr_in sockAddrClient;

void registerSignal();
void signalHandler(int lesignal);

int main(void) {
	daemon(0, 0);
	registerSignal();
	openLogFile();
	writeLog("Starting daemon with PID %i", getpid());
	int socketServer = initSocket();
	int socketClient;
	int addrLen = sizeof(socketClient);
	writeLog("Waiting for incoming connections...");
	while (end == 0) {
		socketClient = accept(socketServer, (struct sockaddr*) &sockAddrClient,
				(socklen_t*) &addrLen);
		if (socketClient != - 2) {
			// TODO Passage en mode non bloquant, sinon read attend
			// fcntl(socketClient, F_SETFL, O_NONBLOCK);
			// Convertion de l'IP en texte
			char ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(sockAddrClient.sin_addr), ip,
			INET_ADDRSTRLEN);
			writeLog("Connexion de %s:%i", ip, sockAddrClient.sin_port);
			send(socketClient, "Welcome", sizeof("Welcome"),
			MSG_DONTWAIT);
			int con = 0;
			char buffer[BUFFER_LEN] = "";
			while (con == 0) {
				int len = read(socketClient, buffer, BUFFER_LEN - 1);
				buffer[len - 1] = '\0';
				if (len > 0) {
					writeLog("Receiving [%s]", buffer);
					if (strcmp(buffer, CMD_QUIT) == 0) {
						send(socketClient, "Bye.\n", sizeof("Bye.\n"),
						MSG_DONTWAIT);
						con = 1;
					} else {
						char msg[] = "You said: ";
						char toSend[strlen(msg) + len + 1];
						sprintf(toSend, "%s%s", msg, buffer);
						send(socketClient, toSend, sizeof(toSend),
						MSG_DONTWAIT);
					}
				}
				sleep(1);
			}
			close(socketClient);
		}
		sleep(1);
	}
	close(socketServer);
	writeLog("Stopping with PID %i", getpid());
	fclose(pFile);
	return EXIT_SUCCESS;
}

void registerSignal() {
	signal(2, signalHandler);
	signal(15, signalHandler);
}

void signalHandler(int lesignal) {
	writeLog("Le signal: %i", lesignal);
	end = 1;
}
