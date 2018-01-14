#include <iostream>

using namespace std;

bool TrueOrFalse(int nums[9][9])
{
	int i, j, k, l;
	//hang
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 8; j++) {
			for (k = j + 1; k < 9; k++) {
				if (nums[i][k] == nums[i][j])
					return false;
			}
		}
	}
	//lie
	for (j = 0; j < 9; j++) {
		for (i = 0; i < 8; i++) {
			for (k = i + 1; k < 9; k++) {
				if (nums[i][j] == nums[k][j])
					return false;
			}
		}
	}
	//ge
	for (i = 0; i < 9; i += 3) {
		for (j = 0; j < 9; j += 3) {
			for (k = 0; k < 8; k++) {
				for (l = k + 1; l < 9; l++) {
					if (nums[i + k / 3][j + k % 3] == nums[i + l / 3][j + l % 3])
						return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	int nums[9][9];
	int shudu, num;
	int i, j;
	cin >> shudu;
	for (int shuduNum = 0; shuduNum < shudu; shuduNum++) {
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				cin >> num;
				nums[i][j] = num;
			}
		}
		if (TrueOrFalse(nums))
			cout << "Right" << endl;
		else
			cout << "Wrong" << endl;
	}
	return 0;
}