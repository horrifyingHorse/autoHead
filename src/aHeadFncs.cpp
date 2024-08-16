#include "../include/aHeadFncs.hpp"
#include "../include/aHeadClass.hpp"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

using ReturnType = int (*)(const UsrCmd &);

std::unordered_map<std::string, ReturnType> cliCmdMap;

int autoHead() {
  std::cout << "autoHead\nez autoGen Header Files 4u <3" << std::endl
            << std::endl;

  return 0;
}

// mapped functions
int ahProcess_exit(const UsrCmd &cmd) {
  exit(0);
  return 0;
}

// map related
void populateCliCmdMap() {
  cliCmdMap["exit"] = ahProcess_exit;

  return;
}

int execute(UsrCmd &cmd) {
  if (cliCmdMap.find(cmd.baseCmd()) != cliCmdMap.end()) {
    cliCmdMap[cmd.baseCmd()](cmd);
  }

  return 0;
}
