#include <iostream>
#include <vector>
#include <algorithm>

using namespace  std;
typedef pair<int, int> PAIR;
int Volume;
vector<PAIR> things;

int package(int vol) // µÝ¹é £¡ 
{
	extern vector<PAIR> things;
	int max_money = 0;
	for (int i = 0; i < things.size(); i++) {
		if (vol >= things[i].first) {
			max_money = max(max_money, things[i].second + package(vol - things[i].first));
		}
		else {
			break;
		}
	}
	return max_money;
}

int main()
{
	extern int Volume;
	int num;
	cin >> Volume >> num;
	int i;
	int volume_sin, value_sin;
	extern vector<PAIR> things;
	for (i = 0; i < num; i++) {
		cin >> volume_sin >> value_sin;
		things.emplace_back(PAIR(volume_sin, value_sin));
	}
	sort(things.begin(), things.end());
	num = package(Volume);
	cout << num;

	return 0;
}