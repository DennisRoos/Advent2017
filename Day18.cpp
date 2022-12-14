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
	duet(){

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
	bool sent = false;
	while (ip >= 0 && ip < ops.size()) {
		long long bb = Value(b[ip]);
		string s = ops[ip];
		if (s.compare("set") == 0) {
			v[findReg(a[ip])].value = bb;
			ip++;
		}
		else if (s.compare("add") == 0) {
			v[findReg(a[ip])].value += bb;
			ip++;
		}
		else if (s.compare("mul") == 0) {
			v[findReg(a[ip])].value *= bb;
			ip++;
		}
		else if (s.compare("mod") == 0) {
			v[findReg(a[ip])].value = v[findReg(a[ip])].value % bb;
			ip++;
		}
		else if (s.compare("jgz") == 0) {
			if (v[findReg(a[ip])].value > 0) {
				ip += bb;
			}
			else {
				ip++;
			}
		}
		else if (s.compare("snd") == 0) {
			if (id == 1) {
				counter++;
			}
			sendMessage(v[findReg(a[ip])].value, id);
			sent = true;
			ip++;
		}
		else if (s.compare("rcv") == 0) {
			if (m.empty()) {
				if (sent) {
					return 0;
				}
				else {
					return 1;
				}
			}
			else {
				v[findReg(a[ip])].value = m.front();
				m.pop();
			}
			ip++;
		}
		else {
			cout << "unrecognized command? " << s << endl;
		}
	}
	return 2; //out of program bounds
}

duet sys[2];

void sendMessage(int data, int id) {
	if (id == 0) {
		sys[1].m.push(data);
	}
	else {
		sys[0].m.push(data);
	}
	return;
}

int main(int argc, char * argv[])
{
	counter = 0;
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
			if (op.compare("snd") == 0 || op.compare("rcv") == 0) {
				b.push_back("0");
			}
			else {
				infile >> o2;
				b.push_back(o2);
			}
		}

		sys[0].initialize(0);
		sys[1].initialize(1);
		bool going = true;

		while (going) {
			int r1 = sys[0].run();
			int r2 = sys[1].run();
			if (r1 > 0 && r2 > 0) {
				going = false;
			}
		}

		cout << "program 1 sent " << counter << " messages" << endl;
		
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}