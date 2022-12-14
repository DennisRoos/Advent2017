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

vector<int> op;
vector<int> a1;
vector<int> a2;
char A[16];



void round() {

	for (int i = 0; i < op.size(); i++) {
		if (op[i] == 0) {
			int one = a1[i];
			int two = a2[i];
			char t = A[one];
			A[one] = A[two];
			A[two] = t;
		}
		else if (op[i] == 1) {
			int o1 = a1[i];
			int o2 = a2[i];
			char one = o1 + 'a';
			char two = o2 + 'a';
			int i1;
			int i2;
			for (int i = 0; i < 16; i++) {
				if (one == A[i]) {
					i1 = i;
				}
				if (two == A[i]) {
					i2 = i;
				}
			}
			char t = A[i1];
			A[i1] = A[i2];
			A[i2] = t;
		}
		else {//spin
			int spin = a1[i];
			char B[16];
			int j = 0;
			for (int i = 16 - spin; i < 16; i++) {
				B[j] = A[i];
				j++;
			}
			for (int i = 0; i < 16 - spin; i++) {
				B[j] = A[i];
				j++;
			}
			for (int i = 0; i < 16; i++) {
				A[i] = B[i];
			}
		}
	}
}

int main(int argc, char * argv[])
{

	ifstream infile;
	infile.open("data.txt");
	regex re("([sxp])(([\\d]+)\/([\\d]+)|([a-z])\/([a-z]))|(s)([\\d]+)");
	string s;
	smatch match;

	if (infile.is_open())
	{
		for (int i = 0; i < 16; i++) {
			A[i] = 'a' + i;
		}
		while (infile >> s) {
			if (regex_search(s, match, re) == true) {
				if (match.str(1).compare("x") == 0) {
					int one = stoi(match.str(3));
					int two = stoi(match.str(4));
					op.push_back(0);
					a1.push_back(one);
					a2.push_back(two);
				}
				else if (match.str(1).compare("p") == 0) {
					string one = match.str(5);
					string two = match.str(6);
					op.push_back(1);
					a1.push_back(one[0] - 'a');
					a2.push_back(two[0] - 'a');
				}
				else {//spin
					op.push_back(2);
					int spin = stoi(match.str(8));
					a1.push_back(spin);
					a2.push_back(0);
				}

			}
		}
		int rounds = 0;
		bool b = true;
		while (b) {
			round();
			b = false;
			for (int i = 0; i < 16; i++) {
				if (A[i] != 'a' + i) {
					b = true;
					break;
				}
			}
			rounds++;
		}

		cout << "repetition after " << rounds << " rounds: " << endl;

		for (int i = 0; i < 16; i++) {
			cout << A[i];
		}
		cout << endl;

		rounds = 1000000000 % rounds;
		for (int i = 0; i < rounds; i++) {
			round();
		}

		cout << "Final ordering is \n";
		for (int i = 0; i < 16; i++) {
			cout << A[i];
		}
		cout << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}