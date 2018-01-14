#include <iostream>
#include <stack>
#include <map>
#include <string>

using namespace std;

int begin_minus_end = 0;

int check(int num, int pre)
{
	extern int begin_minus_end;
	switch (num) {
	case 0: 
		cout << "0" << endl;
		cout << pre << endl << endl;
		begin_minus_end++;
		return (pre != 2);
	case 1: 
		cout << "1" << endl;
		cout << pre << endl << endl;
		begin_minus_end--;
		if (begin_minus_end < 0)
			return 0;
		return 2;
	case 2: 
		cout << "2" << endl;
		cout << pre << endl << endl;
		return (pre == 0);
	case 3: 
		cout << "3" << endl;
		cout << pre << endl << endl;
		return (pre == 2);
	case 4: 
		cout << "4" << endl;
		cout << pre << endl << endl;
		return (pre == 3);
	}
}

int main()
{
	map<string, char> transform;
	transform["begin"] = 0;
	transform["end"] = 1;
	transform["if"] = 2;
	transform["then"] = 3;
	transform["else"] = 4;
	string str;
	stack<char> Pascal;
	int i, n;
	char num, pre = 0, checkResult;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> str;
		num = transform[str];
		checkResult = check(num, pre);
		if (!checkResult) {
			cout << "NO";
			return 0;
		}
		if (checkResult == 1) {
			Pascal.emplace(num);
			pre = num;
			continue;
		}
		if (checkResult == 2) {
			while (Pascal.top() != 0)
				Pascal.pop();
			Pascal.pop();
			if (!Pascal.empty())
				pre = Pascal.top();
			else
				pre = 0;
		}
	}
	cout << "YES";
	return 0;
}