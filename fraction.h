/*
AG2S FRACTION 2.0
A learning project of a freshman
*Fixed some bug about value
*/

#pragma once
#ifndef __AG2S__FRACTION
#define __AG2S__FRACTION

#ifndef __cplusplus
#error Please use C++
#endif

#if __cplusplus <201100L
#error Low edition
#endif
#define LL long long

#include <cmath>
#include <iostream>
using namespace std;
int gcd(int i,int j) {
	int a=i,b=j;
	if(b!=0) {
		return gcd(b,a%b);
	} else {
		return a;
	}
}

//defination of the class;
class fraction {
    private:
    LL molecular;
    LL denominator;
	public:
	LL mole() const {return molecular;}
	LL deno() const {return denominator;}
	double val () const {return double(molecular)/double(denominator);}
	fraction() = default;
	fraction(LL,LL);
	fraction(double);
	~fraction() = default;
	void reduction();
	bool operator== (const fraction);
	bool operator>  (const fraction);
	bool operator<  (const fraction);
	fraction operator+ (const fraction&);
	fraction operator- (const fraction&);
	fraction operator* (const fraction&);
	fraction operator/ (const fraction&);
};
//declaration of outside functions
ostream& operator<< (const ostream&, fraction&);


//construction functions
fraction::fraction(LL up, LL down) {
	molecular = up;
	denominator = down;
	reduction();
}
fraction::fraction(double val) {
	int ti=val;
	double td = val-ti;
	int times = 1;
	while (td > 0){
		val *= 10;
		ti   = val;
		td   = val - ti;
		times *=10; 
	}
	molecular   = ti;
	denominator = times;
	reduction();
}

//reduction important!

void fraction::reduction() {
	int span = gcd(molecular,denominator);
	if(span != 0){
		molecular   = molecular/span;
		denominator = denominator/span;
	}
}

//comperation operators

bool fraction::operator== (const fraction f) {
	return this->val() == f.val();
}
bool fraction::operator<  (const fraction f) {
	return this->val() < f.val();
}
bool fraction::operator>  (const fraction f) {
	return this->val() > f.val();
}

//other operators


fraction fraction::operator+ (const fraction &c) {
	fraction b = 0;
	b.denominator = this->denominator*c.denominator;
	b.molecular   = this->molecular*c.denominator+c.molecular*this->denominator;
	b.reduction();
	return b;
}
fraction fraction::operator- (const fraction &c) {
	fraction b = 0;
	b.denominator = this->denominator*c.denominator;
	b.molecular   = this->molecular*c.denominator-c.molecular*this->denominator;
	b.reduction();
	return b;
}
fraction fraction::operator* (const fraction &c) {
	fraction b = 0;
	b.denominator = this->denominator*c.denominator;
	b.molecular   = this->molecular*c.molecular;
	b.reduction();
	return b;
}
fraction fraction::operator/ (const fraction &c) {
	fraction b = 0;
	fraction temp;
	temp.molecular = c.denominator;
	temp.denominator = c.molecular;
	b=*this*temp;
	return b;
}

//output function
ostream& operator<<(ostream& out, fraction &f) {
	if(f.deno() == 1 || f.mole() == 0)
		out<<f.mole();
	else
		out<<f.mole()<<"/"<<f.deno();
	return out;
}

//Some other api
template <typename _T>
_T operator+ (_T &ori, const fraction &f) {
	ori = ori+f.val();
	return ori;
}
template <typename _T>
_T operator- (_T &ori, const fraction &f) {
	ori = ori-f.val();
	return ori;
}
template <typename _T>
_T operator* (_T &ori, const fraction &f) {
	ori = ori*f.val();
	return ori;
}
template <typename _T>
_T operator/ (_T &ori, const fraction &f) {
	ori = ori/f.val();
	return ori;
}
#endif
