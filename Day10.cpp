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


int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		
		string s;
		getline(infile,s); 
		
		int l;
		int current = 0;
		int skipsize = 0;
		int A[256];
		for (int i = 0; i < 256; i++) {
			A[i] = i;
		}
		vector<int> lengths;
		for (int i = 0; i < s.size(); i++) {
			int j = s[i];
			lengths.push_back(j);
		}

		lengths.push_back(17);
		lengths.push_back(31);
		lengths.push_back(73);
		lengths.push_back(47);
		lengths.push_back(23);

		for (int round = 0; round < 64; round++) {
			for (int length = 0; length < lengths.size(); length++) {
				l = lengths[length];
				int i = current;
				int j = (current + l - 1) % 256;
				for (int k = 0; k < l / 2; k++) {
					int t = A[i];
					A[i] = A[j];
					A[j] = t;
					i = (i + 1) % 256;
					j--;
					if (j < 0) {
						j = 255;
					}
				}
				current = (current + l + skipsize) % 256;
				skipsize++;
			}
		}
		//we now have the sparse hash in A
		int D[16];
		int o = 0;
		for (int i = 0; i < 16; i++) {
			int d = A[o];
			for (int j = 1; j < 16; j++) {
				d = d ^ A[o + j];
			}
			D[i] = d;
			o += 16;
		}
		for (int i = 0; i < 16; i++) {
			std::stringstream stream;
			if (D[i] <= 15) {
				cout << '0';
			}
			stream <<  std::hex << D[i];
			cout << stream.str();
		}
		cout << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}