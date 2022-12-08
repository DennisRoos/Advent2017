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
		int count = 0;
		string s2;
		vector<string> v;
		while (getline(infile,s)) {
			stringstream ss(s);
			v.clear();
			bool b = true;
			while (ss >> s2) {
				sort(s2.begin(), s2.end());
				for (int i = 0; i < v.size(); i++) {
					if (s2.compare(v[i]) == 0) {
						b = false;
					}
				}
				if (b) {
					v.push_back(s2);
				}
				else {
					break;
				}
			}
			if (b) {
				count++;
			}



		}

		cout << "Total count is " << count << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}