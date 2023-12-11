#include <iostream>
#include <fstream>
#include <sstream>

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 50;
const int MAX_ENROLLED_STUDENTS = 100;

class Student {
public:
    std::string name;
    int roll_num;
    int age;
    std::string contact;
};

class Course {
public:
    std::string code;
    std::string name;
    std::string instructor;
    int credits;
    int capacity;
    int enrolled_students[MAX_ENROLLED_STUDENTS];
};

class System {
private:
    Student students[MAX_STUDENTS];
    Course courses[MAX_COURSES];
    int studentCount = 0;
    int courseCount = 0;

    void saveDataToFile() {
        std::ofstream file("data.txt");
        if (file.is_open()) {
            for (int i = 0; i < studentCount; ++i) {
                file << "Student|" << students[i].name << "|" << students[i].roll_num << "|"
                    << students[i].age << "|" << students[i].contact << "\n";
            }

            for (int i = 0; i < courseCount; ++i) {
                file << "Course|" << courses[i].code << "|" << courses[i].name << "|"
                    << courses[i].instructor << "|" << courses[i].credits << "|"
                    << courses[i].capacity << "|";

                for (int j = 0; j < MAX_ENROLLED_STUDENTS && courses[i].enrolled_students[j] != -1; ++j) {
                    file << courses[i].enrolled_students[j] << ",";
                }

                file << "\n";
            }

            file.close();
        }
    }

public:
    void enrollStudent() {
        Student newStudent;
        std::cout << "Enter student information:\n";
        std::cout << "Name: ";
        std::cin >> newStudent.name;
        std::cout << "Roll Number: ";
        std::cin >> newStudent.roll_num;
        std::cout << "Age: ";
        std::cin >> newStudent.age;
        std::cout << "Contact: ";
        std::cin >> newStudent.contact;

        if (studentCount < MAX_STUDENTS) {
            students[studentCount++] = newStudent;
            std::cout << "Student Information successfully saved.\n";
        }
        else {
            std::cout << "Maximum number of students reached.\n";
        }
    }

    void displayEnrolledStudents() {
        std::cout << "Enrolled Students:\n";
        for (int i = 0; i < studentCount; ++i) {
            std::cout << "Name: " << students[i].name << "\nRoll Number: " << students[i].roll_num
                << "\nAge: " << students[i].age << "\nContact: " << students[i].contact << "\n";
            std::cout << "-------------------\n";
        }
    }

    void addCourse() {
        Course newCourse;
        std::cout << "Enter course information:\n";
        std::cout << "Code: ";
        std::cin >> newCourse.code;
        std::cout << "Name: ";
        std::cin >> newCourse.name;
        std::cout << "Instructor: ";
        std::cin >> newCourse.instructor;
        std::cout << "Credits: ";
        std::cin >> newCourse.credits;
        std::cout << "Capacity: ";
        std::cin >> newCourse.capacity;

        if (courseCount < MAX_COURSES) {
            courses[courseCount++] = newCourse;
            std::cout << "Course Information successfully saved.\n";
        }
        else {
            std::cout << "Maximum number of courses reached.\n";
        }
    }

    void displayAvailableCourses() {
        std::cout << "Available Courses:\n";
        for (int i = 0; i < courseCount; ++i) {
            std::cout << "Code: " << courses[i].code << "\nName: " << courses[i].name
                << "\nInstructor: " << courses[i].instructor << "\nCredits: " << courses[i].credits
                << "\nCapacity: " << courses[i].capacity << "\n";
            std::cout << "-------------------\n";
        }
    }
void assignMarks() {
    string courseCode;
    int roll;
    int mark;
    cout << "Enter the code of the course to assign marks: ";
    cin >> courseCode;

    int courseIndex = findCourseIndexByCode(courseCode);
    for (int i = 0; i < courseCount; i++)
    {
        if (courseCode == courses[i].code) {

            cout << "enter roll number of student you want to assign marks";
            cin >> roll;
            for(int j=0;j<studentCount;j++)
            {
                if (roll == students[j].roll_num)
                {
                    cout << "Adding marks to roll no" << roll;
                    cout << "enter marks out of 100";
                    cin >> mark;
                    students[j].marks = mark;
                }
            
            }
        }
        else {
            std::cout << "Course with code " << courseCode << " not found.\n";
        }
    }
}
    void run() {
        int choice;
        do {
            std::cout << "Main Menu\n";
            std::cout << "1- Enroll a student\n2- Display Enrolled Students\n"
                << "3- Add a course\n4- Display Available Courses\n5- Exit\n";
            std::cout << "Press 1 to 5 to select an option: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                enrollStudent();
                break;
            case 2:
                displayEnrolledStudents();
                break;
            case 3:
                addCourse();
                break;
            case 4:
                displayAvailableCourses();
                break;
            case 5:
                saveDataToFile();
                std::cout << "Exiting the system.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    System universitySystem;
    universitySystem.run();

    return 0;
}
