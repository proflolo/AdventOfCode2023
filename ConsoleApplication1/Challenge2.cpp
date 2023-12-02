#include "StdAfx.h"
#include "Challenge2.h"

namespace challenge2
{
	void Part1()
	{
        int result = 0;
        std::ifstream input("input2.txt");
        std::string line;
        while (std::getline(input, line))
        {
            auto [gameStr, handfulStr] = divide(":", line);
            auto [x, gameIdStr] = divide(" ", gameStr);
            int gameId = stoi(gameIdStr);

            bool valid = true;
            for (const std::string_view& handful : split(";", handfulStr))
            {
                for (const std::string_view& colorDraw : split(",", handful))
                {
                    auto [numberStr, colorStr] = divide(" ", trim_left(colorDraw));
                    int num = stoi(numberStr);
                    if (colorStr == "red") { valid = valid && (num <= 12); }
                    else if (colorStr == "blue") { valid = valid && (num <= 14); }
                    else if (colorStr == "green") { valid = valid && (num <= 13); }
                    else { assert(false); }
                }
            }
            if (valid)
            {
                result += gameId;
            }
        }

        std::cout << result << std::endl;
	}


	void Part2()
	{
        int result = 0;
        std::ifstream input("input2.txt");
        std::string line;
        while (std::getline(input, line))
        {
            auto [gameStr, handfulStr] = divide(":", line);
            auto [x, gameIdStr] = divide(" ", gameStr);
            int gameId = stoi(gameIdStr);

            int maxRed = 0;
            int maxGreen = 0;
            int maxBlue = 0;
            for (const std::string_view& handful : split(";", handfulStr))
            {
                for (const std::string_view& colorDraw : split(",", handful))
                {
                    auto [numberStr, colorStr] = divide(" ", trim_left(colorDraw));
                    int num = stoi(numberStr);
                    if (colorStr == "red") { maxRed = std::max(maxRed, num); }
                    else if (colorStr == "blue") { maxBlue = std::max(maxBlue, num); }
                    else if (colorStr == "green") { maxGreen = std::max(maxGreen, num); }
                    else { assert(false); }
                }
            }
            result += maxRed * maxGreen * maxBlue;

        }

        std::cout << result << std::endl;
	}
}