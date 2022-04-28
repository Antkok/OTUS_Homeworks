#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <vector>

using tupIp = std::tuple<int, int, int, int>;

std::tuple<int, int, int, int> parse(const std::string& input);
void checkIp(const tupIp& ip);
void PrintIP(const tupIp& ip);
void sotrPrint(const std::vector<tupIp>& addrs, bool(*func)(const tupIp&));