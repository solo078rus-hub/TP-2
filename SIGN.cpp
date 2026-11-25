#include "SIGN.h"
#include <stdexcept>

SIGN::SIGN() {
    surname = name = zodiac = "";
    birthday[0] = 1;
    birthday[1] = 1;
    birthday[2] = 2000;
    cout << "SIGN: конструктор без параметров\n";
}

SIGN::SIGN(string s, string n, string z, int d, int m, int y) {
    setSurname(s);
    setName(n);
    setZodiac(z);
    setBirthday(d, m, y);
    cout << "SIGN: конструктор с параметрами\n";
}

SIGN::SIGN(const SIGN& other) {
    surname = other.surname;
    name = other.name;
    zodiac = other.zodiac;
    for (int i = 0; i < 3; i++)
        birthday[i] = other.birthday[i];
    cout << "SIGN: конструктор копирования\n";
}

SIGN::~SIGN() {
    cout << "SIGN: деструктор (" << surname << ")\n";
}

void SIGN::setSurname(string s) { surname = s; }
void SIGN::setName(string n) { name = n; }
void SIGN::setZodiac(string z) { zodiac = z; }

void SIGN::setBirthday(int d, int m, int y) {
    if (m < 1 || m > 12 || y < 1)
        throw runtime_error("Неверная дата рождения");

    int days[12] = {31, 28, 31, 30, 31, 30,
                    31, 31, 30, 31, 30, 31};
    if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
        days[1] = 29;

    if (d < 1 || d > days[m - 1])
        throw runtime_error("Неверный день рождения");

    birthday[0] = d;
    birthday[1] = m;
    birthday[2] = y;
}

string SIGN::getSurname() const { return surname; }
string SIGN::getName() const { return name; }
string SIGN::getZodiac() const { return zodiac; }
int SIGN::getDay() const { return birthday[0]; }
int SIGN::getMonth() const { return birthday[1]; }
int SIGN::getYear() const { return birthday[2]; }

istream& operator>>(istream& in, SIGN& p) {
    string s, n, z;
    int d, m, y;

    cout << "Фамилия: ";
    in >> s;
    cout << "Имя: ";
    in >> n;
    cout << "Знак зодиака: ";
    in >> z;
    cout << "Дата рождения (день месяц год): ";
    if (!(in >> d >> m >> y))
        throw runtime_error("Ошибка ввода данных");

    // Создаем объект только после проверки даты
    SIGN temp(s, n, z, d, m, y);
    p = temp;
    return in;
}

ostream& operator<<(ostream& out, const SIGN& p) {
    out << p.surname << " " << p.name << " | "
        << p.zodiac << " | " << p.birthday[0] << "."
        << p.birthday[1] << "." << p.birthday[2];
    return out;
}
