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

struct prog{
	string name;
	int weight;
	int parent;
	vector<int> children;

	prog(string n): name(n), parent(-1) {};
};

vector<prog> v;

int findProg(string n) {
	for (int i = 0; i < v.size(); i++) {
		if (n.compare(v[i].name) == 0) {
			return i;
		}
	}
	prog p = prog(n);
	v.push_back(p);
	return v.size() - 1;
}

int towerWeight(int index) {
	prog p = v[index];
	int s = p.children.size();
	if (s == 0){
		return p.weight;
	}
	else {
		int W[10];
		int total = p.weight;
		for (int i = 0; i < s; i++) {
			W[i] = towerWeight(p.children[i]);
			total += W[i];
		}
		int w = W[0];
		if (W[1] != w) {
			if (W[2] == w) {
				cout << "The program with the wrong weight is " << v[p.children[1]].name << " with current weight " << v[p.children[1]].weight << " , towerweight " << W[1] << " which should be " << W[0] << endl;
				exit(0);
			}
			else {
				cout << "The program with the wrong weight is " << v[p.children[0]].name << " with current weight " << v[p.children[0]].weight << " , towerweight " << W[0] << " which should be " << W[1] << endl;
				exit(0);
			}
		}
		for (int i = 2; i < s; i++) {
			if (W[i] != w) {
				cout << "The program with the wrong weight is " << v[p.children[i]].name << " with current weight " << v[p.children[i]].weight << " , towerweight " << W[i] << " which should be " << w << endl;
				exit(0);
			}
		}
		return total;
	}
}


int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int count = 0;
		string s2;
		while (getline(infile, s)) {
			stringstream ss(s);
			bool b = true;
			string name;
			int weight;
			ss >> name;
			ss >> weight;

			int index = findProg(name);
			v[index].weight = weight;

			string temp;
			ss >> temp;
			while (ss >> s2) {
				int i = findProg(s2);
				v[i].parent = index;
				v[index].children.push_back(i);
			}
		}

		int cur = 0;
		while (v[cur].parent != -1) {
			cur = v[cur].parent;
		}
		cout << "The root is " << v[cur].name << endl;

		towerWeight(cur);

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}