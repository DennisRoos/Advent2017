#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <list>

using namespace std;

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		int A[16][16];
		int checksum = 0;
		int t;
		int j = 0;
		while(infile >> t){
			int min = t;
			int max = t;
			A[0][j] = t;
			for (int i = 1; i < 16; i++) {
				infile >> t;
				A[i][j] = t;
				if (t < min) {
					min = t;
				}
				if (t > max) {
					max = t;
				}
			}
			j++;
			checksum += max - min;
		}
		cout << "The checksum is " << checksum << endl;
		int checksum2 = 0;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				for (int k = 0; k < 16; k++) {
					if (j != k && A[j][i] % A[k][i] == 0) {
						checksum2 += A[j][i] / A[k][i];
					}
				}
			}
		}

		cout << "The result is " << checksum2 << endl;
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}