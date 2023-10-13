#include <iostream>
#include <vector>
#include <fstream>

class Student
{
public:
    int Grade;
    std::string Name;
    Student()
    {
    }
};

std::vector<Student> readStudents() {
    std::vector<Student> students;
    char sep = ' ';

    std::ifstream inputFile("input.txt");
    while (! inputFile.eof()) {
        Student s;
        inputFile >> s.Grade >> sep >> s.Name;
        students.push_back(s);
    }
    inputFile.close();

    return students;
}

void CountSort(std::vector<Student>& sorted_students)
{
    std::vector<std::vector<Student>> count_students(11);
    for (Student i : sorted_students)
    {
        count_students[i.Grade - 1].push_back(i);
    }
    int index = 0;
    for (std::vector<Student> iGrade : count_students)
    {
        for(Student j : iGrade)
        {
            sorted_students[index] = j;
            index++;
        }
    }
}

void writeStudents(std::vector<Student>& students) {
    std::ofstream outputFile("output.txt");

    for (Student s : students) {
        outputFile << s.Grade << " " << s.Name << std::endl;
    }

    outputFile.close();
}

int main() {
    std::vector<Student> stud = readStudents();
    CountSort(stud);
    writeStudents(stud);
    return 0;
}