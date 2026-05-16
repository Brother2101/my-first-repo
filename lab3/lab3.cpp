#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>


using namespace std;

class Human {
protected:
    string lastName;
    string firstName;
    string middleName;
    int birthYear;

public:
    Human(string ln, string fn, string mn, int by)
        : lastName(ln), firstName(fn), middleName(mn), birthYear(by) {}

    virtual ~Human() {}

    int getAge(int currentYear) const {
        return currentYear - birthYear;
    }

    virtual void show() const {
        cout << "ФИО: " << lastName << " " << firstName << " " << middleName << endl;
        cout << "Год рождения: " << birthYear << endl;
        cout << "Возраст: " << getAge(2025) << endl;
    }
};

class Student : public Human {
private:
    string address;
    string phone;
    string faculty;
    int course;

public:
    Student(string ln, string fn, string mn, int by,
            string addr, string ph, string fac, int crs)
        : Human(ln, fn, mn, by),
          address(addr), phone(ph), faculty(fac), course(crs) {}

    void show() const override {
        cout << "\n===== STUDENT =====\n";
        Human::show();
        cout << "Адрес: " << address << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Факультет: " << faculty << endl;
        cout << "Курс: " << course << endl;
    }
};

class Worker : public Human {
private:
    string position;
    int salary;

public:
    Worker(string ln, string fn, string mn, int by,
           string pos, int sal)
        : Human(ln, fn, mn, by),
          position(pos), salary(sal) {}

    void increaseSalary(int value) {
        salary += value;
    }

    void show() const override {
        cout << "\n===== WORKER =====\n";
        Human::show();
        cout << "Должность: " << position << endl;
        cout << "Зарплата: " << salary << endl;
    }
};

void loadStudentsFromFile(vector<Human*>& people, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    string ln, fn, mn, addr, phone, fac;
    int year, course;

    while (file >> ln >> fn >> mn >> year >> addr >> phone >> fac >> course) {
        people.push_back(new Student(ln, fn, mn, year, addr, phone, fac, course));
    }

    file.close();
}

void loadWorkersFromFile(vector<Human*>& people, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    string ln, fn, mn, position;
    int year, salary;

    while (file >> ln >> fn >> mn >> year >> position >> salary) {
        people.push_back(new Worker(ln, fn, mn, year, position, salary));
    }

    file.close();
}


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    vector<Human*> people;

    loadStudentsFromFile(people, "students.txt");
    loadWorkersFromFile(people, "workers.txt");

    int choice;

    do {
        cout << "\n========== МЕНЮ ==========\n";
        cout << "1. Показать студентов\n";
        cout << "2. Показать сотрудников\n";
        cout << "3. Показать всех\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "\n===== STUDENTS =====\n";

            for (Human* person : people) {

                Student* s = dynamic_cast<Student*>(person);

                if (s != nullptr) {
                    s->show();
                }
            }

            break;

        case 2:
            cout << "\n===== WORKERS =====\n";

            for (Human* person : people) {

                Worker* w = dynamic_cast<Worker*>(person);

                if (w != nullptr) {
                    w->show();
                }
            }

            break;

        case 3:
            cout << "\n===== ALL PEOPLE =====\n";

            for (Human* person : people) {
                person->show();
            }

            break;

        case 0:
            cout << "Выход из программы.\n";
            break;

        default:
            cout << "Неверный пункт меню.\n";
        }

    } while (choice != 0);

    // очистка памяти
    for (Human* person : people) {
        delete person;
    }

    return 0;
}