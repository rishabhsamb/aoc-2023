#include <iostream>
#include <string>

int bufferToInt(std::string buffer) {
  if (buffer == "one") {
    return 1;
  } else if (buffer == "two") {
    return 2;
  } else if (buffer == "three") {
    return 3;
  } else if (buffer == "four") {
    return 4;
  } else if (buffer == "five") {
    return 5;
  } else if (buffer == "six") {
    return 6;
  } else if (buffer == "seven") {
    return 7;
  } else if (buffer == "eight") {
    return 8;
  } else if (buffer == "nine") {
    return 9;
  } else if (buffer == "zero") {
    return 0;
  } else {
    return -1;
  }
}

std::string getSuffix(std::string buffer, int len) {
  if (buffer.length() < len) {
    return "";
  } else {
    return buffer.substr(buffer.length() - len);
  }
}

int main() {
  std::string line;
  int sum = 0;
  while(std::getline(std::cin, line)) {
    int first = -1;
    int last = -1;
    std::string buffer = "";
    int conv = -1;
    for(int i = 0; i < line.length(); ++i) {
      if(isdigit(line[i])) {
        if(first == -1) {
          first = line[i] - '0';
        }
        last = line[i] - '0';
      }
      else {
        buffer += line[i];
        for (int j = 5; j > 2; --j) {
          std::string suffix = getSuffix(buffer, j);
          conv = bufferToInt(suffix);
          if (conv != -1) {
            if (first == -1) {
              first = conv;
            }
            last = conv;
          }
        }
      }
    }
    sum += first * 10 + last;
  }
  std::cout << sum << std::endl;
}
