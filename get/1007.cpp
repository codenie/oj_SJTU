#include <iostream>
#include <string>

using namespace std;

int get(string &num, int i, int length)
{
	if (i <= length)
		return num[length - i] - 48;
	else
		return 0;
}

int main()
{
	string num1, num2;
	string result;
	int i, sum, re, carry = 0;
	cin >> num1 >> num2;
	int len1 = num1.size();
	int len2 = num2.size();
	int maxlen = (len1 > len2) ? len1 : len2;
	for (i = 1; i <= 2; i++) {
		sum = get(num1, i, len1) + get(num2, i, len2) + carry;
		carry = sum / 10;
		re = sum % 10;
		result = char(re + '0') + result;
	}
	result = '.' + result;
	for (i = 4; i <= maxlen; i++) {
		sum = get(num1, i, len1) + get(num2, i, len2) + carry;
		carry = sum / 10;
		re = sum % 10;
		result = char(re + '0') + result;
	}
	if (carry)
		result = '1' + result;
	cout << result << endl;
	return 0;
}