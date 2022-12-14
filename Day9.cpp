#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

string s;
int cur;
int total;
int cancelled;

void garbage(int score) {
	total += score;
	while (s[cur] != '}') {
		if (s[cur] == '!') {
			cur++;
		}
		else if (s[cur] == '{') {
			cur++;
			garbage(score + 1);
		}
		else if (s[cur] == '<') {//garbage starts
			cur++;
			while (s[cur] != '>') {
				if (s[cur] == '!') {
					cur++;
				}
				else {
					cancelled++;
				}
				cur++;
			}
		}
		cur++;
	}
	return;
}

int main(int argc, char * argv[])
{


	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		cur = 1;
		total = 0;
		cancelled = 0;
		infile >> s;
		garbage(1);
		cout << "The total score is " << total << endl;
		cout << "The amount of garbage is " << cancelled << endl;

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}