#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
	stack<char> bracket;
	string str;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		while (!bracket.empty()) {
			bracket.pop();
		}
		cin >> str;
		for (char sinbra : str) {
			if (sinbra == '(')
				bracket.emplace('(');
			else {
				if (!bracket.empty() && bracket.top() == '(')
					bracket.pop();
				else
					bracket.emplace(')');
			}
		}
		if (bracket.empty())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}

