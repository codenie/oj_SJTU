#include <iostream>
#include <vector>
#include <algorithm>

using namespace  std;

struct Thing {
	int volume;
	int value;
	double radio;
	Thing(int volume, int value, double radio) :volume(volume), value(value), radio(radio) {};
};

bool operator<(const Thing &a, const Thing &b)
{
	return (a.radio > b.radio);
}

int main()
{
	int volume, num;
	cin >> volume >> num;
	vector<Thing> things;
	int i, vol, val;
	for (i = 0; i < num; i++) {
		cin >> vol >> val;
		things.emplace_back(vol, val, double(val) / vol);  // double ?
	}
	sort(things.begin(), things.end());
	int result = 0;
	for (Thing &thing : things) {
		if (volume >= thing.volume) {
			result += (volume / thing.volume * thing.value);
			volume = volume % thing.volume;
		}
	}
	cout << result;
	return 0;
}