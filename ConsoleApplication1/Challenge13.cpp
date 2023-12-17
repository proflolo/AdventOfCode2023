#include "StdAfx.h"
#include "Challenge13.h"

namespace challenge13
{
    uint64 FindReflection(const std::vector<uint64>& i_horizontal)
    {
        for (size_t i = 0; i < i_horizontal.size(); ++i)
        {
            bool reflects = true;
            bool processed = false;
            for (size_t j = 0; ((i + j + 1) < i_horizontal.size()) && i >= j && reflects; ++j)
            {
                processed = true;
                reflects = reflects && i_horizontal[i - j] == i_horizontal[i + j + 1];
            }
            if (reflects && processed)
            {
                return i+1;
            }
        }
        return 0;
    }

    

    uint64 ProcessReflections(const std::vector<uint64>& i_horizontal, const std::vector<uint64>& i_vertical)
    {
        assert(i_horizontal.size() <= 64 && i_vertical.size() <= 64);
        uint64 verticalValue = 0;
        uint64 horizontalValue = 0;
        //Find reflections
        horizontalValue = FindReflection(i_horizontal);
        verticalValue = FindReflection(i_vertical);

        return verticalValue + 100 * horizontalValue;
    }
	void Part1()
	{
        std::ifstream input("input13.txt");
        std::string line;

        long long result = 0;

        std::vector<uint64> horizontal;
        std::vector<uint64> vertical;
        while (std::getline(input, line))
        {
            if (line.size() == 0)
            {
                result += ProcessReflections(horizontal, vertical);
                horizontal.clear();
                vertical.clear();
                continue;
            }
            if (vertical.size() == 0)
            {
                vertical.resize(line.size());
                std::fill(vertical.begin(), vertical.end(), 0);
            }
            uint64 rowValue = 0;
            size_t i = 0;
            for (char c : line)
            {
                uint64 value = 0;
                switch (c)
                {
                case '.':
                    value = 0;
                    break;
                case '#':
                    value = 1;
                    break;
                }
                rowValue = (rowValue << 1) + value;
                vertical[i] = (vertical[i] << 1) + value;
                i++;
            }
            horizontal.emplace_back(rowValue);
        }
        result += ProcessReflections(horizontal, vertical);
        //37718
        std::cout << result << std::endl;
	}

    uint64 FindReflectionWithSmudge(const std::vector<uint64>& i_horizontal)
    {
        for (size_t i = 0; i < i_horizontal.size(); ++i)
        {
            uint64 smudges = 0;
            bool processed = false;
            for (size_t j = 0; ((i + j + 1) < i_horizontal.size()) && i >= j && smudges <= 1; ++j)
            {
                processed = true;
                uint64 v1 = i_horizontal[i - j];
                uint64 v2 = i_horizontal[i + j + 1];
                uint64 r = ((v1 & ~v2) | (~v1 & v2));
                int ans = 0;
                for (int i = 0; i <= 63; i++) ans += ((r >> i) & 1);

                if (v1 == v2)
                {
                    //reflexat, move on
                }
                else if (ans == 1)
                {
                    smudges++;
                }
                else
                {
                    smudges = 999;
                }
            }
            if (smudges == 1 && processed)
            {
                return i + 1;
            }
        }
        return 0;
    }

    uint64 ProcessReflectionsWithSmudge(const std::vector<uint64>& i_horizontal, const std::vector<uint64>& i_vertical)
    {
        assert(i_horizontal.size() <= 64 && i_vertical.size() <= 64);
        uint64 verticalValue = 0;
        uint64 horizontalValue = 0;
        //Find reflections
        horizontalValue = FindReflectionWithSmudge(i_horizontal);
        verticalValue = FindReflectionWithSmudge(i_vertical);

        return verticalValue + 100 * horizontalValue;
    }

    void Part2()
    {
        std::ifstream input("input13.txt");
        std::string line;

        long long result = 0;

        std::vector<uint64> horizontal;
        std::vector<uint64> vertical;
        while (std::getline(input, line))
        {
            if (line.size() == 0)
            {
                result += ProcessReflectionsWithSmudge(horizontal, vertical);
                horizontal.clear();
                vertical.clear();
                continue;
            }
            if (vertical.size() == 0)
            {
                vertical.resize(line.size());
                std::fill(vertical.begin(), vertical.end(), 0);
            }
            uint64 rowValue = 0;
            size_t i = 0;
            for (char c : line)
            {
                uint64 value = 0;
                switch (c)
                {
                case '.':
                    value = 0;
                    break;
                case '#':
                    value = 1;
                    break;
                }
                rowValue = (rowValue << 1) + value;
                vertical[i] = (vertical[i] << 1) + value;
                i++;
            }
            horizontal.emplace_back(rowValue);
        }
        result += ProcessReflectionsWithSmudge(horizontal, vertical);
        //40995
        std::cout << result << std::endl;
    }
}