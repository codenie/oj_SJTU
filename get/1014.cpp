#include <iostream>
#include <string>

using namespace std;

void addnum(string &a, string &b)
{
	// a is the final result
	char carry = 0, num;
	int i, lengtha = a.size(), lengthb = b.size();
	for (i = 1; i <= lengthb; i++) {
		num = a[lengtha - i] + b[lengthb - i] - '0' + carry;
		if (num > '9') {
			a[lengtha - i] = num - 10;
			carry = 1;
		}
		else {
			carry = 0;
			a[lengtha - i] = num;
		}
	}
	if (carry) {
		for (; i <= lengtha; i++) {
			if(a[lengtha - i] == '9')
				a[lengtha - i] = '0';
			else {
				a[lengtha - i]++;
				break;
			}
		}
		if(i == lengtha + 1)
			a = '1' + a;
	}
	else
		return;
}

int main()
{
	string num1, num2;
	cin >> num1 >> num2;
	if (num1.size() > num2.size()) {
		addnum(num1, num2);
		cout << num1;
	}
	else {
		addnum(num2, num1);
		cout << num2;
	}
	return 0;
}