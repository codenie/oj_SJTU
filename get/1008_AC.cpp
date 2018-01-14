#include <iostream>
#include <stdio.h>
using namespace std;
int dayOfMonth[2][13] = { { 0,31,28,31,30,31,30,31,31,30,31,30,31 },{ 0,31,29,31,30,31,30,31,31,30,31,30,31 } };

//�������ڵĽṹ�壬�����ж�ƽ�����꣬�ж�ĳ�����������ܵĵڼ���
//�������Ҫ��ÿ���1��2����Ϊ��һ���13��14�·�
struct Date
{
	int y, m, d;
	int leap()
	{
		return (y % 4 == 0 && y % 100 != 0 || y % 400 == 0 ? 1 : 0);
	}
	int week()
	{
		int Y = y, M = m;
		if (m == 1 || m == 2)
		{
			Y--;
			M += 12;
		}
		int W = (d + M * 2 + 3 * (M + 1) / 5 + Y + Y / 4 - Y / 100 + Y / 400) % 7;
		return W + 1;
	}
	Date() {}
	//����������캯��
	Date(int yy, int mm, int dd) { y = yy; m = mm; d = dd; }

	//����ṹ�庯��getNext()����ú�һ�������

	Date getNext()
	{
		//����������С�ڸ��µ�����������򽫸�������1
		Date t(y, m, d);
		if (d<dayOfMonth[leap()][m])
			t.d += 1;
		//���dayΪĳ�����һ�죬��Ƚ����ڣ����monthС��12�£����·ݼ�1
		//���ҽ�����Ϊ1
		else if (m<12)
		{
			t.m += 1;
			t.d = 1;
		}
		//�º���Ϊ12.31�������ϼӣ��º��վ���Ϊ1��1��
		else
		{
			t.y += 1;
			t.m = 1;
			t.d = 1;
		}
		return t;
	}
	//�ж��Ƿ�Ϊ֤ȯ���������
	//�������������������Ϊ�������ڣ����������Ԫ������һ��ʮһҲ��Ϊ��������
	bool dealDay()
	{
		if (week() == 6 || week() == 7)
			return false;
		if (m == 1 && d == 1 || m == 5 && d >= 1 && d <= 3 || m == 10 && d >= 1 && d <= 7)
			return false;
		return true;
	}
	//�ж��Ƿ�Ϊ��ĩ
	bool isWeekend()
	{
		return week() == 6 || week() == 7;
	}
};

//�ж��������Ƿ�Ϊ��ȵ����ڣ���������վ���ȣ�������ͬ������

bool equals(Date d1, Date d2)
{
	return d1.y == d2.y&&d1.m == d2.m&&d1.d == d2.d;
}

//�ж�һ�����ж����콻����

int ansOfYear(int year)
{
	bool isleap = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
	int res = (isleap ? 366 : 365), t1, t2, t3 = 0, i;
	//һ����52�ܣ�������104�����ĩ
	t1 = 104;
	//��������꣬һ�����52�������죬����12.30��12.31
	if (isleap)
	{
		//���12.30Ϊ��ĩ����ǽ����ն�һ�죬ͬ��12.31
		if (Date(year, 12, 30).isWeekend())
			t1 += 1;
		if (Date(year, 12, 31).isWeekend())
			t1 += 1;
	}
	//�����ƽ��Ļ���52�ܶ�1�죬��12.31�������ĩ��ǽ����ն�һ��
	else
	{
		if (Date(year, 12, 31).isWeekend())
			t1 += 1;
	}

	//Ԫ��+��һ+����==11��ļ��ڲ�����
	t2 = 11;
	//�ж������������Ƿ����ĩ��ͻ����ͻ���м���
	if (Date(year, 1, 1).isWeekend())
		t3 += 1;
	for (i = 1; i<4; i++)
		if (Date(year, 5, i).isWeekend())
			t3 += 1;
	for (i = 1; i<8; i++)
		if (Date(year, 10, i).isWeekend())
			t3 += 1;
	//����һ���ж��ٸ�������
	res = res - t1 - t2 + t3;
	return res;
}

int main()
{
	int n, res = 0, i;
	Date d1, d2, t;
	scanf("%d", &n);
	while (n--)
	{
		res = 0;
		//������������
		scanf("%d-%d-%d %d-%d-%d", &d1.y, &d1.m, &d1.d, &d2.y, &d2.m, &d2.d);
		//�����������֮�����С�ڵ���һ�꣬��ֱ�Ӽ������ڲ�
		//��ʼ����Ϊ��һ�����ڣ���ֹ����Ϊ�ڶ������ڣ���getNext()�������һ���//���ڣ���������ǽ����յĻ���res++
		if (d2.y - d1.y <= 1)
		{
			for (t = d1; !equals(t, d2.getNext()); t = t.getNext())
				if (t.dealDay())
					res += 1;
		}
		//��������������һ�����ϣ����ȼ����һ�����ڵ���һ��1.1֮ǰ�Ľ�����
		//�ټ���ڶ������ڵĴ�1.1�������ڵĽ�������
		//����ټ������֮����������֮��Ľ�����
		else
		{
			for (t = d1; !equals(t, Date(d1.y + 1, 1, 1)); t = t.getNext())
				if (t.dealDay())
					res += 1;
			for (t = Date(d2.y, 1, 1); !equals(t, d2.getNext()); t = t.getNext())
				if (t.dealDay())
					res += 1;
			for (i = d1.y + 1; i<d2.y; i++)
				res += ansOfYear(i);
		}
		printf("%d\n", res);
	}
	return 0;
}
