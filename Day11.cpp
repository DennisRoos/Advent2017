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
		int furthest = 0;
		int x = 0;
		int y = 0;
		int z = 0;
		string s;
		while (infile >> s) {
			if (s.compare("n") == 0) {
				x--;
				y++;
			}
			else if (s.compare("s") == 0) {
				x++;
				y--;
			}
			else if (s.compare("ne") == 0) {
				y++;
				z--;
			}
			else if (s.compare("se") == 0) {
				x++;
				z--;
			}
			else if (s.compare("nw") == 0) {
				z++;
				x--;
			}
			else if (s.compare("sw") == 0) {
				y--;
				z++;
			}
			int dist = (abs(x) + abs(y) + abs(z)) / 2;
			if (dist > furthest) {
				furthest = dist;
			}
		}
		cout << "Target is at " << x << "," << y << "," << z << endl;
		int distance = (abs(x) + abs(y) + abs(z)) / 2;
		cout << "distance to child is " << distance << endl;
		cout << "Furthest distance is " << furthest << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}