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

struct node {
	int d;
	node *next;
	node(int dd, node *n): d(dd), next(n) {}
};


int main(int argc, char * argv[])
{
	node *current = new node(0, NULL);
	current->next = current;
	node *zero = current;
	for (int i = 1; i <= 2017; i++) {
		for (int j = 0; j < 380; j++) {
			current = current->next;
		}
		node *n = new node(i, current->next);
		current->next = n;
		current = current->next;
	}

	cout << "the value for part 1 is " << current->next->d << endl;

	int data = 0;
	int size = 1;
	int c = 0;
	for (int i = 1; i < 50000000; i++) {
		c = (c + 380) % size;
		if (c == 0) {
			data = i;
			cout << "new answer: " << i << endl;
		}
		c++;
		size++;
	}



	cout << "the value for part 2 is " << data << endl;


	return 0;
}