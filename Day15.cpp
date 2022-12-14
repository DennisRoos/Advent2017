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
	int count = 0;
	long long a = 703;
	long long b = 516;

	for (int i = 0; i < 40000000; i++) {
		a = (a * 16807) % 2147483647;
		b = (b * 48271) % 2147483647;
		int ra = a % 65536;
		int rb = b % 65536;
		if (ra == rb) {
			count++;
		}
	}
	cout << "Total matches for part 1 is " << count << endl;


	a = 703;
	b = 516;
	vector<long long> A;
	vector<long long> B;
	
	int c = 0;
	int ca = 0;

	while(c < 5000000){
		a = (a * 16807) % 2147483647;
		b = (b * 48271) % 2147483647;
		if (ca < 5000000 && a % 4 == 0) {
			A.push_back(a);
			ca++;
		}
		if (b % 8 == 0) {
			B.push_back(b);
			c++;
		}
	}

	int count2 = 0;

	for (int i = 0; i < B.size(); i++) {
		int ra = A[i] % 65536;
		int rb = B[i] % 65536;
		if (ra == rb) {
			count2++;
		}
	}
	cout << "Total matches for part 2 is " << count2 << endl;
}