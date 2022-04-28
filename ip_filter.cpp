#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include "ip_filter.h"

std::tuple<int, int, int, int> parse(const std::string& input)
{
	size_t idx = 0;
	size_t shift = 0;
	auto temp = input.substr(idx);
	int ip1 = stoi(temp, &shift);
	idx += shift + 1;
	int ip2 = stoi(input.substr(idx), &shift);
	idx += shift + 1;
	int ip3 = stoi(input.substr(idx), &shift);
	idx += shift + 1;
	int ip4 = stoi(input.substr(idx), &shift);
	return std::make_tuple(ip1, ip2, ip3, ip4);
}

void checkIp(const tupIp& ip) {
	for (int i = 0; i < std::tuple_size<tupIp>::value; i++)
		if ((std::get<0>(ip) < 0) || (std::get<0>(ip) > 255)) {
			std::cout << "Incorrect IP" << std::endl;
		}
}

void PrintIP(const tupIp& ip)
{
	std::cout << (std::get<0>(ip)) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
}

void sotrPrint(const std::vector<tupIp>& addrs, bool(*func)(const tupIp&))
{
	std::for_each(addrs.begin(), addrs.end(), [&](const tupIp& ip) {
		if (func(ip)) {
			PrintIP(ip);
		}
	});
}