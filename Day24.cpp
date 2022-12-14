#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>  
#include <limits>


using namespace std;

struct component {
	int p1;
	int p2;
	bool u;
	component(int q1, int q2): p1(q1), p2(q2), u(false){}
};

vector<component> v;

int bestStrength;
int bestLength;

void build(int port, int strength, int length) {
	int s = v.size();
	if (length >= bestLength && strength > bestStrength){
		bestLength = length;
		bestStrength = strength;
	}
	for (int i = 0; i < s; i++) {
		if (v[i].p1 == port && v[i].u == false) {
			v[i].u = true;
			build(v[i].p2, strength + v[i].p2 + port, length + 1);
			v[i].u = false;
		}
	}
	for (int i = 0; i < s; i++) {
		if (v[i].p2 == port && v[i].u == false && v[i].p1 != port) {
			v[i].u = true;
			build(v[i].p1, strength + v[i].p1 + port, length + 1);
			v[i].u = false;
		}
	}
}


int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	bestStrength = 0;
	bestLength = 0;

	if (infile.is_open())
	{
		int p1;
		int p2;
		while (infile >> p1) {
			infile >> p2;
			component c = component(p1, p2);
			v.push_back(c);
		}

		build(0, 0, 0);
		cout << "Best bridge has length " << bestLength << " and strength " << bestStrength << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}