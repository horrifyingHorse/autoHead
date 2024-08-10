#include <iostream>
using namespace std;

class UsrCmd {
private:
  int totalArgs;
};

void autoHead() {
  cout << "autoHead\nez autoGen Header Files 4u <3" << endl << endl;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    autoHead();
  }

  return 0;
}
