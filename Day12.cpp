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

struct prog {
	vector<int> v;
	prog() {}
};

prog A[2000];
int visited[2000];
int total;
int cur;
bool b;

void visit(int index) {
	if (visited[index] != -1) {
		return;
	}
	visited[index] = cur;
	b = true;
	if (cur == 0) {
		total++;
	}
	for (int i = 0; i < A[index].v.size(); i++) {
		visit(A[index].v[i]);
	}
	return;
}

int main(int argc, char * argv[])
{
	for (int i = 0; i < 2000; i++) {
		visited[i] = -1;
	}
	total = 0;
	ifstream infile;
	infile.open("data.txt");
	string s;
	if (infile.is_open())
	{
		while (getline(infile, s)) {
			stringstream ss(s);
			int id;
			string t;
			ss >> id;
			ss >> t;

			int child;
			while (ss >> child) {
				A[id].v.push_back(child);
			}
		}
		int total2 = 0;

		for (int i = 0; i < 2000; i++) {
			b = false;
			cur = i;
			visit(i);
			if (b) {
				total2++;
			}
		}
		cout << "There are " << total << " programs in group 0" << endl;
		cout << "There are " << total2 << " groups" << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}