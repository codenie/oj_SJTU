#include <iostream>

using namespace std;

int main()
{
	int n, num;
	int result, minsum = 0, tmp, cursum = 0;
	cin >> n;

	for (int i = 0; i < 2; i++) {
		cin >> num;
		cursum += num;
	}
	result = cursum;
	tmp = num;
	for (int i = 2; i < n; i++) {
		cin >> num;
		minsum = (minsum < cursum - tmp) ? minsum : (cursum - tmp);
		cursum += num;
		tmp = num;
		result = (result > cursum - minsum) ? result : (cursum - minsum);
	}

	if (result > 0)
		cout << result;
	else
		cout << "Game Over";
	return 0;
}