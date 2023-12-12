#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 50;
const int MAX_ENROLLED_STUDENTS = 100;

class Student {
public:
    string name;
    int roll_num;
    int age;
    string contact;
    bool present;
    int marks;
    Student() : present(false), marks(-1) {}
};

class Course {
public:
    std::string code;
    std::string name;
    std::string instructor;
    int credits;
    int capacity=0;
    int enrolled_students[MAX_ENROLLED_STUDENTS];
    Course() : capacity(0) {}
};

class System {
private:
    Student students[MAX_STUDENTS];
    Course courses[MAX_COURSES];
    int studentCount = 0;
    int courseCount = 0;
    

    void initializeCourses() {
        for (int i = 0; i < MAX_COURSES; ++i) {
            courses[i].capacity = 0;  // Initialize course capacities
            for (int j = 0; j < MAX_ENROLLED_STUDENTS; ++j) {
                courses[i].enrolled_students[j] = -1;
            }
        }
    }

    void saveStudentsToFile() {
        std::ofstream file("students.txt");
        if (file.is_open()) {
            for (int i = 0; i < studentCount; ++i) {
                file << students[i].name << "|" << students[i].roll_num << "|"
                    << students[i].age << "|" << students[i].contact << "|" << students[i].marks << "\n";
            }
            file.close();
            cout << "Student data successfully saved to file.\n";
        }
        else {
            cout << "Unable to open students file for writing.\n";
        }
    }

