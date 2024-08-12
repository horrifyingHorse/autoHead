#include "../include/aHeadClass.hpp"
#include <iostream>
using namespace std;

CharQueue::CharQueue() {
  this->head = NULL;
  this->tail = NULL;
}

string CharQueue::enq(string bffr) {
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

string CharQueue::deq() {
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

bool CharQueue::isEmpty() { return (this->tail == NULL) ? true : false; }

ArgsList::ArgsList() { argTail = NULL; }

struct ArgsList::argsNode *ArgsList::argsNodeInsert(string bffr) {
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

void ArgsList::argsNodeDisplay() {
  if (this->argTail == NULL) {
    cout << endl;

    return;
  }
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

ArgsList *UsrCmd::usrInpParser() {
  CharQueue bffr;
  string cmd = "";
  bool escapeCharFlag = false;
  bool dQuotesFlag = false;

  for (char c : this->usrInp) {

    if (!escapeCharFlag) {

      if ((c == ' ' || c == '\t') && !dQuotesFlag) {

        if (cmd == " " || cmd == "")
          continue;

        // Your'e unsure if i am, a loose end or a strand
        // cout << "cmd b4: " << cmd << "!" << endl;
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

UsrCmd::UsrCmd(string usrInp) {
  this->usrInp = usrInp;
  this->totalArgs = 0;
  usrInpParser();
  usrArgs.argsNodeDisplay();
}
