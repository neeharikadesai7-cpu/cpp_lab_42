
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// ==================================================
// UNIT 1: BASICS OF C++
// ==================================================

#define MAX_STUDENTS 50

int globalValue = 100;

inline int square(int n) {
    return n * n;
}

int add(int a, int b = 10) {
    return a + b;
}

void passByValue(int x) {
    x = 500;
}

void passByReference(int &x) {
    x = 500;
}

int& returnByReference(int &x) {
    return x;
}

void displayPointer(float *p) {
    if (p != nullptr)
        cout << "Value through pointer: " << *p << '\n';
}

// ==================================================
// UNIT 2 & 3: CLASSES AND INHERITANCE
// ==================================================

class Person {
protected:
    string name;
    int age;

public:
    Person() : name("Unknown"), age(0) {}

    Person(string n, int a) : name(n), age(a) {}

    Person(const Person &p) : name(p.name), age(p.age) {}

    virtual void displayPerson() const {
        cout << "Name: " << name << "\nAge: " << age << '\n';
    }

    virtual ~Person() {}
};

// Student inherits publicly from Person
class Student : public Person {
private:
    int rollNo;
    string department;
    float marks[5];

    static int studentCount;

public:
    // Nested class
    class Address {
    public:
        string city;

        Address(string c = "Kolhapur") : city(c) {}
    };

    Address address;

    // Default constructor
    Student() : Person(), rollNo(0), department("CSE") {
        for (int i = 0; i < 5; i++)
            marks[i] = 0;

        studentCount++;
    }

    // Parameterized constructor
    Student(string n, int a, int r, string d)
        : Person(n, a), rollNo(r), department(d) {
        for (int i = 0; i < 5; i++)
            marks[i] = 0;

        studentCount++;
    }

    // Copy constructor
    Student(const Student &s)
        : Person(s), rollNo(s.rollNo),
          department(s.department), address(s.address) {
        for (int i = 0; i < 5; i++)
            marks[i] = s.marks[i];

        studentCount++;
    }

    // Function overloading
    void setMarks() {
        for (int i = 0; i < 5; i++) {
            cout << "Enter marks for subject " << i + 1 << " (0-100): ";
            cin >> marks[i];

            if (marks[i] < 0 || marks[i] > 100) {
                cout << "Invalid marks. Setting to 0.\n";
                marks[i] = 0;
            }
        }
    }

    void setMarks(float m) {
        if (m >= 0 && m <= 100)
            marks[0] = m;
    }

    void setMarks(float m1, float m2) {
        if (m1 >= 0 && m1 <= 100)
            marks[0] = m1;

        if (m2 >= 0 && m2 <= 100)
            marks[1] = m2;
    }

    float calculateTotal() const {
        float total = 0;

        for (int i = 0; i < 5; i++)
            total += marks[i];

        return total;
    }

    float calculatePercentage(float maximum = 500) const {
        if (maximum <= 0)
            return 0;

        return (calculateTotal() / maximum) * 100;
    }

    // Returning a reference
    float& getMark(int index) {
        if (index < 0 || index >= 5)
            throw out_of_range("Invalid subject index");

        return marks[index];
    }

    int getRollNo() const {
        return rollNo;
    }

    bool search(int roll) const {
        return rollNo == roll;
    }

    bool compare(const Student &s) const {
        return calculatePercentage() > s.calculatePercentage();
    }

    static int getStudentCount() {
        return studentCount;
    }

    void display() const {
        cout << "\n---------- STUDENT DETAILS ----------\n";
        cout << "Roll Number: " << rollNo << '\n';
        cout << "Name: " << name << '\n';
        cout << "Age: " << age << '\n';
        cout << "Department: " << department << '\n';
        cout << "City: " << address.city << '\n';

        cout << "Marks: ";
        for (int i = 0; i < 5; i++)
            cout << marks[i] << " ";

        cout << "\nTotal Marks: " << calculateTotal();
        cout << "\nPercentage: " << fixed << setprecision(2)
             << calculatePercentage() << "%\n";
    }

    ~Student() override {
        studentCount--;
    }
};

