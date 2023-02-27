#include <iostream>
#include <vector>

using namespace std;

int main()
{
	size_t n;
	cin >> n;

	int64_t sum = 0;
	vector<int64_t> data(n);
	for (auto &it : data) {
		cin >> it;
		sum += it;
	}
	int64_t avg = sum / static_cast<int64_t>(n);

	vector<int> res_vec;
	for (size_t i = 0; i < n; i++) {
		if (data[i] > avg) {
			res_vec.push_back(i);
		}

	}
	cout << res_vec.size() << endl;
	for (const auto it : res_vec)
		cout << it << ' ';
	cout << endl;

	return 0;
}
