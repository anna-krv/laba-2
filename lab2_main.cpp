//Made by Anna Kravets, K-22
#include "LongIntegers.h"
#include <iostream>
using namespace std;

int main()
{
	try {
		string s1, s2;
		cin >> s1 >> s2;
		LongInt a(s1), b(s2), c;
		LongInt::m = new  KaratsubaMulter;
		c = b * a;
		cout << string(c) << endl;
		LongInt::m = new UsualMulter;
		c = b*a;
		cout << string(c) << endl;
		LongInt::m = new Toom3Multer;
		c = b*a;
		cout << string(c) << endl;
	}
	catch (...) {
		cout << "Sorry, I have done smthng wrong(((!((\n";
	}
    return 0;
}

