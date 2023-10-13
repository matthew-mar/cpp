#include <vector>
#include <fstream>
#include <iostream>

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
        while (current > 0 && values[current] > values[parentIndex(current)]) {
            std::swap(values[current], values[parentIndex(current)]);
            current = parentIndex(current);
        }
    }

    void shiftDown(int current) {
        while (firstChildIndex(current) < values.size()) {
            int sub = current;

            if (values[firstChildIndex(current)] > values[current]) {
                sub = firstChildIndex(current);
            }

            if (secondChildIndex(current) < values.size() && 
                values[secondChildIndex(current)] > values[sub]
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



int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    Heap heap = Heap();

    while (! inputFile.eof()) {
        std::string command;
        inputFile >> command;

        if (command == "ADD") {
            int value;
            inputFile >> value;
            heap.add(value);
        } else if (command == "EXTRACT") {
            if (heap.isEmpty()) {
                outputFile << "CANNOT" << std::endl;
            } else {
                outputFile << heap.extract() << std::endl;
            }
        } else if (command == "CLEAR") {
            heap.clear();
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