    void loadStudentsFromFile() {
        std::ifstream file("students.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                string line;
                getline(file, line);

                if (line.empty()) {
                    break;
                }

                stringstream ss(line);
                string name, contact;
                int roll, age, marks;

                getline(ss, name, '|');
                ss >> roll;
                ss.ignore(1, '|');
                ss >> age;
                ss.ignore(1, '|');
                getline(ss, contact, '|');
                ss >> marks;

                // Add the loaded student to the students array
                students[studentCount].name = name;
                students[studentCount].roll_num = roll;
                students[studentCount].age = age;
                students[studentCount].contact = contact;
                students[studentCount].marks = marks;

                // Increment the student count
                ++studentCount;
            }
            file.close();
            cout << "Student data successfully loaded from file.\n";
        }
        else {
            cout << "Unable to open students file for reading.\n";
        }
    }


    void saveCoursesToFile() {
        std::ofstream file("courses.txt");
        if (file.is_open()) {
            for (int i = 0; i < courseCount; ++i) {
                file << courses[i].code << "|" << courses[i].name << "|"
                    << courses[i].instructor << "|" << courses[i].credits << "|"
                    << courses[i].capacity << "|";

                
                file << "\n";
            }
            file.close();
            cout << "Course data successfully saved to file.\n";
        }
        else {
            cout << "Unable to open courses file for writing.\n";
        }
    }

    void loadCoursesFromFile() {
        std::ifstream file("courses.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                string line;
                getline(file, line);

                if (line.empty()) {
                    break;
                }

                stringstream ss(line);
                string code, name, instructor;
                int credits, capacity;

                getline(ss, code, '|');
                getline(ss, name, '|');
                getline(ss, instructor, '|');
                ss >> credits;
                ss.ignore(1, '|');
                ss >> capacity;
                ss.ignore(1, '|');

                // Add the loaded course to the courses array
                courses[courseCount].code = code;
                courses[courseCount].name = name;
                courses[courseCount].instructor = instructor;
                courses[courseCount].credits = credits;
                courses[courseCount].capacity = capacity;

                
                // Increment the course count
                ++courseCount;
            }
            file.close();
            cout << "Course data successfully loaded from file.\n";
        }
        else {
            cout << "Unable to open courses file for reading.\n";
        }
    }

    void saveAttendanceToFile() {
        std::ofstream file("attendance.txt");
        if (file.is_open()) {
            for (int i = 0; i < courseCount; ++i) {
                for (int j = 0; j < courses[i].capacity; ++j) {
                    int studentRoll = courses[i].enrolled_students[j];
                    int studentIndex = findStudentByRoll(studentRoll);

                    if (studentIndex != -1) {
                        file << courses[i].code << "|" << students[studentIndex].roll_num << "|"
                            << students[studentIndex].name << "|" << students[studentIndex].present << "\n";
                    }
                }
            }
            file.close();
            cout << "Attendance data successfully saved to file.\n";
        }
        else {
            cout << "Unable to open attendance file for writing.\n";
        }
    }

    void loadAttendanceFromFile() {
        std::ifstream file("attendance.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                string line;
                getline(file, line);

                if (line.empty()) {
                    break;
                }

                stringstream ss(line);
                string courseCode, studentName;
                int studentRoll;
                bool present;

                getline(ss, courseCode, '|');
                ss >> studentRoll;
                ss.ignore(1, '|');
                getline(ss, studentName, '|');
                ss >> present;

                // Find the course index by code
                int courseIndex = findCourseIndexByCode(courseCode);

                if (courseIndex != -1) {
                    // Find the student index by roll number
                    int studentIndex = findStudentByRoll(studentRoll);

                    if (studentIndex != -1) {
                        students[studentIndex].present = present;
                        cout << "Attendance data loaded for " << studentName << " in course " << courses[courseIndex].name << "\n";
                    }
                    else {
                        cout << "Error: Student with roll number " << studentRoll << " not found.\n";
                    }
                }
                else {
                    cout << "Error: Course with code " << courseCode << " not found.\n";
                }
            }
            file.close();
            cout << "Attendance data successfully loaded from file.\n";
        }
        else {
            cout << "Unable to open attendance file for reading.\n";
        }
    }


    void saveMarksToFile() {
        std::ofstream file("marks.txt");
        if (file.is_open()) {
            for (int i = 0; i < courseCount; ++i) {
                for (int j = 0; j < courses[i].capacity; ++j) {
                    int studentRoll = courses[i].enrolled_students[j];
                    int studentIndex = findStudentByRoll(studentRoll);

                    if (studentIndex != -1) {
                        file << courses[i].code << "|" << students[studentIndex].roll_num << "|"
                            << students[studentIndex].name << "|" << students[studentIndex].marks << "\n";
                    }
                }
            }
            file.close();
            cout << "Marks data successfully saved to file.\n";
        }
        else {
            cout << "Unable to open marks file for writing.\n";
        }
    }

    void loadMarksFromFile() {
        std::ifstream file("marks.txt");
        if (file.is_open()) {
            while (!file.eof()) {
                string line;
                getline(file, line);

                if (line.empty()) {
                    break;
                }

                stringstream ss(line);
                string courseCode, studentName;
                int studentRoll, marks;

                getline(ss, courseCode, '|');
                ss >> studentRoll;
                ss.ignore(1, '|');
                getline(ss, studentName, '|');
                ss >> marks;

                // Find the course index by code
                int courseIndex = findCourseIndexByCode(courseCode);

                if (courseIndex != -1) {
                    // Find the student index by roll number
                    int studentIndex = findStudentByRoll(studentRoll);

                    if (studentIndex != -1) {
                        students[studentIndex].marks = marks;
                        cout << "Marks data loaded for " << studentName << " in course " << courses[courseIndex].name << "\n";
                    }
                    else {
                        cout << "Error: Student with roll number " << studentRoll << " not found.\n";
                    }
                }
                else {
                    cout << "Error: Course with code " << courseCode << " not found.\n";
                }
            }
            file.close();
            cout << "Marks data successfully loaded from file.\n";
        }
        else {
            cout << "Unable to open marks file for reading.\n";
        }
    }

    int findCourseIndexByCode(const std::string& courseCode) {
        for (int i = 0; i < courseCount; ++i) {
            if (courses[i].code == courseCode) {
                return i;
            }
        }
        return -1; // Course not found
    }


