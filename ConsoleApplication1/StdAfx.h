#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <charconv>
#include <assert.h>



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
        result.emplace_back(chunk);
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