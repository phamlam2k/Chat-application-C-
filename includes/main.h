//
// Created by magaz1nes on 22/01/2023.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <thread>

using namespace std;

#ifndef C_BASE_MAIN_H
#define C_BASE_MAIN_H

#define IP_PROTOCOL 0
#define PORT 8075
#define BACKLOG 3
#define CONNECTION_SIZE (BACKLOG * 10)
#define BUFFER_SIZE 1024
#define SYSTEM_NOTICE "[#]~"
#define END_CHAT "#end"

class [[maybe_unused]] main {
};

#endif //C_BASE_MAIN_H
