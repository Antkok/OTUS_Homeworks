#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <list>

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

/// \brief Type traits for vector
/// \details Returns false for not vector
template<typename T> struct is_vector : std::false_type {};
/// \brief Type traits for vector
/// \details Returns true for vector
template<typename... Ts> struct is_vector<std::vector<Ts...>> : std::true_type {};

/// \brief Template function for print view of ip.
/// \details Vector specialization.
template<typename T>
typename std::enable_if_t<is_vector<T>::value, std::string> print_view_ip(const T& t)
{
    std::string result;
    auto last = end(t);
    for(auto elem = begin(t); elem != last; ++elem) {
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

/// \brief Type traits for list
/// \details Returns false for not list
template<typename T> struct is_list : std::false_type {};
/// \brief Type traits for list
/// \details Returns true for list
template<typename... Ts> struct is_list<std::list<Ts...>> : std::true_type {};

/// \brief Template function for print view of ip.
/// \details List specialization.
template<typename T>
typename std::enable_if_t<is_list<T>::value, std::string> print_view_ip(const T& t)
{
    std::string result;
    auto last = end(t);
    for (auto elem = begin(t); elem != last; ++elem) {
        result += std::to_string(*elem) + ".";
    }
    result.pop_back();
    return result;
}
