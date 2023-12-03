#include "StdAfx.h"
#include "Challenge3.h"

namespace challenge3
{
    struct rect
    {
        int x, y, width, height;
        
    };

    bool intersects(const rect& r1, const rect& r2)
    {
        return r1.x < (r2.x + r2.width) && (r1.x + r1.width) > r2.x &&
            r1.y < (r2.y + r2.height) && (r1.y + r1.height) > r2.y;
    }

    rect from_number(int line, int pos, int numSize)
    {
        return rect{ pos, line, numSize, 1 };
    }

    rect from_symbol(int line, int pos)
    {
        return rect{ pos-1, line-1, 3, 3 };
    }

	void Part1()
	{
        int result = 0;
        std::ifstream input("input3.txt");
        std::string line;
        std::regex numRegex("[0-9]+");
        std::regex symbolRegex("[^0-9^\\.]");
        std::vector<std::pair<rect, int>> numbers;
        std::vector<rect> symbols;
        int lineNum = 0;
        while (std::getline(input, line))
        {
            std::match_results<std::string_view::iterator> m;
            std::string_view copy = line;
            while (regex_search(copy.begin(), copy.end(), m, numRegex))  // <-- use it here to get the match
            {
                std::string_view match = copy.substr(m.position(), m.length());
                int value = stoi(match);
                numbers.emplace_back(from_number(lineNum, m.position() + (line.length() - copy.length()), m.length()), value);
                copy = copy.substr(m.position() + m.length()); // <-- just break the match
            }

            copy = line;
            while (regex_search(copy.begin(), copy.end(), m, symbolRegex))  // <-- use it here to get the match
            {
                std::string_view match = copy.substr(m.position(), m.length());
                symbols.emplace_back(from_symbol(lineNum, m.position() + (line.length() - copy.length())));
                copy = copy.substr(m.position() + m.length()); // <-- just break the match
            }
            lineNum++;
        }

        for (const auto& number : numbers)
        {
            bool isValid = false;
            for (const auto& symbol : symbols)
            {
                if (intersects(number.first, symbol))
                {
                    isValid = true;
                    break;
                }
            }

            if (isValid)
            {
                result += number.second;
            }
        }

        std::cout << result << std::endl;
	}


	void Part2()
	{
        int result = 0;
        std::ifstream input("input3.txt");
        std::string line;
        std::regex numRegex("[0-9]+");
        std::regex symbolRegex("\\*");
        std::vector<std::pair<rect, int>> numbers;
        std::vector<rect> gears;
        int lineNum = 0;
        while (std::getline(input, line))
        {
            std::match_results<std::string_view::iterator> m;
            std::string_view copy = line;
            while (regex_search(copy.begin(), copy.end(), m, numRegex))  // <-- use it here to get the match
            {
                std::string_view match = copy.substr(m.position(), m.length());
                int value = stoi(match);
                numbers.emplace_back(from_number(lineNum, m.position() + (line.length() - copy.length()), m.length()), value);
                copy = copy.substr(m.position() + m.length()); // <-- just break the match
            }

            copy = line;
            while (regex_search(copy.begin(), copy.end(), m, symbolRegex))  // <-- use it here to get the match
            {
                std::string_view match = copy.substr(m.position(), m.length());
                gears.emplace_back(from_symbol(lineNum, m.position() + (line.length() - copy.length())));
                copy = copy.substr(m.position() + m.length()); // <-- just break the match
            }
            lineNum++;
        }

        for (const auto& gear : gears)
        {
            bool isValid = false;
            int numIntersections = 0;
            int gearValue = 1;
            for (const auto& number : numbers)
            {
                if (intersects(number.first, gear))
                {
                    gearValue *= number.second;
                    numIntersections++;
                    if (numIntersections >= 3)
                    {
                        break;
                    }
                }
            }

            if (numIntersections == 2)
            {
                result += gearValue;
            }
        }

        std::cout << result << std::endl;
	}
}