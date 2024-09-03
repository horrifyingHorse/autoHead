#ifndef AHEADCLASS_HPP
#define AHEADCLASS_HPP

#include <string>
#include <unordered_map>
#include <vector>

class CharQueue {
private:
  struct qNode {
    struct qNode *plink;
    std::string chr;
    struct qNode *nlink;
  };

  struct qNode *head;
  struct qNode *tail;

public:
  CharQueue();

  std::string enq(std::string bffr);

  std::string deq();

  std::string remLatestEnq();

  bool isEmpty();
};

class ArgsList {
private:
  struct argsNode {
    std::string arg;
    struct argsNode *link;
  };

  struct argsNode *argTail;
  int size;

public:
  ArgsList();

  struct argsNode *argsNodeInsert(std::string bffr);

  std::string at(int index);

  void argsNodeDisplay();
};

class UsrCmd {
private:
  std::string usrInp;
  int totalArgs;
  ArgsList usrArgs; // user args in a circular linked list
  int usrArgPtr;

  ArgsList *usrInpParser();

public:
  UsrCmd(std::string usrInp);

  std::string baseCmd();

  std::string nextCmd();

  std::string prevCmd();
};

// conduit
class CppParser {
private:
  // flags
  bool fSingleLineComment;
  bool fEscapeChar;
  bool fDoubleQuotes;
  bool fSingleQuotes;

  // parserFlags
  bool pfUpdate;
  bool pfPreprocessorCmd;
  bool pfDeclaredDataType;

  // Parsed strings
  std::string parsedBffr;
  std::vector<std::string> preprocessor_cmd;
  std::vector<std::string> globalVariables;
  std::vector<std::string> functionDeclaration;

  // Maps
  std::unordered_map<std::string, int (CppParser::*)()> cppMap;

  // Misc
  CharQueue bffr_q;
  std::string cmd;
  std::vector<std::string> cmdBffr;

  // Functions
  void resetFlags();

  void internalParser();

  void populateParserMap();

  int cpp_include();

public:
  CppParser();

  void parse(std::string &bffr);

  // for test onlu
  void displayParsedBffr();
};

#endif // !aHeadClass_HPP
