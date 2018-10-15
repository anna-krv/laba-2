//Made by Anna Kravets, K-22
#include "LongIntegers.h"
#include <algorithm>
#include <complex>
#include <vector>
#include <cmath>

const double PI = 3.1415926535897;

typedef complex<double> myComplex;

int minPow(int n) {
	if (minPower2(n) * 2 == n)
		return minPower2(n) * 4;
	return minPower2(n) * 2;
}

//pre: vAns - is empty
void resize(vector<myComplex>& vAns, const LongInt& myLong, int newSize) {
	int i = 0; 
	while (i < myLong.getCap()) {
		vAns.push_back(myComplex(myLong[i], 0.));
		i++;
	}
	while (i < newSize) {
		vAns.push_back(myComplex(0., 0.));
		i++;
	}
}


//Fast Fourier Transform
//recursive function to calculate A at n complex points 
//using the time - O(n*log(n))
void FFT(vector<myComplex>& a, myComplex w) {
	if (a.size() <= 1)
		return;
	int n = a.size();
	//Assume a(x)=a0(x^2)+x*a1(x^2)
	vector<myComplex> a0, a1;
	for (int i = 0; i < n; i += 2) {
		a0.push_back(a.at(i));
		a1.push_back(a.at(i + 1));
	}
	//Calculate a0 and a1 at n/2 points
	//recursive call
	FFT(a0, w*w);
	FFT(a1, w*w);
	complex<double> wCur(1., 0.);
	for (int i = 0; i < n; i++) {
		a.at(i) = a0.at(i % (n / 2)) + wCur*a1.at(i % (n / 2));
		wCur *= w;
	}
}


void interpolate(vector<myComplex>& p) {
	int n = p.size();
	myComplex w(cos(-2. * PI / double(n)), sin(-2. * PI / double(n)));
	FFT(p, w);
	for (int i = 0; i < n; i++)
		p.at(i) /= myComplex(double(n),0.);
}

//transforms vector of complex in vector of int
//each int is mod base
void calculate(vector<int>& ans,const vector<myComplex>& p) {
	int add = 0;
	for (int i = 0; i < p.size(); i++) {
		int x = round(p.at(i).real()) + add;
		ans.push_back(x%base);
		add = x / base;
	}
	while (add > 0) {
		ans.push_back(add%base);
		add = add / base;
	}
}


LongInt StrassenMulter::mult(const LongInt& first, const LongInt& second) {
	//a,  b - are like two polynomials
	//p - is like their product
	vector<myComplex> a, b, p;
	int n= minPow(first.getCap()+second.getCap());
	resize(a, first, n);
	resize(b, second, n);
	myComplex w(cos(2. * PI / double(n)), sin(2. * PI / double(n)));
	FFT(a, w);
	FFT(b, w);
	for (int i = 0; i < a.size(); i++) {
		myComplex x = a.at(i)*b.at(i);
		p.push_back(x);
	}
	interpolate(p);
	vector<int> ans;
	calculate(ans, p);
	return LongInt(ans);
}