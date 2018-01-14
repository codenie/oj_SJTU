#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;



long long pow_me(long long a, long long b) {
	long long r = 1, base = a;
	while (b) {
		if (b & 1) r *= base;
		base *= base;
		b >>= 1;
	}
	return r;
}

//ideas:
/*
使用两个数组，一个储存数字，一个储存符号，遇到括号就新开两个数组，进行此过程，这样节省空间，
并且每一次运算都不涉及括号，计算方便，可以在遍历时就储存哥哥符号的位置，计算方便。
有没有更好的方案？
*/
struct LongLongInt {
	long long number;
	char mode;
	LongLongInt(long long number = 0, char mode = 0) :number(number), mode(mode) {};
	/*
	mode operation
	0	number
	1	+
	2	-
	3	*
	4	/
	5	^
	6	(
	7	)
	*/
};

bool compute(vector<LongLongInt> &expression, int left, int right)
{
	long long result;
	for (int index = right - 2; index > left; index -= 2) {
		if (expression[index].mode == 5) {  // ^
			result = pow_me(expression[index - 1].number, expression[index + 1].number);
			expression.erase(expression.begin() + index, expression.begin() + index + 2);
			expression[index - 1].number = result;
		}
	}
	for (int index = left + 2; expression[index].mode != 7;) {
		switch (expression[index].mode) {
		case 3:  // *
			result = expression[index - 1].number * expression[index + 1].number;
			expression.erase(expression.begin() + index, expression.begin() + index + 2);
			expression[index - 1].number = result;
			break;
		case 4: // /
			if (expression[index + 1].number == 0)
				return false;
			result = expression[index - 1].number / expression[index + 1].number;
			expression.erase(expression.begin() + index, expression.begin() + index + 2);
			expression[index - 1].number = result;
			break;
		default:
			index += 2;
		}
	}
	for (int index = left + 2; expression[index].mode != 7;) {
		switch (expression[index].mode) {
		case 1:  // +
			result = expression[index - 1].number + expression[index + 1].number;
			expression.erase(expression.begin() + index, expression.begin() + index + 2);
			expression[index - 1].number = result;
			break;
		case 2: // -
			result = expression[index - 1].number - expression[index + 1].number;
			expression.erase(expression.begin() + index, expression.begin() + index + 2);
			expression[index - 1].number = result;
			break;
		default:
			index += 2;
		}
	}
	return true;
}

int find_to_right(vector<LongLongInt> &expression, int num, int mode)
{
	int length = expression.size();
	int i;
	for (i = num; i < length; i++) {
		if (expression[i].mode == mode)
			break;
	}
	return (i == length) ? (-1) : i;
}

int find_to_left(vector<LongLongInt> &expression, int num, int mode)
{
	int i;
	for (i = num; i >= 0; i--) {
		if (expression[i].mode == mode)
			break;
	}
	return i;
}

// 注意式子的结构，在没有括号的情况下，肯定是一个数字，一个算数符号！！！
// conpute的时候需要查找算数符号，这样可以省去很多时间！！

int main()
{
	string str_expr;
	getline(cin, str_expr);
	str_expr = '(' + str_expr + ')';

	vector<LongLongInt> expression;
	int count = 0;
	int digit_posi = -1;
	int length = str_expr.size();

	for (int i = 0; i < length; i++) {
		if (isdigit(str_expr[i])) {  // digit
			digit_posi = i;
			for (; i < length && isdigit(str_expr[i]); i++);
			expression.emplace_back(stoll(str_expr.substr(digit_posi, i - digit_posi)));
			i--;
		}
		else {  // not a digit
			switch (str_expr[i]) {
			case '(': 
				count++;
				expression.emplace_back(0, 6);
				break;
			case ')':
				if (count == 0) {
					cout << "Error";
					return 0;
				}
				count--;
				expression.emplace_back(0, 7);
				break;
			case '+':
				expression.emplace_back(0, 1);
				break;
			case '-':
				if (str_expr[i + 1] != ' ') {
					digit_posi = ++i;
					for (; i < length && isdigit(str_expr[i]); i++);
					expression.emplace_back( (-1) * stoll(str_expr.substr(digit_posi, i - digit_posi)));
					i--;
				}
				else {
					expression.emplace_back(0, 2);
				}
				break;
			case '*':
				expression.emplace_back(0, 3);
				break;
			case '/':
				expression.emplace_back(0, 4);
				break;
			case '^':
				expression.emplace_back(0, 5);
				break;
			}
		}
	}
	if (count) {
		cout << "Error";
		return 0;
	}

	//for (auto num : expression) {
	//	cout << int(num.mode) << "     " << num.number << endl;
	//}

	int left = expression.size(), right;

	while (true) {
		left = find_to_left(expression, left - 1, 6);
		if (left == -1)
			break;
		right = find_to_right(expression, left + 1, 7);
		if (!compute(expression, left, right)) {
			cout << "Error";
			return 0;
		}
		expression.erase(expression.begin() + left);
		expression.erase(expression.begin() + left + 1);
	}

	cout << expression[0].number << endl;
	//for (auto num : expression) {
	//	cout << num.number << endl;
	//}
	//cout << expression[0].number << endl;
	return 0;
}