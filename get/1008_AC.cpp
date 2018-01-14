#include <iostream>
#include <stdio.h>
using namespace std;
int dayOfMonth[2][13] = { { 0,31,28,31,30,31,30,31,31,30,31,30,31 },{ 0,31,29,31,30,31,30,31,31,30,31,30,31 } };

//定义日期的结构体，用来判断平年闰年，判断某个日期是这周的第几天
//这个方法要将每年的1，2月作为上一年的13，14月份
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
	//定义输出构造函数
	Date(int yy, int mm, int dd) { y = yy; m = mm; d = dd; }

	//定义结构体函数getNext()，获得后一天的日期

	Date getNext()
	{
		//如果这个天数小于该月的最大天数，则将该天数加1
		Date t(y, m, d);
		if (d<dayOfMonth[leap()][m])
			t.d += 1;
		//如果day为某月最后一天，则比较日期，如果month小于12月，则月份加1
		//并且将日设为1
		else if (m<12)
		{
			t.m += 1;
			t.d = 1;
		}
		//月和日为12.31则年往上加，月和日均设为1月1日
		else
		{
			t.y += 1;
			t.m = 1;
			t.d = 1;
		}
		return t;
	}
	//判断是否为证券处理的日期
	//如果这天是周六周日则不为处理日期，如果这天是元旦、五一、十一也不为处理日期
	bool dealDay()
	{
		if (week() == 6 || week() == 7)
			return false;
		if (m == 1 && d == 1 || m == 5 && d >= 1 && d <= 3 || m == 10 && d >= 1 && d <= 7)
			return false;
		return true;
	}
	//判断是否为周末
	bool isWeekend()
	{
		return week() == 6 || week() == 7;
	}
};

//判断这两天是否为相等的日期，如果年月日均相等，则是相同的日期

bool equals(Date d1, Date d2)
{
	return d1.y == d2.y&&d1.m == d2.m&&d1.d == d2.d;
}

//判断一年中有多少天交易日

int ansOfYear(int year)
{
	bool isleap = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
	int res = (isleap ? 366 : 365), t1, t2, t3 = 0, i;
	//一年有52周，这样有104天的周末
	t1 = 104;
	//如果是闰年，一年就有52周余两天，即余12.30与12.31
	if (isleap)
	{
		//如果12.30为周末，则非交易日多一天，同理12.31
		if (Date(year, 12, 30).isWeekend())
			t1 += 1;
		if (Date(year, 12, 31).isWeekend())
			t1 += 1;
	}
	//如果是平年的话，52周多1天，即12.31如果是周末则非交易日多一天
	else
	{
		if (Date(year, 12, 31).isWeekend())
			t1 += 1;
	}

	//元旦+五一+国庆==11天的假期不交易
	t2 = 11;
	//判断这三个假期是否和周末冲突，冲突的有几天
	if (Date(year, 1, 1).isWeekend())
		t3 += 1;
	for (i = 1; i<4; i++)
		if (Date(year, 5, i).isWeekend())
			t3 += 1;
	for (i = 1; i<8; i++)
		if (Date(year, 10, i).isWeekend())
			t3 += 1;
	//计算一年中多少个交易日
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
		//输入两个日期
		scanf("%d-%d-%d %d-%d-%d", &d1.y, &d1.m, &d1.d, &d2.y, &d2.m, &d2.d);
		//如果两个日期之间相差小于等于一年，则直接计算日期差
		//起始日期为第一个日期，终止日期为第二个日期，用getNext()来计算后一天的//日期，并且如果是交易日的话，res++
		if (d2.y - d1.y <= 1)
		{
			for (t = d1; !equals(t, d2.getNext()); t = t.getNext())
				if (t.dealDay())
					res += 1;
		}
		//如果两个日期相差一年以上，则先计算第一个日期到下一年1.1之前的交易日
		//再计算第二个日期的从1.1到该日期的交易日数
		//最后再计算二者之间相差的年数之间的交易日
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
