#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector<int> Pascal;
int posi_begin, posi_end;

int find()
{
	extern int posi_begin, posi_end;
	for (; posi_begin >= 0 && Pascal[posi_begin] != 4; posi_begin--);
	for (posi_end = posi_begin + 1; (posi_end < Pascal.size()) && (Pascal[posi_end] != 5); posi_end++);
	if ((posi_begin == -1) != (posi_end == Pascal.size()))
		return 2;
	else
		return (posi_begin == -1);
}

bool check()
{
	extern int posi_begin, posi_end;
	int length = posi_end - posi_begin - 1;
	if (!length)
		return true;
	if (length > 5 || length < 2)
		return false;
	int i;
	string str;
	for (i = posi_begin + 1; i < posi_end; i++)
		str += char(Pascal[i] + '0');
	switch (length) {
	case 2:
		return (str == "12");
	case 3:
		return (str == "126" || str == "123");
	case 4:
		return (str == "1263" || str == "1236");
	case 5:
		return (str == "12636");
	}
}

int main()
{
	int i, n;
	string str;
	extern int posi_begin, posi_end;
	map<string, int> transform;
	transform["if"] = 1;
	transform["then"] = 2;
	transform["else"] = 3;
	transform["begin"] = 4;
	transform["end"] = 5;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> str;
		Pascal.push_back(transform[str]);
	}
	if (str == "begin"){
		cout << "NO";
		return 0;
	}
	posi_begin = Pascal.size() - 1;
	while (true) {
		n = find();
		if (n == 2) {
			cout << "NO";
			return 0;
		}
		if (n == 1)
			break;
		if (!check()) {
			cout << "NO";
			return 0;
		}
		*Pascal.erase(Pascal.begin() + posi_begin, Pascal.begin() + posi_end) = 6;
	}
	if (check())
		cout << "YES";
	else
		cout << "NO";
	return 0;
}