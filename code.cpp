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

    void editStudent() {
    int rollNumber;
    std::cout << "Enter the Roll Number of the student you want to edit: ";
    std::cin >> rollNumber;

    int index = -1;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].roll_num == rollNumber) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        std::cout << "Enter new information for the student:\n";
        std::cout << "Name: ";
        std::cin >> students[index].name;
        std::cout << "Age: ";
        std::cin >> students[index].age;
        std::cout << "Contact: ";
        std::cin >> students[index].contact;

        std::cout << "Student information updated successfully.\n";
    }
    else {
        std::cout << "Student with Roll Number " << rollNumber << " not found.\n";
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

void assignMarks() {
    string courseCode;
    int roll;
    int mark;
    cout << "Enter the code of the course to assign marks: ";
    cin >> courseCode;

    Course* targetCourse = findCourseByCode(courseCode);

    if (targetCourse != nullptr) {
        cout << "Enter roll number of the student you want to assign marks: ";
        cin >> roll;

        bool studentFound = false;
        for (int j = 0; j < studentCount; j++) {
            if (roll == students[j].roll_num) {
                cout << "Adding marks to roll no " << roll << "\n";
                cout << "Enter marks out of 100: ";
                cin >> mark;
                students[j].marks = mark;
                studentFound = true;
                cout << students[j].marks;
                break;  // Exit the loop once the student is found
            }
        }

        if (!studentFound) {
            cout << "Student with roll number " << roll << " not found.\n";
        }
    }
    else {
        cout << "Course with code " << courseCode << " not found.\n";
    }
}

Course* findCourseByCode(const string& courseCode) {
    for (int i = 0; i < courseCount; i++) {
        if (courseCode == courses[i].code) {
            return &courses[i];
        }
    }
    return nullptr; // Course not found
}


void markAttendance() {
    string courseCode;
    int roll;
    int p;
    cout << "Enter the code of the course for attendance: ";
    cin >> courseCode;

    Course* targetCourse = findCourseByCode(courseCode);

    if (targetCourse != nullptr) {
        cout << "Mark attendance for course: " << targetCourse->name << "\n";

        for (int j = 0; j < studentCount; j++)
        {
            cout << "Is " << students[j].name << " present? (1 for Yes, 0 for No): ";
            cin >> p;
            students[j].present = p;

            cout << "Attendance marked for " << students[j].name << "\n";
        }
    }
    else {
        cout << "Course with code " << courseCode << " not found.\n";
    }
}
void displayAttendance() {
    string courseCode;
    cout << "Enter the code of the course to display attendance: ";
    cin >> courseCode;

    Course* targetCourse = findCourseByCode(courseCode);

    if (targetCourse != nullptr) {
        cout << "Attendance for course: " << targetCourse->name << "\n";

        for (int i = 0; i < targetCourse->capacity; ++i) {
            int studentIndex = targetCourse->enrolled_students[i];

            cout << "Student: " << students[studentIndex].name << "\n";
            cout << "Roll Number: " << students[studentIndex].roll_num << "\n";
            cout << "Attendance Status: " << (students[studentIndex].present ? "Present" : "Absent") << "\n";
            cout << "------------------------\n";
        }
    }
    else {
        cout << "Course with code " << courseCode << " not found.\n";
    }
}
void displayMarks() {
    string courseCode;
    cout << "Enter the code of the course to display marks: ";
    cin >> courseCode;

    Course* targetCourse = findCourseByCode(courseCode);

    if (targetCourse != nullptr) {
        cout << "Marks for course: " << targetCourse->name << "\n";

        for (int i = 0; i < targetCourse->capacity; ++i) {
            int studentIndex = targetCourse->enrolled_students[i];

            cout << "Student: " << students[studentIndex].name << "\n";
            cout << "Roll Number: " << students[studentIndex].roll_num << "\n";
            cout << "Marks: " << (students[studentIndex].marks != -1 ? to_string(students[studentIndex].marks) : "Not Assigned") << "\n";
            cout << "------------------------\n";
        }
    }
    else {
        cout << "Course with code " << courseCode << " not found.\n";
    }
}


void run() {
    int choice;
    do {
        std::cout << "Main Menu\n";
        cout << "1- Enroll a student\n2- Display Enrolled Students\n"
            << "3- Add a course\n4- Display Available Courses\n5- TO Edit a Student\n6- To Mark Attendance\n7- To assign marks to a student\n" 
          <<"8-Display attendance\n 9- display marks \n 10- Exit\n";
        std::cout << "Press 1 to 8 to select an option: ";
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
            editStudent();
            break;
        case 6:
            markAttendance();
            break;
        case 7:
            assignMarks();
            break;
        case 8:
            displayAttendance();
            break;
        case 9:
            displayMarks();
            break;
        case 10:
            saveDataToFile();
            std::cout << "Exiting the system.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);
}

};

int main() {
    System universitySystem;
    universitySystem.run();

    return 0;
}
