//
// Created by magaz1nes on 22/01/2023.
//
#include "includes/main.h"
#include "src/core/functions/common.cpp"
#include "src/client.cpp"
#include "src/server.cpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  int sockfd = socket(AF_INET, SOCK_STREAM, IP_PROTOCOL);
  if (sockfd < 0) {
    exit_failure("Socket init fail");
  }
  if (*argv[1] == 's') {
    init_server(sockfd);
  } else if (*argv[1] == 'c') {
    init_client(sockfd);
  } else {
    exit_failure("Invalid option");
  }
  return 0;
}
