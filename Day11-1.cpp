#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <iterator>         // std::(istream_iterator, back_inserter)
#include <sstream>          // std::(istringstream)
#include <list>

using namespace std;

int A[500][1000];
int xmax;
int ymax;


/*void traverse(int x, int y, int d) {
	if (x < 0 || y < 0 || x > xmax || y > ymax) {// out of bounds
		return;
	}
	if (d > 905) {
		return;
	}
	if (A[x][y] <= d) {
		return;
	}
	A[x][y] = d;
	//traverse(x, y - 1, d + 1);
	traverse(x + 1, y, d + 1);
	traverse(x, y + 1, d + 1);
	//traverse(x - 1, y, d + 1);
	if (x % 2 == 0) {//even
		traverse(x + 1, y + 1, d + 1);
		//traverse(x - 1, y + 1, d + 1);
	}
	else {
		traverse(x + 1, y - 1, d + 1);
		//traverse(x - 1, y - 1, d + 1);
	}

	return;
}*/

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int x = 0;
		int y = 0;
		string s;
		while (infile >> s) {
			if (s.compare("n") == 0) {
				y++;
			}
			else if (s.compare("s") == 0) {
				y--;
			}
			else if (s.compare("ne") == 0) {
				if (abs(x) % 2 == 0) {//even
					y++;
				}
				x++;
			}
			else if (s.compare("se") == 0) {
				if (abs(x) % 2 == 1) {//odd
					y--;
				}
				x++;
			}
			else if (s.compare("nw") == 0) {
				if (abs(x) % 2 == 0) {//even
					y++;
				}
				x--;
			}
			else if (s.compare("sw") == 0) {
				if (abs(x) % 2 == 1) {//odd
					y--;
				}
				x--;
			}
		}
		cout << "Target is at " << x << "," << y << endl;
		xmax = x;
		ymax = y;
		for (int i = 0; i <= xmax; i++) {
			for (int j = 0; j <= ymax; j++) {
				A[i][j] = 99999;
			}
		}
		traverse(0, 0, 0);
		cout << "Distance is " << A[xmax][ymax] << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}