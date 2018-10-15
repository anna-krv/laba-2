//Made by Anna Kravets, K-22
#include "LongIntegers.h"
#include <cmath> 
#include <stdlib.h>

bool LehmannTest(long long n) {
	return true;
}


bool EasyTest(long long n) {
	long long m = sqrt(n) + 1;
	if (n % 2 == 0 && n!=2)
		return false;
	for (int i = 3; i < m; i+=2) {
		if (n%i == 0)
			return false;
	}
	return true;
}


long long fastPow(long long a, long long t, long long n) {
	if (t == 0)
		return 1;
	if (t == 1)
		return a%n;
	if (t % 2 == 0)
		return (fastPow(a, t / 2, n)*fastPow(a, t / 2, n)) % n;
	return (fastPow(a, t-1, n)*a)%n;
}


bool RabinMillerTest(long long n) {
	if ((n % 2==0 && n!=2) || n==1)
		return false;
	long long s = 0, t = n - 1;
	while (t % 2 == 0) {
		t /= 2;
		s++;
	}
	//generates a random number
	//and implements Miller's test
	//makes it r+1 times 
	long long r = log(n) / log(2) + 1;
	for (long long i = 0; i < r; i++) {
		long long a=0;
		while (a==0)
			a= rand() % n;
		a = fastPow(a, t, n);
		if (a != 1) {
			int counter = 0;
			while (counter < s && (a+1)%n) {
				a = (a*a) % n;
				counter++;
			}
			if (counter == s)
				return false;
		}
	}
	return true;
}


long long gcd(long long a, long long n) {
	if (a == 1 || n == 1)
		return 1;
	if (a == 0)
		return n;
	if (n == 0)
		return a;
	if (a <= n)
		return gcd(a, n%a);
	return gcd(a%n, n);
}


long long jacobian(long long a, long long n) {
	if (a == 1)
		return 1;
	if (a % 2==0) {
		long long x = (n*n - 1) / 8;
		if (x % 2)
			return -1*jacobian(a/2,n);
		else
			return jacobian(a/2, n);
	}
	if (a == n - 1) {
		long long x = (n - 1) / 2;
		if (x % 2)
			return -1;
		else
			return 1;
	}
	long long t = ((n - 1) / 2)*((a - 1) / 2);
	if (t % 2)
		t = -1;
	else t = 1;
	return t*jacobian(n%a, a);
}

//number of iterations in Solovay-Strassen Test
const int k = 20;

bool SolovayStrassenTest(long long n) {
	if (n == 2)
		return true;
	if (n % 2 == 0 || n==1)
		return false;
	for (int i = 0; i < k; i++) {
		long long a = 0;
		while (a == 0)
			a = rand() % n;
		if (gcd(a, n) > 1) 
			return false;
		if (fastPow(a, (n - 1) / 2, n) != (n+jacobian(a, n))%n)
			return false;
	}
	return true;
}