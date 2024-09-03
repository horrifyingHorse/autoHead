#include "../include/aHeadClass.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

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

std::string CharQueue::remLatestEnq() {
  if (this->head == NULL) {
    cout << "remEnqErr: Trying to access CharQueue head but points to NULL"
         << endl;
    return "";
  }

  std::string latestEnqData = this->head->chr;
  struct qNode *temp = this->head;

  if (this->tail == this->head) {
    this->head = NULL;
    free(this->tail);
    this->tail = NULL;

    return latestEnqData;
  }

  this->head = this->head->nlink;
  this->head->plink = this->tail;
  this->tail->nlink = this->head;

  free(temp);

  return latestEnqData;
}

bool CharQueue::isEmpty() { return (this->tail == NULL) ? true : false; }

ArgsList::ArgsList() {
  argTail = NULL;
  this->size = 0;
}

struct ArgsList::argsNode *ArgsList::argsNodeInsert(string bffr) {
  struct argsNode *temp = new argsNode;
  temp->arg = bffr;
  temp->link = NULL;

  this->size++;

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

std::string ArgsList::at(int index) {
  if (index >= this->size || index < 0) {
    return "";
  }

  struct argsNode *head = this->argTail->link;

  while (index != 0) {
    head = head->link;
    index--;
  }

  return head->arg;
}

void ArgsList::argsNodeDisplay() {
  if (this->argTail == NULL) {
    cout << endl;

    return;
  }
  struct argsNode *temp = this->argTail->link;
  bool flag = false;

  while (!flag) {
    // cout << temp->arg << " :: ";

    if (temp == this->argTail) {
      flag = true;
    }

    temp = temp->link;
  }

  // cout << endl;
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
  this->usrArgPtr = 1;
  usrInpParser();
  usrArgs.argsNodeDisplay();
}

std::string UsrCmd::baseCmd() { return this->usrArgs.at(0); }

std::string UsrCmd::nextCmd() {
  string bffr = this->usrArgs.at(this->usrArgPtr);
  if (bffr != "") {
    this->usrArgPtr++;
  }

  return bffr;
}

std::string UsrCmd::prevCmd() {
  if (usrArgPtr >= 0) {
    this->usrArgPtr--;
  }

  return this->usrArgs.at(this->usrArgPtr);
}

CppParser::CppParser() {
  this->fSingleLineComment = false;
  this->fSingleQuotes = false;

  this->cmd = "";
  this->parsedBffr = "";

  CppParser::populateParserMap();
}

void CppParser::resetFlags() {
  this->fSingleLineComment = false;
  this->fEscapeChar = false;
  this->fDoubleQuotes = false;
  this->fSingleQuotes = false;
}

void CppParser::parse(std::string &bffr) {
  CppParser::resetFlags();

  this->cmdBffr.clear();
  this->cmd = "";

  char prev_c = ' ';

  for (char c : bffr) {

    if (!this->fEscapeChar) {

      if ((c == ' ' || c == '\t') && !this->fDoubleQuotes) {

        if (this->cmd == " " || this->cmd == "")
          continue;

        // Your'e unsure if i am, a loose end or a strand
        // cout << "this->cmd b4: " << this->cmd << "!" << endl;
        this->bffr_q.enq(this->cmd);
        this->cmd = "";
        continue;

      } else if (c == '\\') {
        this->fEscapeChar = true;
      } else if (c == '\"') {
        this->fDoubleQuotes = !this->fDoubleQuotes;
      } else if (c == '/' && prev_c == '/' && !this->fDoubleQuotes) {
        this->fSingleLineComment = true;
        this->cmd = this->cmd.substr(0, this->cmd.size() - 1);
      }

    } else {
      this->fEscapeChar = false;
    }

    if (fSingleLineComment) {
      break;
    }

    this->cmd += c;
    prev_c = c;
  }

  if (this->cmd != "") {
    this->bffr_q.enq(this->cmd);
  }

  while (!this->bffr_q.isEmpty()) {
    this->cmdBffr.push_back(this->bffr_q.deq());
  }

  CppParser::internalParser();

  return;
}

void CppParser::internalParser() {
  this->pfUpdate = false;
  this->pfPreprocessorCmd = false;
  this->parsedBffr = "";

  for (std::string item : this->cmdBffr) {
    // cout << item << "++";

    if (this->pfPreprocessorCmd) {
      this->parsedBffr += " " + item;
      continue;
    }

    if (this->cppMap.find(item) != this->cppMap.end()) {
      this->pfUpdate = true;
      (this->*cppMap[item])();
    }
  }

  if (this->pfUpdate) {
    this->parsedBffr += "\n";
  }

  if (pfPreprocessorCmd) {
    this->preprocessor_cmd.push_back(this->parsedBffr);
  }
}

void CppParser::populateParserMap() {
  this->cppMap["#include"] = &CppParser::cpp_include;
}

int CppParser::cpp_include() {
  this->pfPreprocessorCmd = true;
  this->parsedBffr += "#include";

  return 0;
}

void CppParser::displayParsedBffr() {
  cout << "parsed string:" << endl;
  cout << "preprocessor_cmd:" << endl;
  for (std::string s : this->preprocessor_cmd) {
    cout << s << endl;
  }
}
