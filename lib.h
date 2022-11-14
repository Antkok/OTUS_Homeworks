#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include <type_traits>

int version();

/// \brief Template function for print view of ip
/// \details Integer specialization
template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, std::string> print_view_ip(const T& value)
{
    auto i = std::max((T)4, (T)sizeof(T));
    std::string result;
    while (i > 0) {
        --i;
        result += std::to_string(((value >> (8 * i))) & 0XFF) + ".";
    }
    result.pop_back();
    return result;
}

/// \brief Template function for print view of ip.
/// \details Specialization for containers.
template<typename T>
decltype(begin(std::declval<T>()), end(std::declval<T>()), std::string()) print_view_ip(const T& container)
{
    std::string result;
    auto last = end(container);
    for(auto elem = begin(container); elem != last; ++elem) {
        result += std::to_string(*elem) + ".";
    }
    result.pop_back();
    return result;
}

/// \brief Type traits for tuple
/// \details Returns false for not tuples
template<typename T> struct is_tuple : std::false_type {};
/// \brief Type traits for tuple
/// \details Returns true for tuples
template<typename... Ts> struct is_tuple<std::tuple<Ts...>> : std::true_type {};

/// \brief Template function for print view of ip.
/// \details Tuple specialization.
template<typename T>
typename std::enable_if_t<is_tuple<T>::value, std::string> print_view_ip(const T& t)
{
    std::string result;
    std::apply([&](auto&&... args) {(( result += std::to_string(args) + "." ), ...);}, t);
    result.pop_back();
    return result;
}

/// \brief Template function for print view of ip.
/// \details Specialization for strings.
std::string print_view_ip(const std::string& value)
{
    return value;
}
