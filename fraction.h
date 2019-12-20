//Fraction
/*
Powered By Ag2S at SDU
Just a fleshman learner =-=
so the lib has bug please inform me at 
179608737@qq.com(I got a school email but that would expose my student number)
thaks for using
*/
#pragma once
#ifndef __AG2S__FRACTION
#define __AG2S__FRACTION

#ifndef __cplusplus
#error C++ Liburary
#endif

#if __cplusplus < 201100LL  //if you're using Visual studio, delete the fowing lines line
#error Low_Edition
#endif

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int got_max_spanner(int i,int j) {
	int a=i,b=j;
	if(b!=0) {
		return got_max_spanner(b,a%b);
	} else {
		return a;
	}
}

class fraction {
	private:
		int molecular;
		int denominator;
		double value;
	public:
		fraction (int up,int down) {
			molecular = up;
			denominator = down;
			reduction();
			value = (double)up/(double)down;
		}
		fraction () = default;
		fraction (double val) { /*A funny way to turn double to fraction*/
			value = val;
			int ti=val;
			double td = val-ti;
			int times = 1;
			while (td > 0){
				val *= 10;
				ti = val;
				td= val - ti;
				times *=10; 
			}
			molecular = ti;
			denominator = times;
			reduction();
		}
		fraction (int val) {
			value = val;
			molecular = val;
			denominator = 1;
		}
		~fraction () = default;
		int mole () const { return molecular;}
		int deno () const { return denominator;}
		double val() const { return value;}

		void reduction () {
			int span = got_max_spanner(molecular,denominator);
			if(span != 0){
				molecular = molecular/span;
				denominator = denominator/span;
			}
		}
		void output () {
			if(denominator == 1 || molecular == 0)
				cout<<molecular;
			else
				cout<<molecular<<'/'<<denominator;
		}
		fraction operator+ (const fraction &c) {
			fraction b;
			b.denominator = this->denominator*c.denominator;
			b.molecular= this->molecular*c.denominator+c.molecular*this->denominator;
			b.value =this->value+c.value;
			b.reduction();
			return b;
		}
		fraction operator- (const fraction &c) {
			fraction b;
			b.denominator = this->denominator*c.denominator;
			b.molecular= this->molecular*c.denominator-c.molecular*this->denominator;
			b.value =this->value-c.value;
			b.reduction();
			return b;
		}
		fraction operator* (const fraction &c) {
			fraction b;
			b.denominator = this->denominator*c.denominator;
			b.molecular =this->molecular*c.molecular;
			b.value = this->value*c.value;
			b.reduction();
			return b;
		}
		fraction operator/ (const fraction &c) {
			fraction b;
			fraction temp;
			temp.molecular = c.denominator;
			temp.denominator = c.molecular;
			b=*this*temp;
			return b;
		}
		/*The default = operator between fractions works*/
		fraction operator= (const int &i) {
			this->denominator = 1;
			this->molecular = i;
			this->value = i;
			return *(this);
		}
		fraction operator= (const double &d) {
			this->value = d;
			double val = d;
			int ti = val;
			double td = val-ti;
			int times = 1;
			while (td > 0){
				val *= 10;
				ti = val;
				td= val - ti;
				times *=10; 
			}
			this -> molecular = ti;
			this ->denominator = times;
			this ->reduction();
			return *(this);
		}
};

#endif