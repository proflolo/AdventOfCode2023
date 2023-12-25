#include "StdAfx.h"
#include "Challenge15.h"

namespace challenge16
{
  
    enum class Direction
    {
        Left,
        Right,
        Down,
        Up
    };
    using Ray = std::tuple<int64_t, int64_t, Direction>;

    using Cell = std::pair<char, bool>;
    std::vector<Ray> ProcessRay(std::vector<std::vector<Cell>>& i_grid, Ray i_ray, uint64& o_result)
    {
        std::vector<Ray> result;
        auto i_row = std::get<0>(i_ray);
        auto i_col = std::get<1>(i_ray);
        auto direction = std::get<2>(i_ray);
        if (i_row < 0 || i_row >= i_grid.size())
        {
            return result;
        }
        if (i_col < 0 || i_col >= i_grid[i_row].size())
        {
            return result;
        }
        Cell& cellRef = i_grid[i_row][i_col];
        

        Ray leftRay = Ray{ i_row, i_col - 1, Direction::Left };
        Ray rightRay = Ray{ i_row, i_col + 1, Direction::Right };
        Ray upRay = Ray{ i_row - 1, i_col, Direction::Up };
        Ray downRay = Ray{ i_row + 1, i_col, Direction::Down };

        switch (cellRef.first)
        {
        case '.':
            switch (direction)
            {
            case challenge16::Direction::Left:
                result.emplace_back(leftRay);
                break;
            case challenge16::Direction::Right:
                result.emplace_back(rightRay);
                break;
            case challenge16::Direction::Down:
                result.emplace_back(downRay);
                break;
            case challenge16::Direction::Up:
                result.emplace_back(upRay);
                break;
            default:
                assert(false);
                break;
            }
            break;
        case '/':
            switch (direction)
            {
            case challenge16::Direction::Left:
                result.emplace_back(downRay);
                break;
            case challenge16::Direction::Right:
                result.emplace_back(upRay);

                break;
            case challenge16::Direction::Down:
                result.emplace_back(leftRay);

                break;
            case challenge16::Direction::Up:
                result.emplace_back(rightRay);

                break;
            default:
                assert(false);
                break;
            }
            break;
        case '\\':
            switch (direction)
            {
            case challenge16::Direction::Left:
                result.emplace_back(upRay);

                break;
            case challenge16::Direction::Right:
                result.emplace_back(downRay);

                break;
            case challenge16::Direction::Down:
                result.emplace_back(rightRay);

                break;
            case challenge16::Direction::Up:
                result.emplace_back(leftRay);

                break;
            default:
                assert(false);
                break;
            }
            break;
        case '-':
            if (!cellRef.second)
            {
                switch (direction)
                {
                case challenge16::Direction::Left:
                    result.emplace_back(leftRay);

                    break;
                case challenge16::Direction::Right:
                    result.emplace_back(rightRay);

                    break;
                case challenge16::Direction::Down:
                    result.emplace_back(rightRay);
                    result.emplace_back(leftRay);

                    break;
                case challenge16::Direction::Up:
                    result.emplace_back(leftRay);
                    result.emplace_back(rightRay);

                    break;
                default:
                    assert(false);
                    break;
                }
            }
            break;
        case '|':
            if (!cellRef.second)
            {
                switch (direction)
                {
                case challenge16::Direction::Left:
                    result.emplace_back(upRay);
                    result.emplace_back(downRay);

                    break;
                case challenge16::Direction::Right:
                    result.emplace_back(downRay);
                    result.emplace_back(upRay);

                    break;
                case challenge16::Direction::Down:
                    result.emplace_back(downRay);

                    break;
                case challenge16::Direction::Up:
                    result.emplace_back(upRay);

                    break;
                default:
                    assert(false);
                    break;
                }
            }
            break;
        default:
            assert(false);
            break;
        }


        if (!cellRef.second)
        {
            cellRef.second = true;
            o_result++;
        }
        return result;
    }

    

	void Part1()
	{
        std::ifstream input("input16.txt");
        std::string line;

        uint64 result = 0;

        std::vector<std::vector<Cell>> grid;
        while (std::getline(input, line))
        {
            std::vector<Cell> row;
            for (char c : line)
            {
                row.emplace_back(c, false);
            }
            grid.emplace_back(std::move(row));
        }

        std::vector<Ray> rays;

        rays.emplace_back(0, 0, Direction::Right);
        while (!rays.empty())
        {
            Ray r = rays.back();
            rays.pop_back();
            auto moreRays = ProcessRay(grid, r, result);
            rays.insert(rays.end(), moreRays.begin(), moreRays.end());
        }
        
        std::cout << result << std::endl;
	}

    uint64 Process(const std::vector<std::vector<Cell>>& i_grid, Ray i_ray)
    {
        uint64 currentResult = 0;
        std::vector<Ray> rays;
        auto copy = i_grid;
        rays.emplace_back(i_ray);
        while (!rays.empty())
        {
            Ray r = rays.back();
            rays.pop_back();
            auto moreRays = ProcessRay(copy, r, currentResult);
            rays.insert(rays.end(), moreRays.begin(), moreRays.end());
        }
        return currentResult;
    }
   
    void Part2()
    {
        std::ifstream input("input16.txt");
        std::string line;

        uint64 result = 0;

        std::vector<std::vector<Cell>> grid;
        while (std::getline(input, line))
        {
            std::vector<Cell> row;
            for (char c : line)
            {
                row.emplace_back(c, false);
            }
            grid.emplace_back(std::move(row));
        }

        size_t height = grid.size();
        size_t width = grid[0].size();
        for (size_t i = 0; i < height; ++i)
        {
            Ray r1 = Ray(i, 0, Direction::Right);
            uint64 v1 = Process(grid, r1);
            
            Ray r2 = Ray(i, width - 1, Direction::Left);
            uint64 v2 = Process(grid, r2);

            result = std::max(result, std::max(v1, v2));
        }

        for (size_t i = 0; i < width; ++i)
        {
            Ray r1 = Ray(0, i, Direction::Down);
            uint64 v1 = Process(grid, r1);

            Ray r2 = Ray(height - 1, i, Direction::Up);
            uint64 v2 = Process(grid, r2);

            result = std::max(result, std::max(v1, v2));
        }

        std::cout << result << std::endl;
    }
}