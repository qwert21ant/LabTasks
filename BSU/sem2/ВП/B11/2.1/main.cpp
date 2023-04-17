#include "header.h"

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	int n;
	fin >> n;

	int* arr = new int[10001];
	memset(arr, 0, sizeof(int) * 10001);

	for (int i = 0; i < n; i++) {
		int val;
		fin >> val;

		arr[val]++;
	}

	for (int i = 0; i < 10001; i++)
		if(arr[i] != 0)
			fout << i << " ";

	delete[] arr;
	fout.close();
	fin.close();

	return 0;
}