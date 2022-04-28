#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include "ip_filter.h"

using namespace std;

int main() {
	vector<tupIp> poolIp;
	string text1, text2, text3;

	while (getline(cin, text1)) {
		if (text1 == "") //for windows
			break;
		tupIp ip = parse(text1);
		checkIp(ip);
		poolIp.emplace_back(std::move(ip));
	}

	sort(poolIp.begin(), poolIp.end(), [](const auto& a, const auto& b) {	
		return a > b; 
	});

	for_each(poolIp.begin(), poolIp.end(), [](const tupIp& ip) {
		PrintIP(ip);
	});

	sotrPrint(poolIp, [](const tupIp& ip) {
		if (get<0>(ip) == 1) return true;
		else return false;
	});

	sotrPrint(poolIp, [](const tupIp& ip) {
		if (get<0>(ip) == 46 && get<1>(ip) == 70) return true;
		else return false;
	});

	sotrPrint(poolIp, [](const tupIp& ip) {
		if (get<0>(ip) == 46 || get<1>(ip) == 46 || get<2>(ip) == 46 || get<3>(ip) == 46) return true;
		else return false;
	});

	return 0;
}