#include "StdAfx.h"
#include "Challenge3.h"

namespace challenge5
{
    using SeedId = unsigned long long;
    using RangeLen = unsigned long long;
    using Range = std::pair<SeedId, RangeLen>;

	void Part2()
	{
        SeedId result = 0;
        std::ifstream input("input5.txt");

        std::string line;

        //Seeds

        std::getline(input, line);
        auto seedsList = split(" ", line);
        std::vector<Range> sources;
        SeedId currentSeed = 0;
        for (int i = 1; i < seedsList.size(); ++i)
        {
            if (i % 2)
            {
                currentSeed = ston<SeedId>(seedsList[i]);
            }
            else
            {
                sources.emplace_back(std::make_pair(currentSeed, ston<RangeLen>(seedsList[i])));
            }
        }

        std::vector<Range> destinations;
        while (std::getline(input, line))
        {
            if (line.size() == 0)
            {

            }
            else if (line.find_last_of(":") != std::string::npos)
            {
                //section swap
                for (auto it = sources.begin(); it != sources.end(); ++it)
                {
                    destinations.emplace_back(*it);
                }
                sources.clear();
                sources.swap(destinations);
            }
            else
            {
                auto [destinationId, sourceId, size] = fragment<3, SeedId>(" ", line);
                Range target(sourceId, size);
                std::vector<Range> newSources;
                newSources.reserve(sources.size());
                for (auto it = sources.begin(); it != sources.end();)
                {
                    Range source = *it;
                    SeedId initialS = source.first;
                    SeedId finalS = source.first + (source.second-1);
                    SeedId initialT = target.first;
                    SeedId finalT = target.first + (target.second - 1);
                    if (initialS <= finalT && initialT <= finalS)
                    {
                        //std::set<SeedId> points {initialS, finalS, initialT, finalT};
                        SeedId overlapStart = std::max(initialS, initialT);
                        SeedId overlapEnd = std::min(finalS, finalT);
                        std::optional<SeedId> previous;

                        if (overlapStart > initialS)
                        {
                            Range remaining(initialS, overlapStart - initialS);
                            newSources.emplace_back(remaining);
                        }
                        if (overlapEnd < finalS)
                        {
                            Range remaining(overlapEnd + 1, finalS - (overlapEnd + 1));
                            newSources.emplace_back(remaining);
                        }

                        auto newDest = destinationId + (overlapStart - initialT);
                        Range r(newDest, overlapEnd - overlapStart);
                        destinations.emplace_back(r);
                    }
                    else
                    {
                        newSources.emplace_back(*it);
                    }
                    it++;
                }
                sources.swap(newSources);

            }
        }

        for (auto it = sources.begin(); it != sources.end(); ++it)
        {
            destinations.emplace_back(*it);
        }

        auto resultIt = std::min_element(destinations.begin(), destinations.end());
        result = resultIt->first;

        std::cout << result << std::endl;
	}


	void Part1()
	{
        SeedId result = 0;
        std::ifstream input("input5_sample.txt");
        
        std::string line;

        //Seeds
        
        std::getline(input, line);
        auto seedsList = split(" ", line);
        std::vector<SeedId> sources;
        for (int i = 1; i < seedsList.size(); ++i)
        {
            sources.emplace_back(ston<SeedId>(seedsList[i]));
        }
        
        std::vector<SeedId> destinations;
        while (std::getline(input, line))
        {
            if (line.size() == 0)
            {
                
            }
            else if (line.find_last_of(":") != std::string::npos)
            {
                //section swap
                for (auto it = sources.begin(); it != sources.end(); ++it)
                {
                    destinations.emplace_back(*it);
                }
                sources.clear();
                sources.swap(destinations);
            }
            else 
            {
                auto[destinationId, sourceId, size]  = fragment<3, SeedId>(" ", line);
                
                for (auto it = sources.begin(); it != sources.end();)
                {
                    SeedId s = *it;
                    if (s >= sourceId && s < sourceId + size)
                    {
                        auto newDest = destinationId + (s - sourceId);
                        destinations.emplace_back(newDest);
                        it = sources.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
                
            }
        }

        for (auto it = sources.begin(); it != sources.end(); ++it)
        {
            destinations.emplace_back(*it);
        }
        
        result = *std::min_element(destinations.begin(), destinations.end());
       

        std::cout << result << std::endl;
	}
}