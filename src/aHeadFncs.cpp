#include "../include/aHeadFncs.hpp"
#include "../include/aHeadClass.hpp"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

#include <fstream>

using ReturnType = int (*)(UsrCmd &);

std::unordered_map<std::string, ReturnType> cliCmdMap;

int autoHead() {
  std::cout << "autoHead\nez autoGen Header Files 4u <3" << std::endl
            << std::endl;

  return 0;
}

// mapped functions
int ahProcess_exit(UsrCmd &cmd) {
  exit(0);
  return 0;
}

// baseCmd "fileDir/file.cpp" ["headerFilename.hpp"]
int ahProcess_gen(UsrCmd &cmd) {
  std::string cppFile = cmd.nextCmd();
  CppParser conduit;

  // remove "" if exists
  if (cppFile[0] == '\"') {
    cppFile = cppFile.substr(1, cppFile.size() - 2);
  }

  std::ifstream inCppFile(cppFile);
  if (!inCppFile.is_open()) {
    std::cout << "Invalid filePath;" << std::endl;
    std::cout << "File \"" << cppFile << "\" not Found." << std::endl;
    std::cout << std::endl;

    return 1;
  }

  std::string line;
  while (std::getline(inCppFile, line)) {
    //    std::cout << line << std::endl;
    conduit.parse(line);
  }

  conduit.displayParsedBffr();

  inCppFile.close();

  return 0;
}

// map related
void populateCliCmdMap() {
  cliCmdMap["exit"] = ahProcess_exit;
  cliCmdMap["q"] = ahProcess_exit;
  cliCmdMap["-g"] = ahProcess_gen;

  return;
}

int execute(UsrCmd &cmd) {
  std::string cmd4Exe = cmd.baseCmd();

  if (cmd4Exe == "ahead") {
    cmd4Exe = cmd.nextCmd();
  }

  if (cliCmdMap.find(cmd4Exe) != cliCmdMap.end()) {
    cliCmdMap[cmd4Exe](cmd);
  }

  return 0;
}
