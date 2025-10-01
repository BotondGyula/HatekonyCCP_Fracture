#include "fraction.h"
#include <stdexcept>
#include <utility>
#include <numeric> 
#include <cmath> 
#include <sstream>

//comment
Fraction::Fraction(const int numerator, const int denominator)
	: numenator{ numerator }
	, denominator{denominator }
{
	if (denominator == 0) {
		throw std::invalid_argument("Denominator cannot be zero. It is automatically set to 1");
	}
	Normalize();

}

Fraction::Fraction(const double num) 
{
	const int prec = 10000; //Ez a pontossághoz kell
	numenator = static_cast<int>(num * prec);
	denominator = prec;
	Normalize();
}

Fraction::Fraction(const int num):numenator(num),denominator(num == 0 ? 1 : num)
{

}

Fraction::Fraction(const Fraction& num) :numenator(num.numenator),denominator(num.denominator)
{

}



int Fraction::GetNumenator() const {
	return numenator;
}

int Fraction::GetDenominator() const {
	return denominator;
}

int& Fraction:: SetNumerator(int num) {
	numenator = num;
	return numenator;
}

int& Fraction:: SetDenominator(int num) {
	denominator = num;
	return denominator;
}

void Fraction::Normalize() 
{

	if (denominator < 0) {
		numenator = -numenator;
		denominator = -denominator;
	}

	if (numenator == 0) {
		denominator = 1;
		return;
	}

	int g = std::gcd(numenator, denominator);
	
	if (g > 1) {
		numenator /= g;
		denominator /= g;
	}
}

int Fraction::CommonDenominator(const Fraction& a,const Fraction& b) {
	return std::lcm(a.denominator,b.denominator);
}

Fraction& Fraction::operator+=(const Fraction other) {

	int lcd = CommonDenominator(*this, other); 

	int factor_this = lcd / this->denominator;
	int factor_other = lcd / other.denominator;

	numenator = numenator * factor_this + other.numenator * factor_other;
	denominator = lcd;

	Normalize();

	return *this;
}

Fraction& Fraction:: operator-=(const Fraction other) {
	int lcd = CommonDenominator(*this, other);

	int factor_this = lcd / this->denominator;
	int factor_other = lcd / other.denominator;

	numenator = numenator * factor_this - other.numenator * factor_other;
	denominator = lcd;

	Normalize();

	return *this;
}

Fraction& Fraction:: operator*=(const Fraction other) {
	numenator = numenator * other.numenator;
	denominator = denominator * other.denominator;
	Normalize();

	return *this;
}

Fraction& Fraction:: operator/=(const Fraction other) {
	numenator = numenator * other.denominator;
	denominator = denominator * other.numenator;

	Normalize();
	
	return *this;
	
}

bool Fraction:: operator==(const Fraction& other) {
	return(this->numenator == other.numenator && this->denominator == other.denominator);
}

bool Fraction:: operator!=(const Fraction& other) {
	return(!(*this == other));
}
	
Fraction operator+(Fraction left, const Fraction& right) {
	int common = Fraction::CommonDenominator(left, right);

	int mL = common / left.GetDenominator();
	int mR = common / right.GetDenominator();

	int num = left.GetNumenator() * mL + right.GetNumenator() * mR;

	left.SetNumerator(num);
	left.SetDenominator(common);

	left.Normalize();

	return left;


}

Fraction operator-(Fraction left, const Fraction& right) {
	int common = Fraction::CommonDenominator(left, right);

	int mL = common / left.GetDenominator();
	int mR = common / right.GetDenominator();

	int num = left.GetNumenator() * mL - right.GetNumenator() * mR;

	left.SetNumerator(num);
	left.SetDenominator(common);

	left.Normalize();

	return left;


}

Fraction operator*(Fraction left, const Fraction& right) {
	int numenator = left.GetNumenator() * right.GetNumenator();
	int denominator = left.GetDenominator() * right.GetDenominator();

	left.SetNumerator(numenator);
	left.SetDenominator(denominator);

	left.Normalize();
	
	return left;

}

Fraction operator/(Fraction left, const Fraction& right) {
	int numenator = left.GetNumenator() * right.GetDenominator();
	int denominator = left.GetDenominator() * right.GetNumenator();

	left.SetNumerator(numenator);
	left.SetDenominator(denominator);

	left.Normalize();

	return left;

}

Fraction:: operator int() const {
	return numenator / denominator;
}

Fraction::operator double() const {
	return static_cast<double>(numenator) / denominator;
}

Fraction::operator bool() const {
	return(numenator / denominator > 0.5);
}

Fraction:: operator std::string() const {
	return(std::to_string(numenator) + "/" + std::to_string(denominator));
}


std::ostream& operator<<(std::ostream& outputStream, const Fraction& f) {
	outputStream << std::to_string(f.GetNumenator()) + "/" + std::to_string(f.GetDenominator());
	return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Fraction& f) {
	char p;
	int numenator;
	int denominator;

	if (inputStream >> numenator >> p >> denominator) {
		if (denominator == 0) {
			throw std::invalid_argument("A nevezõ nem lehet 0!");
		}
		else if (p != '/') {
			p = '/';
		}
		else {
			f.SetDenominator(denominator);
			f.SetNumerator(numenator);
			f.Normalize();
		}
		
	}
	return inputStream; 
}



Fraction Fraction:: FractionParse(const std::string& s) {

	std::stringstream ss(s);
	int numenatorl;
	int denominatorl;
	char per;

	if (ss >> numenatorl >> per >> denominatorl) {
		if (per != '/') {
			throw std::invalid_argument("Missing:'/'");
		}
		if (denominatorl == 0) {
			throw std::invalid_argument("Invalid denominator! 0 not allowed, please seek help!");
		}
		Fraction f(numenatorl, denominatorl);
		return f;
		

	}

	throw std::invalid_argument("Invalid format!");

}







