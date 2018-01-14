#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int, int> PAIR;

int main()
{
	int n;
	cin >> n;
	vector<PAIR> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i].first >> nums[i].second;
	}
	sort(nums.begin(), nums.end());
	int length = 0;
	int start = -2000000000, end = -2000000000;
	for (int i = 0; i < n; i++) {
		if (nums[i].first <= end) {
			end = max(end, nums[i].second);
		}
		else {
			length += (end - start);
			start = nums[i].first;
			end = nums[i].second;
		}
	}
	length += (end - start);
	cout << length << endl;
	return 0;
}