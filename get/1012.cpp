#include <iostream>
/*
����һ��ʧ�ܵ�˼·������ԭ���Ƕ�̬�滮��Ӧ�ô�С����ģ������ǴӴ���С�ң�num��������Ҷ�Ӧ��С��������Ҫ���� num / 2�� �������ܴ������С���ģ�ÿ������Ҫ���100�Σ�1 - 100�� 
��������ǲ��ϸ�ֱ���˳��ģ��������˼�������
��ȷ��������һ���ļ���
DP Problem
*/
using namespace std;
struct number {
	int maxlength;
	int count;
	number(int maxlength = 0, int count = 0) :maxlength(maxlength), count(count) {};
};
int main()
{
	int start, end;
	int i, index;
	double digit;
	int maxlength, length, count = 0, count_blank = 0;
	cin >> start >> end;
	number* nums = new number[end - start];
	nums[0].count = 1;
	nums[0].maxlength = 1;
	for (i = start + 1; i < end; i++) {
		index = ((i / 2 > start) ? (i / 2) : start);
		maxlength = 0;
		for (; index < i; index++) {
			if (nums[index - start].maxlength + 1 < maxlength) {
				continue;
			}
			digit = double(i * 100) / index;
			if (digit != int(digit))
				continue;

			length = nums[index - start].maxlength + 1;
			if (length == maxlength) {
				count += nums[index - start].count;
			}
			else if (length > maxlength) {
				maxlength = length;
				count = nums[index - start].count;
			}
			nums[i - start].count = count;
			nums[i - start].maxlength = maxlength;
		}
	}

	index = ((end / 2 > start) ? (end / 2) : start);
	maxlength = 0;
	for (; index < end; index++) {
		if (nums[index - start].maxlength + 1 < maxlength) {
			continue;
		}
		digit = double(end * 100) / index;
		length = nums[index - start].maxlength + (digit == int(digit));
		if (length == maxlength) {
			count += nums[index - start].count;
		}
		else if (length > maxlength) {
			maxlength = length;
			count = nums[index - start].count;
		}
		else {
			continue;
		}
	}
	cout << maxlength << endl << count << endl;
	return 0;
}