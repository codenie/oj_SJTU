#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
	int time, T, U, F, D;
	unordered_map<char, int> roadtime;
	cin >> time >> T >> U >> F >> D;  // cin
	roadtime['u'] = U + D;
	roadtime['f'] = F + F;
	roadtime['d'] = U + D;
	char ch;
	int i;
	for (i = 0; i < T; i++) {
		cin >> ch;
		time -= roadtime[ch];
		if (time < 0)
			break;
	}
	cout << i;
	return 0;
}