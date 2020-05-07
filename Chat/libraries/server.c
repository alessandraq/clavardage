/*
 * server.c
 *
 *  Created on: Mar 31, 2020
 *      Author: root
 */

#include <server.h>

// Démarrage de la socket serveur
int initSocket() {
	sockAddrServer.sin_family = AF_INET;
	sockAddrServer.sin_addr.s_addr = INADDR_ANY;
	sockAddrServer.sin_port = htons(PORT);
	// Descripteur de socket
	int fdsocket;
	// Nombre d'options
	int opt = 1;
	// Création de la socket en TCP
	if ((fdsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		writeLog("Echéc de la création: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	writeLog("Création de la socket");
	// Paramètrage de la socket
	if (setsockopt(fdsocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
			sizeof(opt)) != 0) {
		writeLog("Echéc de paramètrage: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	writeLog("Paramètrage de la socket\n");
	// Attachement de la socket sur le port et l'adresse IP
	if (bind(fdsocket, (struct sockaddr*) &sockAddrServer,
			sizeof(sockAddrServer)) != 0) {
		writeLog("Echéc d'attachement: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	writeLog("Attachement de la socket sur le port %i\n", PORT);
	// Passage en écoute de la socket
	if (listen(fdsocket, BACKLOG) != 0) {
		writeLog("Echéc de la mise en écoute: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	// Passage en mode non bloquant
	// fcntl(fdsocket, F_SETFL, O_NONBLOCK);
	writeLog("Mise en écoute de la socket\n");
	return fdsocket;
}


