#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

class Heap {

private:
    std::vector<float> values;

    int parentIndex(int current) {
        return (current - 1) / 2;
    }

    int firstChildIndex(int current) {
        return 2 * current + 1;
    }

    int secondChildIndex(int current) {
        return 2 * current + 2;
    }

    void shiftUp(int current) {
        while (current > 0 && values[current] < values[parentIndex(current)]) {
            std::swap(values[current], values[parentIndex(current)]);
            current = parentIndex(current);
        }
    }

    void shiftDown(int current) {
        while (firstChildIndex(current) < values.size()) {
            int sub = current;

            if (values[firstChildIndex(current)] < values[current]) {
                sub = firstChildIndex(current);
            }

            if (secondChildIndex(current) < values.size() && 
                values[secondChildIndex(current)] < values[sub]
            ) {
                sub = secondChildIndex(current);
            }

            if (current == sub) {
                break;
            }

            std::swap(values[current], values[sub]);
            current = sub;
        }
    }

public:
    Heap() {}

    void clear() {
        values.clear();
    }

    void add(float x) {
        values.push_back(x);
        shiftUp(values.size() - 1);
    }

    bool isEmpty() {
        return values.size() == 0;
    }

    float extract() {
        float tmp = values[0];
        values[0] = values[values.size() - 1];
        values.pop_back();
        shiftDown(0);
        return tmp;
    }
};

std::vector<float> readNumbers() {
    std::ifstream inputFile("input.txt");

    int count;
    inputFile >> count;

    std::vector<float> numbers(count);
    for (int i = 0; i < count; i++) {
        inputFile >> numbers[i];
    }

    inputFile.close();

    return numbers;
}

float getSum(std::vector<float>& numbers) {
    Heap heap = Heap();
    for (float s : numbers) {
        heap.add(s);
    }

    float res = 0;
    float min1 = heap.extract();
    for (int i = 0; i < numbers.size() - 1; i++) {
        float min2 = heap.extract();
        float s = min1 + min2;
        res += s / 20;
        heap.add(s);
        min1 = heap.extract();
    }

    return res;
}

void writeSumm(float sum) {
    std::ofstream outputFile("output.txt");
    outputFile << std::fixed << std::setprecision(2) << sum;
    outputFile.close();
}

int main() {
    std::vector<float> numbers = readNumbers();
    float summ = getSum(numbers);
    writeSumm(summ);
    return 0;
}
