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

struct reg {
	string name;
	int value;
	reg(string n) : name(n), value(0) {};
};

vector<reg> v;

int findReg(string n) {
	for (int i = 0; i < v.size(); i++) {
		if (n.compare(v[i].name) == 0) {
			return i;
		}
	}
	reg p = reg(n);
	v.push_back(p);
	return v.size() - 1;
}



int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int h2 = 0;
		string b2;
		while (getline(infile, s)) {
			stringstream ss(s);
			string n1;
			string n2;
			string op;
			string op2;
			string t;
			int amount;
			int amount2;

			ss >> n1;
			ss >> op;
			ss >> amount;
			ss >> t;
			ss >> n2;
			ss >> op2;
			ss >> amount2;

			int i1 = findReg(n2);
			bool b = false;
			if (op2.compare("<") == 0) {
				if (v[i1].value < amount2) {
					b = true;
				}
			}
			else if (op2.compare(">") == 0) {
				if (v[i1].value > amount2) {
					b = true;
				}
			}
			else if (op2.compare("<=") == 0) {
				if (v[i1].value <= amount2) {
					b = true;
				}
			}
			else if (op2.compare(">=") == 0) {
				if (v[i1].value >= amount2) {
					b = true;
				}
			}
			else if (op2.compare("==") == 0) {
				if (v[i1].value == amount2) {
					b = true;
				}
			}
			else if (op2.compare("!=") == 0) {
				if (v[i1].value != amount2) {
					b = true;
				}
			}
			if (b) {
				int i2 = findReg(n1);
				if (op.compare("inc") == 0) {
					v[i2].value += amount;
					if (v[i2].value > h2) {
						h2 = v[i2].value;
						b2 = v[i2].name;
					}
				}
				else {
					v[i2].value -= amount;
					if (v[i2].value > h2) {
						h2 = v[i2].value;
						b2 = v[i2].name;
					}
				}
			}
		}

		int highest = 0;
		string name;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].value > highest) {
				highest = v[i].value;
				name = v[i].name;
			}
		}
		cout << "The best register for part 1 was " << name << " with value " << highest << endl;
		cout << "The best register for part 2 was " << b2 << " with value " << h2 << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}