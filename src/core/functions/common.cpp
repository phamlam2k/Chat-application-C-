//
// Created by magaz1nes on 23/01/2023.
//

void exit_failure(const string &error_msg) {
  perror(error_msg.c_str());
  exit(EXIT_FAILURE);
}
