#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int32_t n, r;
	cin >> n >> r;

	uint64_t w, h, d, res = 0;
	for (int32_t i = 0; i < n; i++) {
		cin >> w >> h >> d;
		res += w * h * d;
	}
	res *= r;
	cout << res << endl;
	
	return 0;
}