public:
    System() {
        // Initialize courses when the System object is created
        initializeCourses();
    }

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

        Course* targetCourse = findCourseByCode(courseCode);

        if (targetCourse != nullptr) {
            cout << "Enter the roll number of the student for whom you want to assign marks: ";
            cin >> roll;

            int studentIndex = findStudentByRoll(roll);

            if (studentIndex != -1) {
                // Check if the student is enrolled in the specified course
                if (isStudentEnrolledInCourse(roll, targetCourse)) {
                    cout << "Adding marks to roll no " << roll << "\n";
                    cout << "Enter marks out of 100: ";
                    cin >> mark;
                    students[studentIndex].marks = mark;
                    cout << "Marks assigned for " << students[studentIndex].name << ": " << students[studentIndex].marks << "\n";
                }
                else {
                    cout << "Error: Student with roll number " << roll << " is not enrolled in course " << targetCourse->name << "\n";
                }
            }
            else {
                cout << "Error: Student with roll number " << roll << " not found.\n";
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
            cout << "Enter the roll number of the student for whom you want to mark attendance: ";
            cin >> roll;

            int studentIndex = findStudentByRoll(roll);

            if (studentIndex != -1) {
                // Check if the student is enrolled in the specified course
                if (isStudentEnrolledInCourse(roll, targetCourse)) {
                    cout << "Mark attendance for course: " << targetCourse->name << "\n";
                    cout << "Is " << students[studentIndex].name << " present? (1 for Yes, 0 for No): ";
                    cin >> p;
                    students[studentIndex].present = (p == 1);

                    cout << "Attendance marked for " << students[studentIndex].name << "\n";
                }
                else {
                    cout << "Error: Student with roll number " << roll << " is not enrolled in course " << targetCourse->name << "\n";
                }
            }
            else {
                cout << "Error: Student with roll number " << roll << " not found.\n";
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
            int studentRoll;
            cout << "Enter the roll number of the student: ";
            cin >> studentRoll;

            // Check if the student is enrolled in the course
            if (isStudentEnrolledInCourse(studentRoll, targetCourse)) {
                // Find the student index by roll number
                int studentIndex = findStudentByRoll(studentRoll);

                if (studentIndex != -1) {
                    cout << "Attendance for course: " << targetCourse->name << "\n";
                    cout << "Student: " << students[studentIndex].name << "\n";
                    cout << "Roll Number: " << students[studentIndex].roll_num << "\n";
                    cout << "Attendance: " << (students[studentIndex].present ? "Present" : "Absent") << "\n";
                }
                else {
                    cout << "Error: Student with roll number " << studentRoll << " not found.\n";
                }
            }
            else {
                cout << "Error: Student with roll number " << studentRoll << " is not enrolled in course " << targetCourse->name << "\n";
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
            int studentRoll;
            cout << "Enter the roll number of the student: ";
            cin >> studentRoll;

            // Check if the student is enrolled in the course
            if (isStudentEnrolledInCourse(studentRoll, targetCourse)) {
                // Find the student index by roll number
                int studentIndex = findStudentByRoll(studentRoll);

                if (studentIndex != -1) {
                    cout << "Marks for course: " << targetCourse->name << "\n";
                    cout << "Student: " << students[studentIndex].name << "\n";
                    cout << "Roll Number: " << students[studentIndex].roll_num << "\n";
                    cout << "Marks: " << (students[studentIndex].marks != -1 ? to_string(students[studentIndex].marks) : "Not Assigned") << "\n";
                }
                else {
                    cout << "Error: Student with roll number " << studentRoll << " not found.\n";
                }
            }
            else {
                cout << "Error: Student with roll number " << studentRoll << " is not enrolled in course " << targetCourse->name << "\n";
            }
        }
        else {
            cout << "Course with code " << courseCode << " not found.\n";
        }
    }



    
        void removeStudent() {
            int roll;
            cout << "Enter the roll number of the student to remove: ";
            cin >> roll;

            int studentIndex = findStudentByRoll(roll);

            if (studentIndex != -1) {
                // Remove the student from all courses
                for (int i = 0; i < courseCount; ++i) {
                    removeStudentFromCourse(roll, &courses[i]);
                }

                // Shift the remaining students in the array
                for (int i = studentIndex; i < studentCount - 1; ++i) {
                    students[i] = students[i + 1];
                }

                // Decrement the student count
                --studentCount;

                cout << "Student with roll number " << roll << " removed.\n";
            }
            else {
                cout << "Student with roll number " << roll << " not found.\n";
            }
        }

        void removeStudentFromCourse(int roll, Course * course) {
            for (int i = 0; i < course->capacity; ++i) {
                if (course->enrolled_students[i] == roll) {
                    // Shift the remaining students in the array
                    for (int j = i; j < course->capacity - 1; ++j) {
                        course->enrolled_students[j] = course->enrolled_students[j + 1];
                    }

                    // Decrement the course capacity
                    --course->capacity;

                    break; // Exit the loop once the student is found and removed
                }
            }
        }
        //to find a student by its roll no,this function is used in other functions
        int findStudentByRoll(int roll) {
            for (int i = 0; i < studentCount; ++i) {
                if (students[i].roll_num == roll) {
                    return i;
                }
            }
            return -1; // Student not found
        }

        void registerCourse() {
            int roll;
            cout << "Enter the roll number of the student: ";
            cin >> roll;

            int studentIndex = findStudentByRoll(roll);

            if (studentIndex != -1) {
                string courseCode;
                cout << "Enter the code of the course to register: ";
                cin >> courseCode;

                Course* targetCourse = findCourseByCode(courseCode);

                if (targetCourse != nullptr) {
                    // Check if the student is not already enrolled in the course
                    if (!isStudentEnrolledInCourse(roll, targetCourse)) {
                        // Check if there is capacity in the course
                        if (targetCourse->capacity < MAX_ENROLLED_STUDENTS) {
                            // Enroll the student in the course
                            targetCourse->enrolled_students[targetCourse->capacity] = roll;
                            ++targetCourse->capacity;

                            cout << "Student with roll number " << roll << " registered for course " << targetCourse->name << "\n";
                        }
                        else {
                            cout << "Course " << targetCourse->name << " is already full.\n";
                        }
                    }
                    else {
                        cout << "Student with roll number " << roll << " is already enrolled in course " << targetCourse->name << "\n";
                    }
                }
                else {
                    cout << "Course with code " << courseCode << " not found.\n";
                }
            }
            else {
                cout << "Student with roll number " << roll << " not found.\n";
            }
        }

        bool isStudentEnrolledInCourse(int roll, Course* course) {
            for (int i = 0; i < course->capacity; ++i) {
                if (course->enrolled_students[i] == roll) {
                    return true; // Student is already enrolled in the course
                }
            }
            return false; // Student is not enrolled in the course
        }

        void enrolledCourses() {
            int roll;
            cout << "Enter the roll number of the student: ";
            cin >> roll;

            int studentIndex = findStudentByRoll(roll);

            if (studentIndex != -1) {
                cout << "Courses enrolled by student with roll number " << roll << ":\n";

                for (int i = 0; i < courseCount; ++i) {
                    if (isStudentEnrolledInCourse(roll, &courses[i])) {
                        cout << "- " << courses[i].code<<"  "<<courses[i].name << "\n";
                    }
                }
            }
            else {
                cout << "Student with roll number " << roll << " not found.\n";
            }
        }

        void withdrawFromCourse() {
            int roll;
            cout << "Enter the roll number of the student: ";
            cin >> roll;

            int studentIndex = findStudentByRoll(roll);

            if (studentIndex != -1) {
                string courseCode;
                cout << "Enter the code of the course to withdraw from: ";
                cin >> courseCode;

                Course* targetCourse = findCourseByCode(courseCode);

                if (targetCourse != nullptr) {
                    // Check if the student is enrolled in the course
                    if (isStudentEnrolledInCourse(roll, targetCourse)) {
                        // Withdraw the student from the course
                        withdrawStudentFromCourse(roll, targetCourse);

                        cout << "Student with roll number " << roll << " withdrawn from course " << targetCourse->name << "\n";
                    }
                    else {
                        cout << "Student with roll number " << roll << " is not enrolled in course " << targetCourse->name << "\n";
                    }
                }
                else {
                    cout << "Course with code " << courseCode << " not found.\n";
                }
            }
            else {
                cout << "Student with roll number " << roll << " not found.\n";
            }
        }

        void withdrawStudentFromCourse(int roll, Course* course) {
            for (int i = 0; i < course->capacity; ++i) {
                if (course->enrolled_students[i] == roll) {
                    // Shift the remaining students in the array
                    for (int j = i; j < course->capacity - 1; ++j) {
                        course->enrolled_students[j] = course->enrolled_students[j + 1];
                    }

                    // Decrement the course capacity
                    --course->capacity;

                    break; // Exit the loop once the student is found and withdrawn
                }
            }
        }


    void MainMenu() {
        int choice;
        do {
            cout << "Main Menu\n";
            cout << "1- Enroll a student\n2- Course Registration \n3- Attendance\n4- Marks\n5- Course Withdraw \n6- Exit\n";
            cout << "Press 1 to 6 to select an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                loadStudentsFromFile();
                EnrollMenu();
                break;
            case 2:
                loadCoursesFromFile();
                CourseRegistrationMenu();
                break;
            case 3:
                loadAttendanceFromFile();
                AttendanceMenu();
                break;
            case 4:
                loadMarksFromFile();
                MarksMenu();
                break;
            case 5:
                loadCoursesFromFile();
                CourseWithdrawMenu();
                break;
            case 6:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }

    void EnrollMenu()
    {
        int choice;
        do {
            cout << "Enroll Menu\n";
            cout << "1- Display already enrolled students\n2- Add a student\n3- Remove a student\n4- Edit student detail\n5- Back\n";
            cout << "Press 1 to 5 to select an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayEnrolledStudents();
                break;
            case 2:
                enrollStudent();
                saveStudentsToFile();
                break;
            case 3:
                removeStudent();
                saveStudentsToFile();
                break;
            case 4:
                editStudent();
                saveStudentsToFile();
                break;
            case 5:
                MainMenu();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }

    void CourseRegistrationMenu()
    {
        int choice;
        do {
            cout << "Course Registration Menu\n";
            cout << "1- Add a Course\n2- Display Available courses\n3- Register in a Course\n4- Back\n";
            cout << "Press 1 to 5 to select an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addCourse();
                saveCoursesToFile();
                break;
            case 2:
                displayAvailableCourses();
                break;
            case 3:
                registerCourse();
                saveCoursesToFile();
                break;
            
            case 4:
                MainMenu();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }

    void AttendanceMenu()
    {
        int choice;
        do {
            cout << "Atteandance Menu\n";
            cout << "1- Display Attendance\n2- Mark Attendance\n3- Back\n";
            cout << "Press 1 to 3 to select an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayAttendance();
                break;
            case 2:
                markAttendance();
                saveAttendanceToFile();
                break;
            case 3:
                MainMenu();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }

    void MarksMenu()
    {
        int choice;
        do {
            cout << "Marks Menu\n";
            cout << "1- Display Marks\n2- Assign Marks\n3- Back\n";
            cout << "Press 1 to 3 to select an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayMarks();
                break;
            case 2:
                assignMarks();
                saveMarksToFile();
                break;
            case 3:
                MainMenu();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }

    void CourseWithdrawMenu()
    {
        int choice;
        do {
            cout << "Course WithDraw Menu\n";
            cout << "1- Display Enrolled Courses by a Student\n2- Drop a Course\n3- Back\n";
            cout << "Press 1 to 3 to select an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                enrolledCourses();
                break;
            case 2:
                withdrawFromCourse();
                saveCoursesToFile();
                break;
            case 3:
                MainMenu();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }

    
};

int main() {
    System universitySystem;
    universitySystem.MainMenu();

    return 0;
}
