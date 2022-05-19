#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <vector>
#include <array>

using arrIp = std::array<int,4>;

class textIP {

public:
	void printIP(const arrIp& ip);
	arrIp parse(const std::string& input);
	void checkIp(const arrIp& ip);
	void sotrPrint(const std::vector<arrIp>& addrs, bool(*func)(const arrIp&));
};
