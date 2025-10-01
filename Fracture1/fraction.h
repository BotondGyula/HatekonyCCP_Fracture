#pragma once

#include<string>
#include<iostream>

//sajnos konzisztensen rosszul numenatort írtam, numerator helyett, csak a végén vettem észre. 

//teszt

class Fraction
{
public:
	Fraction() = default;

	Fraction(const int numenator, const int denominator);

	Fraction(const double num);

	Fraction(const int num);

	Fraction(const Fraction& num);

	int GetNumenator() const;
	int GetDenominator() const;
	int& SetNumerator(int num);
	int& SetDenominator(int num);

	void Normalize();

	static int CommonDenominator(const Fraction& a, const Fraction& b);

	Fraction& operator+=(const Fraction other);
	Fraction& operator-=(const Fraction other);
	Fraction& operator*=(const Fraction other);
	Fraction& operator/=(const Fraction other);
	
	bool operator==(const Fraction& other);
	bool operator!=(const Fraction& other);
	
	
	operator int() const;
	operator double() const;
	operator bool() const;
	operator std::string() const;

	Fraction FractionParse(const std::string& f);


private:
	int numenator;
	int denominator;
};

Fraction operator+(Fraction left, const Fraction& right);
Fraction operator-(Fraction left, const Fraction& right);
Fraction operator*(Fraction left, const Fraction& right);
Fraction operator/(Fraction left, const Fraction& right);

std::ostream& operator<<(std::ostream& outputStream, const Fraction& f);
std::istream& operator>>(std::istream& inputStream, Fraction& f);


