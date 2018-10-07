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
		cout << string(a) << " " << string(b) << endl;
		LongInt::m = new  KaratsubaMulter;
		c = b * a;
		cout << string(c) << endl;
		LongInt::m = new UsualMulter;
		c = b*a;
		cout << string(c) << endl;
		cout << endl;
	}
	catch (logic_error &e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cout << "Sorry, I have done smthng wrong(((!((\n";
	}
    return 0;
}

