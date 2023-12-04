#include <iostream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <sstream>
#include <exception>

class BadInputException : public std::exception {
private:
    std::string message;

public:
    BadInputException(const std::string& msg) : message(msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

enum symbol {
  IGNORE = '.',
  OLD_NUMBER = 'X',
  GEAR = '*'
};

std::vector<std::pair<int, int>> neighbours = {
  {0,-1},
  {0,1},
  {-1,0},
  {1,0},
  {1,1},
  {1,-1},
  {-1,1},
  {-1,-1}
};

void printRepr(const std::vector<std::vector<char>>& repr) {
  for (int i = 0; i < repr.size(); ++i) {
    for (int j = 0; j < repr[i].size(); ++j) {
      std::cout << repr[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void printSet(const std::set<std::pair<int,int>>& set) {
  for (std::set<std::pair<int,int>>::iterator it = set.begin(); it != set.end(); ++it) {
    std::cout << it->first << "," << it->second;
    if (it != std::prev(set.end(), 1))
      std::cout << " | ";
  }
  std::cout << std::endl;
}

bool hasSpecialNeighbours(int row, int col, const std::vector<std::vector<char>>& repr) {
  if (row >= repr.size() || col >= repr[row].size()) {
    throw BadInputException("row or col was out of bounds!");
  }
  int newRow;
  int newCol;
  for (int i = 0; i < neighbours.size(); ++i) {
    newRow = row + neighbours[i].first;
    newCol = col + neighbours[i].second;
    if (newRow < 0 || newRow == repr.size() || newCol < 0 || newCol == repr[newRow].size()) {
      continue;
    } else if (
      repr[newRow][newCol] != OLD_NUMBER &&
      repr[newRow][newCol] != IGNORE &&
      !isdigit(repr[newRow][newCol])
    ) {
      return true;
    }
  }
  return false;
}

int getNumber(int row, int col, const std::vector<std::vector<char>>& repr) {
  if (row >= repr.size() || col >= repr[row].size() || !isdigit(repr[row][col])) {
    throw BadInputException("row or col was out of bounds!");
  }
  while (col > 0 && isdigit(repr[row][col-1])) {
    col -= 1;
  }
  int number = 0;
  int digit;
  while (col < repr[row].size() && isdigit(repr[row][col])) {
    digit = repr[row][col] - '0';
    number *= 10;
    number += digit;
    col += 1;
  }
  return number;
}

void flushNumber(int row, int col, std::vector<std::vector<char>>& repr) {
  if (row >= repr.size() || col >= repr[row].size() || !isdigit(repr[row][col])) {
    throw BadInputException("row or col was out of bounds!");
  }
  while (col > 0 && isdigit(repr[row][col-1])) {
    col -= 1;
  }
  while (col < repr[row].size() && isdigit(repr[row][col])) {
    repr[row][col] = OLD_NUMBER;
    col += 1;
  }
}

std::vector<std::pair<int,int>> getNumberIndices(int row, int col, const std::vector<std::vector<char>>& repr) {
  if (row >= repr.size() || col >= repr[row].size() || !isdigit(repr[row][col])) {
    throw BadInputException("row or col was out of bounds!");
  }
  while (col > 0 && isdigit(repr[row][col-1])) {
    col -= 1;
  }
  std::vector<std::pair<int,int>> result;
  while (col < repr[row].size() && isdigit(repr[row][col])) {
    result.push_back({row, col});
    col += 1;
  }
  return result;
}

bool isOutlawedNumber(
  int row, 
  int col, 
  const std::vector<std::vector<char>>& repr, 
  const std::set<std::pair<int,int>>& outlawedIndices
) {
  if (row >= repr.size() || col >= repr[row].size() || !isdigit(repr[row][col])) {
    throw BadInputException("row or col was out of bounds!");
  }
  std::vector<std::pair<int,int>> numberIndices = getNumberIndices(row, col, repr);
  for (int i = 0; i < numberIndices.size(); ++i) {
    if (outlawedIndices.find(numberIndices[i]) != outlawedIndices.end())
      return true;
  }
  return false;
}

void addOutlawedIndices(
  int row, 
  int col, 
  const std::vector<std::vector<char>>& repr, 
  std::set<std::pair<int,int>>& outlawedIndices
) {
  if (row >= repr.size() || col >= repr[row].size() || !isdigit(repr[row][col])) {
    throw BadInputException("row or col was out of bounds!");
  }
  std::vector<std::pair<int,int>> numberIndices = getNumberIndices(row, col, repr);
  for (int i = 0; i < numberIndices.size(); ++i) {
    outlawedIndices.insert({numberIndices[i].first, numberIndices[i].second});
  }
}

int getGearRatio(int row, int col, const std::vector<std::vector<char>>& repr) {
  if (row >= repr.size() || col >= repr[row].size() || repr[row][col] != GEAR) {
    throw BadInputException("row or col was out of bounds!");
  }
  std::set<std::pair<int,int>> outlawedIndices;
  int numNumbers = 0;
  int newRow;
  int newCol;
  int product = 1;
  for (int i = 0; i < neighbours.size(); ++i) {
    newRow = row + neighbours[i].first;
    newCol = col + neighbours[i].second;
    if (newRow < 0 || newRow == repr.size() || newCol < 0 || newCol == repr[newRow].size()) {
      continue;
    } else if (
      isdigit(repr[newRow][newCol]) &&
      !isOutlawedNumber(newRow, newCol, repr, outlawedIndices)
    ) {
      // std::cout << getNumber(newRow, newCol, repr) << std::endl;
      // get the number, multiply it to the product, outlaw its indices, add one to numNumbers
      product *= getNumber(newRow, newCol, repr);
      addOutlawedIndices(newRow, newCol, repr, outlawedIndices);
      numNumbers += 1;
    }
  }
  if (numNumbers != 2) {
    return 0;
  } else {
    return product;
  }
  return false;
}

int partOne(std::vector<std::vector<char>> repr) {
  char cur;
  int a;
  int sum = 0;
  for (int i = 0; i < repr.size(); ++i) {
    for (int j = 0; j < repr[i].size(); ++j) {
      cur = repr[i][j];
      if (isdigit(cur) && hasSpecialNeighbours(i,j,repr)) {
        a = getNumber(i,j,repr);
        flushNumber(i,j,repr);
        sum += a;
      }
    }
  }
  return sum;
}

int partTwo(std::vector<std::vector<char>> repr) {
  char cur;
  int a;
  int sum = 0;
  for (int i = 0; i < repr.size(); ++i) {
    for (int j = 0; j < repr[i].size(); ++j) {
      cur = repr[i][j];
      if (cur == GEAR)
        sum += getGearRatio(i, j, repr);
    }
  }
  return sum;
}

int main() {
  std::string line;
  std::vector<std::vector<char>> repr;
  char cur;
  while(std::getline(std::cin, line)) {
    std::stringstream lineStream(line);
    std::vector<char> lineVec;
    while (lineStream >> cur) {
      lineVec.push_back(cur);
    }
    repr.push_back(lineVec);
  }
  int sum = partTwo(repr);
  std::cout << sum << std::endl;
}
