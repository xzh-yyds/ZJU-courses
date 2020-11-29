#ifndef _FRACTION_H
#define _FRACTION_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class Fraction{
private:
    int numerator;
    int denominator;
public:
    // default constructor
    Fraction(); 
    // construct with two integers
    Fraction(int a,int b); 
    // copy constructor
    Fraction(const Fraction& f);
    // construct with a finite decimal string
    Fraction(std::string df);
    // construct with a double
    Fraction(double f);
    ~Fraction();
    //simplufy the fraction
    void simplify();

    // overload arithmetical operators
    Fraction operator+(const Fraction& f);
    Fraction operator-(const Fraction& f);
    Fraction operator*(const Fraction& f);
    Fraction operator/(const Fraction& f);

    // overload relational operators
    bool operator<(const Fraction f);
    bool operator>(const Fraction f);
    bool operator==(const Fraction f);
    bool operator!=(const Fraction f);
    bool operator>=(const Fraction f);
    bool operator<=(const Fraction f);

    // to std_string
    std::string frac2string();
    // to double
    double frac2double();

    // inserter and extractor for streams
    friend std::istream& operator>>(std::istream& in, Fraction& f);
    friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
    friend std::ifstream& operator>>(std::ifstream& in, Fraction& f);
    friend std::ofstream& operator<<(std::ofstream& out, const Fraction& f);
};
// overload arithmetical operators
Fraction operator+(const Fraction f, const int x);
Fraction operator-(const Fraction f, const int x);
Fraction operator*(const Fraction f, const int x);
Fraction operator/(const Fraction f, const int x);

Fraction operator+(const int x, const Fraction& f);
Fraction operator-(const int x, const Fraction& f);
Fraction operator*(const int x, const Fraction& f);
Fraction operator/(const int x, const Fraction& f);

Fraction operator+(const Fraction& f, const double x);
Fraction operator-(const Fraction& f, const double x);
Fraction operator*(const Fraction& f, const double x);
Fraction operator/(const Fraction& f, const double x);

Fraction operator+(const double x, const Fraction& f);
Fraction operator-(const double x, const Fraction& f);
Fraction operator*(const double x, const Fraction& f);
Fraction operator/(const double x, const Fraction& f);

// overload relational operators
bool operator<(const Fraction f, const int x);
bool operator>(const Fraction f, const int x);
bool operator==(const Fraction f, const int x);
bool operator!=(const Fraction f, const int x);
bool operator<=(const Fraction f, const int x);
bool operator>=(const Fraction f, const int x);

bool operator<=(const int x, const Fraction f);
bool operator>=(const int x, const Fraction f);
bool operator==(const int x, const Fraction f);
bool operator!=(const int x, const Fraction f);
bool operator<(const int x, const Fraction f);
bool operator>(const int x, const Fraction f);

bool operator<=(const double x, const Fraction f);
bool operator>=(const double x, const Fraction f);
bool operator==(const double x, const Fraction f);
bool operator!=(const double x, const Fraction f);
bool operator<(const double x, const Fraction f);
bool operator>(const double x, const Fraction f);

bool operator<=(const Fraction f, const double x);
bool operator>=(const Fraction f, const double x);
bool operator==(const Fraction f, const double x);
bool operator!=(const Fraction f, const double x);
bool operator<(const Fraction f, const double x);
bool operator>(const Fraction f, const double x);

#endif