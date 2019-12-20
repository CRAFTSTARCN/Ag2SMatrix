// matrix object
/*
Matrix lib powered by Ag2S at SDU 
A fleshman learner's exercise project
raly on another lib(Written by me) fraction.h
If you find bug or has some suggestion
please inform me at 179680737@qq.com
thank you
*/
#pragma once

#ifndef __AG2S__MATRIX
#define __AG2S__MATRIX

#include "fraction.h"
#include <memory.h>
#include <string.h>
#include <cstdio>
using namespace std;

typedef fraction unit;

class matrix {
	public:
		unit mat[100][100];
		int lines;
		int rolls;
		//Down't ask me wy to put those functions inside the class I won't do that later=-=
		matrix () {
			lines = 0;
			rolls = 0;
		}
		matrix (int l, int r) {
			lines = l;
			rolls = r;
		}

		~matrix() = default;

		matrix operator+ (const matrix &m) {
			matrix b;
			if(m.lines != this->lines || m.rolls != this->rolls) return b;
			else {
				b.lines = m.lines;
				b.rolls = m.rolls;
				for(int i=0; i<b.lines; ++i)
					for(int j=0; j<b.rolls; ++j)
						b.mat[i][j]=this->mat[i][j]+m.mat[i][j];
				return b;
			}
		}
		matrix operator- (const matrix &m) {
			matrix b;
			if(m.lines != this->lines || m.rolls != this->rolls) return b;
			else {
				b.lines = m.lines;
				b.rolls = m.rolls;
				for(int i=0; i<b.lines; ++i)
					for(int j=0; j<b.rolls; ++j)
						b.mat[i][j]=this->mat[i][j]-m.mat[i][j];
				return b;
			}
		}
		matrix operator* (const matrix &m) {
			matrix b;
			if(this->rolls != m.lines) return b;
			else {
				b.lines = this->lines;
				b.rolls = m.rolls;
				for(int i = 0; i < this->lines; ++i) {
					for(int j =0; j<m.rolls; ++j) {
						fraction temp(0);
						for(int k=0; k<this->rolls; ++k)
							temp = temp+this->mat[i][k]*m.mat[k][j];
						b.mat[i][j]=temp;
					}
				}
				return b;
			}
		}
		matrix operator* (const fraction &s) {
			matrix b;
			b.lines = this->lines;
			b.rolls = this->rolls;
			for(int i=0; i<b.lines; ++i)
				for(int j=0; j<b.rolls; ++j)
					b.mat[i][j] = this->mat[i][j]*s;
			return b;
		}

		void input() {
			/* 
			This funcion is awful
			One of my friend want to input a matrix with giving the line and roll numbers
			so I manage to realize the function
			end the input by click enter key twice 
			*/
			int iline = 0,iroll = 0;
    		string str;
   			while(true){
    	   		getline(cin,str);
        		if(str.empty()) break;
       			iroll = 0;
        		int temp = 0;
        		for(int i = 0;i<str.length();++i) {
            		if(str.at(i) != ' ')
                		temp = temp*10+int(str.at(i) - 48);
            		if(str.at(i) == ' ' || i+1 == str.length()) {
                		if(i == 0 || str.at(i-1) != ' ' || i+1 == str.length() ){
                    		mat[iline][iroll] = temp;
                    		temp = 0;
                    		++iroll;
               	 		}
           			}
        		}
        	++iline;
			}
			lines = iline;
			rolls = iroll;
		}
		void output () {
			for(int i=0; i<lines; ++i) {
				for(int j=0; j<rolls; ++j) {
					mat[i][j].output();
					printf(" ");
				}
				printf("\n");
			}
		}
};

const matrix nullmat;

matrix got_turn (matrix m) {
	matrix b(m.lines,m.rolls);
	for(int i=0; i<m.lines; ++i)
		for(int j=0; j<m.rolls; ++j)
			b.mat[i][j]=m.mat[j][i];
	return b;
}

matrix complement_mat (matrix m,int i,int j) {
	if(m.lines != m.rolls) {
		cout<<"Error: Not a square mat"<<endl;
		return nullmat;
	}
	if(m.lines == 1) {
		cout<<"Error: The dimention of this mat is 1"<<endl;
		return nullmat;
	}
	if(i>=m.lines || j >= m.lines) {
		cout<<"Error: matrix out of range"<<endl;
		return nullmat;
	}
	matrix ans(m.lines-1,m.rolls-1);
	int i_ans=0,j_ans=0;
	for(int a=0;a<m.lines;++a) {
		if(a == i);
		else {
			for(int b = 0; b<m.rolls;++b){
				if(b == j);
				else{
					ans.mat[i_ans][j_ans] = m.mat[a][b];
					++j_ans;
				}
			}
			++i_ans;
			j_ans = 0;
		}
	}
	return ans;
}

unit det(matrix m) {
	if(m.lines != m.rolls) {
		cout<<"ERROR: Not a square matrix"<<endl;
		return 0;
	}
	if(m.lines == 0) {
		cout<<"Error:  Zero dimention matrix"<<endl;
		return 0;
	}
	if (m.lines == 1) return m.mat[0][0];
	if(m.lines == 2) return m.mat[0][0]*m.mat[1][1] - m.mat[0][1]*m.mat[1][0];
	unit ans = 0;
	for(int i= 0;i<m.rolls;++i) {
		matrix c = complement_mat(m,0,i);
		if(i %2 == 0) ans = ans + m.mat[0][i]*det(c);
		else ans = ans - m.mat[0][i]*det(c); 
	}
	return ans;
} 

#endif
