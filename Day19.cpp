#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>  
#include <limits>


using namespace std;


struct minecart
{
	int x;
	int y;
	int d;

	minecart() :  y(0), d(2) {}
};


struct less_than_angle
{
	inline bool operator() (const minecart& a1, const minecart& a2)
	{
		if (a1.y == a2.y) {
			return a1.x < a2.x;
		}
		return a1.y < a2.y;
	}
};

char A[250][250];
minecart m;


void move() {
	int steps = 0;
	while (true) {
		if (m.d == 0) {//up
			m.y--;
		}
		if (m.d == 1) {//right
			m.x++;
		}
		if (m.d == 2) {//down
			m.y++;
		}
		if (m.d == 3) {//left
			m.x--;
		}
		steps++;
		int x = m.x;
		int y = m.y;
		char a = A[x][y];
		//cout << x << "," << y << " " << m.d << ": " << a << endl;
		if (a == ' ') {
			cout << endl << "Total steps were " << steps << endl;
			return;
		}
		else if (a >= 'A' && a <= 'Z') {
			cout << a;
		}
		else if (a == '+') {
			if (m.d == 0 || m.d == 2) {//up or down
				if (A[x + 1][y] == ' ') {
					m.d = 3;
				}
				else {
					m.d = 1;
				}
			}
			else if (m.d == 1 || m.d == 3) {//left or right
				if (A[x][y+1] == ' ') {
					m.d = 0;
				}
				else {
					m.d = 2;
				}
			}
		}
	}
}



int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");


	string s;
	int xmax = 0;
	int ymax = 0;
	int w;
	int width;
	if (infile.is_open())
	{
		int h = 0;
		while (getline(infile, s)) {
			w = s.size();
			int i = 0;
			for (i; i < w; i++) {
				char c = s[i];
				A[i][h] = c;
				cout << c;
			}
			cout << endl;
			h++;
			width = i;
		}
		cout << endl;
		for (int i = 0; i < width; i++) {
			if (A[i][0] == '|') {
				m.x = i;
				break;
			}
		}
		move();
		cout << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}