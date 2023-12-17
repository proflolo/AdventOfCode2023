#include "StdAfx.h"
#include "Challenge14.h"

namespace challenge14
{
    enum class Type
    {
        RoundRock,
        CubeRock,
        Empty
    };
	void Part1()
	{
        std::ifstream input("input14.txt");
        std::string line;

        long long result = 0;

        std::vector<std::vector<Type>> grid; //Transposat
        while (std::getline(input, line))
        {
            if (grid.size() == 0)
            {
                grid.resize(line.size());
            }
            size_t i = 0;
            for (char c : line)
            {
                switch (c)
                {
                case '#': grid[i].emplace_back(Type::CubeRock); break;
                case 'O': grid[i].emplace_back(Type::RoundRock); break;
                case '.': grid[i].emplace_back(Type::Empty); break;
                }
                i++;
            }
        }

        for (const auto& column : grid)
        {
            uint64 totalWeigth = 0;
            uint64 weigth = column.size();
            size_t i = 0;
            for (Type t : column)
            {
                switch (t)
                {
                case Type::RoundRock: 
                {
                    totalWeigth += weigth;
                    weigth--;
                }
                break;
                case Type::CubeRock:
                {
                    weigth = (column.size() - i);
                    weigth--;
                }
                break;
                case Type::Empty:
                    break;
                }
                ++i;
            }
            result += totalWeigth;
        }
        
        
        std::cout << result << std::endl;
	}

    using Grid = std::vector<std::vector<Type>>;
    std::map<Grid, Grid> cache;

    template<typename Swap, typename Get>
    void Cycle(size_t i_size, Grid& io_grid, Swap swap, Get get)
    {
        for (size_t i = 0; i < io_grid.size(); ++i)
        {
            size_t lastEmpty = 0;
            for (size_t j = 0; j < io_grid[i].size(); ++j)
            {
                Type t = get(io_grid, i, j);// 
                switch (t)
                {
                case Type::RoundRock:
                {
                    swap(io_grid, i, j, lastEmpty);
                    ++lastEmpty;
                }
                break;
                case Type::CubeRock:
                {
                    //io_grid[i][j] = Type::CubeRock;
                    lastEmpty = j + 1;
                }
                break;
                case Type::Empty:
                    break;
                }
            }
        }
    }
    

    void CycleNorth(Grid& io_grid)
    {
        Cycle(io_grid.size(), io_grid, [](Grid& io_grid, size_t i, size_t j, size_t lastEmpty)
            {
                io_grid[i][j] = Type::Empty;
                io_grid[i][lastEmpty] = Type::RoundRock;
            },
            [](const Grid& io_grid, size_t i, size_t j)
            {
                return io_grid[i][j];
            });
    }

    void CycleWest(Grid& io_grid)
    {
        Cycle(io_grid.size(), io_grid, [](Grid& io_grid, size_t i, size_t j, size_t lastEmpty)
            {
                io_grid[j][i] = Type::Empty;
                io_grid[lastEmpty][i] = Type::RoundRock;
            },
            [](const Grid& io_grid, size_t i, size_t j)
            {
                return io_grid[j][i];
            });
    }

    void CycleSouth(Grid& io_grid)
    {
        Cycle(io_grid.size(), io_grid, [](Grid& io_grid, size_t i, size_t j, size_t lastEmpty)
            {
                io_grid[i][io_grid.size() - (j + 1)] = Type::Empty;
                io_grid[i][io_grid.size() - (lastEmpty+1)] = Type::RoundRock;
            },
            [](const Grid& io_grid, size_t i, size_t j)
            {
                return io_grid[i][io_grid.size() - (j + 1)];
            });
    }

    void CycleEast(Grid& io_grid)
    {
        Cycle(io_grid.size(), io_grid, [](Grid& io_grid, size_t i, size_t j, size_t lastEmpty)
            {
                io_grid[io_grid.size() - (j + 1)][i] = Type::Empty;
                io_grid[io_grid.size() - (lastEmpty+1)][i] = Type::RoundRock;
            },
            [](const Grid& io_grid, size_t i, size_t j)
            {
                return io_grid[io_grid.size() - (j + 1)][i];
            });
    }

    void PrintGrid(const Grid& i_grid)
    {
        for (size_t i = 0; i < i_grid.size(); ++i)
        {
            for (size_t j = 0; j < i_grid[i].size(); ++j)
            {
                switch (i_grid[j][i])
                {
                case Type::RoundRock:
                    std::cout << 'O';
                    break;
                case Type::CubeRock:
                    std::cout << '#';
                    break;
                case Type::Empty:
                    std::cout << '.';
                    break;
                }
            }
            std::cout << std::endl;
        }
    }

    void Cycle(Grid& io_grid)
    {
        //PrintGrid(io_grid);
        //std::cout << std::endl << "North: " << std::endl;
        CycleNorth(io_grid);
        //PrintGrid(io_grid);
        //std::cout << std::endl << "West: " << std::endl;
        CycleWest(io_grid);
        //PrintGrid(io_grid);
        //std::cout << std::endl << "South: " << std::endl;
        CycleSouth(io_grid);
        //PrintGrid(io_grid);
        //std::cout << std::endl << "East: " << std::endl;
        CycleEast(io_grid);
        //PrintGrid(io_grid);
        //std::cout << std::endl;
    }

    void Part2()
    {
        std::ifstream input("input14_sample.txt");
        std::string line;

        long long result = 0;

       
        std::vector<std::vector<Type>> grid; //Transposat
        while (std::getline(input, line))
        {
            if (grid.size() == 0)
            {
                grid.resize(line.size());
            }
            size_t i = 0;
            for (char c : line)
            {
                switch (c)
                {
                case '#': grid[i].emplace_back(Type::CubeRock); break;
                case 'O': grid[i].emplace_back(Type::RoundRock); break;
                case '.': grid[i].emplace_back(Type::Empty); break;
                }
                i++;
            }
        }
        
        std::map<Grid, size_t> mapCache;
        size_t numSteps = 0;
        const size_t k_cycles = 100000000;
        for (size_t i = 0; i < k_cycles; ++i)
        {
            auto it = mapCache.find(grid);
            if (it != mapCache.end())
            {
                size_t targetSteps = k_cycles;
                targetSteps = targetSteps - it->second;
                auto cycleLen = i - it->second;
                auto remaining = targetSteps % cycleLen;
                //Cycled!!!
                for (size_t a = 0; a < remaining; ++a)
                {
                    Cycle(grid);
                    PrintGrid(grid);
                    std::cout << std::endl;
                }
                break;
            }
            else
            {
                mapCache.emplace(grid, i);
            }
            Cycle(grid);
        }


        std::cout << result << std::endl;
    }
}