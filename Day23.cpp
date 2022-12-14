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
#include <queue>          // std::queue

using namespace std;

void sendMessage(int data, int id);

int counter;
int mulcount;

struct reg {
	string name;
	long long value;
	reg(string n) : name(n), value(0) {};
};

vector<string> ops;
vector<string> a;
vector<string> b;

class duet {
public:
	int ip;
	vector<reg> v;
	queue<long long> m;
	int id;
	duet() {

	}

	void initialize(int idd);
	int run();
	int findReg(string n);
	long long Value(string n);
};

void duet::initialize(int idd) {
	reg r = reg("p");
	r.value = idd;
	id = idd;
	v.push_back(r);
	reg r2 = reg("1");
	r2.value = 1;
	v.push_back(r2);
	reg r3 = reg("a");
	r3.value = 1;
	v.push_back(r3);
	ip = 0;
}

int duet::findReg(string n) {
	for (int i = 0; i < v.size(); i++) {
		if (n.compare(v[i].name) == 0) {
			return i;
		}
	}
	reg p = reg(n);
	v.push_back(p);
	return v.size() - 1;
}

long long duet::Value(string n) {
	if (n[0] >= 'a' && n[0] <= 'z') {
		return v[findReg(n)].value;
	}
	else return stoi(n);
}

int duet::run() {
	while (ip >= 0 && ip < ops.size()) {
		long long bb = Value(b[ip]);
		string s = ops[ip];
		if (s.compare("set") == 0) {
			v[findReg(a[ip])].value = bb;
			ip++;
		}
		else if (s.compare("sub") == 0) {
			v[findReg(a[ip])].value -= bb;
			ip++;
		}
		else if (s.compare("mul") == 0) {
			v[findReg(a[ip])].value *= bb;
			ip++;
			//mulcount++;
		}
		else if (s.compare("jnz") == 0) {
			if (v[findReg(a[ip])].value != 0) {
				ip += bb;
			}
			else {
				ip++;
			}
		}
		else {
			cout << "unrecognized command? " << s << endl;
		}
	}
	return 2; //out of program bounds
}

duet sys;

bool Prime(int n) {
	for (int i = 2; i <= n / 2; ++i)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char * argv[])
{
	/*counter = 0;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string op;
		string o1;
		string o2;
		while (infile >> op) {
			infile >> o1;
			ops.push_back(op);
			a.push_back(o1);
			infile >> o2;
			b.push_back(o2);
		}
		mulcount = 0;
		duet *d = new duet();
		d->initialize(0);
		d->run();
		
		cout << "There were " << mulcount << " multiplications\n";

	}
	else {
		cout << "can't find file?\n";
	}*/

	int h = 0;
	for (int b = 108100; b <= 125100; b = b + 17) {
		if (Prime(b) == false) {
			h++;
		}
	}
	cout << "final value is " << h << endl;

	return 0;
}