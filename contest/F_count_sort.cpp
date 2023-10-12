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
    std::vector<int> countNegative(10000);
    std::vector<int> countNatural(10000);

    for (int n : numbers) {
        if (n < 0) {
            countNegative[-n] += 1;
        } else {
            countNatural[n] += 1;
        }
    }

    int i = 0;
    
    for (int j = countNegative.size(); j >= 0; j--) {
        for (int k = 0; k < countNegative[j]; k++) {
            numbers[i] = -j;
            i++;
        }
    }

    for (int j = 0; j < countNatural.size(); j++) {
        for (int k = 0; k < countNatural[j]; k++) {
            numbers[i] = j;
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
