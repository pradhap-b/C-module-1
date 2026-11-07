
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Student {
    int rollNo;
    string name;
    int age;
    string course;
    float marks;
};

vector<Student> students;
const string FILE_NAME = "students.txt";

// Find student using roll number
int findStudent(int rollNo) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].rollNo == rollNo)
            return i;
    }
    return -1;
}

// Save records to file
void saveToFile() {
    ofstream file(FILE_NAME);

    if (!file) {
        cout << "Error saving file!\n";
        return;
    }

    for (const Student &s : students) {
        file << s.rollNo << "|"
             << s.name << "|"
             << s.age << "|"
             << s.course << "|"
             << s.marks << "\n";
    }

    file.close();
}

// Load records from file
void loadFromFile() {
    ifstream file(FILE_NAME);
    string line;

    students.clear();

    while (getline(file, line)) {
        Student s;
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        if (p1 == string::npos || p2 == string::npos ||
            p3 == string::npos || p4 == string::npos)
            continue;

        try {
            s.rollNo = stoi(line.substr(0, p1));
            s.name = line.substr(p1 + 1, p2 - p1 - 1);
            s.age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
            s.course = line.substr(p3 + 1, p4 - p3 - 1);
            s.marks = stof(line.substr(p4 + 1));

            if (findStudent(s.rollNo) == -1)
                students.push_back(s);
        }
        catch (...) {
            continue;
        }
    }

    file.close();
}

// Add student
void addStudent() {
    Student s;

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    if (findStudent(s.rollNo) != -1) {
        cout << "Roll number already exists!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Course: ";
    getline(cin, s.course);

    cout << "Enter Marks: ";
    cin >> s.marks;

    students.push_back(s);
    saveToFile();

    cout << "\nStudent added successfully!\n";
}

// Display all students
void displayStudents() {
    if (students.empty()) {
        cout << "\nNo student records found!\n";
        return;
    }

    cout << "\n========== STUDENT RECORDS ==========\n";

    cout << "Roll No\tName\tAge\tCourse\tMarks\n";
    cout << "---------------------------------------------\n";

    for (const Student &s : students) {
        cout << s.rollNo << "\t"
             << s.name << "\t"
             << s.age << "\t"
             << s.course << "\t"
             << s.marks << "\n";
    }
}

// Search student
void searchStudent() {
    int rollNo;

    cout << "\nEnter Roll Number to Search: ";
    cin >> rollNo;

    int index = findStudent(rollNo);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    Student s = students[index];

    cout << "\nStudent Details\n";
    cout << "Roll Number: " << s.rollNo << "\n";
    cout << "Name       : " << s.name << "\n";
    cout << "Age        : " << s.age << "\n";
    cout << "Course     : " << s.course << "\n";
    cout << "Marks      : " << s.marks << "\n";
}

// Update student
void updateStudent() {
    int rollNo;

    cout << "\nEnter Roll Number to Update: ";
    cin >> rollNo;

    int index = findStudent(rollNo);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    Student &s = students[index];

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter New Name: ";
    getline(cin, s.name);

    cout << "Enter New Age: ";
    cin >> s.age;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter New Course: ";
    getline(cin, s.course);

    cout << "Enter New Marks: ";
    cin >> s.marks;

    saveToFile();

    cout << "\nStudent updated successfully!\n";
}

// Delete student
void deleteStudent() {
    int rollNo;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> rollNo;

    int index = findStudent(rollNo);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    students.erase(students.begin() + index);

    saveToFile();

    cout << "\nStudent deleted successfully!\n";
}

// Main menu
int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       STUDENT MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "====================================\n";

        cout << "Enter Your Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                saveToFile();
                cout << "\nThank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
