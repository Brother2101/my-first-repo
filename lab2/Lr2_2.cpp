#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;

class Student {
private:
    string lastName;
    string firstName;
    string middleName;
    int birthYear;
    string address;
    string phone;
    string faculty;
    int course;

    static int objectCount;

public:
    // Конструктор по умолчанию
    Student() {
        lastName = "Неизвестно";
        firstName = "Неизвестно";
        middleName = "Неизвестно";
        birthYear = 2000;
        address = "Неизвестно";
        phone = "Неизвестно";
        faculty = "Неизвестно";
        course = 1;
        objectCount++;
    }

    // Конструктор с параметрами
    Student(string ln, string fn, string mn, int by,
            string addr, string ph, string fac, int crs)
        : lastName(ln), firstName(fn), middleName(mn),
          birthYear(by), address(addr), phone(ph),
          faculty(fac), course(crs)
    {
        objectCount++;
    }

    // Конструктор копирования
    Student(const Student& other)
        : lastName(other.lastName), firstName(other.firstName),
          middleName(other.middleName), birthYear(other.birthYear),
          address(other.address), phone(other.phone),
          faculty(other.faculty), course(other.course)
    {
        objectCount++;
    }

    // Деструктор
    ~Student() {
        objectCount--;
    }

    // set
    void setFaculty(string value) { faculty = value; }
    void setCourse(int value) { course = value; }
    void setAddress(string value) { address = value; }

    // get
    string getLastName() const { return lastName; }
    string getFaculty() const { return faculty; }
    int getCourse() const { return course; }

    // возраст
    int getAge(int currentYear) const {
        return currentYear - birthYear;
    }

    // вывод
    void show() const {
        cout << lastName << " " << firstName << " " << middleName
             << " | " << birthYear
             << " | " << faculty
             << " | курс: " << course << endl;
    }

    static int getObjectCount() {
        return objectCount;
    }
};

int Student::objectCount = 0;

// ================= ФУНКЦИИ =================

// изменение (по ссылке)
void modify_object(Student& s) {
    s.setFaculty("Изменено");
    s.setCourse(s.getCourse() + 1);
    s.setAddress("Новый_адрес");
}

// не изменение (копия)
void try_to_modify_object(Student s) {
    s.setFaculty("Изменено");
    s.setCourse(s.getCourse() + 1);
    s.setAddress("Новый_адрес");

    cout << "Внутри функции:\n";
    s.show();
}

// загрузка из файла
vector<Student> loadFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return students;
    }

    string ln, fn, mn, addr, phone, fac;
    int year, course;

    while (file >> ln >> fn >> mn >> year >> addr >> phone >> fac >> course) {
        students.emplace_back(ln, fn, mn, year, addr, phone, fac, course);
    }

    return students;
}

// ================= DEMO =================

void demoAll(const vector<Student>& students) {
    if (students.empty()) {
        cout << "Нет данных!\n";
        return;
    }

    cout << "\n===== СПИСОК СТУДЕНТОВ =====\n";
    for (const auto& s : students) {
        s.show();
    }

    cout << "Объектов: " << Student::getObjectCount() << endl;
}

void demoModify(const vector<Student>& students) {
    if (students.empty()) return;

    Student s = students[0];

    cout << "\nДо modify:\n";
    s.show();

    modify_object(s);

    cout << "После modify:\n";
    s.show();
}

void demoTryModify(const vector<Student>& students) {
    if (students.empty()) return;

    Student s = students[0];

    cout << "\nДо try:\n";
    s.show();

    try_to_modify_object(s);

    cout << "После try (без изменений):\n";
    s.show();
}

void demoDynamic(const vector<Student>& students) {
    if (students.empty()) return;

    vector<Student*> ptrs;

    for (const auto& s : students) {
        ptrs.push_back(new Student(s));
    }

    cout << "\n===== ДИНАМИЧЕСКИЕ ОБЪЕКТЫ =====\n";

    for (auto* p : ptrs) {
        p->show();
    }

    cout << "До удаления: " << Student::getObjectCount() << endl;

    for (auto* p : ptrs) {
        delete p;
    }

    cout << "После удаления: " << Student::getObjectCount() << endl;
}

// MAIN 

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    vector<Student> students = loadFromFile("students.txt");

    int choice;

    do {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Показать студентов\n";
        cout << "2. modify_object\n";
        cout << "3. try_to_modify_object\n";
        cout << "4. Динамические объекты\n";
        cout << "5. Количество объектов\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: demoAll(students); break;
            case 2: demoModify(students); break;
            case 3: demoTryModify(students); break;
            case 4: demoDynamic(students); break;
            case 5: cout << "Объектов: " << Student::getObjectCount() << endl; break;
        }

    } while (choice != 0);

    return 0;
}