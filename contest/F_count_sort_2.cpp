#include <vector>
#include <fstream>
#include <iostream>

std::vector<int> readNumbers() {
    std::ifstream inputFile("input.txt");

    int count;
    inputFile >> count;

    std::vector<int> numbers(count);
    for (int i = 0; i < count; i++) {
        inputFile >> numbers[i];
    }

    inputFile.close();

    return numbers;
}

void countSort(std::vector<int>& numbers) {
    int maxValue = 10000;
    std::vector<int> countNumbers(maxValue * 2);

    for (int n : numbers) {
        if (n <= 0) {
            countNumbers[-n] += 1;
        } else {
            countNumbers[maxValue + n] += 1;
        }
    }

    int i = 0;
    for (int j = maxValue; j >= 0; j--) {
        for (int k = 0; k < countNumbers[j]; k++) {
            numbers[i] = -j;
            i++;
        }
    }

    for (int j = maxValue; j < maxValue * 2; j++) {
        for (int k = 0; k < countNumbers[j]; k++) {
            numbers[i] = j - maxValue;
            i++;
        }
    }
}

void writeNumbers(std::vector<int>& numbers) {
    std::ofstream outputFile("output.txt");

    for (int n : numbers) {
        outputFile << n << " ";
    }

    outputFile.close();
}

int main() {
    std::vector<int> numbers = readNumbers();
    countSort(numbers);
    writeNumbers(numbers);
    return 0;
}
