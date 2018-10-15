//Made by Anna Kravets, K-22
#pragma once
#include <vector>
#include<string>
#include <iostream>
using namespace std;

//returns min 2^k that 2^k>=n
int minPower2(int n);
//everything is done in base 10
//if you want another base - that is YOUR problem(!!!
const int base = 10;

class Multer;

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
	LongInt& shift(int x);
	static Multer *m;
	LongInt operator *(const LongInt& other);
	int getCap() const;
	int operator[](int i) const;
	bool getSign() const;
	//compares two LongInts 
	//based on their ABS! value
	bool operator >=(const LongInt& other) const;
	void setSign(bool s);
private:
	vector<int> digits = {};
	int capacity = 0;
	bool sign = true;
};


LongInt operator-(const LongInt& first, const LongInt& other);


class Multer {
public:
	virtual string getName() {
		return "";
	}
	virtual LongInt mult(const LongInt& first, const LongInt& second) {
		return LongInt("");
	}
};




class UsualMulter : public Multer {
public:
	UsualMulter() { cout << getName() << endl; }
	string getName() {
		return "Usual Multer";
	}
	LongInt mult(const LongInt& first, const LongInt& second);
};

class KaratsubaMulter : public Multer {
public:
	KaratsubaMulter() { cout << getName() << endl; }
	string getName() {
		return "Karatsuba Multer";
	}
	LongInt mult(const LongInt& first, const LongInt& second);
};


class Toom3Multer : public Multer {
public:
	Toom3Multer() { cout << getName() << endl; }
	string getName() {
		return "Toom-3 Multer";
	}
	LongInt mult(const LongInt& first, const LongInt& second);
};

class SchonhageMulter : public Multer {
public:
	SchonhageMulter()  { cout << getName() << endl; }
	string getName(){
		return "Schonhage Multer";
	}
	LongInt mult(const LongInt& first, const LongInt& second);
};

class StrassenMulter : public Multer {
public:
	StrassenMulter() { cout << getName() << endl; }
	string getName() {
		return "Strassen Multer";
	}
	LongInt mult(const LongInt& first, const LongInt& second);
};


//Tests to check if n is prime

bool EasyTest(long long n);

bool RabinMillerTest(long long n);

bool SolovayStrassenTest(long long n);
