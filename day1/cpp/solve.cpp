#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::string;

uint64_t part1(string &line) {
    uint64_t calibrationValue = 0;
    char first, last;
    for (string::iterator character = line.begin(); character != line.end();
         ++character) {
        if (isdigit(*character)) {
            first = *character;
            break;
        }
    }
    for (string::reverse_iterator character = line.rbegin();
         character != line.rend(); ++character) {
        if (isdigit(*character)) {
            last = *character;
            break;
        }
    }
    string result = "";
    result += first;
    result += last;

    calibrationValue = std::stoull(result, nullptr, 10);
    return calibrationValue;
}

uint64_t part2(string &line) {

    uint64_t calibrationValue = 0;
    std::unordered_map<string, uint8_t> nums{
        {"one", '1'},   {"two", '2'},   {"three", '3'},
        {"four", '4'},  {"five", '5'},  {"six", '6'},
        {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};

    size_t firstIndex = line.length();
    char first = 0;

    // first instance of word
    for (const std::pair<string, uint8_t> &num : nums) {
        size_t index = line.find(num.first);
        if (index < firstIndex) {
            firstIndex = index;
            first = nums[num.first];
        }
    }

    // first instance of digit
    for (string::iterator character = line.begin(); character != line.end();
         character++) {
        if (isdigit(*character)) {
            size_t index = line.find(*character);
            if (index < firstIndex) {
                firstIndex = index;
                first = line[index];
            }
            break;
        }
    }

    int32_t lastIndex = -1;
    char last = 0;

    // last instance of word
    for (const std::pair<string, uint8_t> &num : nums) {
        int32_t index = line.rfind(num.first);
        if (index != string::npos) {
            if (index > lastIndex) {
                lastIndex = index;
                last = nums[num.first];
            }
        }
    }

    // last instance of digit
    for (int32_t index = 0; index < line.length(); index++) {
        if (isdigit(line[index])) {
            if (index > lastIndex) {
                lastIndex = index;
                last = line[index];
            }
        }
    }

    string result = "";
    result += first;
    result += last;

    printf("%c, %c -> %s\n", first, last, line.c_str());
    calibrationValue = std::stoull(result, nullptr, 10);
    return calibrationValue;
}

int32_t main(int32_t argc, char **argv) {

    string fName = "./../input";
    string testPart1 = "./../test.part1";
    string testPart2 = "./../test.part2";

    std::ifstream file(fName);

    string line;
    uint64_t result1, result2;
    result1 = result2 = 0;
    while (std::getline(file, line, '\n')) {
        result1 += part1(line);
        result2 += part2(line);
    }

    cout << "Solution part1: " << result1 << std::endl;
    cout << "Solution part2: " << result2 << std::endl;

    file.close();
    return 0;
}
