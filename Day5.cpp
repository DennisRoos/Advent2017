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

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int t;
		vector<int> v;
		vector<int> u;
		while (infile >> t) {
			v.push_back(t);
			u.push_back(t);
		}

		int steps = 0;
		int current = 0;
		while (current >= 0 && current < v.size()) {
			int a = v[current];
			v[current]++;
			current += a;
			steps++;
		}

		cout << "The number of steps for part 1 was " << steps << endl;

		steps = 0;
		current = 0;
		while (current >= 0 && current < u.size()) {
			int a = u[current];
			if (a >= 3) {
				u[current]--;
			}
			else {
				u[current]++;
			}
			current += a;
			steps++;
		}
		cout << "The number of steps for part 2 was " << steps << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}