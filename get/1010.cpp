#include <iostream>

using namespace std;

int main()
{
	int erge = 0, mother = 0, deposit = 0;
	int budget;
	for (int i = 1; i <= 12; i++)
	{
		cin >> budget;
		erge += 300;
		if (erge < budget) {
			cout << i * (-1);
			return 0;
		}
		mother = (erge - budget) / 100 * 100;
		erge = erge - mother - budget;
		deposit += mother;
	}
	cout << (erge + deposit * 1.2);
	return 0;
}