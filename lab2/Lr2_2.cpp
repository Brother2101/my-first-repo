#include <iostream>
#include <string>
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
        cout << "Вызван конструктор по умолчанию. Объектов: " << objectCount << endl;
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
        cout << "Вызван конструктор с параметрами. Объектов: " << objectCount << endl;
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
        cout << "Вызван конструктор копирования. Объектов: " << objectCount << endl;
    }

    // Деструктор
    ~Student() {
        objectCount--;
        cout << "Вызван деструктор. Объектов осталось: " << objectCount << endl;
    }

    // set-методы
    void setLastName(string value) { lastName = value; }
    void setFirstName(string value) { firstName = value; }
    void setMiddleName(string value) { middleName = value; }
    void setBirthYear(int value) { birthYear = value; }
    void setAddress(string value) { address = value; }
    void setPhone(string value) { phone = value; }
    void setFaculty(string value) { faculty = value; }
    void setCourse(int value) { course = value; }

    // get-методы
    string getLastName() const { return lastName; }
    string getFirstName() const { return firstName; }
    string getMiddleName() const { return middleName; }
    int getBirthYear() const { return birthYear; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    string getFaculty() const { return faculty; }
    int getCourse() const { return course; }

    // Метод подсчета возраста
    int getAge(int currentYear) const {
        return currentYear - birthYear;
    }

    // Метод вывода
    void show() const {
        cout << "Фамилия: " << lastName << endl;
        cout << "Имя: " << firstName << endl;
        cout << "Отчество: " << middleName << endl;
        cout << "Год рождения: " << birthYear << endl;
        cout << "Возраст: " << getAge(2025) << endl;
        cout << "Адрес: " << address << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Факультет: " << faculty << endl;
        cout << "Курс: " << course << endl;
        cout << "-----------------------------" << endl;
    }

    // Получить количество объектов
    static int getObjectCount() {
        return objectCount;
    }
};

// Инициализация статического поля
int Student::objectCount = 0;

// Функция с изменением исходного объекта
void modify_object(Student& s) {
    s.setFaculty("Измененный_факультет");
    s.setCourse(s.getCourse() + 1);
    s.setAddress("Измененный_адрес");
}

// Функция без изменения исходного объекта
void try_to_modify_object(Student s) {
    s.setFaculty("Измененный_факультет");
    s.setCourse(s.getCourse() + 1);
    s.setAddress("Измененный_адрес");

    cout << "\nОбъект внутри try_to_modify_object():\n";
    s.show();
}

// Демонстрация конструкторов
void demoConstructors() {
    cout << "\n===== ДЕМОНСТРАЦИЯ КОНСТРУКТОРОВ =====\n";

    Student s1;
    s1.setLastName("Иванов");
    s1.setFirstName("Иван");
    s1.setMiddleName("Иванович");
    s1.setBirthYear(2003);
    s1.setAddress("Москва");
    s1.setPhone("89001234567");
    s1.setFaculty("ФИТ");
    s1.setCourse(2);

    cout << "\nОбъект, созданный конструктором по умолчанию:\n";
    s1.show();

    Student s2("Петров", "Петр", "Петрович", 2002,
               "Казань", "89001112233", "Эконом", 3);

    cout << "\nОбъект, созданный конструктором с параметрами:\n";
    s2.show();

    Student s3(s2);

    cout << "\nОбъект, созданный конструктором копирования:\n";
    s3.show();

    cout << "Текущее количество объектов: " << Student::getObjectCount() << endl;
}

// Демонстрация modify_object
void demoModifyObject() {
    cout << "\n===== ДЕМОНСТРАЦИЯ modify_object =====\n";

    Student s("Иванов", "Иван", "Иванович", 2003,
              "Москва", "89001234567", "ФИТ", 2);

    cout << "\nДо modify_object():\n";
    s.show();

    modify_object(s);

    cout << "После modify_object():\n";
    s.show();
}

// Демонстрация try_to_modify_object
void demoTryToModifyObject() {
    cout << "\n===== ДЕМОНСТРАЦИЯ try_to_modify_object =====\n";

    Student s("Петров", "Петр", "Петрович", 2002,
              "Казань", "89001112233", "Эконом", 3);

    cout << "\nДо try_to_modify_object():\n";
    s.show();

    try_to_modify_object(s);

    cout << "После try_to_modify_object() исходный объект не изменился:\n";
    s.show();
}

// Классическое создание объектов
void demoStaticObjects() {
    cout << "\n===== КЛАССИЧЕСКОЕ СОЗДАНИЕ ОБЪЕКТОВ =====\n";

    Student s1("Сидоров", "Сидор", "Сидорович", 2004,
               "Омск", "89005556677", "ФИТ", 1);

    Student s2("Кузнецов", "Алексей", "Сергеевич", 2001,
               "Томск", "89009998877", "Эконом", 4);

    cout << "\nОбъект 1:\n";
    s1.show();

    cout << "Объект 2:\n";
    s2.show();

    cout << "Количество объектов сейчас: " << Student::getObjectCount() << endl;
}

// Динамическое создание объектов
void demoDynamicObjects() {
    cout << "\n===== ДИНАМИЧЕСКОЕ СОЗДАНИЕ И УДАЛЕНИЕ ОБЪЕКТОВ =====\n";

    Student* p1 = new Student("Орлов", "Олег", "Игоревич", 2003,
                              "Самара", "89006667788", "ФИТ", 2);

    Student* p2 = new Student("Смирнова", "Анна", "Сергеевна", 2004,
                              "Уфа", "89007778899", "Эконом", 1);

    cout << "\nДинамический объект 1:\n";
    p1->show();

    cout << "Динамический объект 2:\n";
    p2->show();

    cout << "Количество объектов до удаления: " << Student::getObjectCount() << endl;

    delete p1;
    delete p2;

    cout << "Количество объектов после удаления: " << Student::getObjectCount() << endl;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;

    do {
        cout << "\n=========== МЕНЮ ===========\n";
        cout << "1. Демонстрация конструкторов\n";
        cout << "2. Демонстрация modify_object\n";
        cout << "3. Демонстрация try_to_modify_object\n";
        cout << "4. Классическое создание объектов\n";
        cout << "5. Динамическое создание и удаление объектов\n";
        cout << "6. Показать текущее количество объектов\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Неверный ввод.\n";
            continue;
        }

        switch (choice) {
            case 1:
                demoConstructors();
                break;
            case 2:
                demoModifyObject();
                break;
            case 3:
                demoTryToModifyObject();
                break;
            case 4:
                demoStaticObjects();
                break;
            case 5:
                demoDynamicObjects();
                break;
            case 6:
                cout << "Текущее количество объектов: " << Student::getObjectCount() << endl;
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный пункт меню.\n";
        }

    } while (choice != 0);

    return 0;
}