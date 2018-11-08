//Made by Anna Kravets, K-22
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
	if (first.getSign() != second.getSign())
		result.setSign(false);
	return result;
}


int minPower2(int n) {
	if (n == 1)
		return 1;
	double ans = log(double(n)) / log(2.);
	int res = int(pow(2., ceil(ans) - 1.));
	return res;
}


//pre: first, second>=0
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
	if (fCap < newCap) {
		strA = "";
		strB = strF;
	}
	else {
		strA = strF.substr(0, fCap - newCap);
		strB = strF.substr(fCap - newCap, newCap);
	}
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
	res0 = res - (res1 + res2);
	res0.shift(newCap);
	res1.shift(2 * newCap);
	return res0 + res1 + res2;
}


LongInt KaratsubaMulter::mult(const LongInt& first, const LongInt& second) {
	LongInt result = KarMulti(first, second);
	if (first.getSign() != second.getSign())
		result.setSign(false);
	return result;
}

/*
*********PLAN:************
1)split first and second in 3 almost~ equal parts
2)calculate: v and u at points 0, 1, -1, 2, inf
3)calculate w at the same points
4)interpolate
Oooooh, sounds SOOOOO easy and great!!!!!!
***************
*/

void split(const LongInt& myLong, LongInt& D2, LongInt& D1, LongInt& D0, int maxCap) {
	string myStr = string(myLong);
	string d2, d1, d0;
	int len = myStr.length();
	if (len <= maxCap * 2)
		d2 = "";
	else
		d2 = myStr.substr(0, len - 2 * maxCap);
	if (len <= maxCap)
		d1 = "";
	else if (len <= maxCap * 2)
		d1 = myStr.substr(0, len - maxCap);
	else
		d1 = myStr.substr(len - 2 * maxCap, maxCap);
	if (len <= maxCap)
		d0 = myStr;
	else
		d0 = myStr.substr(len - maxCap, maxCap);
	D2 = LongInt(d2);
	D1 = LongInt(d1);
	D0 = LongInt(d0);
}

LongInt Toom3Multi(const LongInt& first, const LongInt& second);

void calculate(LongInt *w, const LongInt& A2, const LongInt& A1,
	const LongInt& A0, const LongInt& B2, const LongInt& B1, const LongInt& B0) {
	LongInt Anew, Bnew;
	w[0] = Toom3Multi(A0, B0);
	Anew = A2 + A1.multiply(2) + A0.multiply(4);
	Bnew = B2 + B1.multiply(2) + B0.multiply(4);
	w[1] = Toom3Multi(Anew, Bnew);
	Anew = A2 + A1 + A0;
	Bnew = B2 + B1 + B0;
	w[2] = Toom3Multi(Anew, Bnew);
	Anew = A2.multiply(4) + A1.multiply(2) + A0;
	Bnew = B2.multiply(4) + B1.multiply(2) + B0;
	w[3] = Toom3Multi(Anew, Bnew);
	w[4] = Toom3Multi(A2, B2);
}


LongInt Toom3Multi(const LongInt& first, const LongInt& second) {
	if (first.getCap() == 0 || second.getCap() == 0)
		return LongInt("0");
	if (first.getCap() == 1)
		return second.multiply(first[0]);
	if (second.getCap() == 1)
		return first.multiply(second[0]);
	int maxCap = (max(first.getCap(), second.getCap()) + 2) / 3;
	LongInt A2, A1, A0, B2, B1, B0, Anew, Bnew;
	split(first, A2, A1, A0, maxCap);
	split(second, B2, B1, B0, maxCap);
	//d[] - coefficients of new polynom after interpolation
	LongInt w[5], d[5];
	calculate(w, A2, A1, A0, B2, B1, B0);
	/*******hardcode*********
	Reverse Matrix
	0	    0	    0	     0	         1
	- 1	   1/6    - 2	    1/3       - 3.5
	3.5   -0.5	    5     - 0.5	        3.5
	- 3.5	1/3     - 2	    1/6         - 1
	1	    0	    0	     0	         0
	*/
	d[4] = w[4];
	d[3] = (w[1] + w[3].multiply(2) - w[4].multiply(7).multiply(3)) / 6 - w[0] - w[2].multiply(2);
	d[2] = ((w[0] + w[4]).multiply(7) - (w[1] + w[3])) / 2 + w[2].multiply(5);
	d[1] = (w[3] + w[1].multiply(2) - w[0].multiply(7).multiply(3)) / 6 - w[4] - w[2].multiply(2);
	d[0] = w[0];
	LongInt res;
	res = d[0] + d[1].shift(maxCap) + d[2].shift(2 * maxCap) + d[3].shift(3 * maxCap) + d[4].shift(4 * maxCap);
	return res;
}

LongInt Toom3Multer::mult(const LongInt& first, const LongInt& second) {
	LongInt result=Toom3Multi(first, second);
	if (first.getSign() != second.getSign())
		result.setSign(false);
	return result;
}

LongInt SchonhageMulti(const LongInt& first, const LongInt& second) {
	return LongInt("");
}


LongInt SchonhageMulter::mult(const LongInt& first, const LongInt& second) {
	LongInt result=SchonhageMulti(first, second);
	if (first.getSign() != second.getSign())
		result.setSign(false);
	return result;
}




