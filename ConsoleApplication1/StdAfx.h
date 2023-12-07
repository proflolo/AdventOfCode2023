#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <charconv>
#include <assert.h>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <tuple>
#include <optional>

inline std::pair<std::string_view, std::string_view> divide(const std::string& i_chars, const std::string_view& i_str)
{
    auto pos = i_str.find_first_of(i_chars);
    if (pos == std::string_view::npos)
    {
        return { i_str, std::string_view() };
    }
    return { std::string_view(&i_str[0], pos), std::string_view(&i_str[pos] + 1, i_str.size() - (pos + 1)) };
}

inline std::vector<std::string_view> split(const std::string& i_chars, const std::string_view& i_str)
{
    std::vector<std::string_view> result;
    std::string_view remaining(&i_str[0], i_str.size());
    auto pos = remaining.find_first_of(i_chars);
    while (pos != std::string::npos && pos < i_str.size())
    {
        std::string_view chunk(&remaining[0], pos);
        if (chunk.size() > 0)
        {
            result.emplace_back(chunk);
        }
        remaining = remaining.substr(pos + 1);
        pos = remaining.find_first_of(i_chars);
    }
    result.emplace_back(remaining);
    return result;
}

inline std::string_view trim_left(const std::string_view& data, std::string_view trimChars)
{
    std::string_view sv{data};
    sv.remove_prefix(std::min(sv.find_first_not_of(trimChars), sv.size()));
    return sv;
}

inline std::string_view trim_left(const std::string_view& data)
{
    return trim_left(data, " ");
}

inline int stoi(std::string_view i_str)
{
    int result = 0;
    std::from_chars(i_str.data(), i_str.data() + i_str.size(), result);
    return result;
}

template<typename T>
inline T ston(std::string_view i_str)
{
    T result = 0;
    std::from_chars(i_str.data(), i_str.data() + i_str.size(), result);
    return result;
}


template<typename S, typename... Strings>
inline std::tuple<S, Strings...> _divide(std::string_view i_chars, std::string_view i_str)
{
    if constexpr (sizeof...(Strings) == 0)
    {
        return { i_str };
    }
    else
    {
        auto pos = i_str.find_first_of(i_chars);
        if (pos == std::string_view::npos)
        {
            return std::tuple<S, Strings...>();
        }
        auto res = _divide<Strings...>(i_chars, std::string_view(&i_str[pos] + 1, i_str.size() - (pos + 1)));
        return std::tuple_cat(std::make_tuple(std::string_view(&i_str[0], pos)), res);
    }
}



template<size_t S = 2, typename T = std::string_view>
inline auto fragment(std::string_view i_chars, std::string_view i_source)
{

}

template<>
inline auto fragment<3, std::string_view>(std::string_view i_chars, std::string_view i_source)
{
    return _divide<std::string_view, std::string_view, std::string_view>(i_chars, i_source);
}

template<>
inline auto fragment<3, unsigned long long>(std::string_view i_chars, std::string_view i_source)
{
    using T = unsigned long long;
    auto t = fragment<3, std::string_view>(i_chars, i_source);
    return std::make_tuple(ston<T>(std::get<0>(t)), ston<T>(std::get<1>(t)) , ston<T>(std::get<2>(t)));
}

