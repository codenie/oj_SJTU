#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int bucket[5];//��¼�ַ�������
int main()
{
	map<string, char> transform;
	transform["begin"] = 0;
	transform["end"] = 1;
	transform["if"] = 2;
	transform["then"] = 3;
	transform["else"] = 4;
	int n;
	bool flag = 0, isif = 0, isbegin = 0;
	vector<string> arr;
	string input_str;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> input_str;
		arr.push_back(input_str);
		bucket[transform[arr[i]]]++;
		if (transform[arr[i]] == 2)isif = 1;
		if (transform[arr[i]] == 3 && isif == 1)isif = 0;
		if (transform[arr[i]] == 0 && isif == 1)isbegin = 1;
		if (transform[arr[i]] == 1 && isif == 1 && isbegin == 1) { cout << "NO"; flag = 1; break; }//��ֹ���������Ϊ�ж�����
		if (bucket[0]<bucket[1] || bucket[2]<bucket[3] || bucket[2]<bucket[4])//���ùؼ��ʲ��ܶ���ǰ�ùؼ���
		{
			cout << "NO"; flag = 1; break;
		}
	}
	if (!flag)
	{
		if (bucket[0] == bucket[1] && bucket[2] == bucket[3])cout << "YES";  //���ùؼ�����ǰ�ùؼ���һһƥ��
		else cout << "NO";
	}
	return 0;
}