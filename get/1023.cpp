#include <iostream>

using namespace std;

int nums[600][600];

void print_hori(int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j >= 0; j--) {
			cout << nums[i][j] << " ";
		}
		cout << endl;
	}
}

void prin_verti(int size) {
	for (int i = size - 1; i >= 0; i--) {
		for (int j = 0; j < size; j++) {
			cout << nums[i][j] << " ";
		}
		cout << endl;
	}
}

void print_tilt(int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << nums[j][i] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int n, size, mode;
	cin >> n;
	for (int num = 0; num < n; num ++) {
		cin >> size >> mode;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cin >> nums[i][j];
			}
		}
		switch (mode) {
		case 0:
			print_hori(size);
			break;
		case 1:
			prin_verti(size);
			break;
		case 2:
			print_tilt(size);
			break;
		}
	}
	return 0;
}