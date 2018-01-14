#include <iostream>
#include <stack>
#include <string>

using namespace std;

int getpreviledge(char ch)
{
	switch (ch) {
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	case '(': return 0;
	}
}

long long pow_me(long long a, long long b) {
	long long r = 1, base = a;
	while (b) {
		if (b & 1) r *= base;
		base *= base;
		b >>= 1;
	}
	return r;
}


long long compute(char ch, long long a, long long b)
{
	switch (ch) {
	case '+': return (a + b);
	case '-': return (a - b);
	case '*': return (a * b);
	case '/': return (a / b);
	case '^': return pow_me(a, b);
	}
}

int main()
{
	stack<long long > nums;
	stack<char> operators;
	string str;
	int count = 0;
	getline(cin, str);
	int i;
	long long b, a;
	char ch;
	for (i = 0; i < str.size();) {
		switch (str[i]) {
		case '(':
			count++; i++;
			break;
		case ')':
			if (!count) {
				cout << "Error" << endl;
				return 0;
			}
			count--; i++;
			break;
		case ' ':
			str.erase(str.begin() + i);
			break;
		default:
			i++;
			break;
		};
	}
	//cout << str << endl;

	for (i = 0; i < str.size(); i++) {
		switch (str[i]) {
		case '*':
		case '/':
			if (operators.empty() || getpreviledge(operators.top()) < getpreviledge(str[i])) {
				operators.push(str[i]);
			}
			else {
				while (!operators.empty() && getpreviledge(operators.top()) >= getpreviledge(str[i])) {
					b = nums.top();
					if (operators.top() == '/' && b == 0) {
						cout << "Error" << endl;
						return 0;
					}
					nums.pop();
					a = nums.top();
					nums.pop();
					nums.push(compute(operators.top(), a, b));
					operators.pop();
				}
				operators.push(str[i]);
			}
			break;
		case '-':
			if (!i || (str[i - 1] != ')' && !isdigit(str[i - 1]))) {
				a = i + 1;
				for (i = a + 1; i < str.size() && isdigit(str[i]); i++);
				nums.push((-1) * stoll(str.substr(a, i - a)));
				i--;
				break; // !
			}
		case '+':
			if (operators.empty() || operators.top() == '(')
				operators.push(str[i]);
			else {
				while (!operators.empty() && operators.top() != '(') {
					b = nums.top();
					if (operators.top() == '/' && b == 0) {
						cout << "Error" << endl;
						return 0;
					}
					nums.pop();
					a = nums.top();
					nums.pop();
					nums.push(compute(operators.top(), a, b));
					operators.pop();
				}
				operators.push(str[i]);
			}
			break;
		case '^':
			operators.push('^');
			break;
		case '0': case '1': case '2': case '3': case '4': 
		case '5': case '6': case '7': case '8': case '9':
			a = i;
			for (i = a + 1; i < str.size() && isdigit(str[i]); i++);
			nums.push(stoll(str.substr(a, i - a)));
			i--;
			break;
		case '(':
			operators.push('(');
			break;
		case ')':
			while ((ch = operators.top()) != '(') {
				b = nums.top();
				if (operators.top() == '/' && b == 0) {
					cout << "Error" << endl;
					return 0;
				}
				nums.pop();
				a = nums.top();
				nums.pop();
				nums.push(compute(ch, a, b));
				operators.pop();
			}
			operators.pop();
		}
	}
	//cout << "A" << endl;
	while (!operators.empty()) {
		b = nums.top();
		if (operators.top() == '/' && b == 0) {
			cout << "Error" << endl;
			return 0;
		}
		nums.pop();
		a = nums.top();
		nums.pop();
		nums.push(compute(operators.top(), a, b));
		operators.pop();
	}

	cout << nums.top() << endl;
	return 1;
}