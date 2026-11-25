#include "SIGN.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>

// Считывание целого числа с проверкой
int readInt() {
    int x;
    if (!(cin >> x))
        throw runtime_error("Необходимо ввести целое число");
    return x;
}

// Сравнение дат: сначала год, потом месяц и день
bool later(const SIGN& a, const SIGN& b) {
    if (a.getYear() != b.getYear())
        return a.getYear() > b.getYear();
    if (a.getMonth() != b.getMonth())
        return a.getMonth() > b.getMonth();
    return a.getDay() > b.getDay();
}

void sortPeople(SIGN* people, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (later(people[j], people[j + 1])) {
                SIGN temp(people[j]);
                people[j] = people[j + 1];
                people[j + 1] = temp;
            }
        }
    }
}

void showPeople(SIGN* people, int n) {
    if (n == 0) cout << "Список пуст\n";
    for (int i = 0; i < n; i++)
        cout << i + 1 << ". " << people[i] << "\n";
}

void addPerson(SIGN*& people, int& n) {
    cout << "Позиция добавления (1-" << n + 1 << "): ";
    int pos = readInt();
    if (pos < 1 || pos > n + 1)
        throw runtime_error("Неверная позиция");

    SIGN person;
    cin >> person;
    SIGN* temp = new SIGN[n + 1];

    for (int i = 0; i < pos - 1; i++)
        temp[i] = people[i];
    temp[pos - 1] = person;
    for (int i = pos - 1; i < n; i++)
        temp[i + 1] = people[i];

    delete[] people;
    people = temp;
    n++;
    sortPeople(people, n);
}

void deletePerson(SIGN*& people, int& n) {
    showPeople(people, n);
    if (n == 0) return;
    cout << "Номер записи для удаления: ";
    int pos = readInt();
    if (pos < 1 || pos > n)
        throw runtime_error("Такой записи нет");

    SIGN* temp = new SIGN[n - 1];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i != pos - 1) {
            temp[j] = people[i];
            j++;
        }
    }
    delete[] people;
    people = temp;
    n--;
}

void editPerson(SIGN* people, int n) {
    showPeople(people, n);
    if (n == 0) return;
    cout << "Номер записи для изменения: ";
    int pos = readInt();
    if (pos < 1 || pos > n)
        throw runtime_error("Такой записи нет");

    cout << "Введите новые данные записи:\n";
    cin >> people[pos - 1];
    sortPeople(people, n);
}

void findPeople(SIGN* people, int n) {
    string zodiac;
    cout << "Введите знак зодиака: ";
    cin >> zodiac;
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (people[i].getZodiac() == zodiac) {
            cout << people[i] << "\n";
            found = true;
        }
    }
    if (!found) cout << "Люди с таким знаком не найдены\n";
}

// Второе задание: работа с файловым и строковым потоками
void readText() {
    string filename;
    cout << "Введите имя файла: ";
    getline(cin >> ws, filename);
    ifstream file(filename.c_str());
    if (!file.is_open())
        throw runtime_error("Не удалось открыть файл");

    string text, line;
    while (getline(file, line))
        text += line + " ";
    file.close();

    stringstream stream(text);
    string sentence, questions, exclamations;
    char c;

    while (stream.get(c)) {
        if (sentence.empty() && (c == ' ' || c == '\t' || c == '\r'))
            continue;
        sentence += c;
        if (c == '?' || c == '!' || c == '.') {
            // Несколько конечных знаков считаем одним окончанием
            while (stream.peek() == '?' || stream.peek() == '!' || stream.peek() == '.') {
                char next;
                stream.get(next);
                sentence += next;
            }
            if (c == '?') questions += sentence + "\n";
            else if (c == '!') exclamations += sentence + "\n";
            sentence = "";
        }
    }

    cout << "\nВопросительные предложения:\n";
    if (questions.empty()) cout << "Нет таких предложений\n";
    else cout << questions;
    cout << "\nВосклицательные предложения:\n";
    if (exclamations.empty()) cout << "Нет таких предложений\n";
    else cout << exclamations;
}

int main() {
    SIGN* people = nullptr;
    int n = 0;
    int choice = -1;

    while (choice != 0) {
        cout << "\n--- МЕНЮ ---\n"
             << "1. Добавить человека\n"
             << "2. Показать всех\n"
             << "3. Изменить запись\n"
             << "4. Удалить запись\n"
             << "5. Поиск по знаку зодиака\n"
             << "6. Обработать текст из файла\n"
             << "0. Выход\n"
             << "Ваш выбор: ";
        try {
            choice = readInt();
            switch (choice) {
                case 1: addPerson(people, n); break;
                case 2: showPeople(people, n); break;
                case 3: editPerson(people, n); break;
                case 4: deletePerson(people, n); break;
                case 5: findPeople(people, n); break;
                case 6: readText(); break;
                case 0: break;
                default: cout << "Нет такого пункта меню\n";
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << "\n";
            if (cin.eof()) break;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    delete[] people;
    return 0;
}
