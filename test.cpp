// This is a test file
// to check if the parser works

#include <iostream>

using namespace std;

int globalVar = 1;
string newOne = "ParseMeThisParser";

void stromBastille() {
  cout << "Incorrect Time Period, 2024 Forbidden" << endl;
  return;
}

void stormBastille(int currDate) {
  if (currDate != 14071789) {
    cout << "Not happening" << endl;
    return;
  }

  cout << "Marchons! Oui, marchons!" << endl;
  return;
}

int main() {
  cout << "Mornin" << globalVar << endl;
  stromBastille();
  stormBastille(14071789);

  return 0;
}