// Definition of static data member
int Student::studentCount = 0;

// Faculty inherits from Person
class Faculty : public Person {
private:
    int employeeId;
    string department;
    float monthlySalary;

public:
    Faculty(string n, int a, int id, string d, float salary)
        : Person(n, a), employeeId(id),
          department(d), monthlySalary(salary) {}

    float annualSalary() const {
        return monthlySalary * 12;
    }

    void displayFaculty() const {
        cout << "\n---------- FACULTY DETAILS ----------\n";
        displayPerson();
        cout << "Employee ID: " << employeeId << '\n';
        cout << "Department: " << department << '\n';
        cout << "Monthly Salary: " << monthlySalary << '\n';
        cout << "Annual Salary: " << annualSalary() << '\n';
    }

    ~Faculty() override {}
};

class Department {
private:
    string departmentName;
    string hod;

public:
    Department(string d = "CSE", string h = "Not Assigned")
        : departmentName(d), hod(h) {}

    void display() const {
        cout << "\nDepartment: " << departmentName << '\n';
        cout << "Head of Department: " << hod << '\n';
    }
};

// ==================================================
// INHERITANCE TYPES DEMONSTRATION
// ==================================================

// Multilevel inheritance
class EngineeringStudent : public Student {
private:
    string branch;

public:
    EngineeringStudent(string n, int a, int r,
                       string d, string b)
        : Student(n, a, r, d), branch(b) {}

    void displayEngineeringStudent() const {
        display();
        cout << "Engineering Branch: " << branch << '\n';
    }
};

// Multiple inheritance
class Sports {
protected:
    string sport;

public:
    Sports(string s = "Not specified") : sport(s) {}
};

class SportsStudent : public Student, public Sports {
public:
    SportsStudent(string n, int a, int r, string d, string s)
        : Student(n, a, r, d), Sports(s) {}

    void displaySports() const {
        display();
        cout << "Sport: " << sport << '\n';
    }
};

// Private inheritance
class PrivateStudent : private Person {
public:
    PrivateStudent(string n, int a) : Person(n, a) {}

    void displayPrivateStudent() const {
        displayPerson();
    }
};

// ==================================================
// MAIN PROGRAM
// ==================================================

