#include <iostream>
#include <string>
#include <vector>

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


std::vector<int> parseBagString(std::string bagString) {
  std::vector<int> result = {0, 0, 0};
  std::vector<std::string> blockStrings = split(bagString, ',');
  for (int i = 0; i < blockStrings.size(); ++i) {
    std::string trimmedBlockString = trim(blockStrings[i]);
    std::vector<std::string> blockStringSplit = split(trimmedBlockString, ' ');
    int val = std::stoi(blockStringSplit[0]);
    std::string colour = blockStringSplit[1];
    if (colour == "blue") {
      result[0] = val;
    } else if (colour == "red") {
      result[1] = val;
    } else if (colour == "green") {
      result[2] = val;
    } else {
      throw "bad colour supplied";
    }
  }
  return result;
}


int main() {
  std::string line;
  int sum = 0;

  while(std::getline(std::cin, line)) {
    std::vector<std::string> splitOnColon = split(line, ':');
    std::vector<std::string> splitFirstOnSpace = split(splitOnColon[0], ' ');
    int gameId = std::stoi(splitFirstOnSpace[1]);
    std::vector<std::string> bagStrings = split(splitOnColon[1], ';');
    
    std::vector<int> maxCounts = {0, 0, 0};
    for (int i = 0; i < bagStrings.size(); ++i) {
      std::vector<int> blockCounts = parseBagString(bagStrings[i]);
      assert(blockCounts.size() == 3);
      for (int j = 0; j < 3; ++j) {
        if (maxCounts[j] < blockCounts[j]) {
          maxCounts[j] = blockCounts[j];
        }
      }
    }
    sum += maxCounts[0] * maxCounts[1] * maxCounts[2];
  }
  std::cout << sum << std::endl;
}
