#include <iostream>

#include <functional>
#include <unordered_map>
#include <variant>

#include "../include/aHeadClass.hpp"
#include "../include/aHeadFncs.hpp"

using namespace std;
using ReturnType = variant<int>;

unordered_map<string, function<ReturnType()>> cliCmdMap;

void populateCliCmdMap() {
  cliCmdMap["exit"] = []() { return autoHeadExit(); };

  return;
}

int execute(UsrCmd cmd) {
  cout << "check to exec....\n";
  if (cliCmdMap.find(cmd.baseCmd()) != cliCmdMap.end()) {
    cout << "Executing /" << endl;
    cliCmdMap[cmd.baseCmd()]();
  }

  return 0;
}

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
