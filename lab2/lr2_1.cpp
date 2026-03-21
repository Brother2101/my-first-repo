#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Student {
public:
    // public поля
    string lastName;
    string firstName;
    string middleName;
    int birthYear;
    string address;
    string phone;
    string faculty;
    int course;

    static int objectCount;

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
        cout << "Конструктор по умолчанию. Объектов: " << objectCount << endl;
    }

    // Конструктор с параметрами
    Student(string ln, string fn, string mn, int by,
            string addr, string ph, string fac, int crs) {
        lastName = ln;
        firstName = fn;
        middleName = mn;
        birthYear = by;
        address = addr;
        phone = ph;
        faculty = fac;
        course = crs;
        objectCount++;
        cout << "Конструктор с параметрами. Объектов: " << objectCount << endl;
    }

    // Конструктор копирования
    Student(const Student& other) {
        lastName = other.lastName;
        firstName = other.firstName;
        middleName = other.middleName;
        birthYear = other.birthYear;
        address = other.address;
        phone = other.phone;
        faculty = other.faculty;
        course = other.course;
        objectCount++;
        cout << "Конструктор копирования. Объектов: " << objectCount << endl;
    }

    // Деструктор
    ~Student() {
        objectCount--;
        cout << "Деструктор. Осталось объектов: " << objectCount << endl;
    }

    // возраст
    int getAge(int currentYear) const {
        return currentYear - birthYear;
    }

    // вывод
    void show() const {
        cout << lastName << " " << firstName << " " << middleName
             << ", Год: " << birthYear
             << ", Факультет: " << faculty
             << ", Курс: " << course << endl;
    }

    static int getCount() {
        return objectCount;
    }
};

int Student::objectCount = 0;

// изменяет объект
void modify_object(Student& s) {
    s.faculty = "Изменено";
    s.course += 1;
    s.address = "Новый_адрес";
}

// не изменяет объект
void try_to_modify_object(Student s) {
    s.faculty = "Внутри функции";
    s.course += 10;
    s.address = "Временный_адрес";

    cout << "\nВнутри try_to_modify_object:\n";
    s.show();
}

// ===== ДЕМО =====

void demoConstructors() {
    Student s1;
    s1.lastName = "Иванов";
    s1.firstName = "Иван";
    s1.middleName = "Иванович";
    s1.birthYear = 2003;
    s1.faculty = "ФИТ";
    s1.course = 2;

    Student s2("Петров", "Петр", "Петрович", 2002,
               "Казань", "123", "Эконом", 3);

    Student s3(s2);

    cout << "\nОбъекты:\n";
    s1.show();
    s2.show();
    s3.show();

    cout << "Всего объектов: " << Student::getCount() << endl;
}

void demoModify() {
    Student s("Иванов", "Иван", "Иванович", 2003,
              "Москва", "123", "ФИТ", 2);

    cout << "\nДо:\n";
    s.show();

    modify_object(s);

    cout << "После modify_object:\n";
    s.show();
}

void demoTryModify() {
    Student s("Петров", "Петр", "Петрович", 2002,
              "Казань", "123", "Эконом", 3);

    cout << "\nДо:\n";
    s.show();

    try_to_modify_object(s);

    cout << "После (не изменился):\n";
    s.show();
}

void demoDynamic() {
    Student* p = new Student("Сидоров", "Сидор", "Сидорович", 2004,
                              "Омск", "123", "ФИТ", 1);

    cout << "\nДинамический объект:\n";
    p->show();

    delete p;

    cout << "После delete: " << Student::getCount() << endl;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;

    do {
        cout << "\n====== МЕНЮ (PUBLIC) ======\n";
        cout << "1. Конструкторы\n";
        cout << "2. modify_object\n";
        cout << "3. try_to_modify_object\n";
        cout << "4. new/delete\n";
        cout << "5. Количество объектов\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: demoConstructors(); break;
            case 2: demoModify(); break;
            case 3: demoTryModify(); break;
            case 4: demoDynamic(); break;
            case 5: cout << "Объектов: " << Student::getCount() << endl; break;
            case 0: break;
            default: cout << "Ошибка\n";
        }

    } while (choice != 0);

    return 0;
}