#include <vector>
#include <fstream>

std::vector<int> readNumbers() {
    std::vector<int> numbers;

    std::ifstream inputFile("input.txt");
    while (! inputFile.eof()) {
        int n;
        inputFile >> n;
        numbers.push_back(n);
    }
    inputFile.close();

    return numbers;
}

void SelectionSort(std::vector<int>& numbers) {
    for (int pos = 0; pos < numbers.size() - 1; pos++) {
        for (int i = pos + 1; i < numbers.size(); i++) {
            if (numbers[i] > numbers[pos]) {
                std::swap(numbers[i], numbers[pos]);
            }
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
    SelectionSort(numbers);
    writeNumbers(numbers);
    return 0;
}
