#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;

int A[525][525];

int main(int argc, char * argv[]) {
	string s;
	ifstream f("data.txt");
	int x = 250;
	int y = 250;
	while (getline(f, s)) {
		x = 250;
		for (int i = 0; i < 25; i++) {
			if (s[i] == '#') {
				A[x][y] = 1;
			}
			x++;
		}
		y++;
	}
	x = 262;
	y = 262;
	int count = 0;
	int direction = 0;

	for (int iter = 0; iter < 10000000; iter++) {
		if (A[x][y] == 1) {//infected
			A[x][y] = 3;
			direction = (direction + 1 ) % 4;
		}
		else if (A[x][y] == 0) {//clean
			A[x][y] = 2;
			direction--;
			if (direction < 0) {
				direction = 3;
			}
		}
		else if (A[x][y] == 2) {//weakened
			A[x][y] = 1;
			count++;
		}
		else if (A[x][y] == 3) {//flagged
			A[x][y] = 0;
			direction = (direction + 2) % 4;
		}

		if (direction == 0) {
			y--;
		}
		else if (direction == 1) {
			x++;
		}
		else if (direction == 2) {
			y++;
		}
		else if (direction == 3) {
			x--;
		}
	}

	cout << "There were " << count << " new infections\n";

	return 0;
}