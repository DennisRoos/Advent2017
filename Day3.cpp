#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <list>

using namespace std;

int A[500][500];

int Sum(int x, int y) {
	return A[x - 1][y - 1] + A[x - 1][y] + A[x - 1][y + 1] + A[x][y - 1] + A[x][y + 1] + A[x + 1][y - 1] + A[x + 1][y] + A[x + 1][y + 1];
}

int main(int argc, char * argv[])
{
	int ring = 1;
	int stored = 1;
	int target = 312051;
	while (stored + 8 * ring < target) {
		stored += 8 * ring;
		ring++;
	}
	int side = (target - stored) / (2 * ring);
	int middle = stored + (side * 2 * ring) + ring;
	int distance = abs(middle - target) + ring;
	cout << "Distance is " << distance << endl;

	A[250][250] = 1;
	ring = 1;
	int x = 251;
	int y = 250;
	while (true) {
		for (int i = 0; i < ring * 2; i++) {
			int sum = Sum(x, y);
			if (sum > target) {
				cout << "The bigger value is " << sum << endl;
				return 0;
			}
			A[x][y] = sum;
			y--;
		}
		y++;
		x--;
		for (int i = 0; i < ring * 2; i++) {
			int sum = Sum(x, y);
			if (sum > target) {
				cout << "The bigger value is " << sum << endl;
				return 0;
			}
			A[x][y] = sum;
			x--;
		}
		x++;
		y++;
		for (int i = 0; i < ring * 2; i++) {
			int sum = Sum(x, y);
			if (sum > target) {
				cout << "The bigger value is " << sum << endl;
				return 0;
			}
			A[x][y] = sum;
			y++;
		}
		x++;
		y--;
		for (int i = 0; i < ring * 2; i++) {
			int sum = Sum(x, y);
			if (sum > target) {
				cout << "The bigger value is " << sum << endl;
				return 0;
			}
			A[x][y] = sum;
			x++;
		}
		ring++;
	}

	return 0;
}