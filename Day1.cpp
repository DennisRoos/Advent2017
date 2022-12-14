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
		int count = 0;
		string s;
		infile >> s;
		int current = s[0] - '0';
		if (current == s[s.size() - 1] - '0') {
			count += current;
		}
		for (int i = 1; i < s.size(); i++) {
			int n = s[i] - '0';
			if (current == n) {
				count += current;
			}
			current = n;
		}

		cout << "Total for part 1 is " << count << endl;
		count = 0;
		int jump = s.size() / 2;
		for (int i = 0; i < s.size(); i++) {
			int j = (i + jump) % s.size();
			if (s[i] == s[j]) {
				count += s[i] - '0';
			}
		}

		cout << "Total for part 2 is " << count << endl;


	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}