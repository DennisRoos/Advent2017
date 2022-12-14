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

struct block {
	int A[16];
	block()  {}
};

vector<block> v;

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int t;
		block b;
		int i = 0;
		int A[16];
		while (infile >> t) {
			b.A[i] = t;
			A[i] = t;
			i++;
		}
		v.push_back(b);
		int rounds = 1;
		while (true) {
			//cout << "Round " << rounds << ": ";
			int highest = 0;
			int index;
			for (int i = 0; i < 16; i++) {
				if (A[i] > highest) {
					highest = A[i];
					index = i;
				}
			}
			A[index] = 0;
			for (int i = 0; i < highest; i++) {
				index = (index + 1) % 16;
				A[index]++;
			}

			for (int k = 0; k < v.size(); k++) {
				bool e = true;
				for (int i = 0; i < 16; i++) {
					if (A[i] != v[k].A[i]) {
						e = false;
						break;
					}
				}
				if (e) {
					cout << "Found a match after " << rounds << " rounds" << endl;
					cout << "It was " << rounds - k << " after the previous occurrence" << endl;
					return 0;
				}
			}

			block newblock = block();
			for (int i = 0; i < 16; i++) {
				newblock.A[i] = A[i];
				//cout << A[i] << " ";
			}
			rounds++;
			v.push_back(newblock);
			//cout << "... " << v.size() << endl;
		}
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}