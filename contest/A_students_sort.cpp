#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

struct Student {
    int grade;
    std::string name;
};

std::vector<Student> readStudents() {
    std::vector<Student> students;

    std::ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        Student s;

        while (inputFile >> s.grade) {
            std::getline(inputFile >> std::ws, s.name);

            students.push_back(s);
        }

        inputFile.close();
    } else {
        std::cout << "Error opening input file." << std::endl;
    }

    return students;
}

void sortStudents(std::vector<Student>& students) {
    std::vector<std::vector<Student>> countStudents(11);

    for (Student s : students) {
        countStudents[s.grade - 1].push_back(s);
    }

    int i = 0;
    for (std::vector<Student> gradeStudents : countStudents) {
        for (Student s : gradeStudents) {
            students[i] = s;
            i++;
        }
    }
}

void writeStudents(std::vector<Student>& students) {
    std::ofstream outputFile("output.txt");
    
    for (Student s : students) {
        outputFile << s.grade << " " << s.name << std::endl;
    }

    outputFile.close();
}

int main() {
    std::vector<Student> students = readStudents();

    for (Student s : students) {
        std::cout << s.name << std::endl;
    }

    sortStudents(students);
    writeStudents(students);
    return 0;
}
