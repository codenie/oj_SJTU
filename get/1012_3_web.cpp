#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 200007;
int d[maxn];
ll cnt[maxn], times[maxn];
//cnt[i]�洢���� ����Ϊi�����еĸ���
//d[i]�洢������i��β��������ĳ���
int main()
{
	int s, t;
	cin >> s >> t;
	memset(cnt, 0, sizeof(cnt));
	int i, j, tmp, ans = 1;
	cnt[1] = t - s + 1;

	for (i = s; i <= t; i++)
		d[i] = times[i] = 1; //��ʼ��Ϊ1

	for (i = s; i <= t; i++) //����ÿ������Ϊ���
		for (j = 1; j <= 100; j++)    if ((i*j) % 100 == 0) //����������Ϊj%
		{
			//���ڴ��������� �õ�����Ϊ tmp ���Կ���,Ҫ��tmpΪ���� ����i*j��100�ı���
			tmp = i + i*j / 100;
			if (tmp <= t) //������tmp���ڹ涨��Χ�ڵ� ���Ǿ��ҵ���һ����
			{
				if (d[i] + 1 > d[tmp]) //��ʱҪ�Ƚ� ����Ҫ��Ҫ������tmp��β����ĳ���
				{
					d[tmp] = d[i] + 1;//��tmpΪ��β�����еĳ��� Ϊ ��iΪ��β�����еĳ��� �ټ���1 ��ʾ����tmp
					times[tmp] = times[i]; //����������ȵĸ��� ����Ҫ���� ��tmp��β������ȵ��ظ�����Ϊ i��
				}
				else if (d[i] + 1 == d[tmp]) //ǡ�����ظ��������
				{
					times[tmp] += times[i];//������ȵĴ��� ���� ��i��β��������ظ�����
				}

				ans = max(ans, d[tmp]);  //����ans
										 //d[i]+1 ��ʾ��i��β�����г���+tmp�����ӵ�1λ ������ȵ���������Ҫ����times[i]
				cnt[d[i] + 1] += times[i];
			}
		}
	cout << ans << endl << cnt[ans] << endl;
	return 0;
}
