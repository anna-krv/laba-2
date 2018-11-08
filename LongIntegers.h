//Made by Anna Kravets, K-22
#pragma once
#include <vector>
#include<string>
#include <iostream>
#include <iomanip>
using namespace std;

//Tests to check if n is prime
bool LehmannTest(long long n);
bool RabinMillerTest(long long n);
bool SolovayStrassenTest(long long n);

//returns min 2^k that 2^k>=n
int minPower2(int n);
//everything is done in base 10
//if you want another base - that is YOUR problem(!!!
const int base = 10;

class Multer;
class LongReal;

class LongInt {
public:
	LongInt(string s = "", bool sign_ = true);
	LongInt(const vector<int>& myVec, bool sign_ = true);
	LongInt(const LongInt& other);
	LongInt(LongInt&& other);
	LongInt& operator=(const LongInt& other);
	LongInt& operator=(LongInt&& other);
	LongInt operator+(const LongInt& other) const;
	operator string() const;
	LongInt multiply(int n) const;
	//pre: n - is a "digit"
	//pre: we are expected to get integer result
	LongInt operator/ (int n) const;
	LongReal operator/(const LongInt& other);
	LongInt& shift(int x);
	static Multer *m;
	LongInt operator *(const LongInt& other);
	LongReal inverse() const; //Cook's algorithm
	int getCap() const;
	int operator[](int i) const;
	bool getSign() const;
	//compares two LongInts 
	//based on their ABS! values
	bool operator >=(const LongInt& other) const;
	void setSign(bool s);
private:
	vector<int> digits = {};
	int capacity = 0;
	bool sign = true;
};

LongInt operator-(const LongInt& first, const LongInt& other);

class LongReal{
public:
	LongReal(string s="", bool sign_ = true);
	LongReal(LongInt myLong_, int decim_=0);
	LongReal operator+(const LongReal& other) const;
	LongReal operator *(const LongReal& other);
	operator string() const;
	int getDecim() const;
	friend LongReal operator-(const LongReal& first, const LongReal& other);
	LongReal cut(int x); //leaves only x decimal points 
private:
	LongInt myLong; //long integer=long real*10^decim
	int decim=0; //number of digits after decimal point
};



class Multer {
public:
	Multer(string s) {cout << left << setw(20) << s;}
	virtual LongInt mult(const LongInt& first, const LongInt& second) {
		return LongInt("");
	}
};


class UsualMulter : public Multer {
public:
	UsualMulter():Multer("Usual Multer ") {}
	LongInt mult(const LongInt& first, const LongInt& second);
};

class KaratsubaMulter : public Multer {
public:
	KaratsubaMulter() :Multer("Karatsuba Multer ") {}
	LongInt mult(const LongInt& first, const LongInt& second);
};


class Toom3Multer : public Multer {
public:
	Toom3Multer() :Multer("Toom-3 Multer ") {}
	LongInt mult(const LongInt& first, const LongInt& second);
};

class SchonhageMulter : public Multer {
public:
	SchonhageMulter() :Multer("Schonhage Multer ") {}
	LongInt mult(const LongInt& first, const LongInt& second);
};

class StrassenMulter : public Multer {
public:
	StrassenMulter() :Multer("Strassen Multer ") {}
	LongInt mult(const LongInt& first, const LongInt& second);
};