#include "funcs.h"
#include <string>
#include <math.h>
#include <vector>


/*Used to understand cin.clear() and cin.ignore()
https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
*/

//Obtains user's resistance as a positive non-zero double
double getRes(){
  double num;
  std::cout << "Please enter your resistance (ohms): ";
  while (!(std::cin >> num) || !(num > 0) ) {
    std::cout << "Please enter a valid resistance (ohms): ";
    std::cin.clear(); //"ignores" error flag
    std::cin.ignore(100, '\n'); //first number is amount of input stream to ignore
  }
  //std::cout << "Your number is " << num << std::endl;
  return num;
}

bool isMin() {
  char response = ' ';
  std::cout << "Is the resistance a required minimum?\n";
  do {
    std::cin.clear();
    std::cin.ignore(100, '\n');
    std::cout << "[y/n] >";
    std::cin >> response;
  }
  while (!std::cin.fail() && std::tolower(response) !='y' && std::tolower(response) !='n');

  if (response == 'y') {
    return true;
  }
  else {
    return false;
  }
}

//Obtains value to be compared against available resistor values
double compVal(double res) {
  int pwr = floor(log10(res));
  float comp = (res / pow(10, pwr));

  return comp;
}

float closest(std::vector<float> npv, float val, bool min) {
  float diff = 0;
  float diff2 = 0;
  for (int i = 0; i < npv.size() - 1; i++) {
    diff = npv[i] - val;
    diff2 = npv[i+1] - val;
    if (diff <= 0 && diff2 > 0) {
      if (min == true) {
        return npv[i+1];
      }
      else if (std::abs(diff) > std::abs(diff2)) {
        return npv[i+1];
      }
      else if (std::abs(diff) < std::abs(diff2)) {
        return npv[i];
      }
      else {
        return npv[i+1];
      }
    }
  }
  std::cout << "An unexpected error occurred\n";
  std::cout << "Exiting...";
  return 0;
}

float calcRes(float val, float res) {
  int pwr = floor(log10(res));
  float resistor = val * pow(10, pwr);
  return resistor;
}