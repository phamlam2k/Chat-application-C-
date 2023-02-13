//
// Created by magaz1nes on 29/01/2023.
//
#include "bits/stdc++.h"
using namespace std;
int main() {
  int arr[10] = {};
  if (fork() == 0) {
    for (int I = 0; I < 10; ++I) {
      arr[I] = 1;
    }
    cout << arr[0] << endl;
  } else {
    for (int I = 0; I < 500000; ++I) {
    }
    for (int I = 0; I < 10; ++I) {
      cout << arr[I] << "|";
    }
  }
  return 0;
}
