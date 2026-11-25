#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <string>
using namespace std;

class SIGN {
private:
    string surname, name, zodiac;
    int birthday[3]; // день, месяц, год

public:
    SIGN();
    SIGN(string s, string n, string z, int d, int m, int y);
    SIGN(const SIGN& other);
    SIGN& operator=(const SIGN& other) = default;
    ~SIGN();

    void setSurname(string s);
    void setName(string n);
    void setZodiac(string z);
    void setBirthday(int d, int m, int y);

    string getSurname() const;
    string getName() const;
    string getZodiac() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    friend istream& operator>>(istream& in, SIGN& p);
    friend ostream& operator<<(ostream& out, const SIGN& p);
};

#endif
