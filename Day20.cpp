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

struct coordinate {
	long long x;
	long long y;
	long long z;

	coordinate(int xx, int yy, int zz) : x(xx),y(yy),z(zz){}
};

struct particle {
	coordinate p;
	coordinate v;
	coordinate a;
	bool b;
	particle(coordinate pp, coordinate vv, coordinate aa) : p(pp), v(vv), a(aa), b(true){}
};

vector<particle> parts;

int main(int argc, char * argv[]) {

	regex re("p=<(-?[\\d]+),(-?[\\d]+),(-?[\\d]+)>, v=<(-?[\\d]+),(-?[\\d]+),(-?[\\d]+)>, a=<(-?[\\d]+),(-?[\\d]+),(-?[\\d]+)>");
	string s;
	smatch match;
	ifstream f("data.txt");
	while (getline(f, s)) {
		if (regex_search(s, match, re) == true) {
			int x;
			int y;
			int z;

			x = stoi(match.str(1));
			y = stoi(match.str(2));
			z = stoi(match.str(3));
			coordinate p = coordinate(x, y, z);
			x = stoi(match.str(4));
			y = stoi(match.str(5));
			z = stoi(match.str(6));
			coordinate v = coordinate(x, y, z);
			x = stoi(match.str(7));
			y = stoi(match.str(8));
			z = stoi(match.str(9));
			coordinate a = coordinate(x, y, z);
			particle par = particle(p, v, a);
			parts.push_back(par);
		}
	}

	long long smallest = 999999999999;
	int bestPar;

	for (int k = 0; k < 1000; k++) {
		for (int i = 0; i < parts.size(); i++) {
			if (parts[i].b) {
				parts[i].v.x += parts[i].a.x;
				parts[i].v.y += parts[i].a.y;
				parts[i].v.z += parts[i].a.z;

				parts[i].p.x += parts[i].v.x;
				parts[i].p.y += parts[i].v.y;
				parts[i].p.z += parts[i].v.z;
			}
		}
		for (int i = 0; i < parts.size(); i++) {
			if (parts[i].b) {
				for (int j = i+1; j < parts.size(); j++) {
					if (parts[j].b) {
						if (parts[i].p.x == parts[j].p.x && parts[i].p.y == parts[j].p.y && parts[i].p.z == parts[j].p.z) {//collision
							parts[i].b = false;
							parts[j].b = false;
						}
					}
				}
			}
		}
	}

	int count = 0;


	for (int i = 0; i < parts.size(); i++) {
		particle par = parts[i];
		long long sum = abs(par.p.x) + abs(par.p.y) + abs(par.p.z);
		if (sum < smallest) {
			smallest = sum;
			bestPar = i;
		}
		if (par.b) {
			count++;
		}
	}

	cout << "Closest particle is " << bestPar << endl;

	cout << "Amount of particles left is " << count << endl;
	return 0;
}