#include <vector>
#include <fstream>

int main() {
    std::ifstream inputFile("input.txt");
    
    int tShirtSize;
    std::vector<int> tShirts;

    int pantSize;
    std::vector<int> pants;

    while (! inputFile.eof()) {
        inputFile >> tShirtSize;

        for (int i = 0; i < tShirtSize; i++) {
            int tsh;
            inputFile >> tsh;
            tShirts.push_back(tsh);
        }

        
        inputFile >> pantSize;
        for (int i = 0; i < pantSize; i++) {
            int pa;
            inputFile >> pa;
            pants.push_back(pa);
        }
    }
    inputFile.close();

    int i = 0;
    int j = 0;
    int t = 0;
    int p = 0;
    int minDif = abs(tShirts[0] - pants[0]);

    while (i < tShirtSize && j < pantSize) {
        int curDif = abs(tShirts[i] - pants[j]);

        if (curDif == 0) {
            t = i;
            p = j;
            break;
        }

        if (curDif < minDif) {
            minDif = curDif;
            t = i;
            p = j;
        }

        if (tShirts[i] < pants[j]) {
            i++;
        } else {
            j++;
        }
    }

    std::ofstream outputFile("output.txt");
    outputFile << tShirts[t] << " " << pants[p] << std::endl;
    outputFile.close();

    return 0;
}
