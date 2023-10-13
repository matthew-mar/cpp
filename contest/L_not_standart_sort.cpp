#include <vector>
#include <fstream>

std::vector<char> sortStringByOrder(std::string str, std::string order) {
    std::vector<char> output;
    for (char s : str) {
        output.push_back(s);
    }

    for (int pos = 0; pos < output.size() - 1; pos++) {
        for (int i = pos + 1; i < output.size(); i++) {
            char f = output[i];
            int fOrder = order.find(f);

            char s = output[pos];
            int sOrder = order.find(s);

            if (fOrder < sOrder) {
                std::swap(output[i], output[pos]);
            }
        }
    }

    return output; 
}

void writeOutput(std::vector<char>& output) {
    std::ofstream outputFile("output.txt");
    
    for (char s : output) {
        outputFile << s;
    }

    outputFile.close();
}

int main() {
    std::string orderString;
    std::string inputString;

    std::ifstream inputFile("input.txt");
    inputFile >> orderString;
    inputFile >> inputString;
    inputFile.close();

    std::vector<char> output = sortStringByOrder(inputString, orderString);
    writeOutput(output);

    return 0;
}
