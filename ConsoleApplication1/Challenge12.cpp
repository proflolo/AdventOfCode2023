#include "StdAfx.h"
#include "Challenge12.h"

namespace challenge12
{
    using Bid = int;
    using Points = long long;

	

    enum class Type
    {
        Spring,
        Empty,
        Unknown
    };
    using Key = std::pair<size_t, long long>;
    ;

    long long Process(std::vector<Type>& i_types, long long i_numUnknows, size_t i_begin, const std::vector<long long>& i_target, long long i_numSpas, std::map<Key, long long>& s_cache)
    {
        if (i_numUnknows > 0 && i_numSpas > 0)
        {
            std::vector<long long> result;
            long long count = 0;
            for (auto it = i_types.begin(); it != i_types.begin() + i_begin + 1; ++it)
            {
                Type t = *it;
                if (t == Type::Empty || t == Type::Unknown)
                {
                    if (count > 0)
                    {
                        result.emplace_back(count);
                    }
                    count = 0;
                }
                else
                {
                    count++;
                }
            }
            if (count > 0)
            {
                result.emplace_back(count);
            }
            for (long long i = 0; i < result.size() && i < i_target.size(); ++i)
            {
                if (i < result.size() - 1)
                {
                    if (result[i] != i_target[i])
                    {
                        return 0;
                    }
                }
                else
                {
                    if (result[i] > i_target[i])
                    {
                        return 0;
                    }
                }
            }

            bool canBecached = i_begin != 0 && (i_types[i_begin] == Type::Empty);
            if (canBecached)
            {
                auto jt = s_cache.find(Key(i_begin, i_numSpas));
                if (jt != s_cache.end())
                {
                    
                    return jt->second;
                }
            }
            long long x1 = 0;
            long long x2 = 0;
            auto it = std::find(i_types.begin() + i_begin, i_types.end(), Type::Unknown);
            {
                *it = Type::Empty;
                x1 = Process(i_types, i_numUnknows - 1, it - i_types.begin(), i_target, i_numSpas, s_cache);
            }
            {
                *it = Type::Spring;
                x2 = Process(i_types, i_numUnknows - 1, it - i_types.begin(), i_target, i_numSpas - 1, s_cache);
            }
            *it = Type::Unknown;
            if (canBecached)
            {
                 s_cache.emplace(Key(i_begin, i_numSpas), x1 + x2);
            }
            return x1 + x2;
        }
        else
        {
            std::vector<long long> result;
            long long count = 0;
            for (Type t : i_types)
            {
                if (t == Type::Empty || t == Type::Unknown)
                {
                    if (count > 0)
                    {
                        result.emplace_back(count);
                    }
                    count = 0;
                }
                else
                {
                    count++;
                }
            }
            if (count > 0)
            {
                result.emplace_back(count);
            }

            if (i_target == result)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    
	void Part1()
	{
        using Amount = long long;
        std::ifstream input("input12_sample.txt");
        std::string line;

        long long result = 0;

        while (std::getline(input, line))
        {
            auto [layoutStr, numbersStr] = divide(" ", line);
            std::vector<Type> types;
            long long numUnknowns = 0;
            for (char c : layoutStr)
            {
                switch (c)
                {
                case '.':
                    types.emplace_back(Type::Empty);
                    break;
                case '#':
                    types.emplace_back(Type::Spring);
                    break;
                case '?':
                    numUnknowns++;
                    types.emplace_back(Type::Unknown);
                    break;
                }
            }
            std::vector<long long> numbers;
            std::vector<std::string_view> splitNumbers = split(",", numbersStr);
            for (std::string_view s : splitNumbers)
            {
                numbers.emplace_back(ston<long long>(s));
            }
            long long numSpas = std::accumulate(numbers.begin(), numbers.end(), 0) - std::count(types.begin(), types.end(), Type::Spring);
            std::map<Key, long long> s_cache;
            long long combos = Process(types, numUnknowns, 0, numbers, numSpas, s_cache);
            result += combos;
        }
        //7110
        std::cout << result << std::endl;
	}

    void Part2()
    {
        using Amount = long long;
        std::ifstream input("input12.txt");
        std::string line;

        long long result = 0;

        long long lineIdx = 0;
        while (std::getline(input, line))
        {
            auto [layoutStr, numbersStr] = divide(" ", line);
            std::vector<Type> types;
            long long numUnknowns = 0;
            for (char c : layoutStr)
            {
                switch (c)
                {
                case '.':
                    types.emplace_back(Type::Empty);
                    break;
                case '#':
                    types.emplace_back(Type::Spring);
                    break;
                case '?':
                    numUnknowns++;
                    types.emplace_back(Type::Unknown);
                    break;
                }
            }
            std::vector<long long> numbers;
            std::vector<std::string_view> splitNumbers = split(",", numbersStr);
            for (std::string_view s : splitNumbers)
            {
                numbers.emplace_back(ston<long long>(s));
            }

            auto copy = types;
            auto copy2 = numbers;
            for (long long i = 0; i < 4; ++i)
            {
                types.emplace_back(Type::Unknown);
                types.insert(types.end(), copy.begin(), copy.end());
                numbers.insert(numbers.end(), copy2.begin(), copy2.end());
            }
            numUnknowns = std::count(types.begin(), types.end(), Type::Unknown);
            long long numSpas = std::accumulate(numbers.begin(), numbers.end(), 0) - std::count(types.begin(), types.end(), Type::Spring);
            std::map<Key, long long> s_cache;
            long long combos = Process(types, numUnknowns, 0, numbers, numSpas, s_cache);
            result += combos;
            std::cout << lineIdx << std::endl;
            lineIdx++;
        }
        //1566786613613
        std::cout << result << std::endl;
    }
}