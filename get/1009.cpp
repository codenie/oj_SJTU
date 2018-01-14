#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Trade {
	int time;
	int stock;
	int mode;
	Trade(int time, int stock, int mode) :time(time), stock(stock), mode(mode) {};
};

struct StockPrice {
	int time;
	int price;
	StockPrice(int time, int price) :time(time), price(price) {};
};

vector<Trade> trade;
vector<StockPrice> price;
int tradeNum, priceNum;

int getPrice(int time)
{
	static int index = 0;
	for (; index < priceNum; index++) {
		if (price[index].time > time)
			break;
	}
	return price[index - 1].price;
}

int main()
{
	int i, t, a, d;
	cin >> tradeNum;
	for (i = 0; i < tradeNum; i++) {
		cin >> t >> a >> d;
		trade.push_back(Trade(t, a, d));
	}
	cin >> priceNum;
	for (i = 0; i < priceNum; i++) {
		cin >> t >> a;
		price.push_back(StockPrice(t, a));
	}
	//cin has ended
	double profit = 0;
	int trademoney;
	for (i = 0; i < tradeNum; i++) {
		trademoney = getPrice(trade[i].time) * trade[i].stock;
		if (trade[i].mode == 1) {   // buy
			profit -= (0.2 * trademoney > 5) ? (0.2 * trademoney) : 5;
			profit = profit - 0.1 * trade[i].stock - 1 - trademoney * 100;
		}
		else {  //sell
			profit -= (0.2 * trademoney > 5) ? (0.2 * trademoney) : 5;
			profit = profit - 0.1 * trade[i].stock - 1 + trademoney * 99.9;
		}
	}
	cout << fixed << setprecision(2) << profit << endl;

	return 0;
}

// 其实这道题还有非常容易的优化策略，遍历所有的交易记录，得到总交易额和总的交易股票数，加在一起再进行处理，可以减小操作量
// 这道题重要地方是数据的储存，使用struct再合适不过了