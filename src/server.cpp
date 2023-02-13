//
// Created by magaz1nes on 23/01/2023.
//

void serve(int clients[], int position);

void init_server(int s_socket) {
  int c_sockets[CONNECTION_SIZE] = {};
  int c_count = -1;
  int s_opt = 1;
  //
  if (setsockopt(s_socket,
                 SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT,
                 &s_opt,
                 sizeof(s_opt)) < 0) {
    exit_failure("Server socket set opt fail");
  }
  struct sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);
  auto *address = (struct sockaddr *) &server_addr;
  if (bind(s_socket,
           (struct sockaddr *) &server_addr,
           sizeof(server_addr)) < 0) {
    exit_failure("Server bind fail");
  }
  cout << SYSTEM_NOTICE << "Server bind success" << endl;
  if (listen(s_socket, BACKLOG) < 0) {
    exit_failure("Server listen fail");
  }
  cout << SYSTEM_NOTICE << "Server listening..." << endl;

  while (true) {
    socklen_t slen = sizeof(*address);
    int new_client = accept(s_socket, address, &slen);
    if (new_client < 0) {
      perror("Server fail to accept client connect");
      continue;
    }
    c_count++;
    c_sockets[c_count] = new_client;
    thread t(serve, c_sockets, c_count);
    t.detach();
  }
  shutdown(s_socket, SHUT_RDWR);
}

void serve(int clients[], int position) {
  char buffer[BUFFER_SIZE];
  cout << SYSTEM_NOTICE << "Client accepted!" << endl;
  while (true) {
    if (read(clients[position], buffer, BUFFER_SIZE) < 0) {
      exit_failure("Server read message fail");
    }
    cout << "Client: " << buffer << endl;
    for (int i = 0; i < CONNECTION_SIZE; ++i) {
      if (i == position || clients[i] == 0)
        continue;
      cout << "Sent to client number: " << i << endl;
      if (send(clients[i], buffer, BUFFER_SIZE, 0) < 0) {
        exit_failure("Server send message fail");
      }
    }
  }
}
