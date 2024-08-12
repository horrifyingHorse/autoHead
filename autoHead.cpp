#include <cstddef>
#include <cstdlib>
#include <iostream>
using namespace std;

class CharQueue {
private:
  struct qNode {
    struct qNode *plink;
    string chr;
    struct qNode *nlink;
  };

  struct qNode *head;
  struct qNode *tail;

public:
  CharQueue() {
    this->head = NULL;
    this->tail = NULL;
  }

  string enq(string bffr) {
    struct qNode *temp = new qNode;
    temp->plink = NULL;
    temp->chr = bffr;
    temp->nlink = this->head;

    if (this->head != NULL) {
      this->head->plink = temp;
    }

    this->head = temp;

    if (this->tail == NULL) {
      this->tail = temp;
    }

    return bffr;
  }

  string deq() {
    string bffr;

    if (this->tail == NULL) {
      return "";
    }

    bffr = this->tail->chr;

    if (this->tail == this->head) {
      this->head = NULL;
      free(this->tail);
      this->tail = NULL;

      return bffr;
    }

    this->tail = this->tail->plink;
    free(this->tail->nlink);
    this->tail->nlink = this->head;

    return bffr;
  }

  bool isEmpty() { return (this->tail == NULL) ? true : false; }
};

class ArgsList {
private:
  struct argsNode {
    string arg;
    struct argsNode *link;
  };

  struct argsNode *argTail;

public:
  ArgsList() { argTail = NULL; }

  struct argsNode *argsNodeInsert(string bffr) {
    struct argsNode *temp = new argsNode;
    temp->arg = bffr;
    temp->link = NULL;

    if (this->argTail == NULL) {
      this->argTail = temp;
      this->argTail->link = this->argTail;
      return this->argTail;
    }

    temp->link = this->argTail->link;
    this->argTail->link = temp;
    this->argTail = temp;

    return this->argTail;
  }

  void argsNodeDisplay() {
    struct argsNode *temp = this->argTail->link;
    bool flag = false;

    while (!flag) {
      cout << temp->arg << " :: ";

      if (temp == this->argTail) {
        flag = true;
      }

      temp = temp->link;
    }

    cout << endl;
  }
};

class UsrCmd {
private:
  string usrInp;
  int totalArgs;
  ArgsList usrArgs; // user args in a circular linked list

  ArgsList *usrInpParser() {
    CharQueue bffr;
    string cmd = "";
    bool escapeCharFlag = false;
    bool dQuotesFlag = false;

    for (char c : this->usrInp) {

      if (!escapeCharFlag) {

        if ((c == ' ' || c == '\t') && !dQuotesFlag) {

          if (cmd == " " || cmd == "")
            continue;

          cout << "cmd b4: " << cmd << "!" << endl;
          bffr.enq(cmd);
          cmd = "";
          continue;

        } else if (c == '\\') {
          escapeCharFlag = true;
        } else if (c == '\"') {
          dQuotesFlag = !dQuotesFlag;
        }

      } else {
        escapeCharFlag = false;
      }

      cmd += c;
    }

    if (cmd != "") {
      bffr.enq(cmd);
    }

    while (!bffr.isEmpty()) {
      this->usrArgs.argsNodeInsert(bffr.deq());
    }

    return NULL;
  }

public:
  UsrCmd(string usrInp) {
    this->usrInp = usrInp;
    this->totalArgs = 0;
    usrInpParser();
    usrArgs.argsNodeDisplay();
  }
};

void autoHead() {
  cout << "autoHead\nez autoGen Header Files 4u <3" << endl << endl;
}

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
