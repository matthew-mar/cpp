#include <vector>
#include <fstream>

struct Student {
    int grade;
    std::string name;
};

std::vector<Student> readStudents() {
    std::vector<Student> students;
    char sep = ' ';

    std::ifstream inputFile("input.txt");
    while (! inputFile.eof()) {
        Student s;
        inputFile >> s.grade >> sep >> s.name;
        students.push_back(s);
    }
    inputFile.close();

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
    sortStudents(students);
    writeStudents(students);
    return 0;
}
