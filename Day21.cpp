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

int TwoThree[512];
int ThreeFour[140000];

int value2(int A[]) {
	int t = 0;
	int mult = 1;
	for (int i = 0; i < 4; i++) {
		if (A[i] == 1) {
			t += mult;
		}
		mult = mult * 2;
	}
	return t;
}


int value3(int A[]) {
	int t = 0;
	int mult = 1;
	for (int i = 0; i < 9; i++) {
		if (A[i] == 1) {
			t += mult;
		}
		mult = mult * 2;
	}
	return t;
}


void rotate2(int A[]) {
	int t = A[0];
	A[0] = A[2];
	A[2] = A[3];
	A[3] = A[1];
	A[1] = t;
	return;
}


void rotate3(int A[]) {
	int t = A[0];
	A[0] = A[6];
	A[6] = A[8];
	A[8] = A[2];
	A[2] = t;
	t = A[1];
	A[1] = A[3];
	A[3] = A[7];
	A[7] = A[5];
	A[5] = t;
	return;
}


void mirror2(int A[]) {
	int t = A[0];
	A[0] = A[2];
	A[2] = t;
	t = A[3];
	A[3] = A[1];
	A[1] = t;
	return;
}

void mirror3(int A[]) {
	int t = A[0];
	A[0] = A[6];
	A[6] = t;
	t = A[1];
	A[1] = A[7];
	A[7] = t;
	t = A[2];
	A[2] = A[8];
	A[8] = t;
	return;
}


static char A[1536][1536];
static char B[1536][1536];

int main(int argc, char * argv[]) {
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string source;
		string target;
		string temp;
		cout << "A" << endl;
		for (int iii = 0; iii < 6; iii++) {
			infile >> source;
			infile >> temp;
			infile >> target;
			int t = 0;
			int mult = 1;
			for (int i = 0; i < 3; i++) {
				int k = 4 * i;
				for (int j = 0; j < 3; j++) {
					if (target[k] == '#') {
						t += mult;
					}
					mult = mult * 2;
					k++;
				}
			}
			int A[4];
			for (int i = 0; i < 4; i++) {
				A[i] = 0;
			}
			if (source[0] == '#') {
				A[0] = 1;
			}
			if (source[1] == '#') {
				A[1] = 1;
			}
			if (source[3] == '#') {
				A[2] = 1;
			}
			if (source[4] == '#') {
				A[3] = 1;
			}
			TwoThree[value2(A)] = t;
			for (int i = 0; i < 3; i++) {
				rotate2(A);
				TwoThree[value2(A)] = t;
			}
			mirror2(A);
			TwoThree[value2(A)] = t;
			for (int i = 0; i < 3; i++) {
				rotate2(A);
				TwoThree[value2(A)] = t;
			}
		}

		cout << "B" << endl;
		//now the 3->4 maps
		while (infile >> source) {
			infile >> temp;
			infile >> target;

			int t = 0;
			int mult = 1;
			for (int i = 0; i < 4; i++) {
				int k = 5 * i;
				for (int j = 0; j < 4; j++) {
					if (target[k] == '#') {
						t += mult;
					}
					mult = mult * 2;
					k++;
				}
			}
			int A[9];
			for (int i = 0; i < 3; i++) {
				int k = 4 * i;
				for (int j = 0; j < 3; j++) {
					if (source[k] == '#') {
						A[3 * i + j] = 1;
					}
					else {
						A[3 * i + j] = 0;
					}
					k++;
				}
			}
			ThreeFour[value3(A)] = t;
			for (int i = 0; i < 3; i++) {
				rotate3(A);
				ThreeFour[value3(A)] = t;
			}
			mirror3(A);
			ThreeFour[value3(A)] = t;
			for (int i = 0; i < 3; i++) {
				rotate3(A);
				ThreeFour[value3(A)] = t;
			}
		}
	}
	cout << "Test" << endl;
	int size = 3;
	A[0][0] = 0;
	A[1][0] = 1;
	A[2][0] = 0;
	A[0][1] = 0;
	A[2][1] = 1;
	A[1][1] = 0;
	A[0][2] = 1;
	A[1][2] = 1;
	A[2][2] = 1;
	for(int iterations = 1; iterations <= 18; iterations++){
		int total = 0;
		cout << "starting iteration " << iterations << endl;
		if (size % 2 == 0) {//evenly divisible by 2!
			int s = size / 2;
			for (int i = 0; i < s; i++) {
				for (int j = 0; j < s; j++) {
					int t = 0;
					int mult = 1;
					if (A[2 * i][2 * j] == 1) {
						t += mult;
					}
					mult = mult * 2;
					if (A[(2 * i) + 1][2 * j] == 1) {
						t += mult;
					}
					mult = mult * 2;
					if (A[(2 * i)][(2 * j) + 1] == 1) {
						t += mult;
					}
					mult = mult * 2;
					if (A[(2 * i) + 1][(2 * j) + 1] == 1) {
						t += mult;
					}
					mult = mult * 2;
					int target = TwoThree[t];
					//now paint target into B

					for (int x = 0; x < 3; x++) {
						for (int y = 0; y < 3; y++) {
							if (target % 2 == 0) {
								B[3 * i + y][3 * j + x] = 0;
							}
							else {
								B[3 * i + y][3 * j + x] = 1;
								total++;
							}
							target = target / 2;
						}
					}
				}
			}
			size = size + (size / 2);
			std::cout << "After " << iterations << " with " << total << " ones the pattern looks like: \n";
			for (int j = 0; j < size; j++) {
				for (int i = 0; i < size; i++) {
					A[i][j] = B[i][j];
					//std::cout << A[i][j];
				}
				//cout << endl;
			}
		}
		else {//evenly divisible by 3
			int s = size / 3;
			for (int i = 0; i < s; i++) {
				for (int j = 0; j < s; j++) {
					int t = 0;
					int mult = 1;
					for (int x = 0; x < 3; x++) {
						for (int y = 0; y < 3; y++) {
							if (A[3 * i + y][3 * j + x] == 1) {
								t += mult;
							}
							mult = mult * 2;
						}
					}
					
					int target = ThreeFour[t];
					//now paint target into B

					for (int x = 0; x < 4; x++) {
						for (int y = 0; y < 4; y++) {
							if (target % 2 == 0) {
								B[4 * i + y][4 * j + x] = 0;
							}
							else {
								B[4 * i + y][4 * j + x] = 1;
								total++;
							}
							target = target / 2;
						}
					}
				}
			}
			size = size + (size / 3);
			std::cout << "After " << iterations << " with " << total << " ones the pattern looks like: \n";
			for (int j = 0; j < size; j++) {
				for (int i = 0; i < size; i++) {
					A[i][j] = B[i][j];
					//std::cout << A[i][j];
				}
				//cout << endl;
			}

		}




	}
	return 0;
}