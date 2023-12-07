#include "StdAfx.h"
#include "Challenge4.h"

namespace challenge4
{
    /*
    int card_score(const std::string& line)
    {
        int result = 0;
        auto [x, data] = divide(":", line);
        auto [winningNumbersStr, numbersStr] = divide("|", data);
        auto winningNumbers = split_set(" ", trim_left(winningNumbersStr));
        auto numbers = split_set(" ", trim_left(numbersStr));
        std::vector<std::string_view> common;
        std::set_intersection(numbers.begin(), numbers.end(), winningNumbers.begin(), winningNumbers.end(), std::back_inserter(common));
        if (common.size() > 0)
        {
            result = std::pow(2, common.size() - 1);
        }
        return result;
    }

    int card_matches(const std::string& line)
    {
        int result = 0;
        auto [x, data] = divide(":", line);
        auto [winningNumbersStr, numbersStr] = divide("|", data);
        auto winningNumbers = split_set(" ", trim_left(winningNumbersStr));
        auto numbers = split_set(" ", trim_left(numbersStr));
        std::vector<std::string_view> common;
        std::set_intersection(numbers.begin(), numbers.end(), winningNumbers.begin(), winningNumbers.end(), std::back_inserter(common));
        return common.size();
        
    }

	void Part1()
	{
        int result = 0;
        std::ifstream input("input4.txt");
        std::string line;
        while (std::getline(input, line))
        {
            result += card_score(line);
        }

        std::cout << result << std::endl;
	}


	void Part2()
	{
        int result = 0;
        std::ifstream input("input4.txt");
        std::string line;
        std::vector<int> scores;
        scores.reserve(220);
        while (std::getline(input, line))
        {
            scores.emplace_back(card_matches(line));
        }

        std::vector<int> times;
        times.resize(scores.size(), 1);
        
        for (int i = 0; i < scores.size(); ++i)
        {
            int numTimes = times[i];
            for (int j = 0; j < scores[i]; ++j)
            {
                times[i + j + 1] += numTimes;
            }
        }

        for (int i = 0; i < scores.size(); ++i)
        {
            result += times[i];
        }

        std::cout << result << std::endl;
	}
    */
}