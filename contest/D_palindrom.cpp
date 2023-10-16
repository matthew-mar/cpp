#include <vector>
#include <fstream>
#include <iostream>

int main() {
    std::ifstream inputFile("input.txt");

    int count;
    inputFile >> count;

    std::vector<char> letters(count);
    for (int i = 0; i < count; i++) {
        inputFile >> letters[i];
    }

    for (int pos = 0; pos < letters.size() - 1; pos++) {
        for (int i = pos; i < letters.size(); i++) {
            if (letters[i] < letters[pos]) {
                std::swap(letters[i], letters[pos]);
            }
        }
    }

    std::vector<char> single;
    std::vector<char> result;

    std::vector<std::pair<char, int>> lettersCount(count);

    int index = 0;
    for (char s : letters) {
        bool found = false;
        for (std::pair<char, int>& pair : lettersCount) {
            if (pair.first == s) {
                pair.second += 1;
                if (pair.second == 2) {
                    pair.second = 0;
                    result.push_back(s);
                }
                found = true;
                break;
            }
        }
        if (! found) {
            lettersCount[index] = std::make_pair(s, 1);
            index++;
        }
    }

    for (std::pair<char, int>& pair : lettersCount) {
        if (pair.second == 1) {
            single.push_back(pair.first);
            break;
        }
    }

    std::vector<char> reversedResult;
    for (int i = result.size() - 1; i >= 0; i--) {
        reversedResult.push_back(result[i]);
    }

    if (single.size() != 0) {
        result.push_back(single[0]);
    }
    
    for (char s : reversedResult) {
        result.push_back(s);
    }

    for (char s : result) {
        std::cout << s;
    }

    std::cout << std::endl;

    return 0;
}
