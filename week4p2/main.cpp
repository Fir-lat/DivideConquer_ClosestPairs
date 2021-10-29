#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
#include <map>
#include <iterator>
#include <list>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

class P2 {
public:;
	P2() {
	}
	~P2() {

	}

	const static int YRANGE = 300;
	const static int D = 10;

	static vector<pair<double, double>> makeSequence(int a) {
		vector<pair<double, double>> sequence;
		double yLast = 0.0;
		double xLast = 0.0;
		unsigned seed = time(nullptr);
		srand(seed + a);
		while (yLast < (double)YRANGE) {
			double x = (double)(rand()) * D / (double)(RAND_MAX);
			double y = yLast + sqrt(pow(D, 2) - pow(x - xLast, 2));
			pair<double, double> node(x, y);
			sequence.push_back(node);
			xLast = x;
			yLast = y;
		}
		return sequence;
	}

	static bool cmpWithY(const pair<double, double>& pair1, const pair<double, double>& pair2) {
		return pair1.second < pair2.second;
	}
};

int main() {
	vector<pair<double, double>> left = P2::makeSequence(1);
	for (pair<double, double> & Pair : left) {
		cout << Pair.first << ", " << Pair.second << endl;
	}
	cout << endl;
	vector<pair<double, double>> right = P2::makeSequence(2);
	for (pair<double, double> & Pair : right) {
		cout << Pair.first << ", " << Pair.second << endl;
	}
	for (vector<pair<double, double>>::iterator iter = right.begin(); iter != right.end(); iter++) {
		iter->first += (double)P2::D;
	}
	left.insert(left.end(), right.begin(), right.end());
	sort(left.begin(), left.end(), P2::cmpWithY);
	vector<pair<pair<double, double>, pair<double, double>>> hit;
	vector<int> times;
	vector<double> distances;
	for (vector<pair<double, double>>::iterator iter = left.begin(); iter != left.end(); iter++) {
		vector<pair<double, double>>::iterator iter2 = iter + 1;//每次仅向后找
		int time = 0;
		while (iter2 != left.end() && distance(iter2, iter) <= 15) { //根据最基础的推论，最多需要寻找15个
			if (iter->first <= P2::D && iter2->first <= P2::D || iter->first > P2::D && iter2->first > P2::D) {
				iter2++;
				continue;
			}
			else {
				double dist = (double)sqrt(pow(iter2->first - iter->first, 2) + pow(iter2->second - iter->second ,2));
				if (dist < P2::D) {
					pair<pair<double, double>, pair<double, double>> Pair(*iter, *iter2);
					hit.push_back(Pair);
					times.push_back(++time);
					distances.push_back(dist);
				}
				iter2++;
			}
		}
	}
	cout << "\nD = " << P2::D << endl;
	cout << "Found pairs:" << endl;
	for (int i = 0; i < hit.size(); i++) {
		cout << hit[i].first.first << "," << hit[i].first.second << "\t<-----> ";
		cout << hit[i].second.first << "," << hit[i].second.second << "\t\tno. " << times[i] << "\t";
		cout << "distance: " << distances[i] << endl;
	}
	cout << "其中\"no.i\"对应的为点对中任一点的第i个点对，可以发现大多数情况，一个点可以在另一边找到一个点使其距离小于D" << endl;
	return 0;
}