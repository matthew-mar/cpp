#include <vector>
#include <fstream>

class Heap {

private:
    std::vector<int> values;

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

    void add(int x) {
        values.push_back(x);
        shiftUp(values.size() - 1);
    }

    bool isEmpty() {
        return values.size() == 0;
    }

    int extract() {
        int tmp = values[0];
        values[0] = values[values.size() - 1];
        values.pop_back();
        shiftDown(0);
        return tmp;
    }
};

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

void heapsort(std::vector<int>& numbers) {
    Heap heap = Heap();
    for (int n : numbers) {
        heap.add(n);
    }

    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = heap.extract();
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
    heapsort(numbers);
    writeNumbers(numbers);
    return 0;
}
