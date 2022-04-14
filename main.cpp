#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "funcs.h"

//This program allows the user to enter a calculated resistance
//alongside certain criteria to find the most suitable commercially
//available resistor for an electronic circuit

int main() {
  const std::string tolerances[6] = {"0.5%", "1%", "2%", "5%", "10%", "20%"};
  const std::string series[6] = {"192", "96", "48", "24", "12", "6"};
  double tolerance;

  std::cout << "*********NPV Calculator*********\n";
  double R = getRes(); //get resistance
  double RC = compVal(R); //gets value to compare against available resistors

  //Display available tolerance levels
  std::cout << "Available tolerance levels: " << std::endl;
  for (int i = 0; i < std::size(tolerances); i++) {
    if (i == (std::size(tolerances)-1)) {
      std::cout << tolerances[i] << "\n";
    }
    else {
      std::cout << tolerances[i] << ", ";
    }
  }

  //Asking user for their desired level of tolerance
  std::cout << "Please enter your tolerance: ";
  bool valid = false;
  int E;
  std::string input;

  while (valid == false) {
    std::cin >> input;
    for (int i = 0; i < std::size(tolerances); i++) {
      if (input == tolerances[i]) {
        //std::cout << tolerances[i];
        valid = true;
        E = i;
      }
    }
    if (valid == false) {
      std::cout << "Please enter a specified value: ";
    }
  }
  
  std::cout << "Selecting from E" << series[E] << std::endl;
  
  bool min = isMin(); //Asking if the resistance is a required minimum
  if (min == true) {
    std::cout << "Selecting next highest resistor\n";
  }

  std::ifstream file; //open npv.csv
  file.open("npv.csv");

  std::vector<float> vals;

  while(file.good()) {
    std::string line;
    std::getline(file,line,',');
    if (line == series[E]) {
      for(int i=0; i < std::stoi(series[E]); i++ ){
        std::getline(file,line, ',');
        vals.push_back(std::stof(line));
      }
    }
  }
  file.close(); //close npv.csv

  float v = closest(vals, RC, min);
  std::cout << "\nYour resistor to use is: " << calcRes(v, R) << "ohms\n";

}