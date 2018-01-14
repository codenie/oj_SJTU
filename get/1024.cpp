#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int i, n;
	cin >> n;
	vector<int> nums(n);
	for (i = 0; i < n; i++) {
		cin >> nums[i];
	}
	sort(nums.begin(), nums.end());
	for (int num : nums) {
		cout << num << " ";
	}
	return 0;
}