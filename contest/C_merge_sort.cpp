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

void mergeSort(std::vector<int>& numbers) {
    int size = numbers.size();

    if (size <= 1) {
        return;
    }

    int middle = size / 2;
    int left = 0;
    int leftSize = middle;

    int right = middle;
    int rightSize = size - leftSize;

    std::vector<int> leftHalf;
    for (int i = left; i < leftSize; i++) {
        leftHalf.push_back(numbers[i]);
    }

    std::vector<int> rightHalf;
    for (int i = right; i < size; i++) {
        rightHalf.push_back(numbers[i]); 
    }

    mergeSort(leftHalf);
    mergeSort(rightHalf);

    std::vector<int> buffer(size);
    int leftPoint = 0;
    int rightPoint = 0;
    int bufferPoint = 0;

    while (leftPoint < leftSize && rightPoint < rightSize) {
        if (leftHalf[leftPoint] <= rightHalf[rightPoint]) {
            buffer[bufferPoint] = leftHalf[leftPoint];
            leftPoint++;
            bufferPoint++;
        } else {
            buffer[bufferPoint] = rightHalf[rightPoint];
            rightPoint++;
            bufferPoint++;
        }
    }

    while (leftPoint < leftSize) {
        buffer[bufferPoint] = leftHalf[leftPoint];
        leftPoint++;
        bufferPoint++;
    }

    while (rightPoint < rightSize) {
        buffer[bufferPoint] = rightHalf[rightPoint];
        rightPoint++;
        bufferPoint++;
    }

    for (int i = 0; i < size; i++) {
        numbers[i] = buffer[i];
    }
    buffer.clear();
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
    mergeSort(numbers);
    writeNumbers(numbers);
    return 0;
}
