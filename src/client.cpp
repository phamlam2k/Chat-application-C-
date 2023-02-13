//
// Created by magaz1nes on 23/01/2023.
//

void client_read(int s_socket, char *buffer);
void client_send(int s_socket, char *msg);
void init_client(int s_socket) {
  int c_socket;
  char buffer[BUFFER_SIZE];
  char msg[BUFFER_SIZE];
  struct sockaddr_in sv_addr{};
  sv_addr.sin_family = AF_INET;
  sv_addr.sin_port = htons(PORT);
  sv_addr.sin_addr.s_addr = INADDR_ANY;
  auto *address = (struct sockaddr *) &sv_addr;
  //
  if ((c_socket = connect(s_socket, address, sizeof(*address))) < 0) {
    exit_failure("Client connect fail");
  }
  cout << SYSTEM_NOTICE << "Client connect success" << endl;

  if (fork() == 0) {
    client_send(s_socket, msg);
  } else {
    client_read(s_socket, buffer);
  }
  close(c_socket);
}

void client_send(int s_socket, char *msg) {
  while (true) {
    cout << "Client type: ";
    cin >> msg;
    if (send(s_socket, msg, sizeof(msg), 0) < 0) {
      exit_failure("Server read message fail");
    }
  }
}
void client_read(int s_socket, char *buffer) {
  while (true) {
    if (read(s_socket, buffer, BUFFER_SIZE) < 0) {
      exit_failure("Client read fail");
    }
    cout << buffer << endl;
  }
}

