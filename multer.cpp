#include "LongIntegers.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
using namespace std;

Multer* LongInt::m = nullptr;

LongInt UsualMulter::mult(const LongInt& first, const LongInt& second) {
	LongInt result;
	for (int i = 0; i < second.getCap(); i++) {
		LongInt newLongInt = first.multiply(second[i]);
		newLongInt.shift(i);
		result = result + newLongInt;
	}
	return result;
}

//повертає мінімальне число, яке є степенем двійки,
//і яке не менша за n
int minPower2(int n) {
	double ans = log(double(n)) / log(2.);
	int res=int(pow(2., ceil(ans) - 1.));
	return res;
}

//pre: first, second>=0
//Рекурсивна функція для множення за методом Карацуби
LongInt KarMulti(const LongInt& first, const LongInt& second) {
	int fCap = first.getCap(), sCap = second.getCap();
	LongInt res, res1, res2, res0;
	if (fCap == 0 || sCap == 0) {
		return LongInt("", true);
	}
	if (sCap == 1) {
		int n = second[0];
		res = first.multiply(n);
		return res;
	}
	if (fCap == 1) {
		int n = first[0];
		res = second.multiply(n);
		return res;
	}
	int newCap = max(fCap, sCap);
	newCap = minPower2(newCap);
	string strA, strB, strC, strD;
	string strF = string(first), strS = string(second);
	//розбиваєм перше число на 2
	if (fCap < newCap) {
		strA = "";
		strB = strF;
	}
	else {
		strA = strF.substr(0, fCap - newCap);
		strB = strF.substr(fCap - newCap, newCap);
	}
	//розбиваєм друге число на 2
	if (sCap < newCap) {
		strC = "";
		strD = strS;
	}
	else {
		strC = strS.substr(0, sCap - newCap);
		strD = strS.substr(sCap - newCap, newCap);
	}
	LongInt A(strA), B(strB), C(strC), D(strD);
	res = KarMulti(A + B, C + D);
	res1 = KarMulti(A, C);
	res2 = KarMulti(B, D);
	res0 = res - (res1+res2);
	res0.shift(newCap);
	res1.shift(2 * newCap);
	return res0 + res1 + res2;
}


LongInt KaratsubaMulter::mult(const LongInt& first, const LongInt& second) {
	return KarMulti(first, second);
}

/*
*********PLAN:************
1)split first and second in 3 almost~ equal parts
2)calculate: v and u at points 0, 1, -1, 2, inf
3)calculate w at the same points
4)interpolate
Oooooh, sounds SOOOOO easy and greatQ!!!!!!
***************
*/
LongInt Toom3Multer::mult(const LongInt& first, const LongInt& second) {
	return LongInt("0");
}