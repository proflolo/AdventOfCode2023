#include "StdAfx.h"
#include "Challenge10.h"

namespace challenge10
{
    
    using Pos = std::pair<size_t, size_t>;

    namespace p1
    {
        struct TileFlags {
            bool north : 1 = false;
            bool south : 1 = false;
            bool east : 1 = false;
            bool west : 1 = false;
        };
        union Tile
        {
            TileFlags flags;
            char value = 0;
        };
        using PipeMap = std::array<std::array<Tile, 150>, 150>;

        bool inline CanGoNorth(const auto& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.first == 0)
            {
                return false;
            }
            else
            {
                return i_pipeMap[i_pos.first][i_pos.second].flags.north && i_pipeMap[i_pos.first - 1][i_pos.second].flags.south;
            }
        }

        bool inline CanGoSouth(const auto& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.first == i_pipeMap.size() - 1)
            {
                return false;
            }
            else
            {
                return i_pipeMap[i_pos.first][i_pos.second].flags.south && i_pipeMap[i_pos.first + 1][i_pos.second].flags.north;
            }
        }

        bool inline CanGoEast(const auto& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.second == i_pipeMap[i_pos.first].size() - 1)
            {
                return false;
            }
            else
            {
                return i_pipeMap[i_pos.first][i_pos.second].flags.east && i_pipeMap[i_pos.first][i_pos.second + 1].flags.west;
            }
        }

        bool inline CanGoWest(const auto& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.second == 0)
            {
                return false;
            }
            else
            {
                return i_pipeMap[i_pos.first][i_pos.second].flags.west && i_pipeMap[i_pos.first][i_pos.second - 1].flags.east;
            }
        }
    }
    namespace p2
    {
        struct TileFlags {
            bool north : 1 = false;
            bool south : 1 = false;
            bool east : 1 = false;
            bool west : 1 = false;
        };
        struct Tile
        {
            TileFlags flags;
            TileFlags comingFrom;
        };
        using PipeMap = std::array<std::array<Tile, 150>, 150>;

        bool inline CanGoNorth(const auto& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.first == 0)
            {
                return false;
            }
            else
            {
                return !i_pipeMap[i_pos.first][i_pos.second].comingFrom.north && i_pipeMap[i_pos.first][i_pos.second].flags.north && i_pipeMap[i_pos.first - 1][i_pos.second].flags.south;
            }
        }

        bool inline CanGoSouth(const auto& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.first == i_pipeMap.size() - 1)
            {
                return false;
            }
            else
            {
                return !i_pipeMap[i_pos.first][i_pos.second].comingFrom.south && i_pipeMap[i_pos.first][i_pos.second].flags.south && i_pipeMap[i_pos.first + 1][i_pos.second].flags.north;
            }
        }

        bool inline CanGoEast(const PipeMap& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.second == i_pipeMap[i_pos.first].size() - 1)
            {
                return false;
            }
            else
            {
                return !i_pipeMap[i_pos.first][i_pos.second].comingFrom.east && i_pipeMap[i_pos.first][i_pos.second].flags.east && i_pipeMap[i_pos.first][i_pos.second + 1].flags.west;
            }
        }

        bool inline CanGoWest(const PipeMap& i_pipeMap, const Pos& i_pos)
        {
            if (i_pos.second == 0)
            {
                return false;
            }
            else
            {
                return !i_pipeMap[i_pos.first][i_pos.second].comingFrom.west && i_pipeMap[i_pos.first][i_pos.second].flags.west && i_pipeMap[i_pos.first][i_pos.second - 1].flags.east;
            }
        }
    }

    using Dist = size_t;
    



    

    void Part1()
    {
        using namespace p1;
        std::ifstream input("input10.txt");
        std::string entryLine;
        PipeMap pipeMap{};
        std::array<std::array<Dist, 150>, 150> distances {};
        size_t line = 0;
        Pos startingPos;
        std::vector<Pos> pendingToProcess;
        while (std::getline(input, entryLine))
        {
            assert(entryLine.size() < 150);
            for (size_t i = 0; i < entryLine.size(); ++i)
            {
                char c = entryLine[i];
                switch (c)
                {
                case '|': pipeMap[line][i].flags = { 1,1,0,0 }; break;
                case '-': pipeMap[line][i].flags = { 0,0,1,1 }; break;
                case 'L': pipeMap[line][i].flags = { 1,0,1,0 }; break;
                case 'J': pipeMap[line][i].flags = { 1,0,0,1 }; break;
                case '7': pipeMap[line][i].flags = { 0,1,0,1 }; break;
                case 'F': pipeMap[line][i].flags = { 0,1,1,0 }; break;
                case '.': pipeMap[line][i].flags = { 0,0,0,0 }; break;
                case 'S':
                    pipeMap[line][i].flags = { 1,1,1,1 };
                    distances[line][i] = 1;
                    startingPos = { line, i };
                    break;
                }
            }
            ++line;
        }
        Dist result = 0;

        pendingToProcess.emplace_back(startingPos);
        bool finished = false;
        while (!finished)
        {
            std::vector<Pos> nextPendingToProcess;
            for (Pos p : pendingToProcess)
            {
                Dist d = distances[p.first][p.second];
                if (CanGoNorth(pipeMap, p))
                {
                    Dist& current = distances[p.first - 1][p.second];
                    nextPendingToProcess.emplace_back(std::make_pair(p.first - 1, p.second));
                    if (current > 0)
                    {
                        result = current-1;
                        finished = true;
                        break;
                    }
                    current = d + 1;
                }
                if (CanGoSouth(pipeMap, p))
                {
                    Dist& current = distances[p.first + 1][p.second];
                    nextPendingToProcess.emplace_back(std::make_pair(p.first + 1, p.second));
                    if (current > 0)
                    {
                        result = current-1;
                        finished = true;
                        break;
                    }
                    current = d + 1;
                }
                if (CanGoEast(pipeMap, p))
                {
                    Dist& current = distances[p.first][p.second + 1];
                    nextPendingToProcess.emplace_back(std::make_pair(p.first, p.second+1));
                    if (current > 0)
                    {
                        result = current-1;
                        finished = true;
                        break;
                    }
                    current = d + 1;
                }
                if (CanGoWest(pipeMap, p))
                {
                    Dist& current = distances[p.first][p.second - 1];
                    nextPendingToProcess.emplace_back(std::make_pair(p.first, p.second-1));
                    if (current > 0)
                    {
                        result = current-1;
                        finished = true;
                        break;
                    }
                    current = d + 1;
                }
                pipeMap[p.first][p.second].value = 0;//so we never check it again
            }
            nextPendingToProcess.swap(pendingToProcess);
        }
        std::cout << result << std::endl;
        
    }
   
	void Part2()
	{
        using namespace p2;
        std::ifstream input("input10_sample.txt");
        std::string entryLine;
        PipeMap pipeMap{};
        std::array<std::array<std::vector<Pos>, 150>, 150> path {};
        size_t line = 0;
        Pos startingPos;
        std::vector<Pos> pendingToProcess;
        while (std::getline(input, entryLine))
        {
            assert(entryLine.size() < 150);
            for (size_t i = 0; i < entryLine.size(); ++i)
            {
                char c = entryLine[i];
                switch (c)
                {
                case '|': pipeMap[line][i].flags = { 1,1,0,0 }; break;
                case '-': pipeMap[line][i].flags = { 0,0,1,1 }; break;
                case 'L': pipeMap[line][i].flags = { 1,0,1,0 }; break;
                case 'J': pipeMap[line][i].flags = { 1,0,0,1 }; break;
                case '7': pipeMap[line][i].flags = { 0,1,0,1 }; break;
                case 'F': pipeMap[line][i].flags = { 0,1,1,0 }; break;
                case '.': pipeMap[line][i].flags = { 0,0,0,0 }; break;
                case 'S':
                    pipeMap[line][i].flags = { 1,1,1,1 };
                    startingPos = { line, i };
                    break;
                }
            }
            ++line;
        }
        std::vector<Pos> loopPath;
        pendingToProcess.emplace_back(startingPos);
        path[startingPos.first][startingPos.second].emplace_back(startingPos);
        bool finished = false;
        while (!finished)
        {
            std::vector<Pos> nextPendingToProcess;
            for (Pos p : pendingToProcess)
            {
                const std::vector<Pos>& myPathSoFar = path[p.first][p.second];
                if (CanGoNorth(pipeMap, p))
                {
                    TileFlags& coming = pipeMap[p.first - 1][p.second].comingFrom;
                    std::vector<Pos>& pathSoFar = path[p.first - 1][p.second];
                    coming.south = 1;
                    nextPendingToProcess.emplace_back(std::make_pair(p.first - 1, p.second));
                    if (pathSoFar.size() > 0)
                    {
                        std::copy(pathSoFar.begin(), pathSoFar.end(), std::back_inserter(loopPath));
                        std::copy(myPathSoFar.rbegin(), myPathSoFar.rend(), std::back_inserter(loopPath));
                        finished = true;
                        break;
                    }
                    pathSoFar.insert(pathSoFar.end(), myPathSoFar.begin(), myPathSoFar.end());
                    pathSoFar.emplace_back(std::make_pair(p.first - 1, p.second));
                }
                if (CanGoSouth(pipeMap, p))
                {
                    TileFlags& coming = pipeMap[p.first + 1][p.second].comingFrom;
                    std::vector<Pos>& pathSoFar = path[p.first + 1][p.second];
                    coming.north = 1;
                    nextPendingToProcess.emplace_back(std::make_pair(p.first + 1, p.second));
                    if (pathSoFar.size() > 0)
                    {
                        finished = true;
                        std::copy(pathSoFar.begin(), pathSoFar.end(), std::back_inserter(loopPath));
                        std::copy(myPathSoFar.rbegin(), myPathSoFar.rend(), std::back_inserter(loopPath));
                        break;
                    }
                    pathSoFar.insert(pathSoFar.end(), myPathSoFar.begin(), myPathSoFar.end());
                    pathSoFar.emplace_back(std::make_pair(p.first + 1, p.second));
                    
                }
                if (CanGoEast(pipeMap, p))
                {
                    TileFlags& coming = pipeMap[p.first][p.second + 1].comingFrom;
                    std::vector<Pos>& pathSoFar = path[p.first][p.second + 1];
                    coming.west = 1;
                    nextPendingToProcess.emplace_back(std::make_pair(p.first, p.second + 1));
                    if (pathSoFar.size() > 0)
                    {
                        finished = true;
                        std::copy(pathSoFar.begin(), pathSoFar.end(), std::back_inserter(loopPath));
                        std::copy(myPathSoFar.rbegin(), myPathSoFar.rend(), std::back_inserter(loopPath));
                        break;
                    }
                    pathSoFar.insert(pathSoFar.end(), myPathSoFar.begin(), myPathSoFar.end());
                    pathSoFar.emplace_back(std::make_pair(p.first, p.second + 1));
                }
                if (CanGoWest(pipeMap, p))
                {
                    TileFlags& coming = pipeMap[p.first][p.second - 1].comingFrom;
                    std::vector<Pos>& pathSoFar = path[p.first][p.second - 1];
                    coming.east = 1;
                    nextPendingToProcess.emplace_back(std::make_pair(p.first, p.second - 1));
                    if (pathSoFar.size() > 0)
                    {
                        finished = true;
                        std::copy(pathSoFar.begin(), pathSoFar.end(), std::inserter(loopPath, loopPath.end()));
                        std::copy(myPathSoFar.rbegin(), myPathSoFar.rend(), std::inserter(loopPath, loopPath.end()));
                        break;
                    }
                    pathSoFar.insert(pathSoFar.end(), myPathSoFar.begin(), myPathSoFar.end());
                    pathSoFar.emplace_back(std::make_pair(p.first, p.second - 1));
                }
                
            }
            nextPendingToProcess.swap(pendingToProcess);
        }
        Dist result = 0;

        auto it = loopPath.begin();
        bool inLoop = it->first > (it + 1)->first;
        while (it->first == (it + 1)->first)
        {
            inLoop = it->first > (it + 1)->first;
        }

        for (size_t fila = 0; fila < 150; ++fila)
        {
            //bool inLoop = false;
            //int pipeIn = 0;
            bool esquerre = true;
            for (size_t columna = 0; columna < 150; ++columna)
            {
                const Tile& t = pipeMap[fila][columna];
                Pos p1 = std::make_pair(fila, columna);
                auto it = std::find(loopPath.begin(), loopPath.end(), p1);
                if (it != loopPath.end())
                {
                    auto jt = it + 1;
                    Pos siguiente = * jt;

                    auto lt = it;
                    if (lt == loopPath.begin())
                    {
                        lt = loopPath.end() - 2;
                    }
                    else
                    {
                        lt = lt - 1;
                    }
                    Pos previous = *lt;
                    
                    if (siguiente.first > p1.first) //  |
                    {
                        esquerre = false;
                    }
                    else if (siguiente.first < p1.first) //  |
                    {
                        esquerre = true;
                    }
                    else if (previous.first > p1.first)
                    {
                        esquerre = true;
                    }
                    else if (previous.first < p1.first)
                    {
                        esquerre = false;
                    }
                    
                }
                else
                {
                    if (esquerre == inLoop)
                    {
                        result++;
                    }
                }
            }
        }
        //3912
        //305
        //Esta malament lo de dreta i esquerra...
        std::cout << result << std::endl;
	}

   
    

	}