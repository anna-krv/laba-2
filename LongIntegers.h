//Made by Anna Kravets, K-22
#pragma once
#include <vector>
#include<string>
using namespace std;

int minPower2(int n);
const int base = 10;

class Multer;
class LongInt;


class Multer {
public:
	virtual LongInt mult(const LongInt& first, const LongInt& second)=0;
};


class LongInt {
public:
	LongInt(string s="", bool sign_=true);
	//у векторі всі числа не більше base
	//останнє число у векторі - не 0
	LongInt(const vector<int>& myVec, bool sign_=true);
	LongInt(const LongInt& other);
	LongInt(LongInt&& other);
	LongInt& operator=(const LongInt& other);
	LongInt& operator=(LongInt&& other);
	LongInt operator+(const LongInt& other) const;
	operator string() const;
	LongInt multiply(int n) const;
	LongInt& shift(int x);
	static Multer *m;
	LongInt operator *(const LongInt& other);
	int getCap() const;
	int operator[](int i) const;
	bool getSign() const;
	//compares two LongInts 
	//based on their ABS! value
	bool operator >=(const LongInt& other) const;
	void setSign(bool s) {
		sign = s;
	}
private:
	vector<int> digits = {};
	int capacity=0;
	static const int maxDigits = 16;
	//false якщо число<0
	bool sign = true;
};


LongInt operator-(const LongInt& first, const LongInt& other);


class UsualMulter : public Multer {
public:
	LongInt mult(const LongInt& first, const LongInt& second);
};

class KaratsubaMulter : public Multer {
public:
	LongInt mult(const LongInt& first, const LongInt& second);
};


class Toom3Multer : public Multer {
public:
	LongInt mult(const LongInt& first, const LongInt& second);
};



