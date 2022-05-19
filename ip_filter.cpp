#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include "ip_filter.h"
#include <array>


void textIP::printIP(const arrIp& ip) {
	std::cout << (std::get<0>(ip)) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
}

arrIp textIP::parse(const std::string& input) {
	size_t idx = 0;
	size_t shift = 0;
	try {
		auto temp = input.substr(idx);
		int ip1 = stoi(temp, &shift);
		idx += shift + 1;
		int ip2 = stoi(input.substr(idx), &shift);
		idx += shift + 1;
		int ip3 = stoi(input.substr(idx), &shift);
		idx += shift + 1;
		int ip4 = stoi(input.substr(idx), &shift);
		return arrIp{ ip1,ip2,ip3,ip4 };
	}
	catch (...)
	{
		return arrIp{ 0,0,0,0 };
	}
}

void textIP::checkIp(const arrIp& ip) {
	for (long unsigned int i = 0; i < std::tuple_size<arrIp>::value; i++)
		if ((std::get<0>(ip) < 0) || (std::get<0>(ip) > 255)) {
			std::cout << "Incorrect IP" << std::endl;
			break;
		}
}

void textIP::sotrPrint(const std::vector<arrIp>& addrs, bool(*func)(const arrIp&)) {
	std::for_each(addrs.begin(), addrs.end(), [&](const arrIp& ip) {
		if (func(ip)) {
			printIP(ip);
		}
	});
}
