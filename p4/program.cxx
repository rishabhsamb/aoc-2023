#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

template <typename T>
void printVec(std::vector<T> vec) {
  std::cout << "length = " << vec.size() << " || ";
  for (int i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i < vec.size() - 1) {
      std::cout << " | ";
    }
  }
  std::cout << std::endl;
}

void printSet(const std::set<int>& set) {
  for (std::set<int>::iterator it = set.begin(); it != set.end(); ++it) {
    std::cout << *it;
    if (it != std::prev(set.end(), 1))
      std::cout << ",";
  }
  std::cout << std::endl;
}

std::vector<std::string> split(std::string s, char delim) {
  std::vector<std::string> result = {""};
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == delim) {
      result.push_back("");
    } else {
      result[result.size()-1] += s[i];
    }
  }
  return result;
}

std::string trimLeft(std::string s) {
  while (s[0] == ' ') {
    s = s.erase(0, 1);
  }
  return s;
}

std::string trimRight(std::string s) {
  while (s[s.length()-1] == ' ') {
    s.pop_back();
  }
  return s;
}

std::string trim(std::string s) {
  return trimLeft(trimRight(s));
}

std::set<int> parseNumStringIntoSet(std::string numString) {
  // std::cout << "parseNumStringIntoSet " << numString << std::endl;
  std::stringstream numStringStream(numString);
  int cur;
  std::set<int> result;
  while (numStringStream >> cur)
    result.insert(cur);
  return result;
}

int partTwo() {
  // put every line into a vector of strings
  // keep track of the number of copies + originals we have in another vector
  // go through each line, compute lineCounts
  // return sum of lineCounts vector
  std::string line;
  long sum = 0;
  std::vector<std::string> lines;
  std::vector<int> lineCounts;
  while(std::getline(std::cin, line)) {
    lines.push_back(line);
    lineCounts.push_back(1);
  }

  int matchingNumbers;
  for (int i = 0; i < lines.size(); ++i) {
    // parse line
    // get number of matching numbers
    // do math to propagate effects into lineCounts
    line = lines[i];
    std::vector<std::string> splitOnColon = split(line, ':');
    std::vector<std::string> splitOnBar = split(splitOnColon[1], '|');
    std::set<int> winningNumbers = parseNumStringIntoSet(splitOnBar[0]);
    std::set<int> candidateNumbers = parseNumStringIntoSet(splitOnBar[1]);

    matchingNumbers = 0;
    for (std::set<int>::iterator it = winningNumbers.begin(); it != winningNumbers.end(); ++it) {
      if (candidateNumbers.find(*it) != candidateNumbers.end())
        matchingNumbers += 1;
    }
    for (int j = i+1; j < lineCounts.size() && j - i <= matchingNumbers; ++j)
      lineCounts[j] += lineCounts[i];

  }
  // sum lineCounts
  for (int i = 0; i < lineCounts.size(); ++i)
    sum += lineCounts[i];
  return sum;
}

int partOne() {
  std::string line;
  long double sum = 0;
  long double power;
  while(std::getline(std::cin, line)) {
    std::vector<std::string> splitOnColon = split(line, ':');
    std::vector<std::string> splitOnBar = split(splitOnColon[1], '|');

    std::set<int> winningNumbers = parseNumStringIntoSet(splitOnBar[0]);
    std::set<int> candidateNumbers = parseNumStringIntoSet(splitOnBar[1]);

    power = -1;
    for (std::set<int>::iterator it = winningNumbers.begin(); it != winningNumbers.end(); ++it) {
      if (candidateNumbers.find(*it) != candidateNumbers.end())
        power += 1;
    }
    if (power != -1)
      sum += std::pow(2, power);
  }
  return sum;
}

int main() {
  int sum = partTwo();
  std::cout << sum << std::endl;
}
