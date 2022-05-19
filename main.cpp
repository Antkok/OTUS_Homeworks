#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ip_filter.h"
#include <array>

using namespace std;
int main() {
	vector<arrIp> poolIp;
	string text;
	textIP sortPrintIP;

	while (getline(cin, text)) {
		if (text == "") //for windows
			break;
		textIP parseText;
		arrIp ip = parseText.parse(text);
		parseText.checkIp(ip);
		poolIp.emplace_back(std::move(ip));
	}

	sort(poolIp.begin(), poolIp.end(), [](const auto& a, const auto& b) {	
		return a > b; 
	});

	for_each(poolIp.begin(), poolIp.end(), [](const arrIp& ip) {
		textIP printIp;
		printIp.printIP(ip);
	});

	sortPrintIP.sotrPrint(poolIp, [](const arrIp& ip) {
		if (get<0>(ip) == 1) return true;
		else return false;
	});

	sortPrintIP.sotrPrint(poolIp, [](const arrIp& ip) {
		if (get<0>(ip) == 46 && get<1>(ip) == 70) return true;
		else return false;
	});

	sortPrintIP.sotrPrint(poolIp, [](const arrIp& ip) {
		if (get<0>(ip) == 46 || get<1>(ip) == 46 || get<2>(ip) == 46 || get<3>(ip) == 46) return true;
		else return false;
	});

	return 0;
}
