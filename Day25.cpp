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

struct node {
	int data;
	node *left;
	node *right;

	node(node *l, node *r): left(l),right(r), data(0) {}
};

int W[6][2];
int S[6][2];
char D[6][2];


int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		int i;
		char c;
		char d;
		for (int s = 0; s < 6; s++) {
			for (int r = 0; r < 2; r++) {
				infile >> i;
				infile >> d;
				infile >> c;
				W[s][r] = i;
				D[s][r] = d;
				int state = c - 'A';
				S[s][r] = state;
			}
		}
		int state = 0;
		int cur;
		node *current = new node(NULL, NULL);
		for (int i = 0; i < 12317297; i++) {
			cur = current->data;
			current->data = W[state][cur];
			if (D[state][cur] == 'r') {
				if (current->right == NULL) {
					node *n = new node(current, NULL);
					current->right = n;
					current = n;
				}
				else {
					current = current->right;
				}
			}
			else {
				if (current->left == NULL) {
					node *n = new node(NULL,current);
					current->left = n;
					current = n;
				}
				else {
					current = current->left;
				}
			}
			state = S[state][cur];

		}

		int ones = current->data;
		int total = 1;
		node *search = current->right;
		while (search != NULL) {
			ones += search->data;
			total++;
			search = search->right;
		}
		search = current->left;
		while (search != NULL) {
			ones += search->data;
			total++;
			search = search->left;
		}

		cout << "There are " << ones << " 1s on the tape. The tape is " << total << " big" << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}