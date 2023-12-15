#include "StdAfx.h"
#include "Challenge11.h"

namespace challenge11
{
    using Bid = int;
    using Points = long long;

	void Part2()
	{
        using Cost = long long;
        std::ifstream input("input11.txt");
        std::string line;
        std::array<Cost, 150> columnCost;
        columnCost.fill(1000000);
        std::array<Cost, 150> rowCost;
        rowCost.fill(1000000);
        int y = 0;
        std::vector<std::pair<int, int>> galaxies;
        while (std::getline(input, line))
        {
            int x = 0;
            for (char c : line)
            {
                switch (c)
                {
                case '.':
                    break;
                case '#':
                    galaxies.emplace_back(x, y);
                    columnCost[x] = 1;
                    rowCost[y] = 1;
                    break;
                }
                ++x;
            }
            ++y;
        }

        Cost result = 0;
        for (int i = 0; i < galaxies.size(); ++i)
        {
            auto sourceGalaxy = galaxies[i];
            for (int j = i + 1; j < galaxies.size(); ++j)
            {
                auto destGalaxy = galaxies[j];
                int c = std::accumulate(columnCost.begin() + std::min(sourceGalaxy.first, destGalaxy.first), columnCost.begin() + std::max(sourceGalaxy.first, destGalaxy.first), 0);
                int r = std::accumulate(rowCost.begin() + std::min(sourceGalaxy.second, destGalaxy.second), rowCost.begin() + std::max(sourceGalaxy.second, destGalaxy.second), 0);
                result += (c + r);
            }
        }


        std::cout << result << std::endl;
	}

    
	void Part1()
	{
        std::ifstream input("input11.txt");
        std::string line;
        std::array<int, 150> columnCost;
        columnCost.fill(2);
        std::array<int, 150> rowCost;
        rowCost.fill(2);
        int y = 0;
        std::vector<std::pair<int, int>> galaxies;
        while (std::getline(input, line))
        {
            int x = 0;
            for (char c : line)
            {
                switch (c)
                {
                case '.':
                    break;
                case '#':
                    galaxies.emplace_back(x, y);
                    columnCost[x] = 1;
                    rowCost[y] = 1;
                    break;
                }
                ++x;
            }
            ++y;
        }

        int result = 0;
        for (int i = 0; i < galaxies.size(); ++i)
        {
            auto sourceGalaxy = galaxies[i];
            for (int j = i+1; j < galaxies.size(); ++j)
            {
                auto destGalaxy = galaxies[j];
                int c = std::accumulate(columnCost.begin() + std::min(sourceGalaxy.first, destGalaxy.first), columnCost.begin() + std::max(sourceGalaxy.first, destGalaxy.first), 0);
                int r = std::accumulate(rowCost.begin() + std::min(sourceGalaxy.second, destGalaxy.second), rowCost.begin() + std::max(sourceGalaxy.second, destGalaxy.second), 0);
                result += (c + r);
            }
        }


        std::cout << result << std::endl;
	}
}