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

struct layer {
	int l;
	int r;
	int p;
	layer(int ll, int rr, int pp): l(ll),r(rr),p(pp) {}
};

vector<layer> v;

int trespass(int ps) {
	int severity = 0;
	for (int i = 0; i < v.size(); i++) {
		if ((ps + v[i].l) % v[i].p == 0) {
			return 1;
		}
	}
	return severity;
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int l;
		int p;
		int r;
		while (infile >> l) {
			infile >> r;
			p = 2 * (r - 1);
			layer ll = layer(l, r, p);
			v.push_back(ll);
		}

		cout << "The severity when leaving immediately is " << trespass(0) << endl;
		int ps = 1;
		while (true) {
			int sev = trespass(ps);
			if (sev == 0) {
				cout << "The first picosecond we can leave is " << ps << endl;
				return 0;
			}
			ps++;
		}
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}