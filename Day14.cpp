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

string knothash(string s) {
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
	string result = "";
	for (int i = 0; i < 16; i++) {
		std::stringstream stream;
		if (D[i] <= 15) {
			result.append("0");
		}
		char t[20];
		_itoa_s(D[i], t, 16);
		result.append(t);
	}
	return result;
}

int A[128][128];

string hex_char_to_bin(char c)
{
	// TODO handle default / error
	switch (toupper(c))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	}
}

int regions;


void traverse(int x, int y) {
	if (x < 0 || x > 127 || y < 0 || y > 127) {
		return;
	}
	if (A[x][y] != 1) {
		return;
	}
	A[x][y] = 2;
	traverse(x - 1, y);
	traverse(x + 1, y);
	traverse(x, y - 1);
	traverse(x, y + 1);

}

int main(int argc, char * argv[])
{
	string base = "amgozmfv";
	base.append("-");
	
	int total = 0;
	for (int i = 0; i < 128; i++) {
		char count[20];
		_itoa_s(i, count, 10);
		string s;
		s.assign(base);
		s.append(count);
		string hash = knothash(s);
		string bin;
		for (int j = 0; j < 32; j++) {
			bin.append(hex_char_to_bin(hash[j]));
		}
		for (int j = 0; j < 128; j++) {
			int b = bin[j] - '0';
			A[i][j] = b;
			total += b;
		}
	}
	cout << "Total ones are " << total << endl;
	regions = 0;
	for (int x = 0; x < 128; x++) {
		for (int y = 0; y < 128; y++) {
			if (A[x][y] == 1) {
				regions++;
				traverse(x, y);
			}
		}
	}
	cout << "Number of regions is " << regions << endl;
	return 0;
}