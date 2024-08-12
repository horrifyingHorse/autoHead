// #include <cstddef>
// #include <cstdlib>
#include <iostream>

#include "../include/aHeadClass.hpp"
#include "../include/aHeadFncs.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string usrInp = "";

  if (argc > 1) {
    for (int i = 0; i < argc; i++) {
      cout << argv[i] << endl;
    }
  }

  autoHead();

  while (usrInp != "exit") {
    cout << ": ";
    getline(cin, usrInp);
    cout << endl;

    UsrCmd cmd(usrInp);
  }

  return 0;
}
