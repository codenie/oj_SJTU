#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int nums[150][150];
	int length = n - 1, number = 1;
	int startx = 0, starty = 0;
	int maxnum;
	while (length >= 0) {
		maxnum = number + length;
		for (; number < maxnum;) {
			nums[startx][starty++] = number++;
		}
		maxnum = number + length;
		for (; number < maxnum;) {
			nums[startx++][starty] = number++;
		}
		maxnum = number + length;
		for (; number < maxnum;) {
			nums[startx][starty--] = number++;
		}
		maxnum = number + length;
		for (; number < maxnum;) {
			nums[startx--][starty] = number++;
		}
		startx++;
		starty++;
		length -= 2;
	}

	if (n % 2) {
		nums[n / 2][n / 2] = number;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(8) << nums[i][j];
		}
		cout << endl;
	}
	return 0;
}