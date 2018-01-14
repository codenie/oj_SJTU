#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
IDEA: 一个数的质因数最多只有一个会大于这个数的开方。
一个数的质因数 num (num > 10)
num一定是 10 * n + 1 or 3 or 7 or 9 
*/


int main()
{
	int number, count = 0;
	cin >> number;
	cout << number << "=";
	int sqrtnum = sqrt(number);
	vector<int> base, index;
	int numsfir[4] = { 2, 3, 5, 7 };
	int numssec[4] = { 11, 13, 17, 19 };
	for (int num : numsfir) {
		if (num <= sqrtnum) {
			if (number % num == 0) {
				base.emplace_back(num);
				count = 1;
				number = number / num;
				while (number % num == 0) {
					number = number / num;
					count++;
				}
				index.emplace_back(count);
			}
		}
	}
	bool token = true;
	while (token) {
		for (int &num : numssec) {
			if (num > sqrtnum) {
				token = false;
				break;
			}
			if (number % num == 0) {
				base.emplace_back(num);
				count = 1;
				number = number / num;
				while (number % num == 0) {
					number = number / num;
					count++;
				}
				index.emplace_back(count);
			}
			num += 10;
		}
	}
	if (number != 1) {
		base.emplace_back(number);
		index.emplace_back(1);
	}

	for (int i = 0; i < base.size(); i++) {
		cout << base[i] << "(" << index[i] << ")";
	}
	return 0;
}