#include <iostream>
#include <string>

using namespace std;

string c;

void multiply(string &a, string &b)
{
	extern string c;
	int carry = 0;
	int lenb = b.size();
	int lena = a.size();
	int length = lena + lenb; // +1
	int right, left;
	int result = 0;
	for (int index = 0; index < length; index++) {
		result = 0;
		left = (index + 1 > lena) ? (index + 1 - lena) : 0;
		right = (lenb < index + 1) ? lenb : (index + 1);
		for (int i = left; i < right; i++) {
			result += (b[i] - '0') * (a[index - i] - '0');
		}
		result += carry;
		carry = result / 10;
		result -= carry * 10;
		c.push_back(char('0' + result));
	}
	if (result == 0)
		c.pop_back();
	if (carry) {
		c.push_back(char('0' + carry));
	}
}

int main()
{
	extern string c;
	string a, b;
	cin >> a >> b;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if (a.size() >= b.size()) {
		multiply(a, b);
	}
	else {
		multiply(b, a);
	}
	reverse(c.begin(), c.end());
	cout << c << endl;

	return 0;
}