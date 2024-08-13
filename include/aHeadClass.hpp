#ifndef AHEADCLASS_HPP
#define AHEADCLASS_HPP

#include <string>

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

  ArgsList *usrInpParser();

public:
  UsrCmd(std::string usrInp);

  std::string baseCmd();
};

#endif // !aHeadClass_HPP
