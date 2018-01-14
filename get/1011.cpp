#include <iostream>
#include <iomanip>

using namespace std;

class MyComplex
{
	friend MyComplex operator+(const MyComplex& a, const MyComplex& b);
	friend MyComplex operator-(const MyComplex& a, const MyComplex& b);
	friend MyComplex operator*(const MyComplex& a, const MyComplex& b);
	friend MyComplex operator/(const MyComplex& a, const MyComplex& b);

private:
	double x, y;
public:
	MyComplex(double x = 0, double y = 0) :x(x), y(y) {};

	friend istream &operator>>(istream &is, MyComplex &item)
	{
		is >> item.x >> item.y;
		return is;
	}
	friend ostream &operator <<(ostream &out, const MyComplex &item)
	{
		out << item.x << " " << item.y;
		return out;
	}

	MyComplex operator+=(const MyComplex& cnum)
	{
		this->x += cnum.x;
		this->y += cnum.y;
		return *this;
	}
	MyComplex operator-=(const MyComplex& cnum)
	{
		this->x -= cnum.x;
		this->y -= cnum.y;
		return *this;
	}
	MyComplex operator*=(const MyComplex& cnum)
	{
		int origin_x = this->x;
		this->x = this->x * cnum.x - this->y * cnum.y;
		this->y = cnum.x * this->y + origin_x * cnum.y;
		return *this;
	}
	MyComplex operator/=(const MyComplex& cnum)
	{
		int origin_x = this->x;
		this->x = (this->x * cnum.x + this->y * cnum.y) / (cnum.x * cnum.x + cnum.y * cnum.y);
		this->y = (cnum.x * this->y - origin_x * cnum.y) / (cnum.x * cnum.x + cnum.y * cnum.y);
		return *this;
	}
};


MyComplex operator+(const MyComplex& a, const MyComplex& b)
{
	return MyComplex(a.x + b.x, a.y + b.y);
}

MyComplex operator-(const MyComplex& a, const MyComplex& b)
{
	return MyComplex(a.x - b.x, a.y - b.y);
}

MyComplex operator*(const MyComplex& a, const MyComplex& b)
{
	MyComplex result;
	result.x = a.x * b.x - a.y * b.y;
	result.y = b.x * a.y + a.x * b.y;
	return result;
}

MyComplex operator/(const MyComplex& a, const MyComplex& b)
{
	MyComplex result;
	result.x = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
	result.y = (b.x * a.y - a.x * b.y) / (b.x * b.x + b.y * b.y);
	return result;
}

int main()
{
	MyComplex z1;
	MyComplex z2;

	cin >> z1 >> z2;
	cout << fixed << setprecision(2);
	cout << (z1 + z2) << endl;
	cout << (z1 - z2) << endl;
	cout << (z1 * z2) << endl;
	cout << (z1 / z2) << endl;
	cout << (z1 += z2) << endl;
	cout << (z1 -= z2) << endl;
	cout << (z1 *= z2) << endl;
	cout << (z1 /= z2) << endl;

	return 0;
}