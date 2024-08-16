#include <iostream>

#include "../include/aHeadClass.hpp"
#include "../include/aHeadFncs.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  string usrInp = "";
  UsrCmd initcmd(usrInp);

  populateCliCmdMap();

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
    execute(cmd);
  }

  return 0;
}
