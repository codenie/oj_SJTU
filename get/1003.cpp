#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int L;
	cin >> L;
	int zero = 0, i, j, num, generation = 0;
	vector<vector<int>> bacteria(L, vector<int>(L, 0));
	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			cin >> num;
			if (num == 2)
				bacteria[i][j] = -1;
			else if (num == 1)
				bacteria[i][j] = 1;
			else {
				zero++;
				bacteria[i][j] = 0;
			}
		}
	}
	num = 0;
	while (zero) {
		generation++;
		num++;
		for (i = 0; i < L; i++) {
			for (j = 0; j < L; j++) {
				if (bacteria[i][j] == num) {
					if (i != 0 && !bacteria[i - 1][j]) {
						bacteria[i - 1][j] = num + 1;
						zero--;
					}
					if (i != L - 1 && !bacteria[i + 1][j]) {
						bacteria[i + 1][j] = num + 1;
						zero--;
					}
					if (j != 0 && !bacteria[i][j - 1]) {
						bacteria[i][j - 1] = num + 1;
						zero--;
					}
					if (j != L - 1 && !bacteria[i][j + 1]) {
						bacteria[i][j + 1] = num + 1;
						zero--;
					}
				}
			}
		}
	}
	cout << generation;
	return 0;
}