int main() {
    Student* students[MAX_STUDENTS] = {};
    int studentTotal = 0;
    int choice = -1;

    do {
        cout << "\n\n====================================\n";
        cout << "     COLLEGE MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Faculty Details\n";
        cout << "5. Department Details\n";
        cout << "6. Compare Two Students\n";
        cout << "7. Copy Constructor Demonstration\n";
        cout << "8. Function Overloading Demonstration\n";
        cout << "9. Pointer and Reference Demonstration\n";
        cout << "10. Static Member Demonstration\n";
        cout << "11. Basic C++ Concepts Demonstration\n";
        cout << "12. Inheritance Demonstration\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            if (studentTotal >= MAX_STUDENTS) {
                cout << "Student storage is full.\n";
                break;
            }

            string n, d;
            int a, r;

            cout << "Enter student name: ";
            cin >> ws;
            getline(cin, n);

            cout << "Enter age: ";
            cin >> a;

            cout << "Enter roll number: ";
            cin >> r;

            cout << "Enter department: ";
            cin >> ws;
            getline(cin, d);

            students[studentTotal] = new Student(n, a, r, d);
            students[studentTotal]->setMarks();

            studentTotal++;
            cout << "Student added successfully!\n";
            break;
        }

        case 2:
            if (studentTotal == 0)
                cout << "No students registered.\n";

            for (int i = 0; i < studentTotal; i++)
                students[i]->display();

            break;

        case 3: {
            int roll;
            bool found = false;

            cout << "Enter roll number to search: ";
            cin >> roll;

            for (int i = 0; i < studentTotal; i++) {
                if (students[i]->search(roll)) {
                    students[i]->display();
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Student not found.\n";

            break;
        }

        case 4: {
            Faculty f("Professor Patil", 40, 101, "CSE", 50000);
            f.displayFaculty();
            break;
        }

        case 5: {
            Department d("Computer Science", "Dr. Kulkarni");
            d.display();
            break;
        }

        case 6: {
            if (studentTotal < 2) {
                cout << "Add at least two students first.\n";
                break;
            }

            int r1, r2;
            Student *s1 = nullptr, *s2 = nullptr;

            cout << "Enter first roll number: ";
            cin >> r1;

            cout << "Enter second roll number: ";
            cin >> r2;

            for (int i = 0; i < studentTotal; i++) {
                if (students[i]->search(r1))
                    s1 = students[i];

                if (students[i]->search(r2))
                    s2 = students[i];
            }

            if (s1 == nullptr || s2 == nullptr) {
                cout << "Student not found.\n";
            } else if (s1 == s2) {
                cout << "You selected the same student twice.\n";
            } else if (s1->compare(*s2)) {
                cout << "First student has a higher percentage.\n";
            } else if (s2->compare(*s1)) {
                cout << "Second student has a higher percentage.\n";
            } else {
                cout << "Both students have equal percentages.\n";
            }

            break;
        }

        case 7:
            if (studentTotal == 0) {
                cout << "Add a student first.\n";
            } else {
                Student copied(*students[0]);
                cout << "Copy created using copy constructor:\n";
                copied.display();
            }
            break;

        case 8:
            if (studentTotal == 0) {
                cout << "Add a student first.\n";
            } else {
                students[0]->setMarks(95.0f);
                students[0]->setMarks(80.0f, 85.0f);

                cout << "Overloaded setMarks() functions demonstrated.\n";
                students[0]->display();
            }
            break;

        case 9:
            if (studentTotal == 0) {
                cout << "Add a student first.\n";
            } else {
                float *ptr = &students[0]->getMark(0);

                cout << "First subject through pointer: ";
                displayPointer(ptr);

                students[0]->getMark(0) = 99;

                cout << "Updated mark through reference: "
                     << students[0]->getMark(0) << '\n';
            }
            break;

        case 10:
            cout << "Current Student objects: "
                 << Student::getStudentCount() << '\n';
            break;

        case 11: {
            int x = 5;

            cout << "\n--- BASIC C++ CONCEPTS ---\n";
            cout << "Global variable: " << globalValue << '\n';
            cout << "Square using inline function: " << square(x) << '\n';
            cout << "Function with default argument: " << add(5) << '\n';

            passByValue(x);
            cout << "After pass by value: " << x << '\n';

            passByReference(x);
            cout << "After pass by reference: " << x << '\n';

            returnByReference(x) = 700;
            cout << "After return by reference: " << x << '\n';

            int numbers[3] = {10, 20, 30};
            int *p = numbers;

            cout << "Array using pointer arithmetic: "
                 << *(p + 1) << '\n';

            int *dynamicValue = new int(100);
            cout << "Dynamic memory value: " << *dynamicValue << '\n';
            delete dynamicValue;

            cout << "Type conversion: "
                 << static_cast<double>(x) / 2 << '\n';

            cout << "Formatted number: " << fixed << setprecision(2)
                 << 3.14159 << '\n';

            break;
        }

        case 12: {
            cout << "\n--- MULTILEVEL INHERITANCE ---\n";
            EngineeringStudent e("Aarav", 20, 201, "CSE", "Computer");

            // Demonstrates inheritance and derived class methods.
            e.displayEngineeringStudent();

            cout << "\n--- MULTIPLE INHERITANCE ---\n";
            SportsStudent ss("Isha", 19, 202, "CSE", "Badminton");
            ss.displaySports();

            cout << "\n--- PRIVATE INHERITANCE ---\n";
            PrivateStudent ps("Riya", 20);
            ps.displayPrivateStudent();

            cout << "\n--- HIERARCHICAL INHERITANCE ---\n";
            Faculty f("Professor Desai", 42, 301, "CSE", 60000);
            f.displayFaculty();

            break;
        }

        case 0:
            cout << "Exiting College Management System...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    // Release dynamically allocated memory.
    for (int i = 0; i < studentTotal; i++)
        delete students[i];

    cout << "All student memory released. Goodbye!\n";
    return 0;
}