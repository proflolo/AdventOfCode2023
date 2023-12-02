#include "StdAfx.h"
#include "Challenge1.h"

namespace challenge1
{
	void Part1()
	{
        std::ifstream input("input1_2.txt");
        std::string line;
        int total = 0;
        while (std::getline(input, line))
        {
            auto firstPos = line.find_first_of("0123456789", 0);
            auto lastPos = line.find_last_of("0123456789");
            auto c1 = line[firstPos] - '0';
            auto c2 = line[lastPos] - '0';
            int sum = c1 * 10 + c2;
            total += sum;
        }

        std::cout << total << std::endl;
	}


    int string_to_number(const std::string& i_in)
    {
        if (i_in == "1") { return 1; }
        else if (i_in == "2") { return 2; }
        else if (i_in == "3") { return 3; }
        else if (i_in == "4") { return 4; }
        else if (i_in == "5") { return 5; }
        else if (i_in == "6") { return 6; }
        else if (i_in == "7") { return 7; }
        else if (i_in == "8") { return 8; }
        else if (i_in == "9") { return 9; }
        else if (i_in == "one") { return 1; }
        else if (i_in == "two") { return 2; }
        else if (i_in == "three") { return 3; }
        else if (i_in == "four") { return 4; }
        else if (i_in == "five") { return 5; }
        else if (i_in == "six") { return 6; }
        else if (i_in == "seven") { return 7; }
        else if (i_in == "eight") { return 8; }
        else if (i_in == "nine") { return 9; }
        return 0;
    }


	void Part2()
	{
        std::ifstream input("input1_2.txt");
        std::string line;
        int total = 0;
        std::regex r("1|2|3|4|5|6|7|8|9|0|one|two|three|four|five|six|seven|eight|nine");
        while (std::getline(input, line))
        {
            std::smatch m; // <-- need a match object
            std::string copy = line;
            std::string firstMatch;
            std::string lastMatch;
            while (regex_search(copy, m, r))  // <-- use it here to get the match
            {
                std::string match = copy.substr(m.position(), m.length());
                if (firstMatch.length() == 0)
                {
                    firstMatch = match;
                }
                lastMatch = match;
                copy = copy.substr(m.position() + 1); // <-- just break the match
            }
            int value = string_to_number(firstMatch) * 10 + string_to_number(lastMatch);
            total += value;
        }
        std::cout << total << std::endl;
	}
}